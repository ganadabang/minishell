/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:32:50 by gpaeng            #+#    #+#             */
/*   Updated: 2022/02/21 16:56:55 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "mush/builtin.h"

static int	ft_isintf(const char *s)
{
	long long	num;

	if (!s)
		return (0);
	s += (ft_strchr("+-", *s) != NULL);
	if (*s == '\0')
		return (0);
	s += ft_strspn(s, "0");
	if (ft_strlen(s) > 10)
		return (0);
	num = ft_atoll(s);
	if ((num > 2147483647) || (num < -2147483648))
		return (0);
	s += ft_strspn(s, "0123456789");
	if (*s != '\0')
		return (0);
	return (1);
}

int	builtin_exit(t_state *state, int argc, char *argv[])
{
	(void)state;
	if (argc > 2)
	{
		ft_dputs(2, "mush: exit: too many arguments\n");
		return (1);
	}
	if (argc == 1)
		exit(0);
	if (ft_isintf(argv[1]) == 0)
	{
		ft_dputs(2, "mush: exit: ");
		ft_dputs(2, argv[1]);
		ft_dputs(2, ": numberic argument required\n");
		exit(255);
	}
	exit(ft_atoi(argv[1]));
}
