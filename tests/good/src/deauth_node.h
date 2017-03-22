#include RADL_HEADER
//#include "RADLAST.h"

#include "stdio.h"
#include <stdbool.h>
#include <openssl/ssl.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include "HACMS_hmac.h"

/* FIXME: Replace these stubs with their actual definitions */
typedef unsigned char session_key_t[64];
typedef unsigned char hmac_digest_t[32];
typedef unsigned char public_key_t[2048/8];
#define ENCRYPT(data,pub_key) data
#define MAKE_SESSION_KEY NULL

typedef struct {
  session_key_t session_key;
  public_key_t public_key;
} RADL_STATE;

void RADL_INIT_FUN(RADL_STATE* s) {
  /* Initialize the public key from the file "pubkey.pem" and initialize 
     the session key using random number generation */

  FILE *fp1;
  fp1 = fopen("deauthnode_init", "w");
  if (fp1 == NULL) { 
    fprintf(stderr,"DEAUTH(init): could not open file for writing.\n");
    return; 
  }
  fprintf(fp1,"DEAUTH(init): file initialized\n"); 
  fflush(fp1);

  SSL_library_init();
  OpenSSL_add_all_algorithms();
  SSL_load_error_strings();
  ERR_load_crypto_strings();
  OPENSSL_config(NULL);

  fprintf(fp1,"DEAUTH(init): openssl loaded\n");
  fflush(fp1);
  
  FILE *fp;
  fp = fopen("pubkey.pem", "r");
  if (fp == NULL) {
    fprintf(fp1,"DEAUTH(init): pubkey.pem NOT found.\n");
    fflush(fp1);
    return;
  }
  char c; int i=0;
  while ( (c = fgetc(fp)) != EOF ) {
    s->public_key[i] = c;
    i++;
  }
  fclose(fp);

  fprintf(fp1,"DEAUTH(init): public key read\n");
  fflush(fp1);
    
  //Seed random generator by reading from /dev/random
  int randombytes = 2048; //TODO: OK many bytes?
  int r = RAND_load_file("/dev/urandom", randombytes);
  if ( r != randombytes ) {
    fprintf(fp1,"DEAUTH(init): RAND_load_file returned UNEXPECTED value\n");
    fflush(fp1);
    return; 
  }
  
  fprintf(fp1,"DEAUTH(init): random data read\n");
  fflush(fp1);
    
  unsigned char buf[64];
  int rc = RAND_bytes(buf, 64);
  if (rc == 1) {
    int j;
    for (j=0; j<64; j++) {
      s->session_key[j] = buf[j];
    }
  }
  fprintf(fp1,"DEAUTH(init): initialization successful, content = %d\n",
              s->session_key[0]);
  
  fclose (fp1);
  return;  
}

void send_session_key (RADL_STATE* s, radl_out_t * o) {
  //WAS: o->key->key = ENCRYPT (s->session_key, s->public_key);
  
  //allocate a new RSA structure
  RSA *rsa;
  if (!(rsa = RSA_new())) { return; }

  //no blinding done here, since blinding only concerns operations on
  //private key. 

  unsigned char buffer[RSA_size(rsa)]; 
  int flen = 64;
  if (flen < RSA_size(rsa) - 41) { 
    // for PKCS1_OAEP_PADDING 
    
    int r = RSA_public_encrypt(flen,s->session_key, buffer, 
			       rsa, RSA_PKCS1_OAEP_PADDING);
    if (r == RSA_size(rsa)) {
      int j;
      for (j=0; j<r; j++) {
        o->key->key[j] = buffer[j];
      }
    }
  }
  RSA_free(rsa); 
  return; 
}

void RADL_STEP_FUN(RADL_STATE* s, const radl_in_t * i, const radl_in_flags_t *inf,
                  radl_out_t * o, radl_out_flags_t * of) {
  fprintf (stdout, "DEAUTH(step): starting step\n");
  fflush(stdout);
  fprintf (stderr, "DEAUTH(step): starting step\n");
  fflush(stderr);
  FILE *fp1;
  fp1 = fopen("deauthnode_step", "w+");
  if (fp1 == NULL) { 
    fprintf(stderr, "DEAUTH(step): could not open file for writing.\n");
    fflush(stderr);
    return;
  }
  fprintf(fp1,"DEAUTH(step): file initialized.\n"); 
  fflush(fp1);

  /* Send the current session key, encrypted */ 
  send_session_key(s, o);
  fprintf(fp1,"DEAUTH(step): session key has been sent.\n"); 
  fflush(fp1);

  /* Check if the input data matches its HMAC field */
  unsigned char *local_hmac;
  if (NULL == (local_hmac = (unsigned char *)malloc(32 * sizeof(unsigned char)))) {
    fprintf(fp1,"DEAUTH(step): malloc of local_hmac failed.\n"); 
    fclose(fp1);
    return;
  }
  unsigned char *data;
  if (NULL == (data = (unsigned char *)malloc(40*sizeof(unsigned char)))) {
    fprintf(fp1,"DEAUTH(step): malloc of emptorrary buffer DATA failed.\n"); 
    fclose(fp1);
    return;
  }
  int j;
  for (j=0; j<40; j++) {
    data[j] = i->i1->auth_data[j];
  }
  (int8_t *)HACMS_HMAC(s->session_key,64,data,40, local_hmac);
  fprintf(fp1,"DEAUTH(step): HMAC calculated.\n");
  fflush(fp1);
  
  bool ok = true;
  for (j = 0; j<32; j++) {
    if (local_hmac[j] != i->i1->hmac[j]) { ok = false;}
  }

  if (ok) {
    /* If so, forward the data on */
    fprintf(fp1,"DEAUTH(step): HMAC ok. Now forwarding data.\n");
    fflush(fp1);
    for (j=0; j<40 ; j++) {
      o->o1->sink_data[j] = data[j];
    }
    
    /* FIXME (need help from Leonard): how to forward the flags? */
  }
  fprintf(fp1,"DEAUTH(step): step completed successfully.\n"); 
  fclose(fp1);
}

void RADL_FINISH_FUN(RADL_STATE* s) {
  EVP_cleanup();
  CRYPTO_cleanup_all_ex_data();
  ERR_free_strings();
}
