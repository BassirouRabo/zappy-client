#include <check.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(command_player_avance_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	t_action	*action;
	char		gstr[] = "ppo 6 0 1 1\n";

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 4;
	var.board_size[1] = 4;
	dummy_t_zappy_add_board(&var);
	dummy_t_player_gfx(&var, gfx);
	dummy_t_player(&var, p);
	command_avance(&var, p, NULL);
	action = find_player_first_action(p, &var);
	ck_assert_ptr_eq(action->run, &action_player_avance);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(gfx);
	clean_msg_queue(p);
	action_player_clear(p, &var);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(command_player_droite_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	t_action	*action;
	char		gstr[] = "ppo 6 0 0 2\n";

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 4;
	var.board_size[1] = 4;
	dummy_t_zappy_add_board(&var);
	dummy_t_player_gfx(&var, gfx);
	dummy_t_player(&var, p);
	command_droite(&var, p, NULL);
	action = find_player_first_action(p, &var);
	ck_assert_ptr_eq(action->run, &action_player_droite);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(gfx);
	clean_msg_queue(p);
	action_player_clear(p, &var);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(command_player_gauche_test)
{
	t_zappy		var;
	t_player	*gfx = &var.players[5];
	t_player	*p = &var.players[6];
	t_action	*action;
	char		gstr[] = "ppo 6 0 0 4\n";

	dummy_t_zappy_without_board(&var);
	var.board_size[0] = 4;
	var.board_size[1] = 4;
	dummy_t_zappy_add_board(&var);
	dummy_t_player_gfx(&var, gfx);
	dummy_t_player(&var, p);
	command_gauche(&var, p, NULL);
	action = find_player_first_action(p, &var);
	ck_assert_ptr_eq(action->run, &action_player_gauche);
	ck_assert_str_eq(gfx->snd.buf[gfx->snd.read], gstr);
	clean_msg_queue(gfx);
	clean_msg_queue(p);
	action_player_clear(p, &var);
	rm_board(&var.board, var.board_size, var.board_size[0], var.board_size[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	commands_moves(void)
{
	TCase	*tc;

	tc = tcase_create("player_moves");
	tcase_add_test(tc, command_player_avance_test);
	tcase_add_test(tc, command_player_droite_test);
	tcase_add_test(tc, command_player_gauche_test);
	return (tc);
}
