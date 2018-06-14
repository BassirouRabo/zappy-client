#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(message_update_pos_pointer_full)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	u_int		i = 0;

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	ck_assert_int_eq(p->snd.read, 0);
	while (i < NB_SND)
	{
		ck_assert_ptr_eq(p->snd.pos, p->snd.buf[p->snd.write]);
		ck_assert_int_eq(p->snd.full, 0);
		ck_assert_int_eq(p->snd.write, i);
		update_pos_pointer(&p->snd);
		++i;
	}
	ck_assert_ptr_eq(p->snd.pos, p->snd.buf[p->snd.write]);
	ck_assert_int_eq(p->snd.full, 1);
	ck_assert_int_eq(p->snd.write, 0);
	clean_msg_queue(p);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	message_update_pos_pointer(void)
{
	TCase	*tc;

	tc = tcase_create("update_pos_pointer");
	tcase_add_test(tc, message_update_pos_pointer_full);
	return (tc);
}
