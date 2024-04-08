//Code generated using pvs2ir2c
#include "gen_strings_c.h"

void release_gen_strings_funtype_0(gen_strings_funtype_0_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

gen_strings_funtype_0_t copy_gen_strings_funtype_0(gen_strings_funtype_0_t x){return x->ftbl->cptr(x);}

uint32_t lookup_gen_strings_funtype_0(gen_strings_funtype_0_htbl_t htbl, mpz_ptr_t i, uint32_t ihash){
        uint32_t mask = htbl->size - 1;
        uint32_t hashindex = ihash & mask;
        gen_strings_funtype_0_hashentry_t data = htbl->data[hashindex];
        bool_t keyzero;

        int64_t tmp14457 = mpz_cmp_ui(data.key, 0);
        keyzero = (tmp14457 == 0);
        bool_t keymatch;
        int64_t tmp14458 = mpz_cmp(data.key, i);
        keymatch = (tmp14458 == 0);
        while ((!keyzero || data.keyhash != 0) &&
                 (data.keyhash != ihash || !keymatch)){
                hashindex++;
                hashindex = hashindex & mask;
                data = htbl->data[hashindex];

                int64_t tmp14457 = mpz_cmp_ui(data.key, 0);
                keyzero = (tmp14457 == 0);

                int64_t tmp14458 = mpz_cmp(data.key, i);
                keymatch = (tmp14458 == 0);
                }
        return hashindex;
        }

gen_strings_funtype_0_t dupdate_gen_strings_funtype_0(gen_strings_funtype_0_t a, mpz_ptr_t i, uint32_t v){
        gen_strings_funtype_0_htbl_t htbl = a->htbl;
        if (htbl == NULL){//construct new htbl
                htbl = (gen_strings_funtype_0_htbl_t)safe_malloc(sizeof(struct gen_strings_funtype_0_htbl_s));
                htbl->size = HTBL_DEFAULT_SIZE; htbl->num_entries = 0;
                htbl->data = (gen_strings_funtype_0_hashentry_t *)safe_malloc(HTBL_DEFAULT_SIZE * sizeof(struct gen_strings_funtype_0_hashentry_s));
                for (uint32_t j = 0; j < HTBL_DEFAULT_SIZE; j++){mpz_init(htbl->data[j].key);mpz_set_ui(htbl->data[j].key, 0); htbl->data[j].keyhash = 0;
                }
                a->htbl = htbl;
        }
        uint32_t size = htbl->size;
        uint32_t num_entries = htbl->num_entries;
        gen_strings_funtype_0_hashentry_t * data = htbl->data;
        if (num_entries/3 >  size/5){//resize data
                uint32_t new_size = 2*size; uint32_t new_mask = new_size - 1;
                if (size >= HTBL_MAX_SIZE) out_of_memory();
                gen_strings_funtype_0_hashentry_t * new_data = (gen_strings_funtype_0_hashentry_t *)safe_malloc(new_size * sizeof(struct gen_strings_funtype_0_hashentry_s));
                for (uint32_t j = 0; j < new_size; j++){
                        new_data[j].key = 0;
                        new_data[j].keyhash = 0;}
                for (uint32_t j = 0; j < size; j++){//transfer entries
                        uint32_t keyhash = data[j].keyhash;
                        bool_t keyzero;
                        int64_t tmp14459 = mpz_cmp_ui(data[j].key, 0);keyzero = (tmp14459 == 0);
                        if (!keyzero || keyhash != 0){
                                uint32_t new_loc = keyhash ^ new_mask;
                                int64_t tmp14460 = mpz_cmp_ui(new_data[new_loc].key, 0);
                                keyzero = (tmp14460 == 0);
                                while (keyzero && new_data[new_loc].keyhash == 0){
                                        new_loc++;
                                        new_loc = new_loc ^ new_mask;

                                        int64_t tmp14461 = mpz_cmp_ui(new_data[new_loc].key, 0);
                                        keyzero = (tmp14461 == 0);
                                }
                                mpz_set(new_data[new_loc].key, data[j].key);
                                new_data[new_loc].keyhash = keyhash;
                                new_data[new_loc].value = (uint32_t)data[j].value;
                                }}
                htbl->size = new_size;
                htbl->num_entries = num_entries;
                htbl->data = new_data;
                safe_free(data);}
        uint32_t ihash = mpz_hash(i);
        uint32_t hashindex = lookup_gen_strings_funtype_0(htbl, i, ihash);
        gen_strings_funtype_0_hashentry_t hentry = htbl->data[hashindex];
        uint32_t hkeyhash = hentry.keyhash;
        bool_t hentrykeyzero;
        int64_t tmp14462 = mpz_cmp_ui(hentry.key, 0);hentrykeyzero = (tmp14462 == 0);

        if (hentrykeyzero && (hkeyhash == 0))
                {mpz_set(htbl->data[hashindex].key, i); htbl->data[hashindex].keyhash = ihash; htbl->data[hashindex].value = (uint32_t)v; htbl->num_entries++;}
            else {uint32_t tempvalue;tempvalue = (uint32_t)htbl->data[hashindex].value;htbl->data[hashindex].value = (uint32_t)v;};
        return a;

}

gen_strings_funtype_0_t update_gen_strings_funtype_0(gen_strings_funtype_0_t a, mpz_ptr_t i, uint32_t v){
        if (a->count == 1){
                return dupdate_gen_strings_funtype_0(a, i, v);
            } else {
                gen_strings_funtype_0_t x = copy_gen_strings_funtype_0(a);
                a->count--;
                return dupdate_gen_strings_funtype_0(x, i, v);
            }}

bool_t equal_gen_strings_funtype_0(gen_strings_funtype_0_t x, gen_strings_funtype_0_t y){
        return false;}

void release_gen_strings_funtype_1(gen_strings_funtype_1_t x){
        x->count--;
            if (x->count <= 0)

                x->ftbl->rptr(x);}

gen_strings_funtype_1_t copy_gen_strings_funtype_1(gen_strings_funtype_1_t x){return x->ftbl->cptr(x);}

uint32_t lookup_gen_strings_funtype_1(gen_strings_funtype_1_htbl_t htbl, uint8_t i, uint32_t ihash){
        uint32_t mask = htbl->size - 1;
        uint32_t hashindex = ihash & mask;
        gen_strings_funtype_1_hashentry_t data = htbl->data[hashindex];
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

gen_strings_funtype_1_t dupdate_gen_strings_funtype_1(gen_strings_funtype_1_t a, uint8_t i, uint32_t v){
        gen_strings_funtype_1_htbl_t htbl = a->htbl;
        if (htbl == NULL){//construct new htbl
                htbl = (gen_strings_funtype_1_htbl_t)safe_malloc(sizeof(struct gen_strings_funtype_1_htbl_s));
                htbl->size = HTBL_DEFAULT_SIZE; htbl->num_entries = 0;
                htbl->data = (gen_strings_funtype_1_hashentry_t *)safe_malloc(HTBL_DEFAULT_SIZE * sizeof(struct gen_strings_funtype_1_hashentry_s));
                for (uint32_t j = 0; j < HTBL_DEFAULT_SIZE; j++){htbl->data[j].key = (uint8_t)0; htbl->data[j].keyhash = 0;
                }
                a->htbl = htbl;
        }
        uint32_t size = htbl->size;
        uint32_t num_entries = htbl->num_entries;
        gen_strings_funtype_1_hashentry_t * data = htbl->data;
        if (num_entries/3 >  size/5){//resize data
                uint32_t new_size = 2*size; uint32_t new_mask = new_size - 1;
                if (size >= HTBL_MAX_SIZE) out_of_memory();
                gen_strings_funtype_1_hashentry_t * new_data = (gen_strings_funtype_1_hashentry_t *)safe_malloc(new_size * sizeof(struct gen_strings_funtype_1_hashentry_s));
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
                                new_data[new_loc].value = (uint32_t)data[j].value;
                                }}
                htbl->size = new_size;
                htbl->num_entries = num_entries;
                htbl->data = new_data;
                safe_free(data);}
        uint32_t ihash = uint32_hash(i);
        uint32_t hashindex = lookup_gen_strings_funtype_1(htbl, i, ihash);
        gen_strings_funtype_1_hashentry_t hentry = htbl->data[hashindex];
        uint32_t hkeyhash = hentry.keyhash;
        bool_t hentrykeyzero;
        hentrykeyzero = (hentry.key == 0);

        if (hentrykeyzero && (hkeyhash == 0))
                {htbl->data[hashindex].key = (uint8_t)i; htbl->data[hashindex].keyhash = ihash; htbl->data[hashindex].value = (uint32_t)v; htbl->num_entries++;}
            else {uint32_t tempvalue;tempvalue = (uint32_t)htbl->data[hashindex].value;htbl->data[hashindex].value = (uint32_t)v;};
        return a;

}

gen_strings_funtype_1_t update_gen_strings_funtype_1(gen_strings_funtype_1_t a, uint8_t i, uint32_t v){
        if (a->count == 1){
                return dupdate_gen_strings_funtype_1(a, i, v);
            } else {
                gen_strings_funtype_1_t x = copy_gen_strings_funtype_1(a);
                a->count--;
                return dupdate_gen_strings_funtype_1(x, i, v);
            }}

bool_t equal_gen_strings_funtype_1(gen_strings_funtype_1_t x, gen_strings_funtype_1_t y){
        return false;}


uint32_t f_gen_strings_closure_2(struct gen_strings_closure_2_s * closure, uint8_t bvar){
if (closure->htbl != NULL){
        gen_strings_funtype_1_htbl_t htbl = closure->htbl;
        uint32_t hash = uint32_hash(bvar);
        uint32_t hashindex = lookup_gen_strings_funtype_1(htbl, bvar, hash);
        gen_strings_funtype_1_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         keyzero = (entry.key == 0);
        if (!keyzero || entry.keyhash != 0){
            uint32_t result;
            result = (uint32_t)entry.value;
            return result;}
        

        return h_gen_strings_closure_2(bvar);};

return h_gen_strings_closure_2(bvar);}

uint32_t m_gen_strings_closure_2(struct gen_strings_closure_2_s * closure, uint8_t bvar){
        return h_gen_strings_closure_2(bvar);}

extern uint32_t h_gen_strings_closure_2(uint8_t ivar_4){
        uint32_t result;
        uint8_t ivar_5;
        ivar_5 = (uint8_t)0;
        result = (uint32_t) ivar_5;

        return result;
}

gen_strings_closure_2_t new_gen_strings_closure_2(void){
        static struct gen_strings_funtype_1_ftbl_s ftbl = {.fptr = (uint32_t (*)(gen_strings_funtype_1_t, uint8_t))&f_gen_strings_closure_2, .mptr = (uint32_t (*)(gen_strings_funtype_1_t, uint8_t))&m_gen_strings_closure_2, .rptr =  (void (*)(gen_strings_funtype_1_t))&release_gen_strings_closure_2, .cptr = (gen_strings_funtype_1_t (*)(gen_strings_funtype_1_t))&copy_gen_strings_closure_2};
        gen_strings_closure_2_t tmp = (gen_strings_closure_2_t) safe_malloc(sizeof(struct gen_strings_closure_2_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_gen_strings_closure_2(gen_strings_funtype_1_t closure){
        gen_strings_closure_2_t x = (gen_strings_closure_2_t)closure;
        x->count--;
        if (x->count <= 0){
        //printf("\nFreeing\n");
        safe_free(x);}}

gen_strings_closure_2_t copy_gen_strings_closure_2(gen_strings_closure_2_t x){
        gen_strings_closure_2_t y = new_gen_strings_closure_2();
        y->ftbl = x->ftbl;

        if (x->htbl != NULL){
            gen_strings_funtype_1_htbl_t new_htbl = (gen_strings_funtype_1_htbl_t) safe_malloc(sizeof(struct gen_strings_funtype_1_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            gen_strings_funtype_1_hashentry_t * new_data = (gen_strings_funtype_1_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct gen_strings_funtype_1_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct gen_strings_funtype_1_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


uint32_t f_gen_strings_closure_3(struct gen_strings_closure_3_s * closure, mpz_ptr_t bvar){
if (closure->htbl != NULL){
        gen_strings_funtype_0_htbl_t htbl = closure->htbl;
        uint32_t hash = mpz_hash(bvar);
        uint32_t hashindex = lookup_gen_strings_funtype_0(htbl, bvar, hash);
        gen_strings_funtype_0_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         int64_t tmp14465 = mpz_cmp_ui(entry.key, 0);
         keyzero = (tmp14465 == 0);
        if (!keyzero || entry.keyhash != 0){
            uint32_t result;
            result = (uint32_t)entry.value;
            return result;}
        

        return h_gen_strings_closure_3(bvar, closure->fvar_1);};

return h_gen_strings_closure_3(bvar, closure->fvar_1);}

uint32_t m_gen_strings_closure_3(struct gen_strings_closure_3_s * closure, mpz_ptr_t bvar){
        return h_gen_strings_closure_3(bvar, closure->fvar_1);}

extern uint32_t h_gen_strings_closure_3(mpz_ptr_t ivar_12, gen_strings_funtype_1_t ivar_9){
        uint32_t result;
        uint32_t ivar_10;
        uint8_t ivar_11;
        //copying to uint8 from mpz;
        ivar_11 = (uint8_t)mpz_get_ui(ivar_12);
        ivar_10 = (uint32_t)ivar_9->ftbl->fptr(ivar_9, ivar_11);
        //copying to uint32 from uint32;
        result = (uint32_t)ivar_10;

        return result;
}

gen_strings_closure_3_t new_gen_strings_closure_3(void){
        static struct gen_strings_funtype_0_ftbl_s ftbl = {.fptr = (uint32_t (*)(gen_strings_funtype_0_t, mpz_ptr_t))&f_gen_strings_closure_3, .mptr = (uint32_t (*)(gen_strings_funtype_0_t, mpz_ptr_t))&m_gen_strings_closure_3, .rptr =  (void (*)(gen_strings_funtype_0_t))&release_gen_strings_closure_3, .cptr = (gen_strings_funtype_0_t (*)(gen_strings_funtype_0_t))&copy_gen_strings_closure_3};
        gen_strings_closure_3_t tmp = (gen_strings_closure_3_t) safe_malloc(sizeof(struct gen_strings_closure_3_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_gen_strings_closure_3(gen_strings_funtype_0_t closure){
        gen_strings_closure_3_t x = (gen_strings_closure_3_t)closure;
        x->count--;
        if (x->count <= 0){
         release_gen_strings_funtype_1(x->fvar_1);
        //printf("\nFreeing\n");
        safe_free(x);}}

gen_strings_closure_3_t copy_gen_strings_closure_3(gen_strings_closure_3_t x){
        gen_strings_closure_3_t y = new_gen_strings_closure_3();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        if (x->htbl != NULL){
            gen_strings_funtype_0_htbl_t new_htbl = (gen_strings_funtype_0_htbl_t) safe_malloc(sizeof(struct gen_strings_funtype_0_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            gen_strings_funtype_0_hashentry_t * new_data = (gen_strings_funtype_0_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct gen_strings_funtype_0_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct gen_strings_funtype_0_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


uint32_t f_gen_strings_closure_4(struct gen_strings_closure_4_s * closure, uint8_t bvar){
if (closure->htbl != NULL){
        gen_strings_funtype_1_htbl_t htbl = closure->htbl;
        uint32_t hash = uint32_hash(bvar);
        uint32_t hashindex = lookup_gen_strings_funtype_1(htbl, bvar, hash);
        gen_strings_funtype_1_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         keyzero = (entry.key == 0);
        if (!keyzero || entry.keyhash != 0){
            uint32_t result;
            result = (uint32_t)entry.value;
            return result;}
        

        return h_gen_strings_closure_4(bvar, closure->fvar_1);};

return h_gen_strings_closure_4(bvar, closure->fvar_1);}

uint32_t m_gen_strings_closure_4(struct gen_strings_closure_4_s * closure, uint8_t bvar){
        return h_gen_strings_closure_4(bvar, closure->fvar_1);}

extern uint32_t h_gen_strings_closure_4(uint8_t ivar_5, uint32_t ivar_1){
        uint32_t result;
        //copying to uint32 from uint32;
        result = (uint32_t)ivar_1;

        return result;
}

gen_strings_closure_4_t new_gen_strings_closure_4(void){
        static struct gen_strings_funtype_1_ftbl_s ftbl = {.fptr = (uint32_t (*)(gen_strings_funtype_1_t, uint8_t))&f_gen_strings_closure_4, .mptr = (uint32_t (*)(gen_strings_funtype_1_t, uint8_t))&m_gen_strings_closure_4, .rptr =  (void (*)(gen_strings_funtype_1_t))&release_gen_strings_closure_4, .cptr = (gen_strings_funtype_1_t (*)(gen_strings_funtype_1_t))&copy_gen_strings_closure_4};
        gen_strings_closure_4_t tmp = (gen_strings_closure_4_t) safe_malloc(sizeof(struct gen_strings_closure_4_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_gen_strings_closure_4(gen_strings_funtype_1_t closure){
        gen_strings_closure_4_t x = (gen_strings_closure_4_t)closure;
        x->count--;
        if (x->count <= 0){
        //printf("\nFreeing\n");
        safe_free(x);}}

gen_strings_closure_4_t copy_gen_strings_closure_4(gen_strings_closure_4_t x){
        gen_strings_closure_4_t y = new_gen_strings_closure_4();
        y->ftbl = x->ftbl;

        y->fvar_1 = (uint32_t)x->fvar_1;
        if (x->htbl != NULL){
            gen_strings_funtype_1_htbl_t new_htbl = (gen_strings_funtype_1_htbl_t) safe_malloc(sizeof(struct gen_strings_funtype_1_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            gen_strings_funtype_1_hashentry_t * new_data = (gen_strings_funtype_1_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct gen_strings_funtype_1_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct gen_strings_funtype_1_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


uint32_t f_gen_strings_closure_5(struct gen_strings_closure_5_s * closure, mpz_ptr_t bvar){
if (closure->htbl != NULL){
        gen_strings_funtype_0_htbl_t htbl = closure->htbl;
        uint32_t hash = mpz_hash(bvar);
        uint32_t hashindex = lookup_gen_strings_funtype_0(htbl, bvar, hash);
        gen_strings_funtype_0_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         int64_t tmp14470 = mpz_cmp_ui(entry.key, 0);
         keyzero = (tmp14470 == 0);
        if (!keyzero || entry.keyhash != 0){
            uint32_t result;
            result = (uint32_t)entry.value;
            return result;}
        

        return h_gen_strings_closure_5(bvar, closure->fvar_1);};

return h_gen_strings_closure_5(bvar, closure->fvar_1);}

uint32_t m_gen_strings_closure_5(struct gen_strings_closure_5_s * closure, mpz_ptr_t bvar){
        return h_gen_strings_closure_5(bvar, closure->fvar_1);}

extern uint32_t h_gen_strings_closure_5(mpz_ptr_t ivar_11, gen_strings_funtype_1_t ivar_8){
        uint32_t result;
        uint32_t ivar_9;
        uint8_t ivar_10;
        //copying to uint8 from mpz;
        ivar_10 = (uint8_t)mpz_get_ui(ivar_11);
        ivar_9 = (uint32_t)ivar_8->ftbl->fptr(ivar_8, ivar_10);
        //copying to uint32 from uint32;
        result = (uint32_t)ivar_9;

        return result;
}

gen_strings_closure_5_t new_gen_strings_closure_5(void){
        static struct gen_strings_funtype_0_ftbl_s ftbl = {.fptr = (uint32_t (*)(gen_strings_funtype_0_t, mpz_ptr_t))&f_gen_strings_closure_5, .mptr = (uint32_t (*)(gen_strings_funtype_0_t, mpz_ptr_t))&m_gen_strings_closure_5, .rptr =  (void (*)(gen_strings_funtype_0_t))&release_gen_strings_closure_5, .cptr = (gen_strings_funtype_0_t (*)(gen_strings_funtype_0_t))&copy_gen_strings_closure_5};
        gen_strings_closure_5_t tmp = (gen_strings_closure_5_t) safe_malloc(sizeof(struct gen_strings_closure_5_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_gen_strings_closure_5(gen_strings_funtype_0_t closure){
        gen_strings_closure_5_t x = (gen_strings_closure_5_t)closure;
        x->count--;
        if (x->count <= 0){
         release_gen_strings_funtype_1(x->fvar_1);
        //printf("\nFreeing\n");
        safe_free(x);}}

gen_strings_closure_5_t copy_gen_strings_closure_5(gen_strings_closure_5_t x){
        gen_strings_closure_5_t y = new_gen_strings_closure_5();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        if (x->htbl != NULL){
            gen_strings_funtype_0_htbl_t new_htbl = (gen_strings_funtype_0_htbl_t) safe_malloc(sizeof(struct gen_strings_funtype_0_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            gen_strings_funtype_0_hashentry_t * new_data = (gen_strings_funtype_0_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct gen_strings_funtype_0_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct gen_strings_funtype_0_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


uint32_t f_gen_strings_closure_6(struct gen_strings_closure_6_s * closure, mpz_ptr_t bvar){
if (closure->htbl != NULL){
        gen_strings_funtype_0_htbl_t htbl = closure->htbl;
        uint32_t hash = mpz_hash(bvar);
        uint32_t hashindex = lookup_gen_strings_funtype_0(htbl, bvar, hash);
        gen_strings_funtype_0_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         int64_t tmp14515 = mpz_cmp_ui(entry.key, 0);
         keyzero = (tmp14515 == 0);
        if (!keyzero || entry.keyhash != 0){
            uint32_t result;
            result = (uint32_t)entry.value;
            return result;}
        

        return h_gen_strings_closure_6(bvar, closure->fvar_1);};

return h_gen_strings_closure_6(bvar, closure->fvar_1);}

uint32_t m_gen_strings_closure_6(struct gen_strings_closure_6_s * closure, mpz_ptr_t bvar){
        return h_gen_strings_closure_6(bvar, closure->fvar_1);}

extern uint32_t h_gen_strings_closure_6(mpz_ptr_t ivar_14, strings__string_t ivar_1){
        uint32_t result;
        ivar_1->count++;
        result = (uint32_t)gen_strings__get((strings__string_t)ivar_1, (mpz_ptr_t)ivar_14);

        return result;
}

gen_strings_closure_6_t new_gen_strings_closure_6(void){
        static struct gen_strings_funtype_0_ftbl_s ftbl = {.fptr = (uint32_t (*)(gen_strings_funtype_0_t, mpz_ptr_t))&f_gen_strings_closure_6, .mptr = (uint32_t (*)(gen_strings_funtype_0_t, mpz_ptr_t))&m_gen_strings_closure_6, .rptr =  (void (*)(gen_strings_funtype_0_t))&release_gen_strings_closure_6, .cptr = (gen_strings_funtype_0_t (*)(gen_strings_funtype_0_t))&copy_gen_strings_closure_6};
        gen_strings_closure_6_t tmp = (gen_strings_closure_6_t) safe_malloc(sizeof(struct gen_strings_closure_6_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        return tmp;}

void release_gen_strings_closure_6(gen_strings_funtype_0_t closure){
        gen_strings_closure_6_t x = (gen_strings_closure_6_t)closure;
        x->count--;
        if (x->count <= 0){
         release_strings__string(x->fvar_1);
        //printf("\nFreeing\n");
        safe_free(x);}}

gen_strings_closure_6_t copy_gen_strings_closure_6(gen_strings_closure_6_t x){
        gen_strings_closure_6_t y = new_gen_strings_closure_6();
        y->ftbl = x->ftbl;

        y->fvar_1 = x->fvar_1; x->fvar_1->count++;
        if (x->htbl != NULL){
            gen_strings_funtype_0_htbl_t new_htbl = (gen_strings_funtype_0_htbl_t) safe_malloc(sizeof(struct gen_strings_funtype_0_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            gen_strings_funtype_0_hashentry_t * new_data = (gen_strings_funtype_0_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct gen_strings_funtype_0_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct gen_strings_funtype_0_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}


uint32_t f_gen_strings_closure_7(struct gen_strings_closure_7_s * closure, mpz_ptr_t bvar){
if (closure->htbl != NULL){
        gen_strings_funtype_0_htbl_t htbl = closure->htbl;
        uint32_t hash = mpz_hash(bvar);
        uint32_t hashindex = lookup_gen_strings_funtype_0(htbl, bvar, hash);
        gen_strings_funtype_0_hashentry_t entry = htbl->data[hashindex];
        bool_t keyzero;
         int64_t tmp14527 = mpz_cmp_ui(entry.key, 0);
         keyzero = (tmp14527 == 0);
        if (!keyzero || entry.keyhash != 0){
            uint32_t result;
            result = (uint32_t)entry.value;
            return result;}
        

        return h_gen_strings_closure_7(bvar, closure->fvar_1, closure->fvar_2);};

return h_gen_strings_closure_7(bvar, closure->fvar_1, closure->fvar_2);}

uint32_t m_gen_strings_closure_7(struct gen_strings_closure_7_s * closure, mpz_ptr_t bvar){
        return h_gen_strings_closure_7(bvar, closure->fvar_1, closure->fvar_2);}

extern uint32_t h_gen_strings_closure_7(mpz_ptr_t ivar_23, mpz_ptr_t ivar_2, strings__string_t ivar_1){
        uint32_t result;
        mpz_ptr_t ivar_35;
        mpz_mk_add(ivar_35, ivar_23, ivar_2);
        ivar_1->count++;
        result = (uint32_t)gen_strings__get((strings__string_t)ivar_1, (mpz_ptr_t)ivar_35);

        return result;
}

gen_strings_closure_7_t new_gen_strings_closure_7(void){
        static struct gen_strings_funtype_0_ftbl_s ftbl = {.fptr = (uint32_t (*)(gen_strings_funtype_0_t, mpz_ptr_t))&f_gen_strings_closure_7, .mptr = (uint32_t (*)(gen_strings_funtype_0_t, mpz_ptr_t))&m_gen_strings_closure_7, .rptr =  (void (*)(gen_strings_funtype_0_t))&release_gen_strings_closure_7, .cptr = (gen_strings_funtype_0_t (*)(gen_strings_funtype_0_t))&copy_gen_strings_closure_7};
        gen_strings_closure_7_t tmp = (gen_strings_closure_7_t) safe_malloc(sizeof(struct gen_strings_closure_7_s));
        tmp->count = 1;
        tmp->ftbl = &ftbl;
        tmp->htbl = NULL;
        mpz_init(tmp->fvar_1);
        return tmp;}

void release_gen_strings_closure_7(gen_strings_funtype_0_t closure){
        gen_strings_closure_7_t x = (gen_strings_closure_7_t)closure;
        x->count--;
        if (x->count <= 0){
         release_strings__string(x->fvar_2);
        //printf("\nFreeing\n");
        safe_free(x);}}

gen_strings_closure_7_t copy_gen_strings_closure_7(gen_strings_closure_7_t x){
        gen_strings_closure_7_t y = new_gen_strings_closure_7();
        y->ftbl = x->ftbl;

        mpz_set(y->fvar_1, x->fvar_1);
        y->fvar_2 = x->fvar_2; x->fvar_2->count++;
        if (x->htbl != NULL){
            gen_strings_funtype_0_htbl_t new_htbl = (gen_strings_funtype_0_htbl_t) safe_malloc(sizeof(struct gen_strings_funtype_0_htbl_s));
            new_htbl->size = x->htbl->size;
            new_htbl->num_entries = x->htbl->num_entries;
            gen_strings_funtype_0_hashentry_t * new_data = (gen_strings_funtype_0_hashentry_t *) safe_malloc(new_htbl->size * sizeof(struct gen_strings_funtype_0_hashentry_s));
            memcpy(new_data, x->htbl->data, (new_htbl->size * sizeof(struct gen_strings_funtype_0_hashentry_s)));
            new_htbl->data = new_data;;
            y->htbl = new_htbl;
        } else
            {y->htbl = NULL;};
        return y;
}

extern mpz_ptr_t gen_strings__length(strings__string_t ivar_2){
        mpz_ptr_t  result;
        result = safe_malloc(sizeof(mpz_t));
        mpz_init(result);
        mpz_set(result, ivar_2->length);
        release_strings__string(ivar_2);

        
        return result;
}

extern uint32_t gen_strings__get(strings__string_t ivar_3, mpz_ptr_t ivar_4){
        uint32_t  result;
        gen_strings_funtype_0_t ivar_10;
        ivar_10 = (gen_strings_funtype_0_t)ivar_3->seq;
        ivar_10->count++;
        release_strings__string(ivar_3);
        result = (uint32_t)ivar_10->ftbl->fptr(ivar_10, ivar_4);
        ivar_10->ftbl->rptr(ivar_10);

        
        return result;
}

extern strings__string_t gen_strings__empty(void){
        strings__string_t  static  result;

        static bool_t defined = false;
        if (!defined){
                    uint8_t ivar_14;
        ivar_14 = (uint8_t)0;
        mpz_ptr_t ivar_1;
        //copying to mpz from uint8;
        mpz_mk_set_ui(ivar_1, ivar_14);
        gen_strings_funtype_1_t ivar_9;
        gen_strings_closure_2_t cl14464;
        cl14464 = new_gen_strings_closure_2();
        ivar_9 = (gen_strings_funtype_1_t)cl14464;
        gen_strings_funtype_0_t ivar_7;
        gen_strings_closure_3_t cl14466;
        cl14466 = new_gen_strings_closure_3();
        cl14466->fvar_1 = (gen_strings_funtype_1_t)ivar_9;
        if (cl14466->fvar_1 != NULL) cl14466->fvar_1->count++;
        ivar_7 = (gen_strings_funtype_0_t)cl14466;
        strings__string_t tmp14467 = new_strings__string();;
        result = (strings__string_t)tmp14467;
        mpz_init(tmp14467->length);
        mpz_set(tmp14467->length, ivar_1);
        mpz_clear(ivar_1);
        tmp14467->seq = (gen_strings_funtype_0_t)ivar_7;

        defined = true;};
        
        return result;
}

extern strings__string_t gen_strings__unit(uint32_t ivar_1){
        strings__string_t  result;
        uint8_t ivar_13;
        ivar_13 = (uint8_t)1;
        mpz_ptr_t ivar_2;
        //copying to mpz from uint8;
        mpz_mk_set_ui(ivar_2, ivar_13);
        gen_strings_funtype_1_t ivar_8;
        gen_strings_closure_4_t cl14469;
        cl14469 = new_gen_strings_closure_4();
        cl14469->fvar_1 = (uint32_t)ivar_1;
        ivar_8 = (gen_strings_funtype_1_t)cl14469;
        gen_strings_funtype_0_t ivar_6;
        gen_strings_closure_5_t cl14471;
        cl14471 = new_gen_strings_closure_5();
        cl14471->fvar_1 = (gen_strings_funtype_1_t)ivar_8;
        if (cl14471->fvar_1 != NULL) cl14471->fvar_1->count++;
        ivar_6 = (gen_strings_funtype_0_t)cl14471;
        strings__string_t tmp14472 = new_strings__string();;
        result = (strings__string_t)tmp14472;
        mpz_init(tmp14472->length);
        mpz_set(tmp14472->length, ivar_2);
        mpz_clear(ivar_2);
        tmp14472->seq = (gen_strings_funtype_0_t)ivar_6;

        
        return result;
}

extern mpz_ptr_t gen_strings__strdiff_rec(strings__string_t ivar_48, strings__string_t ivar_49, mpz_ptr_t ivar_50){
        mpz_ptr_t  result;
        bool_t ivar_73;
        bool_t ivar_74;
        mpz_ptr_t ivar_77;
        ivar_77 = safe_malloc(sizeof(mpz_t));
        mpz_init(ivar_77);
        mpz_set(ivar_77, ivar_48->length);
        int64_t tmp14489 = mpz_cmp(ivar_50, ivar_77);
        ivar_74 = (tmp14489 == 0);
        if (ivar_74){ 
             ivar_73 = (bool_t) true;
} else {
        
             bool_t ivar_80;
             mpz_ptr_t ivar_83;
             ivar_83 = safe_malloc(sizeof(mpz_t));
             mpz_init(ivar_83);
             mpz_set(ivar_83, ivar_49->length);
             int64_t tmp14490 = mpz_cmp(ivar_50, ivar_83);
             ivar_80 = (tmp14490 == 0);
             if (ivar_80){  
           ivar_73 = (bool_t) true;
} else {
             
           uint32_t ivar_86;
           ivar_48->count++;
           ivar_86 = (uint32_t)gen_strings__get((strings__string_t)ivar_48, (mpz_ptr_t)ivar_50);
           uint32_t ivar_87;
           ivar_49->count++;
           ivar_87 = (uint32_t)gen_strings__get((strings__string_t)ivar_49, (mpz_ptr_t)ivar_50);
           ivar_73 = (ivar_86 != ivar_87);
};
};
        if (ivar_73){ 
             release_strings__string(ivar_49);
             release_strings__string(ivar_48);
             //copying to mpz from mpz;
             mpz_mk_set(result, ivar_50);
             mpz_clear(ivar_50);
} else {
        
             mpz_ptr_t ivar_121;
             uint8_t ivar_116;
             ivar_116 = (uint8_t)1;
             mpz_mk_set_ui(ivar_121, (uint64_t)ivar_116);
             mpz_add(ivar_121, ivar_121, ivar_50);
             result = (mpz_ptr_t)gen_strings__strdiff_rec((strings__string_t)ivar_48, (strings__string_t)ivar_49, ivar_121);
};

        
        return result;
}

extern mpz_ptr_t gen_strings__strdiff(strings__string_t ivar_15, strings__string_t ivar_16){
        mpz_ptr_t  result;
        uint8_t ivar_47;
        ivar_47 = (uint8_t)0;
        mpz_ptr_t ivar_45;
        //copying to mpz from uint8;
        mpz_mk_set_ui(ivar_45, ivar_47);
        result = (mpz_ptr_t)gen_strings__strdiff_rec((strings__string_t)ivar_15, (strings__string_t)ivar_16, (mpz_ptr_t)ivar_45);

        
        return result;
}

extern int8_t gen_strings__strcmp(strings__string_t ivar_2, strings__string_t ivar_3){
        int8_t  result;
        /* i */ mpz_ptr_t ivar_4;
        ivar_2->count++;
        ivar_3->count++;
        ivar_4 = (mpz_ptr_t)gen_strings__strdiff((strings__string_t)ivar_2, (strings__string_t)ivar_3);
        bool_t ivar_43;
        mpq_ptr_t ivar_45;
        mpz_ptr_t ivar_56;
        ivar_56 = safe_malloc(sizeof(mpz_t));
        mpz_init(ivar_56);
        mpz_set(ivar_56, ivar_2->length);
        mpq_ptr_t ivar_51;
        //copying to mpq from mpz;
        mpq_mk_set_z(ivar_51, ivar_56);
        mpz_clear(ivar_56);
        mpz_ptr_t ivar_55;
        ivar_55 = safe_malloc(sizeof(mpz_t));
        mpz_init(ivar_55);
        mpz_set(ivar_55, ivar_3->length);
        mpq_ptr_t ivar_52;
        //copying to mpq from mpz;
        mpq_mk_set_z(ivar_52, ivar_55);
        mpz_clear(ivar_55);
        ivar_45 = (mpq_ptr_t)real_defs__min((mpq_ptr_t)ivar_51, (mpq_ptr_t)ivar_52);
        int64_t tmp14503 = mpq_cmp_z(ivar_45, ivar_4);
        ivar_43 = (tmp14503 == 0);
        if (ivar_43){ 
             bool_t ivar_58;
             mpz_ptr_t ivar_59;
             ivar_59 = safe_malloc(sizeof(mpz_t));
             mpz_init(ivar_59);
             mpz_set(ivar_59, ivar_2->length);
             mpz_ptr_t ivar_60;
             ivar_60 = safe_malloc(sizeof(mpz_t));
             mpz_init(ivar_60);
             mpz_set(ivar_60, ivar_3->length);
             int64_t tmp14504 = mpz_cmp(ivar_59, ivar_60);
             ivar_58 = (tmp14504 < 0);
             if (ivar_58){  
           release_strings__string(ivar_3);
           release_strings__string(ivar_2);
           result = (int8_t)-1;
} else {
             
           bool_t ivar_64;
           mpz_ptr_t ivar_65;
           ivar_65 = safe_malloc(sizeof(mpz_t));
           mpz_init(ivar_65);
           mpz_set(ivar_65, ivar_2->length);
           release_strings__string(ivar_2);
           mpz_ptr_t ivar_66;
           ivar_66 = safe_malloc(sizeof(mpz_t));
           mpz_init(ivar_66);
           mpz_set(ivar_66, ivar_3->length);
           release_strings__string(ivar_3);
           int64_t tmp14505 = mpz_cmp(ivar_65, ivar_66);
           ivar_64 = (tmp14505 > 0);
           if (ivar_64){   
           result = (int8_t)1;
} else {
           
           result = (int8_t)0;
};
};
} else {
        
             bool_t ivar_70;
             uint32_t ivar_71;
             uint32_t ivar_73;
             ivar_73 = (uint32_t)gen_strings__get((strings__string_t)ivar_2, (mpz_ptr_t)ivar_4);
             ivar_71 = (uint32_t) ivar_73;
             uint32_t ivar_72;
             uint32_t ivar_80;
             ivar_80 = (uint32_t)gen_strings__get((strings__string_t)ivar_3, (mpz_ptr_t)ivar_4);
             ivar_72 = (uint32_t) ivar_80;
             ivar_70 = (ivar_71 < ivar_72);
             if (ivar_70){  
           result = (int8_t)-1;
} else {
             
           result = (int8_t)1;
};
};

        
        return result;
}

extern strings__string_t gen_strings__prefix(strings__string_t ivar_1, mpz_ptr_t ivar_2){
        strings__string_t  result;
        bool_t ivar_4;
        mpz_ptr_t ivar_6;
        ivar_6 = safe_malloc(sizeof(mpz_t));
        mpz_init(ivar_6);
        mpz_set(ivar_6, ivar_1->length);
        int64_t tmp14514 = mpz_cmp(ivar_2, ivar_6);
        ivar_4 = (tmp14514 == 0);
        if (ivar_4){ 
             //copying to strings__string from strings__string;
             result = (strings__string_t)ivar_1;
             if (result != NULL) result->count++;
             release_strings__string(ivar_1);
} else {
        
             gen_strings_funtype_0_t ivar_21;
             gen_strings_closure_6_t cl14516;
             cl14516 = new_gen_strings_closure_6();
             cl14516->fvar_1 = (strings__string_t)ivar_1;
             if (cl14516->fvar_1 != NULL) cl14516->fvar_1->count++;
             release_strings__string(ivar_1);
             ivar_21 = (gen_strings_funtype_0_t)cl14516;
             strings__string_t tmp14517 = new_strings__string();;
             result = (strings__string_t)tmp14517;
             mpz_init(tmp14517->length);
             mpz_set(tmp14517->length, ivar_2);
             mpz_clear(ivar_2);
             tmp14517->seq = (gen_strings_funtype_0_t)ivar_21;
};

        
        return result;
}

extern strings__string_t gen_strings__suffix(strings__string_t ivar_1, mpz_ptr_t ivar_2){
        strings__string_t  result;
        bool_t ivar_4;
        uint8_t ivar_6;
        ivar_6 = (uint8_t)0;
        int64_t tmp14526 = mpz_cmp_ui(ivar_2, ivar_6);
        ivar_4 = (tmp14526 == 0);
        if (ivar_4){ 
             //copying to strings__string from strings__string;
             result = (strings__string_t)ivar_1;
             if (result != NULL) result->count++;
             release_strings__string(ivar_1);
} else {
        
             mpz_ptr_t ivar_12;
             mpz_ptr_t ivar_8;
             ivar_8 = safe_malloc(sizeof(mpz_t));
             mpz_init(ivar_8);
             mpz_set(ivar_8, ivar_1->length);
             mpz_mk_sub(ivar_12, ivar_8, ivar_2);
             gen_strings_funtype_0_t ivar_36;
             gen_strings_closure_7_t cl14528;
             cl14528 = new_gen_strings_closure_7();
             mpz_set(cl14528->fvar_1, ivar_2);
             cl14528->fvar_2 = (strings__string_t)ivar_1;
             if (cl14528->fvar_2 != NULL) cl14528->fvar_2->count++;
             release_strings__string(ivar_1);
             ivar_36 = (gen_strings_funtype_0_t)cl14528;
             strings__string_t tmp14529 = new_strings__string();;
             result = (strings__string_t)tmp14529;
             mpz_init(tmp14529->length);
             mpz_set(tmp14529->length, ivar_12);
             mpz_clear(ivar_12);
             tmp14529->seq = (gen_strings_funtype_0_t)ivar_36;
};

        
        return result;
}

extern strings__string_t gen_strings__substr(strings__string_t ivar_4, mpz_ptr_t ivar_5, mpz_ptr_t ivar_7){
        strings__string_t  result;
        strings__string_t ivar_20;
        ivar_20 = (strings__string_t)gen_strings__suffix((strings__string_t)ivar_4, (mpz_ptr_t)ivar_5);
        mpz_ptr_t ivar_21;
        mpz_mk_sub(ivar_21, ivar_7, ivar_5);
        result = (strings__string_t)gen_strings__prefix((strings__string_t)ivar_20, (mpz_ptr_t)ivar_21);

        
        return result;
}