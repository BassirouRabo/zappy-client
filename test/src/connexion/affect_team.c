#include <stdlib.h>
#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(connexion_affect_team_valid)
{
	t_zappy		var;
	t_player	*p = &var.players[4];

	dummy_t_zappy_without_board(&var);
	dummy_t_player_client(&var, p);
	dummy_t_zappy_add_remaining_in_team(&var);
	affect_team(&var, p, "tutu", 4);
	ck_assert_ptr_eq(&var.teams[1], p->team);
	ck_assert_int_eq(0, var.teams[1].remain);
	ck_assert_int_eq(FD_CLIENT, p->status);
	ck_assert_str_eq("1\n2 1\n", p->snd.buf[p->snd.write]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(connexion_affect_team_full)
{
	t_zappy		var;
	t_player	*p = &var.players[4];

	dummy_t_zappy_without_board(&var);
	dummy_t_player_client(&var, p);
	var.teams[1].remain = 0;
	affect_team(&var, p, "tutu", 4);
	ck_assert_ptr_eq(p->team, NULL);
	ck_assert_int_eq(var.teams[1].remain, 0);
	ck_assert_int_eq(FD_CLOSE, p->status);
	ck_assert_str_eq("0\n2 1\n", p->snd.buf[p->snd.write]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(connexion_affect_team_unknow)
{
	t_zappy		var;
	t_player	*p = &var.players[4];

	dummy_t_zappy_without_board(&var);
	dummy_t_player_client(&var, p);
	dummy_t_zappy_add_remaining_in_team(&var);
	affect_team(&var, p, "caca", 4);
	ck_assert_ptr_eq(NULL, p->team);
	ck_assert_int_eq(1, var.teams[1].remain);
	ck_assert_str_eq("EQUIPE INCONNUE\n", p->snd.buf[p->snd.write]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(connexion_affect_team_gfx)
{
	int			fd_max = 8;
	t_zappy		var;
	t_player	*gfx = &var.players[4];
	t_player	*p1 = &var.players[5];
	t_player	*p2 = &var.players[6];
	char		str[] = "msz 2 1\nsgt 4\nbct 0 0 0 0 0 0 0 0 0\nbct 1 0 0 0 0 0 0 0 0\n" \
						"tna toto\ntna tutu\npnw 5 4 3 3 1 toto\npnw 6 4 3 3 1 toto\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player_client(&var, gfx);
	dummy_t_player(&var, p1);
	dummy_t_player_default(p1);
	dummy_t_player(&var, p2);
	dummy_t_player_default(p2);
	var.fd_max = &fd_max;
	affect_team(&var, gfx, "GRAPHIC", 7);
	ck_assert_ptr_eq(&var.teams[2], gfx->team);
	ck_assert_int_eq(0, var.teams[2].remain);
	ck_assert_int_eq(FD_GFX, gfx->status);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.write], str);
	ck_assert_ptr_eq(var.gfx_client, gfx);
	rm_teams(&var.teams, &var.nb_team);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	clean_msg_queue(gfx);
}
END_TEST

TCase*	connexion_affect_team(void)
{
	TCase	*tc;

	tc = tcase_create("affect_team");
	tcase_add_test(tc, connexion_affect_team_valid);
	tcase_add_test(tc, connexion_affect_team_full);
	tcase_add_test(tc, connexion_affect_team_unknow);
	tcase_add_test(tc, connexion_affect_team_gfx);
	return (tc);
}
