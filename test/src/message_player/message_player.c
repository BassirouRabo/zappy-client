#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(message_player_voir_square_test)
{
	int			fd_max = 10;
	int			square[2] = {0, 0};
	t_zappy		var;
	t_player	*p1 = &var.players[5];
	t_player	*p2 = &var.players[6];
	t_player	*p3 = &var.players[7];
	t_player	*p4 = &var.players[8];
	char		str[] = "joueur joueur nourriture linemate linemate deraumere"
		" deraumere deraumere sibur sibur sibur sibur mendiane mendiane mendiane mendiane"
		" mendiane phiras phiras phiras phiras phiras phiras thystame thystame thystame"
		" thystame thystame thystame thystame";

	dummy_t_zappy_without_board(&var);
	var.fd_max = &fd_max;
	dummy_t_zappy_add_board(&var);
	dummy_t_board_square(var.board[0][0]);
	dummy_t_player(&var, p1);
	dummy_t_player(&var, p2);
	dummy_t_player(&var, p3);
	dummy_t_player(&var, p4);
	p3->coord[0] = 1;
	message_player_voir_square(&var, p2, square);
	ck_assert_str_eq(p2->snd.buf[p2->snd.read], str);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
	clean_msg_queue(p2);
}
END_TEST

TCase*	message_player_test(void)
{
	TCase	*tc;

	tc = tcase_create("1");
	tcase_add_test(tc, message_player_voir_square_test);
	return (tc);
}
