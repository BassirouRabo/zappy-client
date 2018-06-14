#include <stdlib.h>
#include <check.h>
#include "serveur.h"

START_TEST(connexion_client_error_)
{
	t_player	p;

	bzero(&p, sizeof(t_player));
	p.status = FD_CLIENT;
	p.snd.pos = p.snd.buf[p.snd.write];
	client_error(&p, "caca");
	ck_assert_int_eq(FD_CLOSE, p.status);
	ck_assert_int_eq(0, p.snd.write);
	ck_assert_ptr_eq(p.snd.buf[p.snd.write] + 5, p.snd.pos);
}
END_TEST

TCase*	connexion_client_error(void)
{
	TCase	*tc;

	tc = tcase_create("client_error");
	tcase_add_test(tc, connexion_client_error_);
	return (tc);
}
