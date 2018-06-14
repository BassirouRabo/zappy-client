#include <stdlib.h>
#include <check.h>
#include "serveur.h"
#include "arg.h"

Suite*	suite_arg(void)
{
	Suite	*s;

	s = suite_create("arg");
	suite_add_tcase(s, arg_get_opt());
	suite_add_tcase(s, arg_get_opt_string());
	suite_add_tcase(s, arg_get_opt_int());
	suite_add_tcase(s, arg_read_arguments());
	suite_add_tcase(s, arg_check_arguments());
	return (s);
}
