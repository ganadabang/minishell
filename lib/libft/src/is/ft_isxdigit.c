/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 21:47:49 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/10 18:03:08 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isxdigit(int c)
{
	return (((unsigned char)c >= 0x41 && (unsigned char)c <= 0x46) \
			|| ((unsigned char)c >= 0x30 && (unsigned char)c <= 0x39) \
			|| ((unsigned char)c >= 0x41 && (unsigned char)c <= 0x5a));
}
