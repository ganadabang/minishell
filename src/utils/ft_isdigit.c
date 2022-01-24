/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 15:40:49 by gpaeng            #+#    #+#             */
/*   Updated: 2022/01/24 23:41:07 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush/builtin.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
