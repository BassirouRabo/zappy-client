#include <stdlib.h>
#include <check.h>
#include "serveur.h"

START_TEST(rm_teams_two_team)
{
	t_team	*teams = NULL;
	int	nb_team = 2;

	teams = (t_team *)malloc(sizeof(t_team) * 2);
	strcpy(teams[0].name, "toto");
	strcpy(teams[1].name, "tutu");
	rm_teams(&teams, &nb_team);
	ck_assert_uint_eq(0, nb_team);
	ck_assert_ptr_eq(NULL, teams);
}
END_TEST

START_TEST(rm_teams_no_team)
{
	t_team	*teams = NULL;
	int	nb_team = 0;

	rm_teams(&teams, &nb_team);
	ck_assert_uint_eq(0, nb_team);
	ck_assert_ptr_eq(NULL, teams);
}
END_TEST

START_TEST(rm_teams_no_team_wrong_nb_team)
{
	t_team	*teams = NULL;
	int	nb_team = 2;

	rm_teams(&teams, &nb_team);
	ck_assert_uint_eq(0, nb_team);
	ck_assert_ptr_eq(NULL, teams);
}
END_TEST

TCase*	cleanup_rm_teams(void)
{
	TCase	*tc;

	tc = tcase_create("rm_teams");
	tcase_add_test(tc, rm_teams_two_team);
	tcase_add_test(tc, rm_teams_no_team);
	tcase_add_test(tc, rm_teams_no_team_wrong_nb_team);
	return (tc);
}
