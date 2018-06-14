#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <check.h>
#include "serveur.h"
#include "test_dummies.h"
#include "queue.h"

START_TEST(queue_process)
{
	t_zappy		var;
	t_player	*p1 = &var.players[5];
	t_player	*p2 = &var.players[6];
	t_player	*p3 = &var.players[7];
	t_player	*p4 = &var.players[8];
	t_aargs		arg[8];
	char		result[1024] = {0};
	char		temp[512] = {0};
	t_lst_head	*list;
	t_lst_elem	*cursor;
	t_action	*action;
	const char	str[] = "p1.inventaire 101000000 - p2.avance 108000000 - p2.inventaire 109000000 - p3.voir 110000000 - p4.voir 112000000 - p4.connect_nbr 112000000 - p4.broadcast 119000000 - p1.incantation 401000000";

	bzero(arg, sizeof(t_aargs) * 8);
	dummy_t_zappy_without_board(&var);
	var.start_time = 100 * 1000000;
	var.tick = 1;
	dummy_t_player(&var, p1);
	dummy_t_player(&var, p2);
	dummy_t_player(&var, p3);
	dummy_t_player(&var, p4);
	arg[0].str = "p1.inventaire";
	action_add_wrapper(&var, p1, &arg[0], 4);
	arg[1].str = "p1.incantation";
	action_add_wrapper(&var, p1, &arg[1], 9);
	var.start_time = 101 * 1000000;
	arg[2].str = "p2.avance";
	action_add_wrapper(&var, p2, &arg[2], 0);
	var.start_time = 103 * 1000000;
	arg[3].str = "p3.voir";
	action_add_wrapper(&var, p3, &arg[3], 3);
	arg[4].str = "p2.inventaire";
	action_add_wrapper(&var, p2, &arg[4], 4);
	var.start_time = 105 * 1000000;
	arg[5].str = "p4.voir";
	action_add_wrapper(&var, p4, &arg[5], 3);
	arg[6].str = "p4.connect_nbr";
	action_add_wrapper(&var, p4, &arg[6], 11);
	arg[7].str = "p4.broadcast";
	action_add_wrapper(&var, p4, &arg[7], 8);

	list = &var.actions;
	cursor = list->first;
	while (cursor)
	{
		action = (t_action*)cursor->content;
		sprintf(temp, "%s %lld", action->arg.str, action->trigger_t);
		strcat(result, temp);
		bzero(temp, 512);
		if (cursor->next)
			strcat(result, " - ");
		cursor = cursor->next;
	}
	ck_assert_str_eq(result, str);
	rm_teams(&var.teams, &var.nb_team);
	lst_delete(&var.actions, free);
}
END_TEST

TCase*	queue_add_test(void)
{
	TCase	*tc;

	tc = tcase_create("queue_add_test");
	tcase_add_test(tc, queue_process);
	return (tc);
}

