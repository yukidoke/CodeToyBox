#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector {
	size_t max_size;
	size_t now_size;
	int *ary;
}Vector;

void init(Vector *ary, size_t size, int value) {
	ary->now_size = size;
	ary->max_size = size * 2;
	ary->ary = (int *)malloc(sizeof(int) * size * 2);
	for(size_t i = 0; i < size; i++) ary->ary[i] = value;
}

void alloc(Vector *ary) {
	int *tmp = (int *)malloc(sizeof(int) * ary->max_size * 2);
	memcpy(tmp, ary->ary, sizeof(int) * ary->now_size);
	free(ary->ary);
	ary->ary = tmp;
	ary->max_size *= 2;
}

void push(Vector *ary, int value) {
	if(ary->max_size == ary->now_size) alloc(ary);
	ary->ary[ary->now_size++] = value;
}

int pop(Vector *ary) {
	int ret = 0;
	if(ary->now_size) ret = ary->ary[--(ary->now_size)];
	return ret;
}

int cmp(const void *a, const void *b) {
	long A = *(int *)a, B = *(int *)b;
	return (A > B) - (A < B);
}

void sort(Vector *ary) {
	qsort(ary->ary, ary->now_size, sizeof(int), cmp);
}

int main()
{
	Vector ary;
	init(&ary, 10, 0);

	// init test
	printf("Array size: %ld\tMem size: %ld\n", ary.now_size, ary.max_size);
	for(int i = 0; i < ary.now_size; i++) printf("%d ", ary.ary[i]);
	printf("\n\n");

	// push pop test
	push(&ary, 5);
	for(int i = 130; i > 0; i--) push(&ary, i);
	for(int i = ary.now_size - 1; i > 130; i--) printf("%d ", pop(&ary));
	printf("\n\n");

	// sort test
	printf("Array size: %ld\tMem size: %ld\n", ary.now_size, ary.max_size);
	for(int i = 0; i < ary.now_size; i++) printf("%d ", ary.ary[i]);
	printf("\n");
	sort(&ary);
	for(int i = 0; i < ary.now_size; i++) printf("%d ", ary.ary[i]);
	printf("\n");
}