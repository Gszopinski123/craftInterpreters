#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct node {
	char * string;
	struct node* next;
	struct node* prev;
} Node;
typedef struct list {
	struct node* head;
	struct node* tail;
	int len;
	void (*insert)(char*,struct list*);
	void (*delete)(int,struct list*);
	int (*find)(char*,struct list*);
} List;
int find(char* string, struct list* lst);
void insert(char* string,struct list* lst);
void delete(int index, struct list* lst);
int main(int argc, char** argv) {
	List *lst = malloc(sizeof(List));
	lst->insert = insert;
	lst->delete = delete;
	lst->find = find;
	lst->len = 0;
	char * str1 = malloc(10);
	char * str2 = malloc(10);
	char * str3 = malloc(10);
	str2 = "Perhaps";
	str3 = "node";
	str1 = "Hello!";
	lst->insert(str1, lst);	
	lst->insert(str2, lst);
	lst->insert(str3, lst);
	printf("%d\n",lst->find(str2,lst));
	return 0;

}
int find(char* string, struct list* lst) {
	if (lst->len == 0) {
		return -1;
	}		
	int count = 0;
	Node *node = lst->head;
	while (node != NULL) {
		if (!strcmp(node->string, string))
			return count;
		count++;
		node = node->next;
	}
	return -1;

}

void delete(int index, struct list* lst) {
	if (index >= lst->len) {	
		return ;
	}
	Node *node = lst->head;
	int originalIndex = index;
	while (index != 0) {
		index--;
		node = node->next;
	}
	if (originalIndex == 0) {
		lst->head = node->next;
		lst->head->prev = NULL;
		if (lst->len == 1)
			lst->tail = NULL;
	}
	if (originalIndex == lst->len-1 && lst->len-1 != 0)
		lst->tail = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	lst->len--;
	free(node);
	return;

}
void insert(char* string,struct list* lst) {
	lst->len++;
	Node *node = malloc(sizeof(Node));
	node->string = string;
	node->next = NULL;
	node->prev = NULL;	
	if (lst->head == NULL) {
		lst->head = node;
		lst->tail = node;
		return;	
	}	
	lst->tail->next = node;
	lst->tail->next->prev = lst->tail;
	lst->tail = lst->tail->next;
	return;
}
