/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbourre <cbourre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:07:42 by cbourre           #+#    #+#             */
/*   Updated: 2023/04/01 11:07:38 by cbourre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc < 5 || argc > 6)
	{
		m_error("invalid number of arguments\n");
		return (FAILURE);
	}
	memset(&game, 0, sizeof(t_data));
	if (check_args(argc, argv) == FAILURE)
		return (FAILURE);
	if (init_data(&game, argc, argv) == FAILURE)
	{
		m_error("too many philosophers\n");
		return (FAILURE);
	}
	if (malloc_data(&game) == FAILURE)
	{
		m_error("wrong pthread_create\n");
		return (FAILURE);
	}
	init_philo(&game);
	init_players(&game);
	ft_end_game(&game);
	return (SUCCESS);
}
