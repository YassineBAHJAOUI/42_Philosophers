/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:38:24 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/09/28 15:43:57 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

/*verification si la philo est mort 
Calcule le temps depuis le dernier repas du philosophe
Vérifie si le temps dépasse le temps limite pour manger
Signale que le philosophe est mort
Si le philosophe n'a pas atteint le nombre de repas souhaité met le flag à 1
Indique que le philosophe est toujours en vie*/
int	check_death(int i, t_philos *philo, int *flag)
{
	int		time;

	while (++i < philo->data->n_philos)
	{
		pthread_mutex_lock(&philo[i].mutex_eat);
		pthread_mutex_lock(&philo->data->stop_mutex);
		time = timer() - philo[i].last_meal;
		if (time > philo[i].data->time_dead)
		{
			philo->data->stop = 0;
			pthread_mutex_unlock(&philo->data->stop_mutex);
			pthread_mutex_unlock(&philo[i].mutex_eat);
			pthread_mutex_lock(&philo->data->talk);
			printf("(%ld) Philo %d is dead.\n", timer() - \
			philo->data->time_start, philo[i].id);
			pthread_mutex_unlock(&philo->data->talk);
			return (0);
		}
		pthread_mutex_unlock(&philo->data->stop_mutex);
		if (philo->data->ends == 1 && philo[i].n_meals < philo->data->n_eats)
			*(flag) = 1;
		pthread_mutex_unlock(&philo[i].mutex_eat);
	}
	return (1);
}

int	check_all_eat(t_philos *philo, int flag)
{
	if (philo->data->ends == 1 && flag == 0)
	{
		pthread_mutex_lock(&philo->data->stop_mutex);
		philo->data->stop = 0;
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_mutex_lock(&philo->data->talk);
		printf("All the philosophers have eaten!\n");
		pthread_mutex_unlock(&philo->data->talk);
		return (0);
	}
	return (1);
}

/* Cette boucle parcourt tous les philosophes pour vérifier s'ils sont morts
Cette condition vérifie si tous les philosophes ont terminé leurs repas */
void	*check_thread(void	*param)
{
	int			i;
	t_philos	*philo;
	int			flag;

	philo = (t_philos *)param;
	pthread_mutex_lock(&philo->data->stop_mutex);
	while (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		i = -1;
		flag = 0;
		usleep(10);
		if (check_death(i, philo, &flag) == 0)
			return (NULL);
		if (check_all_eat(philo, flag) == 0)
			return (NULL);
		pthread_mutex_lock(&philo->data->stop_mutex);
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
	return (NULL);
}
