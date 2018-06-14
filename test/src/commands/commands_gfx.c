#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(commands_bct_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[6];
	char		str[] = "bct 1 0 1 2 3 4 5 6 7\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_board(&var);
	dummy_t_board_square(var.board[0][1]);
	dummy_t_player_gfx(&var, gfx);
	command_bct(&var, NULL, "1 0");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
	command_bct(&var, NULL, "2 0");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "sbp\n");
	clean_msg_queue(gfx);
	command_bct(&var, NULL, "");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "sbp\n");
	clean_msg_queue(gfx);
	command_bct(&var, NULL, "1");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "sbp\n");
	clean_msg_queue(gfx);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(commands_sst_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[6];

	dummy_t_zappy_without_board(&var);
	dummy_t_player_gfx(&var, gfx);
	command_sst(&var, NULL, "");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "sbp\n");
	clean_msg_queue(gfx);
	command_sst(&var, NULL, "0");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "sbp\n");
	clean_msg_queue(gfx);
	command_sst(&var, NULL, "1");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "sgt 1\n");
	clean_msg_queue(gfx);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(commands_ppo_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	t_player	*gfx = &var.players[6];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	command_ppo(&var, NULL, "");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "sbp\n");
	clean_msg_queue(gfx);
	command_ppo(&var, NULL, "0");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "sbp\n");
	clean_msg_queue(gfx);
	command_ppo(&var, NULL, "5");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "ppo 5 4 3 3\n");
	clean_msg_queue(gfx);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(commands_plv_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	t_player	*gfx = &var.players[6];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	command_plv(&var, NULL, "");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "sbp\n");
	clean_msg_queue(gfx);
	command_plv(&var, NULL, "0");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "sbp\n");
	clean_msg_queue(gfx);
	command_plv(&var, NULL, "5");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "plv 5 1\n");
	clean_msg_queue(gfx);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(commands_pin_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	t_player	*gfx = &var.players[6];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	command_pin(&var, NULL, "");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "sbp\n");
	clean_msg_queue(gfx);
	command_pin(&var, NULL, "0");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "sbp\n");
	clean_msg_queue(gfx);
	command_pin(&var, NULL, "5");
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "pin 5 4 3 10 5 6 7 8 9 10\n");
	clean_msg_queue(gfx);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	commands_gfx(void)
{
	TCase	*tc;

	tc = tcase_create("gfx");
	tcase_add_test(tc, commands_bct_test);
	tcase_add_test(tc, commands_sst_test);
	tcase_add_test(tc, commands_ppo_test);
	tcase_add_test(tc, commands_plv_test);
	tcase_add_test(tc, commands_pin_test);
	return (tc);
}
