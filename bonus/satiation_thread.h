/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   satiation_thread.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:20:55 by najacque          #+#    #+#             */
/*   Updated: 2022/07/29 16:20:55 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SATIATION_THREAD_H
# define SATIATION_THREAD_H

# include "sems.h"

typedef struct s_st_arg
{
	int		nphilo;
	t_sems	*sems;
}	t_st_arg;

void	*ft_satiation_thread(void *data);
int		ft_sat_thread(int nphilo, t_sems *sems, pthread_t *thread_buf);

#endif
