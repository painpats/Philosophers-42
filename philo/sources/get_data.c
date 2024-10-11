/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbourre <cbourre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:40:12 by cbourre           #+#    #+#             */
/*   Updated: 2023/04/01 10:50:19 by cbourre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// function that initialize the data's structure : args into params
int	init_data(t_data *game, int argc, char **argv)
{
	game->nbr_philo = ft_atol(argv[1]);
	if (game->nbr_philo > 250)
		return (FAILURE);
	game->time_to_die = ft_atol(argv[2]);
	game->time_to_eat = ft_atol(argv[3]);
	game->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		game->must_eat = ft_atol(argv[5]);
	else
		game->must_eat = -1;
	return (SUCCESS);
}

// function that malloc the number of philosophers, forks and threads
int	malloc_data(t_data *game)
{
	game->team_philo = malloc(sizeof(t_philo) * game->nbr_philo);
	if (!game->team_philo)
		return (FAILURE);
	game->forks = malloc(sizeof(pthread_mutex_t) * game->nbr_philo);
	if (!game->forks)
	{
		free(game->team_philo);
		return (FAILURE);
	}
	pthread_mutex_init(&game->end_mtx, NULL);
	pthread_mutex_init(&game->m_mtx, NULL);
	pthread_mutex_init(&game->death_mtx, NULL);
	pthread_mutex_init(&game->last_mtx, NULL);
	return (SUCCESS);
}

// function that initialize the philo's structure
void	init_philo(t_data *game)
{
	int	i;

	i = -1;
	while (game->nbr_philo > ++i)
	{
		game->team_philo[i].philo_id = i;
		pthread_mutex_init(&game->forks[i], NULL);
		pthread_mutex_init(&game->team_philo[i].mtx, NULL);
		pthread_mutex_init(&game->team_philo[i].last_meal_mtx, NULL);
		game->team_philo[i].first_fork = i;
		game->team_philo[i].second_fork = (i + 1) % game->nbr_philo;
		game->team_philo[i].game = game;
		game->team_philo[i].count_meal = 0;
	}
}

// function that start eating
int	start_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->end_mtx);
	if (philo->game->end)
	{
		put_down_fork(philo);
		pthread_mutex_unlock(&philo->game->end_mtx);
		return (FAILURE);
	}
	pthread_mutex_unlock(&philo->game->end_mtx);
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_mtx);
	philo->last_meal = get_time();
	return (SUCCESS);
}
