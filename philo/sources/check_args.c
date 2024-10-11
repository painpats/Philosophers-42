/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbourre <cbourre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:48:48 by cbourre           #+#    #+#             */
/*   Updated: 2023/03/31 18:46:14 by cbourre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	args_error(int i)
{
	if (i == 1)
	{
		m_error("invalid number of philosophers\n");
		return (FAILURE);
	}
	if (i == 2)
	{
		m_error("invalid time_to_die\n");
		return (FAILURE);
	}
	if (i == 3)
	{
		m_error("invalid time_to_eat\n");
		return (FAILURE);
	}
	if (i == 4)
	{
		m_error("invalid time_to_sleep\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	ft_check_digit(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
		{
			m_error("arguments must all be numeric\n");
			return (-1);
		}
		i++;
	}
	return (i);
}

// function that check if the argument is a digit
static int	ft_isdigit(char *arg)
{
	int	i;
	int	j;

	j = 0;
	if (arg[0] == '\0')
	{
		m_error("empty argument\n");
		return (FAILURE);
	}
	while (arg[j] == '0')
		j++;
	i = ft_check_digit(arg);
	if (i == -1)
		return (FAILURE);
	if (i - j > 10)
	{
		m_error("too long argument\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

// function that check the arguments
int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (ft_atol(argv[i]) <= 0 || ft_atol(argv[i]) > 2147483647)
		{
			if (args_error(i) == FAILURE)
				return (FAILURE);
		}
		if (ft_isdigit(argv[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	if (argc == 6)
	{
		if (ft_atol(argv[5]) <= 0 || ft_atol(argv[5]) > 2147483647)
		{
			m_error("invalid number of time each philosopher must eat\n");
			return (FAILURE);
		}	
		if (ft_isdigit(argv[i]) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

// function that check if the philosopher.s ate every meal.s
int	ft_mtx_lastmeal(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->end_mtx);
	if (philo->game->end)
	{
		pthread_mutex_unlock(&philo->game->end_mtx);
		return (FAILURE);
	}
	pthread_mutex_unlock(&philo->game->end_mtx);
	return (SUCCESS);
}
