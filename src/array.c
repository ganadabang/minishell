/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:16:00 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/04 17:24:58 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

bool	hx_array_secure(t_array *array, size_t new_cap)
{
	if (array->cap >= new_cap)
		return (true);
	array->data = (void **)realloc(array->data, new_cap *sizeof(void *));
	if (!array->data)
		return (false);
	array->cap = new_cap;
	return (true);
}

bool	hx_array_push(t_array *array, void *value)
{
	size_t	new_cap;

	if (array->cap <= array->len)
	{
		new_cap = 2 * array->len;
		if (new_cap == 0)
			new_cap = 8;
		if (!hx_array_secure(array, new_cap))
			return (false);
	}
	array->data[array->len] = value;
	array->len += 1;
	return (true);

}
void	hx_array_cleanup(t_array *array)
{
	free(array->data);
	array->data = NULL;
	array->cap = 0;
	array->len = 0;
	return ;
}
