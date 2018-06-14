#ifndef TEST_CONNEXION_H
#define TEST_CONNEXION_H

TCase*	connexion_close_client(void);
TCase*	connexion_client_error(void);
TCase*	connexion_affect_team(void);
TCase*	connexion_process_input(void);
TCase*	connexion_read_buffer(void);
TCase*	connexion_do_read(void);
TCase*	connexion_do_write(void);

#endif
