/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:44:25 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/09/28 16:50:14 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*fonction de nettoyage*/
void	close_and_clean(t_philos *philo, pid_t eat)
{
	int	i;

	kill(eat, SIGKILL);
	i = -1;
	while (++i < philo->data->n_philos)
		kill(philo[i].pid, SIGKILL);
	sem_unlink("/forks");
	sem_unlink("/talk");
	sem_unlink("/stop");
	sem_close(philo->data->stop_sem);
	sem_close(philo->data->talk);
	sem_close(philo->data->forks);
	i = -1;
	while (++i < philo->data->n_philos)
	{
		sem_unlink("/philo_sem");
		sem_close(philo[i].philo_sem);
		sem_unlink("/n_meals");
		sem_close(philo[i].n_meals);
	}
}

/*fonction vérifier si tous les philosophes ont terminé de manger*/
void	check_eat(void	*param)
{
	t_philos	*philo;
	int			n_philos;
	int			i;
	int			j;

	philo = (t_philos *)param;
	n_philos = philo->data->n_philos;
	i = -1;
	while (++i < n_philos)
	{
		j = -1;
		while (++j < philo->data->n_eats)
			sem_wait(philo[i].n_meals);
	}
	sem_wait(philo->data->talk);
	printf("All the philosophers have eaten!\n");
	sem_post(philo->data->stop_sem);
}

/*fonction qui vérifier et nettoyer */
void	check_philos(t_philos *philo)
{
	pid_t	eat;

	eat = fork();
	if (eat == 0)
	{
		if (philo->data->ends == 1)
			check_eat(philo);
		exit(EXIT_SUCCESS);
	}
	sem_wait(philo->data->stop_sem);
	close_and_clean(philo, eat);
}
