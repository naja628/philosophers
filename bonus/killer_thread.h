/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killer_thread.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:20:54 by najacque          #+#    #+#             */
/*   Updated: 2022/07/29 16:20:54 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KILLER_THREAD_H
# define KILLER_THREAD_H

# include "sems.h"

// note : last_ate needs to be accesible from outside scope
typedef struct s_kt_data
{
	int		iphilo;
	int		*last_ate;
	t_sems	*sems;
	int		time_to_die;
}	t_kt_data;

void	*ft_killer_thread(void *arg);
void	ft_launch_killer_thread(int i, int *last_ate, t_sems *sems, int t_die);

#endif
