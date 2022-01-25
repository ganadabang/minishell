/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 16:57:45 by SSONG             #+#    #+#             */
/*   Updated: 2022/01/25 01:21:43 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ctype.h"

int	ft_isalpha(int c)
{
	return (((unsigned char)c >= 'a' && (unsigned char)c <= 'z')
			|| ((unsigned char)c >= 'A' && (unsigned char)c <= 'Z'));
}
