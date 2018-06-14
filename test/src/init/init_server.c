#include <stdlib.h>
#include <string.h>
#include <check.h>
#include "serveur.h"

START_TEST(init_server_valid)
{
	int					ac = 14;
	char				*av[14] = {"./test", "-p", "1234", "-x", "20", "-y",
		"30", "-n", "toto", "tutu", "-c", "40", "-t", "50"};
	t_zappy		var;
	t_arguments	args;
	t_server	serv;

	bzero(&serv, sizeof(t_server));
	bzero(&args, sizeof(t_arguments));
	read_arguments(ac, (const char **)av, &args);
	ck_assert_msg(0 == init_game_var(&var, &args), "Error while initating "
		"test variable");
	ck_assert_int_eq(0, init_server(&var, &serv, &args));
	ck_assert_int_eq(args.port, serv.port);
	ck_assert_int_eq(serv.sock, serv.fd_max);
	ck_assert_int_eq(0, serv.fd_sel);
	ck_assert_int_eq(FD_SERVER, var.players[serv.sock].status);
	cleanup_game(&var, &serv);
}
END_TEST

TCase*	init_init_server(void)
{
	TCase	*tc;

	tc = tcase_create("init_server");
	tcase_add_test(tc, init_server_valid);
	return (tc);
}
