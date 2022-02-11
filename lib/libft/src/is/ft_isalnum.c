/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:14:02 by SSONG             #+#    #+#             */
/*   Updated: 2022/02/10 18:01:19 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

inline static int	ft_isalpha(int c)
{
	return (((unsigned char)c >= 'a' && (unsigned char)c <= 'z')
			|| ((unsigned char)c >= 'A' && (unsigned char)c <= 'Z'));
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) \
		|| ((unsigned char)c >= '0' && (unsigned char)c <= '9'));
}
