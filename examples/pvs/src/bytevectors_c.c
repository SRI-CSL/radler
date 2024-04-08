//Code generated using pvs2ir2c
#include "bytevectors_c.h"


bytevectors__byv_t new_bytevectors__byv(uint32_t size){
        bytevectors__byv_t tmp = (bytevectors__byv_t) safe_malloc(sizeof(struct bytevectors__byv_s) + (size * sizeof(uint8_t)));
        tmp->count = 1;
        tmp->size = size;;
        tmp->max = size;
         return tmp;}

void release_bytevectors__byv(bytevectors__byv_t x, uint32_t bytevectors__n){
        x->count--;
         if (x->count <= 0){safe_free(x);}
}

void release_bytevectors__byv_ptr(pointer_t x, type_actual_t T){
        actual_bytevectors__byv_t actual = (actual_bytevectors__byv_t)T;
        uint32_t bytevectors__n = actual->bytevectors__n;
        release_bytevectors__byv((bytevectors__byv_t)x, bytevectors__n);
}

bytevectors__byv_t copy_bytevectors__byv(bytevectors__byv_t x){
        bytevectors__byv_t tmp = new_bytevectors__byv(x->size);
        tmp->count = 1;
        for (uint32_t i = 0; i < x->size; i++){tmp->elems[i] = (uint8_t)x->elems[i];};
         return tmp;}

bool_t equal_bytevectors__byv(bytevectors__byv_t x, bytevectors__byv_t y, uint32_t bytevectors__n){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = (x->elems[i] == y->elems[i]); i++;};
        return tmp;}

bool_t equal_bytevectors__byv_ptr(pointer_t x, pointer_t y, type_actual_t T){
        actual_bytevectors__byv_t actual = (actual_bytevectors__byv_t)T;
        uint32_t bytevectors__n = actual->bytevectors__n;
        return equal_bytevectors__byv((bytevectors__byv_t)x, (bytevectors__byv_t)y, bytevectors__n);
}

actual_bytevectors__byv_t actual_bytevectors__byv(uint32_t bytevectors__n){
        actual_bytevectors__byv_t new = (actual_bytevectors__byv_t)safe_malloc(sizeof(struct actual_bytevectors__byv_s));
        new->equal_ptr = (equal_ptr_t)(*equal_bytevectors__byv_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_bytevectors__byv_ptr);
 

        new->bytevectors__n = bytevectors__n;
 
        return new;
 };

bytevectors__byv_t update_bytevectors__byv(bytevectors__byv_t x, uint32_t i, uint8_t v, uint32_t bytevectors__n){
        bytevectors__byv_t y; 
         if (x->count == 1){y = x;}
           else {y = copy_bytevectors__byv(x );
                x->count--;};
        y->elems[i] = (uint8_t)v;
        return y;}

bytevectors__byv_t upgrade_bytevectors__byv(bytevectors__byv_t x, uint32_t i, uint8_t v, uint32_t bytevectors__n){
        bytevectors__byv_t y; 
         if (x->count == 1 && i < x->max){y = x;}
           else if (i > x->max){uint32_t newmax = x->max <= UINT32_MAX/2 ? 2*x->max: UINT32_MAX;
                y = safe_realloc(x, sizeof(struct bytevectors__byv_s) + (newmax * sizeof(uint8_t)));
                y->count = 1;
                y->size = i+1;
                y->max = newmax;
                release_bytevectors__byv(x, bytevectors__n);}
           else {y = copy_bytevectors__byv(x );
                x->count--;};
        y->elems[i] = (uint8_t)v;
        return y;}



extern bytevectors__byv_t bytevectors__byvand(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, bytevectors__byv_t ivar_3){
        bytevectors__byv_t  result;
        uint32_t size16089;
        //copying to uint32 from uint32;
        size16089 = (uint32_t)bytevectors__n;
        size16089 += 0;
        result = new_bytevectors__byv(size16089);
        uint32_t ivar_4;
        for (uint32_t index16088 = 0; index16088 < size16089; index16088++){
             ivar_4 = (uint32_t)index16088;
             uint8_t ivar_16;
             ivar_16 = (uint8_t)ivar_2->elems[ivar_4];
             uint8_t ivar_17;
             ivar_17 = (uint8_t)ivar_3->elems[ivar_4];
             result->elems[index16088] = (uint8_t)integer_bv_ops__u8and((uint8_t)ivar_16, (uint8_t)ivar_17);
        };
        release_bytevectors__byv(ivar_2, bytevectors__n);
        release_bytevectors__byv(ivar_3, bytevectors__n);

        
        return result;
}

extern bytevectors__byv_t bytevectors__byvor(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, bytevectors__byv_t ivar_3){
        bytevectors__byv_t  result;
        uint32_t size16092;
        //copying to uint32 from uint32;
        size16092 = (uint32_t)bytevectors__n;
        size16092 += 0;
        result = new_bytevectors__byv(size16092);
        uint32_t ivar_4;
        for (uint32_t index16091 = 0; index16091 < size16092; index16091++){
             ivar_4 = (uint32_t)index16091;
             uint8_t ivar_16;
             ivar_16 = (uint8_t)ivar_2->elems[ivar_4];
             uint8_t ivar_17;
             ivar_17 = (uint8_t)ivar_3->elems[ivar_4];
             result->elems[index16091] = (uint8_t)integer_bv_ops__u8or((uint8_t)ivar_16, (uint8_t)ivar_17);
        };
        release_bytevectors__byv(ivar_2, bytevectors__n);
        release_bytevectors__byv(ivar_3, bytevectors__n);

        
        return result;
}

extern bytevectors__byv_t bytevectors__byvxor(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, bytevectors__byv_t ivar_3){
        bytevectors__byv_t  result;
        uint32_t size16095;
        //copying to uint32 from uint32;
        size16095 = (uint32_t)bytevectors__n;
        size16095 += 0;
        result = new_bytevectors__byv(size16095);
        uint32_t ivar_4;
        for (uint32_t index16094 = 0; index16094 < size16095; index16094++){
             ivar_4 = (uint32_t)index16094;
             uint8_t ivar_16;
             ivar_16 = (uint8_t)ivar_2->elems[ivar_4];
             uint8_t ivar_17;
             ivar_17 = (uint8_t)ivar_3->elems[ivar_4];
             result->elems[index16094] = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_16, (uint8_t)ivar_17);
        };
        release_bytevectors__byv(ivar_2, bytevectors__n);
        release_bytevectors__byv(ivar_3, bytevectors__n);

        
        return result;
}

extern bytevectors__byv_t bytevectors__byvnot(uint32_t bytevectors__n, bytevectors__byv_t ivar_2){
        bytevectors__byv_t  result;
        uint32_t size16098;
        //copying to uint32 from uint32;
        size16098 = (uint32_t)bytevectors__n;
        size16098 += 0;
        result = new_bytevectors__byv(size16098);
        uint32_t ivar_3;
        for (uint32_t index16097 = 0; index16097 < size16098; index16097++){
             ivar_3 = (uint32_t)index16097;
             uint8_t ivar_10;
             ivar_10 = (uint8_t)ivar_2->elems[ivar_3];
             result->elems[index16097] = (uint8_t)integer_bv_ops__u8not((uint8_t)ivar_10);
        };
        release_bytevectors__byv(ivar_2, bytevectors__n);

        
        return result;
}

extern bytevectors__byv_t bytevectors__byvleftrot(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, uint32_t ivar_3){
        bytevectors__byv_t  result;
        uint32_t size16107;
        //copying to uint32 from uint32;
        size16107 = (uint32_t)bytevectors__n;
        size16107 += 0;
        result = new_bytevectors__byv(size16107);
        uint32_t ivar_4;
        for (uint32_t index16106 = 0; index16106 < size16107; index16106++){
             ivar_4 = (uint32_t)index16106;
             uint32_t ivar_16;
             uint32_t ivar_6;
             ivar_6 = (uint32_t)integertypes__u32plus((uint32_t)ivar_3, (uint32_t)ivar_4);
             ivar_16 = (uint32_t)rem_uint32_uint32(ivar_6, bytevectors__n);
             result->elems[index16106] = (uint8_t)ivar_2->elems[ivar_16];
        };
        release_bytevectors__byv(ivar_2, bytevectors__n);

        
        return result;
}

extern uint32_t bytevectors__nextindex(uint32_t bytevectors__n, uint32_t ivar_2){
        uint32_t  result;
        /* j */ uint32_t ivar_3;
        uint8_t ivar_10;
        ivar_10 = (uint8_t)1;
        uint32_t ivar_8;
        //copying to uint32 from uint8;
        ivar_8 = (uint32_t)ivar_10;
        ivar_3 = (uint32_t)integertypes__u32plus((uint32_t)ivar_2, (uint32_t)ivar_8);
        bool_t ivar_11;
        ivar_11 = (ivar_3 == bytevectors__n);
        if (ivar_11){ 
             result = (uint32_t)0;
} else {
        
             //copying to uint32 from uint32;
             result = (uint32_t)ivar_3;
};

        
        return result;
}

extern uint32_t bytevectors__precindex(uint32_t bytevectors__n, uint32_t ivar_2){
        uint32_t  result;
        bool_t ivar_3;
        uint8_t ivar_5;
        ivar_5 = (uint8_t)0;
        ivar_3 = (ivar_2 == ivar_5);
        if (ivar_3){ 
             uint8_t ivar_13;
             ivar_13 = (uint8_t)1;
             uint32_t ivar_11;
             //copying to uint32 from uint8;
             ivar_11 = (uint32_t)ivar_13;
             result = (uint32_t)integertypes__u32minus((uint32_t)bytevectors__n, (uint32_t)ivar_11);
} else {
        
             uint8_t ivar_20;
             ivar_20 = (uint8_t)1;
             uint32_t ivar_18;
             //copying to uint32 from uint8;
             ivar_18 = (uint32_t)ivar_20;
             result = (uint32_t)integertypes__u32minus((uint32_t)ivar_2, (uint32_t)ivar_18);
};

        
        return result;
}

extern bytevectors__byv_t bytevectors__byvrightrot(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, uint32_t ivar_3){
        bytevectors__byv_t  result;
        uint32_t size16124;
        //copying to uint32 from uint32;
        size16124 = (uint32_t)bytevectors__n;
        size16124 += 0;
        result = new_bytevectors__byv(size16124);
        uint32_t ivar_4;
        for (uint32_t index16123 = 0; index16123 < size16124; index16123++){
             ivar_4 = (uint32_t)index16123;
             uint32_t ivar_21;
             uint32_t ivar_6;
             uint32_t ivar_17;
             ivar_17 = (uint32_t)integertypes__u32minus((uint32_t)bytevectors__n, (uint32_t)ivar_4);
             ivar_6 = (uint32_t)integertypes__u32plus((uint32_t)ivar_3, (uint32_t)ivar_17);
             ivar_21 = (uint32_t)rem_uint32_uint32(ivar_6, bytevectors__n);
             result->elems[index16123] = (uint8_t)ivar_2->elems[ivar_21];
        };
        release_bytevectors__byv(ivar_2, bytevectors__n);

        
        return result;
}

extern bytevectors__byv_t bytevectors__byvbitleftrot(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, uint8_t ivar_3){
        bytevectors__byv_t  result;
        uint32_t size16129;
        //copying to uint32 from uint32;
        size16129 = (uint32_t)bytevectors__n;
        size16129 += 0;
        result = new_bytevectors__byv(size16129);
        uint32_t ivar_4;
        for (uint32_t index16128 = 0; index16128 < size16129; index16128++){
             ivar_4 = (uint32_t)index16128;
             uint8_t ivar_34;
             uint8_t ivar_22;
             uint32_t ivar_15;
             ivar_15 = (uint32_t)bytevectors__nextindex((uint32_t)bytevectors__n, (uint32_t)ivar_4);
             ivar_22 = (uint8_t)ivar_2->elems[ivar_15];
             uint8_t ivar_23;
             uint8_t ivar_19;
             ivar_19 = (uint8_t)8;
             ivar_23 = (uint8_t)integertypes__u8minus((uint8_t)ivar_19, (uint8_t)ivar_3);
             ivar_34 = (uint8_t)integertypes__u8lshift((uint8_t)ivar_22, (uint8_t)ivar_23);
             uint8_t ivar_35;
             uint8_t ivar_31;
             ivar_31 = (uint8_t)ivar_2->elems[ivar_4];
             ivar_35 = (uint8_t)integertypes__u8rshift((uint8_t)ivar_31, (uint8_t)ivar_3);
             result->elems[index16128] = (uint8_t)integertypes__u8plus((uint8_t)ivar_34, (uint8_t)ivar_35);
        };
        release_bytevectors__byv(ivar_2, bytevectors__n);

        
        return result;
}

extern bytevectors__byv_t bytevectors__byvbitrightrot(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, uint8_t ivar_3){
        bytevectors__byv_t  result;
        uint32_t size16134;
        //copying to uint32 from uint32;
        size16134 = (uint32_t)bytevectors__n;
        size16134 += 0;
        result = new_bytevectors__byv(size16134);
        uint32_t ivar_4;
        for (uint32_t index16133 = 0; index16133 < size16134; index16133++){
             ivar_4 = (uint32_t)index16133;
             uint8_t ivar_34;
             uint8_t ivar_14;
             ivar_14 = (uint8_t)ivar_2->elems[ivar_4];
             ivar_34 = (uint8_t)integertypes__u8lshift((uint8_t)ivar_14, (uint8_t)ivar_3);
             uint8_t ivar_35;
             uint8_t ivar_31;
             uint32_t ivar_24;
             ivar_24 = (uint32_t)bytevectors__precindex((uint32_t)bytevectors__n, (uint32_t)ivar_4);
             ivar_31 = (uint8_t)ivar_2->elems[ivar_24];
             uint8_t ivar_32;
             uint8_t ivar_28;
             ivar_28 = (uint8_t)8;
             ivar_32 = (uint8_t)integertypes__u8minus((uint8_t)ivar_28, (uint8_t)ivar_3);
             ivar_35 = (uint8_t)integertypes__u8rshift((uint8_t)ivar_31, (uint8_t)ivar_32);
             result->elems[index16133] = (uint8_t)integertypes__u8plus((uint8_t)ivar_34, (uint8_t)ivar_35);
        };
        release_bytevectors__byv(ivar_2, bytevectors__n);

        
        return result;
}

extern bytevectors__byv_t bytevectors__byvleftrotate(uint32_t bytevectors__n, bytevectors__byv_t ivar_5, mpz_ptr_t ivar_6){
        bytevectors__byv_t  result;
        bytevectors__byv_t ivar_25;
        mpz_ptr_t ivar_20;
        uint8_t ivar_15;
        ivar_15 = (uint8_t)8;
        mpz_mk_fdiv_q_ui(ivar_20, ivar_6, ivar_15);
        uint32_t ivar_19;
        //copying to uint32 from mpz;
        ivar_19 = (uint32_t)mpz_get_ui(ivar_20);
        mpz_clear(ivar_20);
        ivar_25 = (bytevectors__byv_t)bytevectors__byvrightrot((uint32_t)bytevectors__n, (bytevectors__byv_t)ivar_5, (uint32_t)ivar_19);
        uint8_t ivar_26;
        uint8_t ivar_22;
        ivar_22 = (uint8_t)8;
        ivar_26 = (uint8_t)rem_mpz_uint32(ivar_6, ivar_22);
        result = (bytevectors__byv_t)bytevectors__byvbitrightrot((uint32_t)bytevectors__n, (bytevectors__byv_t)ivar_25, (uint8_t)ivar_26);

        
        return result;
}

extern bytevectors__byv_t bytevectors__byvrightrotate(uint32_t bytevectors__n, bytevectors__byv_t ivar_5, mpz_ptr_t ivar_6){
        bytevectors__byv_t  result;
        bytevectors__byv_t ivar_25;
        mpz_ptr_t ivar_20;
        uint8_t ivar_15;
        ivar_15 = (uint8_t)8;
        mpz_mk_fdiv_q_ui(ivar_20, ivar_6, ivar_15);
        uint32_t ivar_19;
        //copying to uint32 from mpz;
        ivar_19 = (uint32_t)mpz_get_ui(ivar_20);
        mpz_clear(ivar_20);
        ivar_25 = (bytevectors__byv_t)bytevectors__byvleftrot((uint32_t)bytevectors__n, (bytevectors__byv_t)ivar_5, (uint32_t)ivar_19);
        uint8_t ivar_26;
        uint8_t ivar_22;
        ivar_22 = (uint8_t)8;
        ivar_26 = (uint8_t)rem_mpz_uint32(ivar_6, ivar_22);
        result = (bytevectors__byv_t)bytevectors__byvbitleftrot((uint32_t)bytevectors__n, (bytevectors__byv_t)ivar_25, (uint8_t)ivar_26);

        
        return result;
}

extern bytevectors__byv_t bytevectors__byvXOR(uint32_t bytevectors__n, bytevectors__byv_t ivar_2, bytevectors__byv_t ivar_3){
        bytevectors__byv_t  result;
        uint32_t size16141;
        //copying to uint32 from uint32;
        size16141 = (uint32_t)bytevectors__n;
        size16141 += 0;
        result = new_bytevectors__byv(size16141);
        uint32_t ivar_4;
        for (uint32_t index16140 = 0; index16140 < size16141; index16140++){
             ivar_4 = (uint32_t)index16140;
             uint8_t ivar_16;
             ivar_16 = (uint8_t)ivar_2->elems[ivar_4];
             uint8_t ivar_17;
             ivar_17 = (uint8_t)ivar_3->elems[ivar_4];
             result->elems[index16140] = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_16, (uint8_t)ivar_17);
        };
        release_bytevectors__byv(ivar_2, bytevectors__n);
        release_bytevectors__byv(ivar_3, bytevectors__n);

        
        return result;
}

extern bytestrings__bytestring_t bytevectors__byv2bytestring(uint32_t bytevectors__n, bytevectors__byv_t ivar_1){
        bytestrings__bytestring_t  result;
        bytestrings__bytestring_t tmp16143 = new_bytestrings__bytestring();;
        result = (bytestrings__bytestring_t)tmp16143;
        tmp16143->length = (uint32_t)bytevectors__n;
        tmp16143->seq = (bytevectors__byv_t)ivar_1;

        
        return result;
}