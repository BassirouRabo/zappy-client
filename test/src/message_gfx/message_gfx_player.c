#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(message_gfx_pnw_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	t_player	*gfx = &var.players[6];
	char		str[] = "pnw 5 4 3 3 1 toto\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	message_gfx_pnw(&var, p);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
}
END_TEST

START_TEST(message_gfx_ppo_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	t_player	*gfx = &var.players[6];
	char		str[] = "ppo 5 4 3 3\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	message_gfx_ppo(&var, p);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
}
END_TEST

START_TEST(message_gfx_plv_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	t_player	*gfx = &var.players[6];
	char		str[] = "plv 5 1\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	message_gfx_plv(&var, p);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
}
END_TEST

START_TEST(message_gfx_pin_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	t_player	*gfx = &var.players[6];
	char		str[] = "pin 5 4 3 10 5 6 7 8 9 10\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	message_gfx_pin(&var, p);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
}
END_TEST

START_TEST(message_gfx_pex_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	t_player	*gfx = &var.players[6];
	char		str[] = "pex 5\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	message_gfx_pex(&var, p);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
}
END_TEST

TCase*	message_gfx_player(void)
{
	TCase	*tc;

	tc = tcase_create("player.c");
	tcase_add_test(tc, message_gfx_pnw_test);
	tcase_add_test(tc, message_gfx_ppo_test);
	tcase_add_test(tc, message_gfx_plv_test);
	tcase_add_test(tc, message_gfx_pin_test);
	tcase_add_test(tc, message_gfx_pex_test);
	return (tc);
}
