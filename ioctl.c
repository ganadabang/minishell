/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioctl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:58:25 by hyeonsok          #+#    #+#             */
/*   Updated: 2021/10/18 19:58:19 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>

/* input/output control */
int	main(int argc, char *argv[])
{
	struct winsize	size;

	if (argc != 2 || argv[1] == NULL)
		return (1);
	if (ioctl(atoi(argv[1]), TIOCGWINSZ, &size) == -1)
		return (1);
	printf("Terminal ws_row:\t%d\n",size.ws_row);
	printf("Terminal ws_col:\t%d\n",size.ws_col);
	size.ws_row = 100;
	size.ws_col = 100;
	if (ioctl(atoi(argv[1]), TIOCSWINSZ, &size) == -1)
		return (1);
	printf("Terminal ws_row:\t%d\n",size.ws_row);
	printf("Terminal ws_col:\t%d\n",size.ws_col);
	return (0);
}
