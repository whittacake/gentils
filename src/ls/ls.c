#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "ls.h"

int main(int argc, char** argv) {

	//Points to the locations of directories in argv
	char** dl = malloc(argc * sizeof(char**));
	struct arg_list args = {0, NULL};

	int i;
	int j = 0; //Counts location in dir list
	for(i = 1; i < argc; i++) {
		//Check for flag
		if(argv[i][0] == '-') {
			int n;
			int slen = strlen(argv[i]);
			//Skip "-" and move to flag content
			for(n = 1; n < slen; n++) {
				switch(argv[i][n]) {
					// -a: Show .*
					case 'a':
						args.show_hidden = 1;
				}
			} 
		} else { //not a flag, therefore its a dir to list
			dl[j] = argv[i];
			j++;
		}
	}
	dl[j] = NULL;
	args.dir_list = dl;

	/*
	for(i = 0; i < (argc - 1); i++) {
		char* str = args.dir_list[i];
		if(str != NULL) {
			printf("%s\n", str);
		}
	}
	*/

	itr_ent(argv[1], args);
}

/*
 * Iterate over directory entries
 */
void itr_ent(char* dir_name, struct arg_list args) {
	struct dirent **eps;

	// Iterate over each directory in arg_list
	int i = 0;
	while(1) {
		char* dir = args.dir_list[i];
		if(dir == NULL) {
			break;
		}
		int d;
		if(args.show_hidden == 1) {
			d  = scandir(dir, &eps, one, alphasort);
		} else {
			d = scandir(dir, &eps, no_dot, alphasort);
		}
		
		if(d >= 0) {
			int n;
			for(n = 0; n < d; n++) {
				printf("%s  ", eps[n]->d_name);
			}
			printf("\n");
		} else {
			printf("ls: cannot access %s: No such file or directory",
							dir_name);
		}

		i++;
	}
}

int no_dot(const struct dirent *ent) {
	if(ent->d_name[0] != '.') {
		return 1;
	} else {
		return 0;
	}
}

int one(const struct dirent *ent) {
	return 1;
}
