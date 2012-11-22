#include <stdio.h>

int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		printf("rm: missing operand\n");
		return 0;
	}

	int f = 0, i = 0, r = 0;
	while((argc > 1) && (argv[1][0] == '-'))
	{
		switch(argv[1][1])
		{
			case 'f':
				f = 1;
			break;
			case 'i':
				i = 1;
			break;
			case 'r':
				r = 1;
			break;
			default:
				printf("rm: invalid option -- '%c'\n", argv[1][1]);
				return 0;
			break;
		}

		++argv;
		--argc;
	}

	if(argv[1] == NULL)
	{
		printf("rm: missing operand\n");
		return 0;
	}

	if(i)
	{
		char input[32];
		printf("rm: remove file '%s'? ", argv[1]);
		fgets(input, sizeof(input), stdin);

		if(strcmp(input, "yes"))
		{
			return 0;
		}
	}

	if(remove(argv[1]) != 0)
	{
		printf("rm: cannot remove '%s': No such file or directory\n", argv[1]);
		return 0;
	}
	return 0;
}