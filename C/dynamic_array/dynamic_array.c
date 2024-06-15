#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	_ から始まる変数・関数は、機能及び動作を理解していない限り触らないでください
*/

typedef struct vector {
	size_t _max_size;
	size_t size;
	int *ary;

	void (*push)(struct vector *, int);
	int (*pop)(struct vector *);
}Vector;

void _alloc(Vector *ary) {
	int *tmp = (int *)malloc(sizeof(int) * ary->_max_size * 2);
	memcpy(tmp, ary->ary, sizeof(int) * ary->size);
	free(ary->ary);
	ary->ary = tmp;
	ary->_max_size *= 2;
}

void _push(Vector *ary, int value) {
	if(ary->_max_size == ary->size) _alloc(ary);
	ary->ary[ary->size++] = value;
}

int _pop(Vector *ary) {
	int ret = 0;
	if(ary->size) ret = ary->ary[--(ary->size)];
	return ret;
}

int _cmp(const void *a, const void *b) {
	long A = *(int *)a, B = *(int *)b;
	return (A > B) - (A < B);
}

void sort(Vector *ary) {
	qsort(ary->ary, ary->size, sizeof(int), _cmp);
}

void init(Vector *ary, size_t size, int value) {
	ary->size = size;
	ary->_max_size = size * 2;
	ary->ary = (int *)malloc(sizeof(int) * size * 2);
	for(size_t i = 0; i < size; i++) ary->ary[i] = value;
	ary->push = _push;
	ary->pop = _pop;
}

int main()
{
	Vector ary;
	init(&ary, 10, 0);

	// init test
	printf("Array size: %ld\tMem size: %ld\n", ary.size, ary._max_size);
	for(int i = 0; i < ary.size; i++) printf("%d ", ary.ary[i]);
	printf("\n\n");

	// push pop test
	ary.push(&ary, 5);
	for(int i = 130; i > 0; i--) ary.push(&ary, i);
	for(int i = ary.size - 1; i > 130; i--) printf("%d ", ary.pop(&ary));
	printf("\n\n");

	// sort test
	printf("Array size: %ld\tMem size: %ld\n", ary.size, ary._max_size);
	for(int i = 0; i < ary.size; i++) printf("%d ", ary.ary[i]);
	printf("\n");
	sort(&ary);
	for(int i = 0; i < ary.size; i++) printf("%d ", ary.ary[i]);
	printf("\n");
}