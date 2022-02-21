/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:16:00 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/21 17:35:57 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "libhx/array.h"

int	hx_array_secure(t_array *array, size_t new_cap)
{
	if (array->cap >= new_cap)
		return (1);
	if (array->data == NULL)
		array->data = (void **)ft_calloc(new_cap, sizeof(void *));
	else
	{
		array->data = (void **)ft_realloc(array->data, array->len \
		* sizeof(void *), new_cap * sizeof(void *));
	}
	if (!array->data)
		return (0);
	array->cap = new_cap;
	return (1);
}

int	hx_array_push(t_array *array, void *value)
{
	size_t	new_cap;

	if (array->cap <= array->len)
	{
		new_cap = 2 * array->len;
		if (new_cap == 0)
			new_cap = 8;
		if (!hx_array_secure(array, new_cap))
			return (0);
	}
	array->data[array->len] = value;
	array->len += 1;
	return (1);
}

void	hx_array_cleanup(t_array *array)
{
	free(array->data);
	array->data = NULL;
	array->cap = 0;
	array->len = 0;
	return ;
}

void	*hx_array_pop_index(t_array *array, size_t i)
{
	size_t	last_index;
	void	*ret;

	ret = array->data[i];
	last_index = array->len - 1;
	array->data[i] = array->data[last_index];
	array->data[last_index] = NULL;
	array->len -= 1;
	return (ret);
}
