#include <check.h>
#include "test_connexion.h"

Suite*	suite_connexion(void)
{
	Suite	*s;

	s = suite_create("connexion");
	suite_add_tcase(s, connexion_close_client());
	suite_add_tcase(s, connexion_client_error());
	suite_add_tcase(s, connexion_affect_team());
	suite_add_tcase(s, connexion_process_input());
	suite_add_tcase(s, connexion_read_buffer());
	suite_add_tcase(s, connexion_do_read());
	suite_add_tcase(s, connexion_do_write());
	return (s);
}
