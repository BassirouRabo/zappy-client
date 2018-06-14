#include <stdlib.h>
#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(command_player_broadcast_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	t_action	*action;
	char		message[] = "They see me rollin', They hatin'";
	char		gstr[] = "pbc 6 They see me rollin', They hatin'\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player_gfx(&var, gfx);
	dummy_t_player(&var, p);
	command_broadcast(&var, p, message);
	action = find_player_first_action(p, &var);
	ck_assert_ptr_eq(action->run, &action_player_broadcast);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(p);
	clean_msg_queue(gfx);
	action_player_clear(p, &var);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(command_player_incantation_test)
{
	int			i;
	int			fd_max = 10;
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p;
	char		stop_action_incant_start[] = "ko\nelevation en cours\n";
	char		incant_start[] = "elevation en cours\n";
	char		g_str[] = "ppo 9 0 1 1\nppo 9 0 0 1\npic 0 0 1 8 6 9 10\n";

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 2;
	dummy_t_zappy_add_board(&var);
	var.fd_max = &fd_max;
	dummy_t_player_gfx(&var, gfx);
	i = 6;
	while (i <= fd_max)
	{
		dummy_t_player(&var, &var.players[i]);
		var.players[i].level = 1;
		++i;
	}
	var.players[7].coord[0] = 1;
	command_avance(&var, &var.players[9], NULL);
	command_incantation(&var, &var.players[8], NULL);
	i = 6;
	while (i <= fd_max)
	{
		p = &var.players[i];
		if (i == 9)
			ck_assert_str_eq(p->snd.buf[p->snd.read], stop_action_incant_start);
		else if (i == 7)
			ck_assert_str_eq(p->snd.buf[p->snd.read], "");
		else
			ck_assert_str_eq(p->snd.buf[p->snd.read], incant_start);
		action_player_clear(&var.players[i], &var);
		clean_msg_queue(&var.players[i]);
		++i;
	}
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], g_str);
	clean_msg_queue(gfx);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(command_player_expulse_test)
{
	int			i;
	int			fd_max = 12;
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p8 = &var.players[8];
	t_aargs		*args;
	char		g_str[] = "ppo 9 0 1 1\nppo 11 0 0 3\npex 8\nppo 6 1 0 1\nppo 10 1 0 2\nppo 11 1 0 3\nppo 12 1 0 4\n";

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 2;
	var.board_size[1] = 2;
	dummy_t_zappy_add_board(&var);
	var.fd_max = &fd_max;
	dummy_t_player_gfx(&var, gfx);
	i = 6;
	while (i <= fd_max)
	{
		dummy_t_player(&var, &var.players[i]);
		var.players[i].level = 1;
		++i;
	}
	var.players[7].coord[0] = 1;
	var.players[8].facing = 1;
	var.players[10].facing = 1;
	var.players[11].facing = 1;
	var.players[12].facing = 3;
	command_avance(&var, &var.players[9], NULL);
	command_droite(&var, &var.players[11], NULL);
	command_expulse(&var, &var.players[8], NULL);
	ck_assert_int_eq(p8->pending_actions, 1);
	args = &find_player_first_action(p8, &var)->arg;
	ck_assert_int_eq(args->nb, 4);
	i = 6;
	while (i <= fd_max)
	{
		if (i == 6 || i > 9)
			ck_assert_int_eq(args->pl[i], 1);
		else
			ck_assert_int_eq(args->pl[i], 0);
		if (i != 8)
			action_player_clear(&var.players[i], &var);
		clean_msg_queue(&var.players[i]);
		++i;
	}
	action_player_clear(p8, &var);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], g_str);
	clean_msg_queue(gfx);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(command_player_connect_nbr_test)
{
	t_zappy		var;
	t_player	*p = &var.players[6];
	t_action	*action;

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	command_connect_nbr(&var, p, NULL);
	action = find_player_first_action(p, &var);
	ck_assert_ptr_eq(action->run, &action_player_connect_nbr);
	clean_msg_queue(p);
	action_player_clear(p, &var);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	commands_player_life(void)
{
	TCase	*tc;

	tc = tcase_create("player_ressources");
	tcase_add_test(tc, command_player_broadcast_test);
	tcase_add_test(tc, command_player_incantation_test);
	tcase_add_test(tc, command_player_expulse_test);
	tcase_add_test(tc, command_player_connect_nbr_test);
	return (tc);
}
