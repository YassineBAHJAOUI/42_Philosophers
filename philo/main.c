/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:01:48 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/09/26 15:01:51 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Fonction d'affichage des erreurs
int	ft_error(char *s)
{
	int	i;

	i = 0;
	write (2, "❌ \033[31;1m", 12);
	while (s[i])
	{
		write (2, &s[i], sizeof(char));
		i++;
	}
	write (2, "\n\033[0m", 6);
	return (1);
}

// Fonction de nettoyage des ressources et de fermeture des threads
void	close_and_clean(t_philos *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->n_philos)
		pthread_join(philo[i].thread, NULL);
	pthread_join(philo->data->starvation, NULL);
	i = -1;
	while (++i < philo->data->n_philos)
	{
		pthread_mutex_destroy(&philo[i].fork_r);
		pthread_mutex_destroy(&philo[i].mutex_eat);
	}
	pthread_mutex_destroy(&philo->data->talk);
	pthread_mutex_destroy(&philo->data->stop_mutex);
}

int	main(int narg, char **argv)
{
	t_data			data;
	t_philos		philo[242];
	int				i;

	if (parse(narg, argv, &data, philo) != 0)
		return (1);
	i = -1;
	data.time_start = timer();
	if (data.n_philos == 1)
		if (pthread_create(&philo[0].thread, NULL, exception, &philo[0]))
			return (ft_error("Error creating mutex."));
	if (data.n_philos != 1)
		while (++i < data.n_philos)
			if (pthread_create(&philo[i].thread, NULL, philo_thread, &philo[i]))
				return (ft_error("Error creating mutex."));
	if (pthread_create(&data.starvation, NULL, check_thread, philo))
		return (ft_error("Error creating mutex."));
	close_and_clean(philo);
	return (0);
}
