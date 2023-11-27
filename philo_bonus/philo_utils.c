/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 17:06:53 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/09/28 17:06:57 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	timer(void)
{
	struct timeval	actual_time;

	gettimeofday(&actual_time, NULL);
	return ((actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000));
}

void	ft_usleep(int ms)
{
	long	time;

	time = timer();
	while ((timer() - time) < ms)
		usleep(10);
}

void	printf_sem(char *str, t_philos *philo)
{
	int	time;

	time = timer() - philo->data->time_start;
	sem_wait(philo->data->talk);
	printf("(%d) Philo %d %s\n", time, philo->id, str);
	sem_post(philo->data->talk);
}
