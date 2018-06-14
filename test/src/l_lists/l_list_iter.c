#include <stdio.h>
#include <check.h>
#include "linked_lists_test.h"

static t_lst_head	*push_sample_list()
{	
	t_lst_head	*head;

	head = lst_init(NULL);
	lst_pushback(head, lst_create("Bonjour", 8));
	lst_pushback(head, lst_create("Salut", 6));
	lst_pushback(head, lst_create("Ca va ?", 8));
	lst_pushback(head, lst_create("Au revoir", 10));
	return (head);
}

static int	find_bonjour(void *data, void *data2)
{
	(void)data;
	return (strcmp((char*)data2, "Bonjour"));
}

static int	find_aurevoir(void *data, void *data2)
{
	(void)data;
	return (strcmp((char*)data2, "Au revoir"));
}

static void	free_elem(void* data)
{
	free(data);
}

START_TEST(insert)
{
	t_lst_head	*head;
	t_lst_elem	*new1;
	t_lst_elem	*new3;
	t_lst_elem	*first;
	const char	*str[7] = {"PIERRE!", "Bonjour", "Salut",
							"Ca va ?", "PIERRE!", "Au revoir", NULL};

	head = push_sample_list();
	first = head->first;
	new1 = lst_create("PIERRE!", 8);
	lst_insert(head, new1, find_bonjour);
	ck_assert_ptr_ne(head->first, NULL);
	ck_assert_ptr_eq(head->first, new1);
	ck_assert_ptr_eq(new1->next, first);
	ck_assert_ptr_eq(new1->prev, NULL);

	new3 = lst_create("PIERRE!", 8);
	lst_insert(head, new3, find_aurevoir);
	ck_assert_int_eq(1, check_list(head, str));

	lst_delete(head, free_elem);
	free(head);
}
END_TEST

TCase*	l_list_iter(void)
{
	TCase		*l_list_iter;

	l_list_iter = tcase_create("LINKED LISTS ITER");
	tcase_add_test(l_list_iter, insert);
	return (l_list_iter);
}
