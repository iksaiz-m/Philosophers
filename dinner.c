/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iksaiz-m <iksaiz-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:07:20 by iksaiz-m          #+#    #+#             */
/*   Updated: 2025/02/27 20:12:45 by iksaiz-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *dinner, char **av)
{
	// int	i;
	// int	p;

	// i = 1;
	// p = 0;
	dinner->number_of_philosopher = ft_long_atoi(av[1]);
	// while(i < dinner->number_of_philosopher)
	// {
	// 	dinner->filosophers[p] = i;
	// 	i++;
	// 	p++;
	// }
	dinner->forks = ft_long_atoi(av[1]);
	// while(i < forks)
	// {
	// 	if (pthread_mutex_init(&dinner->lockfork, NULL) != 0) { 
    //     printf("\n mutex init has failed\n");
    //     return (1); 
    // } 
	// }
	dinner->time_to_die = ft_long_atoi(av[2]);
	dinner->time_to_eat = ft_long_atoi(av[3]);
	dinner->time_to_sleep = ft_long_atoi(av[4]);
	if (av[5])
		dinner->number_of_times_each_philosopher_must_eat = ft_long_atoi(av[5]);
}
// void	print(t_philo *dinner)
// {
// 	printf("valor de time to die -> %zu\n", dinner->time_to_die);
// 	printf("valor de forks -> %d\n", dinner->forks);
// 	printf("valor de time to eat -> %zu\n", dinner->time_to_eat);
// 	printf("valor de time to sleep -> %zu\n", dinner->time_to_sleep);
// 	printf("valor de number of times -> %d\n", dinner->number_of_times_each_philosopher_must_eat);
// }

int i;

void	*philorutine(void* arg)
{
	t_philo dinner;

	i += 1;
	pthread_mutex_lock(&dinner.left_fork);
	pthread_mutex_lock(&dinner.right_fork);
	if (arg)
		printf("hola");
	printf("valor i: %d\n", i);
	pthread_mutex_unlock(&dinner.right_fork);
	pthread_mutex_unlock(&dinner.left_fork); 
	return NULL; 
}

void	init_thread(t_philo *dinner)
{
	int	i;
	int philo;
 
	i = 0;
	pthread_mutex_init(&dinner->left_fork, NULL);
	pthread_mutex_init(&dinner->right_fork, NULL);
	while (i < dinner->number_of_philosopher)
	{
		philo = pthread_create(&dinner->thread, NULL, &philorutine, NULL);
		i++;
		if (philo != 0)
		{
			printf("Error creating the thread \n");
			return ;
		}
	}
	pthread_join(dinner->thread, NULL);
	pthread_mutex_destroy(&dinner->left_fork); 
    pthread_mutex_destroy(&dinner->right_fork); 
}

int	main(int ac, char **av)
{
	t_philo dinner;
	int		i;

	i = 0;
	if (ac < 5 || ac > 6 || !handle_multiple_arguments(ac, av))
	{
		error2();
		return (1);
	}
	if (ft_long_atoi(av[1]) > 200)
	{
		printf("Error, too many philosophers\n");
		return(0);
	}
	init_philo(&dinner, av);
	init_thread(&dinner);

	// print(&dinner);
	// if (dinner.number_of_philosopher)
	return (0);
	//pthread_create
	//pthread_join
	//pthread_mutex_lock
	//pthread_mutex_init(&mutex, NULL)
	//pthread_mutex_lock
	//pthread_mutex_unlock
	// gettimeofday;
	// usleep();
	// pthread_mutex_destroy;
}





// pthread_mutex_t mutex;

// // the initial balance is 0
// int balance = 0;

// // write the new balance (after as simulated 1/4 second delay)
// void write_balance(int new_balance)
// {
//   usleep(250000);
//   balance = new_balance;
// }

// // returns the balance (after a simulated 1/4 seond delay)
// int read_balance()
// {
//   usleep(250000);
//   return balance;
// }

// // carry out a deposit
// void* deposit(void *amount)
// {
//   // lock the mutex
//   pthread_mutex_lock(&mutex);

//   // retrieve the bank balance
//   int account_balance = read_balance();

//   // make the update locally
//   account_balance += *((int *) amount);

//   // write the new bank balance
//   write_balance(account_balance);

//   // unlock to make the critical section available to other threads
//   pthread_mutex_unlock(&mutex);

//   return NULL;
// }

// int main()
// {
//   // mutex variable

//   // output the balance before the deposits
//   int before = read_balance();
//   printf("Before: %d\n", before);

//   // we'll create two threads to conduct a deposit using the deposit function
//   pthread_t thread1;
//   pthread_t thread2;

//   // initialize the mutex
//   pthread_mutex_init(&mutex, NULL);

//   // the deposit amounts... the correct total afterwards should be 500
//   int deposit1 = 300;
//   int deposit2 = 200;

//   // create threads to run the deposit function with these deposit amounts
//   pthread_create(&thread1, NULL, deposit, (void*) &deposit1);
//   pthread_create(&thread2, NULL, deposit, (void*) &deposit2);

//   // join the threads
//   pthread_join(thread1, NULL);
//   pthread_join(thread2, NULL);

//    // destroy the mutex
//   pthread_mutex_destroy(&mutex);

//   // output the balance after the deposits
//   int after = read_balance();
//   printf("After: %d\n", after);

//   return 0;
// }