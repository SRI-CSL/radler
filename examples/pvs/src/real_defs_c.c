//Code generated using pvs2ir2c
#include "real_defs_c.h"

extern mpz_ptr_t real_defs__sgn(mpq_ptr_t ivar_2){
        mpz_ptr_t  result;
        bool_t ivar_3;
        mpq_ptr_t ivar_4;
        //copying to mpq from mpq;
        mpq_mk_set(ivar_4, ivar_2);
        uint8_t ivar_5;
        ivar_5 = (uint8_t)0;
        int64_t tmp14296 = mpq_cmp_ui(ivar_4, ivar_5, 1);
        ivar_3 = (tmp14296 >= 0);
        if (ivar_3){ 
             result = safe_malloc(sizeof(mpz_t));
             mpz_init(result);
             mpz_mk_set_ui(result, 1);
} else {
        
             result = safe_malloc(sizeof(mpz_t));
             mpz_init(result);
             mpz_mk_set_si(result, -1);
};

        
        return result;
}

extern mpq_ptr_t real_defs__abs(mpq_ptr_t ivar_2){
        mpq_ptr_t  result;
        bool_t ivar_3;
        mpq_ptr_t ivar_4;
        //copying to mpq from mpq;
        mpq_mk_set(ivar_4, ivar_2);
        uint8_t ivar_5;
        ivar_5 = (uint8_t)0;
        int64_t tmp14297 = mpq_cmp_ui(ivar_4, ivar_5, 1);
        ivar_3 = (tmp14297 < 0);
        if (ivar_3){ 
             mpq_ptr_t ivar_7;
             //copying to mpq from mpq;
             mpq_mk_set(ivar_7, ivar_2);
             mpq_mk_set(result, ivar_7);
             mpq_neg(result, result);
} else {
        
             //copying to mpq from mpq;
             mpq_mk_set(result, ivar_2);
};

        
        return result;
}

extern mpq_ptr_t real_defs__max(mpq_ptr_t ivar_2, mpq_ptr_t ivar_3){
        mpq_ptr_t  result;
        bool_t ivar_4;
        mpq_ptr_t ivar_5;
        //copying to mpq from mpq;
        mpq_mk_set(ivar_5, ivar_2);
        mpq_ptr_t ivar_6;
        //copying to mpq from mpq;
        mpq_mk_set(ivar_6, ivar_3);
        int64_t tmp14298 = mpq_cmp(ivar_5, ivar_6);
        ivar_4 = (tmp14298 < 0);
        if (ivar_4){ 
             //copying to mpq from mpq;
             mpq_mk_set(result, ivar_3);
} else {
        
             //copying to mpq from mpq;
             mpq_mk_set(result, ivar_2);
};

        
        return result;
}

extern mpq_ptr_t real_defs__min(mpq_ptr_t ivar_2, mpq_ptr_t ivar_3){
        mpq_ptr_t  result;
        bool_t ivar_4;
        mpq_ptr_t ivar_5;
        //copying to mpq from mpq;
        mpq_mk_set(ivar_5, ivar_2);
        mpq_ptr_t ivar_6;
        //copying to mpq from mpq;
        mpq_mk_set(ivar_6, ivar_3);
        int64_t tmp14299 = mpq_cmp(ivar_5, ivar_6);
        ivar_4 = (tmp14299 > 0);
        if (ivar_4){ 
             //copying to mpq from mpq;
             mpq_mk_set(result, ivar_3);
} else {
        
             //copying to mpq from mpq;
             mpq_mk_set(result, ivar_2);
};

        
        return result;
}