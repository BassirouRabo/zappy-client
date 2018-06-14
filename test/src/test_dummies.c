#include <stdlib.h>
#include <check.h>
#include <time.h>
#include "serveur.h"

void	dummy_t_zappy_without_board(t_zappy *var)
{
	int i = 0;
	t_tstmp	loop_time;

	bzero(var, sizeof(t_zappy));
	bzero(&var->actions, sizeof(t_lst_head));
	var->board = (int ***)0xdeadbeaf;
	var->board_size[0] = 1;
	var->board_size[1] = 2;
	var->team_size = 3;
	var->tick = 4;
	var->fd_max = &i;
	gettimeofday(&loop_time, NULL);
	var->start_time = time_long(loop_time);
	var->nb_team = 3;
	var->teams = (t_team *)malloc(sizeof(t_team) * 3);
	bzero(var->teams, sizeof(t_team) * 3);
	strcpy(var->teams[0].name, "toto");
	var->teams[0].remain = 0;
	strcpy(var->teams[1].name, "tutu");
	var->teams[1].remain = 0;
	strcpy(var->teams[2].name, "GRAPHIC");
	var->teams[2].remain = 0;
}

void	dummy_t_zappy_add_board(t_zappy *var)
{
	int		i = 0;
	int		j = 0;

	var->board = (int ***)malloc(sizeof(int **) * var->board_size[0]);
	while (i < var->board_size[0])
	{
		var->board[i] = (int **)malloc(sizeof(int *) * var->board_size[1]);
		j = 0;
		while (j < var->board_size[1])
		{
			var->board[i][j] = (int *)malloc(sizeof(int) * 7);
			bzero(var->board[i][j], sizeof(int) * 7);
			++j;
		}
		++i;
	}
}

void	dummy_t_board_square(int *square)
{
	int		i = 0;

	while (i < 7)
	{
		square[i] = i + 1;
		++i;
	}
}

void	dummy_t_zappy_add_remaining_in_team(t_zappy *var)
{
	int	i = 0;

	while (i < var->nb_team)
	{
		++var->teams[i].remain;
		++i;
	}
}

void	dummy_t_serv(t_server *serv)
{
	serv->sock = 5;
	serv->port = 6;
	serv->fd_max = 7;
	serv->fd_sel = 8;
}

void	dummy_t_player_client(t_zappy *var, t_player *p)
{
	size_t	i = 3;

	while (i < MAX_FD && &var->players[i] != p)
		++i;
	bzero(p, sizeof(t_player));
	p->id = i;
	p->snd.pos = p->snd.buf[p->snd.write];
	p->status = FD_USED;
	p->timeofdeath = time_generate(1260, var->start_time, var);
	p->pending_actions = 0;
}

void	dummy_t_player(t_zappy *var, t_player *p)
{
	dummy_t_player_client(var, p);
	p->status = FD_CLIENT;
	p->team = &(var->teams[0]);
}

void	dummy_t_player_gfx(t_zappy *var, t_player *p)
{
	dummy_t_player(var, p);
	var->gfx_client = p;
	p->status = FD_GFX;
}

void	dummy_t_player_fill_buffer(t_player *p)
{
	p->snd.lst.first = lst_create("caca", 5);
	p->snd.lst.last = p->snd.lst.first;
	p->rcv.remain = (char *)malloc(16);
	p->snd.lst.size = 1;
	strcpy(p->rcv.remain, "caca");
}

void	dummy_t_player_default(t_player *p)
{
	p->level = 1;
	p->facing = 2;
	p->coord[0] = 3;
	p->coord[1] = 4;
	p->inv[0] = 5;
	p->inv[1] = 6;
	p->inv[2] = 7;
	p->inv[3] = 8;
	p->inv[4] = 9;
	p->inv[5] = 10;
}
