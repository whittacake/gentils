#include "../shared.h"

void help(const char *p) {
	printf(
		"Destroys a file.\n"
		"Usage: %s FILE\n",
		p
	);
	exit(0);
}

int main(int argc, const char **argv) {
	if (argc == 1) help(argv[0]);
	if (g_unlink(argv[1])) {
		perror("unlink");
		exit(1);
	}
	return 0;
}
