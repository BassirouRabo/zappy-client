#include <stdlib.h>
#include <check.h>
#include "serveur.h"

START_TEST(arg_get_opt_string_two_team)
{
	int					i = 0;
	t_arguments			args;
	char				*av[5] = {"-n", "toto", "tutu", "-p", NULL};
	const t_main_arg	dummy = {4, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(0, get_opt_string(dummy, &i, &args));
	ck_assert_int_eq(3, args.nb_team);
	ck_assert_str_eq("toto", args.teams[0].name);
	ck_assert_str_eq("tutu", args.teams[1].name);
	ck_assert_str_eq("GRAPHIC", args.teams[2].name);
	ck_assert_int_eq(3, i);
}
END_TEST

START_TEST(arg_get_opt_string_two_team_last)
{
	int					i = 0;
	t_arguments			args;
	char				*av[4] = {"-n", "toto", "tutu", NULL};
	const t_main_arg	dummy = {3, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(0, get_opt_string(dummy, &i, &args));
	ck_assert_int_eq(3, args.nb_team);
	ck_assert_str_eq("toto", args.teams[0].name);
	ck_assert_str_eq("tutu", args.teams[1].name);
	ck_assert_str_eq("GRAPHIC", args.teams[2].name);
	ck_assert_int_eq(3, i);
}
END_TEST

START_TEST(arg_get_opt_string_team_name_too_long)
{
	int					i = 0;
	t_arguments			args;
	char				*av[4] = {"-n", "What is the dullest element? Bohrium", NULL};
	const t_main_arg	dummy = {2, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(0, get_opt_string(dummy, &i, &args));
	ck_assert_int_eq(2, args.nb_team);
	ck_assert_str_eq("What is the dullest element? Boh", args.teams[0].name);
	ck_assert_str_eq("GRAPHIC", args.teams[1].name);
	ck_assert_int_eq(2, i);
}
END_TEST

START_TEST(arg_get_opt_string_no_team)
{
	int					i = 0;
	t_arguments			args;
	char				*av[4] = {"-n", "-p", "1234", NULL};
	const t_main_arg	dummy = {3, (const char**)av};

	bzero(&args, sizeof(t_arguments));
	ck_assert_int_eq(1, get_opt_string(dummy, &i, &args));
	ck_assert_int_eq(0, args.nb_team);
	ck_assert_int_eq(1, i);
}
END_TEST

TCase*	arg_get_opt_string(void)
{
	TCase	*arg_get_opt_string;

	arg_get_opt_string = tcase_create("get_opt_string");
	tcase_add_test(arg_get_opt_string, arg_get_opt_string_two_team);
	tcase_add_test(arg_get_opt_string, arg_get_opt_string_two_team_last);
	tcase_add_test(arg_get_opt_string, arg_get_opt_string_team_name_too_long);
	tcase_add_test(arg_get_opt_string, arg_get_opt_string_no_team);
	return (arg_get_opt_string);
}
