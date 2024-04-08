//Code generated using pvs2ir2c
#include "bytestrings_c.h"


bytestrings_array_0_t new_bytestrings_array_0(uint32_t size){
        bytestrings_array_0_t tmp = (bytestrings_array_0_t) safe_malloc(sizeof(struct bytestrings_array_0_s) + (size * sizeof(uint8_t)));
        tmp->count = 1;
        tmp->size = size;;
        tmp->max = size;
         return tmp;}

void release_bytestrings_array_0(bytestrings_array_0_t x){
        x->count--;
         if (x->count <= 0){safe_free(x);}
}

void release_bytestrings_array_0_ptr(pointer_t x, type_actual_t T){
        release_bytestrings_array_0((bytestrings_array_0_t)x);
}

bytestrings_array_0_t copy_bytestrings_array_0(bytestrings_array_0_t x){
        bytestrings_array_0_t tmp = new_bytestrings_array_0(x->size);
        tmp->count = 1;
        for (uint32_t i = 0; i < x->size; i++){tmp->elems[i] = (uint8_t)x->elems[i];};
         return tmp;}

bool_t equal_bytestrings_array_0(bytestrings_array_0_t x, bytestrings_array_0_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = (x->elems[i] == y->elems[i]); i++;};
        return tmp;}

bool_t equal_bytestrings_array_0_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_bytestrings_array_0((bytestrings_array_0_t)x, (bytestrings_array_0_t)y);
}

actual_bytestrings_array_0_t actual_bytestrings_array_0(){
        actual_bytestrings_array_0_t new = (actual_bytestrings_array_0_t)safe_malloc(sizeof(struct actual_bytestrings_array_0_s));
        new->equal_ptr = (equal_ptr_t)(*equal_bytestrings_array_0_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_bytestrings_array_0_ptr);
 

 
        return new;
 };

bytestrings_array_0_t update_bytestrings_array_0(bytestrings_array_0_t x, uint32_t i, uint8_t v){
        bytestrings_array_0_t y; 
         if (x->count == 1){y = x;}
           else {y = copy_bytestrings_array_0(x );
                x->count--;};
        y->elems[i] = (uint8_t)v;
        return y;}

bytestrings_array_0_t upgrade_bytestrings_array_0(bytestrings_array_0_t x, uint32_t i, uint8_t v){
        bytestrings_array_0_t y; 
         if (x->count == 1 && i < x->max){y = x;}
           else if (i > x->max){uint32_t newmax = x->max <= UINT32_MAX/2 ? 2*x->max: UINT32_MAX;
                y = safe_realloc(x, sizeof(struct bytestrings_array_0_s) + (newmax * sizeof(uint8_t)));
                y->count = 1;
                y->size = i+1;
                y->max = newmax;
                release_bytestrings_array_0(x);}
           else {y = copy_bytestrings_array_0(x );
                x->count--;};
        y->elems[i] = (uint8_t)v;
        return y;}




bytestrings__bytestring_t new_bytestrings__bytestring(void){
        bytestrings__bytestring_t tmp = (bytestrings__bytestring_t) safe_malloc(sizeof(struct bytestrings__bytestring_s));
        tmp->count = 1;
        return tmp;}

void release_bytestrings__bytestring(bytestrings__bytestring_t x){
        x->count--;
        if (x->count <= 0){
         release_bytestrings_array_0(x->seq);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_bytestrings__bytestring_ptr(pointer_t x, type_actual_t T){
        release_bytestrings__bytestring((bytestrings__bytestring_t)x);
}

bytestrings__bytestring_t copy_bytestrings__bytestring(bytestrings__bytestring_t x){
        bytestrings__bytestring_t y = new_bytestrings__bytestring();
        y->length = (uint32_t)x->length;
        y->seq = x->seq;
        if (y->seq != NULL){y->seq->count++;};
        y->count = 1;
        return y;}

bool_t equal_bytestrings__bytestring(bytestrings__bytestring_t x, bytestrings__bytestring_t y){
        bool_t tmp = true;
        tmp = tmp && x->length == y->length;
        tmp = tmp && equal_bytestrings_array_0(x->seq, y->seq);
        return tmp;}

bool_t equal_bytestrings__bytestring_ptr(pointer_t x, pointer_t y, actual_bytestrings__bytestring_t T){
        return equal_bytestrings__bytestring((bytestrings__bytestring_t)x, (bytestrings__bytestring_t)y);
}

actual_bytestrings__bytestring_t actual_bytestrings__bytestring(){
        actual_bytestrings__bytestring_t new = (actual_bytestrings__bytestring_t)safe_malloc(sizeof(struct actual_bytestrings__bytestring_s));
        new->equal_ptr = (equal_ptr_t)(*equal_bytestrings__bytestring_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_bytestrings__bytestring_ptr);
 

 
        return new;
 };

bytestrings__bytestring_t update_bytestrings__bytestring_length(bytestrings__bytestring_t x, uint32_t v){
        bytestrings__bytestring_t y;
        if (x->count == 1){y = x;}
        else {y = copy_bytestrings__bytestring(x); x->count--;};
        y->length = (uint32_t)v;
        return y;}

bytestrings__bytestring_t update_bytestrings__bytestring_seq(bytestrings__bytestring_t x, bytestrings_array_0_t v){
        bytestrings__bytestring_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->seq != NULL){release_bytestrings_array_0(x->seq);};}
        else {y = copy_bytestrings__bytestring(x); x->count--; y->seq->count--;};
        y->seq = (bytestrings_array_0_t)v;
        return y;}



extern uint32_t bytestrings__bytestring_bound(void){
        uint32_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    uint8_t ivar_5;
        ivar_5 = (uint8_t)28;
        mpz_ptr_t ivar_3;
        //copying to mpz from uint8;
        mpz_mk_set_ui(ivar_3, ivar_5);
        result = (uint32_t)mpz_get_ui(exp2__exp2((mpz_ptr_t)ivar_3));

        defined = true;};
        
        return result;
}

extern uint32_t bytestrings__length(bytestrings__bytestring_t ivar_2){
        uint32_t  result;
        result = (uint32_t)ivar_2->length;
        release_bytestrings__bytestring(ivar_2);

        
        return result;
}

extern uint8_t bytestrings__get(bytestrings__bytestring_t ivar_3, uint32_t ivar_4){
        uint8_t  result;
        bytestrings_array_0_t ivar_9;
        ivar_9 = (bytestrings_array_0_t)ivar_3->seq;
        ivar_9->count++;
        release_bytestrings__bytestring(ivar_3);
        result = (uint8_t)ivar_9->elems[ivar_4];
        release_bytestrings_array_0(ivar_9);

        
        return result;
}

extern bytestrings__bytestring_t bytestrings__null(void){
        bytestrings__bytestring_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    uint8_t ivar_7;
        ivar_7 = (uint8_t)0;
        uint32_t ivar_1;
        //copying to uint32 from uint8;
        ivar_1 = (uint32_t)ivar_7;
        bytestrings_array_0_t ivar_6;
        uint32_t size14646;
        //copying to uint32 from uint32;
        size14646 = (uint32_t)ivar_1;
        size14646 += 0;
        ivar_6 = new_bytestrings_array_0(size14646);
        uint8_t ivar_5;
        for (uint32_t index14645 = 0; index14645 < size14646; index14645++){
             ivar_5 = (uint8_t)index14645;
             ivar_6->elems[index14645] = (uint8_t)0;
        };
        bytestrings__bytestring_t tmp14647 = new_bytestrings__bytestring();;
        result = (bytestrings__bytestring_t)tmp14647;
        tmp14647->length = (uint32_t)ivar_1;
        tmp14647->seq = (bytestrings_array_0_t)ivar_6;

        defined = true;};
        
        return result;
}

extern bytestrings__bytestring_t bytestrings__unit(uint8_t ivar_1){
        bytestrings__bytestring_t  result;
        uint8_t ivar_7;
        ivar_7 = (uint8_t)1;
        uint32_t ivar_2;
        //copying to uint32 from uint8;
        ivar_2 = (uint32_t)ivar_7;
        bytestrings_array_0_t ivar_6;
        uint32_t size14651;
        //copying to uint32 from uint32;
        size14651 = (uint32_t)ivar_2;
        size14651 += 0;
        ivar_6 = new_bytestrings_array_0(size14651);
        uint8_t ivar_5;
        for (uint32_t index14650 = 0; index14650 < size14651; index14650++){
             ivar_5 = (uint8_t)index14650;
             //copying to uint8 from uint8;
             ivar_6->elems[index14650] = (uint8_t)ivar_1;
        };
        bytestrings__bytestring_t tmp14652 = new_bytestrings__bytestring();;
        result = (bytestrings__bytestring_t)tmp14652;
        tmp14652->length = (uint32_t)ivar_2;
        tmp14652->seq = (bytestrings_array_0_t)ivar_6;

        
        return result;
}

extern bytestrings__bytestring_t bytestrings__mk_bytestring(strings__string_t ivar_1){
        bytestrings__bytestring_t  result;
        mpz_ptr_t ivar_18;
        ivar_18 = safe_malloc(sizeof(mpz_t));
        mpz_init(ivar_18);
        mpz_set(ivar_18, ivar_1->length);
        uint32_t ivar_3;
        //copying to uint32 from mpz;
        ivar_3 = (uint32_t)mpz_get_ui(ivar_18);
        mpz_clear(ivar_18);
        bytestrings_array_0_t ivar_17;
        mpz_t ivar_8;
        mpz_init(ivar_8);
        uint32_t size14659;
        //copying to uint32 from uint32;
        size14659 = (uint32_t)ivar_3;
        size14659 += 0;
        ivar_17 = new_bytestrings_array_0(size14659);
        for (uint32_t index14658 = 0; index14658 < size14659; index14658++){
             mpz_t ivar_8;
             mpz_init(ivar_8);
             mpz_set_ui(ivar_8, index14658);
             uint32_t ivar_10;
             ivar_1->count++;
             ivar_10 = (uint32_t)gen_strings__get((strings__string_t)ivar_1, (mpz_ptr_t)ivar_8);
             ivar_17->elems[index14658] = (uint32_t) ivar_10;
        };
        release_strings__string(ivar_1);
        bytestrings__bytestring_t tmp14660 = new_bytestrings__bytestring();;
        result = (bytestrings__bytestring_t)tmp14660;
        tmp14660->length = (uint32_t)ivar_3;
        tmp14660->seq = (bytestrings_array_0_t)ivar_17;

        
        return result;
}

extern bytestrings__bytestring_t bytestrings__doubleplus(bytestrings__bytestring_t ivar_1, bytestrings__bytestring_t ivar_2){
        bytestrings__bytestring_t  result;
        bool_t ivar_3;
        uint32_t ivar_4;
        ivar_4 = (uint32_t)ivar_1->length;
        uint8_t ivar_5;
        ivar_5 = (uint8_t)0;
        ivar_3 = (ivar_4 == ivar_5);
        if (ivar_3){ 
             release_bytestrings__bytestring(ivar_1);
             //copying to bytestrings__bytestring from bytestrings__bytestring;
             result = (bytestrings__bytestring_t)ivar_2;
             if (result != NULL) result->count++;
             release_bytestrings__bytestring(ivar_2);
} else {
        
             bool_t ivar_8;
             uint32_t ivar_9;
             ivar_9 = (uint32_t)ivar_2->length;
             uint8_t ivar_10;
             ivar_10 = (uint8_t)0;
             ivar_8 = (ivar_9 == ivar_10);
             if (ivar_8){  
           release_bytestrings__bytestring(ivar_2);
           //copying to bytestrings__bytestring from bytestrings__bytestring;
           result = (bytestrings__bytestring_t)ivar_1;
           if (result != NULL) result->count++;
           release_bytestrings__bytestring(ivar_1);
} else {
             
           /* n */ uint32_t ivar_13;
           uint32_t ivar_14;
           ivar_14 = (uint32_t)ivar_1->length;
           uint32_t ivar_15;
           ivar_15 = (uint32_t)ivar_2->length;
           ivar_13 = (uint32_t)(ivar_14 + ivar_15);
           bytestrings_array_0_t ivar_44;
           uint32_t size14667;
           //copying to uint32 from uint32;
           size14667 = (uint32_t)ivar_13;
           size14667 += 0;
           ivar_44 = new_bytestrings_array_0(size14667);
           uint32_t ivar_22;
           for (uint32_t index14666 = 0; index14666 < size14667; index14666++){
           ivar_22 = (uint32_t)index14666;
           bool_t ivar_23;
           uint32_t ivar_25;
           ivar_25 = (uint32_t)ivar_1->length;
           ivar_23 = (ivar_22 < ivar_25);
           if (ivar_23){    
            ivar_1->count++;
            ivar_44->elems[index14666] = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_22);
} else {
           
            int32_t ivar_43;
            uint32_t ivar_36;
            ivar_36 = (uint32_t)ivar_1->length;
            ivar_43 = (int32_t)((uint64_t)ivar_22 - (uint64_t)ivar_36);
            uint32_t ivar_41;
            //copying to uint32 from int32;
            ivar_41 = (uint32_t)ivar_43;
            ivar_2->count++;
            ivar_44->elems[index14666] = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_2, (uint32_t)ivar_41);
};
           };
           release_bytestrings__bytestring(ivar_1);
           release_bytestrings__bytestring(ivar_2);
           bytestrings__bytestring_t tmp14668 = new_bytestrings__bytestring();;
           result = (bytestrings__bytestring_t)tmp14668;
           tmp14668->length = (uint32_t)ivar_13;
           tmp14668->seq = (bytestrings_array_0_t)ivar_44;
};
};

        
        return result;
}

extern uint32_t bytestrings__strdiff_rec(bytestrings__bytestring_t ivar_12, bytestrings__bytestring_t ivar_13, uint32_t ivar_14){
        uint32_t  result;
        bool_t ivar_19;
        bool_t ivar_20;
        uint32_t ivar_23;
        ivar_23 = (uint32_t)ivar_12->length;
        ivar_20 = (ivar_14 == ivar_23);
        if (ivar_20){ 
             ivar_19 = (bool_t) true;
} else {
        
             bool_t ivar_26;
             uint32_t ivar_29;
             ivar_29 = (uint32_t)ivar_13->length;
             ivar_26 = (ivar_14 == ivar_29);
             if (ivar_26){  
           ivar_19 = (bool_t) true;
} else {
             
           uint8_t ivar_32;
           ivar_12->count++;
           ivar_32 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_12, (uint32_t)ivar_14);
           uint8_t ivar_33;
           ivar_13->count++;
           ivar_33 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_13, (uint32_t)ivar_14);
           ivar_19 = (ivar_32 != ivar_33);
};
};
        if (ivar_19){ 
             release_bytestrings__bytestring(ivar_13);
             release_bytestrings__bytestring(ivar_12);
             //copying to uint32 from uint32;
             result = (uint32_t)ivar_14;
} else {
        
             uint32_t ivar_58;
             uint8_t ivar_53;
             ivar_53 = (uint8_t)1;
             ivar_58 = (uint32_t)(ivar_14 + ivar_53);
             result = (uint32_t)bytestrings__strdiff_rec((bytestrings__bytestring_t)ivar_12, (bytestrings__bytestring_t)ivar_13, (uint32_t)ivar_58);
};

        
        return result;
}

extern uint32_t bytestrings__strdiff(bytestrings__bytestring_t ivar_6, bytestrings__bytestring_t ivar_7){
        uint32_t  result;
        uint8_t ivar_20;
        ivar_20 = (uint8_t)0;
        uint32_t ivar_18;
        //copying to uint32 from uint8;
        ivar_18 = (uint32_t)ivar_20;
        result = (uint32_t)bytestrings__strdiff_rec((bytestrings__bytestring_t)ivar_6, (bytestrings__bytestring_t)ivar_7, (uint32_t)ivar_18);

        
        return result;
}

extern int8_t bytestrings__strcmp(bytestrings__bytestring_t ivar_2, bytestrings__bytestring_t ivar_3){
        int8_t  result;
        /* i */ uint32_t ivar_4;
        ivar_2->count++;
        ivar_3->count++;
        ivar_4 = (uint32_t)bytestrings__strdiff((bytestrings__bytestring_t)ivar_2, (bytestrings__bytestring_t)ivar_3);
        bool_t ivar_16;
        bool_t ivar_17;
        uint32_t ivar_20;
        ivar_20 = (uint32_t)ivar_2->length;
        ivar_17 = (ivar_4 == ivar_20);
        if (ivar_17){ 
             ivar_16 = (bool_t) true;
} else {
        
             uint32_t ivar_24;
             ivar_24 = (uint32_t)ivar_3->length;
             ivar_16 = (ivar_4 == ivar_24);
};
        if (ivar_16){ 
             bool_t ivar_28;
             uint32_t ivar_29;
             ivar_29 = (uint32_t)ivar_2->length;
             uint32_t ivar_30;
             ivar_30 = (uint32_t)ivar_3->length;
             ivar_28 = (ivar_29 < ivar_30);
             if (ivar_28){  
           release_bytestrings__bytestring(ivar_3);
           release_bytestrings__bytestring(ivar_2);
           result = (int8_t)-1;
} else {
             
           bool_t ivar_34;
           uint32_t ivar_35;
           ivar_35 = (uint32_t)ivar_2->length;
           release_bytestrings__bytestring(ivar_2);
           uint32_t ivar_36;
           ivar_36 = (uint32_t)ivar_3->length;
           release_bytestrings__bytestring(ivar_3);
           ivar_34 = (ivar_35 > ivar_36);
           if (ivar_34){   
           result = (int8_t)1;
} else {
           
           result = (int8_t)0;
};
};
} else {
        
             bool_t ivar_40;
             uint8_t ivar_41;
             ivar_41 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_2, (uint32_t)ivar_4);
             uint8_t ivar_42;
             ivar_42 = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_3, (uint32_t)ivar_4);
             ivar_40 = (ivar_41 < ivar_42);
             if (ivar_40){  
           result = (int8_t)-1;
} else {
             
           result = (int8_t)1;
};
};

        
        return result;
}

extern bytestrings__bytestring_t bytestrings__prefix(bytestrings__bytestring_t ivar_1, uint32_t ivar_2){
        bytestrings__bytestring_t  result;
        bool_t ivar_4;
        uint32_t ivar_6;
        ivar_6 = (uint32_t)ivar_1->length;
        ivar_4 = (ivar_2 == ivar_6);
        if (ivar_4){ 
             //copying to bytestrings__bytestring from bytestrings__bytestring;
             result = (bytestrings__bytestring_t)ivar_1;
             if (result != NULL) result->count++;
             release_bytestrings__bytestring(ivar_1);
} else {
        
             bytestrings_array_0_t ivar_21;
             uint32_t size14707;
             //copying to uint32 from uint32;
             size14707 = (uint32_t)ivar_2;
             size14707 += 0;
             ivar_21 = new_bytestrings_array_0(size14707);
             uint32_t ivar_14;
             for (uint32_t index14706 = 0; index14706 < size14707; index14706++){
           ivar_14 = (uint32_t)index14706;
           ivar_1->count++;
           ivar_21->elems[index14706] = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_14);
             };
             release_bytestrings__bytestring(ivar_1);
             bytestrings__bytestring_t tmp14708 = new_bytestrings__bytestring();;
             result = (bytestrings__bytestring_t)tmp14708;
             tmp14708->length = (uint32_t)ivar_2;
             tmp14708->seq = (bytestrings_array_0_t)ivar_21;
};

        
        return result;
}

extern bytestrings__bytestring_t bytestrings__suffix(bytestrings__bytestring_t ivar_1, uint32_t ivar_2){
        bytestrings__bytestring_t  result;
        bool_t ivar_4;
        uint8_t ivar_6;
        ivar_6 = (uint8_t)0;
        ivar_4 = (ivar_2 == ivar_6);
        if (ivar_4){ 
             //copying to bytestrings__bytestring from bytestrings__bytestring;
             result = (bytestrings__bytestring_t)ivar_1;
             if (result != NULL) result->count++;
             release_bytestrings__bytestring(ivar_1);
} else {
        
             mpz_ptr_t ivar_39;
             uint32_t ivar_8;
             ivar_8 = (uint32_t)ivar_1->length;
             mpz_mk_set_ui(ivar_39, (uint64_t)ivar_8);
             mpz_sub_ui(ivar_39, ivar_39, (uint64_t)ivar_2);
             uint32_t ivar_12;
             //copying to uint32 from mpz;
             ivar_12 = (uint32_t)mpz_get_ui(ivar_39);
             mpz_clear(ivar_39);
             bytestrings_array_0_t ivar_38;
             mpz_t ivar_23;
             mpz_init(ivar_23);
             uint32_t size14719;
             //copying to uint32 from uint32;
             size14719 = (uint32_t)ivar_12;
             size14719 += 0;
             ivar_38 = new_bytestrings_array_0(size14719);
             for (uint32_t index14718 = 0; index14718 < size14719; index14718++){
           mpz_t ivar_23;
           mpz_init(ivar_23);
           mpz_set_ui(ivar_23, index14718);
           mpz_ptr_t ivar_37;
           mpz_mk_add_ui(ivar_37, ivar_23, (uint64_t)ivar_2);
           uint32_t ivar_35;
           //copying to uint32 from mpz;
           ivar_35 = (uint32_t)mpz_get_ui(ivar_37);
           mpz_clear(ivar_37);
           ivar_1->count++;
           ivar_38->elems[index14718] = (uint8_t)bytestrings__get((bytestrings__bytestring_t)ivar_1, (uint32_t)ivar_35);
             };
             release_bytestrings__bytestring(ivar_1);
             bytestrings__bytestring_t tmp14720 = new_bytestrings__bytestring();;
             result = (bytestrings__bytestring_t)tmp14720;
             tmp14720->length = (uint32_t)ivar_12;
             tmp14720->seq = (bytestrings_array_0_t)ivar_38;
};

        
        return result;
}

extern bytestrings__bytestring_t bytestrings__substr(bytestrings__bytestring_t ivar_4, uint32_t ivar_5, mpz_ptr_t ivar_7){
        bytestrings__bytestring_t  result;
        bytestrings__bytestring_t ivar_20;
        ivar_20 = (bytestrings__bytestring_t)bytestrings__suffix((bytestrings__bytestring_t)ivar_4, (uint32_t)ivar_5);
        mpz_ptr_t ivar_23;
        mpz_mk_sub_ui(ivar_23, ivar_7, (uint64_t)ivar_5);
        uint32_t ivar_21;
        //copying to uint32 from mpz;
        ivar_21 = (uint32_t)mpz_get_ui(ivar_23);
        mpz_clear(ivar_23);
        result = (bytestrings__bytestring_t)bytestrings__prefix((bytestrings__bytestring_t)ivar_20, (uint32_t)ivar_21);

        
        return result;
}

extern bool_t bytestrings__ascii_bytestringp(bytestrings__bytestring_t ivar_1){
        bool_t  result;
        result = (bool_t)u_undef_quant_expr();

        
        return result;
}