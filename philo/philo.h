/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:02:01 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/09/26 15:37:22 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

// Structure de données pour les informations des philosophes
typedef struct data
{
	int				n_philos;
	int				time_dead;
	int				time_eat;
	int				time_sleep;
	int				n_eats;
	short int		ends;
	short int		stop;
	long			time_start;
	pthread_mutex_t	talk;
	pthread_mutex_t	stop_mutex;
	pthread_t		starvation;
}				t_data;
// Structure de données pour un philosophe individuel
typedef struct philo
{
	int					id;
	int					n_meals;
	int					last_meal;
	pthread_t			thread;
	pthread_mutex_t		fork_r;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		mutex_eat;
	t_data				*data;
}				t_philos;

int		parse(int narg, char **argv, t_data *data, t_philos *philo);
void	*philo_thread(void *arg);
void	*check_thread(void	*param);
void	printf_mutex(char *str, t_philos *philo);
int		timer(void);
void	ft_usleep(int ms, t_philos *philo);
int		ft_error(char *s);
void	*exception(void *arg);

#endif
