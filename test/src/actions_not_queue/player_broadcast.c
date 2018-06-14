#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(action_player_broadcast_test_1)
{
	int			i = 1;
	int			fd_max = 24;
	t_aargs		a;
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p0 = &var.players[6];
	t_player	*p1 = &var.players[7];
	t_player	*p2 = &var.players[8];
	t_player	*p3 = &var.players[9];
	t_player	*p4 = &var.players[10];
	t_player	*p5 = &var.players[11];
	t_player	*p6 = &var.players[12];
	t_player	*p7 = &var.players[13];
	t_player	*p8 = &var.players[14];
	t_player	*p9 = &var.players[15];
	t_player	*p10 = &var.players[16];
	t_player	*p11 = &var.players[17];
	t_player	*p12 = &var.players[18];
	t_player	*p13 = &var.players[19];
	t_player	*p14 = &var.players[20];
	t_player	*p15 = &var.players[21];
	t_player	*p16 = &var.players[22];
	t_player	*p17 = &var.players[23];
	t_player	*p18 = &var.players[24];
	t_player	*p;
	char		caster[] = "ok\n";
	char		broadcast[] = "LEERROOYYYY JJEEENNNKKIINNSSSSS";
	char		ret[] = "message 1,LEERROOYYYY JJEEENNNKKIINNSSSSS\n";

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 10;
	var.board_size[1] = 10;
	var.fd_max = &fd_max;
	dummy_t_player_gfx(&var, gfx);
	dummy_t_player(&var, p0);
	dummy_t_player(&var, p1);
	dummy_t_player(&var, p2);
	dummy_t_player(&var, p3);
	dummy_t_player(&var, p4);
	dummy_t_player(&var, p5);
	dummy_t_player(&var, p6);
	dummy_t_player(&var, p7);
	dummy_t_player(&var, p8);
	dummy_t_player(&var, p9);
	dummy_t_player(&var, p10);
	dummy_t_player(&var, p11);
	dummy_t_player(&var, p12);
	dummy_t_player(&var, p13);
	dummy_t_player(&var, p14);
	dummy_t_player(&var, p15);
	dummy_t_player(&var, p16);
	dummy_t_player(&var, p17);
	dummy_t_player(&var, p18);
	a.str = broadcast;
	/*
	p0 {2, 2}
	p1 {0, 1} -> 1
	p2 {9, 5} -> 2
	p3 {2, 7} -> 3
	p4 {4, 4} -> 4
	p5 {0, 6} -> 5
	p6 {5, 9} -> 6
	p7 {3, 9} -> 7
	p8 {9, 9} -> 8
	*/
	p0->coord[0] = 2;
	p0->coord[1] = 2;
	p1->coord[1] = 1;
	p2->coord[0] = 9;
	p2->coord[1] = 5;
	p3->coord[0] = 2;
	p3->coord[1] = 7;
	p4->coord[0] = 4;
	p4->coord[1] = 4;
	p5->coord[0] = 6;
	p6->coord[0] = 5;
	p6->coord[1] = 9;
	p7->coord[0] = 3;
	p7->coord[1] = 9;
	p8->coord[0] = 9;
	p8->coord[1] = 9;

	p9->coord[0] = 2;
	p9->coord[1] = 2;
	p10->coord[0] = 2;
	p10->coord[1] = 2;
	p11->coord[0] = 2;
	p11->coord[1] = 2;
	p12->coord[0] = 2;
	p12->coord[1] = 2;

	p13->coord[1] = 2;
	p13->coord[1] = 1;
	p13->facing = 1;
	p14->coord[1] = 2;
	p14->coord[1] = 1;
	p14->facing = 2;
	p15->coord[1] = 2;
	p15->coord[1] = 1;
	p15->facing = 3;

	p16->coord[0] = 9;
	p16->coord[1] = 5;
	p16->facing = 1;
	p17->coord[0] = 9;
	p17->coord[1] = 5;
	p17->facing = 2;
	p18->coord[0] = 9;
	p18->coord[1] = 5;
	p18->facing = 3;
	action_player_broadcast(&var, p0, &a);
	while (i < 19)
	{
		p = &var.players[i + 6];
		if (i < 9)
			ret[8] = i + '0';
		else if (i < 13)
			ret[8] = '0';
		else if (i < 16)
			ret[8] = (i - 12) * 2 + 1 + '0';
		else if (i < 19)
			ret[8] = (i - 14) * 2 + '0';
		ck_assert_str_eq(p->snd.buf[p->snd.read], ret);
		clean_msg_queue(p);
		++i;
	}
	ck_assert_str_eq(p0->snd.buf[p0->snd.read], caster);
	clean_msg_queue(p0);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], "");
	clean_msg_queue(gfx);
}
END_TEST

TCase*	action_player_broadcast_test(void)
{
	TCase	*tc;

	tc = tcase_create("player_ressources");
	tcase_add_test(tc, action_player_broadcast_test_1);
	return (tc);
}
