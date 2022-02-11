/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 17:25:26 by SSONG             #+#    #+#             */
/*   Updated: 2022/02/11 14:08:29 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if ((unsigned char)c >= 0x61 && (unsigned char)c <= 0x7a)
		return ((unsigned char)c + 0x20);
	return ((unsigned char)c);
}
