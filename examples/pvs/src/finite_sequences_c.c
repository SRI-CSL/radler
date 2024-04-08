//Code generated using pvs2ir2c
#include "finite_sequences_c.h"

void release_finite_sequences_funtype_0(finite_sequences_funtype_0_t x, type_actual_t finite_sequences__T){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

finite_sequences_funtype_0_t copy_finite_sequences_funtype_0(finite_sequences_funtype_0_t x){return x->ftbl->cptr(x);}

uint32_t lookup_finite_sequences_funtype_0(finite_sequences_funtype_0_htbl_t htbl, mpz_ptr_t i, uint32_t ihash){
        uint32_t mask = htbl->size - 1;
        uint32_t hashindex = ihash & mask;
        finite_sequences_funtype_0_hashentry_t data = htbl->data[hashindex];
        bool_t keyzero;

        int64_t tmp14330 = mpz_cmp_ui(data.key, 0);
        keyzero = (tmp14330 == 0);
        bool_t keymatch;
        int64_t tmp14331 = mpz_cmp(data.key, i);
        keymatch = (tmp14331 == 0);
        while ((!keyzero || data.keyhash != 0) &&
                 (data.keyhash != ihash || !keymatch)){
                hashindex++;
                hashindex = hashindex & mask;
                data = htbl->data[hashindex];

                int64_t tmp14330 = mpz_cmp_ui(data.key, 0);
                keyzero = (tmp14330 == 0);

                int64_t tmp14331 = mpz_cmp(data.key, i);
                keymatch = (tmp14331 == 0);
                }
        return hashindex;
        }

finite_sequences_funtype_0_t dupdate_finite_sequences_funtype_0(finite_sequences_funtype_0_t a, mpz_ptr_t i, finite_sequences__T_t v, type_actual_t finite_sequences__T){
        finite_sequences_funtype_0_htbl_t htbl = a->htbl;
        if (htbl == NULL){//construct new htbl
                htbl = (finite_sequences_funtype_0_htbl_t)safe_malloc(sizeof(struct finite_sequences_funtype_0_htbl_s));
                htbl->size = HTBL_DEFAULT_SIZE; htbl->num_entries = 0;
                htbl->data = (finite_sequences_funtype_0_hashentry_t *)safe_malloc(HTBL_DEFAULT_SIZE * sizeof(struct finite_sequences_funtype_0_hashentry_s));
                for (uint32_t j = 0; j < HTBL_DEFAULT_SIZE; j++){mpz_init(htbl->data[j].key);mpz_set_ui(htbl->data[j].key, 0); htbl->data[j].keyhash = 0;
                }
                a->htbl = htbl;
        }
        uint32_t size = htbl->size;
        uint32_t num_entries = htbl->num_entries;
        finite_sequences_funtype_0_hashentry_t * data = htbl->data;
        if (num_entries/3 >  size/5){//resize data
                uint32_t new_size = 2*size; uint32_t new_mask = new_size - 1;
                if (size >= HTBL_MAX_SIZE) out_of_memory();
                finite_sequences_funtype_0_hashentry_t * new_data = (finite_sequences_funtype_0_hashentry_t *)safe_malloc(new_size * sizeof(struct finite_sequences_funtype_0_hashentry_s));
                for (uint32_t j = 0; j < new_size; j++){
                        new_data[j].key = 0;
                        new_data[j].keyhash = 0;}
                for (uint32_t j = 0; j < size; j++){//transfer entries
                        uint32_t keyhash = data[j].keyhash;
                        bool_t keyzero;
                        int64_t tmp14332 = mpz_cmp_ui(data[j].key, 0);keyzero = (tmp14332 == 0);
                        if (!keyzero || keyhash != 0){
                                uint32_t new_loc = keyhash ^ new_mask;
                                int64_t tmp14333 = mpz_cmp_ui(new_data[new_loc].key, 0);
                                keyzero = (tmp14333 == 0);
                                while (keyzero && new_data[new_loc].keyhash == 0){
                                        new_loc++;
                                        new_loc = new_loc ^ new_mask;

                                        int64_t tmp14334 = mpz_cmp_ui(new_data[new_loc].key, 0);
                                        keyzero = (tmp14334 == 0);
                                }
                                mpz_set(new_data[new_loc].key, data[j].key);
                                new_data[new_loc].keyhash = keyhash;
                                new_data[new_loc].value = (finite_sequences__T_t)data[j].value;
                                }}
                htbl->size = new_size;
                htbl->num_entries = num_entries;
                htbl->data = new_data;
                safe_free(data);}
        uint32_t ihash = mpz_hash(i);
        uint32_t hashindex = lookup_finite_sequences_funtype_0(htbl, i, ihash);
        finite_sequences_funtype_0_hashentry_t hentry = htbl->data[hashindex];
        uint32_t hkeyhash = hentry.keyhash;
        bool_t hentrykeyzero;
        int64_t tmp14335 = mpz_cmp_ui(hentry.key, 0);hentrykeyzero = (tmp14335 == 0);

        if (hentrykeyzero && (hkeyhash == 0))
                {mpz_set(htbl->data[hashindex].key, i); htbl->data[hashindex].keyhash = ihash; htbl->data[hashindex].value = (finite_sequences__T_t)v; htbl->num_entries++;}
            else {finite_sequences__T_t tempvalue;tempvalue = (finite_sequences__T_t)htbl->data[hashindex].value;htbl->data[hashindex].value = (finite_sequences__T_t)v;if (v != NULL) v->count++;if (tempvalue != NULL)finite_sequences__T->release_ptr(tempvalue, finite_sequences__T);};
        return a;

}

finite_sequences_funtype_0_t update_finite_sequences_funtype_0(finite_sequences_funtype_0_t a, mpz_ptr_t i, finite_sequences__T_t v, type_actual_t finite_sequences__T){
        if (a->count == 1){
                return dupdate_finite_sequences_funtype_0(a, i, v, finite_sequences__T);
            } else {
                finite_sequences_funtype_0_t x = copy_finite_sequences_funtype_0(a);
                a->count--;
                return dupdate_finite_sequences_funtype_0(x, i, v, finite_sequences__T);
            }}

bool_t equal_finite_sequences_funtype_0(finite_sequences_funtype_0_t x, finite_sequences_funtype_0_t y, type_actual_t finite_sequences__T){
        return false;}


finite_sequences__finseq_t new_finite_sequences__finseq(void){
        finite_sequences__finseq_t tmp = (finite_sequences__finseq_t) safe_malloc(sizeof(struct finite_sequences__finseq_s));
        tmp->count = 1;
        return tmp;}

void release_finite_sequences__finseq(finite_sequences__finseq_t x, type_actual_t finite_sequences__T){
        x->count--;
        if (x->count <= 0){
         release_finite_sequences_funtype_0(x->seq, finite_sequences__T);
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_finite_sequences__finseq_ptr(pointer_t x, type_actual_t T){
        actual_finite_sequences__finseq_t actual = (actual_finite_sequences__finseq_t)T;
        type_actual_t finite_sequences__T = actual->finite_sequences__T;
        release_finite_sequences__finseq((finite_sequences__finseq_t)x, finite_sequences__T);
}

finite_sequences__finseq_t copy_finite_sequences__finseq(finite_sequences__finseq_t x){
        finite_sequences__finseq_t y = new_finite_sequences__finseq();
        mpz_set(y->length, x->length);
        y->seq = x->seq;
        if (y->seq != NULL){y->seq->count++;};
        y->count = 1;
        return y;}

bool_t equal_finite_sequences__finseq(finite_sequences__finseq_t x, finite_sequences__finseq_t y, type_actual_t finite_sequences__T){
        bool_t tmp = true;
        tmp = tmp && x->length == y->length;
        tmp = tmp && equal_finite_sequences_funtype_0(x->seq, y->seq, finite_sequences__T);
        return tmp;}

bool_t equal_finite_sequences__finseq_ptr(pointer_t x, pointer_t y, actual_finite_sequences__finseq_t T){
        actual_finite_sequences__finseq_t actual = (actual_finite_sequences__finseq_t)T;
        type_actual_t finite_sequences__T = actual->finite_sequences__T;
        return equal_finite_sequences__finseq((finite_sequences__finseq_t)x, (finite_sequences__finseq_t)y, finite_sequences__T);
}

actual_finite_sequences__finseq_t actual_finite_sequences__finseq(type_actual_t finite_sequences__T){
        actual_finite_sequences__finseq_t new = (actual_finite_sequences__finseq_t)safe_malloc(sizeof(struct actual_finite_sequences__finseq_s));
        new->equal_ptr = (equal_ptr_t)(*equal_finite_sequences__finseq_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_finite_sequences__finseq_ptr);
 

        new->finite_sequences__T = finite_sequences__T;
 
        return new;
 };

finite_sequences__finseq_t update_finite_sequences__finseq_length(finite_sequences__finseq_t x, mpz_ptr_t v){
        finite_sequences__finseq_t y;
        if (x->count == 1){y = x;}
        else {y = copy_finite_sequences__finseq(x); x->count--;};
        mpz_set(y->length, v);
        return y;}

finite_sequences__finseq_t update_finite_sequences__finseq_seq(finite_sequences__finseq_t x, finite_sequences_funtype_0_t v, type_actual_t finite_sequences__T){
        finite_sequences__finseq_t y;
        if (v != NULL){v->count++;};
        if (x->count == 1){y = x; if (x->seq != NULL){release_finite_sequences_funtype_0(x->seq, finite_sequences__T);};}
        else {y = copy_finite_sequences__finseq(x); x->count--; y->seq->count--;};
        y->seq = (finite_sequences_funtype_0_t)v;
        return y;}



void release_finite_sequences_funtype_2(finite_sequences_funtype_2_t x, type_actual_t finite_sequences__T){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

finite_sequences_funtype_2_t copy_finite_sequences_funtype_2(finite_sequences_funtype_2_t x){return x->ftbl->cptr(x);}

uint32_t lookup_finite_sequences_funtype_2(finite_sequences_funtype_2_htbl_t htbl, uint8_t i, uint32_t ihash){
        uint32_t mask = htbl->size - 1;
        uint32_t hashindex = ihash & mask;
        finite_sequences_funtype_2_hashentry_t data = htbl->data[hashindex];
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

finite_sequences_funtype_2_t dupdate_finite_sequences_funtype_2(finite_sequences_funtype_2_t a, uint8_t i, finite_sequences__T_t v, type_actual_t finite_sequences__T){
        finite_sequences_funtype_2_htbl_t htbl = a->htbl;
        if (htbl == NULL){//construct new htbl
                htbl = (finite_sequences_funtype_2_htbl_t)safe_malloc(sizeof(struct finite_sequences_funtype_2_htbl_s));
                htbl->size = HTBL_DEFAULT_SIZE; htbl->num_entries = 0;
                htbl->data = (finite_sequences_funtype_2_hashentry_t *)safe_malloc(HTBL_DEFAULT_SIZE * sizeof(struct finite_sequences_funtype_2_hashentry_s));
                for (uint32_t j = 0; j < HTBL_DEFAULT_SIZE; j++){htbl->data[j].key = (uint8_t)0; htbl->data[j].keyhash = 0;
                }
                a->htbl = htbl;
        }
        uint32_t size = htbl->size;
        uint32_t num_entries = htbl->num_entries;
        finite_sequences_funtype_2_hashentry_t * data = htbl->data;
        if (num_entries/3 >  size/5){//resize data
                uint32_t new_size = 2*size; uint32_t new_mask = new_size - 1;
                if (size >= HTBL_MAX_SIZE) out_of_memory();
                finite_sequences_funtype_2_hashentry_t * new_data = (finite_sequences_funtype_2_hashentry_t *)safe_malloc(new_size * sizeof(struct finite_sequences_funtype_2_hashentry_s));
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
                                new_data[new_loc].value = (finite_sequences__T_t)data[j].value;
                                }}
                htbl->size = new_size;
                htbl->num_entries = num_entries;
                htbl->data = new_data;
                safe_free(data);}
        uint32_t ihash = uint32_hash(i);
        uint32_t hashindex = lookup_finite_sequences_funtype_2(htbl, i, ihash);
        finite_sequences_funtype_2_hashentry_t hentry = htbl->data[hashindex];
        uint32_t hkeyhash = hentry.keyhash;
        bool_t hentrykeyzero;
        hentrykeyzero = (hentry.key == 0);

        if (hentrykeyzero && (hkeyhash == 0))
                {htbl->data[hashindex].key = (uint8_t)i; htbl->data[hashindex].keyhash = ihash; htbl->data[hashindex].value = (finite_sequences__T_t)v; htbl->num_entries++;}
            else {finite_sequences__T_t tempvalue;tempvalue = (finite_sequences__T_t)htbl->data[hashindex].value;htbl->data[hashindex].value = (finite_sequences__T_t)v;if (v != NULL) v->count++;if (tempvalue != NULL)finite_sequences__T->release_ptr(tempvalue, finite_sequences__T);};
        return a;

}

finite_sequences_funtype_2_t update_finite_sequences_funtype_2(finite_sequences_funtype_2_t a, uint8_t i, finite_sequences__T_t v, type_actual_t finite_sequences__T){
        if (a->count == 1){
                return dupdate_finite_sequences_funtype_2(a, i, v, finite_sequences__T);
            } else {
                finite_sequences_funtype_2_t x = copy_finite_sequences_funtype_2(a);
                a->count--;
                return dupdate_finite_sequences_funtype_2(x, i, v, finite_sequences__T);
            }}

bool_t equal_finite_sequences_funtype_2(finite_sequences_funtype_2_t x, finite_sequences_funtype_2_t y, type_actual_t finite_sequences__T){
        return false;}


finite_sequences__T_t f_finite_sequences_closure_3(struct finite_sequences_closure_3_s * closure, uint8_t bvar){
if (closure->htbl != NULL){
        finite_sequences_funtype_2_htbl_t htbl = closure->htbl;
        uint32_t hash = uint32_hash(bvar);
        uint32_t hashindex = lookup_finite_sequences_funtype_2(htbl, bvar, hash);
        finite_sequences_funtype_2_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         keyzero = (entry.key == 0);
        if (!keyzero || entry.keyhash != 0){
            finite_sequences__T_t result;
            result = (finite_sequences__T_t)entry.value;
            return result;}
        

        return h_finite_sequences_closure_3(bvar, closure->fvar_1);};

return h_finite_sequences_closure_3(bvar, closure->fvar_1);}

finite_sequences__T_t m_finite_sequences_closure_3(struct finite_sequences_closure_3_s * closure, uint8_t bvar){
        return h_finite_sequences_closure_3(bvar, closure->fvar_1);}

extern finite_sequences__T_t h_finite_sequences_closure_3(uint8_t ivar_4, type_actual_t finite_sequences__T){
        finite_sequences__T_t result;
        pvs2cerror("Non-executable theory: epsilons", PVS2C_EXIT_ERROR);

        return result;
}

finite_sequences_closure_3_t new_finite_sequences_closure_3(void){
        static struct finite_sequences_funtype_2_ftbl_s ftbl = {.fptr = (finite_sequences__T_t (*)(finite_sequences_funtype_2_t, uint8_t))&f_finite_sequences_closure_3, .mptr = (finite_sequences__T_t (*)(finite_sequences_funtype_2_t, uint8_t))&m_finite_sequences_closure_3, .rptr =  (void (*)(finite_sequences_funtype_2_t))&release_finite_sequences_closure_3, .cptr = (finite_sequences_funtype_2_t (*)(finite_sequences_funtype_2_t))&copy_finite_sequences_closure_3};
        finite_sequences_closure_3_t tmp = (finite_sequences_closure_3_t) safe_malloc(sizeof(struct finite_sequences_closure_3_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_finite_sequences_closure_3(finite_sequences_funtype_2_t closure, type_actual_t finite_sequences__T){
        finite_sequences_closure_3_t x = (finite_sequences_closure_3_t)closure;
        x->count--;
        if (x->count <= 0){
        //printf("\nFreeing\n");
        safe_free(x);}}

finite_sequences_closure_3_t copy_finite_sequences_closure_3(finite_sequences_closure_3_t x){
        finite_sequences_closure_3_t y = new_finite_sequences_closure_3();
        y->ftbl = x->ftbl;

        y->fvar_1 = (type_actual_t)x->fvar_1;
        if (x->htbl != NULL){
            finite_sequences_funtype_2_htbl_t new_htbl = (finite_sequences_funtype_2_htbl_t) safe_malloc(sizeof(struct finite_sequences_funtype_2_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            finite_sequences_funtype_2_hashentry_t * new_data = (finite_sequences_funtype_2_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct finite_sequences_funtype_2_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct finite_sequences_funtype_2_hashentry_s)));
            new_htbl->data = new_data;
            for (uint32_t j = 0; j < new_htbl->size; j++){
                        if ((new_htbl->data[j].key != 0) || new_htbl->data[j].keyhash != 0) new_htbl->data[j].value->count++;};
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


finite_sequences__T_t f_finite_sequences_closure_4(struct finite_sequences_closure_4_s * closure, mpz_ptr_t bvar){
if (closure->htbl != NULL){
        finite_sequences_funtype_0_htbl_t htbl = closure->htbl;
        uint32_t hash = mpz_hash(bvar);
        uint32_t hashindex = lookup_finite_sequences_funtype_0(htbl, bvar, hash);
        finite_sequences_funtype_0_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         int64_t tmp14337 = mpz_cmp_ui(entry.key, 0);
         keyzero = (tmp14337 == 0);
        if (!keyzero || entry.keyhash != 0){
            finite_sequences__T_t result;
            result = (finite_sequences__T_t)entry.value;
            return result;}
        

        return h_finite_sequences_closure_4(bvar, closure->fvar_1, closure->fvar_2);};

return h_finite_sequences_closure_4(bvar, closure->fvar_1, closure->fvar_2);}

finite_sequences__T_t m_finite_sequences_closure_4(struct finite_sequences_closure_4_s * closure, mpz_ptr_t bvar){
        return h_finite_sequences_closure_4(bvar, closure->fvar_1, closure->fvar_2);}

extern finite_sequences__T_t h_finite_sequences_closure_4(mpz_ptr_t ivar_15, finite_sequences_funtype_2_t ivar_12, type_actual_t finite_sequences__T){
        finite_sequences__T_t result;
        finite_sequences__T_t ivar_13;
        uint8_t ivar_14;
        //copying to uint8 from mpz;
        ivar_14 = (uint8_t)mpz_get_ui(ivar_15);
        ivar_13 = (finite_sequences__T_t)ivar_12->ftbl->fptr(ivar_12, ivar_14);
        //copying to finite_sequences__T from finite_sequences__T;
        result = (finite_sequences__T_t)ivar_13;

        return result;
}

finite_sequences_closure_4_t new_finite_sequences_closure_4(void){
        static struct finite_sequences_funtype_0_ftbl_s ftbl = {.fptr = (finite_sequences__T_t (*)(finite_sequences_funtype_0_t, mpz_ptr_t))&f_finite_sequences_closure_4, .mptr = (finite_sequences__T_t (*)(finite_sequences_funtype_0_t, mpz_ptr_t))&m_finite_sequences_closure_4, .rptr =  (void (*)(finite_sequences_funtype_0_t))&release_finite_sequences_closure_4, .cptr = (finite_sequences_funtype_0_t (*)(finite_sequences_funtype_0_t))&copy_finite_sequences_closure_4};
        finite_sequences_closure_4_t tmp = (finite_sequences_closure_4_t) safe_malloc(sizeof(struct finite_sequences_closure_4_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_finite_sequences_closure_4(finite_sequences_funtype_0_t closure, type_actual_t finite_sequences__T){
        finite_sequences_closure_4_t x = (finite_sequences_closure_4_t)closure;
        x->count--;
        if (x->count <= 0){
         release_finite_sequences_funtype_2(x->fvar_1, finite_sequences__T);
        //printf("\nFreeing\n");
        safe_free(x);}}

finite_sequences_closure_4_t copy_finite_sequences_closure_4(finite_sequences_closure_4_t x){
        finite_sequences_closure_4_t y = new_finite_sequences_closure_4();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        y->fvar_2 = (type_actual_t)x->fvar_2;
        if (x->htbl != NULL){
            finite_sequences_funtype_0_htbl_t new_htbl = (finite_sequences_funtype_0_htbl_t) safe_malloc(sizeof(struct finite_sequences_funtype_0_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            finite_sequences_funtype_0_hashentry_t * new_data = (finite_sequences_funtype_0_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct finite_sequences_funtype_0_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct finite_sequences_funtype_0_hashentry_s)));
            new_htbl->data = new_data;
            for (uint32_t j = 0; j < new_htbl->size; j++){
                        if ((new_htbl->data[j].key != 0) || new_htbl->data[j].keyhash != 0) new_htbl->data[j].value->count++;};
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


finite_sequences__T_t f_finite_sequences_closure_5(struct finite_sequences_closure_5_s * closure, mpz_ptr_t bvar){
if (closure->htbl != NULL){
        finite_sequences_funtype_0_htbl_t htbl = closure->htbl;
        uint32_t hash = mpz_hash(bvar);
        uint32_t hashindex = lookup_finite_sequences_funtype_0(htbl, bvar, hash);
        finite_sequences_funtype_0_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         int64_t tmp14347 = mpz_cmp_ui(entry.key, 0);
         keyzero = (tmp14347 == 0);
        if (!keyzero || entry.keyhash != 0){
            finite_sequences__T_t result;
            result = (finite_sequences__T_t)entry.value;
            return result;}
        

        return h_finite_sequences_closure_5(bvar, closure->fvar_1, closure->fvar_2, closure->fvar_3, closure->fvar_4);};

return h_finite_sequences_closure_5(bvar, closure->fvar_1, closure->fvar_2, closure->fvar_3, closure->fvar_4);}

finite_sequences__T_t m_finite_sequences_closure_5(struct finite_sequences_closure_5_s * closure, mpz_ptr_t bvar){
        return h_finite_sequences_closure_5(bvar, closure->fvar_1, closure->fvar_2, closure->fvar_3, closure->fvar_4);}

extern finite_sequences__T_t h_finite_sequences_closure_5(mpz_ptr_t ivar_13, mpz_ptr_t ivar_3, type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_2, finite_sequences__finseq_t ivar_1){
        finite_sequences__T_t result;
        bool_t ivar_14;
        int64_t tmp14348 = mpz_cmp(ivar_13, ivar_3);
        ivar_14 = (tmp14348 < 0);
        if (ivar_14){ 
             finite_sequences_funtype_0_t ivar_22;
             ivar_22 = (finite_sequences_funtype_0_t)ivar_1->seq;
             ivar_22->count++;
             result = (finite_sequences__T_t)ivar_22->ftbl->fptr(ivar_22, ivar_13);
             ivar_22->ftbl->rptr(ivar_22);
} else {
        
             finite_sequences_funtype_0_t ivar_32;
             ivar_32 = (finite_sequences_funtype_0_t)ivar_2->seq;
             ivar_32->count++;
             mpz_ptr_t ivar_34;
             mpz_mk_sub(ivar_34, ivar_13, ivar_3);
             result = (finite_sequences__T_t)ivar_32->ftbl->fptr(ivar_32, ivar_34);
             ivar_32->ftbl->rptr(ivar_32);
};

        return result;
}

finite_sequences_closure_5_t new_finite_sequences_closure_5(void){
        static struct finite_sequences_funtype_0_ftbl_s ftbl = {.fptr = (finite_sequences__T_t (*)(finite_sequences_funtype_0_t, mpz_ptr_t))&f_finite_sequences_closure_5, .mptr = (finite_sequences__T_t (*)(finite_sequences_funtype_0_t, mpz_ptr_t))&m_finite_sequences_closure_5, .rptr =  (void (*)(finite_sequences_funtype_0_t))&release_finite_sequences_closure_5, .cptr = (finite_sequences_funtype_0_t (*)(finite_sequences_funtype_0_t))&copy_finite_sequences_closure_5};
        finite_sequences_closure_5_t tmp = (finite_sequences_closure_5_t) safe_malloc(sizeof(struct finite_sequences_closure_5_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        mpz_init(tmp->fvar_1);
        return tmp;}

void release_finite_sequences_closure_5(finite_sequences_funtype_0_t closure, type_actual_t finite_sequences__T){
        finite_sequences_closure_5_t x = (finite_sequences_closure_5_t)closure;
        x->count--;
        if (x->count <= 0){
         release_finite_sequences__finseq(x->fvar_3, finite_sequences__T);
         release_finite_sequences__finseq(x->fvar_4, finite_sequences__T);
        //printf("\nFreeing\n");
        safe_free(x);}}

finite_sequences_closure_5_t copy_finite_sequences_closure_5(finite_sequences_closure_5_t x){
        finite_sequences_closure_5_t y = new_finite_sequences_closure_5();
        y->ftbl = x->ftbl;

        mpz_set(y->fvar_1, x->fvar_1);
        y->fvar_2 = (type_actual_t)x->fvar_2;
        y->fvar_3 = x->fvar_3; x->fvar_3->count++;
        y->fvar_4 = x->fvar_4; x->fvar_4->count++;
        if (x->htbl != NULL){
            finite_sequences_funtype_0_htbl_t new_htbl = (finite_sequences_funtype_0_htbl_t) safe_malloc(sizeof(struct finite_sequences_funtype_0_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            finite_sequences_funtype_0_hashentry_t * new_data = (finite_sequences_funtype_0_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct finite_sequences_funtype_0_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct finite_sequences_funtype_0_hashentry_s)));
            new_htbl->data = new_data;
            for (uint32_t j = 0; j < new_htbl->size; j++){
                        if ((new_htbl->data[j].key != 0) || new_htbl->data[j].keyhash != 0) new_htbl->data[j].value->count++;};
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


finite_sequences_record_6_t new_finite_sequences_record_6(void){
        finite_sequences_record_6_t tmp = (finite_sequences_record_6_t) safe_malloc(sizeof(struct finite_sequences_record_6_s));
        tmp->count = 1;
        return tmp;}

void release_finite_sequences_record_6(finite_sequences_record_6_t x, type_actual_t finite_sequences__T){
        x->count--;
        if (x->count <= 0){
        //printf("\nFreeing\n");
        safe_free(x);}}

void release_finite_sequences_record_6_ptr(pointer_t x, type_actual_t T){
        actual_finite_sequences_record_6_t actual = (actual_finite_sequences_record_6_t)T;
        type_actual_t finite_sequences__T = actual->finite_sequences__T;
        release_finite_sequences_record_6((finite_sequences_record_6_t)x, finite_sequences__T);
}

finite_sequences_record_6_t copy_finite_sequences_record_6(finite_sequences_record_6_t x){
        finite_sequences_record_6_t y = new_finite_sequences_record_6();
        mpz_set(y->project_1, x->project_1);
        mpz_set(y->project_2, x->project_2);
        y->count = 1;
        return y;}

bool_t equal_finite_sequences_record_6(finite_sequences_record_6_t x, finite_sequences_record_6_t y, type_actual_t finite_sequences__T){
        bool_t tmp = true;
        tmp = tmp && x->project_1 == y->project_1;
        tmp = tmp && x->project_2 == y->project_2;
        return tmp;}

bool_t equal_finite_sequences_record_6_ptr(pointer_t x, pointer_t y, actual_finite_sequences_record_6_t T){
        actual_finite_sequences_record_6_t actual = (actual_finite_sequences_record_6_t)T;
        type_actual_t finite_sequences__T = actual->finite_sequences__T;
        return equal_finite_sequences_record_6((finite_sequences_record_6_t)x, (finite_sequences_record_6_t)y, finite_sequences__T);
}

actual_finite_sequences_record_6_t actual_finite_sequences_record_6(type_actual_t finite_sequences__T){
        actual_finite_sequences_record_6_t new = (actual_finite_sequences_record_6_t)safe_malloc(sizeof(struct actual_finite_sequences_record_6_s));
        new->equal_ptr = (equal_ptr_t)(*equal_finite_sequences_record_6_ptr);
 
        new->release_ptr = (release_ptr_t)(*release_finite_sequences_record_6_ptr);
 

        new->finite_sequences__T = finite_sequences__T;
 
        return new;
 };

finite_sequences_record_6_t update_finite_sequences_record_6_project_1(finite_sequences_record_6_t x, mpz_ptr_t v){
        finite_sequences_record_6_t y;
        if (x->count == 1){y = x;}
        else {y = copy_finite_sequences_record_6(x); x->count--;};
        mpz_set(y->project_1, v);
        return y;}

finite_sequences_record_6_t update_finite_sequences_record_6_project_2(finite_sequences_record_6_t x, mpz_ptr_t v){
        finite_sequences_record_6_t y;
        if (x->count == 1){y = x;}
        else {y = copy_finite_sequences_record_6(x); x->count--;};
        mpz_set(y->project_2, v);
        return y;}




finite_sequences__T_t f_finite_sequences_closure_7(struct finite_sequences_closure_7_s * closure, mpz_ptr_t bvar){
if (closure->htbl != NULL){
        finite_sequences_funtype_0_htbl_t htbl = closure->htbl;
        uint32_t hash = mpz_hash(bvar);
        uint32_t hashindex = lookup_finite_sequences_funtype_0(htbl, bvar, hash);
        finite_sequences_funtype_0_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         int64_t tmp14358 = mpz_cmp_ui(entry.key, 0);
         keyzero = (tmp14358 == 0);
        if (!keyzero || entry.keyhash != 0){
            finite_sequences__T_t result;
            result = (finite_sequences__T_t)entry.value;
            return result;}
        

        return h_finite_sequences_closure_7(bvar, closure->fvar_1, closure->fvar_2, closure->fvar_3);};

return h_finite_sequences_closure_7(bvar, closure->fvar_1, closure->fvar_2, closure->fvar_3);}

finite_sequences__T_t m_finite_sequences_closure_7(struct finite_sequences_closure_7_s * closure, mpz_ptr_t bvar){
        return h_finite_sequences_closure_7(bvar, closure->fvar_1, closure->fvar_2, closure->fvar_3);}

extern finite_sequences__T_t h_finite_sequences_closure_7(mpz_ptr_t ivar_42, mpz_ptr_t ivar_3, type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_1){
        finite_sequences__T_t result;
        finite_sequences_funtype_0_t ivar_50;
        ivar_50 = (finite_sequences_funtype_0_t)ivar_1->seq;
        ivar_50->count++;
        mpz_ptr_t ivar_52;
        mpz_mk_add(ivar_52, ivar_3, ivar_42);
        result = (finite_sequences__T_t)ivar_50->ftbl->fptr(ivar_50, ivar_52);
        ivar_50->ftbl->rptr(ivar_50);

        return result;
}

finite_sequences_closure_7_t new_finite_sequences_closure_7(void){
        static struct finite_sequences_funtype_0_ftbl_s ftbl = {.fptr = (finite_sequences__T_t (*)(finite_sequences_funtype_0_t, mpz_ptr_t))&f_finite_sequences_closure_7, .mptr = (finite_sequences__T_t (*)(finite_sequences_funtype_0_t, mpz_ptr_t))&m_finite_sequences_closure_7, .rptr =  (void (*)(finite_sequences_funtype_0_t))&release_finite_sequences_closure_7, .cptr = (finite_sequences_funtype_0_t (*)(finite_sequences_funtype_0_t))&copy_finite_sequences_closure_7};
        finite_sequences_closure_7_t tmp = (finite_sequences_closure_7_t) safe_malloc(sizeof(struct finite_sequences_closure_7_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        mpz_init(tmp->fvar_1);
        return tmp;}

void release_finite_sequences_closure_7(finite_sequences_funtype_0_t closure, type_actual_t finite_sequences__T){
        finite_sequences_closure_7_t x = (finite_sequences_closure_7_t)closure;
        x->count--;
        if (x->count <= 0){
         release_finite_sequences__finseq(x->fvar_3, finite_sequences__T);
        //printf("\nFreeing\n");
        safe_free(x);}}

finite_sequences_closure_7_t copy_finite_sequences_closure_7(finite_sequences_closure_7_t x){
        finite_sequences_closure_7_t y = new_finite_sequences_closure_7();
        y->ftbl = x->ftbl;

        mpz_set(y->fvar_1, x->fvar_1);
        y->fvar_2 = (type_actual_t)x->fvar_2;
        y->fvar_3 = x->fvar_3; x->fvar_3->count++;
        if (x->htbl != NULL){
            finite_sequences_funtype_0_htbl_t new_htbl = (finite_sequences_funtype_0_htbl_t) safe_malloc(sizeof(struct finite_sequences_funtype_0_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            finite_sequences_funtype_0_hashentry_t * new_data = (finite_sequences_funtype_0_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct finite_sequences_funtype_0_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct finite_sequences_funtype_0_hashentry_s)));
            new_htbl->data = new_data;
            for (uint32_t j = 0; j < new_htbl->size; j++){
                        if ((new_htbl->data[j].key != 0) || new_htbl->data[j].keyhash != 0) new_htbl->data[j].value->count++;};
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


finite_sequences__T_t f_finite_sequences_closure_8(struct finite_sequences_closure_8_s * closure, mpz_ptr_t bvar){
if (closure->htbl != NULL){
        finite_sequences_funtype_0_htbl_t htbl = closure->htbl;
        uint32_t hash = mpz_hash(bvar);
        uint32_t hashindex = lookup_finite_sequences_funtype_0(htbl, bvar, hash);
        finite_sequences_funtype_0_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         int64_t tmp14368 = mpz_cmp_ui(entry.key, 0);
         keyzero = (tmp14368 == 0);
        if (!keyzero || entry.keyhash != 0){
            finite_sequences__T_t result;
            result = (finite_sequences__T_t)entry.value;
            return result;}
        

        return h_finite_sequences_closure_8(bvar, closure->fvar_1, closure->fvar_2, closure->fvar_3);};

return h_finite_sequences_closure_8(bvar, closure->fvar_1, closure->fvar_2, closure->fvar_3);}

finite_sequences__T_t m_finite_sequences_closure_8(struct finite_sequences_closure_8_s * closure, mpz_ptr_t bvar){
        return h_finite_sequences_closure_8(bvar, closure->fvar_1, closure->fvar_2, closure->fvar_3);}

extern finite_sequences__T_t h_finite_sequences_closure_8(mpz_ptr_t ivar_39, mpz_ptr_t ivar_3, type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_1){
        finite_sequences__T_t result;
        finite_sequences_funtype_0_t ivar_47;
        ivar_47 = (finite_sequences_funtype_0_t)ivar_1->seq;
        ivar_47->count++;
        mpz_ptr_t ivar_49;
        mpz_mk_add(ivar_49, ivar_3, ivar_39);
        result = (finite_sequences__T_t)ivar_47->ftbl->fptr(ivar_47, ivar_49);
        ivar_47->ftbl->rptr(ivar_47);

        return result;
}

finite_sequences_closure_8_t new_finite_sequences_closure_8(void){
        static struct finite_sequences_funtype_0_ftbl_s ftbl = {.fptr = (finite_sequences__T_t (*)(finite_sequences_funtype_0_t, mpz_ptr_t))&f_finite_sequences_closure_8, .mptr = (finite_sequences__T_t (*)(finite_sequences_funtype_0_t, mpz_ptr_t))&m_finite_sequences_closure_8, .rptr =  (void (*)(finite_sequences_funtype_0_t))&release_finite_sequences_closure_8, .cptr = (finite_sequences_funtype_0_t (*)(finite_sequences_funtype_0_t))&copy_finite_sequences_closure_8};
        finite_sequences_closure_8_t tmp = (finite_sequences_closure_8_t) safe_malloc(sizeof(struct finite_sequences_closure_8_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        mpz_init(tmp->fvar_1);
        return tmp;}

void release_finite_sequences_closure_8(finite_sequences_funtype_0_t closure, type_actual_t finite_sequences__T){
        finite_sequences_closure_8_t x = (finite_sequences_closure_8_t)closure;
        x->count--;
        if (x->count <= 0){
         release_finite_sequences__finseq(x->fvar_3, finite_sequences__T);
        //printf("\nFreeing\n");
        safe_free(x);}}

finite_sequences_closure_8_t copy_finite_sequences_closure_8(finite_sequences_closure_8_t x){
        finite_sequences_closure_8_t y = new_finite_sequences_closure_8();
        y->ftbl = x->ftbl;

        mpz_set(y->fvar_1, x->fvar_1);
        y->fvar_2 = (type_actual_t)x->fvar_2;
        y->fvar_3 = x->fvar_3; x->fvar_3->count++;
        if (x->htbl != NULL){
            finite_sequences_funtype_0_htbl_t new_htbl = (finite_sequences_funtype_0_htbl_t) safe_malloc(sizeof(struct finite_sequences_funtype_0_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            finite_sequences_funtype_0_hashentry_t * new_data = (finite_sequences_funtype_0_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct finite_sequences_funtype_0_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct finite_sequences_funtype_0_hashentry_s)));
            new_htbl->data = new_data;
            for (uint32_t j = 0; j < new_htbl->size; j++){
                        if ((new_htbl->data[j].key != 0) || new_htbl->data[j].keyhash != 0) new_htbl->data[j].value->count++;};
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

extern finite_sequences__finseq_t finite_sequences__empty_seq(type_actual_t finite_sequences__T){
        finite_sequences__finseq_t  result;
        uint8_t ivar_17;
        ivar_17 = (uint8_t)0;
        mpz_ptr_t ivar_1;
        //copying to mpz from uint8;
        mpz_mk_set_ui(ivar_1, ivar_17);
        finite_sequences_funtype_2_t ivar_12;
        finite_sequences_closure_3_t cl14336;
        cl14336 = new_finite_sequences_closure_3();
        cl14336->fvar_1 = (type_actual_t)finite_sequences__T;
        ivar_12 = (finite_sequences_funtype_2_t)cl14336;
        finite_sequences_funtype_0_t ivar_10;
        finite_sequences_closure_4_t cl14338;
        cl14338 = new_finite_sequences_closure_4();
        cl14338->fvar_1 = (finite_sequences_funtype_2_t)ivar_12;
        if (cl14338->fvar_1 != NULL) cl14338->fvar_1->count++;
        cl14338->fvar_2 = (type_actual_t)finite_sequences__T;
        ivar_10 = (finite_sequences_funtype_0_t)cl14338;
        finite_sequences__finseq_t tmp14339 = new_finite_sequences__finseq();;
        result = (finite_sequences__finseq_t)tmp14339;
        mpz_init(tmp14339->length);
        mpz_set(tmp14339->length, ivar_1);
        mpz_clear(ivar_1);
        tmp14339->seq = (finite_sequences_funtype_0_t)ivar_10;

        
        return result;
}

extern finite_sequences_funtype_0_t finite_sequences__finseq_appl(type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_1){
        finite_sequences_funtype_0_t  result;
        result = (finite_sequences_funtype_0_t)ivar_1->seq;
        result->count++;
        release_finite_sequences__finseq(ivar_1, finite_sequences__T);

        
        return result;
}

extern finite_sequences__finseq_t finite_sequences__oh(type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_1, finite_sequences__finseq_t ivar_2){
        finite_sequences__finseq_t  result;
        /* l1 */ mpz_ptr_t ivar_3;
        ivar_3 = safe_malloc(sizeof(mpz_t));
        mpz_init(ivar_3);
        mpz_set(ivar_3, ivar_1->length);
        /* lsum */ mpz_ptr_t ivar_5;
        mpz_ptr_t ivar_7;
        ivar_7 = safe_malloc(sizeof(mpz_t));
        mpz_init(ivar_7);
        mpz_set(ivar_7, ivar_2->length);
        mpz_mk_add(ivar_5, ivar_7, ivar_3);
        finite_sequences_funtype_0_t ivar_35;
        finite_sequences_closure_5_t cl14349;
        cl14349 = new_finite_sequences_closure_5();
        mpz_set(cl14349->fvar_1, ivar_3);
        cl14349->fvar_2 = (type_actual_t)finite_sequences__T;
        cl14349->fvar_3 = (finite_sequences__finseq_t)ivar_2;
        if (cl14349->fvar_3 != NULL) cl14349->fvar_3->count++;
        cl14349->fvar_4 = (finite_sequences__finseq_t)ivar_1;
        if (cl14349->fvar_4 != NULL) cl14349->fvar_4->count++;
        release_finite_sequences__finseq(ivar_1, finite_sequences__T);
        release_finite_sequences__finseq(ivar_2, finite_sequences__T);
        ivar_35 = (finite_sequences_funtype_0_t)cl14349;
        finite_sequences__finseq_t tmp14350 = new_finite_sequences__finseq();;
        result = (finite_sequences__finseq_t)tmp14350;
        mpz_init(tmp14350->length);
        mpz_set(tmp14350->length, ivar_5);
        mpz_clear(ivar_5);
        tmp14350->seq = (finite_sequences_funtype_0_t)ivar_35;

        
        return result;
}

extern finite_sequences__finseq_t finite_sequences__caret(type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_1, finite_sequences_record_6_t ivar_2){
        finite_sequences__finseq_t  result;
        /* m */ mpz_ptr_t ivar_3;
        ivar_3 = safe_malloc(sizeof(mpz_t));
        mpz_init(ivar_3);
        mpz_set(ivar_3, ivar_2->project_1);
        /* n */ mpz_ptr_t ivar_5;
        ivar_5 = safe_malloc(sizeof(mpz_t));
        mpz_init(ivar_5);
        mpz_set(ivar_5, ivar_2->project_2);
        release_finite_sequences_record_6(ivar_2, finite_sequences__T);
        bool_t ivar_7;
        bool_t ivar_8;
        int64_t tmp14356 = mpz_cmp(ivar_3, ivar_5);
        ivar_8 = (tmp14356 > 0);
        if (ivar_8){ 
             ivar_7 = (bool_t) true;
} else {
        
             mpz_ptr_t ivar_14;
             ivar_14 = safe_malloc(sizeof(mpz_t));
             mpz_init(ivar_14);
             mpz_set(ivar_14, ivar_1->length);
             int64_t tmp14357 = mpz_cmp(ivar_3, ivar_14);
             ivar_7 = (tmp14357 >= 0);
};
        if (ivar_7){ 
             release_finite_sequences__finseq(ivar_1, finite_sequences__T);
             result = (finite_sequences__finseq_t)finite_sequences__empty_seq((type_actual_t)finite_sequences__T);
} else {
        
             /* len */ mpz_ptr_t ivar_19;
             mpz_ptr_t ivar_38;
             mpz_ptr_t ivar_22;
             mpz_mk_sub(ivar_22, ivar_5, ivar_3);
             uint8_t ivar_23;
             ivar_23 = (uint8_t)1;
             mpz_mk_set_ui(ivar_38, (uint64_t)ivar_23);
             mpz_add(ivar_38, ivar_38, ivar_22);
             mpq_ptr_t ivar_33;
             //copying to mpq from mpz;
             mpq_mk_set_z(ivar_33, ivar_38);
             mpz_clear(ivar_38);
             mpz_ptr_t ivar_37;
             mpz_ptr_t ivar_28;
             ivar_28 = safe_malloc(sizeof(mpz_t));
             mpz_init(ivar_28);
             mpz_set(ivar_28, ivar_1->length);
             mpz_mk_sub(ivar_37, ivar_28, ivar_3);
             mpq_ptr_t ivar_34;
             //copying to mpq from mpz;
             mpq_mk_set_z(ivar_34, ivar_37);
             mpz_clear(ivar_37);
             mpz_mk_set_q(ivar_19, real_defs__min((mpq_ptr_t)ivar_33, (mpq_ptr_t)ivar_34));
             finite_sequences_funtype_0_t ivar_53;
             finite_sequences_closure_7_t cl14359;
             cl14359 = new_finite_sequences_closure_7();
             mpz_set(cl14359->fvar_1, ivar_3);
             cl14359->fvar_2 = (type_actual_t)finite_sequences__T;
             cl14359->fvar_3 = (finite_sequences__finseq_t)ivar_1;
             if (cl14359->fvar_3 != NULL) cl14359->fvar_3->count++;
             release_finite_sequences__finseq(ivar_1, finite_sequences__T);
             ivar_53 = (finite_sequences_funtype_0_t)cl14359;
             finite_sequences__finseq_t tmp14360 = new_finite_sequences__finseq();;
             result = (finite_sequences__finseq_t)tmp14360;
             mpz_init(tmp14360->length);
             mpz_set(tmp14360->length, ivar_19);
             mpz_clear(ivar_19);
             tmp14360->seq = (finite_sequences_funtype_0_t)ivar_53;
};

        
        return result;
}

extern finite_sequences__finseq_t finite_sequences__doublecaret(type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_1, finite_sequences_record_6_t ivar_2){
        finite_sequences__finseq_t  result;
        /* m */ mpz_ptr_t ivar_3;
        ivar_3 = safe_malloc(sizeof(mpz_t));
        mpz_init(ivar_3);
        mpz_set(ivar_3, ivar_2->project_1);
        /* n */ mpz_ptr_t ivar_5;
        ivar_5 = safe_malloc(sizeof(mpz_t));
        mpz_init(ivar_5);
        mpz_set(ivar_5, ivar_2->project_2);
        release_finite_sequences_record_6(ivar_2, finite_sequences__T);
        bool_t ivar_7;
        bool_t ivar_8;
        int64_t tmp14366 = mpz_cmp(ivar_3, ivar_5);
        ivar_8 = (tmp14366 >= 0);
        if (ivar_8){ 
             ivar_7 = (bool_t) true;
} else {
        
             mpz_ptr_t ivar_14;
             ivar_14 = safe_malloc(sizeof(mpz_t));
             mpz_init(ivar_14);
             mpz_set(ivar_14, ivar_1->length);
             int64_t tmp14367 = mpz_cmp(ivar_3, ivar_14);
             ivar_7 = (tmp14367 >= 0);
};
        if (ivar_7){ 
             release_finite_sequences__finseq(ivar_1, finite_sequences__T);
             result = (finite_sequences__finseq_t)finite_sequences__empty_seq((type_actual_t)finite_sequences__T);
} else {
        
             /* len */ mpz_ptr_t ivar_19;
             mpz_ptr_t ivar_35;
             mpz_mk_sub(ivar_35, ivar_5, ivar_3);
             mpq_ptr_t ivar_30;
             //copying to mpq from mpz;
             mpq_mk_set_z(ivar_30, ivar_35);
             mpz_clear(ivar_35);
             mpz_ptr_t ivar_34;
             mpz_ptr_t ivar_25;
             ivar_25 = safe_malloc(sizeof(mpz_t));
             mpz_init(ivar_25);
             mpz_set(ivar_25, ivar_1->length);
             mpz_mk_sub(ivar_34, ivar_25, ivar_3);
             mpq_ptr_t ivar_31;
             //copying to mpq from mpz;
             mpq_mk_set_z(ivar_31, ivar_34);
             mpz_clear(ivar_34);
             mpz_mk_set_q(ivar_19, real_defs__min((mpq_ptr_t)ivar_30, (mpq_ptr_t)ivar_31));
             finite_sequences_funtype_0_t ivar_50;
             finite_sequences_closure_8_t cl14369;
             cl14369 = new_finite_sequences_closure_8();
             mpz_set(cl14369->fvar_1, ivar_3);
             cl14369->fvar_2 = (type_actual_t)finite_sequences__T;
             cl14369->fvar_3 = (finite_sequences__finseq_t)ivar_1;
             if (cl14369->fvar_3 != NULL) cl14369->fvar_3->count++;
             release_finite_sequences__finseq(ivar_1, finite_sequences__T);
             ivar_50 = (finite_sequences_funtype_0_t)cl14369;
             finite_sequences__finseq_t tmp14370 = new_finite_sequences__finseq();;
             result = (finite_sequences__finseq_t)tmp14370;
             mpz_init(tmp14370->length);
             mpz_set(tmp14370->length, ivar_19);
             mpz_clear(ivar_19);
             tmp14370->seq = (finite_sequences_funtype_0_t)ivar_50;
};

        
        return result;
}

extern finite_sequences__T_t finite_sequences__extract1(type_actual_t finite_sequences__T, finite_sequences__finseq_t ivar_1){
        finite_sequences__T_t  result;
        finite_sequences_funtype_0_t ivar_6;
        ivar_6 = (finite_sequences_funtype_0_t)ivar_1->seq;
        ivar_6->count++;
        release_finite_sequences__finseq(ivar_1, finite_sequences__T);
        uint8_t ivar_9;
        ivar_9 = (uint8_t)0;
        mpz_ptr_t ivar_8;
        //copying to mpz from uint8;
        mpz_mk_set_ui(ivar_8, ivar_9);
        result = (finite_sequences__T_t)ivar_6->ftbl->fptr(ivar_6, ivar_8);
        ivar_6->ftbl->rptr(ivar_6);

        
        return result;
}