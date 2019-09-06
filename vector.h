#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/* api prototypes

uint16_t vec_cap(void *);
uint16_t vec_len(void *);
void vec_add_len(void *, uint16_t augment);
void vec_push(void *, item_t x);
void vec_ensure(void *, uint16_t augment);
void vec_free(void *);

uint32_t dvec_cap(void *);
uint32_t dvec_len(void *);
void dvec_add_len(void *, uint32_t augment);
void dvec_push(void *, item_t x);
void dvec_ensure(void *, uint16_t augment);
void dvec_free(void *);

never call (d)vec_add_len before calling (d)vec_ensure, or you'll go out of bounds
*/

/* public api macros */
#define vec_cap(a) ((a) ? vec_cap_raw(a) : 0)
#define vec_len(a) ((a) ? vec_len_raw(a) : 0)
#define vec_add_len(a, n) (vec_len_raw(a) += n)
#define vec_push(a, el) (vec_full(a) ? (*((void **) &(a)) = vec_grow(a, sizeof(*(a)), 1)) : 0,\
	(a[vec_len_raw(a)++] = el), 0 )
//ensure there is room for at least n more elements
#define vec_ensure(a, n) ((n) + vec_len(a) > vec_cap(a) ? \
	(*((void **) &(a)) = vec_grow((a), sizeof(*(a)), (n) + vec_len(a) - vec_cap(a))) :\
	0)
#define vec_free(a) (free((uint16_t *)(a) - 2), *((void **) &(a)) = NULL)

/* implementation details (subject to change) */
#define vec_cap_raw(a) (((uint16_t *)(a))[-2])
#define vec_len_raw(a) (((uint16_t *)(a))[-1]) 
#define vec_full(a) ((a) ? vec_cap_raw(a) == vec_len_raw(a) : true)


//returns true if there is an error
void *vec_grow(void *v, size_t inc, uint16_t augment) {
	uint16_t dcap = vec_cap(v) << 1;
	uint16_t min = vec_len(v) + augment;

	min--;
	min |= min >> 1;
	min |= min >> 2;
	min |= min >> 4;
	min |= min >> 8;
	min++;

	uint16_t ncap = dcap > min ? dcap : min;
	uint16_t *p;
	
	p = realloc(v ? (uint16_t *)(v) - 2 : NULL, 4 + (inc * ncap));
	if (!p) {
		return (void *)-1;
	}

	p += 2;
	vec_cap_raw(p) = ncap;
	
	return p;
}

/* public api macros */
#define dvec_cap(a) ((a) ? dvec_cap_raw(a) : 0)
#define dvec_len(a) ((a) ? dvec_len_raw(a) : 0)
#define dvec_add_len(a, n) (dvec_len_raw(a) += n)
#define dvec_push(a, el) (dvec_full(a) ? (*((void **) &(a)) = dvec_grow(a, sizeof(*(a)), 1)) : 0,\
	(a[dvec_len_raw(a)++] = el), 0 )
//ensure there is room for at least n more elements
#define dvec_ensure(a, n) ((n) + dvec_len(a) > dvec_cap(a) ? \
	(*((void **) &(a)) = dvec_grow((a), sizeof(*(a)), (n) + dvec_len(a) - dvec_cap(a) )) :\
	0)
#define dvec_free(a) (free((uint32_t *)(a) - 2), *((void **) &(a)) = NULL)

/* implementation details (subject to change) */
#define dvec_cap_raw(a) (((uint32_t *)(a))[-2])
#define dvec_len_raw(a) (((uint32_t *)(a))[-1]) 
#define dvec_full(a) ((a) ? dvec_cap_raw(a) == dvec_len_raw(a) : 1)


//returns true if there is an error
void *dvec_grow(void *v, size_t inc, uint16_t augment) {
	uint32_t dcap = dvec_cap(v) * 2;
	uint32_t min = dvec_len(v) + augment;

	min--;
	min |= min >> 1;
	min |= min >> 2;
	min |= min >> 4;
	min |= min >> 8;
	min |= min >> 16;
	min++;

	uint32_t ncap = dcap > min ? dcap : min;
	uint32_t *p;
	
	p = realloc(v ? (uint32_t *)(v) - 2 : NULL, 4 + (inc * ncap));
	if (!p) {
		return (void *)-1;
	}

	p += 2;
	dvec_cap_raw(p) = ncap;
	
	return p;
}
