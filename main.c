/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:09:28 by qacjl             #+#    #+#             */
/*   Updated: 2025/04/18 14:04:24 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	monitor;
	int			i;

	i = 0;
	if (!init_all(&data, ac, av))
		return (1);
	while (i < data.nb_philo)
	{
		pthread_create(&data.philos[i].thread, NULL, routine, &data.philos[i]);
		i++;
	}
	i = 0;
	pthread_create(&monitor, NULL, monitoring, &data);
	while (i < data.nb_philo)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	exit_clean(&data);
	return (0);
}
