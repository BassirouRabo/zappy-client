#include <stdlib.h>
#include <check.h>
#include "serveur.h"

START_TEST(arg_get_opt_int_port_valid)
{
	int					i = 0;
	t_arguments			args;
	char				*av[5] = {"-p", "1234", "-n", "tutu", NULL};
	const t_main_arg	dummy = {4, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(0, get_opt_int(dummy, &i, 0, &args));
	ck_assert_int_eq(1234, args.port);
	ck_assert_int_eq(0, args.width);
	ck_assert_int_eq(0, args.height);
	ck_assert_int_eq(0, args.nb_clients);
	ck_assert_int_eq(0, args.tick);
	ck_assert_int_eq(2, i);
}
END_TEST

START_TEST(arg_get_opt_int_port_missing)
{
	int					i = 0;
	t_arguments			args;
	char				*av[4] = {"-p", "-n", "tutu", NULL};
	const t_main_arg	dummy = {3, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(1, get_opt_int(dummy, &i, 0, &args));
	ck_assert_int_eq(0, args.port);
	ck_assert_int_eq(0, args.width);
	ck_assert_int_eq(0, args.height);
	ck_assert_int_eq(0, args.nb_clients);
	ck_assert_int_eq(0, args.tick);
	ck_assert_int_eq(1, i);
}
END_TEST

START_TEST(arg_get_opt_int_port_invalid)
{
	int					i = 0;
	t_arguments			args;
	char				*av[5] = {"-p", "-1234", "-n", "tutu", NULL};
	const t_main_arg	dummy = {4, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(1, get_opt_int(dummy, &i, 0, &args));
	ck_assert_int_eq(0, args.port);
	ck_assert_int_eq(0, args.width);
	ck_assert_int_eq(0, args.height);
	ck_assert_int_eq(0, args.nb_clients);
	ck_assert_int_eq(0, args.tick);
	ck_assert_int_eq(2, i);
}
END_TEST

START_TEST(arg_get_opt_int_width_valid)
{
	int					i = 0;
	t_arguments			args;
	char				*av[5] = {"-x", "1234", "-n", "tutu", NULL};
	const t_main_arg	dummy = {4, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(0, get_opt_int(dummy, &i, 1, &args));
	ck_assert_int_eq(0, args.port);
	ck_assert_int_eq(1234, args.width);
	ck_assert_int_eq(0, args.height);
	ck_assert_int_eq(0, args.nb_clients);
	ck_assert_int_eq(0, args.tick);
	ck_assert_int_eq(2, i);
}
END_TEST

START_TEST(arg_get_opt_int_width_missing)
{
	int					i = 0;
	t_arguments			args;
	char				*av[4] = {"-x", "-n", "tutu", NULL};
	const t_main_arg	dummy = {3, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(1, get_opt_int(dummy, &i, 1, &args));
	ck_assert_int_eq(0, args.port);
	ck_assert_int_eq(0, args.width);
	ck_assert_int_eq(0, args.height);
	ck_assert_int_eq(0, args.nb_clients);
	ck_assert_int_eq(0, args.tick);
	ck_assert_int_eq(1, i);
}
END_TEST

START_TEST(arg_get_opt_int_width_invalid)
{
	int					i = 0;
	t_arguments			args;
	char				*av[5] = {"-x", "-1234", "-n", "tutu", NULL};
	const t_main_arg	dummy = {4, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(1, get_opt_int(dummy, &i, 1, &args));
	ck_assert_int_eq(0, args.port);
	ck_assert_int_eq(0, args.width);
	ck_assert_int_eq(0, args.height);
	ck_assert_int_eq(0, args.nb_clients);
	ck_assert_int_eq(0, args.tick);
	ck_assert_int_eq(2, i);
}
END_TEST

START_TEST(arg_get_opt_int_height_valid)
{
	int					i = 0;
	t_arguments			args;
	char				*av[5] = {"-y", "1234", "-n", "tutu", NULL};
	const t_main_arg	dummy = {4, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(0, get_opt_int(dummy, &i, 2, &args));
	ck_assert_int_eq(0, args.port);
	ck_assert_int_eq(0, args.width);
	ck_assert_int_eq(1234, args.height);
	ck_assert_int_eq(0, args.nb_clients);
	ck_assert_int_eq(0, args.tick);
	ck_assert_int_eq(2, i);
}
END_TEST

START_TEST(arg_get_opt_int_height_missing)
{
	int					i = 0;
	t_arguments			args;
	char				*av[4] = {"-y", "-n", "tutu", NULL};
	const t_main_arg	dummy = {3, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(1, get_opt_int(dummy, &i, 2, &args));
	ck_assert_int_eq(0, args.port);
	ck_assert_int_eq(0, args.width);
	ck_assert_int_eq(0, args.height);
	ck_assert_int_eq(0, args.nb_clients);
	ck_assert_int_eq(0, args.tick);
	ck_assert_int_eq(1, i);
}
END_TEST

START_TEST(arg_get_opt_int_height_invalid)
{
	int					i = 0;
	t_arguments			args;
	char				*av[5] = {"-y", "-1234", "-n", "tutu", NULL};
	const t_main_arg	dummy = {4, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(1, get_opt_int(dummy, &i, 2, &args));
	ck_assert_int_eq(0, args.port);
	ck_assert_int_eq(0, args.width);
	ck_assert_int_eq(0, args.height);
	ck_assert_int_eq(0, args.nb_clients);
	ck_assert_int_eq(0, args.tick);
	ck_assert_int_eq(2, i);
}
END_TEST

START_TEST(arg_get_opt_int_nb_clients_valid)
{
	int					i = 0;
	t_arguments			args;
	char				*av[5] = {"-c", "1234", "-n", "tutu", NULL};
	const t_main_arg	dummy = {4, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(0, get_opt_int(dummy, &i, 3, &args));
	ck_assert_int_eq(0, args.port);
	ck_assert_int_eq(0, args.width);
	ck_assert_int_eq(0, args.height);
	ck_assert_int_eq(1234, args.nb_clients);
	ck_assert_int_eq(0, args.tick);
	ck_assert_int_eq(2, i);
}
END_TEST

START_TEST(arg_get_opt_int_nb_clients_missing)
{
	int					i = 0;
	t_arguments			args;
	char				*av[4] = {"-c", "-n", "tutu", NULL};
	const t_main_arg	dummy = {3, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(1, get_opt_int(dummy, &i, 3, &args));
	ck_assert_int_eq(0, args.port);
	ck_assert_int_eq(0, args.width);
	ck_assert_int_eq(0, args.height);
	ck_assert_int_eq(0, args.nb_clients);
	ck_assert_int_eq(0, args.tick);
	ck_assert_int_eq(1, i);
}
END_TEST

START_TEST(arg_get_opt_int_nb_clients_invalid)
{
	int					i = 0;
	t_arguments			args;
	char				*av[5] = {"-c", "-1234", "-n", "tutu", NULL};
	const t_main_arg	dummy = {4, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(1, get_opt_int(dummy, &i, 3, &args));
	ck_assert_int_eq(0, args.port);
	ck_assert_int_eq(0, args.width);
	ck_assert_int_eq(0, args.height);
	ck_assert_int_eq(0, args.nb_clients);
	ck_assert_int_eq(0, args.tick);
	ck_assert_int_eq(2, i);
}
END_TEST

START_TEST(arg_get_opt_int_tick_valid)
{
	int					i = 0;
	t_arguments			args;
	char				*av[5] = {"-t", "1234", "-n", "tutu", NULL};
	const t_main_arg	dummy = {4, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(0, get_opt_int(dummy, &i, 4, &args));
	ck_assert_int_eq(0, args.port);
	ck_assert_int_eq(0, args.width);
	ck_assert_int_eq(0, args.height);
	ck_assert_int_eq(0, args.nb_clients);
	ck_assert_int_eq(1234, args.tick);
	ck_assert_int_eq(2, i);
}
END_TEST

START_TEST(arg_get_opt_int_tick_missing)
{
	int					i = 0;
	t_arguments			args;
	char				*av[4] = {"-t", "-n", "tutu", NULL};
	const t_main_arg	dummy = {3, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(1, get_opt_int(dummy, &i, 4, &args));
	ck_assert_int_eq(0, args.port);
	ck_assert_int_eq(0, args.width);
	ck_assert_int_eq(0, args.height);
	ck_assert_int_eq(0, args.nb_clients);
	ck_assert_int_eq(0, args.tick);
	ck_assert_int_eq(1, i);
}
END_TEST

START_TEST(arg_get_opt_int_tick_invalid)
{
	int					i = 0;
	t_arguments			args;
	char				*av[5] = {"-t", "-1234", "-n", "tutu", NULL};
	const t_main_arg	dummy = {4, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(1, get_opt_int(dummy, &i, 4, &args));
	ck_assert_int_eq(0, args.port);
	ck_assert_int_eq(0, args.width);
	ck_assert_int_eq(0, args.height);
	ck_assert_int_eq(0, args.nb_clients);
	ck_assert_int_eq(0, args.tick);
	ck_assert_int_eq(2, i);
}
END_TEST

TCase*	arg_get_opt_int(void)
{
	TCase	*arg_get_opt_int;

	arg_get_opt_int = tcase_create("get_opt_int");
	tcase_add_test(arg_get_opt_int, arg_get_opt_int_port_valid);
	tcase_add_test(arg_get_opt_int, arg_get_opt_int_port_invalid);
	tcase_add_test(arg_get_opt_int, arg_get_opt_int_port_missing);
	tcase_add_test(arg_get_opt_int, arg_get_opt_int_width_valid);
	tcase_add_test(arg_get_opt_int, arg_get_opt_int_width_invalid);
	tcase_add_test(arg_get_opt_int, arg_get_opt_int_width_missing);
	tcase_add_test(arg_get_opt_int, arg_get_opt_int_height_valid);
	tcase_add_test(arg_get_opt_int, arg_get_opt_int_height_invalid);
	tcase_add_test(arg_get_opt_int, arg_get_opt_int_height_missing);
	tcase_add_test(arg_get_opt_int, arg_get_opt_int_nb_clients_valid);
	tcase_add_test(arg_get_opt_int, arg_get_opt_int_nb_clients_invalid);
	tcase_add_test(arg_get_opt_int, arg_get_opt_int_nb_clients_missing);
	tcase_add_test(arg_get_opt_int, arg_get_opt_int_tick_valid);
	tcase_add_test(arg_get_opt_int, arg_get_opt_int_tick_invalid);
	tcase_add_test(arg_get_opt_int, arg_get_opt_int_tick_missing);
	return (arg_get_opt_int);
}
