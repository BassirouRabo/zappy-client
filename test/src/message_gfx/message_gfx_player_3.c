#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(message_gfx_pgt_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	t_player	*gfx = &var.players[6];
	char		str[] = "pgt 5 2\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	message_gfx_pgt(&var, p, 2);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
}
END_TEST

START_TEST(message_gfx_pdi_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	t_player	*gfx = &var.players[6];
	char		str[] = "pdi 5\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	message_gfx_pdi(&var, p);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
}
END_TEST

TCase*	message_gfx_player_3(void)
{
	TCase	*tc;

	tc = tcase_create("player.c");
	tcase_add_test(tc, message_gfx_pgt_test);
	tcase_add_test(tc, message_gfx_pdi_test);
	return (tc);
}
