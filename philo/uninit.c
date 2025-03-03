/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uninit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:15:57 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/01 13:50:36 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_mutex(t_data *data, int p_count)
{
	int (i);
	i = -1;
	data->death_flag = false;
	while (++i < p_count)
		pthread_mutex_init(&data->fork[i], NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->ts_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->reservation, NULL);
}

void	uninit_mutex(t_data *data, t_philo *philo)
{
	long (i);
	i = -1;
	while (++i < philo->philo_count)
		pthread_mutex_destroy(&data->fork[i]);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->ts_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->reservation);
}

void	join_threads(pthread_t *thread, int p_count)
{
	int (i);
	i = -1;
	while (++i < p_count)
		pthread_join(thread[i], NULL);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long milliseconds)
{
	long	start;
	long	elapsed;

	start = get_time();
	elapsed = 0;
	while (elapsed < milliseconds)
	{
		usleep(500);
		elapsed = get_time() - start;
	}
}
