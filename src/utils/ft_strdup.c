/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:30:47 by gpaeng            #+#    #+#             */
/*   Updated: 2021/11/11 17:30:48 by gpaeng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
char *ft_strdup(const char *str)
{
    char *arr;
    
    if (!(arr = malloc(sizeof(char) * (ft_strlen(str) + 1))))
        return (0);
    ft_memcpy(arr, str, ft_strlen(str) + 1);
    return (arr);
}