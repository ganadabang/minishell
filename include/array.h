/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 21:08:07 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/01/24 23:33:37 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct s_array {
	void	**data;
	size_t	len;
	size_t	cap;
}	t_array;

bool	hx_array_secure(t_array *array, size_t new_cap);
bool	hx_array_push(t_array *array, void *value);
void	hx_array_cleanup(t_array *array);

#endif
