#include <check.h>
#include "linked_lists_test.h"

t_lst_head	*sample_list(void (*add)(t_lst_head*, t_lst_elem*))
{	
	t_lst_head	*head;

	head = lst_init(NULL);
	add(head, lst_create("Bonjour", 8));
	add(head, lst_create("Salut", 6));
	add(head, lst_create("Ca va ?", 8));
	add(head, lst_create("A+", 3));
	return (head);
}

void	free_elem(t_lst_elem	**elem)
{
	free((*elem)->content);
	free(*elem);
	*elem = NULL;
}

START_TEST(create_elem)
{
	t_lst_elem		*elem;
	char			str[] = "Bonjour";
	char			*content;

	elem = lst_create(str, strlen(str) + 1);
	ck_assert_msg(elem != NULL, "elem could not be created");
	ck_assert_ptr_ne(str, elem->content);
	ck_assert_ptr_eq(NULL, elem->prev);
	ck_assert_ptr_eq(NULL, elem->next);

	ck_assert_str_eq("Bonjour", (char*)elem->content);
	content = (char*)elem->content;
	content[0] = 'C';
	ck_assert_str_eq("Conjour", (char*)elem->content);
	free_elem(&elem);
}
END_TEST

START_TEST(init_head)
{
	t_lst_head		*head;
	char			str1[] = "Trololo1";
	char			str2[] = "42";
	t_lst_elem		*elem1;
	t_lst_elem		*elem2;

	elem1 = lst_create(str1, strlen(str1) + 1);
	elem2 = lst_create(str2, strlen(str2) + 1);

	// check empty list
	head = lst_init(NULL);
	ck_assert_int_eq(0, head->size);
	free(head);

	// check size == 1
	head = lst_init(elem1);
	ck_assert_ptr_eq(head->first, head->last);
	ck_assert_int_eq(1, head->size);
	free(head);

	// check size == 2
	elem1->next = elem2;
	elem2->prev = elem1;
	head = lst_init(elem1);
	ck_assert_int_eq(2, head->size);
	ck_assert_ptr_eq(elem2, head->last);
	free(head);

	free_elem(&elem1);
	free_elem(&elem2);
}
END_TEST

START_TEST(pushfront)
{
	t_lst_head	*head;
	t_lst_elem	*to_free;
	const char	*str[5] = {"A+", "Ca va ?", "Salut", "Bonjour", NULL};

	head = sample_list(lst_pushfront);

	//head == NULL
	lst_pushfront(NULL, NULL);

	ck_assert_int_eq(1, check_list(head, str));
	ck_assert_int_eq(4, head->size);

	while (head->first)
	{
		to_free = head->first;
		head->first = head->first->next;
		free_elem(&to_free);
	}
	free(head);
}
END_TEST

START_TEST(pushback)
{
	t_lst_head	*head;
	t_lst_elem	*to_free;
	const char	*str[5] = {"Bonjour", "Salut", "Ca va ?", "A+", NULL};

	head = sample_list(lst_pushback);

	//head == NULL
	lst_pushback(NULL, NULL);

	ck_assert_int_eq(1, check_list(head, str));
	ck_assert_int_eq(4, head->size);

	while (head->first)
	{
		to_free = head->first;
		head->first = head->first->next;
		free_elem(&to_free);
	}
	free(head);
}
END_TEST

TCase*		l_list_basic(void)
{
	TCase		*l_list_basic;

	l_list_basic = tcase_create("LINKED LISTS BASIC");
	tcase_add_test(l_list_basic, init_head);
	tcase_add_test(l_list_basic, create_elem);
	tcase_add_test(l_list_basic, pushfront);
	tcase_add_test(l_list_basic, pushback);
	return (l_list_basic);
}
