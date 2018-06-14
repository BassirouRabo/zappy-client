#include <check.h>
#include "serveur.h"

START_TEST(commands_command_match_avance)
{
	ck_assert_int_eq(command_match(get_cmd_list()[0], "avance"), strlen(get_cmd_list()[0].cmd));
	ck_assert_int_eq(command_match(get_cmd_list()[0], "avance 1"), -2);
}
END_TEST

START_TEST(commands_command_match_droite)
{
	ck_assert_int_eq(command_match(get_cmd_list()[1], "droite"), strlen(get_cmd_list()[1].cmd));
	ck_assert_int_eq(command_match(get_cmd_list()[1], "droite 1"), -2);
}
END_TEST

START_TEST(commands_command_match_gauche)
{
	ck_assert_int_eq(command_match(get_cmd_list()[2], "gauche"), strlen(get_cmd_list()[2].cmd));
	ck_assert_int_eq(command_match(get_cmd_list()[2], "gauche 1"), -2);
}
END_TEST

START_TEST(commands_command_match_voir)
{
	ck_assert_int_eq(command_match(get_cmd_list()[3], "voir"), strlen(get_cmd_list()[3].cmd));
	ck_assert_int_eq(command_match(get_cmd_list()[3], "voir 1"), -2);
}
END_TEST

START_TEST(commands_command_match_inventaire)
{
	ck_assert_int_eq(command_match(get_cmd_list()[4], "inventaire"), strlen(get_cmd_list()[4].cmd));
	ck_assert_int_eq(command_match(get_cmd_list()[4], "inventaire 1"), -2);
}
END_TEST

START_TEST(commands_command_match_prend)
{
	ck_assert_int_eq(command_match(get_cmd_list()[5], "prend sibur"), strlen(get_cmd_list()[5].cmd) + 1);
	ck_assert_int_eq(command_match(get_cmd_list()[5], "prend"), -1);
}
END_TEST

START_TEST(commands_command_match_pose)
{
	ck_assert_int_eq(command_match(get_cmd_list()[6], "pose sibur"), strlen(get_cmd_list()[6].cmd) + 1);
	ck_assert_int_eq(command_match(get_cmd_list()[6], "pose"), -1);
}
END_TEST

START_TEST(commands_command_match_expulse)
{
	ck_assert_int_eq(command_match(get_cmd_list()[7], "expulse"), strlen(get_cmd_list()[7].cmd));
	ck_assert_int_eq(command_match(get_cmd_list()[7], "expulse 1"), -2);
}
END_TEST

START_TEST(commands_command_match_broadcast)
{
	ck_assert_int_eq(command_match(get_cmd_list()[8], "broadcast caca"), strlen(get_cmd_list()[8].cmd) + 1);
	ck_assert_int_eq(command_match(get_cmd_list()[8], "broadcast"), -1);
}
END_TEST

START_TEST(commands_command_match_incantation)
{
	ck_assert_int_eq(command_match(get_cmd_list()[9], "incantation"), strlen(get_cmd_list()[9].cmd));
	ck_assert_int_eq(command_match(get_cmd_list()[9], "incantation 1"), -2);
}
END_TEST

START_TEST(commands_command_match_fork)
{
	ck_assert_int_eq(command_match(get_cmd_list()[10], "fork"), strlen(get_cmd_list()[10].cmd));
	ck_assert_int_eq(command_match(get_cmd_list()[10], "fork 1"), -2);
}
END_TEST

START_TEST(commands_command_match_connect_nbr)
{
	ck_assert_int_eq(command_match(get_cmd_list()[11], "connect_nbr"), strlen(get_cmd_list()[11].cmd));
	ck_assert_int_eq(command_match(get_cmd_list()[11], "connect_nbr 1"), -2);
}
END_TEST

START_TEST(commands_command_match_msz)
{
	ck_assert_int_eq(command_match(get_cmd_list()[12], "msz"), strlen(get_cmd_list()[12].cmd));
	ck_assert_int_eq(command_match(get_cmd_list()[12], "msz 1"), -2);
}
END_TEST

START_TEST(commands_command_match_bct)
{
	ck_assert_int_eq(command_match(get_cmd_list()[13], "bct X Y"), strlen(get_cmd_list()[13].cmd) + 1);
	ck_assert_int_eq(command_match(get_cmd_list()[13], "bct"), -1);
}
END_TEST

START_TEST(commands_command_match_mct)
{
	ck_assert_int_eq(command_match(get_cmd_list()[14], "mct"), strlen(get_cmd_list()[14].cmd));
	ck_assert_int_eq(command_match(get_cmd_list()[14], "mct 1"), -2);
}
END_TEST

START_TEST(commands_command_match_tna)
{
	ck_assert_int_eq(command_match(get_cmd_list()[15], "tna"), strlen(get_cmd_list()[15].cmd));
	ck_assert_int_eq(command_match(get_cmd_list()[15], "tna 1"), -2);
}
END_TEST

START_TEST(commands_command_match_ppo)
{
	ck_assert_int_eq(command_match(get_cmd_list()[16], "ppo 4"), strlen(get_cmd_list()[16].cmd) + 1);
	ck_assert_int_eq(command_match(get_cmd_list()[16], "ppo"), -1);
}
END_TEST

START_TEST(commands_command_match_plv)
{
	ck_assert_int_eq(command_match(get_cmd_list()[17], "plv 4"), strlen(get_cmd_list()[17].cmd) + 1);
	ck_assert_int_eq(command_match(get_cmd_list()[17], "plv"), -1);
}
END_TEST

START_TEST(commands_command_match_pin)
{
	ck_assert_int_eq(command_match(get_cmd_list()[18], "pin 5"), strlen(get_cmd_list()[18].cmd) + 1);
	ck_assert_int_eq(command_match(get_cmd_list()[18], "pin"), -1);
}
END_TEST

START_TEST(commands_command_match_sgt)
{
	ck_assert_int_eq(command_match(get_cmd_list()[19], "sgt"), strlen(get_cmd_list()[19].cmd));
	ck_assert_int_eq(command_match(get_cmd_list()[19], "sgt 1"), -2);
}
END_TEST

START_TEST(commands_command_match_sst)
{
	ck_assert_int_eq(command_match(get_cmd_list()[20], "sst 4"), strlen(get_cmd_list()[20].cmd) + 1);
	ck_assert_int_eq(command_match(get_cmd_list()[20], "sst"), -1);
}
END_TEST

TCase*	commands_command_match(void)
{
	TCase	*tc;

	tc = tcase_create("commands");
	tcase_add_test(tc, commands_command_match_avance);
	tcase_add_test(tc, commands_command_match_droite);
	tcase_add_test(tc, commands_command_match_gauche);
	tcase_add_test(tc, commands_command_match_voir);
	tcase_add_test(tc, commands_command_match_inventaire);
	tcase_add_test(tc, commands_command_match_prend);
	tcase_add_test(tc, commands_command_match_pose);
	tcase_add_test(tc, commands_command_match_expulse);
	tcase_add_test(tc, commands_command_match_broadcast);
	tcase_add_test(tc, commands_command_match_incantation);
	tcase_add_test(tc, commands_command_match_fork);
	tcase_add_test(tc, commands_command_match_connect_nbr);
	tcase_add_test(tc, commands_command_match_msz);
	tcase_add_test(tc, commands_command_match_bct);
	tcase_add_test(tc, commands_command_match_mct);
	tcase_add_test(tc, commands_command_match_tna);
	tcase_add_test(tc, commands_command_match_ppo);
	tcase_add_test(tc, commands_command_match_plv);
	tcase_add_test(tc, commands_command_match_pin);
	tcase_add_test(tc, commands_command_match_sgt);
	tcase_add_test(tc, commands_command_match_sst);
	return (tc);
}
