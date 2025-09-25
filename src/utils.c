/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lukorman <lukorman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 01:34:30 by lukorman          #+#    #+#             */
/*   Updated: 2025/09/25 01:56:50 by lukorman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_atoi(const char *nptr);
void	ms_sleep(long long ms);

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		res;
	int		sig;

	i = 0;
	res = 0;
	sig = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sig = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (res * sig);
}

void	ms_sleep(long long ms)
{
	long long	start;

	start = get_current_timestamp();
	while ((get_current_timestamp() - start) < ms)
		usleep(100);
}
