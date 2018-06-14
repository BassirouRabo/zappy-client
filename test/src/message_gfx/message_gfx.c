#include <check.h>
#include "message_gfx_test.h"

Suite*	suite_message_gfx_test(void)
{
	Suite	*s;

	s = suite_create("message_gfx");
	suite_add_tcase(s, message_gfx_player());
	suite_add_tcase(s, message_gfx_player_2());
	suite_add_tcase(s, message_gfx_player_3());
	suite_add_tcase(s, message_gfx_server());
	return (s);
}
