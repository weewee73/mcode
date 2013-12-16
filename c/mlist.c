#include <stdio.h> 
#include <stdlib.h>

/*
typedef struct node_t{
	int data;
	struct node_t *next; 
}node;
typedef node mlist;
*/

typedef struct _mlist mlist;

struct _mlist{
	int data;
	mlist *next;
};

void delete(mlist **list, int data)
{
	mlist **curr = list;
	mlist *p = NULL;

	while ( *curr )
	{
		p = *curr;

		if (p->data == data)
		{
			*curr = p->next;
			free(p);
		}
		else
		{
			curr = &p->next;
		}
	}
}

mlist *delete2(mlist *list, int data)
{
	mlist *curr = list;
	mlist *prev = NULL;
	mlist *next = NULL;

	while ( curr )
	{
		next = curr->next;
		
		if (curr->data == data)
		{
			if (prev) // is not head node
				prev->next = next;
			else
				list = next;
			free(curr);
		}
		else
		{
			prev = curr;
		}

		curr = next;
	}
	return list;
}

mlist *merege(mlist *l1, mlist *l2)
{
	mlist list, *l;

	l = &list;

	while (l1 && l2)
	{
		if (l1->data <= l2->data)
		{
			l = l->next = l1; //l->next = l1, l = l->next;
			l1 = l1->next;
		}
		else
		{
			l = l->next = l2; //l->next = l2, l = l->next;
			l2 = l2->next;
		}
	}
	l->next = l1 ? l1 : l2;

	return list.next;
}

mlist *reverse(mlist *list)
{
	mlist *prev = NULL;
	mlist *next = NULL;

	while (list)
	{
		next = list->next;

		list->next = prev;

		prev = list;
		list = next;
	}

	return prev;
}
