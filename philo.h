/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:14:51 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/05/11 19:29:12 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(PHILO_H)
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdbool.h>

# define MAX_INT	2147483647

typedef struct s_table	t_table;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}	t_forks;

typedef struct s_philo
{
	int				id;
	int				forks;
	long			last_meal;
	long			meals_eaten;
	bool			full;
	bool			death;
	pthread_t		thread_id;
	t_table			*dinner;
	t_forks			*left_fork;
	t_forks			*right_fork;
	// pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	last_meal_mutex;
}	t_philo;

typedef struct s_table
{
	long			number_of_philosopher;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_each_philosopher_must_eat;
	long			time_of_start;
	bool			ending_flag;
	pthread_mutex_t	lock;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_t		chef;
	t_philo			*philos;
	t_forks			*forks;
}	t_table;

//arguments
void	error(void);
int		handle_multiple_arguments(int ac, char **av);
long	ft_long_atoi(const char *str);

//utils.c
size_t	ft_strlen(const char *str);
long	get_time(void);
void	write_status(t_philo *philo, char *str);
void	take_fork(t_philo *philo);
bool	death_philo(t_philo *philo);

//utils2.c
int		ft_usleep(size_t milliseconds);
bool	philo_is_dead(t_philo *philo);

//init.c
int		init_table(t_table *dinner);
void	init_data(t_table *dinner, char **av);

//actions.c
void	sleep_action(t_philo *philo);
void	think_action(t_philo *philo);
void	eat_action(t_philo *philo);

//finish.c
void	finish_dinner(t_table *dinner);

//monitoring.c
bool	check_end_flag(t_table *chef, int i);

#endif // PHILO_H
