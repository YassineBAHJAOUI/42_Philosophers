/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:13:32 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/09/28 16:16:14 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*fonction renvoie le temps écoulé en millisecondes
depuis le début de l'exécution du programme*/
int	timer(void)
{
	struct timeval	actual_time;

	gettimeofday(&actual_time, NULL);
	return ((actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000));
}

/* fonction fait dormir le thread pendant un certain nombre de millisecondes*/
void	ft_usleep(int ms, t_philos *philo)
{
	int	time;

	time = timer();
	pthread_mutex_lock(&philo->data->stop_mutex);
	while ((timer() - time < ms) && philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		usleep(10);
		pthread_mutex_lock(&philo->data->stop_mutex);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
}

void	printf_mutex(char *str, t_philos *philo)
{
	int	time;

	pthread_mutex_lock(&philo->data->talk);
	time = timer() - philo->data->time_start;
	pthread_mutex_lock(&philo->data->stop_mutex);
	if (philo->data->stop == 1)
		printf("(%d) ms Philo %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_mutex_unlock(&philo->data->talk);
}
