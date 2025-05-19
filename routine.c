/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:09:15 by qacjl             #+#    #+#             */
/*   Updated: 2025/04/18 14:01:27 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_right);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_left);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->fork_right);
		print_action(philo, "has taken a fork");
	}
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->death_mutex);
	print_action(philo, "is eating");
	dormir(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	philo->nb_meal_eat++;
}

int	is_simulation_running(t_data *data)
{
	int	running;

	pthread_mutex_lock(&data->death_mutex);
	running = !data->someone_die;
	pthread_mutex_unlock(&data->death_mutex);
	return (running);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(philo->fork_left);
		print_action(philo, "has taken a fork");
		dormir(philo->data->time_to_die, philo->data);
		pthread_mutex_unlock(philo->fork_left);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (is_simulation_running(philo->data))
	{
		eat(philo);
		if (philo->data->must_eat > 0
			&& philo->nb_meal_eat >= philo->data->must_eat)
			break ;
		print_action(philo, "is sleeping");
		dormir(philo->data->time_to_sleep, philo->data);
		print_action(philo, "is thinking");
	}
	return (NULL);
}
