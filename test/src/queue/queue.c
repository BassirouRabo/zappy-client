#include <check.h>
#include "queue.h"

Suite*	suite_queue(void)
{
	Suite	*s;

	s = suite_create("queue");
	suite_add_tcase(s, queue_add_test());
	return (s);
}
