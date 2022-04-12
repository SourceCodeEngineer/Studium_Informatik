#include "bstree.h"
#include <float.h>
#include <assert.h>

//#define ERROR printf("IN LINE %d\n", __LINE__)
#define ERROR 

//Stores the nodes//
typedef struct node
{
	value_t value;
	struct node *right;
	struct node *left;
} node;

//Stores a binary tree of values, in wich
typedef struct bstree
{
	struct node *root;
	int size;
} bstree;

bstree *bstree_create();
static node *node_create();
void node_destroy(node *t);
void bstree_destroy(bstree *t);
void bstree_insert(bstree *t, value_t v);
void node_insert(node *t, value_t v);
bool node_contains(const node *t, value_t v);
bool bstree_contains(const bstree *t, value_t v);
void bstree_print(const bstree *t, FILE *out);
void node_print(node *t, FILE *out);

//it creats and returns a new binary tree//
bstree *bstree_create()
{
	bstree *tmp = malloc(sizeof(bstree));
	assert(tmp != NULL);
	tmp->root = NULL;
	tmp->size = 0;
	return tmp;
}

static node *node_create()
{
	node *tmp;
	tmp = malloc(sizeof(node));
	assert(tmp != NULL);
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}

void node_destroy(node *t)
{
	if (t == NULL)
		return;
	node_destroy(t->left);
	node_destroy(t->right);
	free(t);
}

void bstree_destroy(bstree *t)
{
	if (t == NULL)
		return;
	node_destroy(t->root);
	free(t);
}

void bstree_insert(bstree *t, value_t v)
{

	if (t->root == NULL)
	{
		t->root = node_create();
		t->root->value = v;
	}
	else
	{
		node_insert(t->root, v);
	}
}
void node_insert(node *t, value_t v)
{
	if (v > t->value)
	{
		if (t->right == NULL)
		{
			t->right = node_create();
			t->right->value = v;
		}
		else
		{
			node_insert(t->right, v);
		}
	}
	else if (v < t->value)
	{
		if (t->left == NULL)
		{
			t->left = node_create();
			t->left->value = v;
		}
		else
		{
			node_insert(t->left, v);
		}
	}
}

bool node_contains(const node *t, value_t v)
{
	if (t == NULL){
		ERROR;
		return false;}
	else if( t->value == v){
		ERROR;
		return true;}
	else if (v < t->value){
		ERROR;
		return node_contains(t->left, v);
	}
	else if (v > t->value){
		return node_contains(t->right, v);
		ERROR;}
	ERROR;
	return false;
}

bool bstree_contains(const bstree *t, value_t v)
{
	ERROR;
	if (t->root != NULL) //@help this was missing
	{
		if(t->root->value == v)
		{
			ERROR;
			return true;
		}
		else
		{
			ERROR;
			return node_contains(t->root, v);
		}
	}
	else
		return false;
}

void bstree_print(const bstree *t, FILE *out)
{

	if (t == NULL)
	{
		printf("NULL:0");
	}
	node_print(t->root, out);
}
void node_print(node *t, FILE *out)
{
	if (t == NULL)
		return;

	node_print(t->left, out);

	fprintf(out, "%f", t->value);

	node_print(t->right, out);
	printf("\n");
}