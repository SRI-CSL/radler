#include RADL_HEADER

#include "stdio.h"
#include <openssl/ssl.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include "HACMS_hmac.h"

/* FIXME: Replace these stubs with their actual definitions */
typedef unsigned char session_key_t[64];
typedef unsigned char private_key_t[2048/8];
//#define DECRYPT(data,priv_key) data

typedef struct {
  session_key_t session_key;
  private_key_t private_key;
} RADL_STATE;

void RADL_INIT_FUN(RADL_STATE* s) {

  FILE *fp1;
  fp1 = fopen("authnode_init", "w");
  if (fp1 == NULL) { 
    printf("AUTH(init): could not open file for writing.\n");
    return; 
  }
  fprintf(fp1,"AUTH(init): file initialized\n"); 

  SSL_library_init();
  OpenSSL_add_all_algorithms();
  SSL_load_error_strings();
  ERR_load_crypto_strings();
  OPENSSL_config(NULL);

  fprintf(fp1,"AUTH(init): openssl loaded\n");

  /* Initialize the private key from the file "privkey.pem" and set the 
     session key to be NULL. */

  fprintf(fp1,"AUTH(init): openssl loaded\n");

  FILE *fp;
  fp = fopen("privkey.pem", "r");
  if (fp == NULL) { 
    printf("AUTH(init): privkey.pem NOT found. Terminating AUTH.\n");
    return; 
  }
  char c; int i=0;
  while ( (c = fgetc(fp)) != EOF ) {
    s->private_key[i] = c;
    i++;
  }
  fclose (fp);

  int j;
  for (j=0; j<64; j++) {
    s->session_key[j] = 0;
  }
  fprintf(fp1,"AUTH(init): initialization successful, content = %d\n", 
         s->private_key[0]);
  fclose (fp1);
}

void RADL_STEP_FUN(RADL_STATE* s, const radl_in_t * i, const radl_in_flags_t *inf,
                  radl_out_t * o, radl_out_flags_t * of) {
  FILE *fp1;
  fp1 = fopen("authnode_step", "w");
  if (fp1 == NULL) { 
    printf("AUTH(step): could not open file for writing.\n");
    return; 
  }
  fprintf(fp1,"AUTH(step): file initialized\n");

  /* Test if there is a new session key */
  if (!radl_is_stale (inf->key)) {
    /* decrypt the key in i->key->key, and store it in s->session_key */
    //WAS: s->session_key = DECRYPT(i->key->key,s->private_key);
    
    //allocate a new RSA structure
    RSA *rsa;
    if (!(rsa = RSA_new())) { return; }
    if (RSA_blinding_on(rsa, NULL) == 0) {
      fprintf(fp1,"AUTH(step): RSA blinding failed, Terminating step. \n");
      fclose (fp1);
      return;
    }
    int r = RSA_private_decrypt(RSA_size(rsa),i->key->key, s->session_key, 
				rsa, RSA_PKCS1_OAEP_PADDING);
    RSA_blinding_off(rsa); // frees the memory associated with blinding 
    RSA_free(rsa);
  }

  /* This just forwards input data to the output */
  int j;
  for (j=0; j < 40; j++) {
    o->o1->auth_data[j] = i->i1->source_data[j];
  }

  /* FIXME (need help from Leonard): how to forward the flags? */

  /* set o->o1->hmac to the correct HMAC value */
  unsigned char *data;
  data = (unsigned char *)malloc(40*sizeof(unsigned char));
  for (j=0; j<40; j++) {
    data[j] = i->i1->source_data[j];
  }

  unsigned char *hmac_value;
  hmac_value = (unsigned char *)malloc(32*sizeof(unsigned char));
  (int8_t *)HACMS_HMAC(s->session_key,64,data,40,hmac_value);

  fprintf(fp1,"AUTH(step): HMAC calculated.\n");
  for (j=0; j<32; j++) {
    o->o1->hmac[j] = hmac_value[j]; 
  }

  fprintf(fp1,"AUTH(step): HMAC'ed message sent. Leaving step-function.\n");
  fclose (fp1);
}

void RADL_FINISH_FUN(RADL_STATE* s) {
  EVP_cleanup();
  CRYPTO_cleanup_all_ex_data();
  ERR_free_strings();
}
