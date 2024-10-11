/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbourre <cbourre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:43:48 by cbourre           #+#    #+#             */
/*   Updated: 2023/04/01 11:07:34 by cbourre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_data
{
	int				philo_death;
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				end;
	int				last_philo;
	struct s_philo	*team_philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	end_mtx;
	pthread_mutex_t	m_mtx;
	pthread_mutex_t	last_mtx;
	pthread_mutex_t	death_mtx;
	unsigned long	time;
	long long		time_death;
}	t_data;

typedef struct s_philo
{
	int				philo_id;
	int				first_fork;
	int				second_fork;
	int				last_meal;
	int				count_meal;
	t_data			*game;
	pthread_t		threads;
	pthread_mutex_t	last_meal_mtx;
	pthread_mutex_t	mtx;
}	t_philo;

#endif
