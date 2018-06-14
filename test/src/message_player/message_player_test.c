#include <check.h>
#include "message_player_test.h"

Suite*	suite_message_player_test(void)
{
	Suite	*s;

	s = suite_create("message_player");
	suite_add_tcase(s, message_player_test());
	suite_add_tcase(s, message_player_2_test());
	return (s);
}
