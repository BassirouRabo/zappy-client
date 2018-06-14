#include <stdlib.h>
#include <check.h>
#include "serveur.h"

START_TEST(arg_check_arguments_valid)
{
	t_arguments		args = {1234, 20, 30, 40, 50, 2, NULL};

	args.teams = (t_team*)malloc(sizeof(t_team)*2);
	strcpy(args.teams[0].name, "toto");
	strcpy(args.teams[1].name, "tutu");
	ck_assert_int_eq(0, check_arguments(&args, 0));
	ck_assert_int_eq(1234, args.port);
	ck_assert_int_eq(20, args.width);
	ck_assert_int_eq(30, args.height);
	ck_assert_int_eq(40, args.nb_clients);
	ck_assert_int_eq(50, args.tick);
	ck_assert_uint_eq(2, args.nb_team);
	ck_assert_str_eq("toto", args.teams[0].name);
	ck_assert_str_eq("tutu", args.teams[1].name);
	rm_teams(&args.teams, (int *)&args.nb_team);
}
END_TEST

START_TEST(arg_check_arguments_duplicate_team_name)
{
	t_arguments		args = {1234, 20, 30, 40, 50, 3, NULL};

	args.teams = (t_team*)malloc(sizeof(t_team)*3);
	strcpy(args.teams[0].name, "toto");
	strcpy(args.teams[1].name, "tutu");
	strcpy(args.teams[2].name, "toto");
	ck_assert_int_eq(1, check_arguments(&args, 0));
	ck_assert_int_eq(1234, args.port);
	ck_assert_int_eq(20, args.width);
	ck_assert_int_eq(30, args.height);
	ck_assert_int_eq(40, args.nb_clients);
	ck_assert_int_eq(50, args.tick);
	ck_assert_uint_eq(3, args.nb_team);
	ck_assert_str_eq("toto", args.teams[0].name);
	ck_assert_str_eq("tutu", args.teams[1].name);
	rm_teams(&args.teams, (int *)&args.nb_team);
}
END_TEST

START_TEST(arg_check_arguments_invalid_team_name)
{
	t_arguments		args = {1234, 20, 30, 40, 50, 3, NULL};

	args.teams = (t_team*)malloc(sizeof(t_team)*3);
	strcpy(args.teams[0].name, "V4l1d 734M_N4m3");
	strcpy(args.teams[1].name, "!nv@li!d-\"team\";name");
	strcpy(args.teams[2].name, "toto");
	ck_assert_int_eq(7, check_arguments(&args, 0));
	ck_assert_int_eq(1234, args.port);
	ck_assert_int_eq(20, args.width);
	ck_assert_int_eq(30, args.height);
	ck_assert_int_eq(40, args.nb_clients);
	ck_assert_int_eq(50, args.tick);
	ck_assert_uint_eq(3, args.nb_team);
	rm_teams(&args.teams, (int *)&args.nb_team);
}
END_TEST

START_TEST(arg_check_arguments_too_much)
{
	t_arguments		args = {123411, 120, 130, 340, 550, 112, NULL};

	ck_assert_int_eq(7, check_arguments(&args, 0));
}
END_TEST

START_TEST(arg_check_arguments_too_few)
{
	t_arguments		args = {1, 2, 3, 4, 0, 0, NULL};

	ck_assert_int_eq(5, check_arguments(&args, 0));
}
END_TEST

TCase*	arg_check_arguments(void)
{
	TCase	*check_arguments;

	check_arguments = tcase_create("check_arguments");
	tcase_add_test(check_arguments, arg_check_arguments_valid);
	tcase_add_test(check_arguments, arg_check_arguments_duplicate_team_name);
	tcase_add_test(check_arguments, arg_check_arguments_invalid_team_name);
	tcase_add_test(check_arguments, arg_check_arguments_too_much);
	tcase_add_test(check_arguments, arg_check_arguments_too_few);
	return (check_arguments);
}
