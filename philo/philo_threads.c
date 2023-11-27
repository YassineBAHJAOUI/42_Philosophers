/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:56:15 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/09/28 16:13:02 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*fonction est exécutée si un seul philosophe est présent*/
void	*exception(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->data->n_philos == 1)
	{
		printf_mutex("is thinking.", philo);
		pthread_mutex_lock(&philo->data->stop_mutex);
		while (philo->data->stop == 1)
		{
			pthread_mutex_unlock(&philo->data->stop_mutex);
			usleep(1);
			pthread_mutex_lock(&philo->data->stop_mutex);
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
	}
	pthread_exit(NULL);
}

/* fonction simule le processus de manger d'un philosophe
utilisant des mutex pour éviter les conflits de fourchettes*/
void	eat(t_philos *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->fork_r);
		printf_mutex("has taken the right fork.", philo);
		pthread_mutex_lock(philo->fork_l);
		printf_mutex("has taken the left fork.", philo);
	}
	else
	{
		pthread_mutex_lock(philo->fork_l);
		printf_mutex("has taken the left fork.", philo);
		pthread_mutex_lock(&philo->fork_r);
		printf_mutex("has taken the right fork.", philo);
	}
	pthread_mutex_lock(&philo->mutex_eat);
	printf_mutex("is eating.", philo);
	philo->last_meal = timer();
	philo->n_meals++;
	pthread_mutex_unlock(&philo->mutex_eat);
	ft_usleep(philo->data->time_eat, philo);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(&philo->fork_r);
}

/*fonction est exécutée par chaque philosophe dans un thread 
séparé pour simuler leur comportement général*/
void	*philo_thread(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(&philo->data->stop_mutex);
	while (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		eat(philo);
		printf_mutex("is sleaping.", philo);
		ft_usleep(philo->data->time_sleep, philo);
		if (philo->data->time_sleep == 0)
			usleep(1);
		printf_mutex("is thinking.", philo);
		pthread_mutex_lock(&philo->data->stop_mutex);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	pthread_exit(NULL);
}
