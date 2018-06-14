#ifndef ARG_H
#define ARG_H

TCase*	arg_get_opt(void);
TCase*	arg_get_opt_string(void);
TCase*	arg_get_opt_int(void);
TCase*	arg_read_arguments(void);
TCase*	arg_check_arguments(void);

#endif
