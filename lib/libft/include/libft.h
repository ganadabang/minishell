/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 20:51:02 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/11 14:39:32 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "libft/is.h"
# include "libft/io.h"
# include "libft/string.h"

void		*ft_calloc(size_t count, size_t size);
int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);

/* Not in libc */
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(const char *input, const char *sep);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

#endif /* LIBFT_H */
