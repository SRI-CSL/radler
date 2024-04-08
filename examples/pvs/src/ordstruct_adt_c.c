//Code generated using pvs2ir2c
#include "ordstruct_adt_c.h"


ordstruct_adt__ordstruct_adt_t new_ordstruct_adt__ordstruct_adt(void){
        ordstruct_adt__ordstruct_adt_t tmp = (ordstruct_adt__ordstruct_adt_t) safe_malloc(sizeof(struct ordstruct_adt__ordstruct_adt_s));
        tmp->count = 1;
        return tmp;}

void release_ordstruct_adt__ordstruct_adt(ordstruct_adt__ordstruct_adt_t x){
switch (x->ordstruct_adt__ordstruct_adt_index) {
case 1:  release_ordstruct_adt__add((ordstruct_adt__add_t) x); break;
}}

void release_ordstruct_adt__ordstruct_adt_ptr(pointer_t x, type_actual_t T){
        release_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)x);
}

ordstruct_adt__ordstruct_adt_t copy_ordstruct_adt__ordstruct_adt(ordstruct_adt__ordstruct_adt_t x){
        ordstruct_adt__ordstruct_adt_t y = new_ordstruct_adt__ordstruct_adt();
        y->ordstruct_adt__ordstruct_adt_index = (uint8_t)x->ordstruct_adt__ordstruct_adt_index;
        y->count = 1;
        return y;}

bool_t equal_ordstruct_adt__ordstruct_adt(ordstruct_adt__ordstruct_adt_t x, ordstruct_adt__ordstruct_adt_t y){
        bool_t tmp = x->ordstruct_adt__ordstruct_adt_index == y->ordstruct_adt__ordstruct_adt_index;
        switch  (x->ordstruct_adt__ordstruct_adt_index) {
                case 1: tmp = tmp && equal_ordstruct_adt__add((ordstruct_adt__add_t) x, (ordstruct_adt__add_t) y); break;
        }
        return tmp;
}

bool_t equal_ordstruct_adt__ordstruct_adt_ptr(pointer_t x, pointer_t y, actual_ordstruct_adt__ordstruct_adt_t T){
        return equal_ordstruct_adt__ordstruct_adt((ordstruct_adt__ordstruct_adt_t)x, (ordstruct_adt__ordstruct_adt_t)y);
}

actual_ordstruct_adt__ordstruct_adt_t actual_ordstruct_adt__ordstruct_adt(){
        actual_ordstruct_adt__ordstruct_adt_t new = (actual_ordstruct_adt__ordstruct_adt_t)safe_malloc(sizeof(struct actual_ordstruct_adt__ordstruct_adt_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ordstruct_adt__ordstruct_adt_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ordstruct_adt__ordstruct_adt_ptr);
 

 
        return new;
 };

ordstruct_adt__ordstruct_adt_t update_ordstruct_adt__ordstruct_adt_ordstruct_adt__ordstruct_adt_index(ordstruct_adt__ordstruct_adt_t x, uint8_t v){
        ordstruct_adt__ordstruct_adt_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ordstruct_adt__ordstruct_adt(x); x->count--;};
        y->ordstruct_adt__ordstruct_adt_index = (uint8_t)v;
        return y;}




ordstruct_adt__add_t new_ordstruct_adt__add(void){
        ordstruct_adt__add_t tmp = (ordstruct_adt__add_t) safe_malloc(sizeof(struct ordstruct_adt__add_s));
        tmp->count = 1;
        return tmp;}

void release_ordstruct_adt__add(ordstruct_adt__add_t x){
        x->count--;
        if (x->count <= 0){
         release_ordstruct_adt__ordstruct_adt(x->exp);
         release_ordstruct_adt__ordstruct_adt(x->rest);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ordstruct_adt__add_ptr(pointer_t x, type_actual_t T){
        release_ordstruct_adt__add((ordstruct_adt__add_t)x);
}

ordstruct_adt__add_t copy_ordstruct_adt__add(ordstruct_adt__add_t x){
        ordstruct_adt__add_t y = new_ordstruct_adt__add();
        y->ordstruct_adt__ordstruct_adt_index = (uint8_t)x->ordstruct_adt__ordstruct_adt_index;
        mpz_set(y->coef, x->coef);
        y->exp = x->exp;
        if (y->exp != NULL){y->exp->count++;};
        y->rest = x->rest;
        if (y->rest != NULL){y->rest->count++;};
        y->count = 1;
        return y;}

bool_t equal_ordstruct_adt__add(ordstruct_adt__add_t x, ordstruct_adt__add_t y){
        bool_t tmp = true;
        tmp = tmp && x->ordstruct_adt__ordstruct_adt_index == y->ordstruct_adt__ordstruct_adt_index;
        tmp = tmp && x->coef == y->coef;
        tmp = tmp && equal_ordstruct_adt__ordstruct_adt(x->exp, y->exp);
        tmp = tmp && equal_ordstruct_adt__ordstruct_adt(x->rest, y->rest);
        return tmp;}

bool_t equal_ordstruct_adt__add_ptr(pointer_t x, pointer_t y, actual_ordstruct_adt__add_t T){
        return equal_ordstruct_adt__add((ordstruct_adt__add_t)x, (ordstruct_adt__add_t)y);
}

actual_ordstruct_adt__add_t actual_ordstruct_adt__add(){
        actual_ordstruct_adt__add_t new = (actual_ordstruct_adt__add_t)safe_malloc(sizeof(struct actual_ordstruct_adt__add_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ordstruct_adt__add_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ordstruct_adt__add_ptr);
 

 
        return new;
 };

ordstruct_adt__add_t update_ordstruct_adt__add_ordstruct_adt__ordstruct_adt_index(ordstruct_adt__add_t x, uint8_t v){
        ordstruct_adt__add_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ordstruct_adt__add(x); x->count--;};
        y->ordstruct_adt__ordstruct_adt_index = (uint8_t)v;
        return y;}

ordstruct_adt__add_t update_ordstruct_adt__add_coef(ordstruct_adt__add_t x, mpz_ptr_t v){
        ordstruct_adt__add_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ordstruct_adt__add(x); x->count--;};
        mpz_set(y->coef, v);
        return y;}

ordstruct_adt__add_t update_ordstruct_adt__add_exp(ordstruct_adt__add_t x, ordstruct_adt__ordstruct_adt_t v){
        ordstruct_adt__add_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->exp != NULL){release_ordstruct_adt__ordstruct_adt(x->exp);};}
        else {y = copy_ordstruct_adt__add(x); x->count--; y->exp->count--;};
        y->exp = (ordstruct_adt__ordstruct_adt_t)v;
        return y;}

ordstruct_adt__add_t update_ordstruct_adt__add_rest(ordstruct_adt__add_t x, ordstruct_adt__ordstruct_adt_t v){
        ordstruct_adt__add_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->rest != NULL){release_ordstruct_adt__ordstruct_adt(x->rest);};}
        else {y = copy_ordstruct_adt__add(x); x->count--; y->rest->count--;};
        y->rest = (ordstruct_adt__ordstruct_adt_t)v;
        return y;}



void release_ordstruct_adt_funtype_2(ordstruct_adt_funtype_2_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ordstruct_adt_funtype_2_t copy_ordstruct_adt_funtype_2(ordstruct_adt_funtype_2_t x){return x->ftbl->cptr(x);}

bool_t equal_ordstruct_adt_funtype_2(ordstruct_adt_funtype_2_t x, ordstruct_adt_funtype_2_t y){
        return false;}

void release_ordstruct_adt_funtype_3(ordstruct_adt_funtype_3_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ordstruct_adt_funtype_3_t copy_ordstruct_adt_funtype_3(ordstruct_adt_funtype_3_t x){return x->ftbl->cptr(x);}

bool_t equal_ordstruct_adt_funtype_3(ordstruct_adt_funtype_3_t x, ordstruct_adt_funtype_3_t y){
        return false;}


ordstruct_adt_record_4_t new_ordstruct_adt_record_4(void){
        ordstruct_adt_record_4_t tmp = (ordstruct_adt_record_4_t) safe_malloc(sizeof(struct ordstruct_adt_record_4_s));
        tmp->count = 1;
        return tmp;}

void release_ordstruct_adt_record_4(ordstruct_adt_record_4_t x){
        x->count--;
        if (x->count <= 0){
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ordstruct_adt_record_4_ptr(pointer_t x, type_actual_t T){
        release_ordstruct_adt_record_4((ordstruct_adt_record_4_t)x);
}

ordstruct_adt_record_4_t copy_ordstruct_adt_record_4(ordstruct_adt_record_4_t x){
        ordstruct_adt_record_4_t y = new_ordstruct_adt_record_4();
        mpz_set(y->project_1, x->project_1);
        mpz_set(y->project_2, x->project_2);
        mpz_set(y->project_3, x->project_3);
        y->count = 1;
        return y;}

bool_t equal_ordstruct_adt_record_4(ordstruct_adt_record_4_t x, ordstruct_adt_record_4_t y){
        bool_t tmp = true;
        tmp = tmp && x->project_1 == y->project_1;
        tmp = tmp && x->project_2 == y->project_2;
        tmp = tmp && x->project_3 == y->project_3;
        return tmp;}

bool_t equal_ordstruct_adt_record_4_ptr(pointer_t x, pointer_t y, actual_ordstruct_adt_record_4_t T){
        return equal_ordstruct_adt_record_4((ordstruct_adt_record_4_t)x, (ordstruct_adt_record_4_t)y);
}

actual_ordstruct_adt_record_4_t actual_ordstruct_adt_record_4(){
        actual_ordstruct_adt_record_4_t new = (actual_ordstruct_adt_record_4_t)safe_malloc(sizeof(struct actual_ordstruct_adt_record_4_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ordstruct_adt_record_4_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ordstruct_adt_record_4_ptr);
 

 
        return new;
 };

ordstruct_adt_record_4_t update_ordstruct_adt_record_4_project_1(ordstruct_adt_record_4_t x, mpz_ptr_t v){
        ordstruct_adt_record_4_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ordstruct_adt_record_4(x); x->count--;};
        mpz_set(y->project_1, v);
        return y;}

ordstruct_adt_record_4_t update_ordstruct_adt_record_4_project_2(ordstruct_adt_record_4_t x, mpz_ptr_t v){
        ordstruct_adt_record_4_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ordstruct_adt_record_4(x); x->count--;};
        mpz_set(y->project_2, v);
        return y;}

ordstruct_adt_record_4_t update_ordstruct_adt_record_4_project_3(ordstruct_adt_record_4_t x, mpz_ptr_t v){
        ordstruct_adt_record_4_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ordstruct_adt_record_4(x); x->count--;};
        mpz_set(y->project_3, v);
        return y;}



void release_ordstruct_adt_funtype_5(ordstruct_adt_funtype_5_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ordstruct_adt_funtype_5_t copy_ordstruct_adt_funtype_5(ordstruct_adt_funtype_5_t x){return x->ftbl->cptr(x);}

bool_t equal_ordstruct_adt_funtype_5(ordstruct_adt_funtype_5_t x, ordstruct_adt_funtype_5_t y){
        return false;}


mpz_ptr_t f_ordstruct_adt_closure_6(struct ordstruct_adt_closure_6_s * closure, ordstruct_adt__ordstruct_adt_t bvar){
        mpz_ptr_t result = h_ordstruct_adt_closure_6(bvar, closure->fvar_1, closure->fvar_2); 
        return result;}

mpz_ptr_t m_ordstruct_adt_closure_6(struct ordstruct_adt_closure_6_s * closure, ordstruct_adt__ordstruct_adt_t bvar){
        return h_ordstruct_adt_closure_6(bvar, closure->fvar_1, closure->fvar_2);}

extern mpz_ptr_t h_ordstruct_adt_closure_6(ordstruct_adt__ordstruct_adt_t ivar_9, ordstruct_adt_funtype_5_t ivar_5, mpz_ptr_t ivar_4){
        mpz_ptr_t result;
        /* red */ ordstruct_adt_funtype_3_t ivar_10;
        ivar_5->count++;
        ivar_10 = (ordstruct_adt_funtype_3_t)ordstruct_adt__reduce_nat(ivar_4, (ordstruct_adt_funtype_5_t)ivar_5);
        bool_t ivar_21;
        ivar_9->count++;
        ivar_21 = (bool_t)r_ordstruct_adt__zerop((ordstruct_adt__ordstruct_adt_t)ivar_9);
        if (ivar_21){ 
             release_ordstruct_adt_funtype_3(ivar_10);
             release_ordstruct_adt__ordstruct_adt(ivar_9);
             //copying to mpz from mpz;
             mpz_mk_set(result, ivar_4);
} else {
        
             mpz_ptr_t ivar_25;
             ivar_9->count++;
             ivar_25 = (mpz_ptr_t)ordstruct_adt__ordstruct_adt_coef((ordstruct_adt__ordstruct_adt_t)ivar_9);
             ordstruct_adt__ordstruct_adt_t ivar_26;
             ivar_9->count++;
             ivar_26 = (ordstruct_adt__ordstruct_adt_t)ordstruct_adt__ordstruct_adt_exp((ordstruct_adt__ordstruct_adt_t)ivar_9);
             ordstruct_adt__ordstruct_adt_t ivar_27;
             ivar_27 = (ordstruct_adt__ordstruct_adt_t)ordstruct_adt__ordstruct_adt_rest((ordstruct_adt__ordstruct_adt_t)ivar_9);
             mpz_ptr_t ivar_54;
             mpz_mk_set(ivar_54, ivar_10->ftbl->fptr(ivar_10, ivar_26));
             mpz_ptr_t ivar_55;
             mpz_mk_set(ivar_55, ivar_10->ftbl->fptr(ivar_10, ivar_27));
             ivar_10->ftbl->rptr(ivar_10);
             mpz_mk_set(result, ivar_5->ftbl->mptr(ivar_5, ivar_25, ivar_54, ivar_55));
};

        return result;
}

ordstruct_adt_closure_6_t new_ordstruct_adt_closure_6(void){
        static struct ordstruct_adt_funtype_3_ftbl_s ftbl = {.fptr = (mpz_ptr_t (*)(ordstruct_adt_funtype_3_t, ordstruct_adt__ordstruct_adt_t))&f_ordstruct_adt_closure_6, .mptr = (mpz_ptr_t (*)(ordstruct_adt_funtype_3_t, ordstruct_adt__ordstruct_adt_t))&m_ordstruct_adt_closure_6, .rptr =  (void (*)(ordstruct_adt_funtype_3_t))&release_ordstruct_adt_closure_6, .cptr = (ordstruct_adt_funtype_3_t (*)(ordstruct_adt_funtype_3_t))&copy_ordstruct_adt_closure_6};
        ordstruct_adt_closure_6_t tmp = (ordstruct_adt_closure_6_t) safe_malloc(sizeof(struct ordstruct_adt_closure_6_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        mpz_init(tmp->fvar_2);
        return tmp;}

void release_ordstruct_adt_closure_6(ordstruct_adt_funtype_3_t closure){
        ordstruct_adt_closure_6_t x = (ordstruct_adt_closure_6_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ordstruct_adt_funtype_5(x->fvar_1);
        //printf("\nFreeing\n");
        safe_free(x);}}

ordstruct_adt_closure_6_t copy_ordstruct_adt_closure_6(ordstruct_adt_closure_6_t x){
        ordstruct_adt_closure_6_t y = new_ordstruct_adt_closure_6();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        mpz_set(y->fvar_2, x->fvar_2);
        if (x->htbl != NULL){
            ordstruct_adt_funtype_3_htbl_t new_htbl = (ordstruct_adt_funtype_3_htbl_t) safe_malloc(sizeof(struct ordstruct_adt_funtype_3_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ordstruct_adt_funtype_3_hashentry_t * new_data = (ordstruct_adt_funtype_3_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ordstruct_adt_funtype_3_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct ordstruct_adt_funtype_3_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


ordstruct_adt_record_7_t new_ordstruct_adt_record_7(void){
        ordstruct_adt_record_7_t tmp = (ordstruct_adt_record_7_t) safe_malloc(sizeof(struct ordstruct_adt_record_7_s));
        tmp->count = 1;
        return tmp;}

void release_ordstruct_adt_record_7(ordstruct_adt_record_7_t x){
        x->count--;
        if (x->count <= 0){
         release_ordstruct_adt__ordstruct_adt(x->project_4);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_ordstruct_adt_record_7_ptr(pointer_t x, type_actual_t T){
        release_ordstruct_adt_record_7((ordstruct_adt_record_7_t)x);
}

ordstruct_adt_record_7_t copy_ordstruct_adt_record_7(ordstruct_adt_record_7_t x){
        ordstruct_adt_record_7_t y = new_ordstruct_adt_record_7();
        mpz_set(y->project_1, x->project_1);
        mpz_set(y->project_2, x->project_2);
        mpz_set(y->project_3, x->project_3);
        y->project_4 = x->project_4;
        if (y->project_4 != NULL){y->project_4->count++;};
        y->count = 1;
        return y;}

bool_t equal_ordstruct_adt_record_7(ordstruct_adt_record_7_t x, ordstruct_adt_record_7_t y){
        bool_t tmp = true;
        tmp = tmp && x->project_1 == y->project_1;
        tmp = tmp && x->project_2 == y->project_2;
        tmp = tmp && x->project_3 == y->project_3;
        tmp = tmp && equal_ordstruct_adt__ordstruct_adt(x->project_4, y->project_4);
        return tmp;}

bool_t equal_ordstruct_adt_record_7_ptr(pointer_t x, pointer_t y, actual_ordstruct_adt_record_7_t T){
        return equal_ordstruct_adt_record_7((ordstruct_adt_record_7_t)x, (ordstruct_adt_record_7_t)y);
}

actual_ordstruct_adt_record_7_t actual_ordstruct_adt_record_7(){
        actual_ordstruct_adt_record_7_t new = (actual_ordstruct_adt_record_7_t)safe_malloc(sizeof(struct actual_ordstruct_adt_record_7_s));
        new->equal_ptr = (equal_ptr_t)(*equal_ordstruct_adt_record_7_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_ordstruct_adt_record_7_ptr);
 

 
        return new;
 };

ordstruct_adt_record_7_t update_ordstruct_adt_record_7_project_1(ordstruct_adt_record_7_t x, mpz_ptr_t v){
        ordstruct_adt_record_7_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ordstruct_adt_record_7(x); x->count--;};
        mpz_set(y->project_1, v);
        return y;}

ordstruct_adt_record_7_t update_ordstruct_adt_record_7_project_2(ordstruct_adt_record_7_t x, mpz_ptr_t v){
        ordstruct_adt_record_7_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ordstruct_adt_record_7(x); x->count--;};
        mpz_set(y->project_2, v);
        return y;}

ordstruct_adt_record_7_t update_ordstruct_adt_record_7_project_3(ordstruct_adt_record_7_t x, mpz_ptr_t v){
        ordstruct_adt_record_7_t y;
        if (x->count == 1){y = x;}
        else {y = copy_ordstruct_adt_record_7(x); x->count--;};
        mpz_set(y->project_3, v);
        return y;}

ordstruct_adt_record_7_t update_ordstruct_adt_record_7_project_4(ordstruct_adt_record_7_t x, ordstruct_adt__ordstruct_adt_t v){
        ordstruct_adt_record_7_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_4 != NULL){release_ordstruct_adt__ordstruct_adt(x->project_4);};}
        else {y = copy_ordstruct_adt_record_7(x); x->count--; y->project_4->count--;};
        y->project_4 = (ordstruct_adt__ordstruct_adt_t)v;
        return y;}



void release_ordstruct_adt_funtype_8(ordstruct_adt_funtype_8_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

ordstruct_adt_funtype_8_t copy_ordstruct_adt_funtype_8(ordstruct_adt_funtype_8_t x){return x->ftbl->cptr(x);}

bool_t equal_ordstruct_adt_funtype_8(ordstruct_adt_funtype_8_t x, ordstruct_adt_funtype_8_t y){
        return false;}


mpz_ptr_t f_ordstruct_adt_closure_9(struct ordstruct_adt_closure_9_s * closure, ordstruct_adt__ordstruct_adt_t bvar){
        mpz_ptr_t result = h_ordstruct_adt_closure_9(bvar, closure->fvar_1, closure->fvar_2); 
        return result;}

mpz_ptr_t m_ordstruct_adt_closure_9(struct ordstruct_adt_closure_9_s * closure, ordstruct_adt__ordstruct_adt_t bvar){
        return h_ordstruct_adt_closure_9(bvar, closure->fvar_1, closure->fvar_2);}

extern mpz_ptr_t h_ordstruct_adt_closure_9(ordstruct_adt__ordstruct_adt_t ivar_11, ordstruct_adt_funtype_8_t ivar_7, ordstruct_adt_funtype_3_t ivar_5){
        mpz_ptr_t result;
        /* red */ ordstruct_adt_funtype_3_t ivar_12;
        ivar_5->count++;
        ivar_7->count++;
        ivar_12 = (ordstruct_adt_funtype_3_t)ordstruct_adt__REDUCE_nat((ordstruct_adt_funtype_3_t)ivar_5, (ordstruct_adt_funtype_8_t)ivar_7);
        bool_t ivar_29;
        ivar_11->count++;
        ivar_29 = (bool_t)r_ordstruct_adt__zerop((ordstruct_adt__ordstruct_adt_t)ivar_11);
        if (ivar_29){ 
             release_ordstruct_adt_funtype_3(ivar_12);
             mpz_mk_set(result, ivar_5->ftbl->fptr(ivar_5, ivar_11));
} else {
        
             mpz_ptr_t ivar_33;
             ivar_11->count++;
             ivar_33 = (mpz_ptr_t)ordstruct_adt__ordstruct_adt_coef((ordstruct_adt__ordstruct_adt_t)ivar_11);
             ordstruct_adt__ordstruct_adt_t ivar_34;
             ivar_11->count++;
             ivar_34 = (ordstruct_adt__ordstruct_adt_t)ordstruct_adt__ordstruct_adt_exp((ordstruct_adt__ordstruct_adt_t)ivar_11);
             ordstruct_adt__ordstruct_adt_t ivar_35;
             ivar_11->count++;
             ivar_35 = (ordstruct_adt__ordstruct_adt_t)ordstruct_adt__ordstruct_adt_rest((ordstruct_adt__ordstruct_adt_t)ivar_11);
             mpz_ptr_t ivar_63;
             mpz_mk_set(ivar_63, ivar_12->ftbl->fptr(ivar_12, ivar_34));
             mpz_ptr_t ivar_64;
             mpz_mk_set(ivar_64, ivar_12->ftbl->fptr(ivar_12, ivar_35));
             ivar_12->ftbl->rptr(ivar_12);
             mpz_mk_set(result, ivar_7->ftbl->mptr(ivar_7, ivar_33, ivar_63, ivar_64, ivar_11));
};

        return result;
}

ordstruct_adt_closure_9_t new_ordstruct_adt_closure_9(void){
        static struct ordstruct_adt_funtype_3_ftbl_s ftbl = {.fptr = (mpz_ptr_t (*)(ordstruct_adt_funtype_3_t, ordstruct_adt__ordstruct_adt_t))&f_ordstruct_adt_closure_9, .mptr = (mpz_ptr_t (*)(ordstruct_adt_funtype_3_t, ordstruct_adt__ordstruct_adt_t))&m_ordstruct_adt_closure_9, .rptr =  (void (*)(ordstruct_adt_funtype_3_t))&release_ordstruct_adt_closure_9, .cptr = (ordstruct_adt_funtype_3_t (*)(ordstruct_adt_funtype_3_t))&copy_ordstruct_adt_closure_9};
        ordstruct_adt_closure_9_t tmp = (ordstruct_adt_closure_9_t) safe_malloc(sizeof(struct ordstruct_adt_closure_9_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_ordstruct_adt_closure_9(ordstruct_adt_funtype_3_t closure){
        ordstruct_adt_closure_9_t x = (ordstruct_adt_closure_9_t)closure;
        x->count--;
        if (x->count <= 0){
         release_ordstruct_adt_funtype_8(x->fvar_1);
         release_ordstruct_adt_funtype_3(x->fvar_2);
        //printf("\nFreeing\n");
        safe_free(x);}}

ordstruct_adt_closure_9_t copy_ordstruct_adt_closure_9(ordstruct_adt_closure_9_t x){
        ordstruct_adt_closure_9_t y = new_ordstruct_adt_closure_9();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        if (x->htbl != NULL){
            ordstruct_adt_funtype_3_htbl_t new_htbl = (ordstruct_adt_funtype_3_htbl_t) safe_malloc(sizeof(struct ordstruct_adt_funtype_3_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            ordstruct_adt_funtype_3_hashentry_t * new_data = (ordstruct_adt_funtype_3_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct ordstruct_adt_funtype_3_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct ordstruct_adt_funtype_3_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

extern bool_t r_ordstruct_adt__zerop(ordstruct_adt__ordstruct_adt_t ivar_1){
        bool_t  result;
        uint8_t ivar_3;
        ivar_3 = (uint8_t)0;
        uint8_t ivar_2;
        ivar_2 = (uint8_t)ivar_1->ordstruct_adt__ordstruct_adt_index;
        release_ordstruct_adt__ordstruct_adt(ivar_1);
        result = (ivar_2 == ivar_3);

        
        return result;
}

extern bool_t r_ordstruct_adt__nonzerop(ordstruct_adt__ordstruct_adt_t ivar_1){
        bool_t  result;
        uint8_t ivar_3;
        ivar_3 = (uint8_t)1;
        uint8_t ivar_2;
        ivar_2 = (uint8_t)ivar_1->ordstruct_adt__ordstruct_adt_index;
        release_ordstruct_adt__ordstruct_adt(ivar_1);
        result = (ivar_2 == ivar_3);

        
        return result;
}

extern ordstruct_adt__add_t update_ordstruct_adt__ordstruct_adt_coef(ordstruct_adt__ordstruct_adt_t ivar_1, mpz_ptr_t ivar_3){
        ordstruct_adt__add_t  result;
        ordstruct_adt__add_t ivar_2;
        //copying to ordstruct_adt__add from ordstruct_adt__ordstruct_adt;
        ivar_2 = (ordstruct_adt__add_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ordstruct_adt__ordstruct_adt(ivar_1);
        result = (ordstruct_adt__add_t)update_ordstruct_adt__add_coef(ivar_2, ivar_3);

        
        return result;
}

extern mpz_ptr_t ordstruct_adt__ordstruct_adt_coef(ordstruct_adt__ordstruct_adt_t ivar_1){
        mpz_ptr_t  result;
        ordstruct_adt__add_t ivar_2;
        //copying to ordstruct_adt__add from ordstruct_adt__ordstruct_adt;
        ivar_2 = (ordstruct_adt__add_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ordstruct_adt__ordstruct_adt(ivar_1);
        result = safe_malloc(sizeof(mpz_t));
        mpz_init(result);
        mpz_set(result, ivar_2->coef);
        release_ordstruct_adt__add(ivar_2);

        
        return result;
}

extern ordstruct_adt__add_t update_ordstruct_adt__ordstruct_adt_exp(ordstruct_adt__ordstruct_adt_t ivar_1, ordstruct_adt__ordstruct_adt_t ivar_3){
        ordstruct_adt__add_t  result;
        ordstruct_adt__add_t ivar_2;
        //copying to ordstruct_adt__add from ordstruct_adt__ordstruct_adt;
        ivar_2 = (ordstruct_adt__add_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ordstruct_adt__ordstruct_adt(ivar_1);
        result = (ordstruct_adt__add_t)update_ordstruct_adt__add_exp(ivar_2, ivar_3);

        
        return result;
}

extern ordstruct_adt__ordstruct_adt_t ordstruct_adt__ordstruct_adt_exp(ordstruct_adt__ordstruct_adt_t ivar_1){
        ordstruct_adt__ordstruct_adt_t  result;
        ordstruct_adt__add_t ivar_2;
        //copying to ordstruct_adt__add from ordstruct_adt__ordstruct_adt;
        ivar_2 = (ordstruct_adt__add_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ordstruct_adt__ordstruct_adt(ivar_1);
        result = (ordstruct_adt__ordstruct_adt_t)ivar_2->exp;
        result->count++;
        release_ordstruct_adt__add(ivar_2);

        
        return result;
}

extern ordstruct_adt__add_t update_ordstruct_adt__ordstruct_adt_rest(ordstruct_adt__ordstruct_adt_t ivar_1, ordstruct_adt__ordstruct_adt_t ivar_3){
        ordstruct_adt__add_t  result;
        ordstruct_adt__add_t ivar_2;
        //copying to ordstruct_adt__add from ordstruct_adt__ordstruct_adt;
        ivar_2 = (ordstruct_adt__add_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ordstruct_adt__ordstruct_adt(ivar_1);
        result = (ordstruct_adt__add_t)update_ordstruct_adt__add_rest(ivar_2, ivar_3);

        
        return result;
}

extern ordstruct_adt__ordstruct_adt_t ordstruct_adt__ordstruct_adt_rest(ordstruct_adt__ordstruct_adt_t ivar_1){
        ordstruct_adt__ordstruct_adt_t  result;
        ordstruct_adt__add_t ivar_2;
        //copying to ordstruct_adt__add from ordstruct_adt__ordstruct_adt;
        ivar_2 = (ordstruct_adt__add_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_ordstruct_adt__ordstruct_adt(ivar_1);
        result = (ordstruct_adt__ordstruct_adt_t)ivar_2->rest;
        result->count++;
        release_ordstruct_adt__add(ivar_2);

        
        return result;
}

extern ordstruct_adt__ordstruct_adt_t ordstruct_adt__zero(void){
        ordstruct_adt__ordstruct_adt_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    uint8_t ivar_1;
        ivar_1 = (uint8_t)0;
        ordstruct_adt__ordstruct_adt_t tmp14381 = new_ordstruct_adt__ordstruct_adt();;
        result = (ordstruct_adt__ordstruct_adt_t)tmp14381;
        tmp14381->ordstruct_adt__ordstruct_adt_index = (uint8_t)ivar_1;

        defined = true;};
        
        return result;
}

extern ordstruct_adt__ordstruct_adt_t ordstruct_adt__add(mpz_ptr_t ivar_2, ordstruct_adt__ordstruct_adt_t ivar_3, ordstruct_adt__ordstruct_adt_t ivar_4){
        ordstruct_adt__ordstruct_adt_t  result;
        uint8_t ivar_1;
        ivar_1 = (uint8_t)1;
        ordstruct_adt__add_t tmp14382 = new_ordstruct_adt__add();;
        result = (ordstruct_adt__ordstruct_adt_t)tmp14382;
        tmp14382->ordstruct_adt__ordstruct_adt_index = (uint8_t)ivar_1;
        mpz_init(tmp14382->coef);
        mpz_set(tmp14382->coef, ivar_2);
        mpz_clear(ivar_2);
        tmp14382->exp = (ordstruct_adt__ordstruct_adt_t)ivar_3;
        tmp14382->rest = (ordstruct_adt__ordstruct_adt_t)ivar_4;

        
        return result;
}

extern ordstruct_adt_funtype_2_t ordstruct_adt__ordstruct_ord(void){
        ordstruct_adt_funtype_2_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    pvs2cerror("Missing definition", PVS2C_EXIT_ERROR);

        defined = true;};
        
        return result;
}

extern uint8_t ordstruct_adt__ord(ordstruct_adt__ordstruct_adt_t ivar_2){
        uint8_t  result;
        bool_t ivar_4;
        ivar_2->count++;
        ivar_4 = (bool_t)r_ordstruct_adt__zerop((ordstruct_adt__ordstruct_adt_t)ivar_2);
        if (ivar_4){ 
             release_ordstruct_adt__ordstruct_adt(ivar_2);
             result = (uint8_t)0;
} else {
        
             result = (uint8_t)1;
};

        
        return result;
}

extern bool_t ordstruct_adt__subterm(ordstruct_adt__ordstruct_adt_t ivar_1, ordstruct_adt__ordstruct_adt_t ivar_2){
        bool_t  result;
        bool_t ivar_3;
        ivar_1->count++;
        ivar_2->count++;
        ivar_3 = (bool_t) equal_ordstruct_adt__ordstruct_adt(ivar_1, ivar_2);
        if (ivar_3){ 
             release_ordstruct_adt__ordstruct_adt(ivar_1);
             release_ordstruct_adt__ordstruct_adt(ivar_2);
             result = (bool_t) true;
} else {
        
             bool_t ivar_9;
             ivar_2->count++;
             ivar_9 = (bool_t)r_ordstruct_adt__zerop((ordstruct_adt__ordstruct_adt_t)ivar_2);
             if (ivar_9){  
           release_ordstruct_adt__ordstruct_adt(ivar_2);
           release_ordstruct_adt__ordstruct_adt(ivar_1);
           result = (bool_t) false;
} else {
             
           ordstruct_adt__ordstruct_adt_t ivar_14;
           ivar_2->count++;
           ivar_14 = (ordstruct_adt__ordstruct_adt_t)ordstruct_adt__ordstruct_adt_exp((ordstruct_adt__ordstruct_adt_t)ivar_2);
           ordstruct_adt__ordstruct_adt_t ivar_15;
           ivar_15 = (ordstruct_adt__ordstruct_adt_t)ordstruct_adt__ordstruct_adt_rest((ordstruct_adt__ordstruct_adt_t)ivar_2);
           bool_t ivar_25;
           ivar_1->count++;
           ivar_25 = (bool_t)ordstruct_adt__subterm((ordstruct_adt__ordstruct_adt_t)ivar_1, (ordstruct_adt__ordstruct_adt_t)ivar_14);
           if (ivar_25){   
           release_ordstruct_adt__ordstruct_adt(ivar_1);
           release_ordstruct_adt__ordstruct_adt(ivar_15);
           result = (bool_t) true;
} else {
           
           result = (bool_t)ordstruct_adt__subterm((ordstruct_adt__ordstruct_adt_t)ivar_1, (ordstruct_adt__ordstruct_adt_t)ivar_15);
};
};
};

        
        return result;
}

extern bool_t ordstruct_adt__doublelessp(ordstruct_adt__ordstruct_adt_t ivar_1, ordstruct_adt__ordstruct_adt_t ivar_2){
        bool_t  result;
        bool_t ivar_4;
        ivar_2->count++;
        ivar_4 = (bool_t)r_ordstruct_adt__zerop((ordstruct_adt__ordstruct_adt_t)ivar_2);
        if (ivar_4){ 
             release_ordstruct_adt__ordstruct_adt(ivar_2);
             release_ordstruct_adt__ordstruct_adt(ivar_1);
             result = (bool_t) false;
} else {
        
             ordstruct_adt__ordstruct_adt_t ivar_9;
             ivar_2->count++;
             ivar_9 = (ordstruct_adt__ordstruct_adt_t)ordstruct_adt__ordstruct_adt_exp((ordstruct_adt__ordstruct_adt_t)ivar_2);
             ordstruct_adt__ordstruct_adt_t ivar_10;
             ivar_10 = (ordstruct_adt__ordstruct_adt_t)ordstruct_adt__ordstruct_adt_rest((ordstruct_adt__ordstruct_adt_t)ivar_2);
             bool_t ivar_20;
             bool_t ivar_27;
             ivar_1->count++;
             ivar_9->count++;
             ivar_27 = (bool_t) equal_ordstruct_adt__ordstruct_adt(ivar_1, ivar_9);
             if (ivar_27){  
           release_ordstruct_adt__ordstruct_adt(ivar_9);
           ivar_20 = (bool_t) true;
} else {
             
           ivar_1->count++;
           ivar_20 = (bool_t)ordstruct_adt__doublelessp((ordstruct_adt__ordstruct_adt_t)ivar_1, (ordstruct_adt__ordstruct_adt_t)ivar_9);
};
             if (ivar_20){  
           release_ordstruct_adt__ordstruct_adt(ivar_1);
           release_ordstruct_adt__ordstruct_adt(ivar_10);
           result = (bool_t) true;
} else {
             
           bool_t ivar_44;
           ivar_1->count++;
           ivar_10->count++;
           ivar_44 = (bool_t) equal_ordstruct_adt__ordstruct_adt(ivar_1, ivar_10);
           if (ivar_44){   
           release_ordstruct_adt__ordstruct_adt(ivar_10);
           release_ordstruct_adt__ordstruct_adt(ivar_1);
           result = (bool_t) true;
} else {
           
           result = (bool_t)ordstruct_adt__doublelessp((ordstruct_adt__ordstruct_adt_t)ivar_1, (ordstruct_adt__ordstruct_adt_t)ivar_10);
};
};
};

        
        return result;
}

extern ordstruct_adt_funtype_3_t ordstruct_adt__reduce_nat(mpz_ptr_t ivar_4, ordstruct_adt_funtype_5_t ivar_5){
        ordstruct_adt_funtype_3_t  result;
        ordstruct_adt_closure_6_t cl14387;
        cl14387 = new_ordstruct_adt_closure_6();
        cl14387->fvar_1 = (ordstruct_adt_funtype_5_t)ivar_5;
        if (cl14387->fvar_1 != NULL) cl14387->fvar_1->count++;
        mpz_set(cl14387->fvar_2, ivar_4);
        release_ordstruct_adt_funtype_5(ivar_5);
        result = (ordstruct_adt_funtype_3_t)cl14387;

        
        return result;
}

extern ordstruct_adt_funtype_3_t ordstruct_adt__REDUCE_nat(ordstruct_adt_funtype_3_t ivar_5, ordstruct_adt_funtype_8_t ivar_7){
        ordstruct_adt_funtype_3_t  result;
        ordstruct_adt_closure_9_t cl14389;
        cl14389 = new_ordstruct_adt_closure_9();
        cl14389->fvar_1 = (ordstruct_adt_funtype_8_t)ivar_7;
        if (cl14389->fvar_1 != NULL) cl14389->fvar_1->count++;
        cl14389->fvar_2 = (ordstruct_adt_funtype_3_t)ivar_5;
        if (cl14389->fvar_2 != NULL) cl14389->fvar_2->count++;
        release_ordstruct_adt_funtype_8(ivar_7);
        release_ordstruct_adt_funtype_3(ivar_5);
        result = (ordstruct_adt_funtype_3_t)cl14389;

        
        return result;
}