/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:43:49 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/01 13:49:47 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

long	ft_atoi(const char *str)
{
	long (v), sign = 1, result = 0;
	(void)v;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	is_alpha(char *s)
{
	int (v), i = 0;
	(void)v;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			i++;
			continue ;
		}
		else
			return (1);
	}
	return (0);
}

int	parse_args(int ac, char *av[])
{
	int (v), i = 0;
	(void)v;
	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philo [philo count] [time to die] [time to eat] \
[time to sleep] [eat count]\n");
		return (0);
	}
	if (ft_atoi(av[1]) > 200)
		return (0);
	if (ac == 6 && ft_atoi(av[5]) == 0)
		return (0);
	while (++i < ac)
	{
		if (!av[i][0])
			return (0);
		if (ft_atoi(av[i]) < 0)
			return (0);
		if (is_alpha(av[i]))
			return (0);
	}
	return (1);
}

void	init_philos(t_philo *philo, char *av[], t_data *data, int i)
{
	philo->id = i + 1;
	philo->well_fed = false;
	philo->philo_count = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->right_fork = philo->id % philo->philo_count;
	philo->left_fork = philo->id - 1;
	philo->e_f = 0;
	if (av[5])
	{
		philo->eat_count = ft_atoi(av[5]);
		philo->e_f = 1;
	}
	philo->meals_eaten = 0;
	philo->last_meal = get_time();
	philo->data = data;
}

int	main(int argc, char *argv[])
{
	t_data		data;
	t_philo		philo[200];
	pthread_t	thread[200];

	if (!parse_args(argc, argv))
		return (1);
	if (ft_atoi(argv[1]) == 0)
		return (1);
	int (p_count), i = -1;
	p_count = ft_atoi(argv[1]);
	init_mutex(&data, p_count);
	while (++i < p_count)
		init_philos(&philo[i], argv, &data, i);
	i = -1;
	data.t_stamp = 0;
	data.init_time = get_time();
	while (++i < p_count)
		pthread_create(&thread[i], NULL, philosopher, &philo[i]);
	monitor_philos(philo, &data);
	join_threads(thread, p_count);
	uninit_mutex(&data, philo);
	return (0);
}
