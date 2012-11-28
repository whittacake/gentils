#include <stdio.h>

int main(int argc, char *argv[])
{
	char *s;
	s = argc <2 ? "y" : argv[1];

	while(1)
		printf("%s\n", s);
}
