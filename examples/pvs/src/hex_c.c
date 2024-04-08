//Code generated using pvs2ir2c
#include "hex_c.h"


hex_array_0_t new_hex_array_0(uint32_t size){
        hex_array_0_t tmp = (hex_array_0_t) safe_malloc(sizeof(struct hex_array_0_s) + (size * sizeof(uint8_t)));
        tmp->count = 1;
        tmp->size = size;;
        tmp->max = size;
         return tmp;}

void release_hex_array_0(hex_array_0_t x){
        x->count--;
         if (x->count <= 0){safe_free(x);}
}

void release_hex_array_0_ptr(pointer_t x, type_actual_t T){
        release_hex_array_0((hex_array_0_t)x);
}

hex_array_0_t copy_hex_array_0(hex_array_0_t x){
        hex_array_0_t tmp = new_hex_array_0(x->size);
        tmp->count = 1;
        for (uint32_t i = 0; i < x->size; i++){tmp->elems[i] = (uint8_t)x->elems[i];};
         return tmp;}

bool_t equal_hex_array_0(hex_array_0_t x, hex_array_0_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = (x->elems[i] == y->elems[i]); i++;};
        return tmp;}

bool_t equal_hex_array_0_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_hex_array_0((hex_array_0_t)x, (hex_array_0_t)y);
}

actual_hex_array_0_t actual_hex_array_0(){
        actual_hex_array_0_t new = (actual_hex_array_0_t)safe_malloc(sizeof(struct actual_hex_array_0_s));
        new->equal_ptr = (equal_ptr_t)(*equal_hex_array_0_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_hex_array_0_ptr);
 

 
        return new;
 };

hex_array_0_t update_hex_array_0(hex_array_0_t x, uint32_t i, uint8_t v){
        hex_array_0_t y; 
         if (x->count == 1){y = x;}
           else {y = copy_hex_array_0(x );
                x->count--;};
        y->elems[i] = (uint8_t)v;
        return y;}

hex_array_0_t upgrade_hex_array_0(hex_array_0_t x, uint32_t i, uint8_t v){
        hex_array_0_t y; 
         if (x->count == 1 && i < x->max){y = x;}
           else if (i > x->max){uint32_t newmax = x->max <= UINT32_MAX/2 ? 2*x->max: UINT32_MAX;
                y = safe_realloc(x, sizeof(struct hex_array_0_s) + (newmax * sizeof(uint8_t)));
                y->count = 1;
                y->size = i+1;
                y->max = newmax;
                release_hex_array_0(x);}
           else {y = copy_hex_array_0(x );
                x->count--;};
        y->elems[i] = (uint8_t)v;
        return y;}




hex_array_1_t new_hex_array_1(uint32_t size){
        hex_array_1_t tmp = (hex_array_1_t) safe_malloc(sizeof(struct hex_array_1_s) + (size * sizeof(uint32_t)));
        tmp->count = 1;
        tmp->size = size;;
        tmp->max = size;
         return tmp;}

void release_hex_array_1(hex_array_1_t x){
        x->count--;
         if (x->count <= 0){safe_free(x);}
}

void release_hex_array_1_ptr(pointer_t x, type_actual_t T){
        release_hex_array_1((hex_array_1_t)x);
}

hex_array_1_t copy_hex_array_1(hex_array_1_t x){
        hex_array_1_t tmp = new_hex_array_1(x->size);
        tmp->count = 1;
        for (uint32_t i = 0; i < x->size; i++){tmp->elems[i] = (uint32_t)x->elems[i];};
         return tmp;}

bool_t equal_hex_array_1(hex_array_1_t x, hex_array_1_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = (x->elems[i] == y->elems[i]); i++;};
        return tmp;}

bool_t equal_hex_array_1_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_hex_array_1((hex_array_1_t)x, (hex_array_1_t)y);
}

actual_hex_array_1_t actual_hex_array_1(){
        actual_hex_array_1_t new = (actual_hex_array_1_t)safe_malloc(sizeof(struct actual_hex_array_1_s));
        new->equal_ptr = (equal_ptr_t)(*equal_hex_array_1_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_hex_array_1_ptr);
 

 
        return new;
 };

hex_array_1_t update_hex_array_1(hex_array_1_t x, uint32_t i, uint32_t v){
        hex_array_1_t y; 
         if (x->count == 1){y = x;}
           else {y = copy_hex_array_1(x );
                x->count--;};
        y->elems[i] = (uint32_t)v;
        return y;}

hex_array_1_t upgrade_hex_array_1(hex_array_1_t x, uint32_t i, uint32_t v){
        hex_array_1_t y; 
         if (x->count == 1 && i < x->max){y = x;}
           else if (i > x->max){uint32_t newmax = x->max <= UINT32_MAX/2 ? 2*x->max: UINT32_MAX;
                y = safe_realloc(x, sizeof(struct hex_array_1_s) + (newmax * sizeof(uint32_t)));
                y->count = 1;
                y->size = i+1;
                y->max = newmax;
                release_hex_array_1(x);}
           else {y = copy_hex_array_1(x );
                x->count--;};
        y->elems[i] = (uint32_t)v;
        return y;}



extern bool_t hex__digitp(uint8_t ivar_1){
        bool_t  result;
        bool_t ivar_2;
        uint8_t ivar_5;
        ivar_5 = (uint8_t)48;
        ivar_2 = (ivar_1 >= ivar_5);
        if (ivar_2){ 
             uint8_t ivar_8;
             ivar_8 = (uint8_t)57;
             result = (ivar_1 <= ivar_8);
} else {
        
             result = (bool_t) false;
};

        
        return result;
}

extern bool_t hex__hexalphap(uint8_t ivar_1){
        bool_t  result;
        bool_t ivar_2;
        bool_t ivar_4;
        uint8_t ivar_7;
        ivar_7 = (uint8_t)65;
        ivar_4 = (ivar_1 >= ivar_7);
        if (ivar_4){ 
             uint8_t ivar_10;
             ivar_10 = (uint8_t)70;
             ivar_2 = (ivar_1 <= ivar_10);
} else {
        
             ivar_2 = (bool_t) false;
};
        if (ivar_2){ 
             result = (bool_t) true;
} else {
        
             bool_t ivar_13;
             uint8_t ivar_16;
             ivar_16 = (uint8_t)97;
             ivar_13 = (ivar_1 >= ivar_16);
             if (ivar_13){  
           uint8_t ivar_19;
           ivar_19 = (uint8_t)102;
           result = (ivar_1 <= ivar_19);
} else {
             
           result = (bool_t) false;
};
};

        
        return result;
}

extern bool_t hex__hexdigitp(uint8_t ivar_1){
        bool_t  result;
        bool_t ivar_2;
        ivar_2 = (bool_t)hex__digitp((uint8_t)ivar_1);
        if (ivar_2){ 
             result = (bool_t) true;
} else {
        
             result = (bool_t)hex__hexalphap((uint8_t)ivar_1);
};

        
        return result;
}

extern uint8_t hex__hexvalue(uint8_t ivar_2){
        uint8_t  result;
        bool_t ivar_3;
        uint8_t ivar_5;
        ivar_5 = (uint8_t)97;
        ivar_3 = (ivar_2 >= ivar_5);
        if (ivar_3){ 
             uint8_t ivar_8;
             ivar_8 = (uint8_t)87;
             result = (uint8_t)(ivar_2 - ivar_8);
} else {
        
             bool_t ivar_10;
             uint8_t ivar_12;
             ivar_12 = (uint8_t)65;
             ivar_10 = (ivar_2 >= ivar_12);
             if (ivar_10){  
           uint8_t ivar_15;
           ivar_15 = (uint8_t)55;
           result = (uint8_t)(ivar_2 - ivar_15);
} else {
             
           uint8_t ivar_18;
           ivar_18 = (uint8_t)48;
           result = (uint8_t)(ivar_2 - ivar_18);
};
};

        
        return result;
}

extern uint8_t hex__hex2byte(uint8_t ivar_2, uint8_t ivar_3){
        uint8_t  result;
        uint8_t ivar_18;
        uint8_t ivar_12;
        ivar_12 = (uint8_t)hex__hexvalue((uint8_t)ivar_2);
        uint8_t ivar_13;
        ivar_13 = (uint8_t)4;
        ivar_18 = (uint8_t)integertypes__u8lshift((uint8_t)ivar_12, (uint8_t)ivar_13);
        uint8_t ivar_19;
        ivar_19 = (uint8_t)hex__hexvalue((uint8_t)ivar_3);
        result = (uint8_t)integertypes__u8plus((uint8_t)ivar_18, (uint8_t)ivar_19);

        
        return result;
}

extern bytestrings__bytestring_t hex__hex2bytestring(bytestrings__bytestring_t ivar_1){
        bytestrings__bytestring_t  result;
        /* len */ mpz_ptr_t ivar_2;
        bool_t ivar_3;
        uint32_t ivar_4;
        ivar_4 = (uint32_t)ivar_1->length;
        uint32_t ivar_5;
        ivar_5 = (uint32_t)integertypes__max32();
        ivar_3 = (ivar_4 == ivar_5);
        if (ivar_3){ 
             uint32_t ivar_8;
             uint32_t ivar_13;
             ivar_13 = (uint32_t)integertypes__max32();
             uint8_t ivar_16;
             ivar_16 = (uint8_t)2;
             uint32_t ivar_14;
             //copying to uint32 from uint8;
             ivar_14 = (uint32_t)ivar_16;
             ivar_8 = (uint32_t)integertypes__u32div((uint32_t)ivar_13, (uint32_t)ivar_14);
             uint8_t ivar_9;
             ivar_9 = (uint8_t)1;
             mpz_mk_set_ui(ivar_2, (uint64_t)ivar_8);
             mpz_add_ui(ivar_2, ivar_2, (uint64_t)ivar_9);
} else {
        
             uint32_t ivar_25;
             uint32_t ivar_20;
             ivar_20 = (uint32_t)ivar_1->length;
             uint8_t ivar_21;
             ivar_21 = (uint8_t)1;
             ivar_25 = (uint32_t)(ivar_20 + ivar_21);
             uint8_t ivar_28;
             ivar_28 = (uint8_t)2;
             uint32_t ivar_26;
             //copying to uint32 from uint8;
             ivar_26 = (uint32_t)ivar_28;
             mpz_mk_set_ui(ivar_2, integertypes__u32div((uint32_t)ivar_25, (uint32_t)ivar_26));
};
        uint32_t ivar_29;
        //copying to uint32 from mpz;
        ivar_29 = (uint32_t)mpz_get_ui(ivar_2);
        mpz_clear(ivar_2);
        hex_array_0_t ivar_83;
        mpz_t ivar_32;
        mpz_init(ivar_32);
        uint32_t size15778;
        //copying to uint32 from uint32;
        size15778 = (uint32_t)ivar_29;
        size15778 += 0;
        ivar_83 = new_hex_array_0(size15778);
        for (uint32_t index15777 = 0; index15777 < size15778; index15777++){
             mpz_t ivar_32;
             mpz_init(ivar_32);
             mpz_set_ui(ivar_32, index15777);
             /* twoi */ uint32_t ivar_33;
             uint32_t ivar_37;
             //copying to uint32 from mpz;
             ivar_37 = (uint32_t)mpz_get_ui(ivar_32);
             mpz_clear(ivar_32);
             uint8_t ivar_40;
             ivar_40 = (uint8_t)2;
             uint32_t ivar_38;
             //copying to uint32 from uint8;
             ivar_38 = (uint32_t)ivar_40;
             ivar_33 = (uint32_t)integertypes__u32times((uint32_t)ivar_37, (uint32_t)ivar_38);
             bool_t ivar_41;
             uint32_t ivar_42;
             uint8_t ivar_50;
             ivar_50 = (uint8_t)1;
             uint32_t ivar_48;
             //copying to uint32 from uint8;
             ivar_48 = (uint32_t)ivar_50;
             ivar_42 = (uint32_t)integertypes__u32plus((uint32_t)ivar_33, (uint32_t)ivar_48);
             uint32_t ivar_43;
             ivar_43 = (uint32_t)ivar_1->length;
             ivar_41 = (ivar_42 == ivar_43);
             if (ivar_41){  
           uint8_t ivar_61;
           ivar_1->count++;
           ivar_61 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_33);
           uint8_t ivar_62;
           ivar_62 = (uint8_t)48;
           ivar_83->elems[index15777] = (uint8_t)hex__hex2byte((uint8_t)ivar_61, (uint8_t)ivar_62);
} else {
             
           uint8_t ivar_81;
           ivar_1->count++;
           ivar_81 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_33);
           uint8_t ivar_82;
           uint64_t ivar_79;
           uint8_t ivar_73;
           ivar_73 = (uint8_t)1;
           ivar_79 = (uint64_t)(ivar_33 + ivar_73);
           uint32_t ivar_77;
           //copying to uint32 from uint64;
           ivar_77 = (uint32_t)ivar_79;
           ivar_1->count++;
           ivar_82 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_77);
           ivar_83->elems[index15777] = (uint8_t)hex__hex2byte((uint8_t)ivar_81, (uint8_t)ivar_82);
};
        };
        release_bytestrings__bytestring(ivar_1);
        bytestrings__bytestring_t tmp15779 = new_bytestrings__bytestring();;
        result = (bytestrings__bytestring_t)tmp15779;
        tmp15779->length = (uint32_t)ivar_29;
        tmp15779->seq = (hex_array_0_t)ivar_83;

        
        return result;
}

extern bytestrings__bytestring_t hex__test_hex2bytestring(void){
        bytestrings__bytestring_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    bytestrings__bytestring_t ivar_7;
        strings__string_t ivar_5;
        uint32_t len15782 = 16;
        uint32_t characters15783[16] = {65, 66, 67, 68, 69, 70, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57};
        stringliteral_t string15781 = mk_string(16, characters15783);
        ivar_5 = (strings__string_t)strings__make_string(len15782, string15781);
        ivar_7 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_5);
        result = (bytestrings__bytestring_t)hex__hex2bytestring((bytestrings__bytestring_t)ivar_7);

        defined = true;};
        
        return result;
}

extern uint8_t hex__hex0(uint8_t ivar_2){
        uint8_t  result;
        /* hnum */ uint8_t ivar_3;
        uint8_t ivar_8;
        ivar_8 = (uint8_t)4;
        ivar_3 = (uint8_t)integertypes__u8rshift((uint8_t)ivar_2, (uint8_t)ivar_8);
        bool_t ivar_9;
        uint8_t ivar_11;
        ivar_11 = (uint8_t)10;
        ivar_9 = (ivar_3 < ivar_11);
        if (ivar_9){ 
             uint8_t ivar_13;
             ivar_13 = (uint8_t)48;
             result = (uint8_t)(ivar_13 + ivar_3);
} else {
        
             uint8_t ivar_19;
             ivar_19 = (uint8_t)55;
             result = (uint8_t)integertypes__u8plus((uint8_t)ivar_19, (uint8_t)ivar_3);
};

        
        return result;
}

extern uint8_t hex__hex1(uint8_t ivar_2){
        uint8_t  result;
        /* hnum */ uint8_t ivar_3;
        uint8_t ivar_8;
        ivar_8 = (uint8_t)16;
        ivar_3 = (uint8_t)integertypes__u8rem((uint8_t)ivar_2, (uint8_t)ivar_8);
        bool_t ivar_9;
        uint8_t ivar_11;
        ivar_11 = (uint8_t)10;
        ivar_9 = (ivar_3 < ivar_11);
        if (ivar_9){ 
             uint8_t ivar_13;
             ivar_13 = (uint8_t)48;
             result = (uint8_t)(ivar_13 + ivar_3);
} else {
        
             uint8_t ivar_19;
             ivar_19 = (uint8_t)55;
             result = (uint8_t)integertypes__u8plus((uint8_t)ivar_19, (uint8_t)ivar_3);
};

        
        return result;
}

extern bytestrings__bytestring_t hex__bytestring2hexstring(bytestrings__bytestring_t ivar_2){
        bytestrings__bytestring_t  result;
        /* len */ uint32_t ivar_3;
        uint32_t ivar_8;
        ivar_8 = (uint32_t)ivar_2->length;
        uint8_t ivar_11;
        ivar_11 = (uint8_t)2;
        uint32_t ivar_9;
        //copying to uint32 from uint8;
        ivar_9 = (uint32_t)ivar_11;
        ivar_3 = (uint32_t)integertypes__u32times((uint32_t)ivar_8, (uint32_t)ivar_9);
        hex_array_0_t ivar_51;
        uint32_t size15789;
        //copying to uint32 from uint32;
        size15789 = (uint32_t)ivar_3;
        size15789 += 0;
        ivar_51 = new_hex_array_0(size15789);
        uint32_t ivar_15;
        for (uint32_t index15788 = 0; index15788 < size15789; index15788++){
             ivar_15 = (uint32_t)index15788;
             /* i2 */ uint32_t ivar_16;
             uint8_t ivar_23;
             ivar_23 = (uint8_t)2;
             uint32_t ivar_21;
             //copying to uint32 from uint8;
             ivar_21 = (uint32_t)ivar_23;
             ivar_16 = (uint32_t)integertypes__u32div((uint32_t)ivar_15, (uint32_t)ivar_21);
             bool_t ivar_24;
             uint32_t ivar_25;
             uint8_t ivar_33;
             ivar_33 = (uint8_t)2;
             uint32_t ivar_31;
             //copying to uint32 from uint8;
             ivar_31 = (uint32_t)ivar_33;
             ivar_25 = (uint32_t)integertypes__u32rem((uint32_t)ivar_15, (uint32_t)ivar_31);
             uint8_t ivar_26;
             ivar_26 = (uint8_t)0;
             ivar_24 = (ivar_25 == ivar_26);
             if (ivar_24){  
           uint8_t ivar_42;
           ivar_2->count++;
           ivar_42 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_2, (uint32_t)ivar_16);
           ivar_51->elems[index15788] = (uint8_t)hex__hex0((uint8_t)ivar_42);
} else {
             
           uint8_t ivar_50;
           ivar_2->count++;
           ivar_50 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_2, (uint32_t)ivar_16);
           ivar_51->elems[index15788] = (uint8_t)hex__hex1((uint8_t)ivar_50);
};
        };
        release_bytestrings__bytestring(ivar_2);
        bytestrings__bytestring_t tmp15790 = new_bytestrings__bytestring();;
        result = (bytestrings__bytestring_t)tmp15790;
        tmp15790->length = (uint32_t)ivar_3;
        tmp15790->seq = (hex_array_0_t)ivar_51;

        
        return result;
}

extern bytestrings__bytestring_t hex__test_bytestring2hexstring(void){
        bytestrings__bytestring_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    bytestrings__bytestring_t ivar_7;
        strings__string_t ivar_5;
        uint32_t len15793 = 16;
        uint32_t characters15794[16] = {65, 66, 67, 68, 69, 70, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57};
        stringliteral_t string15792 = mk_string(16, characters15794);
        ivar_5 = (strings__string_t)strings__make_string(len15793, string15792);
        ivar_7 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_5);
        result = (bytestrings__bytestring_t)hex__bytestring2hexstring((bytestrings__bytestring_t)ivar_7);

        defined = true;};
        
        return result;
}

extern uint32_t hex__bytes2uint32(bytestrings__bytestring_t ivar_3, uint32_t ivar_4){
        uint32_t  result;
        bool_t ivar_6;
        uint32_t ivar_7;
        uint8_t ivar_10;
        ivar_10 = (uint8_t)3;
        ivar_7 = (uint32_t)(ivar_4 + ivar_10);
        uint32_t ivar_8;
        ivar_8 = (uint32_t)ivar_3->length;
        ivar_6 = (ivar_7 < ivar_8);
        if (ivar_6){ 
             mpz_ptr_t ivar_14;
             mpq_ptr_t ivar_16;
             uint32_t ivar_18;
             uint8_t ivar_31;
             ivar_3->count++;
             ivar_31 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_4);
             uint32_t ivar_28;
             //copying to uint32 from uint8;
             ivar_28 = (uint32_t)ivar_31;
             uint8_t ivar_29;
             ivar_29 = (uint8_t)24;
             ivar_18 = (uint32_t)integertypes__u32lshift((uint32_t)ivar_28, (uint32_t)ivar_29);
             uint32_t ivar_19;
             uint8_t ivar_46;
             uint32_t ivar_41;
             uint8_t ivar_37;
             ivar_37 = (uint8_t)1;
             ivar_41 = (uint32_t)(ivar_4 + ivar_37);
             ivar_3->count++;
             ivar_46 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_41);
             uint32_t ivar_43;
             //copying to uint32 from uint8;
             ivar_43 = (uint32_t)ivar_46;
             uint8_t ivar_44;
             ivar_44 = (uint8_t)16;
             ivar_19 = (uint32_t)integertypes__u32lshift((uint32_t)ivar_43, (uint32_t)ivar_44);
             mpz_t tmp15797;
             mpz_init(tmp15797);
             mpz_set_ui(tmp15797, (uint64_t)ivar_18);
             mpz_add_ui(tmp15797, tmp15797, (uint64_t)ivar_19);
             mpq_mk_set_z(ivar_16, tmp15797);
             mpz_clear(tmp15797);
             uint32_t ivar_17;
             uint8_t ivar_62;
             uint32_t ivar_57;
             uint8_t ivar_53;
             ivar_53 = (uint8_t)2;
             ivar_57 = (uint32_t)(ivar_4 + ivar_53);
             ivar_3->count++;
             ivar_62 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_57);
             uint32_t ivar_59;
             //copying to uint32 from uint8;
             ivar_59 = (uint32_t)ivar_62;
             uint8_t ivar_60;
             ivar_60 = (uint8_t)8;
             ivar_17 = (uint32_t)integertypes__u32lshift((uint32_t)ivar_59, (uint32_t)ivar_60);
             mpz_mk_set_q(ivar_14, ivar_16);
             mpz_add_ui(ivar_14, ivar_14, (uint64_t)ivar_17);
             uint8_t ivar_15;
             uint32_t ivar_71;
             uint8_t ivar_67;
             ivar_67 = (uint8_t)3;
             ivar_71 = (uint32_t)(ivar_4 + ivar_67);
             ivar_15 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_71);
             mpz_t tmp15798;
             mpz_init(tmp15798);
             mpz_add_ui(tmp15798, ivar_14, ivar_15);
             result = (uint32_t)mpz_get_ui(tmp15798);
             mpz_clear(tmp15798);
} else {
        
             bool_t ivar_73;
             uint32_t ivar_74;
             uint8_t ivar_77;
             ivar_77 = (uint8_t)2;
             ivar_74 = (uint32_t)(ivar_4 + ivar_77);
             uint32_t ivar_75;
             ivar_75 = (uint32_t)ivar_3->length;
             ivar_73 = (ivar_74 < ivar_75);
             if (ivar_73){  
           mpq_ptr_t ivar_81;
           uint32_t ivar_83;
           uint8_t ivar_96;
           ivar_3->count++;
           ivar_96 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_4);
           uint32_t ivar_93;
           //copying to uint32 from uint8;
           ivar_93 = (uint32_t)ivar_96;
           uint8_t ivar_94;
           ivar_94 = (uint8_t)16;
           ivar_83 = (uint32_t)integertypes__u32lshift((uint32_t)ivar_93, (uint32_t)ivar_94);
           uint32_t ivar_84;
           uint8_t ivar_111;
           uint32_t ivar_106;
           uint8_t ivar_102;
           ivar_102 = (uint8_t)1;
           ivar_106 = (uint32_t)(ivar_4 + ivar_102);
           ivar_3->count++;
           ivar_111 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_106);
           uint32_t ivar_108;
           //copying to uint32 from uint8;
           ivar_108 = (uint32_t)ivar_111;
           uint8_t ivar_109;
           ivar_109 = (uint8_t)8;
           ivar_84 = (uint32_t)integertypes__u32lshift((uint32_t)ivar_108, (uint32_t)ivar_109);
           mpz_t tmp15799;
           mpz_init(tmp15799);
           mpz_set_ui(tmp15799, (uint64_t)ivar_83);
           mpz_add_ui(tmp15799, tmp15799, (uint64_t)ivar_84);
           mpq_mk_set_z(ivar_81, tmp15799);
           mpz_clear(tmp15799);
           uint8_t ivar_82;
           uint32_t ivar_120;
           uint8_t ivar_116;
           ivar_116 = (uint8_t)2;
           ivar_120 = (uint32_t)(ivar_4 + ivar_116);
           ivar_82 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_120);
           mpz_t tmp15800;
           mpz_init(tmp15800);
           mpz_set_q(tmp15800, ivar_81);
           mpz_add_ui(tmp15800, tmp15800, ivar_82);
           result = (uint32_t)mpz_get_ui(tmp15800);
           mpz_clear(tmp15800);
} else {
             
           bool_t ivar_122;
           uint32_t ivar_123;
           uint8_t ivar_126;
           ivar_126 = (uint8_t)1;
           ivar_123 = (uint32_t)(ivar_4 + ivar_126);
           uint32_t ivar_124;
           ivar_124 = (uint32_t)ivar_3->length;
           ivar_122 = (ivar_123 < ivar_124);
           if (ivar_122){   
           uint32_t ivar_130;
           uint8_t ivar_143;
           ivar_3->count++;
           ivar_143 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_4);
           uint32_t ivar_140;
           //copying to uint32 from uint8;
           ivar_140 = (uint32_t)ivar_143;
           uint8_t ivar_141;
           ivar_141 = (uint8_t)8;
           ivar_130 = (uint32_t)integertypes__u32lshift((uint32_t)ivar_140, (uint32_t)ivar_141);
           uint8_t ivar_131;
           uint32_t ivar_151;
           uint8_t ivar_147;
           ivar_147 = (uint8_t)1;
           ivar_151 = (uint32_t)(ivar_4 + ivar_147);
           ivar_131 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_151);
           result = (uint32_t)(ivar_130 + ivar_131);
} else {
           
           result = (uint32_t)bytestrings__get((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_4);
};
};
};

        
        return result;
}

extern uint16_t hex__bytes2uint16(bytestrings__bytestring_t ivar_3, uint32_t ivar_4){
        uint16_t  result;
        bool_t ivar_6;
        uint32_t ivar_7;
        uint8_t ivar_10;
        ivar_10 = (uint8_t)1;
        ivar_7 = (uint32_t)(ivar_4 + ivar_10);
        uint32_t ivar_8;
        ivar_8 = (uint32_t)ivar_3->length;
        ivar_6 = (ivar_7 < ivar_8);
        if (ivar_6){ 
             uint16_t ivar_14;
             uint8_t ivar_27;
             ivar_3->count++;
             ivar_27 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_4);
             uint16_t ivar_24;
             //copying to uint16 from uint8;
             ivar_24 = (uint16_t)ivar_27;
             uint8_t ivar_25;
             ivar_25 = (uint8_t)8;
             ivar_14 = (uint16_t)integertypes__u16lshift((uint16_t)ivar_24, (uint16_t)ivar_25);
             uint8_t ivar_15;
             uint32_t ivar_35;
             uint8_t ivar_31;
             ivar_31 = (uint8_t)1;
             ivar_35 = (uint32_t)(ivar_4 + ivar_31);
             ivar_15 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_35);
             result = (uint16_t)(ivar_14 + ivar_15);
} else {
        
             result = (uint16_t)bytestrings__get((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_4);
};

        
        return result;
}

extern uint8_t hex__bytes2uint8(bytestrings__bytestring_t ivar_3, uint32_t ivar_4){
        uint8_t  result;
        result = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_4);

        
        return result;
}

extern uint64_t hex__bytes2uint64(bytestrings__bytestring_t ivar_3, uint32_t ivar_4){
        uint64_t  result;
        bool_t ivar_6;
        uint32_t ivar_7;
        uint8_t ivar_10;
        ivar_10 = (uint8_t)3;
        ivar_7 = (uint32_t)(ivar_4 + ivar_10);
        uint32_t ivar_8;
        ivar_8 = (uint32_t)ivar_3->length;
        ivar_6 = (ivar_7 <= ivar_8);
        if (ivar_6){ 
             /* msw */ uint32_t ivar_14;
             ivar_3->count++;
             ivar_14 = (uint32_t)hex__bytes2uint32((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_4);
             /* lsw */ uint32_t ivar_20;
             uint32_t ivar_28;
             uint8_t ivar_24;
             ivar_24 = (uint8_t)4;
             ivar_28 = (uint32_t)(ivar_4 + ivar_24);
             ivar_20 = (uint32_t)hex__bytes2uint32((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_28);
             mpz_ptr_t ivar_29;
             mpz_ptr_t ivar_31;
             uint8_t ivar_37;
             ivar_37 = (uint8_t)8;
             mpz_ptr_t ivar_35;
             //copying to mpz from uint8;
             mpz_mk_set_ui(ivar_35, ivar_37);
             ivar_31 = (mpz_ptr_t)exp2__exp2((mpz_ptr_t)ivar_35);
             mpz_mk_mul_ui(ivar_29, ivar_31, (uint64_t)ivar_14);
             mpz_t tmp15807;
             mpz_init(tmp15807);
             mpz_add_ui(tmp15807, ivar_29, ivar_20);
             result = (uint64_t)mpz_get_ui(tmp15807);
             mpz_clear(tmp15807);
} else {
        
             result = (uint64_t)hex__bytes2uint32((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_4);
};

        
        return result;
}

extern bool_t hex__equalUpto(bytestrings__bytestring_t ivar_1, bytestrings__bytestring_t ivar_2, uint32_t ivar_3){
        bool_t  result;
        result = (bool_t)u_undef_quant_expr();

        
        return result;
}

extern hex_array_1_t hex__bytes2uint32array(bytestrings__bytestring_t ivar_9){
        hex_array_1_t  result;
        uint32_t size15813;
        mpq_ptr_t ivar_16;
        uint32_t ivar_11;
        bytestrings__bytestring_t ivar_13;
        //copying to bytestrings__bytestring from bytestrings__bytestring;
        ivar_13 = (bytestrings__bytestring_t)ivar_9;
        if (ivar_13 != NULL) ivar_13->count++;
        ivar_11 = (uint32_t)ivar_13->length;
        uint8_t ivar_12;
        ivar_12 = (uint8_t)4;
        mpq_t tmp15814;
        mpq_init(tmp15814);
        mpq_t tmp15815;
        mpq_init(tmp15815);
        mpq_set_ui(tmp15814, (uint64_t)ivar_11, 1);
        mpq_set_ui(tmp15815, ivar_12, 1);
        mpq_mk_div(ivar_16, tmp15814, tmp15815);
        mpq_clear(tmp15814);
        mpq_clear(tmp15815);
        size15813 = (uint32_t)integertypes__u32ceiling(ivar_16);
        size15813 += 0;
        result = new_hex_array_1(size15813);
        uint32_t ivar_24;
        for (uint32_t index15812 = 0; index15812 < size15813; index15812++){
             ivar_24 = (uint32_t)index15812;
             uint64_t ivar_41;
             uint8_t ivar_34;
             ivar_34 = (uint8_t)4;
             ivar_41 = (uint64_t)((uint64_t)ivar_34 * (uint64_t)ivar_24);
             uint32_t ivar_39;
             //copying to uint32 from uint64;
             ivar_39 = (uint32_t)ivar_41;
             ivar_9->count++;
             result->elems[index15812] = (uint32_t)hex__bytes2uint32((bytestrings__bytestring_t)ivar_9, (uint32_t)ivar_39);
        };
        release_bytestrings__bytestring(ivar_9);

        
        return result;
}