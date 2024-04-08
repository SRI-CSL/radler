//Code generated using pvs2ir2c
#include "Rijndael_c.h"


Rijndael_record_0_t new_Rijndael_record_0(void){
        Rijndael_record_0_t tmp = (Rijndael_record_0_t) safe_malloc(sizeof(struct Rijndael_record_0_s));
        tmp->count = 1;
        return tmp;}

void release_Rijndael_record_0(Rijndael_record_0_t x){
        x->count--;
        if (x->count <= 0){
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_Rijndael_record_0_ptr(pointer_t x, type_actual_t T){
        release_Rijndael_record_0((Rijndael_record_0_t)x);
}

Rijndael_record_0_t copy_Rijndael_record_0(Rijndael_record_0_t x){
        Rijndael_record_0_t y = new_Rijndael_record_0();
        y->project_1 = (uint8_t)x->project_1;
        y->project_2 = (uint8_t)x->project_2;
        y->count = 1;
        return y;}

bool_t equal_Rijndael_record_0(Rijndael_record_0_t x, Rijndael_record_0_t y){
        bool_t tmp = true;
        tmp = tmp && x->project_1 == y->project_1;
        tmp = tmp && x->project_2 == y->project_2;
        return tmp;}

bool_t equal_Rijndael_record_0_ptr(pointer_t x, pointer_t y, actual_Rijndael_record_0_t T){
        return equal_Rijndael_record_0((Rijndael_record_0_t)x, (Rijndael_record_0_t)y);
}

actual_Rijndael_record_0_t actual_Rijndael_record_0(){
        actual_Rijndael_record_0_t new = (actual_Rijndael_record_0_t)safe_malloc(sizeof(struct actual_Rijndael_record_0_s));
        new->equal_ptr = (equal_ptr_t)(*equal_Rijndael_record_0_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_Rijndael_record_0_ptr);
 

 
        return new;
 };

Rijndael_record_0_t update_Rijndael_record_0_project_1(Rijndael_record_0_t x, uint8_t v){
        Rijndael_record_0_t y;
        if (x->count == 1){y = x;}
        else {y = copy_Rijndael_record_0(x); x->count--;};
        y->project_1 = (uint8_t)v;
        return y;}

Rijndael_record_0_t update_Rijndael_record_0_project_2(Rijndael_record_0_t x, uint8_t v){
        Rijndael_record_0_t y;
        if (x->count == 1){y = x;}
        else {y = copy_Rijndael_record_0(x); x->count--;};
        y->project_2 = (uint8_t)v;
        return y;}



void release_Rijndael_funtype_1(Rijndael_funtype_1_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

Rijndael_funtype_1_t copy_Rijndael_funtype_1(Rijndael_funtype_1_t x){return x->ftbl->cptr(x);}

bool_t equal_Rijndael_funtype_1(Rijndael_funtype_1_t x, Rijndael_funtype_1_t y){
        return false;}


Rijndael_array_2_t new_Rijndael_array_2(uint32_t size){
        Rijndael_array_2_t tmp = (Rijndael_array_2_t) safe_malloc(sizeof(struct Rijndael_array_2_s) + (size * sizeof(uint8_t)));
        tmp->count = 1;
        tmp->size = size;;
        tmp->max = size;
         return tmp;}

void release_Rijndael_array_2(Rijndael_array_2_t x){
        x->count--;
         if (x->count <= 0){safe_free(x);}
}

void release_Rijndael_array_2_ptr(pointer_t x, type_actual_t T){
        release_Rijndael_array_2((Rijndael_array_2_t)x);
}

Rijndael_array_2_t copy_Rijndael_array_2(Rijndael_array_2_t x){
        Rijndael_array_2_t tmp = new_Rijndael_array_2(x->size);
        tmp->count = 1;
        for (uint32_t i = 0; i < x->size; i++){tmp->elems[i] = (uint8_t)x->elems[i];};
         return tmp;}

bool_t equal_Rijndael_array_2(Rijndael_array_2_t x, Rijndael_array_2_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = (x->elems[i] == y->elems[i]); i++;};
        return tmp;}

bool_t equal_Rijndael_array_2_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_Rijndael_array_2((Rijndael_array_2_t)x, (Rijndael_array_2_t)y);
}

actual_Rijndael_array_2_t actual_Rijndael_array_2(){
        actual_Rijndael_array_2_t new = (actual_Rijndael_array_2_t)safe_malloc(sizeof(struct actual_Rijndael_array_2_s));
        new->equal_ptr = (equal_ptr_t)(*equal_Rijndael_array_2_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_Rijndael_array_2_ptr);
 

 
        return new;
 };

Rijndael_array_2_t update_Rijndael_array_2(Rijndael_array_2_t x, uint32_t i, uint8_t v){
        Rijndael_array_2_t y; 
         if (x->count == 1){y = x;}
           else {y = copy_Rijndael_array_2(x );
                x->count--;};
        y->elems[i] = (uint8_t)v;
        return y;}

Rijndael_array_2_t upgrade_Rijndael_array_2(Rijndael_array_2_t x, uint32_t i, uint8_t v){
        Rijndael_array_2_t y; 
         if (x->count == 1 && i < x->max){y = x;}
           else if (i > x->max){uint32_t newmax = x->max <= UINT32_MAX/2 ? 2*x->max: UINT32_MAX;
                y = safe_realloc(x, sizeof(struct Rijndael_array_2_s) + (newmax * sizeof(uint8_t)));
                y->count = 1;
                y->size = i+1;
                y->max = newmax;
                release_Rijndael_array_2(x);}
           else {y = copy_Rijndael_array_2(x );
                x->count--;};
        y->elems[i] = (uint8_t)v;
        return y;}




uint8_t f_Rijndael_closure_3(struct Rijndael_closure_3_s * closure, Rijndael_record_0_t bvar){
        uint8_t bvar_1;
        bvar_1 = (uint8_t)bvar->project_1;
        uint8_t bvar_2;
        bvar_2 = (uint8_t)bvar->project_2;
        release_Rijndael_record_0(bvar);
        uint8_t result = h_Rijndael_closure_3(bvar_1, bvar_2, closure->fvar_1); 
        return result;}

uint8_t m_Rijndael_closure_3(struct Rijndael_closure_3_s * closure, uint8_t bvar_1, uint8_t bvar_2){
        return h_Rijndael_closure_3(bvar_1, bvar_2, closure->fvar_1);}

extern uint8_t h_Rijndael_closure_3(uint8_t ivar_6, uint8_t ivar_7, Rijndael_array_2_t ivar_3){
        uint8_t result;
        uint8_t ivar_17;
        uint8_t ivar_10;
        uint8_t ivar_11;
        ivar_11 = (uint8_t)4;
        ivar_10 = (uint8_t)((uint64_t)ivar_11 * (uint64_t)ivar_7);
        ivar_17 = (uint8_t)(ivar_6 + ivar_10);
        result = (uint8_t)ivar_3->elems[ivar_17];

        return result;
}

Rijndael_closure_3_t new_Rijndael_closure_3(void){
        static struct Rijndael_funtype_1_ftbl_s ftbl = {.fptr = (uint8_t (*)(Rijndael_funtype_1_t, Rijndael_record_0_t))&f_Rijndael_closure_3, .mptr = (uint8_t (*)(Rijndael_funtype_1_t, uint8_t, uint8_t))&m_Rijndael_closure_3, .rptr =  (void (*)(Rijndael_funtype_1_t))&release_Rijndael_closure_3, .cptr = (Rijndael_funtype_1_t (*)(Rijndael_funtype_1_t))&copy_Rijndael_closure_3};
        Rijndael_closure_3_t tmp = (Rijndael_closure_3_t) safe_malloc(sizeof(struct Rijndael_closure_3_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_Rijndael_closure_3(Rijndael_funtype_1_t closure){
        Rijndael_closure_3_t x = (Rijndael_closure_3_t)closure;
        x->count--;
        if (x->count <= 0){
         release_Rijndael_array_2(x->fvar_1);
        //printf("\nFreeing\n");
        safe_free(x);}}

Rijndael_closure_3_t copy_Rijndael_closure_3(Rijndael_closure_3_t x){
        Rijndael_closure_3_t y = new_Rijndael_closure_3();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        if (x->htbl != NULL){
            Rijndael_funtype_1_htbl_t new_htbl = (Rijndael_funtype_1_htbl_t) safe_malloc(sizeof(struct Rijndael_funtype_1_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            Rijndael_funtype_1_hashentry_t * new_data = (Rijndael_funtype_1_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct Rijndael_funtype_1_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct Rijndael_funtype_1_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

void release_Rijndael_funtype_4(Rijndael_funtype_4_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

Rijndael_funtype_4_t copy_Rijndael_funtype_4(Rijndael_funtype_4_t x){return x->ftbl->cptr(x);}

uint32_t lookup_Rijndael_funtype_4(Rijndael_funtype_4_htbl_t htbl, mpz_ptr_t i, uint32_t ihash){
        uint32_t mask = htbl->size - 1;
        uint32_t hashindex = ihash & mask;
        Rijndael_funtype_4_hashentry_t data = htbl->data[hashindex];
        bool_t keyzero;

        int64_t tmp15884 = mpz_cmp_ui(data.key, 0);
        keyzero = (tmp15884 == 0);
        bool_t keymatch;
        int64_t tmp15885 = mpz_cmp(data.key, i);
        keymatch = (tmp15885 == 0);
        while ((!keyzero || data.keyhash != 0) &&
                 (data.keyhash != ihash || !keymatch)){
                hashindex++;
                hashindex = hashindex & mask;
                data = htbl->data[hashindex];

                int64_t tmp15884 = mpz_cmp_ui(data.key, 0);
                keyzero = (tmp15884 == 0);

                int64_t tmp15885 = mpz_cmp(data.key, i);
                keymatch = (tmp15885 == 0);
                }
        return hashindex;
        }

Rijndael_funtype_4_t dupdate_Rijndael_funtype_4(Rijndael_funtype_4_t a, mpz_ptr_t i, bool_t v){
        Rijndael_funtype_4_htbl_t htbl = a->htbl;
        if (htbl == NULL){//construct new htbl
                htbl = (Rijndael_funtype_4_htbl_t)safe_malloc(sizeof(struct Rijndael_funtype_4_htbl_s));
                htbl->size = HTBL_DEFAULT_SIZE; htbl->num_entries = 0;
                htbl->data = (Rijndael_funtype_4_hashentry_t *)safe_malloc(HTBL_DEFAULT_SIZE * sizeof(struct Rijndael_funtype_4_hashentry_s));
                for (uint32_t j = 0; j < HTBL_DEFAULT_SIZE; j++){mpz_init(htbl->data[j].key);mpz_set_ui(htbl->data[j].key, 0); htbl->data[j].keyhash = 0;
                }
                a->htbl = htbl;
        }
        uint32_t size = htbl->size;
        uint32_t num_entries = htbl->num_entries;
        Rijndael_funtype_4_hashentry_t * data = htbl->data;
        if (num_entries/3 >  size/5){//resize data
                uint32_t new_size = 2*size; uint32_t new_mask = new_size - 1;
                if (size >= HTBL_MAX_SIZE) out_of_memory();
                Rijndael_funtype_4_hashentry_t * new_data = (Rijndael_funtype_4_hashentry_t *)safe_malloc(new_size * sizeof(struct Rijndael_funtype_4_hashentry_s));
                for (uint32_t j = 0; j < new_size; j++){
                        new_data[j].key = 0;
                        new_data[j].keyhash = 0;}
                for (uint32_t j = 0; j < size; j++){//transfer entries
                        uint32_t keyhash = data[j].keyhash;
                        bool_t keyzero;
                        int64_t tmp15886 = mpz_cmp_ui(data[j].key, 0);keyzero = (tmp15886 == 0);
                        if (!keyzero || keyhash != 0){
                                uint32_t new_loc = keyhash ^ new_mask;
                                int64_t tmp15887 = mpz_cmp_ui(new_data[new_loc].key, 0);
                                keyzero = (tmp15887 == 0);
                                while (keyzero && new_data[new_loc].keyhash == 0){
                                        new_loc++;
                                        new_loc = new_loc ^ new_mask;

                                        int64_t tmp15888 = mpz_cmp_ui(new_data[new_loc].key, 0);
                                        keyzero = (tmp15888 == 0);
                                }
                                mpz_set(new_data[new_loc].key, data[j].key);
                                new_data[new_loc].keyhash = keyhash;
                                new_data[new_loc].value = (bool_t)data[j].value;
                                }}
                htbl->size = new_size;
                htbl->num_entries = num_entries;
                htbl->data = new_data;
                safe_free(data);}
        uint32_t ihash = mpz_hash(i);
        uint32_t hashindex = lookup_Rijndael_funtype_4(htbl, i, ihash);
        Rijndael_funtype_4_hashentry_t hentry = htbl->data[hashindex];
        uint32_t hkeyhash = hentry.keyhash;
        bool_t hentrykeyzero;
        int64_t tmp15889 = mpz_cmp_ui(hentry.key, 0);hentrykeyzero = (tmp15889 == 0);

        if (hentrykeyzero && (hkeyhash == 0))
                {mpz_set(htbl->data[hashindex].key, i); htbl->data[hashindex].keyhash = ihash; htbl->data[hashindex].value = (bool_t)v; htbl->num_entries++;}
            else {bool_t tempvalue;tempvalue = (bool_t)htbl->data[hashindex].value;htbl->data[hashindex].value = (bool_t)v;};
        return a;

}

Rijndael_funtype_4_t update_Rijndael_funtype_4(Rijndael_funtype_4_t a, mpz_ptr_t i, bool_t v){
        if (a->count == 1){
                return dupdate_Rijndael_funtype_4(a, i, v);
            } else {
                Rijndael_funtype_4_t x = copy_Rijndael_funtype_4(a);
                a->count--;
                return dupdate_Rijndael_funtype_4(x, i, v);
            }}

bool_t equal_Rijndael_funtype_4(Rijndael_funtype_4_t x, Rijndael_funtype_4_t y){
        return false;}


Rijndael_record_5_t new_Rijndael_record_5(void){
        Rijndael_record_5_t tmp = (Rijndael_record_5_t) safe_malloc(sizeof(struct Rijndael_record_5_s));
        tmp->count = 1;
        return tmp;}

void release_Rijndael_record_5(Rijndael_record_5_t x){
        x->count--;
        if (x->count <= 0){
         release_Rijndael_funtype_4(x->project_1);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_Rijndael_record_5_ptr(pointer_t x, type_actual_t T){
        release_Rijndael_record_5((Rijndael_record_5_t)x);
}

Rijndael_record_5_t copy_Rijndael_record_5(Rijndael_record_5_t x){
        Rijndael_record_5_t y = new_Rijndael_record_5();
        y->project_1 = x->project_1;
        if (y->project_1 != NULL){y->project_1->count++;};
        mpz_set(y->project_2, x->project_2);
        y->count = 1;
        return y;}

bool_t equal_Rijndael_record_5(Rijndael_record_5_t x, Rijndael_record_5_t y){
        bool_t tmp = true;
        tmp = tmp && equal_Rijndael_funtype_4(x->project_1, y->project_1);
        tmp = tmp && x->project_2 == y->project_2;
        return tmp;}

bool_t equal_Rijndael_record_5_ptr(pointer_t x, pointer_t y, actual_Rijndael_record_5_t T){
        return equal_Rijndael_record_5((Rijndael_record_5_t)x, (Rijndael_record_5_t)y);
}

actual_Rijndael_record_5_t actual_Rijndael_record_5(){
        actual_Rijndael_record_5_t new = (actual_Rijndael_record_5_t)safe_malloc(sizeof(struct actual_Rijndael_record_5_s));
        new->equal_ptr = (equal_ptr_t)(*equal_Rijndael_record_5_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_Rijndael_record_5_ptr);
 

 
        return new;
 };

Rijndael_record_5_t update_Rijndael_record_5_project_1(Rijndael_record_5_t x, Rijndael_funtype_4_t v){
        Rijndael_record_5_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->project_1 != NULL){release_Rijndael_funtype_4(x->project_1);};}
        else {y = copy_Rijndael_record_5(x); x->count--; y->project_1->count--;};
        y->project_1 = (Rijndael_funtype_4_t)v;
        return y;}

Rijndael_record_5_t update_Rijndael_record_5_project_2(Rijndael_record_5_t x, mpz_ptr_t v){
        Rijndael_record_5_t y;
        if (x->count == 1){y = x;}
        else {y = copy_Rijndael_record_5(x); x->count--;};
        mpz_set(y->project_2, v);
        return y;}



void release_Rijndael_funtype_6(Rijndael_funtype_6_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

Rijndael_funtype_6_t copy_Rijndael_funtype_6(Rijndael_funtype_6_t x){return x->ftbl->cptr(x);}

bool_t equal_Rijndael_funtype_6(Rijndael_funtype_6_t x, Rijndael_funtype_6_t y){
        return false;}


bool_t f_Rijndael_closure_7(struct Rijndael_closure_7_s * closure, Rijndael_record_5_t bvar){
        Rijndael_funtype_4_t bvar_1;
        bvar_1 = (Rijndael_funtype_4_t)bvar->project_1;
        bvar->project_1->count++;
        mpz_t bvar_2;
        mpz_init(bvar_2);
        mpz_set(bvar_2, bvar->project_2);
        release_Rijndael_record_5(bvar);
        bool_t result = h_Rijndael_closure_7(bvar_1, bvar_2, closure->fvar_1); 
        release_Rijndael_funtype_4(bvar_1);
        release_mpz(bvar_2);
        return result;}

bool_t m_Rijndael_closure_7(struct Rijndael_closure_7_s * closure, Rijndael_funtype_4_t bvar_1, mpz_ptr_t bvar_2){
        return h_Rijndael_closure_7(bvar_1, bvar_2, closure->fvar_1);}

extern bool_t h_Rijndael_closure_7(Rijndael_funtype_4_t ivar_4, mpz_ptr_t ivar_6, mpz_ptr_t ivar_1){
        bool_t result;
        bool_t ivar_7;
        uint8_t ivar_9;
        ivar_9 = (uint8_t)0;
        int64_t tmp15890 = mpz_cmp_ui(ivar_6, ivar_9);
        ivar_7 = (tmp15890 == 0);
        if (ivar_7){ 
             release_Rijndael_funtype_4(ivar_4);
             result = (bool_t) true;
} else {
        
             bool_t ivar_11;
             mpz_ptr_t ivar_20;
             uint8_t ivar_15;
             ivar_15 = (uint8_t)1;
             mpz_mk_sub_ui(ivar_20, ivar_6, (uint64_t)ivar_15);
             ivar_11 = (bool_t)ivar_4->ftbl->fptr(ivar_4, ivar_20);
             if (ivar_11){  
           Rijndael_funtype_6_t ivar_29;
           ivar_29 = (Rijndael_funtype_6_t)Rijndael__every(ivar_1);
           mpz_ptr_t ivar_36;
           uint8_t ivar_24;
           ivar_24 = (uint8_t)1;
           mpz_mk_sub_ui(ivar_36, ivar_6, (uint64_t)ivar_24);
           result = (bool_t)ivar_29->ftbl->mptr(ivar_29, ivar_4, ivar_36);
           ivar_29->ftbl->rptr(ivar_29);
} else {
             
           release_Rijndael_funtype_4(ivar_4);
           result = (bool_t) false;
};
};

        return result;
}

Rijndael_closure_7_t new_Rijndael_closure_7(void){
        static struct Rijndael_funtype_6_ftbl_s ftbl = {.fptr = (bool_t (*)(Rijndael_funtype_6_t, Rijndael_record_5_t))&f_Rijndael_closure_7, .mptr = (bool_t (*)(Rijndael_funtype_6_t, Rijndael_funtype_4_t, mpz_ptr_t))&m_Rijndael_closure_7, .rptr =  (void (*)(Rijndael_funtype_6_t))&release_Rijndael_closure_7, .cptr = (Rijndael_funtype_6_t (*)(Rijndael_funtype_6_t))&copy_Rijndael_closure_7};
        Rijndael_closure_7_t tmp = (Rijndael_closure_7_t) safe_malloc(sizeof(struct Rijndael_closure_7_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        mpz_init(tmp->fvar_1);
        return tmp;}

void release_Rijndael_closure_7(Rijndael_funtype_6_t closure){
        Rijndael_closure_7_t x = (Rijndael_closure_7_t)closure;
        x->count--;
        if (x->count <= 0){
        //printf("\nFreeing\n");
        safe_free(x);}}

Rijndael_closure_7_t copy_Rijndael_closure_7(Rijndael_closure_7_t x){
        Rijndael_closure_7_t y = new_Rijndael_closure_7();
        y->ftbl = x->ftbl;

        mpz_set(y->fvar_1, x->fvar_1);
        if (x->htbl != NULL){
            Rijndael_funtype_6_htbl_t new_htbl = (Rijndael_funtype_6_htbl_t) safe_malloc(sizeof(struct Rijndael_funtype_6_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            Rijndael_funtype_6_hashentry_t * new_data = (Rijndael_funtype_6_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct Rijndael_funtype_6_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct Rijndael_funtype_6_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

void release_Rijndael_funtype_8(Rijndael_funtype_8_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

Rijndael_funtype_8_t copy_Rijndael_funtype_8(Rijndael_funtype_8_t x){return x->ftbl->cptr(x);}

uint32_t lookup_Rijndael_funtype_8(Rijndael_funtype_8_htbl_t htbl, uint8_t i, uint32_t ihash){
        uint32_t mask = htbl->size - 1;
        uint32_t hashindex = ihash & mask;
        Rijndael_funtype_8_hashentry_t data = htbl->data[hashindex];
        bool_t keyzero;

        keyzero = (data.key == 0);
        bool_t keymatch;
        keymatch = (data.key == i);
        while ((!keyzero || data.keyhash != 0) &&
                 (data.keyhash != ihash || !keymatch)){
                hashindex++;
                hashindex = hashindex & mask;
                data = htbl->data[hashindex];

                keyzero = (data.key == 0);

                keymatch = (data.key == i);
                }
        return hashindex;
        }

Rijndael_funtype_8_t dupdate_Rijndael_funtype_8(Rijndael_funtype_8_t a, uint8_t i, uint8_t v){
        Rijndael_funtype_8_htbl_t htbl = a->htbl;
        if (htbl == NULL){//construct new htbl
                htbl = (Rijndael_funtype_8_htbl_t)safe_malloc(sizeof(struct Rijndael_funtype_8_htbl_s));
                htbl->size = HTBL_DEFAULT_SIZE; htbl->num_entries = 0;
                htbl->data = (Rijndael_funtype_8_hashentry_t *)safe_malloc(HTBL_DEFAULT_SIZE * sizeof(struct Rijndael_funtype_8_hashentry_s));
                for (uint32_t j = 0; j < HTBL_DEFAULT_SIZE; j++){htbl->data[j].key = (uint8_t)0; htbl->data[j].keyhash = 0;
                }
                a->htbl = htbl;
        }
        uint32_t size = htbl->size;
        uint32_t num_entries = htbl->num_entries;
        Rijndael_funtype_8_hashentry_t * data = htbl->data;
        if (num_entries/3 >  size/5){//resize data
                uint32_t new_size = 2*size; uint32_t new_mask = new_size - 1;
                if (size >= HTBL_MAX_SIZE) out_of_memory();
                Rijndael_funtype_8_hashentry_t * new_data = (Rijndael_funtype_8_hashentry_t *)safe_malloc(new_size * sizeof(struct Rijndael_funtype_8_hashentry_s));
                for (uint32_t j = 0; j < new_size; j++){
                        new_data[j].key = 0;
                        new_data[j].keyhash = 0;}
                for (uint32_t j = 0; j < size; j++){//transfer entries
                        uint32_t keyhash = data[j].keyhash;
                        bool_t keyzero;
                        keyzero = (data[j].key == 0);
                        if (!keyzero || keyhash != 0){
                                uint32_t new_loc = keyhash ^ new_mask;
                                keyzero = (new_data[new_loc].key == 0);
                                while (keyzero && new_data[new_loc].keyhash == 0){
                                        new_loc++;
                                        new_loc = new_loc ^ new_mask;

                                        keyzero = (new_data[new_loc].key == 0);
                                }
                                new_data[new_loc].key = (uint8_t)data[j].key;
                                new_data[new_loc].keyhash = keyhash;
                                new_data[new_loc].value = (uint8_t)data[j].value;
                                }}
                htbl->size = new_size;
                htbl->num_entries = num_entries;
                htbl->data = new_data;
                safe_free(data);}
        uint32_t ihash = uint32_hash(i);
        uint32_t hashindex = lookup_Rijndael_funtype_8(htbl, i, ihash);
        Rijndael_funtype_8_hashentry_t hentry = htbl->data[hashindex];
        uint32_t hkeyhash = hentry.keyhash;
        bool_t hentrykeyzero;
        hentrykeyzero = (hentry.key == 0);

        if (hentrykeyzero && (hkeyhash == 0))
                {htbl->data[hashindex].key = (uint8_t)i; htbl->data[hashindex].keyhash = ihash; htbl->data[hashindex].value = (uint8_t)v; htbl->num_entries++;}
            else {uint8_t tempvalue;tempvalue = (uint8_t)htbl->data[hashindex].value;htbl->data[hashindex].value = (uint8_t)v;};
        return a;

}

Rijndael_funtype_8_t update_Rijndael_funtype_8(Rijndael_funtype_8_t a, uint8_t i, uint8_t v){
        if (a->count == 1){
                return dupdate_Rijndael_funtype_8(a, i, v);
            } else {
                Rijndael_funtype_8_t x = copy_Rijndael_funtype_8(a);
                a->count--;
                return dupdate_Rijndael_funtype_8(x, i, v);
            }}

bool_t equal_Rijndael_funtype_8(Rijndael_funtype_8_t x, Rijndael_funtype_8_t y){
        return false;}


uint8_t f_Rijndael_closure_9(struct Rijndael_closure_9_s * closure, uint8_t bvar){
if (closure->htbl != NULL){
        Rijndael_funtype_8_htbl_t htbl = closure->htbl;
        uint32_t hash = uint32_hash(bvar);
        uint32_t hashindex = lookup_Rijndael_funtype_8(htbl, bvar, hash);
        Rijndael_funtype_8_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         keyzero = (entry.key == 0);
        if (!keyzero || entry.keyhash != 0){
            uint8_t result;
            result = (uint8_t)entry.value;
            return result;}
        

        return h_Rijndael_closure_9(bvar, closure->fvar_1, closure->fvar_2);};

return h_Rijndael_closure_9(bvar, closure->fvar_1, closure->fvar_2);}

uint8_t m_Rijndael_closure_9(struct Rijndael_closure_9_s * closure, uint8_t bvar){
        return h_Rijndael_closure_9(bvar, closure->fvar_1, closure->fvar_2);}

extern uint8_t h_Rijndael_closure_9(uint8_t ivar_6, Rijndael_array_2_t ivar_2, uint8_t ivar_3){
        uint8_t result;
        bool_t ivar_7;
        uint8_t ivar_9;
        ivar_9 = (uint8_t)0;
        ivar_7 = (ivar_6 == ivar_9);
        if (ivar_7){ 
             uint8_t ivar_45;
             uint8_t ivar_42;
             Rijndael_funtype_1_t ivar_19;
             ivar_2->count++;
             ivar_19 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
             uint8_t ivar_24;
             ivar_24 = (uint8_t)0;
             uint8_t ivar_25;
             ivar_25 = (uint8_t)0;
             ivar_42 = (uint8_t)ivar_19->ftbl->mptr(ivar_19, ivar_24, ivar_25);
             ivar_19->ftbl->rptr(ivar_19);
             uint8_t ivar_43;
             uint8_t ivar_39;
             Rijndael_funtype_1_t ivar_31;
             ivar_2->count++;
             ivar_31 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
             uint8_t ivar_36;
             ivar_36 = (uint8_t)1;
             uint8_t ivar_37;
             ivar_37 = (uint8_t)3;
             ivar_39 = (uint8_t)ivar_31->ftbl->mptr(ivar_31, ivar_36, ivar_37);
             ivar_31->ftbl->rptr(ivar_31);
             Rijndael_array_2_t ivar_40;
             ivar_40 = (Rijndael_array_2_t)Rijndael__Sbox();
             if (ivar_40 != NULL) ivar_40->count++;
             ivar_43 = (uint8_t)ivar_40->elems[ivar_39];
             release_Rijndael_array_2(ivar_40);
             ivar_45 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_42, (uint8_t)ivar_43);
             result = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_45, (uint8_t)ivar_3);
} else {
        
             uint8_t ivar_82;
             Rijndael_funtype_1_t ivar_53;
             ivar_2->count++;
             ivar_53 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
             uint8_t ivar_59;
             ivar_59 = (uint8_t)0;
             ivar_82 = (uint8_t)ivar_53->ftbl->mptr(ivar_53, ivar_6, ivar_59);
             ivar_53->ftbl->rptr(ivar_53);
             uint8_t ivar_83;
             uint8_t ivar_79;
             Rijndael_funtype_1_t ivar_71;
             ivar_2->count++;
             ivar_71 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
             uint8_t ivar_76;
             uint8_t ivar_63;
             uint8_t ivar_66;
             ivar_66 = (uint8_t)1;
             ivar_63 = (uint8_t)(ivar_6 + ivar_66);
             uint8_t ivar_64;
             ivar_64 = (uint8_t)4;
             ivar_76 = (uint8_t)rem_uint32_uint32(ivar_63, ivar_64);
             uint8_t ivar_77;
             ivar_77 = (uint8_t)3;
             ivar_79 = (uint8_t)ivar_71->ftbl->mptr(ivar_71, ivar_76, ivar_77);
             ivar_71->ftbl->rptr(ivar_71);
             Rijndael_array_2_t ivar_80;
             ivar_80 = (Rijndael_array_2_t)Rijndael__Sbox();
             if (ivar_80 != NULL) ivar_80->count++;
             ivar_83 = (uint8_t)ivar_80->elems[ivar_79];
             release_Rijndael_array_2(ivar_80);
             result = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_82, (uint8_t)ivar_83);
};

        return result;
}

Rijndael_closure_9_t new_Rijndael_closure_9(void){
        static struct Rijndael_funtype_8_ftbl_s ftbl = {.fptr = (uint8_t (*)(Rijndael_funtype_8_t, uint8_t))&f_Rijndael_closure_9, .mptr = (uint8_t (*)(Rijndael_funtype_8_t, uint8_t))&m_Rijndael_closure_9, .rptr =  (void (*)(Rijndael_funtype_8_t))&release_Rijndael_closure_9, .cptr = (Rijndael_funtype_8_t (*)(Rijndael_funtype_8_t))&copy_Rijndael_closure_9};
        Rijndael_closure_9_t tmp = (Rijndael_closure_9_t) safe_malloc(sizeof(struct Rijndael_closure_9_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_Rijndael_closure_9(Rijndael_funtype_8_t closure){
        Rijndael_closure_9_t x = (Rijndael_closure_9_t)closure;
        x->count--;
        if (x->count <= 0){
         release_Rijndael_array_2(x->fvar_1);
        //printf("\nFreeing\n");
        safe_free(x);}}

Rijndael_closure_9_t copy_Rijndael_closure_9(Rijndael_closure_9_t x){
        Rijndael_closure_9_t y = new_Rijndael_closure_9();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = (uint8_t)x->fvar_2;
        if (x->htbl != NULL){
            Rijndael_funtype_8_htbl_t new_htbl = (Rijndael_funtype_8_htbl_t) safe_malloc(sizeof(struct Rijndael_funtype_8_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            Rijndael_funtype_8_hashentry_t * new_data = (Rijndael_funtype_8_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct Rijndael_funtype_8_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct Rijndael_funtype_8_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


uint8_t f_Rijndael_closure_10(struct Rijndael_closure_10_s * closure, uint8_t bvar){
if (closure->htbl != NULL){
        Rijndael_funtype_8_htbl_t htbl = closure->htbl;
        uint32_t hash = uint32_hash(bvar);
        uint32_t hashindex = lookup_Rijndael_funtype_8(htbl, bvar, hash);
        Rijndael_funtype_8_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         keyzero = (entry.key == 0);
        if (!keyzero || entry.keyhash != 0){
            uint8_t result;
            result = (uint8_t)entry.value;
            return result;}
        

        return h_Rijndael_closure_10(bvar, closure->fvar_1, closure->fvar_2);};

return h_Rijndael_closure_10(bvar, closure->fvar_1, closure->fvar_2);}

uint8_t m_Rijndael_closure_10(struct Rijndael_closure_10_s * closure, uint8_t bvar){
        return h_Rijndael_closure_10(bvar, closure->fvar_1, closure->fvar_2);}

extern uint8_t h_Rijndael_closure_10(uint8_t ivar_86, Rijndael_array_2_t ivar_2, Rijndael_array_2_t ivar_4){
        uint8_t result;
        uint8_t ivar_105;
        Rijndael_funtype_1_t ivar_93;
        ivar_2->count++;
        ivar_93 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
        uint8_t ivar_99;
        ivar_99 = (uint8_t)1;
        ivar_105 = (uint8_t)ivar_93->ftbl->mptr(ivar_93, ivar_86, ivar_99);
        ivar_93->ftbl->rptr(ivar_93);
        uint8_t ivar_106;
        ivar_106 = (uint8_t)ivar_4->elems[ivar_86];
        result = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_105, (uint8_t)ivar_106);

        return result;
}

Rijndael_closure_10_t new_Rijndael_closure_10(void){
        static struct Rijndael_funtype_8_ftbl_s ftbl = {.fptr = (uint8_t (*)(Rijndael_funtype_8_t, uint8_t))&f_Rijndael_closure_10, .mptr = (uint8_t (*)(Rijndael_funtype_8_t, uint8_t))&m_Rijndael_closure_10, .rptr =  (void (*)(Rijndael_funtype_8_t))&release_Rijndael_closure_10, .cptr = (Rijndael_funtype_8_t (*)(Rijndael_funtype_8_t))&copy_Rijndael_closure_10};
        Rijndael_closure_10_t tmp = (Rijndael_closure_10_t) safe_malloc(sizeof(struct Rijndael_closure_10_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_Rijndael_closure_10(Rijndael_funtype_8_t closure){
        Rijndael_closure_10_t x = (Rijndael_closure_10_t)closure;
        x->count--;
        if (x->count <= 0){
         release_Rijndael_array_2(x->fvar_1);
         release_Rijndael_array_2(x->fvar_2);
        //printf("\nFreeing\n");
        safe_free(x);}}

Rijndael_closure_10_t copy_Rijndael_closure_10(Rijndael_closure_10_t x){
        Rijndael_closure_10_t y = new_Rijndael_closure_10();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        if (x->htbl != NULL){
            Rijndael_funtype_8_htbl_t new_htbl = (Rijndael_funtype_8_htbl_t) safe_malloc(sizeof(struct Rijndael_funtype_8_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            Rijndael_funtype_8_hashentry_t * new_data = (Rijndael_funtype_8_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct Rijndael_funtype_8_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct Rijndael_funtype_8_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


uint8_t f_Rijndael_closure_11(struct Rijndael_closure_11_s * closure, uint8_t bvar){
if (closure->htbl != NULL){
        Rijndael_funtype_8_htbl_t htbl = closure->htbl;
        uint32_t hash = uint32_hash(bvar);
        uint32_t hashindex = lookup_Rijndael_funtype_8(htbl, bvar, hash);
        Rijndael_funtype_8_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         keyzero = (entry.key == 0);
        if (!keyzero || entry.keyhash != 0){
            uint8_t result;
            result = (uint8_t)entry.value;
            return result;}
        

        return h_Rijndael_closure_11(bvar, closure->fvar_1, closure->fvar_2);};

return h_Rijndael_closure_11(bvar, closure->fvar_1, closure->fvar_2);}

uint8_t m_Rijndael_closure_11(struct Rijndael_closure_11_s * closure, uint8_t bvar){
        return h_Rijndael_closure_11(bvar, closure->fvar_1, closure->fvar_2);}

extern uint8_t h_Rijndael_closure_11(uint8_t ivar_109, Rijndael_array_2_t ivar_2, Rijndael_array_2_t ivar_84){
        uint8_t result;
        uint8_t ivar_128;
        Rijndael_funtype_1_t ivar_116;
        ivar_2->count++;
        ivar_116 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
        uint8_t ivar_122;
        ivar_122 = (uint8_t)2;
        ivar_128 = (uint8_t)ivar_116->ftbl->mptr(ivar_116, ivar_109, ivar_122);
        ivar_116->ftbl->rptr(ivar_116);
        uint8_t ivar_129;
        ivar_129 = (uint8_t)ivar_84->elems[ivar_109];
        result = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_128, (uint8_t)ivar_129);

        return result;
}

Rijndael_closure_11_t new_Rijndael_closure_11(void){
        static struct Rijndael_funtype_8_ftbl_s ftbl = {.fptr = (uint8_t (*)(Rijndael_funtype_8_t, uint8_t))&f_Rijndael_closure_11, .mptr = (uint8_t (*)(Rijndael_funtype_8_t, uint8_t))&m_Rijndael_closure_11, .rptr =  (void (*)(Rijndael_funtype_8_t))&release_Rijndael_closure_11, .cptr = (Rijndael_funtype_8_t (*)(Rijndael_funtype_8_t))&copy_Rijndael_closure_11};
        Rijndael_closure_11_t tmp = (Rijndael_closure_11_t) safe_malloc(sizeof(struct Rijndael_closure_11_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_Rijndael_closure_11(Rijndael_funtype_8_t closure){
        Rijndael_closure_11_t x = (Rijndael_closure_11_t)closure;
        x->count--;
        if (x->count <= 0){
         release_Rijndael_array_2(x->fvar_1);
         release_Rijndael_array_2(x->fvar_2);
        //printf("\nFreeing\n");
        safe_free(x);}}

Rijndael_closure_11_t copy_Rijndael_closure_11(Rijndael_closure_11_t x){
        Rijndael_closure_11_t y = new_Rijndael_closure_11();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        if (x->htbl != NULL){
            Rijndael_funtype_8_htbl_t new_htbl = (Rijndael_funtype_8_htbl_t) safe_malloc(sizeof(struct Rijndael_funtype_8_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            Rijndael_funtype_8_hashentry_t * new_data = (Rijndael_funtype_8_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct Rijndael_funtype_8_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct Rijndael_funtype_8_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


uint8_t f_Rijndael_closure_12(struct Rijndael_closure_12_s * closure, uint8_t bvar){
if (closure->htbl != NULL){
        Rijndael_funtype_8_htbl_t htbl = closure->htbl;
        uint32_t hash = uint32_hash(bvar);
        uint32_t hashindex = lookup_Rijndael_funtype_8(htbl, bvar, hash);
        Rijndael_funtype_8_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         keyzero = (entry.key == 0);
        if (!keyzero || entry.keyhash != 0){
            uint8_t result;
            result = (uint8_t)entry.value;
            return result;}
        

        return h_Rijndael_closure_12(bvar, closure->fvar_1, closure->fvar_2);};

return h_Rijndael_closure_12(bvar, closure->fvar_1, closure->fvar_2);}

uint8_t m_Rijndael_closure_12(struct Rijndael_closure_12_s * closure, uint8_t bvar){
        return h_Rijndael_closure_12(bvar, closure->fvar_1, closure->fvar_2);}

extern uint8_t h_Rijndael_closure_12(uint8_t ivar_132, Rijndael_array_2_t ivar_2, Rijndael_array_2_t ivar_107){
        uint8_t result;
        uint8_t ivar_151;
        Rijndael_funtype_1_t ivar_139;
        ivar_2->count++;
        ivar_139 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
        uint8_t ivar_145;
        ivar_145 = (uint8_t)3;
        ivar_151 = (uint8_t)ivar_139->ftbl->mptr(ivar_139, ivar_132, ivar_145);
        ivar_139->ftbl->rptr(ivar_139);
        uint8_t ivar_152;
        ivar_152 = (uint8_t)ivar_107->elems[ivar_132];
        result = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_151, (uint8_t)ivar_152);

        return result;
}

Rijndael_closure_12_t new_Rijndael_closure_12(void){
        static struct Rijndael_funtype_8_ftbl_s ftbl = {.fptr = (uint8_t (*)(Rijndael_funtype_8_t, uint8_t))&f_Rijndael_closure_12, .mptr = (uint8_t (*)(Rijndael_funtype_8_t, uint8_t))&m_Rijndael_closure_12, .rptr =  (void (*)(Rijndael_funtype_8_t))&release_Rijndael_closure_12, .cptr = (Rijndael_funtype_8_t (*)(Rijndael_funtype_8_t))&copy_Rijndael_closure_12};
        Rijndael_closure_12_t tmp = (Rijndael_closure_12_t) safe_malloc(sizeof(struct Rijndael_closure_12_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_Rijndael_closure_12(Rijndael_funtype_8_t closure){
        Rijndael_closure_12_t x = (Rijndael_closure_12_t)closure;
        x->count--;
        if (x->count <= 0){
         release_Rijndael_array_2(x->fvar_1);
         release_Rijndael_array_2(x->fvar_2);
        //printf("\nFreeing\n");
        safe_free(x);}}

Rijndael_closure_12_t copy_Rijndael_closure_12(Rijndael_closure_12_t x){
        Rijndael_closure_12_t y = new_Rijndael_closure_12();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        if (x->htbl != NULL){
            Rijndael_funtype_8_htbl_t new_htbl = (Rijndael_funtype_8_htbl_t) safe_malloc(sizeof(struct Rijndael_funtype_8_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            Rijndael_funtype_8_hashentry_t * new_data = (Rijndael_funtype_8_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct Rijndael_funtype_8_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct Rijndael_funtype_8_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


Rijndael_array_13_t new_Rijndael_array_13(uint32_t size){
        Rijndael_array_13_t tmp = (Rijndael_array_13_t) safe_malloc(sizeof(struct Rijndael_array_13_s) + (size * sizeof(Rijndael_array_2_t)));
        tmp->count = 1;
        tmp->size = size;
        tmp->max = size;
        return tmp;}

void release_Rijndael_array_13(Rijndael_array_13_t x){
        x->count--;
        if (x->count <= 0){
                for (int i = 0; i < x->size; i++){release_Rijndael_array_2(x->elems[i]);};
        //printf("\nFreeing\n");
        safe_free(x);}
}

void release_Rijndael_array_13_ptr(pointer_t x, type_actual_t T){
        release_Rijndael_array_13((Rijndael_array_13_t)x);
}

Rijndael_array_13_t copy_Rijndael_array_13(Rijndael_array_13_t x){
        Rijndael_array_13_t tmp = new_Rijndael_array_13(x->size);
        tmp->count = 1;
        for (uint32_t i = 0; i < x->size; i++){tmp->elems[i] = x->elems[i];
                x->elems[i]->count++;};
         return tmp;}

bool_t equal_Rijndael_array_13(Rijndael_array_13_t x, Rijndael_array_13_t y){
        bool_t tmp = true;
        uint32_t i = 0;
        while (i < x->size && tmp){tmp = equal_Rijndael_array_2(x->elems[i], y->elems[i]);};
        return tmp;}

bool_t equal_Rijndael_array_13_ptr(pointer_t x, pointer_t y, type_actual_t T){
        return equal_Rijndael_array_13((Rijndael_array_13_t)x, (Rijndael_array_13_t)y);
}

actual_Rijndael_array_13_t actual_Rijndael_array_13(){
        actual_Rijndael_array_13_t new = (actual_Rijndael_array_13_t)safe_malloc(sizeof(struct actual_Rijndael_array_13_s));
        new->equal_ptr = (equal_ptr_t)(*equal_Rijndael_array_13_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_Rijndael_array_13_ptr);
 

 
        return new;
 };

Rijndael_array_13_t update_Rijndael_array_13(Rijndael_array_13_t x, uint32_t i, Rijndael_array_2_t v){
         Rijndael_array_13_t y;
         if (x->count == 1){y = x;}
                 else {y = copy_Rijndael_array_13(x);
                      x->count--;};
        Rijndael_array_2_t * yelems = y->elems;
        if (v != NULL){v->count++;}
        if (yelems[i] != NULL){release_Rijndael_array_2(yelems[i]);};
         yelems[i] = v;
         return y;}

Rijndael_array_13_t upgrade_Rijndael_array_13(Rijndael_array_13_t x, uint32_t i, Rijndael_array_2_t v){
         Rijndael_array_13_t y;
         if (x->count == 1 && i < x->max){y = x;}
                 else if (i > x->max){uint32_t newmax = x->max <= UINT32_MAX/2 ? 2*x->max: UINT32_MAX;
                y = safe_realloc(x, sizeof(struct Rijndael_array_13_s) + (newmax * sizeof(Rijndael_array_2_t)));
                y->count = 1;
                y->size = i+1;
                y->max = newmax;
                release_Rijndael_array_13(x);} else {y = copy_Rijndael_array_13(x);
                      x->count--;};
        Rijndael_array_2_t * yelems = y->elems;
        if (v != NULL){v->count++;}
        if (yelems[i] != NULL){release_Rijndael_array_2(yelems[i]);};
         yelems[i] = v;
         return y;}




Rijndael_record_14_t new_Rijndael_record_14(void){
        Rijndael_record_14_t tmp = (Rijndael_record_14_t) safe_malloc(sizeof(struct Rijndael_record_14_s));
        tmp->count = 1;
        return tmp;}

void release_Rijndael_record_14(Rijndael_record_14_t x){
        x->count--;
        if (x->count <= 0){
         release_Rijndael_array_2(x->seq);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_Rijndael_record_14_ptr(pointer_t x, type_actual_t T){
        release_Rijndael_record_14((Rijndael_record_14_t)x);
}

Rijndael_record_14_t copy_Rijndael_record_14(Rijndael_record_14_t x){
        Rijndael_record_14_t y = new_Rijndael_record_14();
        y->length = (uint8_t)x->length;
        y->seq = x->seq;
        if (y->seq != NULL){y->seq->count++;};
        y->count = 1;
        return y;}

bool_t equal_Rijndael_record_14(Rijndael_record_14_t x, Rijndael_record_14_t y){
        bool_t tmp = true;
        tmp = tmp && x->length == y->length;
        tmp = tmp && equal_Rijndael_array_2(x->seq, y->seq);
        return tmp;}

bool_t equal_Rijndael_record_14_ptr(pointer_t x, pointer_t y, actual_Rijndael_record_14_t T){
        return equal_Rijndael_record_14((Rijndael_record_14_t)x, (Rijndael_record_14_t)y);
}

actual_Rijndael_record_14_t actual_Rijndael_record_14(){
        actual_Rijndael_record_14_t new = (actual_Rijndael_record_14_t)safe_malloc(sizeof(struct actual_Rijndael_record_14_s));
        new->equal_ptr = (equal_ptr_t)(*equal_Rijndael_record_14_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_Rijndael_record_14_ptr);
 

 
        return new;
 };

Rijndael_record_14_t update_Rijndael_record_14_length(Rijndael_record_14_t x, uint8_t v){
        Rijndael_record_14_t y;
        if (x->count == 1){y = x;}
        else {y = copy_Rijndael_record_14(x); x->count--;};
        y->length = (uint8_t)v;
        return y;}

Rijndael_record_14_t update_Rijndael_record_14_seq(Rijndael_record_14_t x, Rijndael_array_2_t v){
        Rijndael_record_14_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->seq != NULL){release_Rijndael_array_2(x->seq);};}
        else {y = copy_Rijndael_record_14(x); x->count--; y->seq->count--;};
        y->seq = (Rijndael_array_2_t)v;
        return y;}




Rijndael_record_15_t new_Rijndael_record_15(void){
        Rijndael_record_15_t tmp = (Rijndael_record_15_t) safe_malloc(sizeof(struct Rijndael_record_15_s));
        tmp->count = 1;
        return tmp;}

void release_Rijndael_record_15(Rijndael_record_15_t x){
        x->count--;
        if (x->count <= 0){
         release_Rijndael_array_2(x->seq);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_Rijndael_record_15_ptr(pointer_t x, type_actual_t T){
        release_Rijndael_record_15((Rijndael_record_15_t)x);
}

Rijndael_record_15_t copy_Rijndael_record_15(Rijndael_record_15_t x){
        Rijndael_record_15_t y = new_Rijndael_record_15();
        y->length = (uint32_t)x->length;
        y->seq = x->seq;
        if (y->seq != NULL){y->seq->count++;};
        y->count = 1;
        return y;}

bool_t equal_Rijndael_record_15(Rijndael_record_15_t x, Rijndael_record_15_t y){
        bool_t tmp = true;
        tmp = tmp && x->length == y->length;
        tmp = tmp && equal_Rijndael_array_2(x->seq, y->seq);
        return tmp;}

bool_t equal_Rijndael_record_15_ptr(pointer_t x, pointer_t y, actual_Rijndael_record_15_t T){
        return equal_Rijndael_record_15((Rijndael_record_15_t)x, (Rijndael_record_15_t)y);
}

actual_Rijndael_record_15_t actual_Rijndael_record_15(){
        actual_Rijndael_record_15_t new = (actual_Rijndael_record_15_t)safe_malloc(sizeof(struct actual_Rijndael_record_15_s));
        new->equal_ptr = (equal_ptr_t)(*equal_Rijndael_record_15_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_Rijndael_record_15_ptr);
 

 
        return new;
 };

Rijndael_record_15_t update_Rijndael_record_15_length(Rijndael_record_15_t x, uint32_t v){
        Rijndael_record_15_t y;
        if (x->count == 1){y = x;}
        else {y = copy_Rijndael_record_15(x); x->count--;};
        y->length = (uint32_t)v;
        return y;}

Rijndael_record_15_t update_Rijndael_record_15_seq(Rijndael_record_15_t x, Rijndael_array_2_t v){
        Rijndael_record_15_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->seq != NULL){release_Rijndael_array_2(x->seq);};}
        else {y = copy_Rijndael_record_15(x); x->count--; y->seq->count--;};
        y->seq = (Rijndael_array_2_t)v;
        return y;}



extern Rijndael_funtype_1_t Rijndael__get(Rijndael_array_2_t ivar_3){
        Rijndael_funtype_1_t  result;
        Rijndael_closure_3_t cl15874;
        cl15874 = new_Rijndael_closure_3();
        cl15874->fvar_1 = (Rijndael_array_2_t)ivar_3;
        if (cl15874->fvar_1 != NULL) cl15874->fvar_1->count++;
        release_Rijndael_array_2(ivar_3);
        result = (Rijndael_funtype_1_t)cl15874;

        
        return result;
}

extern Rijndael_funtype_6_t Rijndael__every(mpz_ptr_t ivar_1){
        Rijndael_funtype_6_t  result;
        Rijndael_closure_7_t cl15891;
        cl15891 = new_Rijndael_closure_7();
        mpz_set(cl15891->fvar_1, ivar_1);
        result = (Rijndael_funtype_6_t)cl15891;

        
        return result;
}

extern bytestrings__bytestring_t Rijndael__SboxHex(void){
        bytestrings__bytestring_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    strings__string_t ivar_4;
        uint32_t len15894 = 512;
        uint32_t characters15895[512] = {54, 51, 55, 99, 55, 55, 55, 98, 102, 50, 54, 98, 54, 102, 99, 53, 51, 48, 48, 49, 54, 55, 50, 98, 102, 101, 100, 55, 97, 98, 55, 54, 99, 97, 56, 50, 99, 57, 55, 100, 102, 97, 53, 57, 52, 55, 102, 48, 97, 100, 100, 52, 97, 50, 97, 102, 57, 99, 97, 52, 55, 50, 99, 48, 98, 55, 102, 100, 57, 51, 50, 54, 51, 54, 51, 102, 102, 55, 99, 99, 51, 52, 97, 53, 101, 53, 102, 49, 55, 49, 100, 56, 51, 49, 49, 53, 48, 52, 99, 55, 50, 51, 99, 51, 49, 56, 57, 54, 48, 53, 57, 97, 48, 55, 49, 50, 56, 48, 101, 50, 101, 98, 50, 55, 98, 50, 55, 53, 48, 57, 56, 51, 50, 99, 49, 97, 49, 98, 54, 101, 53, 97, 97, 48, 53, 50, 51, 98, 100, 54, 98, 51, 50, 57, 101, 51, 50, 102, 56, 52, 53, 51, 100, 49, 48, 48, 101, 100, 50, 48, 102, 99, 98, 49, 53, 98, 54, 97, 99, 98, 98, 101, 51, 57, 52, 97, 52, 99, 53, 56, 99, 102, 100, 48, 101, 102, 97, 97, 102, 98, 52, 51, 52, 100, 51, 51, 56, 53, 52, 53, 102, 57, 48, 50, 55, 102, 53, 48, 51, 99, 57, 102, 97, 56, 53, 49, 97, 51, 52, 48, 56, 102, 57, 50, 57, 100, 51, 56, 102, 53, 98, 99, 98, 54, 100, 97, 50, 49, 49, 48, 102, 102, 102, 51, 100, 50, 99, 100, 48, 99, 49, 51, 101, 99, 53, 102, 57, 55, 52, 52, 49, 55, 99, 52, 97, 55, 55, 101, 51, 100, 54, 52, 53, 100, 49, 57, 55, 51, 54, 48, 56, 49, 52, 102, 100, 99, 50, 50, 50, 97, 57, 48, 56, 56, 52, 54, 101, 101, 98, 56, 49, 52, 100, 101, 53, 101, 48, 98, 100, 98, 101, 48, 51, 50, 51, 97, 48, 97, 52, 57, 48, 54, 50, 52, 53, 99, 99, 50, 100, 51, 97, 99, 54, 50, 57, 49, 57, 53, 101, 52, 55, 57, 101, 55, 99, 56, 51, 55, 54, 100, 56, 100, 100, 53, 52, 101, 97, 57, 54, 99, 53, 54, 102, 52, 101, 97, 54, 53, 55, 97, 97, 101, 48, 56, 98, 97, 55, 56, 50, 53, 50, 101, 49, 99, 97, 54, 98, 52, 99, 54, 101, 56, 100, 100, 55, 52, 49, 102, 52, 98, 98, 100, 56, 98, 56, 97, 55, 48, 51, 101, 98, 53, 54, 54, 52, 56, 48, 51, 102, 54, 48, 101, 54, 49, 51, 53, 53, 55, 98, 57, 56, 54, 99, 49, 49, 100, 57, 101, 101, 49, 102, 56, 57, 56, 49, 49, 54, 57, 100, 57, 56, 101, 57, 52, 57, 98, 49, 101, 56, 55, 101, 57, 99, 101, 53, 53, 50, 56, 100, 102, 56, 99, 97, 49, 56, 57, 48, 100, 98, 102, 101, 54, 52, 50, 54, 56, 52, 49, 57, 57, 50, 100, 48, 102, 98, 48, 53, 52, 98, 98, 49, 54};
        stringliteral_t string15893 = mk_string(512, characters15895);
        ivar_4 = (strings__string_t)strings__make_string(len15894, string15893);
        result = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_4);

        defined = true;};
        
        return result;
}

extern Rijndael_array_2_t Rijndael__Sbox(void){
        Rijndael_array_2_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    /* X */ bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_4;
        ivar_4 = (bytestrings__bytestring_t)Rijndael__SboxHex();
        if (ivar_4 != NULL) ivar_4->count++;
        ivar_1 = (bytestrings__bytestring_t)hex__hex2bytestring((bytestrings__bytestring_t)ivar_4);
        result = (Rijndael_array_2_t)ivar_1->seq;
        result->count++;
        release_bytestrings__bytestring(ivar_1);

        defined = true;};
        
        return result;
}

extern Rijndael_array_2_t Rijndael__byteSubst(Rijndael_array_2_t ivar_2){
        Rijndael_array_2_t  result;
        result = new_Rijndael_array_2(16);
        uint8_t ivar_3;
        for (uint32_t index15896 = 0; index15896 < 16; index15896++){
             ivar_3 = (uint8_t)index15896;
             uint8_t ivar_10;
             ivar_10 = (uint8_t)ivar_2->elems[ivar_3];
             Rijndael_array_2_t ivar_11;
             ivar_11 = (Rijndael_array_2_t)Rijndael__Sbox();
             if (ivar_11 != NULL) ivar_11->count++;
             result->elems[index15896] = (uint8_t)ivar_11->elems[ivar_10];
             release_Rijndael_array_2(ivar_11);
        };
        release_Rijndael_array_2(ivar_2);

        
        return result;
}

extern Rijndael_array_2_t Rijndael__shiftRow(Rijndael_array_2_t ivar_2){
        Rijndael_array_2_t  result;
        result = new_Rijndael_array_2(16);
        uint8_t ivar_3;
        for (uint32_t index15897 = 0; index15897 < 16; index15897++){
             ivar_3 = (uint8_t)index15897;
             /* i */ uint16_t ivar_4;
             uint16_t ivar_8;
             //copying to uint16 from uint8;
             ivar_8 = (uint16_t)ivar_3;
             uint8_t ivar_11;
             ivar_11 = (uint8_t)4;
             uint16_t ivar_9;
             //copying to uint16 from uint8;
             ivar_9 = (uint16_t)ivar_11;
             ivar_4 = (uint16_t)integertypes__u16rem((uint16_t)ivar_8, (uint16_t)ivar_9);
             /* j */ uint16_t ivar_12;
             uint16_t ivar_16;
             //copying to uint16 from uint8;
             ivar_16 = (uint16_t)ivar_3;
             uint8_t ivar_19;
             ivar_19 = (uint8_t)4;
             uint16_t ivar_17;
             //copying to uint16 from uint8;
             ivar_17 = (uint16_t)ivar_19;
             ivar_12 = (uint16_t)integertypes__u16div((uint16_t)ivar_16, (uint16_t)ivar_17);
             /* ij */ uint8_t ivar_20;
             ivar_20 = (uint8_t)(ivar_12 + ivar_4);
             /* l */ uint16_t ivar_24;
             uint16_t ivar_28;
             //copying to uint16 from uint8;
             ivar_28 = (uint16_t)ivar_20;
             uint8_t ivar_31;
             ivar_31 = (uint8_t)4;
             uint16_t ivar_29;
             //copying to uint16 from uint8;
             ivar_29 = (uint16_t)ivar_31;
             ivar_24 = (uint16_t)integertypes__u16rem((uint16_t)ivar_28, (uint16_t)ivar_29);
             Rijndael_funtype_1_t ivar_36;
             ivar_2->count++;
             ivar_36 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
             uint8_t ivar_41;
             //copying to uint8 from uint16;
             ivar_41 = (uint8_t)ivar_4;
             uint8_t ivar_42;
             //copying to uint8 from uint16;
             ivar_42 = (uint8_t)ivar_24;
             result->elems[index15897] = (uint8_t)ivar_36->ftbl->mptr(ivar_36, ivar_41, ivar_42);
             ivar_36->ftbl->rptr(ivar_36);
        };
        release_Rijndael_array_2(ivar_2);

        
        return result;
}

extern bool_t Rijndael__byte_msb(uint8_t ivar_1){
        bool_t  result;
        mpz_ptr_t ivar_2;
        uint8_t ivar_5;
        ivar_5 = (uint8_t)128;
        mpz_mk_set_ui(ivar_2, div_uint32_uint32(ivar_1, ivar_5));
        uint8_t ivar_3;
        ivar_3 = (uint8_t)0;
        int64_t tmp15898 = mpz_cmp_ui(ivar_2, ivar_3);
        result = (tmp15898 > 0);

        
        return result;
}

extern uint8_t Rijndael__T2(uint8_t ivar_2){
        uint8_t  result;
        bool_t ivar_3;
        bool_t ivar_4;
        ivar_4 = (bool_t)Rijndael__byte_msb((uint8_t)ivar_2);
        ivar_3 = !ivar_4;
        if (ivar_3){ 
             uint8_t ivar_13;
             ivar_13 = (uint8_t)1;
             result = (uint8_t)integertypes__u8lshift((uint8_t)ivar_2, (uint8_t)ivar_13);
} else {
        
             uint8_t ivar_22;
             uint8_t ivar_20;
             ivar_20 = (uint8_t)1;
             ivar_22 = (uint8_t)integertypes__u8lshift((uint8_t)ivar_2, (uint8_t)ivar_20);
             uint8_t ivar_23;
             ivar_23 = (uint8_t)27;
             result = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_22, (uint8_t)ivar_23);
};

        
        return result;
}

extern uint8_t Rijndael__T3(uint8_t ivar_2){
        uint8_t  result;
        uint8_t ivar_9;
        ivar_9 = (uint8_t)Rijndael__T2((uint8_t)ivar_2);
        result = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_9, (uint8_t)ivar_2);

        
        return result;
}

extern uint8_t Rijndael__timesConst(uint8_t ivar_2, uint8_t ivar_3){
        uint8_t  result;
        bool_t ivar_4;
        uint8_t ivar_6;
        ivar_6 = (uint8_t)0;
        ivar_4 = (ivar_2 == ivar_6);
        if (ivar_4){ 
             result = (uint8_t)0;
} else {
        
             bool_t ivar_8;
             uint8_t ivar_9;
             uint8_t ivar_15;
             ivar_15 = (uint8_t)2;
             ivar_9 = (uint8_t)integertypes__u8rem((uint8_t)ivar_2, (uint8_t)ivar_15);
             uint8_t ivar_10;
             ivar_10 = (uint8_t)1;
             ivar_8 = (ivar_9 == ivar_10);
             if (ivar_8){  
           uint8_t ivar_34;
           uint8_t ivar_30;
           uint8_t ivar_25;
           ivar_25 = (uint8_t)2;
           ivar_30 = (uint8_t)integertypes__u8div((uint8_t)ivar_2, (uint8_t)ivar_25);
           uint8_t ivar_31;
           ivar_31 = (uint8_t)Rijndael__T2((uint8_t)ivar_3);
           ivar_34 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_30, (uint8_t)ivar_31);
           result = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_3, (uint8_t)ivar_34);
} else {
             
           uint8_t ivar_46;
           uint8_t ivar_41;
           ivar_41 = (uint8_t)2;
           ivar_46 = (uint8_t)integertypes__u8div((uint8_t)ivar_2, (uint8_t)ivar_41);
           uint8_t ivar_47;
           ivar_47 = (uint8_t)Rijndael__T2((uint8_t)ivar_3);
           result = (uint8_t)Rijndael__timesConst((uint8_t)ivar_46, (uint8_t)ivar_47);
};
};

        
        return result;
}

extern Rijndael_array_2_t Rijndael__mixColumn(Rijndael_array_2_t ivar_2){
        Rijndael_array_2_t  result;
        result = new_Rijndael_array_2(16);
        uint8_t ivar_3;
        for (uint32_t index15899 = 0; index15899 < 16; index15899++){
             ivar_3 = (uint8_t)index15899;
             /* i */ uint16_t ivar_4;
             uint16_t ivar_8;
             //copying to uint16 from uint8;
             ivar_8 = (uint16_t)ivar_3;
             uint8_t ivar_11;
             ivar_11 = (uint8_t)4;
             uint16_t ivar_9;
             //copying to uint16 from uint8;
             ivar_9 = (uint16_t)ivar_11;
             ivar_4 = (uint16_t)integertypes__u16rem((uint16_t)ivar_8, (uint16_t)ivar_9);
             /* j */ uint16_t ivar_12;
             uint16_t ivar_16;
             //copying to uint16 from uint8;
             ivar_16 = (uint16_t)ivar_3;
             uint8_t ivar_19;
             ivar_19 = (uint8_t)4;
             uint16_t ivar_17;
             //copying to uint16 from uint8;
             ivar_17 = (uint16_t)ivar_19;
             ivar_12 = (uint16_t)integertypes__u16div((uint16_t)ivar_16, (uint16_t)ivar_17);
             bool_t ivar_20;
             uint8_t ivar_22;
             ivar_22 = (uint8_t)0;
             ivar_20 = (ivar_4 == ivar_22);
             if (ivar_20){  
           uint8_t ivar_87;
           uint8_t ivar_73;
           uint8_t ivar_59;
           uint8_t ivar_43;
           Rijndael_funtype_1_t ivar_35;
           ivar_2->count++;
           ivar_35 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_40;
           ivar_40 = (uint8_t)0;
           uint8_t ivar_41;
           //copying to uint8 from uint16;
           ivar_41 = (uint8_t)ivar_12;
           ivar_43 = (uint8_t)ivar_35->ftbl->mptr(ivar_35, ivar_40, ivar_41);
           ivar_35->ftbl->rptr(ivar_35);
           ivar_59 = (uint8_t)Rijndael__T2((uint8_t)ivar_43);
           uint8_t ivar_60;
           uint8_t ivar_57;
           Rijndael_funtype_1_t ivar_49;
           ivar_2->count++;
           ivar_49 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_54;
           ivar_54 = (uint8_t)1;
           uint8_t ivar_55;
           //copying to uint8 from uint16;
           ivar_55 = (uint8_t)ivar_12;
           ivar_57 = (uint8_t)ivar_49->ftbl->mptr(ivar_49, ivar_54, ivar_55);
           ivar_49->ftbl->rptr(ivar_49);
           ivar_60 = (uint8_t)Rijndael__T3((uint8_t)ivar_57);
           ivar_73 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_59, (uint8_t)ivar_60);
           uint8_t ivar_74;
           Rijndael_funtype_1_t ivar_65;
           ivar_2->count++;
           ivar_65 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_70;
           ivar_70 = (uint8_t)2;
           uint8_t ivar_71;
           //copying to uint8 from uint16;
           ivar_71 = (uint8_t)ivar_12;
           ivar_74 = (uint8_t)ivar_65->ftbl->mptr(ivar_65, ivar_70, ivar_71);
           ivar_65->ftbl->rptr(ivar_65);
           ivar_87 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_73, (uint8_t)ivar_74);
           uint8_t ivar_88;
           Rijndael_funtype_1_t ivar_79;
           ivar_2->count++;
           ivar_79 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_84;
           ivar_84 = (uint8_t)3;
           uint8_t ivar_85;
           //copying to uint8 from uint16;
           ivar_85 = (uint8_t)ivar_12;
           ivar_88 = (uint8_t)ivar_79->ftbl->mptr(ivar_79, ivar_84, ivar_85);
           ivar_79->ftbl->rptr(ivar_79);
           result->elems[index15899] = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_87, (uint8_t)ivar_88);
} else {
             
           bool_t ivar_89;
           uint8_t ivar_91;
           ivar_91 = (uint8_t)1;
           ivar_89 = (ivar_4 == ivar_91);
           if (ivar_89){   
           uint8_t ivar_156;
           uint8_t ivar_142;
           uint8_t ivar_125;
           Rijndael_funtype_1_t ivar_103;
           ivar_2->count++;
           ivar_103 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_108;
           ivar_108 = (uint8_t)0;
           uint8_t ivar_109;
           //copying to uint8 from uint16;
           ivar_109 = (uint8_t)ivar_12;
           ivar_125 = (uint8_t)ivar_103->ftbl->mptr(ivar_103, ivar_108, ivar_109);
           ivar_103->ftbl->rptr(ivar_103);
           uint8_t ivar_126;
           uint8_t ivar_123;
           Rijndael_funtype_1_t ivar_115;
           ivar_2->count++;
           ivar_115 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_120;
           ivar_120 = (uint8_t)1;
           uint8_t ivar_121;
           //copying to uint8 from uint16;
           ivar_121 = (uint8_t)ivar_12;
           ivar_123 = (uint8_t)ivar_115->ftbl->mptr(ivar_115, ivar_120, ivar_121);
           ivar_115->ftbl->rptr(ivar_115);
           ivar_126 = (uint8_t)Rijndael__T2((uint8_t)ivar_123);
           ivar_142 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_125, (uint8_t)ivar_126);
           uint8_t ivar_143;
           uint8_t ivar_140;
           Rijndael_funtype_1_t ivar_132;
           ivar_2->count++;
           ivar_132 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_137;
           ivar_137 = (uint8_t)2;
           uint8_t ivar_138;
           //copying to uint8 from uint16;
           ivar_138 = (uint8_t)ivar_12;
           ivar_140 = (uint8_t)ivar_132->ftbl->mptr(ivar_132, ivar_137, ivar_138);
           ivar_132->ftbl->rptr(ivar_132);
           ivar_143 = (uint8_t)Rijndael__T3((uint8_t)ivar_140);
           ivar_156 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_142, (uint8_t)ivar_143);
           uint8_t ivar_157;
           Rijndael_funtype_1_t ivar_148;
           ivar_2->count++;
           ivar_148 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_153;
           ivar_153 = (uint8_t)3;
           uint8_t ivar_154;
           //copying to uint8 from uint16;
           ivar_154 = (uint8_t)ivar_12;
           ivar_157 = (uint8_t)ivar_148->ftbl->mptr(ivar_148, ivar_153, ivar_154);
           ivar_148->ftbl->rptr(ivar_148);
           result->elems[index15899] = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_156, (uint8_t)ivar_157);
} else {
           
           bool_t ivar_158;
           uint8_t ivar_160;
           ivar_160 = (uint8_t)2;
           ivar_158 = (ivar_4 == ivar_160);
           if (ivar_158){    
            uint8_t ivar_225;
            uint8_t ivar_208;
            uint8_t ivar_191;
            Rijndael_funtype_1_t ivar_172;
            ivar_2->count++;
            ivar_172 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_177;
            ivar_177 = (uint8_t)0;
            uint8_t ivar_178;
            //copying to uint8 from uint16;
            ivar_178 = (uint8_t)ivar_12;
            ivar_191 = (uint8_t)ivar_172->ftbl->mptr(ivar_172, ivar_177, ivar_178);
            ivar_172->ftbl->rptr(ivar_172);
            uint8_t ivar_192;
            Rijndael_funtype_1_t ivar_183;
            ivar_2->count++;
            ivar_183 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_188;
            ivar_188 = (uint8_t)1;
            uint8_t ivar_189;
            //copying to uint8 from uint16;
            ivar_189 = (uint8_t)ivar_12;
            ivar_192 = (uint8_t)ivar_183->ftbl->mptr(ivar_183, ivar_188, ivar_189);
            ivar_183->ftbl->rptr(ivar_183);
            ivar_208 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_191, (uint8_t)ivar_192);
            uint8_t ivar_209;
            uint8_t ivar_206;
            Rijndael_funtype_1_t ivar_198;
            ivar_2->count++;
            ivar_198 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_203;
            ivar_203 = (uint8_t)2;
            uint8_t ivar_204;
            //copying to uint8 from uint16;
            ivar_204 = (uint8_t)ivar_12;
            ivar_206 = (uint8_t)ivar_198->ftbl->mptr(ivar_198, ivar_203, ivar_204);
            ivar_198->ftbl->rptr(ivar_198);
            ivar_209 = (uint8_t)Rijndael__T2((uint8_t)ivar_206);
            ivar_225 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_208, (uint8_t)ivar_209);
            uint8_t ivar_226;
            uint8_t ivar_223;
            Rijndael_funtype_1_t ivar_215;
            ivar_2->count++;
            ivar_215 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_220;
            ivar_220 = (uint8_t)3;
            uint8_t ivar_221;
            //copying to uint8 from uint16;
            ivar_221 = (uint8_t)ivar_12;
            ivar_223 = (uint8_t)ivar_215->ftbl->mptr(ivar_215, ivar_220, ivar_221);
            ivar_215->ftbl->rptr(ivar_215);
            ivar_226 = (uint8_t)Rijndael__T3((uint8_t)ivar_223);
            result->elems[index15899] = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_225, (uint8_t)ivar_226);
} else {
           
            uint8_t ivar_290;
            uint8_t ivar_273;
            uint8_t ivar_259;
            uint8_t ivar_246;
            Rijndael_funtype_1_t ivar_238;
            ivar_2->count++;
            ivar_238 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_243;
            ivar_243 = (uint8_t)0;
            uint8_t ivar_244;
            //copying to uint8 from uint16;
            ivar_244 = (uint8_t)ivar_12;
            ivar_246 = (uint8_t)ivar_238->ftbl->mptr(ivar_238, ivar_243, ivar_244);
            ivar_238->ftbl->rptr(ivar_238);
            ivar_259 = (uint8_t)Rijndael__T3((uint8_t)ivar_246);
            uint8_t ivar_260;
            Rijndael_funtype_1_t ivar_251;
            ivar_2->count++;
            ivar_251 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_256;
            ivar_256 = (uint8_t)1;
            uint8_t ivar_257;
            //copying to uint8 from uint16;
            ivar_257 = (uint8_t)ivar_12;
            ivar_260 = (uint8_t)ivar_251->ftbl->mptr(ivar_251, ivar_256, ivar_257);
            ivar_251->ftbl->rptr(ivar_251);
            ivar_273 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_259, (uint8_t)ivar_260);
            uint8_t ivar_274;
            Rijndael_funtype_1_t ivar_265;
            ivar_2->count++;
            ivar_265 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_270;
            ivar_270 = (uint8_t)2;
            uint8_t ivar_271;
            //copying to uint8 from uint16;
            ivar_271 = (uint8_t)ivar_12;
            ivar_274 = (uint8_t)ivar_265->ftbl->mptr(ivar_265, ivar_270, ivar_271);
            ivar_265->ftbl->rptr(ivar_265);
            ivar_290 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_273, (uint8_t)ivar_274);
            uint8_t ivar_291;
            uint8_t ivar_288;
            Rijndael_funtype_1_t ivar_280;
            ivar_2->count++;
            ivar_280 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_285;
            ivar_285 = (uint8_t)3;
            uint8_t ivar_286;
            //copying to uint8 from uint16;
            ivar_286 = (uint8_t)ivar_12;
            ivar_288 = (uint8_t)ivar_280->ftbl->mptr(ivar_280, ivar_285, ivar_286);
            ivar_280->ftbl->rptr(ivar_280);
            ivar_291 = (uint8_t)Rijndael__T2((uint8_t)ivar_288);
            result->elems[index15899] = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_290, (uint8_t)ivar_291);
};
};
};
        };
        release_Rijndael_array_2(ivar_2);

        
        return result;
}

extern Rijndael_array_2_t Rijndael__roundkeyXOR(Rijndael_array_2_t ivar_2, Rijndael_array_2_t ivar_3){
        Rijndael_array_2_t  result;
        uint8_t ivar_10;
        ivar_10 = (uint8_t)16;
        /* n */ uint32_t ivar_7;
        //copying to uint32 from uint8;
        ivar_7 = (uint32_t)ivar_10;
        result = (Rijndael_array_2_t)bytevectors__byvXOR((uint32_t)ivar_7, (bytevectors__byv_t)ivar_2, (bytevectors__byv_t)ivar_3);

        
        return result;
}

extern Rijndael_array_2_t Rijndael__nextRoundKey(Rijndael_array_2_t ivar_2, uint8_t ivar_3){
        Rijndael_array_2_t  result;
        Rijndael_funtype_8_t ivar_194;
        Rijndael_closure_9_t cl15900;
        cl15900 = new_Rijndael_closure_9();
        cl15900->fvar_1 = (Rijndael_array_2_t)ivar_2;
        if (cl15900->fvar_1 != NULL) cl15900->fvar_1->count++;
        cl15900->fvar_2 = (uint8_t)ivar_3;
        ivar_194 = (Rijndael_funtype_8_t)cl15900;
        /* K0 */ Rijndael_array_2_t ivar_4;
        //copying to Rijndael_array_2 from Rijndael_funtype_8;
        uint32_t tmp15901;
        tmp15901 = (uint32_t)4;
        ivar_4 = new_Rijndael_array_2(tmp15901);
        for (uint32_t index_195 = 0; index_195 < tmp15901; index_195++){
             ivar_4->elems[index_195] = (uint8_t)ivar_194->ftbl->fptr(ivar_194, index_195);
        };
        release_Rijndael_funtype_8(ivar_194);
        Rijndael_funtype_8_t ivar_193;
        Rijndael_closure_10_t cl15902;
        cl15902 = new_Rijndael_closure_10();
        cl15902->fvar_1 = (Rijndael_array_2_t)ivar_2;
        if (cl15902->fvar_1 != NULL) cl15902->fvar_1->count++;
        cl15902->fvar_2 = (Rijndael_array_2_t)ivar_4;
        if (cl15902->fvar_2 != NULL) cl15902->fvar_2->count++;
        ivar_193 = (Rijndael_funtype_8_t)cl15902;
        /* K1 */ Rijndael_array_2_t ivar_84;
        //copying to Rijndael_array_2 from Rijndael_funtype_8;
        uint32_t tmp15903;
        tmp15903 = (uint32_t)4;
        ivar_84 = new_Rijndael_array_2(tmp15903);
        for (uint32_t index_196 = 0; index_196 < tmp15903; index_196++){
             ivar_84->elems[index_196] = (uint8_t)ivar_193->ftbl->fptr(ivar_193, index_196);
        };
        release_Rijndael_funtype_8(ivar_193);
        Rijndael_funtype_8_t ivar_192;
        Rijndael_closure_11_t cl15904;
        cl15904 = new_Rijndael_closure_11();
        cl15904->fvar_1 = (Rijndael_array_2_t)ivar_2;
        if (cl15904->fvar_1 != NULL) cl15904->fvar_1->count++;
        cl15904->fvar_2 = (Rijndael_array_2_t)ivar_84;
        if (cl15904->fvar_2 != NULL) cl15904->fvar_2->count++;
        ivar_192 = (Rijndael_funtype_8_t)cl15904;
        /* K2 */ Rijndael_array_2_t ivar_107;
        //copying to Rijndael_array_2 from Rijndael_funtype_8;
        uint32_t tmp15905;
        tmp15905 = (uint32_t)4;
        ivar_107 = new_Rijndael_array_2(tmp15905);
        for (uint32_t index_197 = 0; index_197 < tmp15905; index_197++){
             ivar_107->elems[index_197] = (uint8_t)ivar_192->ftbl->fptr(ivar_192, index_197);
        };
        release_Rijndael_funtype_8(ivar_192);
        Rijndael_funtype_8_t ivar_191;
        Rijndael_closure_12_t cl15906;
        cl15906 = new_Rijndael_closure_12();
        cl15906->fvar_1 = (Rijndael_array_2_t)ivar_2;
        if (cl15906->fvar_1 != NULL) cl15906->fvar_1->count++;
        cl15906->fvar_2 = (Rijndael_array_2_t)ivar_107;
        if (cl15906->fvar_2 != NULL) cl15906->fvar_2->count++;
        release_Rijndael_array_2(ivar_2);
        ivar_191 = (Rijndael_funtype_8_t)cl15906;
        /* K3 */ Rijndael_array_2_t ivar_130;
        //copying to Rijndael_array_2 from Rijndael_funtype_8;
        uint32_t tmp15907;
        tmp15907 = (uint32_t)4;
        ivar_130 = new_Rijndael_array_2(tmp15907);
        for (uint32_t index_198 = 0; index_198 < tmp15907; index_198++){
             ivar_130->elems[index_198] = (uint8_t)ivar_191->ftbl->fptr(ivar_191, index_198);
        };
        release_Rijndael_funtype_8(ivar_191);
        result = new_Rijndael_array_2(16);
        uint8_t ivar_153;
        for (uint32_t index15908 = 0; index15908 < 16; index15908++){
             ivar_153 = (uint8_t)index15908;
             bool_t ivar_154;
             uint8_t ivar_156;
             ivar_156 = (uint8_t)4;
             ivar_154 = (ivar_153 < ivar_156);
             if (ivar_154){  
           result->elems[index15908] = (uint8_t)ivar_4->elems[ivar_153];
} else {
             
           bool_t ivar_162;
           uint8_t ivar_164;
           ivar_164 = (uint8_t)8;
           ivar_162 = (ivar_153 < ivar_164);
           if (ivar_162){   
           uint8_t ivar_172;
           uint8_t ivar_168;
           ivar_168 = (uint8_t)4;
           ivar_172 = (uint8_t)(ivar_153 - ivar_168);
           result->elems[index15908] = (uint8_t)ivar_84->elems[ivar_172];
} else {
           
           bool_t ivar_173;
           uint8_t ivar_175;
           ivar_175 = (uint8_t)12;
           ivar_173 = (ivar_153 < ivar_175);
           if (ivar_173){    
            uint8_t ivar_183;
            uint8_t ivar_179;
            ivar_179 = (uint8_t)8;
            ivar_183 = (uint8_t)(ivar_153 - ivar_179);
            result->elems[index15908] = (uint8_t)ivar_107->elems[ivar_183];
} else {
           
            uint8_t ivar_190;
            uint8_t ivar_186;
            ivar_186 = (uint8_t)12;
            ivar_190 = (uint8_t)(ivar_153 - ivar_186);
            result->elems[index15908] = (uint8_t)ivar_130->elems[ivar_190];
};
};
};
        };
        release_Rijndael_array_2(ivar_107);
        release_Rijndael_array_2(ivar_130);
        release_Rijndael_array_2(ivar_84);
        release_Rijndael_array_2(ivar_4);

        
        return result;
}

extern Rijndael_array_13_t Rijndael__allKeys(Rijndael_array_13_t ivar_2, uint8_t ivar_3, uint8_t ivar_4){
        Rijndael_array_13_t  result;
        bool_t ivar_5;
        uint8_t ivar_7;
        ivar_7 = (uint8_t)10;
        ivar_5 = (ivar_4 == ivar_7);
        if (ivar_5){ 
             //copying to Rijndael_array_13 from Rijndael_array_13;
             result = (Rijndael_array_13_t)ivar_2;
             if (result != NULL) result->count++;
             release_Rijndael_array_13(ivar_2);
} else {
        
             Rijndael_array_13_t ivar_39;
             Rijndael_array_2_t ivar_12;
             Rijndael_array_2_t ivar_20;
             ivar_20 = (Rijndael_array_2_t)ivar_2->elems[ivar_4];
             ivar_20->count++;
             ivar_12 = (Rijndael_array_2_t)Rijndael__nextRoundKey((Rijndael_array_2_t)ivar_20, (uint8_t)ivar_3);
             uint8_t ivar_24;
             uint8_t ivar_26;
             ivar_26 = (uint8_t)1;
             ivar_24 = (uint8_t)(ivar_4 + ivar_26);
             Rijndael_array_13_t ivar_28;
             Rijndael_array_2_t ivar_30;
             ivar_30 = NULL;
             ivar_28 = (Rijndael_array_13_t)update_Rijndael_array_13(ivar_2, ivar_24, ivar_30);
             if (ivar_30 != NULL) ivar_30->count--;
             ivar_39 = (Rijndael_array_13_t)update_Rijndael_array_13(ivar_28, ivar_24, ivar_12);
             if (ivar_12 != NULL) ivar_12->count--;
             uint8_t ivar_40;
             ivar_40 = (uint8_t)Rijndael__T2((uint8_t)ivar_3);
             uint8_t ivar_41;
             uint8_t ivar_36;
             ivar_36 = (uint8_t)1;
             ivar_41 = (uint8_t)(ivar_4 + ivar_36);
             result = (Rijndael_array_13_t)Rijndael__allKeys((Rijndael_array_13_t)ivar_39, (uint8_t)ivar_40, (uint8_t)ivar_41);
};

        
        return result;
}

extern Rijndael_array_2_t Rijndael__Rijndael_step(Rijndael_array_2_t ivar_2, Rijndael_array_2_t ivar_3){
        Rijndael_array_2_t  result;
        /* A1 */ Rijndael_array_2_t ivar_4;
        ivar_4 = (Rijndael_array_2_t)Rijndael__byteSubst((Rijndael_array_2_t)ivar_2);
        /* A2 */ Rijndael_array_2_t ivar_8;
        ivar_8 = (Rijndael_array_2_t)Rijndael__shiftRow((Rijndael_array_2_t)ivar_4);
        /* A3 */ Rijndael_array_2_t ivar_12;
        ivar_12 = (Rijndael_array_2_t)Rijndael__mixColumn((Rijndael_array_2_t)ivar_8);
        result = (Rijndael_array_2_t)Rijndael__roundkeyXOR((Rijndael_array_2_t)ivar_12, (Rijndael_array_2_t)ivar_3);

        
        return result;
}

extern Rijndael_array_2_t Rijndael__Rijndael_rec(Rijndael_array_2_t ivar_2, Rijndael_array_13_t ivar_3, uint8_t ivar_4){
        Rijndael_array_2_t  result;
        bool_t ivar_5;
        uint8_t ivar_7;
        ivar_7 = (uint8_t)10;
        ivar_5 = (ivar_4 >= ivar_7);
        if (ivar_5){ 
             Rijndael_array_2_t ivar_22;
             Rijndael_array_2_t ivar_16;
             ivar_16 = (Rijndael_array_2_t)Rijndael__byteSubst((Rijndael_array_2_t)ivar_2);
             ivar_22 = (Rijndael_array_2_t)Rijndael__shiftRow((Rijndael_array_2_t)ivar_16);
             Rijndael_array_2_t ivar_23;
             ivar_23 = (Rijndael_array_2_t)ivar_3->elems[ivar_4];
             ivar_23->count++;
             release_Rijndael_array_13(ivar_3);
             result = (Rijndael_array_2_t)Rijndael__roundkeyXOR((Rijndael_array_2_t)ivar_22, (Rijndael_array_2_t)ivar_23);
} else {
        
             bool_t ivar_24;
             uint8_t ivar_26;
             ivar_26 = (uint8_t)0;
             ivar_24 = (ivar_4 == ivar_26);
             if (ivar_24){  
           Rijndael_array_2_t ivar_44;
           Rijndael_array_2_t ivar_39;
           ivar_39 = (Rijndael_array_2_t)ivar_3->elems[ivar_4];
           ivar_39->count++;
           ivar_44 = (Rijndael_array_2_t)Rijndael__roundkeyXOR((Rijndael_array_2_t)ivar_2, (Rijndael_array_2_t)ivar_39);
           uint8_t ivar_46;
           uint8_t ivar_41;
           ivar_41 = (uint8_t)1;
           ivar_46 = (uint8_t)(ivar_4 + ivar_41);
           result = (Rijndael_array_2_t)Rijndael__Rijndael_rec((Rijndael_array_2_t)ivar_44, (Rijndael_array_13_t)ivar_3, (uint8_t)ivar_46);
} else {
             
           /* A4 */ Rijndael_array_2_t ivar_47;
           Rijndael_array_2_t ivar_56;
           ivar_56 = (Rijndael_array_2_t)ivar_3->elems[ivar_4];
           ivar_56->count++;
           ivar_47 = (Rijndael_array_2_t)Rijndael__Rijndael_step((Rijndael_array_2_t)ivar_2, (Rijndael_array_2_t)ivar_56);
           uint8_t ivar_66;
           uint8_t ivar_61;
           ivar_61 = (uint8_t)1;
           ivar_66 = (uint8_t)(ivar_4 + ivar_61);
           result = (Rijndael_array_2_t)Rijndael__Rijndael_rec((Rijndael_array_2_t)ivar_47, (Rijndael_array_13_t)ivar_3, (uint8_t)ivar_66);
};
};

        
        return result;
}

extern Rijndael_array_2_t Rijndael__Rijndael(Rijndael_array_2_t ivar_2, Rijndael_array_2_t ivar_3){
        Rijndael_array_2_t  result;
        Rijndael_array_13_t ivar_19;
        Rijndael_array_13_t ivar_14;
        ivar_14 = new_Rijndael_array_13(11);
        uint8_t ivar_10;
        for (uint32_t index15909 = 0; index15909 < 11; index15909++){
             ivar_10 = (uint8_t)index15909;
             //copying to Rijndael_array_2 from Rijndael_array_2;
             ivar_14->elems[index15909] = (Rijndael_array_2_t)ivar_3;
             if (ivar_14->elems[index15909] != NULL) ivar_14->elems[index15909]->count++;
        };
        release_Rijndael_array_2(ivar_3);
        uint8_t ivar_15;
        ivar_15 = (uint8_t)1;
        uint8_t ivar_16;
        ivar_16 = (uint8_t)0;
        ivar_19 = (Rijndael_array_13_t)Rijndael__allKeys((Rijndael_array_13_t)ivar_14, (uint8_t)ivar_15, (uint8_t)ivar_16);
        uint8_t ivar_20;
        ivar_20 = (uint8_t)0;
        result = (Rijndael_array_2_t)Rijndael__Rijndael_rec((Rijndael_array_2_t)ivar_2, (Rijndael_array_13_t)ivar_19, (uint8_t)ivar_20);

        
        return result;
}

extern bytestrings__bytestring_t Rijndael__hex16(Rijndael_array_2_t ivar_2){
        bytestrings__bytestring_t  result;
        Rijndael_record_14_t ivar_9;
        uint8_t ivar_4;
        ivar_4 = (uint8_t)16;
        Rijndael_record_14_t tmp15910 = new_Rijndael_record_14();;
        ivar_9 = (Rijndael_record_14_t)tmp15910;
        tmp15910->length = (uint8_t)ivar_4;
        tmp15910->seq = (Rijndael_array_2_t)ivar_2;
        bytestrings__bytestring_t ivar_7;
        //copying to bytestrings__bytestring from Rijndael_record_14;
        {
         ivar_7 = new_Rijndael_record_15();
         ivar_7->length = (uint32_t)ivar_9->length;
         ivar_7->seq = (Rijndael_array_2_t)ivar_9->seq;
         if (ivar_7->seq != NULL) ivar_7->seq->count++;
        };
        release_Rijndael_record_14(ivar_9);
        result = (bytestrings__bytestring_t)hex__bytestring2hexstring((bytestrings__bytestring_t)ivar_7);

        
        return result;
}

extern bytestrings__bytestring_t Rijndael__test0RD(void){
        bytestrings__bytestring_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    /* Input */ bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_8;
        strings__string_t ivar_6;
        uint32_t len15918 = 32;
        uint32_t characters15919[32] = {51, 50, 52, 51, 102, 54, 97, 56, 56, 56, 53, 97, 51, 48, 56, 100, 51, 49, 51, 49, 57, 56, 97, 50, 101, 48, 51, 55, 48, 55, 51, 52};
        stringliteral_t string15917 = mk_string(32, characters15919);
        ivar_6 = (strings__string_t)strings__make_string(len15918, string15917);
        ivar_8 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_6);
        ivar_1 = (bytestrings__bytestring_t)hex__hex2bytestring((bytestrings__bytestring_t)ivar_8);
        /* Cipher */ bytestrings__bytestring_t ivar_9;
        bytestrings__bytestring_t ivar_16;
        strings__string_t ivar_14;
        uint32_t len15921 = 32;
        uint32_t characters15922[32] = {50, 98, 55, 101, 49, 53, 49, 54, 50, 56, 97, 101, 100, 50, 97, 54, 97, 98, 102, 55, 49, 53, 56, 56, 48, 57, 99, 102, 52, 102, 51, 99};
        stringliteral_t string15920 = mk_string(32, characters15922);
        ivar_14 = (strings__string_t)strings__make_string(len15921, string15920);
        ivar_16 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_14);
        ivar_9 = (bytestrings__bytestring_t)hex__hex2bytestring((bytestrings__bytestring_t)ivar_16);
        /* Output */ Rijndael_array_2_t ivar_17;
        Rijndael_array_2_t ivar_27;
        ivar_27 = (Rijndael_array_2_t)ivar_1->seq;
        ivar_27->count++;
        release_bytestrings__bytestring(ivar_1);
        Rijndael_array_2_t ivar_28;
        ivar_28 = (Rijndael_array_2_t)ivar_9->seq;
        ivar_28->count++;
        release_bytestrings__bytestring(ivar_9);
        ivar_17 = (Rijndael_array_2_t)Rijndael__roundkeyXOR((Rijndael_array_2_t)ivar_27, (Rijndael_array_2_t)ivar_28);
        /* Outputbytestring */ Rijndael_record_14_t ivar_29;
        uint8_t ivar_30;
        ivar_30 = (uint8_t)16;
        Rijndael_record_14_t tmp15923 = new_Rijndael_record_14();;
        ivar_29 = (Rijndael_record_14_t)tmp15923;
        tmp15923->length = (uint8_t)ivar_30;
        tmp15923->seq = (Rijndael_array_2_t)ivar_17;
        bytestrings__bytestring_t ivar_34;
        //copying to bytestrings__bytestring from Rijndael_record_14;
        {
         ivar_34 = new_Rijndael_record_15();
         ivar_34->length = (uint32_t)ivar_29->length;
         ivar_34->seq = (Rijndael_array_2_t)ivar_29->seq;
         if (ivar_34->seq != NULL) ivar_34->seq->count++;
        };
        release_Rijndael_record_14(ivar_29);
        result = (bytestrings__bytestring_t)hex__bytestring2hexstring((bytestrings__bytestring_t)ivar_34);

        defined = true;};
        
        return result;
}

extern bytestrings__bytestring_t Rijndael__testRijndael1(void){
        bytestrings__bytestring_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    /* Input */ bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_8;
        strings__string_t ivar_6;
        uint32_t len15931 = 32;
        uint32_t characters15932[32] = {51, 50, 52, 51, 102, 54, 97, 56, 56, 56, 53, 97, 51, 48, 56, 100, 51, 49, 51, 49, 57, 56, 97, 50, 101, 48, 51, 55, 48, 55, 51, 52};
        stringliteral_t string15930 = mk_string(32, characters15932);
        ivar_6 = (strings__string_t)strings__make_string(len15931, string15930);
        ivar_8 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_6);
        ivar_1 = (bytestrings__bytestring_t)hex__hex2bytestring((bytestrings__bytestring_t)ivar_8);
        /* Cipher */ bytestrings__bytestring_t ivar_9;
        bytestrings__bytestring_t ivar_16;
        strings__string_t ivar_14;
        uint32_t len15934 = 32;
        uint32_t characters15935[32] = {50, 98, 55, 101, 49, 53, 49, 54, 50, 56, 97, 101, 100, 50, 97, 54, 97, 98, 102, 55, 49, 53, 56, 56, 48, 57, 99, 102, 52, 102, 51, 99};
        stringliteral_t string15933 = mk_string(32, characters15935);
        ivar_14 = (strings__string_t)strings__make_string(len15934, string15933);
        ivar_16 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_14);
        ivar_9 = (bytestrings__bytestring_t)hex__hex2bytestring((bytestrings__bytestring_t)ivar_16);
        /* Output */ Rijndael_array_2_t ivar_17;
        Rijndael_array_2_t ivar_27;
        ivar_27 = (Rijndael_array_2_t)ivar_1->seq;
        ivar_27->count++;
        release_bytestrings__bytestring(ivar_1);
        Rijndael_array_2_t ivar_28;
        ivar_28 = (Rijndael_array_2_t)ivar_9->seq;
        ivar_28->count++;
        release_bytestrings__bytestring(ivar_9);
        ivar_17 = (Rijndael_array_2_t)Rijndael__Rijndael((Rijndael_array_2_t)ivar_27, (Rijndael_array_2_t)ivar_28);
        /* Outputbytestring */ Rijndael_record_14_t ivar_29;
        uint8_t ivar_30;
        ivar_30 = (uint8_t)16;
        Rijndael_record_14_t tmp15936 = new_Rijndael_record_14();;
        ivar_29 = (Rijndael_record_14_t)tmp15936;
        tmp15936->length = (uint8_t)ivar_30;
        tmp15936->seq = (Rijndael_array_2_t)ivar_17;
        bytestrings__bytestring_t ivar_34;
        //copying to bytestrings__bytestring from Rijndael_record_14;
        {
         ivar_34 = new_Rijndael_record_15();
         ivar_34->length = (uint32_t)ivar_29->length;
         ivar_34->seq = (Rijndael_array_2_t)ivar_29->seq;
         if (ivar_34->seq != NULL) ivar_34->seq->count++;
        };
        release_Rijndael_record_14(ivar_29);
        result = (bytestrings__bytestring_t)hex__bytestring2hexstring((bytestrings__bytestring_t)ivar_34);

        defined = true;};
        
        return result;
}

extern bytestrings__bytestring_t Rijndael__invSboxHex(void){
        bytestrings__bytestring_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    strings__string_t ivar_4;
        uint32_t len15939 = 512;
        uint32_t characters15940[512] = {53, 50, 48, 57, 54, 97, 100, 53, 51, 48, 51, 54, 97, 53, 51, 56, 98, 102, 52, 48, 97, 51, 57, 101, 56, 49, 102, 51, 100, 55, 102, 98, 55, 99, 101, 51, 51, 57, 56, 50, 57, 98, 50, 102, 102, 102, 56, 55, 51, 52, 56, 101, 52, 51, 52, 52, 99, 52, 100, 101, 101, 57, 99, 98, 53, 52, 55, 98, 57, 52, 51, 50, 97, 54, 99, 50, 50, 51, 51, 100, 101, 101, 52, 99, 57, 53, 48, 98, 52, 50, 102, 97, 99, 51, 52, 101, 48, 56, 50, 101, 97, 49, 54, 54, 50, 56, 100, 57, 50, 52, 98, 50, 55, 54, 53, 98, 97, 50, 52, 57, 54, 100, 56, 98, 100, 49, 50, 53, 55, 50, 102, 56, 102, 54, 54, 52, 56, 54, 54, 56, 57, 56, 49, 54, 100, 52, 97, 52, 53, 99, 99, 99, 53, 100, 54, 53, 98, 54, 57, 50, 54, 99, 55, 48, 52, 56, 53, 48, 102, 100, 101, 100, 98, 57, 100, 97, 53, 101, 49, 53, 52, 54, 53, 55, 97, 55, 56, 100, 57, 100, 56, 52, 57, 48, 100, 56, 97, 98, 48, 48, 56, 99, 98, 99, 100, 51, 48, 97, 102, 55, 101, 52, 53, 56, 48, 53, 98, 56, 98, 51, 52, 53, 48, 54, 100, 48, 50, 99, 49, 101, 56, 102, 99, 97, 51, 102, 48, 102, 48, 50, 99, 49, 97, 102, 98, 100, 48, 51, 48, 49, 49, 51, 56, 97, 54, 98, 51, 97, 57, 49, 49, 49, 52, 49, 52, 102, 54, 55, 100, 99, 101, 97, 57, 55, 102, 50, 99, 102, 99, 101, 102, 48, 98, 52, 101, 54, 55, 51, 57, 54, 97, 99, 55, 52, 50, 50, 101, 55, 97, 100, 51, 53, 56, 53, 101, 50, 102, 57, 51, 55, 101, 56, 49, 99, 55, 53, 100, 102, 54, 101, 52, 55, 102, 49, 49, 97, 55, 49, 49, 100, 50, 57, 99, 53, 56, 57, 54, 102, 98, 55, 54, 50, 48, 101, 97, 97, 49, 56, 98, 101, 49, 98, 102, 99, 53, 54, 51, 101, 52, 98, 99, 54, 100, 50, 55, 57, 50, 48, 57, 97, 100, 98, 99, 48, 102, 101, 55, 56, 99, 100, 53, 97, 102, 52, 49, 102, 100, 100, 97, 56, 51, 51, 56, 56, 48, 55, 99, 55, 51, 49, 98, 49, 49, 50, 49, 48, 53, 57, 50, 55, 56, 48, 101, 99, 53, 102, 54, 48, 53, 49, 55, 102, 97, 57, 49, 57, 98, 53, 52, 97, 48, 100, 50, 100, 101, 53, 55, 97, 57, 102, 57, 51, 99, 57, 57, 99, 101, 102, 97, 48, 101, 48, 51, 98, 52, 100, 97, 101, 50, 97, 102, 53, 98, 48, 99, 56, 101, 98, 98, 98, 51, 99, 56, 51, 53, 51, 57, 57, 54, 49, 49, 55, 50, 98, 48, 52, 55, 101, 98, 97, 55, 55, 100, 54, 50, 54, 101, 49, 54, 57, 49, 52, 54, 51, 53, 53, 50, 49, 48, 99, 55, 100};
        stringliteral_t string15938 = mk_string(512, characters15940);
        ivar_4 = (strings__string_t)strings__make_string(len15939, string15938);
        result = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_4);

        defined = true;};
        
        return result;
}

extern Rijndael_array_2_t Rijndael__invSbox(void){
        Rijndael_array_2_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    /* X */ bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_4;
        ivar_4 = (bytestrings__bytestring_t)Rijndael__invSboxHex();
        if (ivar_4 != NULL) ivar_4->count++;
        ivar_1 = (bytestrings__bytestring_t)hex__hex2bytestring((bytestrings__bytestring_t)ivar_4);
        result = (Rijndael_array_2_t)ivar_1->seq;
        result->count++;
        release_bytestrings__bytestring(ivar_1);

        defined = true;};
        
        return result;
}

extern Rijndael_array_2_t Rijndael__invByteSubst(Rijndael_array_2_t ivar_2){
        Rijndael_array_2_t  result;
        result = new_Rijndael_array_2(16);
        uint8_t ivar_3;
        for (uint32_t index15941 = 0; index15941 < 16; index15941++){
             ivar_3 = (uint8_t)index15941;
             uint8_t ivar_10;
             ivar_10 = (uint8_t)ivar_2->elems[ivar_3];
             Rijndael_array_2_t ivar_11;
             ivar_11 = (Rijndael_array_2_t)Rijndael__invSbox();
             if (ivar_11 != NULL) ivar_11->count++;
             result->elems[index15941] = (uint8_t)ivar_11->elems[ivar_10];
             release_Rijndael_array_2(ivar_11);
        };
        release_Rijndael_array_2(ivar_2);

        
        return result;
}

extern Rijndael_array_2_t Rijndael__invShiftRow(Rijndael_array_2_t ivar_2){
        Rijndael_array_2_t  result;
        result = new_Rijndael_array_2(16);
        uint8_t ivar_3;
        for (uint32_t index15942 = 0; index15942 < 16; index15942++){
             ivar_3 = (uint8_t)index15942;
             /* i */ uint16_t ivar_4;
             uint16_t ivar_8;
             //copying to uint16 from uint8;
             ivar_8 = (uint16_t)ivar_3;
             uint8_t ivar_11;
             ivar_11 = (uint8_t)4;
             uint16_t ivar_9;
             //copying to uint16 from uint8;
             ivar_9 = (uint16_t)ivar_11;
             ivar_4 = (uint16_t)integertypes__u16rem((uint16_t)ivar_8, (uint16_t)ivar_9);
             /* j */ uint16_t ivar_12;
             uint16_t ivar_16;
             //copying to uint16 from uint8;
             ivar_16 = (uint16_t)ivar_3;
             uint8_t ivar_19;
             ivar_19 = (uint8_t)4;
             uint16_t ivar_17;
             //copying to uint16 from uint8;
             ivar_17 = (uint16_t)ivar_19;
             ivar_12 = (uint16_t)integertypes__u16div((uint16_t)ivar_16, (uint16_t)ivar_17);
             /* ij */ uint8_t ivar_20;
             uint32_t ivar_21;
             uint8_t ivar_24;
             ivar_24 = (uint8_t)4;
             ivar_21 = (uint32_t)(ivar_12 + ivar_24);
             ivar_20 = (uint8_t)(ivar_21 - ivar_4);
             /* l */ uint16_t ivar_27;
             uint16_t ivar_31;
             //copying to uint16 from uint8;
             ivar_31 = (uint16_t)ivar_20;
             uint8_t ivar_34;
             ivar_34 = (uint8_t)4;
             uint16_t ivar_32;
             //copying to uint16 from uint8;
             ivar_32 = (uint16_t)ivar_34;
             ivar_27 = (uint16_t)integertypes__u16rem((uint16_t)ivar_31, (uint16_t)ivar_32);
             Rijndael_funtype_1_t ivar_39;
             ivar_2->count++;
             ivar_39 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
             uint8_t ivar_44;
             //copying to uint8 from uint16;
             ivar_44 = (uint8_t)ivar_4;
             uint8_t ivar_45;
             //copying to uint8 from uint16;
             ivar_45 = (uint8_t)ivar_27;
             result->elems[index15942] = (uint8_t)ivar_39->ftbl->mptr(ivar_39, ivar_44, ivar_45);
             ivar_39->ftbl->rptr(ivar_39);
        };
        release_Rijndael_array_2(ivar_2);

        
        return result;
}

extern Rijndael_array_2_t Rijndael__invMixColumn(Rijndael_array_2_t ivar_2){
        Rijndael_array_2_t  result;
        result = new_Rijndael_array_2(16);
        uint8_t ivar_3;
        for (uint32_t index15943 = 0; index15943 < 16; index15943++){
             ivar_3 = (uint8_t)index15943;
             /* i */ uint16_t ivar_4;
             uint16_t ivar_8;
             //copying to uint16 from uint8;
             ivar_8 = (uint16_t)ivar_3;
             uint8_t ivar_11;
             ivar_11 = (uint8_t)4;
             uint16_t ivar_9;
             //copying to uint16 from uint8;
             ivar_9 = (uint16_t)ivar_11;
             ivar_4 = (uint16_t)integertypes__u16rem((uint16_t)ivar_8, (uint16_t)ivar_9);
             /* j */ uint16_t ivar_12;
             uint16_t ivar_16;
             //copying to uint16 from uint8;
             ivar_16 = (uint16_t)ivar_3;
             uint8_t ivar_19;
             ivar_19 = (uint8_t)4;
             uint16_t ivar_17;
             //copying to uint16 from uint8;
             ivar_17 = (uint16_t)ivar_19;
             ivar_12 = (uint16_t)integertypes__u16div((uint16_t)ivar_16, (uint16_t)ivar_17);
             bool_t ivar_20;
             uint8_t ivar_22;
             ivar_22 = (uint8_t)0;
             ivar_20 = (ivar_4 == ivar_22);
             if (ivar_20){  
           uint8_t ivar_101;
           uint8_t ivar_82;
           uint8_t ivar_63;
           uint8_t ivar_44;
           ivar_44 = (uint8_t)14;
           uint8_t ivar_45;
           Rijndael_funtype_1_t ivar_36;
           ivar_2->count++;
           ivar_36 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_41;
           ivar_41 = (uint8_t)0;
           uint8_t ivar_42;
           //copying to uint8 from uint16;
           ivar_42 = (uint8_t)ivar_12;
           ivar_45 = (uint8_t)ivar_36->ftbl->mptr(ivar_36, ivar_41, ivar_42);
           ivar_36->ftbl->rptr(ivar_36);
           ivar_63 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_44, (uint8_t)ivar_45);
           uint8_t ivar_64;
           uint8_t ivar_60;
           ivar_60 = (uint8_t)11;
           uint8_t ivar_61;
           Rijndael_funtype_1_t ivar_52;
           ivar_2->count++;
           ivar_52 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_57;
           ivar_57 = (uint8_t)1;
           uint8_t ivar_58;
           //copying to uint8 from uint16;
           ivar_58 = (uint8_t)ivar_12;
           ivar_61 = (uint8_t)ivar_52->ftbl->mptr(ivar_52, ivar_57, ivar_58);
           ivar_52->ftbl->rptr(ivar_52);
           ivar_64 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_60, (uint8_t)ivar_61);
           ivar_82 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_63, (uint8_t)ivar_64);
           uint8_t ivar_83;
           uint8_t ivar_79;
           ivar_79 = (uint8_t)13;
           uint8_t ivar_80;
           Rijndael_funtype_1_t ivar_71;
           ivar_2->count++;
           ivar_71 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_76;
           ivar_76 = (uint8_t)2;
           uint8_t ivar_77;
           //copying to uint8 from uint16;
           ivar_77 = (uint8_t)ivar_12;
           ivar_80 = (uint8_t)ivar_71->ftbl->mptr(ivar_71, ivar_76, ivar_77);
           ivar_71->ftbl->rptr(ivar_71);
           ivar_83 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_79, (uint8_t)ivar_80);
           ivar_101 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_82, (uint8_t)ivar_83);
           uint8_t ivar_102;
           uint8_t ivar_98;
           ivar_98 = (uint8_t)9;
           uint8_t ivar_99;
           Rijndael_funtype_1_t ivar_90;
           ivar_2->count++;
           ivar_90 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_95;
           ivar_95 = (uint8_t)3;
           uint8_t ivar_96;
           //copying to uint8 from uint16;
           ivar_96 = (uint8_t)ivar_12;
           ivar_99 = (uint8_t)ivar_90->ftbl->mptr(ivar_90, ivar_95, ivar_96);
           ivar_90->ftbl->rptr(ivar_90);
           ivar_102 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_98, (uint8_t)ivar_99);
           result->elems[index15943] = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_101, (uint8_t)ivar_102);
} else {
             
           bool_t ivar_103;
           uint8_t ivar_105;
           ivar_105 = (uint8_t)1;
           ivar_103 = (ivar_4 == ivar_105);
           if (ivar_103){   
           uint8_t ivar_184;
           uint8_t ivar_165;
           uint8_t ivar_146;
           uint8_t ivar_127;
           ivar_127 = (uint8_t)9;
           uint8_t ivar_128;
           Rijndael_funtype_1_t ivar_119;
           ivar_2->count++;
           ivar_119 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_124;
           ivar_124 = (uint8_t)0;
           uint8_t ivar_125;
           //copying to uint8 from uint16;
           ivar_125 = (uint8_t)ivar_12;
           ivar_128 = (uint8_t)ivar_119->ftbl->mptr(ivar_119, ivar_124, ivar_125);
           ivar_119->ftbl->rptr(ivar_119);
           ivar_146 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_127, (uint8_t)ivar_128);
           uint8_t ivar_147;
           uint8_t ivar_143;
           ivar_143 = (uint8_t)14;
           uint8_t ivar_144;
           Rijndael_funtype_1_t ivar_135;
           ivar_2->count++;
           ivar_135 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_140;
           ivar_140 = (uint8_t)1;
           uint8_t ivar_141;
           //copying to uint8 from uint16;
           ivar_141 = (uint8_t)ivar_12;
           ivar_144 = (uint8_t)ivar_135->ftbl->mptr(ivar_135, ivar_140, ivar_141);
           ivar_135->ftbl->rptr(ivar_135);
           ivar_147 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_143, (uint8_t)ivar_144);
           ivar_165 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_146, (uint8_t)ivar_147);
           uint8_t ivar_166;
           uint8_t ivar_162;
           ivar_162 = (uint8_t)11;
           uint8_t ivar_163;
           Rijndael_funtype_1_t ivar_154;
           ivar_2->count++;
           ivar_154 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_159;
           ivar_159 = (uint8_t)2;
           uint8_t ivar_160;
           //copying to uint8 from uint16;
           ivar_160 = (uint8_t)ivar_12;
           ivar_163 = (uint8_t)ivar_154->ftbl->mptr(ivar_154, ivar_159, ivar_160);
           ivar_154->ftbl->rptr(ivar_154);
           ivar_166 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_162, (uint8_t)ivar_163);
           ivar_184 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_165, (uint8_t)ivar_166);
           uint8_t ivar_185;
           uint8_t ivar_181;
           ivar_181 = (uint8_t)13;
           uint8_t ivar_182;
           Rijndael_funtype_1_t ivar_173;
           ivar_2->count++;
           ivar_173 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
           uint8_t ivar_178;
           ivar_178 = (uint8_t)3;
           uint8_t ivar_179;
           //copying to uint8 from uint16;
           ivar_179 = (uint8_t)ivar_12;
           ivar_182 = (uint8_t)ivar_173->ftbl->mptr(ivar_173, ivar_178, ivar_179);
           ivar_173->ftbl->rptr(ivar_173);
           ivar_185 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_181, (uint8_t)ivar_182);
           result->elems[index15943] = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_184, (uint8_t)ivar_185);
} else {
           
           bool_t ivar_186;
           uint8_t ivar_188;
           ivar_188 = (uint8_t)2;
           ivar_186 = (ivar_4 == ivar_188);
           if (ivar_186){    
            uint8_t ivar_267;
            uint8_t ivar_248;
            uint8_t ivar_229;
            uint8_t ivar_210;
            ivar_210 = (uint8_t)13;
            uint8_t ivar_211;
            Rijndael_funtype_1_t ivar_202;
            ivar_2->count++;
            ivar_202 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_207;
            ivar_207 = (uint8_t)0;
            uint8_t ivar_208;
            //copying to uint8 from uint16;
            ivar_208 = (uint8_t)ivar_12;
            ivar_211 = (uint8_t)ivar_202->ftbl->mptr(ivar_202, ivar_207, ivar_208);
            ivar_202->ftbl->rptr(ivar_202);
            ivar_229 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_210, (uint8_t)ivar_211);
            uint8_t ivar_230;
            uint8_t ivar_226;
            ivar_226 = (uint8_t)9;
            uint8_t ivar_227;
            Rijndael_funtype_1_t ivar_218;
            ivar_2->count++;
            ivar_218 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_223;
            ivar_223 = (uint8_t)1;
            uint8_t ivar_224;
            //copying to uint8 from uint16;
            ivar_224 = (uint8_t)ivar_12;
            ivar_227 = (uint8_t)ivar_218->ftbl->mptr(ivar_218, ivar_223, ivar_224);
            ivar_218->ftbl->rptr(ivar_218);
            ivar_230 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_226, (uint8_t)ivar_227);
            ivar_248 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_229, (uint8_t)ivar_230);
            uint8_t ivar_249;
            uint8_t ivar_245;
            ivar_245 = (uint8_t)14;
            uint8_t ivar_246;
            Rijndael_funtype_1_t ivar_237;
            ivar_2->count++;
            ivar_237 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_242;
            ivar_242 = (uint8_t)2;
            uint8_t ivar_243;
            //copying to uint8 from uint16;
            ivar_243 = (uint8_t)ivar_12;
            ivar_246 = (uint8_t)ivar_237->ftbl->mptr(ivar_237, ivar_242, ivar_243);
            ivar_237->ftbl->rptr(ivar_237);
            ivar_249 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_245, (uint8_t)ivar_246);
            ivar_267 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_248, (uint8_t)ivar_249);
            uint8_t ivar_268;
            uint8_t ivar_264;
            ivar_264 = (uint8_t)11;
            uint8_t ivar_265;
            Rijndael_funtype_1_t ivar_256;
            ivar_2->count++;
            ivar_256 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_261;
            ivar_261 = (uint8_t)3;
            uint8_t ivar_262;
            //copying to uint8 from uint16;
            ivar_262 = (uint8_t)ivar_12;
            ivar_265 = (uint8_t)ivar_256->ftbl->mptr(ivar_256, ivar_261, ivar_262);
            ivar_256->ftbl->rptr(ivar_256);
            ivar_268 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_264, (uint8_t)ivar_265);
            result->elems[index15943] = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_267, (uint8_t)ivar_268);
} else {
           
            uint8_t ivar_346;
            uint8_t ivar_327;
            uint8_t ivar_308;
            uint8_t ivar_289;
            ivar_289 = (uint8_t)11;
            uint8_t ivar_290;
            Rijndael_funtype_1_t ivar_281;
            ivar_2->count++;
            ivar_281 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_286;
            ivar_286 = (uint8_t)0;
            uint8_t ivar_287;
            //copying to uint8 from uint16;
            ivar_287 = (uint8_t)ivar_12;
            ivar_290 = (uint8_t)ivar_281->ftbl->mptr(ivar_281, ivar_286, ivar_287);
            ivar_281->ftbl->rptr(ivar_281);
            ivar_308 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_289, (uint8_t)ivar_290);
            uint8_t ivar_309;
            uint8_t ivar_305;
            ivar_305 = (uint8_t)13;
            uint8_t ivar_306;
            Rijndael_funtype_1_t ivar_297;
            ivar_2->count++;
            ivar_297 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_302;
            ivar_302 = (uint8_t)1;
            uint8_t ivar_303;
            //copying to uint8 from uint16;
            ivar_303 = (uint8_t)ivar_12;
            ivar_306 = (uint8_t)ivar_297->ftbl->mptr(ivar_297, ivar_302, ivar_303);
            ivar_297->ftbl->rptr(ivar_297);
            ivar_309 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_305, (uint8_t)ivar_306);
            ivar_327 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_308, (uint8_t)ivar_309);
            uint8_t ivar_328;
            uint8_t ivar_324;
            ivar_324 = (uint8_t)9;
            uint8_t ivar_325;
            Rijndael_funtype_1_t ivar_316;
            ivar_2->count++;
            ivar_316 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_321;
            ivar_321 = (uint8_t)2;
            uint8_t ivar_322;
            //copying to uint8 from uint16;
            ivar_322 = (uint8_t)ivar_12;
            ivar_325 = (uint8_t)ivar_316->ftbl->mptr(ivar_316, ivar_321, ivar_322);
            ivar_316->ftbl->rptr(ivar_316);
            ivar_328 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_324, (uint8_t)ivar_325);
            ivar_346 = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_327, (uint8_t)ivar_328);
            uint8_t ivar_347;
            uint8_t ivar_343;
            ivar_343 = (uint8_t)14;
            uint8_t ivar_344;
            Rijndael_funtype_1_t ivar_335;
            ivar_2->count++;
            ivar_335 = (Rijndael_funtype_1_t)Rijndael__get((Rijndael_array_2_t)ivar_2);
            uint8_t ivar_340;
            ivar_340 = (uint8_t)3;
            uint8_t ivar_341;
            //copying to uint8 from uint16;
            ivar_341 = (uint8_t)ivar_12;
            ivar_344 = (uint8_t)ivar_335->ftbl->mptr(ivar_335, ivar_340, ivar_341);
            ivar_335->ftbl->rptr(ivar_335);
            ivar_347 = (uint8_t)Rijndael__timesConst((uint8_t)ivar_343, (uint8_t)ivar_344);
            result->elems[index15943] = (uint8_t)integer_bv_ops__u8xor((uint8_t)ivar_346, (uint8_t)ivar_347);
};
};
};
        };
        release_Rijndael_array_2(ivar_2);

        
        return result;
}

extern Rijndael_array_2_t Rijndael__invRijndael_step(Rijndael_array_2_t ivar_2, Rijndael_array_2_t ivar_3){
        Rijndael_array_2_t  result;
        /* A1 */ Rijndael_array_2_t ivar_4;
        ivar_4 = (Rijndael_array_2_t)Rijndael__roundkeyXOR((Rijndael_array_2_t)ivar_2, (Rijndael_array_2_t)ivar_3);
        /* A2 */ Rijndael_array_2_t ivar_10;
        ivar_10 = (Rijndael_array_2_t)Rijndael__invMixColumn((Rijndael_array_2_t)ivar_4);
        /* A3 */ Rijndael_array_2_t ivar_14;
        ivar_14 = (Rijndael_array_2_t)Rijndael__invShiftRow((Rijndael_array_2_t)ivar_10);
        result = (Rijndael_array_2_t)Rijndael__invByteSubst((Rijndael_array_2_t)ivar_14);

        
        return result;
}

extern Rijndael_array_2_t Rijndael__invRijndael_rec(Rijndael_array_2_t ivar_2, Rijndael_array_13_t ivar_3, uint8_t ivar_4){
        Rijndael_array_2_t  result;
        bool_t ivar_5;
        uint8_t ivar_7;
        ivar_7 = (uint8_t)10;
        ivar_5 = (ivar_4 >= ivar_7);
        if (ivar_5){ 
             Rijndael_array_2_t ivar_23;
             Rijndael_array_2_t ivar_21;
             Rijndael_array_2_t ivar_19;
             ivar_19 = (Rijndael_array_2_t)ivar_3->elems[ivar_4];
             ivar_19->count++;
             release_Rijndael_array_13(ivar_3);
             ivar_21 = (Rijndael_array_2_t)Rijndael__roundkeyXOR((Rijndael_array_2_t)ivar_2, (Rijndael_array_2_t)ivar_19);
             ivar_23 = (Rijndael_array_2_t)Rijndael__invShiftRow((Rijndael_array_2_t)ivar_21);
             result = (Rijndael_array_2_t)Rijndael__invByteSubst((Rijndael_array_2_t)ivar_23);
} else {
        
             bool_t ivar_24;
             uint8_t ivar_26;
             ivar_26 = (uint8_t)0;
             ivar_24 = (ivar_4 == ivar_26);
             if (ivar_24){  
           Rijndael_array_2_t ivar_45;
           uint8_t ivar_39;
           uint8_t ivar_34;
           ivar_34 = (uint8_t)1;
           ivar_39 = (uint8_t)(ivar_4 + ivar_34);
           ivar_3->count++;
           ivar_45 = (Rijndael_array_2_t)Rijndael__invRijndael_rec((Rijndael_array_2_t)ivar_2, (Rijndael_array_13_t)ivar_3, (uint8_t)ivar_39);
           Rijndael_array_2_t ivar_46;
           ivar_46 = (Rijndael_array_2_t)ivar_3->elems[ivar_4];
           ivar_46->count++;
           release_Rijndael_array_13(ivar_3);
           result = (Rijndael_array_2_t)Rijndael__roundkeyXOR((Rijndael_array_2_t)ivar_45, (Rijndael_array_2_t)ivar_46);
} else {
             
           Rijndael_array_2_t ivar_64;
           uint8_t ivar_58;
           uint8_t ivar_53;
           ivar_53 = (uint8_t)1;
           ivar_58 = (uint8_t)(ivar_4 + ivar_53);
           ivar_3->count++;
           ivar_64 = (Rijndael_array_2_t)Rijndael__invRijndael_rec((Rijndael_array_2_t)ivar_2, (Rijndael_array_13_t)ivar_3, (uint8_t)ivar_58);
           Rijndael_array_2_t ivar_65;
           ivar_65 = (Rijndael_array_2_t)ivar_3->elems[ivar_4];
           ivar_65->count++;
           release_Rijndael_array_13(ivar_3);
           result = (Rijndael_array_2_t)Rijndael__invRijndael_step((Rijndael_array_2_t)ivar_64, (Rijndael_array_2_t)ivar_65);
};
};

        
        return result;
}

extern Rijndael_array_2_t Rijndael__invRijndael(Rijndael_array_2_t ivar_2, Rijndael_array_2_t ivar_3){
        Rijndael_array_2_t  result;
        Rijndael_array_13_t ivar_19;
        Rijndael_array_13_t ivar_14;
        ivar_14 = new_Rijndael_array_13(11);
        uint8_t ivar_10;
        for (uint32_t index15944 = 0; index15944 < 11; index15944++){
             ivar_10 = (uint8_t)index15944;
             //copying to Rijndael_array_2 from Rijndael_array_2;
             ivar_14->elems[index15944] = (Rijndael_array_2_t)ivar_3;
             if (ivar_14->elems[index15944] != NULL) ivar_14->elems[index15944]->count++;
        };
        release_Rijndael_array_2(ivar_3);
        uint8_t ivar_15;
        ivar_15 = (uint8_t)1;
        uint8_t ivar_16;
        ivar_16 = (uint8_t)0;
        ivar_19 = (Rijndael_array_13_t)Rijndael__allKeys((Rijndael_array_13_t)ivar_14, (uint8_t)ivar_15, (uint8_t)ivar_16);
        uint8_t ivar_20;
        ivar_20 = (uint8_t)0;
        result = (Rijndael_array_2_t)Rijndael__invRijndael_rec((Rijndael_array_2_t)ivar_2, (Rijndael_array_13_t)ivar_19, (uint8_t)ivar_20);

        
        return result;
}

extern bytestrings__bytestring_t Rijndael__testInvRijndael1(void){
        bytestrings__bytestring_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    /* Input */ bytestrings__bytestring_t ivar_1;
        bytestrings__bytestring_t ivar_8;
        strings__string_t ivar_6;
        uint32_t len15954 = 32;
        uint32_t characters15955[32] = {51, 50, 52, 51, 102, 54, 97, 56, 56, 56, 53, 97, 51, 48, 56, 100, 51, 49, 51, 49, 57, 56, 97, 50, 101, 48, 51, 55, 48, 55, 51, 52};
        stringliteral_t string15953 = mk_string(32, characters15955);
        ivar_6 = (strings__string_t)strings__make_string(len15954, string15953);
        ivar_8 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_6);
        ivar_1 = (bytestrings__bytestring_t)hex__hex2bytestring((bytestrings__bytestring_t)ivar_8);
        /* Cipher */ bytestrings__bytestring_t ivar_9;
        bytestrings__bytestring_t ivar_16;
        strings__string_t ivar_14;
        uint32_t len15957 = 32;
        uint32_t characters15958[32] = {50, 98, 55, 101, 49, 53, 49, 54, 50, 56, 97, 101, 100, 50, 97, 54, 97, 98, 102, 55, 49, 53, 56, 56, 48, 57, 99, 102, 52, 102, 51, 99};
        stringliteral_t string15956 = mk_string(32, characters15958);
        ivar_14 = (strings__string_t)strings__make_string(len15957, string15956);
        ivar_16 = (bytestrings__bytestring_t)bytestrings__mk_bytestring((strings__string_t)ivar_14);
        ivar_9 = (bytestrings__bytestring_t)hex__hex2bytestring((bytestrings__bytestring_t)ivar_16);
        /* Output */ Rijndael_array_2_t ivar_17;
        Rijndael_array_2_t ivar_35;
        Rijndael_array_2_t ivar_29;
        ivar_29 = (Rijndael_array_2_t)ivar_1->seq;
        ivar_29->count++;
        release_bytestrings__bytestring(ivar_1);
        Rijndael_array_2_t ivar_30;
        ivar_30 = (Rijndael_array_2_t)ivar_9->seq;
        ivar_30->count++;
        ivar_35 = (Rijndael_array_2_t)Rijndael__Rijndael((Rijndael_array_2_t)ivar_29, (Rijndael_array_2_t)ivar_30);
        Rijndael_array_2_t ivar_36;
        ivar_36 = (Rijndael_array_2_t)ivar_9->seq;
        ivar_36->count++;
        release_bytestrings__bytestring(ivar_9);
        ivar_17 = (Rijndael_array_2_t)Rijndael__invRijndael((Rijndael_array_2_t)ivar_35, (Rijndael_array_2_t)ivar_36);
        /* Outputbytestring */ Rijndael_record_14_t ivar_37;
        uint8_t ivar_38;
        ivar_38 = (uint8_t)16;
        Rijndael_record_14_t tmp15959 = new_Rijndael_record_14();;
        ivar_37 = (Rijndael_record_14_t)tmp15959;
        tmp15959->length = (uint8_t)ivar_38;
        tmp15959->seq = (Rijndael_array_2_t)ivar_17;
        bytestrings__bytestring_t ivar_42;
        //copying to bytestrings__bytestring from Rijndael_record_14;
        {
         ivar_42 = new_Rijndael_record_15();
         ivar_42->length = (uint32_t)ivar_37->length;
         ivar_42->seq = (Rijndael_array_2_t)ivar_37->seq;
         if (ivar_42->seq != NULL) ivar_42->seq->count++;
        };
        release_Rijndael_record_14(ivar_37);
        result = (bytestrings__bytestring_t)hex__bytestring2hexstring((bytestrings__bytestring_t)ivar_42);

        defined = true;};
        
        return result;
}

extern bytestrings__bytestring_t Rijndael__testRijndael(bytestrings__bytestring_t ivar_2, bytestrings__bytestring_t ivar_3){
        bytestrings__bytestring_t  result;
        /* Input */ bytestrings__bytestring_t ivar_4;
        bytestrings__bytestring_t ivar_10;
        ivar_10 = (bytestrings__bytestring_t)hex__hex2bytestring((bytestrings__bytestring_t)ivar_2);
        ivar_4 = (bytestrings__bytestring_t)file__printh((bytestrings__bytestring_t)ivar_10);
        /* Cipher */ bytestrings__bytestring_t ivar_11;
        bytestrings__bytestring_t ivar_17;
        ivar_17 = (bytestrings__bytestring_t)hex__hex2bytestring((bytestrings__bytestring_t)ivar_3);
        ivar_11 = (bytestrings__bytestring_t)file__printh((bytestrings__bytestring_t)ivar_17);
        /* Output */ bytestrings__bytestring_t ivar_18;
        bytestrings__bytestring_t ivar_37;
        uint8_t ivar_35;
        ivar_35 = (uint8_t)16;
        /* n */ uint32_t ivar_33;
        //copying to uint32 from uint8;
        ivar_33 = (uint32_t)ivar_35;
        Rijndael_array_2_t ivar_34;
        Rijndael_array_2_t ivar_30;
        ivar_30 = (Rijndael_array_2_t)ivar_4->seq;
        ivar_30->count++;
        release_bytestrings__bytestring(ivar_4);
        Rijndael_array_2_t ivar_31;
        ivar_31 = (Rijndael_array_2_t)ivar_11->seq;
        ivar_31->count++;
        ivar_34 = (Rijndael_array_2_t)Rijndael__Rijndael((Rijndael_array_2_t)ivar_30, (Rijndael_array_2_t)ivar_31);
        ivar_37 = (bytestrings__bytestring_t)bytevectors__byv2bytestring((uint32_t)ivar_33, (bytevectors__byv_t)ivar_34);
        ivar_18 = (bytestrings__bytestring_t)file__printh((bytestrings__bytestring_t)ivar_37);
        /* Inverse */ bytestrings__bytestring_t ivar_38;
        bytestrings__bytestring_t ivar_57;
        uint8_t ivar_55;
        ivar_55 = (uint8_t)16;
        /* n */ uint32_t ivar_53;
        //copying to uint32 from uint8;
        ivar_53 = (uint32_t)ivar_55;
        Rijndael_array_2_t ivar_54;
        Rijndael_array_2_t ivar_50;
        ivar_50 = (Rijndael_array_2_t)ivar_18->seq;
        ivar_50->count++;
        release_bytestrings__bytestring(ivar_18);
        Rijndael_array_2_t ivar_51;
        ivar_51 = (Rijndael_array_2_t)ivar_11->seq;
        ivar_51->count++;
        release_bytestrings__bytestring(ivar_11);
        ivar_54 = (Rijndael_array_2_t)Rijndael__invRijndael((Rijndael_array_2_t)ivar_50, (Rijndael_array_2_t)ivar_51);
        ivar_57 = (bytestrings__bytestring_t)bytevectors__byv2bytestring((uint32_t)ivar_53, (bytevectors__byv_t)ivar_54);
        ivar_38 = (bytestrings__bytestring_t)file__printh((bytestrings__bytestring_t)ivar_57);
        result = (bytestrings__bytestring_t)hex__bytestring2hexstring((bytestrings__bytestring_t)ivar_38);

        
        return result;
}