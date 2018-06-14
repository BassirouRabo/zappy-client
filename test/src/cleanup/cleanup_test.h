#ifndef CLEANUP_TEST_H
# define CLEANUP_TEST_H

TCase*	cleanup_rm_teams(void);
TCase*	cleanup_rm_board(void);
TCase*	cleanup_cleanup_game(void);

int		***gen_board(int size[2], int fail_i, int fail_j);

#endif
