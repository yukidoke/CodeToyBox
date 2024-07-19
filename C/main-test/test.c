#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {

	// main関数の第三引数を確認するテスト
	for(int i = 0; envp[i]; i++) {
		printf("%s\n", envp[i]);
	}

	return 0;
}