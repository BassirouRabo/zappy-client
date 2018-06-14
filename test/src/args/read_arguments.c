#include <stdlib.h>
#include <check.h>
#include "serveur.h"

extern int		g_log;

START_TEST(arg_read_arguments_valid)
{
	int					ac = 14;
	char				*av[14] = {"./test", "-p", "1234", "-x", "20", "-y",
		"30", "-n", "toto", "tutu", "-c", "40", "-t", "50"};
	t_arguments			args;

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(0, read_arguments(ac, (const char **)av, &args));
	ck_assert_int_eq(3, args.nb_team);
	ck_assert_str_eq("toto", args.teams[0].name);
	ck_assert_str_eq("tutu", args.teams[1].name);
	ck_assert_int_eq(1234, args.port);
	ck_assert_int_eq(20, args.width);
	ck_assert_int_eq(30, args.height);
	ck_assert_int_eq(40, args.nb_clients);
	ck_assert_int_eq(50, args.tick);
}
END_TEST

START_TEST(arg_read_arguments_valid_verbose)
{
	int					ac = 16;
	char				*av[16] = {"./test", "-p", "1234", "-x", "20", "-y",
		"30", "-n", "toto", "tutu", "-c", "40", "-t", "50", "-v", "weica"};
	t_arguments			args;

	bzero(&args, sizeof(t_arguments));
	g_log = 0;
	ck_assert_int_eq(0, read_arguments(ac, (const char **)av, &args));
	ck_assert_int_eq(3, args.nb_team);
	ck_assert_str_eq("toto", args.teams[0].name);
	ck_assert_str_eq("tutu", args.teams[1].name);
	ck_assert_int_eq(1234, args.port);
	ck_assert_int_eq(20, args.width);
	ck_assert_int_eq(30, args.height);
	ck_assert_int_eq(40, args.nb_clients);
	ck_assert_int_eq(50, args.tick);
	ck_assert_int_eq(g_log, LOG_W + LOG_E + LOG_I + LOG_C + LOG_A);
}
END_TEST

START_TEST(arg_read_arguments_missing_team_name)
{
	int					ac = 12;
	char				*av[12] = {"./test", "-p", "1234", "-x", "20", "-y",
		"30", "-n", "-c", "40", "-t", "50"};
	t_arguments			args;

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(2, read_arguments(ac, (const char **)av, &args));
	ck_assert_int_eq(0, args.nb_team);
	ck_assert_int_eq(1234, args.port);
	ck_assert_int_eq(20, args.width);
	ck_assert_int_eq(30, args.height);
	ck_assert_int_eq(40, args.nb_clients);
	ck_assert_int_eq(50, args.tick);
}
END_TEST

START_TEST(arg_read_arguments_team_name_given_two_time)
{
	int					ac = 16;
	char				*av[16] = {"./test", "-p", "1234", "-n", "caca", "-x",
		"20", "-y", "30", "-n", "toto", "tutu", "-c", "40", "-t", "50"};
	t_arguments			args;

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(0, read_arguments(ac, (const char **)av, &args));
	ck_assert_int_eq(3, args.nb_team);
	ck_assert_str_eq("toto", args.teams[0].name);
	ck_assert_str_eq("tutu", args.teams[1].name);
	ck_assert_int_eq(1234, args.port);
	ck_assert_int_eq(20, args.width);
	ck_assert_int_eq(30, args.height);
	ck_assert_int_eq(40, args.nb_clients);
	ck_assert_int_eq(50, args.tick);
}
END_TEST

START_TEST(arg_read_arguments_missing_port)
{
	int					ac = 13;
	char				*av[13] = {"./test", "-p", "-x", "20", "-y", "30",
		"-n", "toto", "tutu", "-c", "40", "-t", "50"};
	t_arguments			args;

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(2, read_arguments(ac, (const char **)av, &args));
	ck_assert_int_eq(3, args.nb_team);
	ck_assert_str_eq("toto", args.teams[0].name);
	ck_assert_str_eq("tutu", args.teams[1].name);
	ck_assert_int_eq(0, args.port);
	ck_assert_int_eq(20, args.width);
	ck_assert_int_eq(30, args.height);
	ck_assert_int_eq(40, args.nb_clients);
	ck_assert_int_eq(50, args.tick);
}
END_TEST

START_TEST(arg_read_arguments_port_given_two_time)
{
	int					ac = 16;
	char				*av[16] = {"./test", "-p", "1234", "-x", "20", "-y",
		"30", "-n", "toto", "tutu", "-c", "40", "-t", "50", "-p", "2345"};
	t_arguments			args;

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(0, read_arguments(ac, (const char **)av, &args));
	ck_assert_int_eq(3, args.nb_team);
	ck_assert_str_eq("toto", args.teams[0].name);
	ck_assert_str_eq("tutu", args.teams[1].name);
	ck_assert_int_eq(2345, args.port);
	ck_assert_int_eq(20, args.width);
	ck_assert_int_eq(30, args.height);
	ck_assert_int_eq(40, args.nb_clients);
	ck_assert_int_eq(50, args.tick);
}
END_TEST

START_TEST(arg_read_arguments_invalid_verbose)
{
	int					ac = 16;
	char				*av[16] = {"./test", "-p", "1234", "-x", "20", "-y",
		"30", "-n", "toto", "tutu", "-c", "40", "-t", "50", "-v", "toto"};
	t_arguments			args;

	bzero(&args, sizeof(t_arguments));
	g_log = 0;
	ck_assert_int_eq(4, read_arguments(ac, (const char **)av, &args));
	ck_assert_int_eq(3, args.nb_team);
	ck_assert_str_eq("toto", args.teams[0].name);
	ck_assert_str_eq("tutu", args.teams[1].name);
	ck_assert_int_eq(1234, args.port);
	ck_assert_int_eq(20, args.width);
	ck_assert_int_eq(30, args.height);
	ck_assert_int_eq(40, args.nb_clients);
	ck_assert_int_eq(50, args.tick);
	ck_assert_int_eq(g_log, 0);
}
END_TEST

TCase*	arg_read_arguments(void)
{
	TCase	*arg_read_arguments;

	arg_read_arguments = tcase_create("read_arguments");
	tcase_add_test(arg_read_arguments, arg_read_arguments_valid);
	tcase_add_test(arg_read_arguments, arg_read_arguments_valid_verbose);
	tcase_add_test(arg_read_arguments, arg_read_arguments_missing_team_name);
	tcase_add_test(arg_read_arguments, arg_read_arguments_team_name_given_two_time);
	tcase_add_test(arg_read_arguments, arg_read_arguments_missing_port);
	tcase_add_test(arg_read_arguments, arg_read_arguments_port_given_two_time);
	tcase_add_test(arg_read_arguments, arg_read_arguments_invalid_verbose);
	return (arg_read_arguments);
}
