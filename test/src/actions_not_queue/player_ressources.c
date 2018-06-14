#include <stdlib.h>
#include <check.h>
#include <time.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(action_player_inventaire_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	char		str[] = "{nourriture 10, linemate 5, deraumere 6, sibur 7, "
					"mendiane 8, phiras 9, thystame 10}\n";
	char		gstr[] = "";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	action_player_inventaire(&var, p, NULL);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(p);
	clean_msg_queue(gfx);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(action_player_prend_test)
{
	int			i = 0;
	int			j = 0;
	t_aargs		a;
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	char		ressources[7][16] = {"nourriture", "linemate",
	"deraumere", "sibur", "mendiane", "phiras", "thystame"};
	char		str[] = "ok\n";
	char		gstr[] = "pin 6 0 0 10 0 0 0 0 0 0\nbct 0 0 1 2 3 4 5 6 7\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_board(&var);
	dummy_t_board_square(var.board[0][0]);
	dummy_t_player(&var, p);
	dummy_t_player_gfx(&var, gfx);
	while (i < 6)
	{
		gstr[13 + i * 2] = '1';
		gstr[35 + i * 2] = i + 1 + '0';
		a.str = ressources[i + 1];
		action_player_prend(&var, p, &a);
		ck_assert_str_eq(p->snd.buf[p->snd.read], str);
		ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
		clean_msg_queue(p);
		clean_msg_queue(gfx);
		j = 0;
		while (j < 6)
		{
			ck_assert_int_eq(p->inv[j], (j <= i) ? 1 : 0);
			ck_assert_int_eq(var.board[0][0][j + 1], (j <= i) ? j + 1 : j + 2);
			++j;
		}
		++i;
	}
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(action_player_pose_test)
{
	int			i = 0;
	int			j = 0;
	t_aargs		a;
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	char		ressources[7][16] = {"nourriture", "linemate",
	"deraumere", "sibur", "mendiane", "phiras", "thystame"};
	char		gstr[] = "pin 6 0 0 10 5 6 7 8 9 10\nbct 0 0 0 0 0 0 0 0 0\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	bzero(p->coord, sizeof(int) * 2);
	while (i < 6)
	{
		gstr[13 + i * 2] = i + 4 + '0';
		gstr[36 + i * 2] = '1';
		if (i == 5)
			memmove(gstr + 24, gstr + 25, 25);
		a.str = ressources[i + 1];
		action_player_pose(&var, p, &a);
		ck_assert_str_eq(p->snd.buf[p->snd.read], "ok\n");
		ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
		clean_msg_queue(p);
		clean_msg_queue(gfx);
		j = 0;
		while (j < 6)
		{
			ck_assert_int_eq(p->inv[j], (j <= i) ? j + 4 : j + 5);
			ck_assert_int_eq(var.board[0][0][j + 1], (j <= i) ? 1 : 0);
			++j;
		}
		++i;
	}
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(action_player_prend_pose_nourriture_test)
{
	t_aargs		a;
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	long long	player_initial;
	char		nourriture[] = "nourriture";
	char		inventaire[] = "inventaire";
	char		str[] = "{nourriture 10, linemate 0, deraumere 0, sibur 0, mendiane 0, phiras 0, thystame 0}\nok\n"
		"{nourriture 11, linemate 0, deraumere 0, sibur 0, mendiane 0, phiras 0, thystame 0}\nok\n"
		"{nourriture 10, linemate 0, deraumere 0, sibur 0, mendiane 0, phiras 0, thystame 0}\n";
	char		gstr[] = "bct 1 0 1 2 3 4 5 6 7\npin 6 0 0 11 0 0 0 0 0 0\n"
		"bct 0 0 0 2 3 4 5 6 7\npin 6 0 0 10 0 0 0 0 0 0\nbct 0 0 1 2 3 4 5 6 7\n";

	srand(time(NULL));
	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_board(&var);
	dummy_t_board_square(var.board[0][0]);
	dummy_t_board_square(var.board[0][1]);
	dummy_t_player(&var, p);
	dummy_t_player_gfx(&var, gfx);
	player_initial = p->timeofdeath;
	bzero(&a, sizeof(t_aargs));
	a.str = inventaire;
	action_player_inventaire(&var, p, &a);
	a.str = nourriture;
	action_player_prend(&var, p, &a);
	ck_assert_ptr_ne((void*)player_initial, (void*)p->timeofdeath);
	if (var.board[0][0][0] == 1)
	{
		gstr[4] = '0';
		gstr[55] = '1';
		gstr[102] = '2';
	}
	else
		gstr[8] = '2';
	a.str = inventaire;
	action_player_inventaire(&var, p, &a);
	a.str = nourriture;
	action_player_pose(&var, p, &a);
	a.str = inventaire;
	action_player_inventaire(&var, p, &a);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(p);
	clean_msg_queue(gfx);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	action_player_ressources_test(void)
{
	TCase	*tc;

	tc = tcase_create("player_ressources");
	tcase_add_test(tc, action_player_inventaire_test);
	tcase_add_test(tc, action_player_prend_test);
	tcase_add_test(tc, action_player_pose_test);
	tcase_add_test(tc, action_player_prend_pose_nourriture_test);
	return (tc);
}
