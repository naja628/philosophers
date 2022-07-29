/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killer_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:20:42 by najacque          #+#    #+#             */
/*   Updated: 2022/07/29 16:20:44 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "killer_thread.h"
#include "timestamp.h"

void	*ft_killer_thread(void *arg)
{
	t_kt_data	data;
	int			now;

	data = *(t_kt_data *) arg;
	now = ft_timestamp(0);
	while (1)
	{
		if (now - *(data.last_ate) > data.time_to_die)
		{
			sem_wait(data.sems->guard_sem);
			printf("%d %d %s\n", now, data.iphilo, "died");
			sem_post(data.sems->finished_sem);
			return (NULL);
		}
		else
			usleep(1000 * (*(data.last_ate) + data.time_to_die - now));
		now = ft_timestamp(0);
	}
}
