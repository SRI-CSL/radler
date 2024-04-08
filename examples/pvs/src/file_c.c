//Code generated using pvs2ir2c
#include "file_c.h"


file__lifted_file_adt_t new_file__lifted_file_adt(void){
        file__lifted_file_adt_t tmp = (file__lifted_file_adt_t) safe_malloc(sizeof(struct file__lifted_file_adt_s));
        tmp->count = 1;
        return tmp;}

void release_file__lifted_file_adt(file__lifted_file_adt_t x){
switch (x->file__lifted_file_adt_index) {
case 1:  release_file__pass((file__pass_t) x); break;
}}

void release_file__lifted_file_adt_ptr(pointer_t x, type_actual_t T){
        release_file__lifted_file_adt((file__lifted_file_adt_t)x);
}

file__lifted_file_adt_t copy_file__lifted_file_adt(file__lifted_file_adt_t x){
        file__lifted_file_adt_t y = new_file__lifted_file_adt();
        y->file__lifted_file_adt_index = (uint8_t)x->file__lifted_file_adt_index;
        y->count = 1;
        return y;}

bool_t equal_file__lifted_file_adt(file__lifted_file_adt_t x, file__lifted_file_adt_t y){
        bool_t tmp = x->file__lifted_file_adt_index == y->file__lifted_file_adt_index;
        switch  (x->file__lifted_file_adt_index) {
                case 1: tmp = tmp && equal_file__pass((file__pass_t) x, (file__pass_t) y); break;
        }
        return tmp;
}

bool_t equal_file__lifted_file_adt_ptr(pointer_t x, pointer_t y, actual_file__lifted_file_adt_t T){
        return equal_file__lifted_file_adt((file__lifted_file_adt_t)x, (file__lifted_file_adt_t)y);
}

actual_file__lifted_file_adt_t actual_file__lifted_file_adt(){
        actual_file__lifted_file_adt_t new = (actual_file__lifted_file_adt_t)safe_malloc(sizeof(struct actual_file__lifted_file_adt_s));
        new->equal_ptr = (equal_ptr_t)(*equal_file__lifted_file_adt_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_file__lifted_file_adt_ptr);
 

 
        return new;
 };

file__lifted_file_adt_t update_file__lifted_file_adt_file__lifted_file_adt_index(file__lifted_file_adt_t x, uint8_t v){
        file__lifted_file_adt_t y;
        if (x->count == 1){y = x;}
        else {y = copy_file__lifted_file_adt(x); x->count--;};
        y->file__lifted_file_adt_index = (uint8_t)v;
        return y;}




file__pass_t new_file__pass(void){
        file__pass_t tmp = (file__pass_t) safe_malloc(sizeof(struct file__pass_s));
        tmp->count = 1;
        return tmp;}

void release_file__pass(file__pass_t x){
        x->count--;
        if (x->count <= 0){
         release_file__file(x->contents);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_file__pass_ptr(pointer_t x, type_actual_t T){
        release_file__pass((file__pass_t)x);
}

file__pass_t copy_file__pass(file__pass_t x){
        file__pass_t y = new_file__pass();
        y->file__lifted_file_adt_index = (uint8_t)x->file__lifted_file_adt_index;
        y->contents = x->contents;
        if (y->contents != NULL){y->contents->count++;};
        y->count = 1;
        return y;}

bool_t equal_file__pass(file__pass_t x, file__pass_t y){
        bool_t tmp = true;
        tmp = tmp && x->file__lifted_file_adt_index == y->file__lifted_file_adt_index;
        tmp = tmp && equal_file__file(x->contents, y->contents);
        return tmp;}

bool_t equal_file__pass_ptr(pointer_t x, pointer_t y, actual_file__pass_t T){
        return equal_file__pass((file__pass_t)x, (file__pass_t)y);
}

actual_file__pass_t actual_file__pass(){
        actual_file__pass_t new = (actual_file__pass_t)safe_malloc(sizeof(struct actual_file__pass_s));
        new->equal_ptr = (equal_ptr_t)(*equal_file__pass_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_file__pass_ptr);
 

 
        return new;
 };

file__pass_t update_file__pass_file__lifted_file_adt_index(file__pass_t x, uint8_t v){
        file__pass_t y;
        if (x->count == 1){y = x;}
        else {y = copy_file__pass(x); x->count--;};
        y->file__lifted_file_adt_index = (uint8_t)v;
        return y;}

file__pass_t update_file__pass_contents(file__pass_t x, file__file_t v){
        file__pass_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->contents != NULL){release_file__file(x->contents);};}
        else {y = copy_file__pass(x); x->count--; y->contents->count--;};
        y->contents = (file__file_t)v;
        return y;}



void release_file_funtype_3(file_funtype_3_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

file_funtype_3_t copy_file_funtype_3(file_funtype_3_t x){return x->ftbl->cptr(x);}

bool_t equal_file_funtype_3(file_funtype_3_t x, file_funtype_3_t y){
        return false;}

void release_file_funtype_4(file_funtype_4_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

file_funtype_4_t copy_file_funtype_4(file_funtype_4_t x){return x->ftbl->cptr(x);}

bool_t equal_file_funtype_4(file_funtype_4_t x, file_funtype_4_t y){
        return false;}

void release_file_funtype_5(file_funtype_5_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

file_funtype_5_t copy_file_funtype_5(file_funtype_5_t x){return x->ftbl->cptr(x);}

bool_t equal_file_funtype_5(file_funtype_5_t x, file_funtype_5_t y){
        return false;}


mpz_ptr_t f_file_closure_6(struct file_closure_6_s * closure, file__lifted_file_adt_t bvar){
        mpz_ptr_t result = h_file_closure_6(bvar, closure->fvar_1, closure->fvar_2); 
        return result;}

mpz_ptr_t m_file_closure_6(struct file_closure_6_s * closure, file__lifted_file_adt_t bvar){
        return h_file_closure_6(bvar, closure->fvar_1, closure->fvar_2);}

extern mpz_ptr_t h_file_closure_6(file__lifted_file_adt_t ivar_9, file_funtype_5_t ivar_5, mpz_ptr_t ivar_4){
        mpz_ptr_t result;
        bool_t ivar_21;
        ivar_9->count++;
        ivar_21 = (bool_t)r_file__failp((file__lifted_file_adt_t)ivar_9);
        if (ivar_21){ 
             release_file__lifted_file_adt(ivar_9);
             //copying to mpz from mpz;
             mpz_mk_set(result, ivar_4);
} else {
        
             file__file_t ivar_25;
             ivar_25 = (file__file_t)file__lifted_file_adt_contents((file__lifted_file_adt_t)ivar_9);
             mpz_mk_set(result, ivar_5->ftbl->fptr(ivar_5, ivar_25));
};

        return result;
}

file_closure_6_t new_file_closure_6(void){
        static struct file_funtype_4_ftbl_s ftbl = {.fptr = (mpz_ptr_t (*)(file_funtype_4_t, file__lifted_file_adt_t))&f_file_closure_6, .mptr = (mpz_ptr_t (*)(file_funtype_4_t, file__lifted_file_adt_t))&m_file_closure_6, .rptr =  (void (*)(file_funtype_4_t))&release_file_closure_6, .cptr = (file_funtype_4_t (*)(file_funtype_4_t))&copy_file_closure_6};
        file_closure_6_t tmp = (file_closure_6_t) safe_malloc(sizeof(struct file_closure_6_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        mpz_init(tmp->fvar_2);
        return tmp;}

void release_file_closure_6(file_funtype_4_t closure){
        file_closure_6_t x = (file_closure_6_t)closure;
        x->count--;
        if (x->count <= 0){
         release_file_funtype_5(x->fvar_1);
        //printf("\nFreeing\n");
        safe_free(x);}}

file_closure_6_t copy_file_closure_6(file_closure_6_t x){
        file_closure_6_t y = new_file_closure_6();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        mpz_set(y->fvar_2, x->fvar_2);
        if (x->htbl != NULL){
            file_funtype_4_htbl_t new_htbl = (file_funtype_4_htbl_t) safe_malloc(sizeof(struct file_funtype_4_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            file_funtype_4_hashentry_t * new_data = (file_funtype_4_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct file_funtype_4_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct file_funtype_4_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


file_record_7_t new_file_record_7(void){
        file_record_7_t tmp = (file_record_7_t) safe_malloc(sizeof(struct file_record_7_s));
        tmp->count = 1;
        return tmp;}

void release_file_record_7(file_record_7_t x){
        x->count--;
        if (x->count <= 0){
         release_file__file(x->project_1);
         release_file__lifted_file_adt(x->project_2);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_file_record_7_ptr(pointer_t x, type_actual_t T){
        release_file_record_7((file_record_7_t)x);
}

file_record_7_t copy_file_record_7(file_record_7_t x){
        file_record_7_t y = new_file_record_7();
        y->project_1 = x->project_1;
        if (y->project_1 != NULL){y->project_1->count++;};
        y->project_2 = x->project_2;
        if (y->project_2 != NULL){y->project_2->count++;};
        y->count = 1;
        return y;}

bool_t equal_file_record_7(file_record_7_t x, file_record_7_t y){
        bool_t tmp = true;
        tmp = tmp && equal_file__file(x->project_1, y->project_1);
        tmp = tmp && equal_file__lifted_file_adt(x->project_2, y->project_2);
        return tmp;}

bool_t equal_file_record_7_ptr(pointer_t x, pointer_t y, actual_file_record_7_t T){
        return equal_file_record_7((file_record_7_t)x, (file_record_7_t)y);
}

actual_file_record_7_t actual_file_record_7(){
        actual_file_record_7_t new = (actual_file_record_7_t)safe_malloc(sizeof(struct actual_file_record_7_s));
        new->equal_ptr = (equal_ptr_t)(*equal_file_record_7_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_file_record_7_ptr);
 

 
        return new;
 };

file_record_7_t update_file_record_7_project_1(file_record_7_t x, file__file_t v){
        file_record_7_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_1 != NULL){release_file__file(x->project_1);};}
        else {y = copy_file_record_7(x); x->count--; y->project_1->count--;};
        y->project_1 = (file__file_t)v;
        return y;}

file_record_7_t update_file_record_7_project_2(file_record_7_t x, file__lifted_file_adt_t v){
        file_record_7_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_2 != NULL){release_file__lifted_file_adt(x->project_2);};}
        else {y = copy_file_record_7(x); x->count--; y->project_2->count--;};
        y->project_2 = (file__lifted_file_adt_t)v;
        return y;}



void release_file_funtype_8(file_funtype_8_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

file_funtype_8_t copy_file_funtype_8(file_funtype_8_t x){return x->ftbl->cptr(x);}

bool_t equal_file_funtype_8(file_funtype_8_t x, file_funtype_8_t y){
        return false;}


mpz_ptr_t f_file_closure_9(struct file_closure_9_s * closure, file__lifted_file_adt_t bvar){
        mpz_ptr_t result = h_file_closure_9(bvar, closure->fvar_1, closure->fvar_2); 
        return result;}

mpz_ptr_t m_file_closure_9(struct file_closure_9_s * closure, file__lifted_file_adt_t bvar){
        return h_file_closure_9(bvar, closure->fvar_1, closure->fvar_2);}

extern mpz_ptr_t h_file_closure_9(file__lifted_file_adt_t ivar_11, file_funtype_4_t ivar_5, file_funtype_8_t ivar_7){
        mpz_ptr_t result;
        bool_t ivar_29;
        ivar_11->count++;
        ivar_29 = (bool_t)r_file__failp((file__lifted_file_adt_t)ivar_11);
        if (ivar_29){ 
             mpz_mk_set(result, ivar_5->ftbl->fptr(ivar_5, ivar_11));
} else {
        
             file__file_t ivar_33;
             ivar_11->count++;
             ivar_33 = (file__file_t)file__lifted_file_adt_contents((file__lifted_file_adt_t)ivar_11);
             mpz_mk_set(result, ivar_7->ftbl->mptr(ivar_7, ivar_33, ivar_11));
};

        return result;
}

file_closure_9_t new_file_closure_9(void){
        static struct file_funtype_4_ftbl_s ftbl = {.fptr = (mpz_ptr_t (*)(file_funtype_4_t, file__lifted_file_adt_t))&f_file_closure_9, .mptr = (mpz_ptr_t (*)(file_funtype_4_t, file__lifted_file_adt_t))&m_file_closure_9, .rptr =  (void (*)(file_funtype_4_t))&release_file_closure_9, .cptr = (file_funtype_4_t (*)(file_funtype_4_t))&copy_file_closure_9};
        file_closure_9_t tmp = (file_closure_9_t) safe_malloc(sizeof(struct file_closure_9_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_file_closure_9(file_funtype_4_t closure){
        file_closure_9_t x = (file_closure_9_t)closure;
        x->count--;
        if (x->count <= 0){
         release_file_funtype_4(x->fvar_1);
         release_file_funtype_8(x->fvar_2);
        //printf("\nFreeing\n");
        safe_free(x);}}

file_closure_9_t copy_file_closure_9(file_closure_9_t x){
        file_closure_9_t y = new_file_closure_9();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        if (x->htbl != NULL){
            file_funtype_4_htbl_t new_htbl = (file_funtype_4_htbl_t) safe_malloc(sizeof(struct file_funtype_4_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            file_funtype_4_hashentry_t * new_data = (file_funtype_4_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct file_funtype_4_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct file_funtype_4_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

void release_file_funtype_10(file_funtype_10_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

file_funtype_10_t copy_file_funtype_10(file_funtype_10_t x){return x->ftbl->cptr(x);}

bool_t equal_file_funtype_10(file_funtype_10_t x, file_funtype_10_t y){
        return false;}

void release_file_funtype_11(file_funtype_11_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

file_funtype_11_t copy_file_funtype_11(file_funtype_11_t x){return x->ftbl->cptr(x);}

bool_t equal_file_funtype_11(file_funtype_11_t x, file_funtype_11_t y){
        return false;}


ordstruct_adt__ordstruct_adt_t f_file_closure_12(struct file_closure_12_s * closure, file__lifted_file_adt_t bvar){
        ordstruct_adt__ordstruct_adt_t result = h_file_closure_12(bvar, closure->fvar_1, closure->fvar_2); 
        return result;}

ordstruct_adt__ordstruct_adt_t m_file_closure_12(struct file_closure_12_s * closure, file__lifted_file_adt_t bvar){
        return h_file_closure_12(bvar, closure->fvar_1, closure->fvar_2);}

extern ordstruct_adt__ordstruct_adt_t h_file_closure_12(file__lifted_file_adt_t ivar_9, file_funtype_11_t ivar_5, ordstruct_adt__ordstruct_adt_t ivar_4){
        ordstruct_adt__ordstruct_adt_t result;
        bool_t ivar_21;
        ivar_9->count++;
        ivar_21 = (bool_t)r_file__failp((file__lifted_file_adt_t)ivar_9);
        if (ivar_21){ 
             release_file__lifted_file_adt(ivar_9);
             //copying to ordstruct_adt__ordstruct_adt from ordstruct_adt__ordstruct_adt;
             result = (ordstruct_adt__ordstruct_adt_t)ivar_4;
             if (result != NULL) result->count++;
} else {
        
             file__file_t ivar_25;
             ivar_25 = (file__file_t)file__lifted_file_adt_contents((file__lifted_file_adt_t)ivar_9);
             result = (ordstruct_adt__ordstruct_adt_t)ivar_5->ftbl->fptr(ivar_5, ivar_25);
};

        return result;
}

file_closure_12_t new_file_closure_12(void){
        static struct file_funtype_10_ftbl_s ftbl = {.fptr = (ordstruct_adt__ordstruct_adt_t (*)(file_funtype_10_t, file__lifted_file_adt_t))&f_file_closure_12, .mptr = (ordstruct_adt__ordstruct_adt_t (*)(file_funtype_10_t, file__lifted_file_adt_t))&m_file_closure_12, .rptr =  (void (*)(file_funtype_10_t))&release_file_closure_12, .cptr = (file_funtype_10_t (*)(file_funtype_10_t))&copy_file_closure_12};
        file_closure_12_t tmp = (file_closure_12_t) safe_malloc(sizeof(struct file_closure_12_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_file_closure_12(file_funtype_10_t closure){
        file_closure_12_t x = (file_closure_12_t)closure;
        x->count--;
        if (x->count <= 0){
         release_file_funtype_11(x->fvar_1);
         release_ordstruct_adt__ordstruct_adt(x->fvar_2);
        //printf("\nFreeing\n");
        safe_free(x);}}

file_closure_12_t copy_file_closure_12(file_closure_12_t x){
        file_closure_12_t y = new_file_closure_12();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        if (x->htbl != NULL){
            file_funtype_10_htbl_t new_htbl = (file_funtype_10_htbl_t) safe_malloc(sizeof(struct file_funtype_10_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            file_funtype_10_hashentry_t * new_data = (file_funtype_10_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct file_funtype_10_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct file_funtype_10_hashentry_s)));
            new_htbl->data = new_data;
            for (uint32_t j = 0; j < new_htbl->size; j++){
                        if ((new_htbl->data[j].key != 0) || new_htbl->data[j].keyhash != 0) new_htbl->data[j].value->count++;};
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

void release_file_funtype_13(file_funtype_13_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

file_funtype_13_t copy_file_funtype_13(file_funtype_13_t x){return x->ftbl->cptr(x);}

bool_t equal_file_funtype_13(file_funtype_13_t x, file_funtype_13_t y){
        return false;}


ordstruct_adt__ordstruct_adt_t f_file_closure_14(struct file_closure_14_s * closure, file__lifted_file_adt_t bvar){
        ordstruct_adt__ordstruct_adt_t result = h_file_closure_14(bvar, closure->fvar_1, closure->fvar_2); 
        return result;}

ordstruct_adt__ordstruct_adt_t m_file_closure_14(struct file_closure_14_s * closure, file__lifted_file_adt_t bvar){
        return h_file_closure_14(bvar, closure->fvar_1, closure->fvar_2);}

extern ordstruct_adt__ordstruct_adt_t h_file_closure_14(file__lifted_file_adt_t ivar_11, file_funtype_10_t ivar_5, file_funtype_13_t ivar_7){
        ordstruct_adt__ordstruct_adt_t result;
        bool_t ivar_29;
        ivar_11->count++;
        ivar_29 = (bool_t)r_file__failp((file__lifted_file_adt_t)ivar_11);
        if (ivar_29){ 
             result = (ordstruct_adt__ordstruct_adt_t)ivar_5->ftbl->fptr(ivar_5, ivar_11);
} else {
        
             file__file_t ivar_33;
             ivar_11->count++;
             ivar_33 = (file__file_t)file__lifted_file_adt_contents((file__lifted_file_adt_t)ivar_11);
             result = (ordstruct_adt__ordstruct_adt_t)ivar_7->ftbl->mptr(ivar_7, ivar_33, ivar_11);
};

        return result;
}

file_closure_14_t new_file_closure_14(void){
        static struct file_funtype_10_ftbl_s ftbl = {.fptr = (ordstruct_adt__ordstruct_adt_t (*)(file_funtype_10_t, file__lifted_file_adt_t))&f_file_closure_14, .mptr = (ordstruct_adt__ordstruct_adt_t (*)(file_funtype_10_t, file__lifted_file_adt_t))&m_file_closure_14, .rptr =  (void (*)(file_funtype_10_t))&release_file_closure_14, .cptr = (file_funtype_10_t (*)(file_funtype_10_t))&copy_file_closure_14};
        file_closure_14_t tmp = (file_closure_14_t) safe_malloc(sizeof(struct file_closure_14_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_file_closure_14(file_funtype_10_t closure){
        file_closure_14_t x = (file_closure_14_t)closure;
        x->count--;
        if (x->count <= 0){
         release_file_funtype_10(x->fvar_1);
         release_file_funtype_13(x->fvar_2);
        //printf("\nFreeing\n");
        safe_free(x);}}

file_closure_14_t copy_file_closure_14(file_closure_14_t x){
        file_closure_14_t y = new_file_closure_14();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        if (x->htbl != NULL){
            file_funtype_10_htbl_t new_htbl = (file_funtype_10_htbl_t) safe_malloc(sizeof(struct file_funtype_10_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            file_funtype_10_hashentry_t * new_data = (file_funtype_10_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct file_funtype_10_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct file_funtype_10_hashentry_s)));
            new_htbl->data = new_data;
            for (uint32_t j = 0; j < new_htbl->size; j++){
                        if ((new_htbl->data[j].key != 0) || new_htbl->data[j].keyhash != 0) new_htbl->data[j].value->count++;};
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

extern int32_t file__max_file_size(void){
        int32_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    pvs2cerror("Missing definition", PVS2C_EXIT_ERROR);

        defined = true;};
        
        return result;
}

extern bool_t r_file__failp(file__lifted_file_adt_t ivar_1){
        bool_t  result;
        uint8_t ivar_3;
        ivar_3 = (uint8_t)0;
        uint8_t ivar_2;
        ivar_2 = (uint8_t)ivar_1->file__lifted_file_adt_index;
        release_file__lifted_file_adt(ivar_1);
        result = (ivar_2 == ivar_3);

        
        return result;
}

extern bool_t r_file__passp(file__lifted_file_adt_t ivar_1){
        bool_t  result;
        uint8_t ivar_3;
        ivar_3 = (uint8_t)1;
        uint8_t ivar_2;
        ivar_2 = (uint8_t)ivar_1->file__lifted_file_adt_index;
        release_file__lifted_file_adt(ivar_1);
        result = (ivar_2 == ivar_3);

        
        return result;
}

extern file__pass_t update_file__lifted_file_adt_contents(file__lifted_file_adt_t ivar_1, file__file_t ivar_3){
        file__pass_t  result;
        file__pass_t ivar_2;
        //copying to file__pass from file__lifted_file_adt;
        ivar_2 = (file__pass_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_file__lifted_file_adt(ivar_1);
        result = (file__pass_t)update_file__pass_contents(ivar_2, ivar_3);

        
        return result;
}

extern file__file_t file__lifted_file_adt_contents(file__lifted_file_adt_t ivar_1){
        file__file_t  result;
        file__pass_t ivar_2;
        //copying to file__pass from file__lifted_file_adt;
        ivar_2 = (file__pass_t)ivar_1;
        if (ivar_2 != NULL) ivar_2->count++;
        release_file__lifted_file_adt(ivar_1);
        result = (file__file_t)ivar_2->contents;
        result->count++;
        release_file__pass(ivar_2);

        
        return result;
}

extern file__lifted_file_adt_t file__fail(void){
        file__lifted_file_adt_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    uint8_t ivar_1;
        ivar_1 = (uint8_t)0;
        file__lifted_file_adt_t tmp16188 = new_file__lifted_file_adt();;
        result = (file__lifted_file_adt_t)tmp16188;
        tmp16188->file__lifted_file_adt_index = (uint8_t)ivar_1;

        defined = true;};
        
        return result;
}

extern file__lifted_file_adt_t file__pass(file__file_t ivar_2){
        file__lifted_file_adt_t  result;
        uint8_t ivar_1;
        ivar_1 = (uint8_t)1;
        file__pass_t tmp16189 = new_file__pass();;
        result = (file__lifted_file_adt_t)tmp16189;
        tmp16189->file__lifted_file_adt_index = (uint8_t)ivar_1;
        tmp16189->contents = (file__file_t)ivar_2;

        
        return result;
}

extern file_funtype_3_t file__lifted_file_ord(void){
        file_funtype_3_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    pvs2cerror("Missing definition", PVS2C_EXIT_ERROR);

        defined = true;};
        
        return result;
}

extern uint8_t file__ord(file__lifted_file_adt_t ivar_2){
        uint8_t  result;
        bool_t ivar_4;
        ivar_2->count++;
        ivar_4 = (bool_t)r_file__failp((file__lifted_file_adt_t)ivar_2);
        if (ivar_4){ 
             release_file__lifted_file_adt(ivar_2);
             result = (uint8_t)0;
} else {
        
             result = (uint8_t)1;
};

        
        return result;
}

extern bool_t file__subterm(file__lifted_file_adt_t ivar_1, file__lifted_file_adt_t ivar_2){
        bool_t  result;
        result = (bool_t) equal_file__lifted_file_adt(ivar_1, ivar_2);

        
        return result;
}

extern bool_t file__doublelessp(file__lifted_file_adt_t ivar_1, file__lifted_file_adt_t ivar_2){
        bool_t  result;
        result = (bool_t) false;

        
        return result;
}

extern file_funtype_4_t file__reduce_nat(mpz_ptr_t ivar_4, file_funtype_5_t ivar_5){
        file_funtype_4_t  result;
        file_closure_6_t cl16192;
        cl16192 = new_file_closure_6();
        cl16192->fvar_1 = (file_funtype_5_t)ivar_5;
        if (cl16192->fvar_1 != NULL) cl16192->fvar_1->count++;
        mpz_set(cl16192->fvar_2, ivar_4);
        release_file_funtype_5(ivar_5);
        result = (file_funtype_4_t)cl16192;

        
        return result;
}

extern file_funtype_4_t file__REDUCE_nat(file_funtype_4_t ivar_5, file_funtype_8_t ivar_7){
        file_funtype_4_t  result;
        file_closure_9_t cl16194;
        cl16194 = new_file_closure_9();
        cl16194->fvar_1 = (file_funtype_4_t)ivar_5;
        if (cl16194->fvar_1 != NULL) cl16194->fvar_1->count++;
        cl16194->fvar_2 = (file_funtype_8_t)ivar_7;
        if (cl16194->fvar_2 != NULL) cl16194->fvar_2->count++;
        release_file_funtype_8(ivar_7);
        release_file_funtype_4(ivar_5);
        result = (file_funtype_4_t)cl16194;

        
        return result;
}

extern file_funtype_10_t file__reduce_ordinal(ordstruct_adt__ordstruct_adt_t ivar_4, file_funtype_11_t ivar_5){
        file_funtype_10_t  result;
        file_closure_12_t cl16196;
        cl16196 = new_file_closure_12();
        cl16196->fvar_1 = (file_funtype_11_t)ivar_5;
        if (cl16196->fvar_1 != NULL) cl16196->fvar_1->count++;
        cl16196->fvar_2 = (ordstruct_adt__ordstruct_adt_t)ivar_4;
        if (cl16196->fvar_2 != NULL) cl16196->fvar_2->count++;
        release_file_funtype_11(ivar_5);
        release_ordstruct_adt__ordstruct_adt(ivar_4);
        result = (file_funtype_10_t)cl16196;

        
        return result;
}

extern file_funtype_10_t file__REDUCE_ordinal(file_funtype_10_t ivar_5, file_funtype_13_t ivar_7){
        file_funtype_10_t  result;
        file_closure_14_t cl16198;
        cl16198 = new_file_closure_14();
        cl16198->fvar_1 = (file_funtype_10_t)ivar_5;
        if (cl16198->fvar_1 != NULL) cl16198->fvar_1->count++;
        cl16198->fvar_2 = (file_funtype_13_t)ivar_7;
        if (cl16198->fvar_2 != NULL) cl16198->fvar_2->count++;
        release_file_funtype_13(ivar_7);
        release_file_funtype_10(ivar_5);
        result = (file_funtype_10_t)cl16198;

        
        return result;
}

bool_t file__openp(file__file_t f){struct stat s;
    return (fstat(f->fd, &s) != -1);
   }

file__lifted_file_adt_t file__open(bytestrings__bytestring_t name){
    char * filenamestring = byte2cstring(name->length, name->seq->elems);
    uint64_t fd = open(filenamestring, O_RDWR, S_IRUSR | S_IWUSR);
    release_bytestrings__bytestring(name); 
    safe_free(filenamestring);
    struct stat s;
    if (fstat(fd, &s) == -1){
       return file__fail(); //pvs2cerror("File size extraction failed.n")
       }
    uint32_t size = s.st_size;
    uint32_t capacity = 4096 * (size/4096 + 1);
    char * contents = (char *) mmap(NULL, capacity, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    file_t ff = (file_t) safe_malloc(sizeof(file_s));
    ff->count = 1;
    ff->fd = fd;
    ff->size = size;
    ff->capacity = capacity;
    ff->contents = contents;
    ff->name = filenamestring;
    return file__pass(ff);
   }

file__lifted_file_adt_t file__append(file__file_t f, bytestrings__bytestring_t b){uint64_t fd = f->fd;
    uint32_t size = f->size;
    uint32_t capacity = f->capacity;
    char * contents = f->contents;
    uint32_t len = b->length;
    char * data = (char *)b->seq->elems;
    ftruncate(fd, size + len);
    if (size + len < capacity){
    for (size_t i = 0; i < len; i++)
      contents[i + size] = data[i];
  } else {
    munmap(contents, capacity);
    uint32_t new_capacity = capacity + (10 * 4096);
    char * new_contents = mmap(NULL, new_capacity, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
    for (size_t i = 0; i < len; i++)
      new_contents[i + size] = data[i];
    f->contents = new_contents;
 };
   f->size = size + len;
   return file__pass(f);
}

uint32_t file__file_size(file__file_t f){uint32_t result = f->size;
    release_file__file(f);
    return result;}

uint8_t file__getbyte(file__file_t f, uint32_t i){uint8_t result = f->contents[i];
    release_file__file(f);
    return result;
}

bytestrings__bytestring_t file__getbytestring(file__file_t f, uint32_t i, uint32_t size){bytestrings_array_0_t newarray = new_bytestrings_array_0(size);
    memcpy(newarray, (char *) f->contents + i, size);
    bytestrings__bytestring_t newstring = new_bytestrings__bytestring();
    newstring->length = size;
    newstring->seq = newarray;
    release_file__file(f);
    return newstring;
    }

file__file_t file__setbyte(file__file_t f, uint32_t i, uint8_t b){if (f->count == 1){
     f->contents[i] = b;
     };
    return f;
}

bytestrings__bytestring_t file__printc(bytestrings__bytestring_t b){printf("\n");
    for (uint32_t i = 0; i < b->length; i++) printf("%c", b->seq->elems[i]);
    return b;
   }


bytestrings__bytestring_t file__printh(bytestrings__bytestring_t b){printf("\n");
    for (uint32_t i = 0; i < b->length; i++) printf("%02X", b->seq->elems[i]);
    return b;
   }
