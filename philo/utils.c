/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:00:24 by yabarhda          #+#    #+#             */
/*   Updated: 2025/02/26 16:09:24 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	the_end(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->death_flag = true;
	pthread_mutex_unlock(&data->death_mutex);
}

void	death_wish(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->death_flag = true;
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_lock(&data->ts_mutex);
	data->t_stamp = get_time() - data->init_time;
	printf("%ld %d died\n", data->t_stamp, philo->id);
	pthread_mutex_unlock(&data->ts_mutex);
	pthread_mutex_unlock(&data->meal_mutex);
}
