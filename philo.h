/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:14:51 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/02/27 20:06:33 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(PHILO_H)
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>


	typedef struct s_philo
{
	int				number_of_philosopher;
	int				*filosophers;
	int				forks;
	size_t			time_of_start;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				meals_eaten;
	int				death;
	pthread_t		thread;
	pthread_mutex_t right_fork;
	pthread_mutex_t left_fork;
}	t_philo;

typedef struct s_phi
{
	t_philo *dinners;
}	t_phi;


//arguments
void	error2(void);
int		handle_multiple_arguments(int ac, char **av);
long	ft_long_atoi(const char *str);
#endif // PHILO_H
