/* Adapted 2014 by Lennart Beringer from OpenSSL091c crypto/hmac/hmac.c 
 * Copyright (c) 2004 The OpenSSL Project.  All rights reserved
 * according to the OpenSSL license.

 * Specializes openssl's file to use the hash function sha256, avoiding 
 * use of "object-oriented" programming style (engines etc) used in 
 * recent versions of openssl.  
 */

/* crypto/hmac/hmac.c */
/* Copyright (C) 1995-1998 Eric Young (eay@cryptsoft.com)
 * All rights reserved.
 *
 * This package is an SSL implementation written
 * by Eric Young (eay@cryptsoft.com).
 * The implementation was written so as to conform with Netscapes SSL.
 * 
 * This library is free for commercial and non-commercial use as long as
 * the following conditions are aheared to.  The following conditions
 * apply to all code found in this distribution, be it the RC4, RSA,
 * lhash, DES, etc., code; not just the SSL code.  The SSL documentation
 * included with this distribution is covered by the same copyright terms
 * except that the holder is Tim Hudson (tjh@cryptsoft.com).
 * 
 * Copyright remains Eric Young's, and as such any Copyright notices in
 * the code are not to be removed.
 * If this package is used in a product, Eric Young should be given attribution
 * as the author of the parts of the library used.
 * This can be in the form of a textual message at program startup or
 * in documentation (online or textual) provided with the package.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    "This product includes cryptographic software written by
 *     Eric Young (eay@cryptsoft.com)"
 *    The word 'cryptographic' can be left out if the rouines from the library
 *    being used are not cryptographic related :-).
 * 4. If you include any Windows specific code (or a derivative thereof) from 
 *    the apps directory (application code) you must include an acknowledgement:
 *    "This product includes software written by Tim Hudson (tjh@cryptsoft.com)"
 * 
 * THIS SOFTWARE IS PROVIDED BY ERIC YOUNG ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * 
 * The licence and distribution terms for any publically available version or
 * derivative of this code cannot be changed.  i.e. this code cannot simply be
 * copied and put under another distribution licence
 * [including the GNU Public Licence.]
 */

#include "HACMS_hmac.h"

void HACMS_HMAC_Init(HACMS_HMAC_CTX *ctx, unsigned char *key, int len)
{
     int i,j,reset=0;
     unsigned char pad[HACMS_HMAC_MAX_MD_CBLOCK];

     unsigned char aux; // for the initialization loops

     if (key != NULL)
       {
         reset=1;
         j= HACMS_HMAC_MAX_MD_CBLOCK;
      	 if (j < len)
	   {
             HACMS_SHA256_Init(&ctx->md_ctx);
	     HACMS_SHA256_Update(&ctx->md_ctx,key,len);
	     HACMS_SHA256_Final(ctx->key,&(ctx->md_ctx));
	     memset(&(ctx->key[32]),0,32);
	     ctx->key_length=32;
	   }
	 else
	   {
	     memcpy(ctx->key,key,len);
	     memset(&(ctx->key[len]),0,sizeof(ctx->key)-len);
	     ctx->key_length=len; 
           }
       }
     
     if (reset)	
       {
	 for (i=0; i<HACMS_HMAC_MAX_MD_CBLOCK; i++)  {
           aux = ctx->key[i];
	   aux = 0x36^aux;
           pad[i]=aux; 
         }

         HACMS_SHA256_Init(&ctx->i_ctx);
	 HACMS_SHA256_Update(&ctx->i_ctx,pad,HACMS_HMAC_MAX_MD_CBLOCK);
	 
	 
	 for (i=0; i<HACMS_HMAC_MAX_MD_CBLOCK; i++) {
           aux = ctx->key[i];
	   pad[i]= 0x5c^aux;
         }

	 HACMS_SHA256_Init(&ctx->o_ctx);
	 HACMS_SHA256_Update(&ctx->o_ctx,pad,HACMS_HMAC_MAX_MD_CBLOCK);
       }
     
     memcpy(&ctx->md_ctx,&ctx->i_ctx,sizeof(ctx->i_ctx));
}

void HACMS_HMAC_Update(HACMS_HMAC_CTX *ctx, const void *data, size_t len)
{
  HACMS_SHA256_Update(&(ctx->md_ctx),data,len);
}

void HACMS_HMAC_Final(HACMS_HMAC_CTX *ctx, unsigned char *md)
{
  unsigned char buf[HACMS_SHA256_DIGEST_LENGTH]; 
  
  HACMS_SHA256_Final(buf,&(ctx->md_ctx));

  memcpy(&(ctx->md_ctx),&(ctx->o_ctx),sizeof(ctx->o_ctx));

  HACMS_SHA256_Update(&(ctx->md_ctx),buf,HACMS_SHA256_DIGEST_LENGTH);

  HACMS_SHA256_Final(md,&(ctx->md_ctx));
}

void HACMS_HMAC_cleanup(HACMS_HMAC_CTX *ctx)
{
  memset(ctx,0,sizeof(HACMS_HMAC_CTX));
}

unsigned char *HACMS_HMAC( unsigned char *key, int key_len, 
                    unsigned char *d, int n, 
                    unsigned char *md)
	{
	HACMS_HMAC_CTX c;
	static unsigned char m[HACMS_SHA256_DIGEST_LENGTH];

	if (md == NULL) md=m;

        HACMS_HMAC_Init(&c, key, key_len);

	HACMS_HMAC_Update(&c,d,n);
	HACMS_HMAC_Final(&c,md); 
	HACMS_HMAC_cleanup(&c);
	return(md);
	}
