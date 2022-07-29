/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:20:51 by najacque          #+#    #+#             */
/*   Updated: 2022/07/29 16:20:51 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timestamp.h"

unsigned int	ft_timestamp(int reset)
{
	static struct timeval	start;
	struct timeval			now;
	unsigned int			diff_ms;

	if (reset == TS_RESET)
	{
		gettimeofday(&start, NULL);
		return (0);
	}
	gettimeofday(&now, NULL);
	diff_ms = 1000 * (now.tv_sec - start.tv_sec);
	diff_ms += ((int) now.tv_usec - (int) start.tv_usec) / 1000;
	return (diff_ms);
}
