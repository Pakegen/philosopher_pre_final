/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:09:31 by qacjl             #+#    #+#             */
/*   Updated: 2025/04/18 14:03:19 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	init_philosophes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].nb_meal_eat = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].fork_left = &data->forks[i];
		data->philos[i].fork_right = &data->forks[(i + 1) % data->nb_philo];
		i++;
	}
}

static int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (0);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	return (1);
}

int	init_all(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (0);
	data->nb_philo = atoi_safe_nb(av[1]);
	data->time_to_die = atoi_safe_nb(av[2]);
	data->time_to_eat = atoi_safe_nb(av[3]);
	data->time_to_sleep = atoi_safe_nb(av[4]);
	if (ac == 6)
		data->must_eat = atoi_safe_nb(av[5]);
	else
		data->must_eat = -1;
	if (data->nb_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0
		|| data->time_to_sleep <= 0
		|| (ac == 6 && data->must_eat <= 0))
		return (0);
	data->someone_die = 0;
	data->start_time = get_time();
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (0);
	if (!init_mutexes(data))
		return (0);
	init_philosophes(data);
	return (1);
}
