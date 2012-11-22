#ifndef LS_H
#define LS_H

struct arg_list {
	int show_hidden;
	char** dir_list;
};

int one(const struct dirent *ent);
void itr_ent(char* dir_name, struct arg_list args);
int no_dot(const struct dirent *ent);

#endif
