#include <boost/atomic.hpp>

#define relaxed boost::memory_order_relaxed
#define acquire boost::memory_order_acquire
#define release boost::memory_order_release

template<typename T>
class spscMailbox {
  /*
   * The spscMailbox require that only one thread is writing (the publisher)
   * and one thread is reading (the subscriber).
   * Note that it may be the same thread.
   * read will always read the latest available value.
   */
public:
  spscMailbox() : w_pos(0), r_pos(1) {}

  bool write(const T & value) {
    // Go the furthest
    uint8_t next_pos = before(r_pos.load(acquire));
    ring[next_pos] = value;
    // Compute if this was an overwrite before updating w_pos
    bool overwrite = next_pos == w_pos.load(relaxed);
    w_pos.store(next_pos, release);
    return overwrite;
  }

  bool read(T & value) {
    /*
     * The value is ensured to be untouched between two calls to pop.
     * This is the main guarantee needed to have T a pointer type.
     * The returned value indicate if value changed since last call to pop.
     */
    // Go the furthest
    uint8_t next_pos = before(w_pos.load(acquire)); //TODO: Clearly wrong!!
    // Compute if we made progress before updating r_pos
    bool overwrite = next_pos == r_pos.load(relaxed);
    // Mark that the writer can advance, we need only next_pos to stay safe.
    r_pos.store(next_pos, release);
    value = ring[next_pos];
    return overwrite;
  }
private:
  uint8_t before(uint8_t p) {
    return (p == 0) ? 2 : p - 1;
  }
  T ring[3];
  boost::atomic<uint8_t> w_pos, r_pos;
};


template<typename T, size_t Size>
class spscInplaceMailbox {
public:
  spscMailbox(T initial_value) :
    written_pos(0), reading_pos(0), writting_pos(1) {
    ring[0] = initial_value;
  }

  //TODO: prevent copies, etc.

  T* commit_n_stall(bool& overwrite) {
    // Try to go to the next position if possible
    size_t next_pos = after(writting_pos);
    overwrite = next_pos == reading_pos.load(acquire);
    if (overwrite) {
      // We can't advance, we have to continue writing at the same position.
      return &ring[writting_pos];
    }
    else {
      // Commit: Mark previous writing as available
      written_pos.store(writting_pos, release);
      // Stall: Next slot
      writting_pos++;
      return &ring[writting_pos];
    }
  }

  T* update_n_release(bool& stale) {
    // Go to the furthest
    uint8_t next_pos = written_pos.load(acquire);
    // Compute if we made progress before updating r_pos
    stale = next_pos == reading_pos.load(relaxed);
    if !stale { // We got an update, we can release previous position.
      // Release: Mark that the writer can advance, we need only next_pos.
      reading_pos.store(next_pos, release);
    }
    return &ring[next_pos];
  }

private:
  T ring[Size];
  boost::atomic<size_t> written_pos, reading_pos;
  size_t writting_pos;

  /* Utility functions to compute a fast modulo. */
  inline size_t before(size_t p) { return (p == 0) ? Size : p - 1; }
  inline size_t after(size_t p) { p++; return (p == Size) ? 0 : p; }
};
