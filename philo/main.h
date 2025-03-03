/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabarhda <yabarhda@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:39:49 by yabarhda          #+#    #+#             */
/*   Updated: 2025/03/01 13:49:33 by yabarhda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_data
{
	pthread_mutex_t		fork[200];
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		ts_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		reservation;
	long				init_time;
	long				t_stamp;
	bool				death_flag;
}						t_data;

typedef struct s_philo
{
	t_data			*data;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			eat_count;
	long			meals_eaten;
	long			philo_count;
	long			last_meal;
	int				id;
	int				e_f;
	int				right_fork;
	int				left_fork;
	bool			well_fed;
}					t_philo;

void	ft_usleep(long milliseconds);

long	get_time(void);

void	*philosopher(void *data);
void	monitor_philos(t_philo *philo, t_data *data);
void	init_mutex(t_data *data, int p_count);
void	uninit_mutex(t_data *data, t_philo *philo);
void	join_threads(pthread_t *thread, int p_count);
void	death_wish(t_philo *philo, t_data *data);
void	the_end(t_data *data);
int		_print(t_philo *philo, int f);

#endif