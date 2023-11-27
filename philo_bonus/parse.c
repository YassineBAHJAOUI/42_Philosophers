/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahjaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:58:11 by ybahjaou          #+#    #+#             */
/*   Updated: 2023/09/28 17:09:37 by ybahjaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int narg, char **argv)
{
	int	i;

	i = 0;
	if (narg != 5 && narg != 6)
		return (ft_error("Invalid number of arguments, variables:\n \
◦[1] Number of philosophers \n \
◦[2] Time to die (milliseconds) \n \
◦[3] Time to eat (milliseconds)\n \
◦[4] Time to sleep (milliseconds)\n \
◦[5] Number of times each philosopher must eat (OPTIONAL)"));
	while (--narg > 0)
	{
		i = -1;
		while (argv[narg][++i])
			if (argv[narg][i] < '0' || argv[narg][i] > '9')
				return (ft_error("Arguments can only be \
unsigned positive integers."));
	}
	return (0);
}

int	ft_atoi_mod(const char *str)
{
	long			number;
	int				i;

	number = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	if (number > 2147483647)
		return (ft_error("Values ​​must be in the \
range of unsigned int.") * -1);
	return (number);
}

int	parse_data(int narg, char **argv, t_data *data)
{
	data->ends = 0;
	data->flag = 0;
	data->n_philos = ft_atoi_mod(argv[1]);
	data->time_dead = ft_atoi_mod(argv[2]);
	data->time_eat = ft_atoi_mod(argv[3]);
	data->time_sleep = ft_atoi_mod(argv[4]);
	if (narg == 6)
	{
		data->ends = 1;
		data->n_eats = ft_atoi_mod(argv[5]);
	}
	if (data->n_philos < 0 || data->time_dead < 0 \
	|| data->time_eat < 0 || data->time_sleep < 0)
		return (1);
	if (data->n_philos == 0)
		return (ft_error("There is no philosopher."));
	if (data->n_philos > 242)
		return (ft_error("The maximum number of philosophers is 242."));
	data->stop_sem = sem_open("/stop", O_CREAT, 0644, 0);
	data->talk = sem_open("/talk", O_CREAT, 0644, 1);
	data->forks = sem_open("/forks", O_CREAT, 0644, data->n_philos / 2);
	if (data->stop_sem == SEM_FAILED || data->talk == SEM_FAILED \
	|| data->forks == SEM_FAILED)
		return (ft_error("Error creating the stop semaphore."));
	return (0);
}

int	parse_philo(t_data *data, t_philos *philo, int i)
{
	while (++i < data->n_philos)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = timer();
		philo[i].last_meal = 0;
		philo[i].data = data;
		philo[i].philo_sem = sem_open("/philo_sem", O_CREAT, 0644, 1);
		philo[i].n_meals = sem_open("/n_meals", O_CREAT, 0644, 0);
		if (philo[i].philo_sem == SEM_FAILED || philo[i].n_meals == SEM_FAILED)
			return (ft_error("Error creating the last meal semaphore."));
	}
	return (0);
}

int	parse(int narg, char **argv, t_data *data, t_philos *philo)
{
	if (check_args(narg, argv) != 0)
		return (1);
	if (parse_data(narg, argv, data) != 0)
		return (1);
	if (parse_philo(data, philo, -1) != 0)
		return (1);
	return (0);
}
