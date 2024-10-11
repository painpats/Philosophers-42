/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbourre <cbourre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:11:41 by cbourre           #+#    #+#             */
/*   Updated: 2023/04/01 11:06:39 by cbourre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// function that print the error message
int	m_error(char *str)
{
	write(2, "Error : ", 8);
	write(2, str, ft_strlen(str));
	return (FAILURE);
}

// function that get the length of the string in parameter
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

// function that convert a string str to a long integer
long	ft_atol(const char *nptr)
{
	long	i;
	long	sym;
	long	nbr;

	i = 0;
	sym = 1;
	nbr = 0;
	while (nptr[i] == '0' || nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sym = sym * -1;
		i++;
	}
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + (nptr[i] - '0');
		i++;
	}
	return (sym * nbr);
}

//function that print actions on the terminal
void	print_action(t_philo *ph, char *str)
{
	long long	infos_time;

	infos_time = (get_time() - ph->game->time);
	pthread_mutex_lock(&ph->game->m_mtx);
	pthread_mutex_lock(&ph->game->end_mtx);
	if (!ph->game->end)
		printf("%lld\t%d\t%s\n", infos_time, ph->philo_id + 1, str);
	pthread_mutex_unlock(&ph->game->end_mtx);
	pthread_mutex_unlock(&ph->game->m_mtx);
}

// function that check if we reach the must_eat
int	nbr_of_meal(t_philo *philo)
{
	int	i;

	i = -1;
	if (philo->game->must_eat == -1)
		return (0);
	while (philo->game->nbr_philo > ++i)
	{
		pthread_mutex_lock(&philo->game->team_philo[i].mtx);
		if (philo->game->team_philo[i].count_meal < philo->game->must_eat)
		{
			pthread_mutex_unlock(&philo->game->team_philo[i].mtx);
			return (0);
		}
		pthread_mutex_unlock(&philo->game->team_philo[i].mtx);
	}
	pthread_mutex_lock(&philo->game->end_mtx);
	philo->game->end = YUM;
	pthread_mutex_unlock(&philo->game->end_mtx);
	return (1);
}
