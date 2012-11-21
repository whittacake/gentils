#include <stdio.h>
#include <string.h>
#include <dirent.h>

struct arg_list 
{
	int show_hidden;
	char** dir_list;
};

int one(const struct dirent *ent);
void itr_ent(char* dir_name, struct arg_list args);
int no_dot(const struct dirent *ent);

int main(int argc, char** argv) {

	struct arg_list args = {0,0};

	int i;
	for(i = 0; i < argc; i++) {
		//Check for flag
		if(argv[i][0] == '-') {
			int n;
			int slen = strlen(argv[i]);
			//Skip "-" and move to flag content
			for(n = 1; n < slen; n++) {
				switch(argv[i][n]) {
					case 'a':
						args.show_hidden = 1;
				}
			} 
		} else { //not a flag, therefore its a dir to list
		
		}
	}

	itr_ent(argv[1], args);
}

/*
 * Iterate over directory entries
 */
void itr_ent(char* dir_name, struct arg_list args) {
	struct dirent **eps;

	int d;
	if(args.show_hidden == 1) {
		d  = scandir("./", &eps, one, alphasort);
	} else {
		d = scandir("./", &eps, no_dot, alphasort);
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
