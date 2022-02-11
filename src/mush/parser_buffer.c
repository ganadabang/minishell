/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 01:58:30 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/11 16:02:05 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libfthx.h"
#include "mush/parser.h"

static size_t	get_operator_size(char *input)
{
	if (ft_strchr("<|>", *input) == NULL)
		return (0);
	if (input[0] == input[1] && (input[0] == '<' || input[0] == '>'))
		return (2);
	return (1);
}

int	parser_buffer_write_quoted(t_parser *parser_ref, char quoting)
{
	char	*pos_ref;
	char	*brk;
	size_t	len;

	pos_ref = &parser_ref->input[parser_ref->pos];
	// TODO strchr -> ft_strchr
	brk = ft_strchr(&pos_ref[1], quoting);
	if (!brk)
	{
		parser_ref->syntax_error = 1;
		return (-1);
	}
	len = brk - pos_ref + 1;
	hx_buffer_putstr(&parser_ref->buffer, pos_ref, len);
	parser_ref->pos += len;
	return (0);
}

char	*parser_buffer_withdraw_operator(t_parser *parser_ref)
{
	char	*pos_ref;
	size_t	len;
	int		ret;

	pos_ref = &parser_ref->input[parser_ref->pos];
	len = get_operator_size(pos_ref);
	hx_buffer_putstr(&parser_ref->buffer, pos_ref, len);
	parser_ref->pos += len;
	return (hx_buffer_withdraw(&parser_ref->buffer));
}

void	parser_buffer_write_char(t_parser *parser_ref, char ch)
{
	hx_buffer_putchar(&parser_ref->buffer, ch);
	parser_ref->pos += 1;
	return ;
}

char	*parser_buffer_withdraw_word(t_parser *parser_ref)
{
	return (hx_buffer_withdraw(&parser_ref->buffer));
}
