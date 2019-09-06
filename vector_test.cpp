#include "vector.h"
#include <stdio.h>

int main(int argc, char **argv) {
	uint16_t *vector = NULL;
	for(int i = 0; i < 50; i++) {
		vec_push(vector, i);
	}
	printf("[");
	for(int i = 0; i < vec_len(vector); i++) {
		printf( "%d ", vector[i]);
	}
	printf("]\n");
	printf("cap: %d\nlen: %d\n", vec_cap(vector), vec_len(vector));
	vec_free(vector);
	printf("cap: %d\nlen: %d\n", vec_cap(vector), vec_len(vector));
	vec_ensure(vector, 50);
	printf("cap: %d\nlen: %d\n", vec_cap(vector), vec_len(vector));
	for(int i = 0; i < 50; i++) {
		vector[i] = i << 1;
	}
	vec_add_len(vector, 50);
	printf("cap: %d\nlen: %d\n", vec_cap(vector), vec_len(vector));
	vec_ensure(vector, 50);
	printf("cap: %d\nlen: %d\n", vec_cap(vector), vec_len(vector));
	for(int i = 0; i < 50; i++) {
		vector[50 + i] = (i << 1) + i;
	}
	vec_add_len(vector, 50);
	printf("[");
	for(int i = 0; i < vec_len(vector); i++) {
		printf( "%d ", vector[i]);
	}
	printf("]\n");
	printf("cap: %d\nlen: %d\n", vec_cap(vector), vec_len(vector));
	vec_free(vector);

	uint64_t *dvector = NULL;
	for(int i = 0; i < 50; i++) {
		dvec_push(dvector, i);
	}
	printf("[");
	for(int i = 0; i < dvec_len(dvector); i++) {
		printf( "%d ", dvector[i]);
	}
	printf("]\n");
	printf("cap: %d\nlen: %d\n", dvec_cap(dvector), dvec_len(dvector));
	dvec_free(dvector);
	printf("cap: %d\nlen: %d\n", dvec_cap(dvector), dvec_len(dvector));
	dvec_ensure(dvector, 50);
	printf("cap: %d\nlen: %d\n", dvec_cap(dvector), dvec_len(dvector));
	for(int i = 0; i < 50; i++) {
		dvector[i] = i << 1;
	}
	dvec_add_len(dvector, 50);
	printf("cap: %d\nlen: %d\n", dvec_cap(dvector), dvec_len(dvector));
	dvec_ensure(dvector, 50);
	printf("cap: %d\nlen: %d\n", dvec_cap(dvector), dvec_len(dvector));
	for(int i = 0; i < 50; i++) {
		dvector[50 + i] = (i << 1) + i;
	}
	dvec_add_len(dvector, 50);
	printf("[");
	for(int i = 0; i < dvec_len(dvector); i++) {
		printf( "%d ", dvector[i]);
	}
	printf("]\n");
	printf("cap: %d\nlen: %d\n", dvec_cap(dvector), dvec_len(dvector));
	dvec_free(dvector);
	return 0;
}
