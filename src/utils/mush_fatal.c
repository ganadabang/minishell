/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mush_fatal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:12:54 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/19 05:03:28 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "mush.h"

void	mush_fatal(const char *fn_name)
{
	perror(fn_name);
	exit(1);
}
