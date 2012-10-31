#include <stdlib.h>
#include <assert.h>

#include "list.h"
#include "sys.h"

struct list {
	void * data;
	struct list * next;
};

struct list * list_new() {
	return sys_malloc_zero(sizeof(struct list));
}

bool list_end(struct list * node) {
	assert(node && "list error: sentinel gone");
	return (node->next == 0);
}

void * list_data(struct list * node) {
	assert(node && "list error: sentinel gone");
	return node->data;
}

struct list * list_next(struct list * node) {
	assert(node && "list error: sentinel gone");
	if (!node->next) /* reached the sentinel */
		return node;
	return node->next;
}

struct list * list_push_front(struct list * head, void * data) {
	struct list * new = sys_malloc_zero(sizeof(struct list));
	new->data = data;
	new->next = head;
	return new;
}

struct list * list_pop_front(struct list * head) {
	assert(head && "list error: sentinel gone");
	if (!head->next) /* reached the sentinel */
		return head;
	struct list * new = head->next;
	sys_free((void **)&head);
	return new;
}

void list_remove(struct list * node) {
	assert(node && "list error: sentinel gone");
	if (!node->next) /* reached the sentinel */
		return;
	struct list * next = node->next;
	node->next = next->next;
	node->data = next->data;
	sys_free((void **)&next);
}

