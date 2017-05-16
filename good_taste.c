#include <stdio.h>

typedef struct _node
{
	struct _node *next;
	int value;
}node_t;

node_t *creat_list(node_t *head, int total)
{
	node_t *node = NULL;
	node_t *cur_node = NULL;

	if(total <= 0 || head != NULL ) {
		return NULL;
	}
	head = node = (node_t*)malloc(sizeof(node_t));
	node->value = total;
	node->next = NULL;
	total--;
	while(total > 0){
		cur_node = (node_t*)malloc(sizeof(node_t));
		cur_node->value = total;
		node->next = cur_node;
		node = cur_node;
		node->next = NULL;
		total--;
	}
	return head;
}

char clear_list(node_t **head)
{
	node_t *cur = *head;
	while(*head != NULL){
		cur = (*head)->next;
		free(*head);
		*head = cur;
	}
	return 1;
}

node_t *get_node(node_t *head, int index)
{
	while(head != NULL && head->value != index){
		head = head->next;
	}
	return head;
}

//poor taste code, need to test head node
node_t *remove_node_poor(node_t *head, node_t *node)
{
	node_t *prv = NULL;
	node_t *cur = head;

	while(head != NULL && cur != node){
		prv = cur;
		cur = cur->next;
	}
	printf("adr prv = %x, next = %x\n", prv, node->next);
	if(!prv){
		head = node->next;
	} else {
		prv->next = node->next;
	}
	free(node);

	return head;
}


//good taste code, no need to test head node
node_t *remove_node(node_t *head, node_t *node)
{
	node_t **indirect = NULL;
	if(head == NULL)return head;
	indirect = &head;
	while((*indirect) != node){
		indirect = &((*indirect)->next);
	}
	printf("adr prv = %x, next = %x\n", *indirect, node->next);
	*indirect = node->next;
	free(node);

	return head;
}

void print_list(node_t *head)
{
	printf("print start!\n");
	while(head != NULL){
		printf("adr=%x, v=%d\n", (unsigned int)head, head->value);
		head = head->next;
	}
	printf("print end!\n");
}


int main(int argc, char const *argv[])
{
	node_t *list = NULL;
	list = creat_list(list, 5);
	print_list(list);
	// list = remove_node(list, get_node(list, 5));
	list = remove_node_poor(list, get_node(list, 5));
	print_list(list);
	clear_list(&list);
	print_list(list);

	return 0;
}