/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:13:59 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/01 13:49:40 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	monitor_philos(t_philo *philo, t_data *data)
{
	long (count), i;
	while (1)
	{
		count = 0;
		i = -1;
		while (++i < philo->philo_count)
		{
			pthread_mutex_lock(&data->meal_mutex);
			if (philo[i].well_fed)
				count++;
			if ((get_time() - philo[i].last_meal) >= philo[i].time_to_die)
				return (death_wish(&philo[i], data), (void)0);
			pthread_mutex_unlock(&data->meal_mutex);
		}
		if (count == philo->philo_count)
			return (the_end(data), (void)0);
		usleep(1000);
	}
}

void	unlock_forks(t_philo *philo)
{
	if (philo->id == philo->philo_count)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
	}
}

int	_print(t_philo *philo, int f)
{
	bool (permission);
	permission = true;
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->death_flag)
		return (pthread_mutex_unlock(&philo->data->death_mutex), 0);
	pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->data->ts_mutex);
	pthread_mutex_lock(&philo->data->death_mutex);
	permission = !philo->data->death_flag;
	pthread_mutex_unlock(&philo->data->death_mutex);
	if (permission)
	{
		philo->data->t_stamp = get_time() - philo->data->init_time;
		if (f == 0)
			printf("%ld %d has taken a fork\n", philo->data->t_stamp, philo->id);
		else if (f == 1)
			printf("%ld %d is eating\n", philo->data->t_stamp, philo->id);
		else if (f == 2)
			printf("%ld %d is sleeping\n", philo->data->t_stamp, philo->id);
		else if (f == 3)
			printf("%ld %d is thinking\n", philo->data->t_stamp, philo->id);
	}
	pthread_mutex_unlock(&philo->data->ts_mutex);
	return (permission);
}

int	_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->reservation);
	if (philo->id == philo->philo_count)
	{
		pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->reservation);
		pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->reservation);
		pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	}
	if (!_print(philo, 0) || !_print(philo, 0) || !_print(philo, 1))
		return (unlock_forks(philo), 0);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	if (philo->e_f && (philo->meals_eaten == philo->eat_count))
		philo->well_fed = true;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(philo->time_to_eat);
	unlock_forks(philo);
	return (1);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->philo_count == 1)
	{
		_print(philo, 0);
		return (ft_usleep(philo->time_to_die), NULL);
	}
	if (!(philo->id % 2))
		usleep(1000);
	while (1)
	{	
		if (!_eat(philo))
			return (NULL);
		if (!_print(philo, 2))
			return (NULL);
		ft_usleep(philo->time_to_sleep);
		if (!_print(philo, 3))
			return (NULL);
		if (philo->philo_count % 2)
			usleep(1000);
	}
	return (NULL);
}
