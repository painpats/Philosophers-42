/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbourre <cbourre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:02:37 by cbourre           #+#    #+#             */
/*   Updated: 2023/04/01 18:48:27 by cbourre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// function that tell the philosopher to grab 2 fork in order to eat
int	grab_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->end_mtx);
	if (philo->game->end)
	{
		pthread_mutex_unlock(&philo->game->end_mtx);
		return (FAILURE);
	}
	pthread_mutex_unlock(&philo->game->end_mtx);
	pthread_mutex_lock(&(philo->game->forks[philo->first_fork]));
	print_action(philo, "has taken a fork");
	if (philo->game->nbr_philo == 1)
	{
		pthread_mutex_unlock(&(philo->game->forks[philo->first_fork]));
		return (FAILURE);
	}
	pthread_mutex_lock(&(philo->game->forks[philo->second_fork]));
	print_action(philo, "has taken a fork");
	return (SUCCESS);
}

// function that put down the forks
void	put_down_fork(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->game->forks[philo->second_fork]));
	pthread_mutex_unlock(&(philo->game->forks[philo->first_fork]));
}

// function that make the philosopher eat
int	is_eating(t_philo *philo)
{
	if (start_eating(philo) == FAILURE)
		return (FAILURE);
	while ((int)get_time() - philo->last_meal <= philo->game->time_to_eat)
	{
		pthread_mutex_unlock(&philo->last_meal_mtx);
		if (ft_mtx_lastmeal(philo) == FAILURE)
		{
			put_down_fork(philo);
			return (FAILURE);
		}
		pthread_mutex_lock(&philo->last_meal_mtx);
	}
	pthread_mutex_unlock(&philo->last_meal_mtx);
	pthread_mutex_lock(&philo->mtx);
	philo->count_meal += 1;
	if (philo->count_meal == philo->game->must_eat)
	{
		pthread_mutex_lock(&philo->game->last_mtx);
		philo->game->last_philo += 1;
		pthread_mutex_unlock(&philo->game->last_mtx);
	}
	pthread_mutex_unlock(&philo->mtx);
	put_down_fork(philo);
	return (SUCCESS);
}

// function that make the philosopher sleep
void	is_sleeping(t_philo *philo)
{
	unsigned long	now;

	pthread_mutex_lock(&philo->game->end_mtx);
	if (philo->game->end)
	{
		pthread_mutex_unlock(&philo->game->end_mtx);
		return ;
	}
	pthread_mutex_unlock(&philo->game->end_mtx);
	print_action(philo, "is sleeping");
	now = get_time();
	while ((int)(get_time() - now) <= philo->game->time_to_sleep)
	{
		pthread_mutex_lock(&philo->game->end_mtx);
		if (philo->game->end)
		{
			pthread_mutex_unlock(&philo->game->end_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->game->end_mtx);
		usleep(1000);
	}
}

// function that make the philosopher think
void	is_thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->end_mtx);
	if (philo->game->end)
	{
		pthread_mutex_unlock(&philo->game->end_mtx);
		return ;
	}
	pthread_mutex_unlock(&philo->game->end_mtx);
	print_action(philo, "is thinking");
}
