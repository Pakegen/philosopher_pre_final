/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:09:22 by qacjl             #+#    #+#             */
/*   Updated: 2025/04/18 14:04:04 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*monitoring(void *arg)
{
	t_data	*data;
	int		i;
	long	now;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->death_mutex);
			now = get_time();
			if (!data->someone_die
				&& now - data->philos[i].last_meal > data->time_to_die)
			{
				data->someone_die = 1;
				pthread_mutex_lock(&data->print);
				printf("%ld %d died\n", now - data->start_time,
					data->philos[i].id);
				pthread_mutex_unlock(&data->print);
				pthread_mutex_unlock(&data->death_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->death_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
