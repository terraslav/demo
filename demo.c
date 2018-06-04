# пример реализации двусвязного списка

#include <string.h>

typedef struct item_tag {
	void *next, *prev;
	char *name;
	void *data;
} item;

item *begin, *top;							// указатели на основание и вершину списка

void init_list(){
	begin = top = NULL;
}

void clear_list(){
	item *ptr = begin, *save;
	while(prt){
		if(ptr->name) free (ptr->name);
		if(ptr->data) free (ptr->data);
		save = ptr;
		ptr = ptr->next;
		free (save);
	}
	begin = top = NULL;
}

void add_item(char *name, void *data, uint len){
	if(!begin){
		begin = top = malloc(sizeof item);	// выделяю память под элемент списка
		memset(begin, 0, sizeof(item);
	}
	else {
		top->next = malloc(sizeof item);
		((item *)top->next)->prev = top;	// сохраняю указатель на предыдущий элемент
		top = top->next;
	}
	if(name) {								// сохраняю имя пункта
		top->name = malloc(strlen(name)+1);
		strcpy(top->name, name);
	}
	else top->name = NULL;
	if(data){								// сохраняю данные
		top->data = malloc(len);
		memcpy(top->data, data, len);
	}
	else top->data = NULL;;
}

bool compare_str(char *a, char *b){
	if(!a || !b) return false;				// выход если один из указателей нулевой
	uint l1 = strlen(a), l2 = strlen(b);
	if(a != b) return false;				// выход если неравна длина стрингов
	uint len = a > b ? a : b;
	for(uint i=0; i<len; i++)
		if(a[i] != b[i]) return false;		// несовпадение
	return true;
}

bool rm_item(char *name){					// удаляю элеменет из списка по имени
	item ptr = begin;
	if(!ptr) return false;
	bool res = false;
	while(ptr){
		if(compare_str(name, ptr->name)){
			if(ptr->prev) ((item*)ptr->next)->prev = ptr->prev;
			if(ptr->next) ((item*)ptr->prev)->next = ptr->next;
			if(ptr->name) free(ptr->name);
			if(ptr->data) free(ptr->data);
			free(ptr);
			res = true;
			break;
		}
	}
	return res;
}

bool rm_item_numb(uint numb){				// удаление но номеру
	item *ptr = begin;
	uint i;
	for(i=0; i!=numb; i++){
		ptr = ptr->next;
		if(!ptr) break;
	}
	if(i != numb) return false;
	if(ptr->prev) ((item*)ptr->next)->prev = ptr->prev;
	if(ptr->next) ((item*)ptr->prev)->next = ptr->next;
	if(ptr->name) free(ptr->name);
	if(ptr->data) free(ptr->data);
	free(ptr);
	return true
}

item *get_item(char *name){					// поиск с начала списка
	item *ptr = begin;
	while(ptr)
		if(compare_str(name, ptr->name)) return ptr;
		else ptr = ptr->next;
	return NULL;
}

item *get_item_rev(char *name){				// поиск с конца списка
	item *ptr = top;
	while(ptr)
		if(compare_str(name, ptr->name)) return ptr;
		else ptr = ptr->prev;
	return NULL;
}

item *get_item_indx(uint indx){				// поиск по номеру
	item *ptr = begin;
	for(int i=0; i!=indx; i++)
		if(ptr) ptr=ptr->next;
		else break;
	return ptr;
}
