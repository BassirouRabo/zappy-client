#include <stdlib.h>
#include <check.h>
#include <stdio.h>
#include <string.h>
#include "serveur.h"
#include "cleanup_test.h"

void	set_dummy_t_zappy(t_zappy *var)
{
	var->board_size[0] = 10;
	var->board_size[1] = 10;
	var->board = gen_board(var->board_size, 10, 10);
	var->teams = (t_team *)malloc(sizeof(t_team) * 2);
	strcpy(var->teams[0].name, "toto");
	strcpy(var->teams[1].name, "tutu");
	var->nb_team = 2;
}

START_TEST(cleanup_game_just_init)
{
	t_zappy		var;
	t_server	serv;

	bzero(&var, sizeof(t_zappy));
	bzero(&serv, sizeof(t_server));
	set_dummy_t_zappy(&var);
	cleanup_game(&var, &serv);
	ck_assert_ptr_eq(NULL, var.teams);
	ck_assert_ptr_eq(NULL, var.board);
}
END_TEST

TCase*	cleanup_cleanup_game(void)
{
	TCase	*tc;

	tc = tcase_create("cleanup_game");
	tcase_add_test(tc, cleanup_game_just_init);
	return (tc);
}
