//Code generated using pvs2ir2c
#include "exp2_c.h"

extern mpz_ptr_t exp2__exp2(mpz_ptr_t ivar_2){
        mpz_ptr_t  result;
        bool_t ivar_3;
        uint8_t ivar_5;
        ivar_5 = (uint8_t)0;
        int64_t tmp14301 = mpz_cmp_ui(ivar_2, ivar_5);
        ivar_3 = (tmp14301 == 0);
        if (ivar_3){ 
             result = safe_malloc(sizeof(mpz_t));
             mpz_init(result);
             mpz_mk_set_ui(result, 1);
} else {
        
             uint8_t ivar_7;
             ivar_7 = (uint8_t)2;
             mpz_ptr_t ivar_8;
             mpz_ptr_t ivar_14;
             uint8_t ivar_11;
             ivar_11 = (uint8_t)1;
             mpz_mk_sub_ui(ivar_14, ivar_2, (uint64_t)ivar_11);
             ivar_8 = (mpz_ptr_t)exp2__exp2(ivar_14);
             mpz_mk_mul_ui(result, ivar_8, (uint64_t)ivar_7);
};

        
        return result;
}

extern mpz_ptr_t exp2__log2(mpz_ptr_t ivar_2){
        mpz_ptr_t  result;
        bool_t ivar_3;
        uint8_t ivar_5;
        ivar_5 = (uint8_t)0;
        int64_t tmp14302 = mpz_cmp_ui(ivar_2, ivar_5);
        ivar_3 = (tmp14302 == 0);
        if (ivar_3){ 
             result = safe_malloc(sizeof(mpz_t));
             mpz_init(result);
             mpz_mk_set_ui(result, 0);
} else {
        
             mpz_ptr_t ivar_7;
             mpz_ptr_t ivar_14;
             uint8_t ivar_11;
             ivar_11 = (uint8_t)2;
             mpz_mk_fdiv_q_ui(ivar_14, ivar_2, ivar_11);
             ivar_7 = (mpz_ptr_t)exp2__log2(ivar_14);
             uint8_t ivar_8;
             ivar_8 = (uint8_t)1;
             mpz_mk_set_ui(result, (uint64_t)ivar_8);
             mpz_add(result, result, ivar_7);
};

        
        return result;
}