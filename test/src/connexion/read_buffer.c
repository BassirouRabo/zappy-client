#include <check.h>
#include <stdio.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(connexion_read_buffer_normal)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "prend\n";
	char		str2[30] = "Command format error\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player(&var, p);
	strcpy(p->rcv.buf[p->rcv.write], str);
	p->rcv.write = (p->rcv.write + 1 == NB_RCV) ? 0 : p->rcv.write + 1;
	p->rcv.full = (p->rcv.write == p->rcv.read);
	read_buffer(&var, p);
	ck_assert_int_eq(p->rcv.write, p->rcv.read);
	ck_assert_int_eq(p->rcv.full, 0);
	ck_assert_ptr_eq(p->rcv.remain, NULL);
	ck_assert_int_eq(p->snd.write, p->snd.read);
	ck_assert_ptr_eq(p->snd.pos, (void *)&p->snd.buf[p->snd.write] + strlen(str2));
	ck_assert_str_eq(p->snd.buf[p->snd.write], str2);
	ck_assert_int_eq(p->snd.full, 0);
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(connexion_read_buffer_normal_multiple_buffer)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "prend\n";
	char		str2[50] = "Command format error\nCommand format error\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player(&var, p);
	strcpy(p->rcv.buf[p->rcv.write], str);
	p->rcv.write = (p->rcv.write + 1 == NB_RCV) ? 0 : p->rcv.write + 1;
	p->rcv.full = (p->rcv.write == p->rcv.read);
	strcpy(p->rcv.buf[p->rcv.write], "pre");
	p->rcv.write = (p->rcv.write + 1 == NB_RCV) ? 0 : p->rcv.write + 1;
	p->rcv.full = (p->rcv.write == p->rcv.read);
	strcpy(p->rcv.buf[p->rcv.write], "nd");
	p->rcv.write = (p->rcv.write + 1 == NB_RCV) ? 0 : p->rcv.write + 1;
	p->rcv.full = (p->rcv.write == p->rcv.read);
	strcpy(p->rcv.buf[p->rcv.write], "\n");
	p->rcv.write = (p->rcv.write + 1 == NB_RCV) ? 0 : p->rcv.write + 1;
	p->rcv.full = (p->rcv.write == p->rcv.read);
	read_buffer(&var, p);
	ck_assert_int_eq(p->rcv.write, p->rcv.read);
	ck_assert_int_eq(p->rcv.full, 0);
	ck_assert_ptr_eq(p->rcv.remain, NULL);
	ck_assert_int_eq(p->snd.write, p->snd.read);
	ck_assert_ptr_eq(p->snd.pos, (void *)&p->snd.buf[p->snd.write] + strlen(str2));
	ck_assert_str_eq(p->snd.buf[p->snd.write], str2);
	ck_assert_int_eq(p->snd.full, 0);
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(connexion_read_buffer_missing_new_line)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	char		str[10] = "prend";

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_player(&var, p);
	strcpy(p->rcv.buf[p->rcv.write], str);
	p->rcv.write = (p->rcv.write + 1 == NB_RCV) ? 0 : p->rcv.write + 1;
	p->rcv.full = (p->rcv.write == p->rcv.read);
	read_buffer(&var, p);
	ck_assert_int_eq(p->rcv.write, p->rcv.read);
	ck_assert_int_eq(p->rcv.full, 0);
	ck_assert_ptr_ne(p->rcv.remain, NULL);
	ck_assert_str_eq(p->rcv.remain, str);
	ck_assert_int_eq(p->snd.write, p->snd.read);
	ck_assert_int_eq(p->snd.full, 0);
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	connexion_read_buffer(void)
{
	TCase	*tc;

	tc = tcase_create("read_buffer");
	tcase_add_test(tc, connexion_read_buffer_normal);
	tcase_add_test(tc, connexion_read_buffer_normal_multiple_buffer);
	tcase_add_test(tc, connexion_read_buffer_missing_new_line);
	return (tc);
}
