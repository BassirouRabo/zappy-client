#include <check.h>
#include <stdio.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(connexion_process_input_normal)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "toto\n";
	char		str2[128];
	char		*ret;

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player(&var, p);
	sprintf(str2, "%d\n%d %d\n", p->team->remain, var.board_size[1], var.board_size[0]);
	p->status = FD_USED;
	p->team = NULL;
	ret = process_input(&var, p, str);
	ck_assert_ptr_eq(p->rcv.remain, NULL);
	ck_assert_ptr_eq(ret, NULL);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str2);
	ck_assert_ptr_eq(p->team, &var.teams[0]);
	ck_assert_int_eq(p->status, FD_CLIENT);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(connexion_process_input_gfx)
{
	int			fd_max = 10;
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "GRAPHIC\n";
	char		str2[128] = "msz 2 2\nsgt 4\nbct 0 0 0 0 0 0 0 0 0\nbct 1 0 0 0 0 0 0 0 0\n" \
					"bct 0 1 0 0 0 0 0 0 0\nbct 1 1 0 0 0 0 0 0 0\ntna toto\ntna tutu\n";
	char		*ret;

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 2;
	var.board_size[1] = 2;
	var.fd_max = &fd_max;
	dummy_t_zappy_add_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player_client(&var, p);
	ret = process_input(&var, p, str);
	ck_assert_ptr_eq(p->rcv.remain, NULL);
	ck_assert_ptr_eq(ret, NULL);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str2);
	ck_assert_ptr_eq(p->team, &var.teams[var.nb_team - 1]);
	ck_assert_int_eq(p->status, FD_GFX);
	rm_teams(&var.teams, &var.nb_team);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
}
END_TEST

START_TEST(connexion_process_input_unkown)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "lol\n";
	char		str2[128] = "EQUIPE INCONNUE\n";
	char		*ret;

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player_client(&var, p);
	ret = process_input(&var, p, str);
	ck_assert_ptr_eq(p->rcv.remain, NULL);
	ck_assert_ptr_eq(ret, NULL);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str2);
	ck_assert_ptr_eq(p->team, NULL);
	ck_assert_int_eq(p->status, FD_CLOSE);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

// This test will evolve when command will be supported
START_TEST(connexion_process_input_multiple_commands)
{
	int			fd_max = 10;
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[30] = "avance\ngauche\navance\n";
	char		str2[128] = "";
	char		*ret;

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 10;
	var.board_size[1] = 10;
	var.fd_max = &fd_max;
	dummy_t_zappy_add_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player(&var, p);
	ret = process_input(&var, p, str);
	ck_assert_ptr_eq(p->rcv.remain, NULL);
	ck_assert_ptr_eq(ret, NULL);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str2);
	rm_teams(&var.teams, &var.nb_team);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
}
END_TEST

START_TEST(connexion_process_input_incomplete_command)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "toto";
	char		*ret;

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player(&var, p);
	ret = process_input(&var, p, str);
	ck_assert_ptr_eq(p->rcv.remain, NULL);
	ck_assert_str_eq(ret, str);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	connexion_process_input(void)
{
	TCase	*tc;

	tc = tcase_create("process_input");
	tcase_add_test(tc, connexion_process_input_normal);
	tcase_add_test(tc, connexion_process_input_gfx);
	tcase_add_test(tc, connexion_process_input_unkown);
	tcase_add_test(tc, connexion_process_input_multiple_commands);
	tcase_add_test(tc, connexion_process_input_incomplete_command);
	return (tc);
}
