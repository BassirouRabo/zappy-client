#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(message_rearrange_simple_queue)
{
	t_zappy		var;
	t_player	*p = &var.players[5];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	add_msg_to_player(p, "caca", 0, 1);
	add_msg_to_player(p, "caca boudin", 0, 1);
	add_msg_to_player(p, "crotte", 6, 1);
	add_msg_to_player(p, "crotte de chien", 15, 1);
	rearrange_message_queue(p, 17, 1);
	add_msg_to_player(p, "caca", 4, 1);
	ck_assert_str_eq(p->snd.buf[p->snd.read], "crotte\ncrotte de chien\ncaca\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(message_rearrange_extend_queue)
{
	t_zappy		var;
	t_player	*p = &var.players[5];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	add_msg_to_player(p, "caca", 0, 1);
	add_msg_to_player(p, "caca boudin", 0, 1);
	add_msg_to_player(p, "crotte", 6, 1);
	add_msg_to_player(p, "crotte de chien", 15, 1);
	add_msg_to_player_lst(p, "LEERRROOOOYYY ", 14, 0);
	add_msg_to_player_lst(p, "JJEEENNKKIINNKKSSSSS !", 23, 1);
	rearrange_message_queue(p, 17, 1);
	ck_assert_str_eq(p->snd.buf[p->snd.read], "crotte\ncrotte de chien\nLEERRROOOOYYY JJEEENNKKIINNKKSSSSS !\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	message_rearrange_message_queue(void)
{
	TCase	*tc;

	tc = tcase_create("rearrange_msg_queue");
	tcase_add_test(tc, message_rearrange_simple_queue);
	tcase_add_test(tc, message_rearrange_extend_queue);
	return (tc);
}
