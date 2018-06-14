#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(commands_find_command_unrecognised_command)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "caca\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	find_command(&var, p, str, 4);
	ck_assert_str_eq(p->snd.buf[p->snd.read], "Unrecognised command\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(commands_find_command_unrecognised_command_gfx)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "caca\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	p->status = FD_GFX;
	find_command(&var, p, str, 4);
	ck_assert_str_eq(p->snd.buf[p->snd.read], "suc\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(commands_find_command_command_format_error)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "prend\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	find_command(&var, p, str, 5);
	ck_assert_str_eq(p->snd.buf[p->snd.read], "Command format error\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(commands_find_command_command_format_error_gfx)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "sst\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player_gfx(&var, p);
	find_command(&var, p, str, 3);
	ck_assert_str_eq(p->snd.buf[p->snd.read], "sbp\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(commands_find_command_unauthorised_command)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "msz\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	find_command(&var, p, str, 3);
	ck_assert_str_eq(p->snd.buf[p->snd.read], "Unauthorised command\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(commands_find_command_unauthorised_command_gfx)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "avance\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player_gfx(&var, p);
	find_command(&var, p, str, 6);
	p->status = FD_GFX;
	ck_assert_str_eq(p->snd.buf[p->snd.read], "suc\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	commands_find_command(void)
{
	TCase	*tc;

	tc = tcase_create("find_command");
	tcase_add_test(tc, commands_find_command_unrecognised_command);
	tcase_add_test(tc, commands_find_command_unrecognised_command_gfx);
	tcase_add_test(tc, commands_find_command_command_format_error);
	tcase_add_test(tc, commands_find_command_command_format_error_gfx);
	tcase_add_test(tc, commands_find_command_unauthorised_command);
	tcase_add_test(tc, commands_find_command_unauthorised_command_gfx);
	return (tc);
}
