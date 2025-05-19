/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:09:19 by qacjl             #+#    #+#             */
/*   Updated: 2025/04/18 14:05:56 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	atoi_safe_nb(char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		res = res * 10 + str[i] - '0';
		if (res > 2147483647)
			return (-1);
		i++;
	}
	if (res == 0)
		return (-1);
	return (res);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	dormir(long time_ms, t_data *data)
{
	long	start;

	start = get_time();
	while (get_time() - start < time_ms)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->someone_die)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		usleep(100);
	}
}

void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->someone_die)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id,
			msg);
		pthread_mutex_unlock(&philo->data->print);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}
