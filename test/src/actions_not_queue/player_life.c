#include <time.h>
#include <stdlib.h>
#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(action_player_incantation_test)
{
	int			i;
	int			fd_max = 13;
	int			pl[MAX_FD];
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p;
	t_aargs		a;
	char		str[] = "niveau actuel : 2\n";
	char		gstr[] = "pie 0 0 1\nplv 6 2\nplv 7 2\nplv 8 2\nplv 9 2\n"
		"plv 10 2\nplv 11 2\nplv 12 2\nplv 13 2\nbct 0 0 0 1 0 0 0 0 0\n"
		"bct 0 0 1 1 3 4 5 6 7\n";

	srand(time(NULL));
	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 10;
	var.board_size[1] = 10;
	var.fd_max = &fd_max;
	dummy_t_zappy_add_board(&var);
	dummy_t_board_square(var.board[0][0]);
	dummy_t_player_gfx(&var, gfx);
	bzero(&a, sizeof(t_aargs));
	bzero(pl, sizeof(int) * MAX_FD);
	i = 6;
	while (i < 14)
	{
		p = &var.players[i];
		dummy_t_player(&var, p);
		p->pending_actions = 10;
		p->level = 1;
		pl[i] = 1;
		++i;
	}
	a.pl = pl;
	a.nb = 1;
	pl[0] = 1;
	action_player_incantation(&var, p, &a);
	i = 6;
	while (i < 14)
	{
		p = &var.players[i];
		ck_assert_str_eq(p->snd.buf[p->snd.read], str);
		ck_assert_int_eq(p->level, 2);
		ck_assert_int_eq(p->pending_actions, 0);
		clean_msg_queue(p);
		++i;
	}
	gstr[82] = gfx->snd.buf[gfx->snd.read][82];
	gstr[84] = gfx->snd.buf[gfx->snd.read][84];
	if (gstr[82] == '0' && gstr[84] == '0')
	{
		gstr[86] = '1';
		gstr[88] = '2';
		gstr[90] = '3';
		gstr[92] = '4';
		gstr[94] = '5';
		gstr[96] = '6';
		gstr[98] = '7';
		gstr[110] = '2';
	}
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(gfx);
	pl[0] = 0;
	action_player_incantation(&var, p, &a);
	i = 6;
	while (i < 14)
	{
		p = &var.players[i];
		ck_assert_int_eq(p->level, 2);
		ck_assert_str_eq(p->snd.buf[p->snd.read], str);
		clean_msg_queue(p);
		++i;
	}
	gstr[8] = '0';
	gstr[78] = '\0';
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(gfx);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(action_player_connect_nbr_test)
{
	t_zappy		var;
	t_player	*p = &var.players[6];
	t_aargs		t;
	char		str[] = "1\n2\n";

	bzero(&t, sizeof(t_aargs));
	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_zappy_add_remaining_in_team(&var);
	action_player_connect_nbr(&var, p, &t);
	dummy_t_zappy_add_remaining_in_team(&var);
	action_player_connect_nbr(&var, p, &t);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(action_player_expulse_test)
{
	int			i;
	int			fd_max = 12;
	int			pl[MAX_FD];
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p8 = &var.players[8];
	t_player	*p;
	t_aargs		args;
	char		str[] = "deplacement 1\n";
	char		gstr[] = "ppo 6 0 0 4\nppo 6 0 1 1\nppo 10 0 1 2\nppo 11 0 1 3\nppo 12 0 1 4\n";

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 2;
	var.board_size[1] = 2;
	var.fd_max = &fd_max;
	dummy_t_zappy_add_board(&var);
	dummy_t_player_gfx(&var, gfx);
	bzero(&args, sizeof(t_aargs));
	bzero(pl, sizeof(int) * MAX_FD);
	args.pl = pl;
	i = 6;
	while (i <= fd_max)
	{
		if (i == 6 || i > 9)
		{
			pl[i] = 1;
			++args.nb;
		}
		dummy_t_player(&var, &var.players[i]);
		var.players[i].level = 1;
		++i;
	}
	var.players[8].facing = 2;
	var.players[10].facing = 1;
	var.players[11].facing = 2;
	var.players[12].facing = 3;
	command_gauche(&var, &var.players[6], NULL);
	action_player_expulse(&var, p8, &args);
	i = 6;
	while (i <= fd_max)
	{
		p = &var.players[i];
		if (i > 9)
			str[12] = (i - 9) * 2 + 1 + '0';
		if (i == 6 || i > 9)
			ck_assert_str_eq(p->snd.buf[p->snd.read], str);
		ck_assert_int_eq(p->pending_actions, 0);
		clean_msg_queue(p);
		++i;
	}
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(gfx);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	action_player_life_test(void)
{
	TCase	*tc;

	tc = tcase_create("player_life");
	tcase_add_test(tc, action_player_incantation_test);
	tcase_add_test(tc, action_player_connect_nbr_test);
	tcase_add_test(tc, action_player_expulse_test);
	return (tc);
}
