#ifndef TEST_DUMMIES_H
#define TEST_DUMMIES_H
#include "serveur.h"

void	dummy_t_zappy_without_board(t_zappy *var);
void	dummy_t_zappy_add_board(t_zappy *var);
void	dummy_t_board_square(int *square);
void	dummy_t_zappy_add_remaining_in_team(t_zappy *var);
void	dummy_t_serv(t_server *serv);
void	dummy_t_player_client(t_zappy *var, t_player *p);
void	dummy_t_player(t_zappy *var, t_player *p);
void	dummy_t_player_gfx(t_zappy *var, t_player *p);
void	dummy_t_player_fill_buffer(t_player *p);
void	dummy_t_player_default(t_player *p);

#endif
