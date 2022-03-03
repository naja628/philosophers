#ifndef TIME_OPS_H
# define TIME_OPS_H

/* compute diff between 2 'time.h' 'struct timeval's
 * as a number of milliseconds
 * hopefully overflow safe as long as the result is within an int
 */
int	ft_tv_diff_ms(struct timeval const *t, struct timeval const *u);

/* return number of ms elapsed since start of program 
 * (techinally since last called with 'now_p' being true) */
int ft_timestamp(int start_p);

#endif
