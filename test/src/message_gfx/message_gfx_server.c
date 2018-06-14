#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(message_gfx_msz_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[6];
	char		str[] = "msz 2 1\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player_gfx(&var, gfx);
	message_gfx_msz(&var);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
}
END_TEST

START_TEST(message_gfx_bct_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[6];
	char		str[] = "bct 1 0 1 2 3 4 5 6 7\n";
	int			pos[2] = {0, 1};

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_board(&var);
	dummy_t_board_square(var.board[0][1]);
	dummy_t_player_gfx(&var, gfx);
	message_gfx_bct(&var, pos);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	clean_msg_queue(gfx);
}
END_TEST

START_TEST(message_gfx_tna_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[6];
	char		str[] = "tna toto\ntna tutu\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player_gfx(&var, gfx);
	message_gfx_tna(&var);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
}
END_TEST

START_TEST(message_gfx_sgt_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[6];
	char		str[] = "sgt 4\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player_gfx(&var, gfx);
	message_gfx_sgt(&var);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
}
END_TEST

TCase*	message_gfx_server(void)
{
	TCase	*tc;

	tc = tcase_create("server.c");
	tcase_add_test(tc, message_gfx_msz_test);
	tcase_add_test(tc, message_gfx_bct_test);
	tcase_add_test(tc, message_gfx_tna_test);
	tcase_add_test(tc, message_gfx_sgt_test);
	return (tc);
}
