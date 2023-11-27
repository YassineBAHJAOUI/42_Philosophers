/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:33:41 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/09/28 16:35:09 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct data
{
	int				n_philos;
	int				time_dead;
	int				time_eat;
	int				time_sleep;
	int				n_eats;
	short int		ends;
	short int		flag;
	long			time_start;
	sem_t			*talk;
	sem_t			*stop_sem;
	sem_t			*forks;
}				t_data;

typedef struct philo
{
	pid_t				pid;
	int					id;
	long				last_meal;
	t_data				*data;
	sem_t				*philo_sem;
	sem_t				*n_meals;
}				t_philos;

int		parse(int narg, char **argv, t_data *data, t_philos *philo);
void	check_philos(t_philos *philo);
void	philo_fork(t_philos *philo);
void	printf_sem(char *str, t_philos *philo);
long	timer(void);
void	ft_usleep(int ms);
int		ft_error(char *s);

#endif
