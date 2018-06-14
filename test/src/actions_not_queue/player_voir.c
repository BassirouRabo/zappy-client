#include <stdlib.h>
#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(action_player_voir_test_1_0)
{
	int			fd_max = 10;
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[] = "{nourriture, linemate, deraumere, sibur}\n";

	dummy_t_zappy_without_board(&var);
	var.fd_max = &fd_max;
	var.board_size[0] = 10;
	var.board_size[1] = 10;
	dummy_t_zappy_add_board(&var);
	dummy_t_player(&var, p);
	p->coord[1] = 4;
	p->level = 1;
	var.board[0][4][0] = 1;
	var.board[1][3][1] = 1;
	var.board[1][4][2] = 1;
	var.board[1][5][3] = 1;
	action_player_voir(&var, p, NULL);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	clean_msg_queue(p);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(action_player_voir_test_1_1)
{
	int			fd_max = 10;
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[] = "{nourriture, linemate, deraumere, sibur}\n";

	dummy_t_zappy_without_board(&var);
	var.fd_max = &fd_max;
	var.board_size[0] = 10;
	var.board_size[1] = 10;
	dummy_t_zappy_add_board(&var);
	dummy_t_player(&var, p);
	p->coord[1] = 4;
	p->facing = 1;
	p->level = 1;
	var.board[0][4][0] = 1;
	var.board[1][5][1] = 1;
	var.board[0][5][2] = 1;
	var.board[9][5][3] = 1;
	action_player_voir(&var, p, NULL);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	clean_msg_queue(p);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(action_player_voir_test_1_2)
{
	int			fd_max = 10;
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[] = "{nourriture, linemate, deraumere, sibur}\n";

	dummy_t_zappy_without_board(&var);
	var.fd_max = &fd_max;
	var.board_size[0] = 10;
	var.board_size[1] = 10;
	dummy_t_zappy_add_board(&var);
	dummy_t_player(&var, p);
	p->coord[1] = 4;
	p->facing = 2;
	p->level = 1;
	var.board[0][4][0] = 1;
	var.board[9][5][1] = 1;
	var.board[9][4][2] = 1;
	var.board[9][3][3] = 1;
	action_player_voir(&var, p, NULL);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	clean_msg_queue(p);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(action_player_voir_test_1_3)
{
	int			fd_max = 10;
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[] = "{nourriture, linemate, deraumere, sibur}\n";

	dummy_t_zappy_without_board(&var);
	var.fd_max = &fd_max;
	var.board_size[0] = 10;
	var.board_size[1] = 10;
	dummy_t_zappy_add_board(&var);
	dummy_t_player(&var, p);
	p->coord[1] = 4;
	p->facing = 3;
	p->level = 1;
	var.board[0][4][0] = 1;
	var.board[9][3][1] = 1;
	var.board[0][3][2] = 1;
	var.board[1][3][3] = 1;
	action_player_voir(&var, p, NULL);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	clean_msg_queue(p);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(action_player_voir_test_3_0)
{
	int			fd_max = 10;
	t_zappy		var;
	t_player	*p1 = &var.players[5];
	t_player	*p2 = &var.players[6];
	t_player	*p3 = &var.players[7];
	char		str[] = "{nourriture, linemate, joueur deraumere, sibur, mendiane, phiras,"
				" thystame, nourriture, linemate, deraumere, sibur, mendiane, phiras,"
				" thystame, nourriture, joueur linemate}\n";

	dummy_t_zappy_without_board(&var);
	var.fd_max = &fd_max;
	var.board_size[0] = 10;
	var.board_size[1] = 10;
	dummy_t_zappy_add_board(&var);
	dummy_t_player(&var, p1);
	dummy_t_player(&var, p2);
	dummy_t_player(&var, p3);
	p1->level = 3;
	var.board[0][0][0] = 1;
	var.board[1][9][1] = 1;
	var.board[1][0][2] = 1;
	var.board[1][1][3] = 1;

	var.board[2][8][4] = 1;
	var.board[2][9][5] = 1;
	var.board[2][0][6] = 1;
	var.board[2][1][0] = 1;
	var.board[2][2][1] = 1;

	var.board[3][7][2] = 1;
	var.board[3][8][3] = 1;
	var.board[3][9][4] = 1;
	var.board[3][0][5] = 1;
	var.board[3][1][6] = 1;
	var.board[3][2][0] = 1;
	var.board[3][3][1] = 1;
	p2->coord[0] = 1;
	p3->coord[0] = 3;
	p3->coord[1] = 3;
	action_player_voir(&var, p1, NULL);
	ck_assert_str_eq(p1->snd.buf[p1->snd.read], str);
	clean_msg_queue(p1);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	action_player_voir_test(void)
{
	TCase	*tc;

	tc = tcase_create("player_voir");
	tcase_add_test(tc, action_player_voir_test_1_0);
	tcase_add_test(tc, action_player_voir_test_1_1);
	tcase_add_test(tc, action_player_voir_test_1_2);
	tcase_add_test(tc, action_player_voir_test_1_3);
	tcase_add_test(tc, action_player_voir_test_3_0);
	return (tc);
}
