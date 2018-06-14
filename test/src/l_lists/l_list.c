#include <check.h>
#include "linked_lists_test.h"

Suite*	suite_l_list(void)
{
	Suite	*s;

	s = suite_create("l_list");
	suite_add_tcase(s, l_list_basic());
	suite_add_tcase(s, l_list_remove());
	suite_add_tcase(s, l_list_iter());
	return (s);
}
