#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	for(int i = 0; i < argc; ++i) {
		printf("%d: %s\n", i, argv[i]); //if you want to keep the quotes, use a backslash!!!
	}
	return EXIT_SUCCESS;
}