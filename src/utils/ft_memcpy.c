/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:30:40 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/11 17:30:41 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
void *ft_memcpy(void *dest, const void *src, size_t n)
{
    char *dtmp;
    const char *stmp;
    
    if (!dest && !src)
        return (0);
    dtmp = dest;
    stmp = src;
    while (n--)
    {
        *dtmp++ = *stmp++;
    }
    return (dest);
}
