#include <check.h>
#include "message_test.h"

Suite*	suite_message_test(void)
{
	Suite	*s;

	s = suite_create("message");
	suite_add_tcase(s, message_update_pos_pointer());
	suite_add_tcase(s, message_add_msg_to_player_lst());
	suite_add_tcase(s, message_add_msg_to_player());
	suite_add_tcase(s, message_rearrange_message_queue());
	return (s);
}
