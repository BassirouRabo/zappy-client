#include <stdlib.h>
#include <check.h>
#include "serveur.h"
#include "action.h"

Suite*	suite_actions(void)
{
	Suite	*s;

	s = suite_create("actions");
	suite_add_tcase(s, action_player_moves());
	suite_add_tcase(s, action_player_voir_test());
	suite_add_tcase(s, action_player_ressources_test());
	suite_add_tcase(s, action_player_broadcast_test());
	suite_add_tcase(s, action_player_life_test());
	return (s);
}
