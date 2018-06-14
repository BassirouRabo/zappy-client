#include <stdlib.h>
#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(player_avance_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	char		str[] = "ok\nok\n";
	char		gstr[] = "ppo 6 0 1 1\nppo 6 1 1 2\n";

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 4;
	var.board_size[1] = 4;
	dummy_t_zappy_add_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_gfx(&var, gfx);
	ck_assert_int_eq(p->coord[0], 0);
	ck_assert_int_eq(p->coord[1], 0);
	ck_assert_int_eq(p->facing, 0);
	action_player_avance(&var, p, NULL);
	ck_assert_int_eq(p->coord[0], 1);
	ck_assert_int_eq(p->coord[1], 0);
	ck_assert_int_eq(p->facing, 0);
	++p->facing;
	action_player_avance(&var, p, NULL);
	ck_assert_int_eq(p->coord[0], 1);
	ck_assert_int_eq(p->coord[1], 1);
	ck_assert_int_eq(p->facing, 1);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(p);
	clean_msg_queue(gfx);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(player_droite_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	char		str[] = "ok\nok\n";
	char		gstr[] = "ppo 6 0 0 2\nppo 6 0 0 3\n";

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 4;
	var.board_size[1] = 4;
	dummy_t_zappy_add_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_gfx(&var, gfx);
	ck_assert_int_eq(p->coord[0], 0);
	ck_assert_int_eq(p->coord[1], 0);
	ck_assert_int_eq(p->facing, 0);
	action_player_droite(&var, p, NULL);
	ck_assert_int_eq(p->coord[0], 0);
	ck_assert_int_eq(p->coord[1], 0);
	ck_assert_int_eq(p->facing, 1);
	action_player_droite(&var, p, NULL);
	ck_assert_int_eq(p->coord[0], 0);
	ck_assert_int_eq(p->coord[1], 0);
	ck_assert_int_eq(p->facing, 2);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(p);
	clean_msg_queue(gfx);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(player_gauche_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	char		str[] = "ok\nok\n";
	char		gstr[] = "ppo 6 0 0 4\nppo 6 0 0 3\n";

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 4;
	var.board_size[1] = 4;
	dummy_t_zappy_add_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_gfx(&var, gfx);
	ck_assert_int_eq(p->coord[0], 0);
	ck_assert_int_eq(p->coord[1], 0);
	ck_assert_int_eq(p->facing, 0);
	action_player_gauche(&var, p, NULL);
	ck_assert_int_eq(p->coord[0], 0);
	ck_assert_int_eq(p->coord[1], 0);
	ck_assert_int_eq(p->facing, 3);
	action_player_gauche(&var, p, NULL);
	ck_assert_int_eq(p->coord[0], 0);
	ck_assert_int_eq(p->coord[1], 0);
	ck_assert_int_eq(p->facing, 2);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(p);
	clean_msg_queue(gfx);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	action_player_moves(void)
{
	TCase	*tc;

	tc = tcase_create("players_moves");
	tcase_add_test(tc, player_avance_test);
	tcase_add_test(tc, player_droite_test);
	tcase_add_test(tc, player_gauche_test);
	return (tc);
}
