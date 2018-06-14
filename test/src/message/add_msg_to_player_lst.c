#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(message_add_msg_to_player_lst_)
{
	t_zappy		var;
	t_player	*p = &var.players[5];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_fill_buffer(p);
	add_msg_to_player_lst(p, "boudin", 7, 1);
	add_msg_to_player_lst(p, "crotte de chien", 16, 1);
	ck_assert_int_eq(p->snd.lst.size, 3);
	ck_assert_str_eq(p->snd.lst.first->content, "caca");
	ck_assert_str_eq(p->snd.lst.first->next->content, "boudin\n");
	ck_assert_str_eq(p->snd.lst.last->content, "crotte de chien\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(message_add_msg_to_player_lst_without_cr)
{
	t_zappy		var;
	t_player	*p = &var.players[5];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_fill_buffer(p);
	add_msg_to_player_lst(p, "boudin", 7, 0);
	add_msg_to_player_lst(p, "crotte de chien", 16, 1);
	ck_assert_int_eq(p->snd.lst.size, 3);
	ck_assert_str_eq(p->snd.lst.first->content, "caca");
	ck_assert_str_eq(p->snd.lst.last->content, "crotte de chien\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	message_add_msg_to_player_lst(void)
{
	TCase	*tc;

	tc = tcase_create("add_msg_to_player_lst");
	tcase_add_test(tc, message_add_msg_to_player_lst_);
	tcase_add_test(tc, message_add_msg_to_player_lst_without_cr);
	return (tc);
}
