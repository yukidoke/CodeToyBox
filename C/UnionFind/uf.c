#include <stdio.h>
#include <stdlib.h>

typedef struct uf // Union Find を行う構造体
{
	int *ary;	// 根のデータ
	int *_rank;	// union by rank
}UF;

// UnionFind構造体のポインタと頂点数で初期化
void init(UF *uf, size_t size) {
	uf->ary = (int *)malloc(sizeof(int) * size);
	uf->_rank = (int *)calloc(size, sizeof(int));
	for(size_t i = 0; i < size; i++) uf->ary[i] = i;
}

// v_num の根を返す(経路圧縮)
int root(UF *uf, int v_num) {
	if(uf->ary[v_num] == v_num) return v_num;
	else return v_num = root(uf, uf->ary[v_num]);
}

// union by rank
void merge(UF *uf, int a, int b) {
	if(uf->_rank[a] < uf->_rank[b]) {int tmp = a;a = b;b = tmp;/* swap */}
	uf->ary[b] = root(uf, a);
	if(uf->_rank[a] == uf->_rank[b]) uf->_rank[a]++;
}


int main()
{
	// init test
	int n; scanf("%d", &n);
	UF uf; init(&uf, n);
	for(int i = 0; i < n; i++) {printf("%d ", uf.ary[i]);if(i == n-1)printf("\n");}
	for(int i = 0; i < n; i++) {printf("%d ", uf._rank[i]);if(i == n-1)printf("\n");}

	// union test
	for(int i = 0; i < n / 2; i++) {
		merge(&uf, i, i + n/2);
		for(int j = 0; j < n; j++) {printf("%d ", root(&uf, j));if(j == n-1)printf("\n");}
	}
}