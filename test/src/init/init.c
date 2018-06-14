#include <check.h>
#include "init_test.h"

Suite*	suite_init_test(void)
{
	Suite	*s;

	s = suite_create("init");
	suite_add_tcase(s, init_init_game_var());
	suite_add_tcase(s, init_init_server());
	return (s);
}
