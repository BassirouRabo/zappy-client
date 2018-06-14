#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

void	test_snd_overflow(t_player *p, int cr, int cr_separated)
{
	u_int		i = 0;
	char		str[SND_SIZE + 1];

	memset(str, '0', SND_SIZE);
	str[SND_SIZE] = 0;
	while (i < NB_SND - 1)
	{
		add_msg_to_player(p, str, SND_SIZE - 1, 1);
		++i;
	}
	add_msg_to_player(p, str, SND_SIZE - 3, 1);
	add_msg_to_player(p, "caca", 0, cr && !cr_separated);
	if (cr && cr_separated)
		add_msg_to_player(p, "", 0, 1);
	ck_assert_int_eq(p->snd.full, 1);
	ck_assert_int_eq(p->snd.read, p->snd.write);
	str[SND_SIZE - 1] = '\n';
	i = 0;
	while (i < NB_SND - 1)
	{
		ck_assert_str_eq(p->snd.buf[p->snd.read], str);
		p->snd.read = (p->snd.read + 1 == NB_SND) ? 0 : p->snd.read + 1;
		p->snd.full = 0;
		++i;
	}
	strcpy(str + SND_SIZE - 3, "\nca");
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	p->snd.read = (p->snd.read + 1 == NB_SND) ? 0 : p->snd.read + 1;
	ck_assert_str_eq(p->snd.lst.first->content, (cr && !cr_separated) ? "ca\n" : "ca");
	if (cr && cr_separated)
		ck_assert_str_eq(p->snd.lst.last->content, "\n");
	clean_msg_queue(p);
}

START_TEST(message_add_msg_to_player_)
{
	t_zappy		var;
	t_player	*p = &var.players[5];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	add_msg_to_player(p, "caca", 0, 1);
	add_msg_to_player(p, "caca boudin", 0, 1);
	add_msg_to_player(p, "crotte", 6, 1);
	add_msg_to_player(p, "crotte de chien", 15, 1);
	ck_assert_str_eq(p->snd.buf[p->snd.read], "caca\ncaca boudin\ncrotte\ncrotte de chien\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(message_add_msg_to_player_without_cr)
{
	t_zappy		var;
	t_player	*p = &var.players[5];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	add_msg_to_player(p, "caca", 0, 1);
	add_msg_to_player(p, "caca ", 0, 0);
	add_msg_to_player(p, "boudin", 0, 1);
	add_msg_to_player(p, "crotte", 6, 1);
	add_msg_to_player(p, "crotte de chien", 15, 0);
	ck_assert_str_eq(p->snd.buf[p->snd.read], "caca\ncaca boudin\ncrotte\ncrotte de chien");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(message_add_msg_to_player_without_cr_2)
{
	t_zappy		var;
	t_player	*p = &var.players[5];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	add_msg_to_player(p, "caca", 0, 0);
	add_msg_to_player(p, "", 0, 1);
	add_msg_to_player(p, "caca ", 0, 0);
	add_msg_to_player(p, "boudin", 0, 0);
	add_msg_to_player(p, "", 0, 1);
	add_msg_to_player(p, "crotte", 6, 0);
	add_msg_to_player(p, "", 0, 1);
	add_msg_to_player(p, "crotte de chien", 15, 0);
	ck_assert_str_eq(p->snd.buf[p->snd.read], "caca\ncaca boudin\ncrotte\ncrotte de chien");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(message_add_msg_to_player_buffer_overflow)
{
	char		str[SND_SIZE + 1];
	t_zappy		var;
	t_player	*p = &var.players[5];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	memset(str, '0', SND_SIZE);
	str[SND_SIZE] = 0;
	add_msg_to_player(p, str, SND_SIZE - 3, 1);
	add_msg_to_player(p, "caca", 0, 1);
	strcpy(str + SND_SIZE - 3, "\nca");
	ck_assert_int_eq(p->snd.read + 1, p->snd.write);
	ck_assert_str_eq(p->snd.buf[p->snd.read], str);
	ck_assert_str_eq(p->snd.buf[p->snd.read + 1], "ca\n");
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(message_add_msg_to_player_all_buffer_overflow)
{
	t_zappy		var;
	t_player	*p = &var.players[5];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	test_snd_overflow(p, 1, 0);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(message_add_msg_to_player_all_buffer_overflow_without_cr)
{
	t_zappy		var;
	t_player	*p = &var.players[5];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	test_snd_overflow(p, 0, 0);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(message_add_msg_to_player_all_buffer_overflow_without_cr_2)
{
	t_zappy		var;
	t_player	*p = &var.players[5];

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	test_snd_overflow(p, 1, 1);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(message_add_msg_to_player_all_buffer_overflow_multiple)
{
	int			i;
	t_zappy		var;
	t_player	*p1 = &var.players[5];
	t_player	*p2;

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p1);
	i = 6;
	while (i < MAX_FD)
	{
		dummy_t_player(&var, &var.players[i]);
		++i;
	}
	test_snd_overflow(p1, 1, 0);
	test_snd_overflow(p1, 1, 0);
	test_snd_overflow(p1, 1, 0);
	i = 6;
	while (i < MAX_FD)
 	{
		p2 = &var.players[i];
		ck_assert_int_eq(p2->id, i);
		ck_assert_int_eq(p2->inv[0], 0);
		ck_assert_int_eq(p2->inv[1], 0);
		ck_assert_int_eq(p2->inv[2], 0);
		ck_assert_int_eq(p2->inv[3], 0);
		ck_assert_int_eq(p2->inv[4], 0);
		ck_assert_int_eq(p2->inv[5], 0);
		ck_assert_int_eq(p2->coord[0], 0);
		ck_assert_int_eq(p2->coord[1], 0);
		ck_assert_int_eq(p2->pending_actions, 0);
		ck_assert_ptr_eq(p2->team, &var.teams[0]);
		ck_assert_int_eq(p2->facing, 0);
		ck_assert_int_eq(p2->status, FD_CLIENT);
		ck_assert_int_eq(p2->level, 0);
		++i;
	}
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	message_add_msg_to_player(void)
{
	TCase	*tc;

	tc = tcase_create("add_msg_to_player");
	tcase_add_test(tc, message_add_msg_to_player_);
	tcase_add_test(tc, message_add_msg_to_player_without_cr);
	tcase_add_test(tc, message_add_msg_to_player_without_cr_2);
	tcase_add_test(tc, message_add_msg_to_player_buffer_overflow);
	tcase_add_test(tc, message_add_msg_to_player_all_buffer_overflow);
	tcase_add_test(tc, message_add_msg_to_player_all_buffer_overflow_without_cr);
	tcase_add_test(tc, message_add_msg_to_player_all_buffer_overflow_without_cr_2);
	tcase_add_test(tc, message_add_msg_to_player_all_buffer_overflow_multiple);
	return (tc);
}
