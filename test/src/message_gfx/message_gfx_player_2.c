#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(message_gfx_pbc_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	t_player	*gfx = &var.players[6];
	char		msg[] = "Tonight I'm gonna have myself a real good time";
	char		str[] = "pbc 5 Tonight I'm gonna have myself a real good time\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	message_gfx_pbc(&var, p, msg);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
}
END_TEST

START_TEST(message_gfx_pic_test)
{
	int			fd_max = 13;
	int			pl[MAX_FD];
	t_zappy		var;
	t_player	*p1 = &var.players[5];
	t_player	*p2 = &var.players[6];
	t_player	*p3 = &var.players[7];
	t_player	*p4 = &var.players[8];
	t_player	*p5 = &var.players[9];
	t_player	*p6 = &var.players[10];
	t_player	*p7 = &var.players[11];
	t_player	*p8 = &var.players[12];
	t_player	*gfx = &var.players[13];
	char		str[] = "pic 4 3 1 9 5 7 11 12\n";

	dummy_t_zappy_without_board(&var);
	memset(pl, 0, sizeof(int) * MAX_FD);
	memset(pl + 5, 1, sizeof(int) * 8);
	var.fd_max = &fd_max;
	dummy_t_player(&var, p1);
	dummy_t_player_default(p1);
	dummy_t_player(&var, p2);
	dummy_t_player_default(p2);
	dummy_t_player(&var, p3);
	dummy_t_player_default(p3);
	dummy_t_player(&var, p4);
	dummy_t_player_default(p4);
	dummy_t_player(&var, p5);
	dummy_t_player_default(p5);
	dummy_t_player(&var, p6);
	dummy_t_player_default(p6);
	dummy_t_player(&var, p7);
	dummy_t_player_default(p7);
	dummy_t_player(&var, p8);
	dummy_t_player_default(p8);
	dummy_t_player_gfx(&var, gfx);
	pl[6] = 0;
	pl[8] = 0;
	pl[10] = 0;
	message_gfx_pic(&var, p5, pl);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
}
END_TEST

START_TEST(message_gfx_pie_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	t_player	*gfx = &var.players[6];
	char		str[] = "pie 4 3 1\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	message_gfx_pie(&var, p, 1);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
}
END_TEST

START_TEST(message_gfx_pfk_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	t_player	*gfx = &var.players[6];
	char		str[] = "pfk 5\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	message_gfx_pfk(&var, p);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
}
END_TEST

START_TEST(message_gfx_pdr_test)
{
	t_zappy		var;
	t_player	*p = &var.players[5];
	t_player	*gfx = &var.players[6];
	char		str[] = "pdr 5 2\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_default(p);
	dummy_t_player_gfx(&var, gfx);
	message_gfx_pdr(&var, p, 2);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], str);
	clean_msg_queue(gfx);
}
END_TEST

TCase*	message_gfx_player_2(void)
{
	TCase	*tc;

	tc = tcase_create("player_2.c");
	tcase_add_test(tc, message_gfx_pbc_test);
	tcase_add_test(tc, message_gfx_pic_test);
	tcase_add_test(tc, message_gfx_pie_test);
	tcase_add_test(tc, message_gfx_pfk_test);
	tcase_add_test(tc, message_gfx_pdr_test);
	return (tc);
}
