#include <stdlib.h>
#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(command_player_voir_test)
{
	t_zappy		var;
	t_player	*p = &var.players[6];
	t_action	*action;

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 10;
	var.board_size[1] = 10;
	dummy_t_zappy_add_board(&var);
	dummy_t_player(&var, p);
	command_voir(&var, p, NULL);
	action = find_player_first_action(p, &var);
	ck_assert_ptr_eq(action->run, &action_player_voir);
	clean_msg_queue(p);
	action_player_clear(p, &var);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(command_player_inventaire_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	t_action	*action;
	char		gstr[] = "pin 6 0 0 10 0 0 0 0 0 0\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_player(&var, p);
	dummy_t_player_gfx(&var, gfx);
	command_inventaire(&var, p, NULL);
	action = find_player_first_action(p, &var);
	ck_assert_ptr_eq(action->run, &action_player_inventaire);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(p);
	clean_msg_queue(gfx);
	action_player_clear(p, &var);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(command_player_prend_test)
{
	int			i = 0;
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	t_action	*action;
	char		ressources[8][16] = {"nourriture", "linemate",
	"deraumere", "sibur", "mendiane", "phiras", "thystame", "caca"};
	char		gstr[] = "pgt 6 0\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_board(&var);
	dummy_t_player_gfx(&var, gfx);
	dummy_t_player(&var, p);
	while (i < 8)
	{
		if (i < 7)
			gstr[6] = i + '0';
		else
			gstr[6] = '0';
		command_prend(&var, p, ressources[i]);
		action = find_player_first_action(p, &var);
		ck_assert_ptr_eq(action->run, &action_player_prend);
		ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
		action_player_clear(p, &var);
		clean_msg_queue(gfx);
		++i;
	}
	clean_msg_queue(p);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(command_player_pose_test)
{
	int			i = 0;
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	t_action	*action;
	char		ressources[8][16] = {"nourriture", "linemate",
	"deraumere", "sibur", "mendiane", "phiras", "thystame", "caca"};
	char		gstr[] = "pdr 6 0\n";

	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_board(&var);
	dummy_t_player_gfx(&var, gfx);
	dummy_t_player(&var, p);
	while (i < 8)
	{
		if (i < 7)
			gstr[6] = i + '0';
		else
			gstr[6] = '0';
		command_pose(&var, p, ressources[i]);
		action = find_player_first_action(p, &var);
		ck_assert_ptr_eq(action->run, &action_player_pose);
		ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
		action_player_clear(p, &var);
		clean_msg_queue(gfx);
		++i;
	}
	clean_msg_queue(p);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	commands_player_ressources_test(void)
{
	TCase	*tc;

	tc = tcase_create("player_voir");
	tcase_add_test(tc, command_player_voir_test);
	tcase_add_test(tc, command_player_inventaire_test);
	tcase_add_test(tc, command_player_prend_test);
	tcase_add_test(tc, command_player_pose_test);
	return (tc);
}
