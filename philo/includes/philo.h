/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbourre <cbourre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:48:13 by cbourre           #+#    #+#             */
/*   Updated: 2023/04/01 18:11:49 by cbourre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include "struct.h"

# define SUCCESS 0
# define FAILURE 1
# define RIP 1
# define YUM 2

// check_args.c
int			check_args(int argc, char **argv);
int			ft_mtx_lastmeal(t_philo *philo);

// get_data.c
int			init_data(t_data *game, int argc, char **argv);
int			malloc_data(t_data *game);
void		init_philo(t_data *game);
int			start_eating(t_philo *philo);

// game.c
int			init_players(t_data *game);
void		*ft_begin_game(void *struc);
int			check_death(void *argv);
void		ft_end_game(t_data *game);

// action.c
void		put_down_fork(t_philo *philo);
int			grab_fork(t_philo *philo);
int			is_eating(t_philo *philo);
void		is_sleeping(t_philo *philo);
void		is_thinking(t_philo *philo);

// get_time.c
void		ft_usleep(int nbr);
long long	get_time(void);

// utils.c
int			m_error(char *str);
size_t		ft_strlen(const char *str);
long		ft_atol(const char *nptr);
void		print_action(t_philo *ph, char *str);
int			nbr_of_meal(t_philo *philo);

#endif
