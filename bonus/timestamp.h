/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:20:57 by najacque          #+#    #+#             */
/*   Updated: 2022/07/29 16:20:57 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMESTAMP_H
# define TIMESTAMP_H

# include <sys/time.h>
# include <stddef.h>

# define TS_RESET 1

unsigned int	ft_timestamp(int reset);

#endif
