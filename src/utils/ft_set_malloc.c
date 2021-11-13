/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:35:54 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/13 13:36:11 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

char *ft_set_malloc(int size)
{
    char *arr;
    int i;

    i = 0;
    if (!(arr = (char *)malloc(sizeof(char) * size)))
        return (0);
    while (i < size)
    {
        arr[i] = 0;
        i++;
    }
    arr[i] = '\0';
    return (arr);
}
