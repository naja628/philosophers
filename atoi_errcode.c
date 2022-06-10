/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_errcode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:47:56 by najacque          #+#    #+#             */
/*   Updated: 2021/12/14 15:47:56 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

typedef unsigned int	t_uint;

static int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else
		return (0);
}

/* note : as unsigned, INT_MIN = - INT_MIN
 * try to update the value of *acc
 * if we're going to overflow return (0)
 * otherwise return (1) */
static int	ft_try_update(int sign, t_uint *acc, t_uint digit)
{
	t_uint	max;

	if (sign == 1)
		max = INT_MAX;
	else
		max = (t_uint) -INT_MIN; // TODO compiler warning
	if (*acc <= max / 10)
		*acc *= 10;
	else
		return (0);
	if (*acc <= max - digit)
		*acc += digit;
	else
		return (0);
	return (1);
}

/* special version of atoi that sets errcode to -1 
 * when we overflow an int or if s is not an integer 
 * representation (using stricter rules than atoi) */
int	ft_atoi_errcode(const char *s, int *errcode)
{
	int		sign;
	t_uint	acc;

	if (*errcode)
		return (0);
	while (('\t' <= *s && *s <= '\r') || *s == ' ')
		++s;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*(s++) == '-')
			sign = -1;
	}
	acc = 0;
	while (*errcode != -1 && ft_isdigit(*s))
	{
		if (ft_try_update(sign, &acc, *s - '0'))
			++s;
		else
			*errcode = -1;
	}
	if (*s != '\0')
		*errcode = -1;
	return (sign * acc);
}
