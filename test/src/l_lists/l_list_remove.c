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

static int		cmp_eq(void *data1, void *data2)
{
	return (!strcmp((char*)data1, (char*)data2));
}

static int		cmp_ne(void *data1, void *data2)
{
	return (strcmp((char*)data1, (char*)data2));
}

static void		simple_free(void *simple)
{
	free(simple);
}

START_TEST(delete_elem)
{
	t_lst_elem	*elem;

	elem = NULL;
	lst_delete_elem(&elem, simple_free);
	ck_assert_ptr_eq(NULL, elem);

	elem = lst_create("Bonjour", 8);
	lst_delete_elem(&elem, simple_free);
	ck_assert_ptr_eq(NULL, elem);
}
END_TEST

START_TEST(test_remove)
{
	t_lst_head	*head;
	t_lst_elem	*removed;
	t_lst_elem	*second;
	t_lst_elem	*third;
	t_lst_elem	*last;

	head = push_sample_list();
	second = head->first->next;
	third = head->first->next->next;

	ck_assert_ptr_eq(NULL, lst_remove(NULL, NULL));
	removed = lst_remove(head, second);
	ck_assert_str_eq((char*)removed->content, "Salut");
	ck_assert_str_eq((char*)head->first->next->content, "Ca va ?");
	ck_assert_ptr_eq(third->prev, head->first);
	ck_assert_int_eq(3, head->size);
	lst_delete_elem(&removed, simple_free);

	last = head->last;
	removed = lst_remove(head, head->last);
	ck_assert_ptr_eq(removed, last);
	ck_assert_ptr_eq(head->last, third);
	ck_assert_ptr_eq(head->last->prev, head->first);
	ck_assert_ptr_eq(head->first->next, third);
	ck_assert_int_eq(2, head->size);
	lst_delete_elem(&removed, simple_free);

	removed = lst_remove(head, third);
	ck_assert_ptr_eq(removed, third);
	ck_assert_ptr_eq(head->last, head->first);
	ck_assert_ptr_eq(head->last->next, NULL);
	ck_assert_int_eq(1, head->size);
	lst_delete_elem(&removed, simple_free);

	removed = lst_remove(head, head->first);
	ck_assert_ptr_eq(head->first, NULL);
	ck_assert_ptr_eq(head->last, NULL);
	ck_assert_int_eq(0, head->size);
	lst_delete_elem(&removed, simple_free);
	free(head);
}
END_TEST

START_TEST(delete_list)
{
	t_lst_head	*head;	

	head = push_sample_list();

	ck_assert_str_eq("Bonjour", (char*)head->first->content);
	ck_assert_str_eq("Au revoir", (char*)head->last->content);
	ck_assert_int_eq(4, head->size);
	lst_delete(head, simple_free);
	ck_assert_ptr_eq(NULL, head->first);
	ck_assert_ptr_eq(NULL, head->last);
	ck_assert_int_eq(0, head->size);
	free(head);
}
END_TEST

START_TEST(pop)
{
	t_lst_head	*head;
	t_lst_elem	*elem;

	head = push_sample_list();

	elem = lst_pop(head, 0);
	ck_assert_str_eq("Bonjour", (char*)elem->content);
	ck_assert_str_eq("Salut", (char*)head->first->content);
	lst_delete_elem(&elem, simple_free);
}
END_TEST

START_TEST(free_match)
{
	t_lst_head	*head;
	const char	*str[4] = {"Salut", "Ca va ?", "Au revoir", NULL};

	head = push_sample_list();
	lst_free_match(head, "Salut", cmp_ne, simple_free);	
	ck_assert_ptr_ne(NULL, head->first);
	ck_assert_ptr_eq(head->first, head->last);
	ck_assert_str_eq("Salut", (char*)head->first->content);
	ck_assert_str_eq("Salut", (char*)head->last->content);

	lst_free_match(head, "Salut", cmp_eq, simple_free);	
	ck_assert_ptr_eq(NULL, head->first);
	ck_assert_ptr_eq(head->first, head->last);
	free(head);
	
	head = push_sample_list();
	lst_free_match(head, "Bonjour", cmp_eq, simple_free);	
	ck_assert_int_eq(1, check_list(head, str));
	lst_delete(head, simple_free);
	free(head);
}
END_TEST

TCase*	l_list_remove(void)
{
	TCase		*l_list_remove;

	l_list_remove = tcase_create("LINKED LISTS REMOVE");
	tcase_add_test(l_list_remove, delete_elem);
	tcase_add_test(l_list_remove, test_remove);
	tcase_add_test(l_list_remove, delete_list);
	tcase_add_test(l_list_remove, pop);
	tcase_add_test(l_list_remove, free_match);
	return (l_list_remove);
}
