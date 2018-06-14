#include <check.h>
#include <unistd.h>
#include <stdio.h>
#include "serveur.h"
#include "test_dummies.h"

START_TEST(connexion_do_write_normal)
{
	int			pipe_fd[2];
	int			ret;
	int			i = 0;
	t_zappy		var;
	t_server	serv;
	t_player	*p;
	char		str[SND_SIZE + 1];
	char		rd[SND_SIZE + 1];

	ck_assert(pipe(pipe_fd) == 0);
	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_serv(&serv);
	p = &var.players[pipe_fd[1]];
	dummy_t_player(&var, p);
	ck_assert_int_eq(p->id, pipe_fd[1]);
	memset(str, '0', SND_SIZE);
	str[SND_SIZE] = 0;
	while (i < 3)
	{
		add_msg_to_player(p, str, SND_SIZE - 1, 1);
		++i;
	}
	str[SND_SIZE - 1] = '\n';
	ck_assert_str_eq(str, p->snd.buf[p->snd.read]);
	ck_assert_str_eq(str, p->snd.buf[p->snd.read + 1]);
	ck_assert_str_eq(str, p->snd.buf[p->snd.read + 2]);
	do_write(&var, &serv, pipe_fd[1]);
	i = 0;
	while (i < 3)
	{
		ck_assert_int_eq((ret = read(pipe_fd[0], rd, SND_SIZE)), SND_SIZE);
		rd[ret] = 0;
		ck_assert_str_eq(rd, str);
		++i;
	}
	ck_assert_int_eq(p->snd.read, p->snd.write);
	clean_msg_queue(p);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

START_TEST(connexion_do_write_linked_list)
{
	int			pipe_fd[2];
	int			ret;
	int			i = 0;
	t_zappy		var;
	t_server	serv;
	t_player	*p;
	char		str[SND_SIZE + 1];
	char		rd[SND_SIZE + 1];

	ck_assert(pipe(pipe_fd) == 0);
	dummy_t_zappy_without_board(&var);
	dummy_t_zappy_add_remaining_in_team(&var);
	dummy_t_serv(&serv);
	p = &var.players[pipe_fd[1]];
	dummy_t_player(&var, p);
	ck_assert_int_eq(p->id, pipe_fd[1]);
	memset(str, '0', SND_SIZE);
	str[SND_SIZE] = 0;
	while (i < 3)
	{
		add_msg_to_player_lst(p, str, SND_SIZE, 1);
		++i;
	}
	str[SND_SIZE - 1] = '\n';
	do_write(&var, &serv, pipe_fd[1]);
	i = 0;
	while (i < 3)
	{
		ck_assert_int_eq((ret = read(pipe_fd[0], rd, SND_SIZE)), SND_SIZE);
		rd[ret] = 0;
		ck_assert_str_eq(rd, str);
		++i;
	}
	ck_assert_int_eq(p->snd.read, p->snd.write);
	clean_msg_queue(p);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	rm_teams(&var.teams, &var.nb_team);
}
END_TEST

TCase*	connexion_do_write(void)
{
	TCase	*tc;

	tc = tcase_create("do_write");
	tcase_add_test(tc, connexion_do_write_normal);
	tcase_add_test(tc, connexion_do_write_linked_list);
	return (tc);
}
