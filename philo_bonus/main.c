/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:33:06 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/09/28 16:44:02 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

/*Fonction qui supprime les sémaphores existants*/
void	preclean(void)
{
	sem_unlink("/forks");
	sem_unlink("/talk");
	sem_unlink("/stop");
	sem_unlink("/n_meals");
	sem_unlink("/philo_sem");
}

int	main(int narg, char **argv)
{
	t_data			data;
	t_philos		philo[242];
	int				i;

	preclean();
	if (parse(narg, argv, &data, philo) != 0)
		return (1);
	i = -1;
	data.time_start = timer();
	while (++i < data.n_philos)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			philo_fork(&philo[i]);
			exit(EXIT_SUCCESS);
		}
		if (philo[i].pid < 0)
			return (ft_error("Failed to create the processes."));
	}
	if (philo->pid > 0)
		check_philos(philo);
	return (0);
}
