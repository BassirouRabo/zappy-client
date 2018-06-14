#ifndef LINKED_LISTS_TEST_H
# define LINKED_LISTS_TEST_H

# include "linked_lists.h"

TCase*	l_list_basic(void);
TCase*	l_list_remove(void);
TCase*	l_list_iter(void);

int				check_list(t_lst_head *head, const char *str[]);

#endif
