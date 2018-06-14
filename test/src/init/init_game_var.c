#include <stdlib.h>
#include <string.h>
#include <check.h>
#include "serveur.h"

START_TEST(init_game_var_valid)
{
	int					i;
	int					ac = 14;
	char				*av[14] = {"./test", "-p", "1234", "-x", "20", "-y",
		"30", "-n", "toto", "tutu", "-c", "40", "-t", "50"};
	t_zappy		var;
	t_arguments	args;
	t_server	serv;

	bzero(&var, sizeof(t_zappy));
	bzero(&serv, sizeof(t_server));
	bzero(&args, sizeof(t_arguments));
	read_arguments(ac, (const char **)av, &args);
	ck_assert_int_eq(0, init_game_var(&var, &args));
	ck_assert_ptr_ne(NULL, var.board);
	ck_assert_ptr_eq(NULL, var.actions.first);
	ck_assert_ptr_eq(NULL, var.actions.last);
	ck_assert_int_eq(0, var.actions.size);
	ck_assert_ptr_eq(args.teams, var.teams);
	ck_assert_int_eq(args.nb_team, var.nb_team);
	ck_assert_int_eq(args.height, var.board_size[0]);
	ck_assert_int_eq(args.width, var.board_size[1]);
	ck_assert_int_eq((MAX_FD - 4) / (int)args.nb_team, var.team_size);
	ck_assert_int_eq(args.tick, var.tick);
	i = 0;
	while (i < var.nb_team)
	{
		if (i == var.nb_team - 1)
			ck_assert_int_eq(var.teams[i].remain, 1);
		else
			ck_assert_int_eq(var.teams[i].remain, args.nb_clients);
		++i;
	}
	cleanup_game(&var, &serv);
}
END_TEST

TCase*	init_init_game_var(void)
{
	TCase	*tc;

	tc = tcase_create("init_game_var");
	tcase_add_test(tc, init_game_var_valid);
	return (tc);
}
