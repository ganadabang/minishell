/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mush_fatal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:12:54 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/11 15:49:58 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	mush_fatal(const char *fn_name)
{
	perror(fn_name);
	exit(1);
}
