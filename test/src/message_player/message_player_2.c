#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(message_player_expulsed_test)
{
	int			fd_max = 10;
	t_zappy		var;
	t_player	*p1 = &var.players[5];
	t_player	*p2 = &var.players[6];
	char		str[] = "deplacement 5\n";

	dummy_t_zappy_without_board(&var);
	var.fd_max = &fd_max;
	dummy_t_player(&var, p1);
	dummy_t_player(&var, p2);
	message_player_expulsed(p1, p2);
	ck_assert_str_eq(p2->snd.buf[p2->snd.read], str);
	clean_msg_queue(p2);
	++p1->facing;
	str[12] = '3';
	message_player_expulsed(p1, p2);
	ck_assert_str_eq(p2->snd.buf[p2->snd.read], str);
	clean_msg_queue(p2);
	++p1->facing;
	str[12] = '1';
	message_player_expulsed(p1, p2);
	ck_assert_str_eq(p2->snd.buf[p2->snd.read], str);
	clean_msg_queue(p2);
	++p1->facing;
	str[12] = '7';
	message_player_expulsed(p1, p2);
	ck_assert_str_eq(p2->snd.buf[p2->snd.read], str);
	clean_msg_queue(p2);
	p1->facing = 0;
	++p2->facing;
	message_player_expulsed(p1, p2);
	ck_assert_str_eq(p2->snd.buf[p2->snd.read], str);
	clean_msg_queue(p2);
	++p1->facing;
	str[12] = '5';
	message_player_expulsed(p1, p2);
	ck_assert_str_eq(p2->snd.buf[p2->snd.read], str);
	clean_msg_queue(p2);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(message_player_message_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[] = "message 2,I need a dollar\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	message_player_message(p, 2, "I need a dollar");
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(message_player_incantation_end_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[] = "niveau actuel : 1\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	message_player_incantation_end(p);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(message_player_connect_nbr_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[] = "0\n1\n2\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	message_player_connect_nbr(p);
	dummy_t_zappy_add_remaining_in_team(&var);
	message_player_connect_nbr(p);
	dummy_t_zappy_add_remaining_in_team(&var);
	message_player_connect_nbr(p);
	dummy_t_zappy_add_remaining_in_team(&var);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	message_player_2_test(void)
{
	TCase	*tc;

	tc = tcase_create("2");
	tcase_add_test(tc, message_player_expulsed_test);
	tcase_add_test(tc, message_player_message_test);
	tcase_add_test(tc, message_player_incantation_end_test);
	tcase_add_test(tc, message_player_connect_nbr_test);
	return (tc);
}
