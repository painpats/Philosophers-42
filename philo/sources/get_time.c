/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbourre <cbourre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:02:37 by cbourre           #+#    #+#             */
/*   Updated: 2023/04/01 18:48:27 by cbourre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// fonction that suspend execution for microsecond intervals
void	ft_usleep(int nbr)
{
	long long	time;

	time = get_time();
	while (get_time() - time <= nbr)
		usleep(1000);
}

// function that get the time of each action
long long	get_time(void)
{
	struct timeval	time;
	long long		u_sec;

	gettimeofday(&time, NULL);
	u_sec = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (u_sec);
}
