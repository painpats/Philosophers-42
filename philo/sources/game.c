/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbourre <cbourre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 18:02:55 by cbourre           #+#    #+#             */
/*   Updated: 2023/04/01 18:50:45 by cbourre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// function that create the threads
static int	ft_create_th(t_data *game, pthread_t *th, int i)
{
	game->team_philo[i].last_meal = get_time();
	if (pthread_create(&th[i], NULL, ft_begin_game,
			&game->team_philo[i]) != 0)
		return (FAILURE);
	if (pthread_create(&game->team_philo[i].threads, NULL,
			(void *)check_death, &game->team_philo[i]) != 0)
		return (FAILURE);
	return (SUCCESS);
}

// function that initialize the game
int	init_players(t_data *game)
{
	pthread_t	*th;
	int			i;

	i = -1;
	game->time = get_time();
	th = malloc(game->nbr_philo * sizeof(pthread_t *));
	if (!th)
		return (FAILURE);
	while (game->nbr_philo > ++i)
	{
		if (ft_create_th(game, th, i) == FAILURE)
			return (FAILURE);
	}
	i = -1;
	while (game->nbr_philo > ++i)
	{
		if (pthread_join(th[i], NULL))
			return (FAILURE);
		if (pthread_join(game->team_philo[i].threads, NULL))
			return (FAILURE);
	}
	free(th);
	return (SUCCESS);
}

// function that run the game
void	*ft_begin_game(void *struc)
{
	t_philo	*ph;

	ph = (t_philo *)struc;
	if (ph->philo_id % 2 == 1)
		ft_usleep(200);
	while (1)
	{
		if (grab_fork(ph) == FAILURE)
			break ;
		if (is_eating(ph) == FAILURE)
			break ;
		if (nbr_of_meal(ph))
			break ;
		is_sleeping(ph);
		is_thinking(ph);
	}
	return (NULL);
}

// function that check if a philosopher died
int	check_death(void *struc)
{
	t_philo	*ph;

	ph = (t_philo *)struc;
	pthread_mutex_lock(&ph->game->end_mtx);
	while (!ph->game->end)
	{
		pthread_mutex_unlock(&ph->game->end_mtx);
		pthread_mutex_lock(&ph->last_meal_mtx);
		if (((int)get_time() - ph->last_meal) >= ph->game->time_to_die)
		{
			pthread_mutex_unlock(&ph->last_meal_mtx);
			pthread_mutex_lock(&ph->game->death_mtx);
			ph->game->philo_death = ph->philo_id + 1;
			ph->game->time_death = get_time() - ph->game->time;
			pthread_mutex_unlock(&ph->game->death_mtx);
			pthread_mutex_lock(&ph->game->end_mtx);
			ph->game->end = RIP;
			pthread_mutex_unlock(&ph->game->end_mtx);
			return (RIP);
		}
		pthread_mutex_unlock(&ph->last_meal_mtx);
		pthread_mutex_lock(&ph->game->end_mtx);
	}
	pthread_mutex_unlock(&ph->game->end_mtx);
	return (0);
}

// function that end the game when a philosopher died
void	ft_end_game(t_data *game)
{
	int	i;

	if (game->end == RIP)
		printf("%lld\t%d\tdied\n", game->time_death, game->philo_death);
	i = -1;
	usleep(2000);
	pthread_mutex_destroy(&game->m_mtx);
	pthread_mutex_destroy(&game->end_mtx);
	pthread_mutex_destroy(&game->last_mtx);
	pthread_mutex_destroy(&game->death_mtx);
	while (game->nbr_philo > ++i)
	{
		pthread_mutex_destroy(&game->team_philo[i].mtx);
		pthread_mutex_destroy(&game->team_philo[i].last_meal_mtx);
	}
	free(game->team_philo);
	i = -1;
	while (game->nbr_philo > ++i)
		pthread_mutex_destroy(&game->forks[i]);
	free(game->forks);
}
