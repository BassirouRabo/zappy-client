#include <check.h>
#include "linked_lists_test.h"

int		check_list(t_lst_head *head, const char *str[])
{
	t_lst_elem	*cursor;
	t_lst_elem	*cursor_end;
	int			i;

	i = 0;
	cursor = head->first;
	while (cursor)
	{
		if (strcmp((char*)cursor->content, str[i]) != 0)
			return (0);
		i++;
		if (!cursor->next)
			cursor_end = cursor;
		cursor = cursor->next;
	}
	while (cursor_end)
	{
		if (strcmp((char*)cursor_end->content, str[--i]) != 0)
			return (0);
		cursor_end = cursor_end->prev;
	}
	return (1);
}
