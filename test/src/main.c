#include <stdlib.h>
#include <check.h>
#include "tests.h"

int		main(void)
{
	int		nb_failed;
	SRunner	*sr;

	sr = srunner_create(suite_cleanup());
	srunner_add_suite(sr, suite_l_list());
	srunner_add_suite(sr, suite_arg());
	srunner_add_suite(sr, suite_init_test());
	srunner_add_suite(sr, suite_message_test());
	srunner_add_suite(sr, suite_message_gfx_test());
	srunner_add_suite(sr, suite_message_player_test());
	srunner_add_suite(sr, suite_commands_test());
	srunner_add_suite(sr, suite_actions());
	srunner_add_suite(sr, suite_connexion());
	srunner_add_suite(sr, suite_queue());
	srunner_run_all(sr, CK_NORMAL);
	nb_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	if (nb_failed > 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
