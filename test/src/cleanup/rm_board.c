#include <stdlib.h>
#include <check.h>
#include <stdio.h>
#include "serveur.h"

int		***gen_board(int size[2], int fail_i, int fail_j)
{
	int		i;
	int		j;
	int		***board = NULL;

	if (!(board = (int ***)malloc(sizeof(int **) * size[0])))
	{
		dprintf(2, "Can't malloc needed memory for test\n");
		return (NULL);
	}
	i = 0;
	while (i < size[0] && i <= fail_i)
	{
		j = 0;
		if (!(board[i] = (int **)malloc(sizeof(int *) * size[1])))
		{
			dprintf(2, "Can't malloc needed memory for test\n");
			return (NULL);
		}
		while (j < size[1] && (j <= fail_j || i < fail_i))
		{
			if (!(board[i][j] = (int *)malloc(sizeof(int) * 7)))
			{
				dprintf(2, "Can't malloc needed memory for test\n");
				return (NULL);
			}
			++j;
		}
		++i;
	}
	return (board);
}

START_TEST(rm_board_full_board)
{
	int		***board;
	int		size[2] = {10, 10};

	board = gen_board(size, 10, 10);
	ck_assert_msg(NULL != board, "Can't allocate needed memory for test");
	rm_board(&board, size, size[0], size[1]);
	ck_assert_ptr_eq(NULL, board);
}
END_TEST

START_TEST(rm_board_middle_row)
{
	int		***board;
	int		size[2] = {10, 10};

	board = gen_board(size, 5, 5);
	ck_assert_msg(NULL != board, "Can't allocate needed memory for test");
	rm_board(&board, size, 5, 4);
	ck_assert_ptr_eq(NULL, board);
}
END_TEST

START_TEST(rm_board_start_row)
{
	int		***board;
	int		size[2] = {10, 10};

	board = gen_board(size, 5, 10);
	ck_assert_msg(NULL != board, "Can't allocate needed memory for test");
	rm_board(&board, size, 5, 10);
	ck_assert_ptr_eq(NULL, board);
}
END_TEST

TCase*	cleanup_rm_board(void)
{
	TCase	*tc;

	tc = tcase_create("rm_board");
	tcase_add_test(tc, rm_board_full_board);
	tcase_add_test(tc, rm_board_middle_row);
	tcase_add_test(tc, rm_board_start_row);
	return (tc);
}
