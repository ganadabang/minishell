/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 01:58:30 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/07 12:01:15 by hyeonsok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mush.h"

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
	char	*ref_pos;
	char	*brk;
	size_t	len;

	ref_pos = &parser_ref->input[parser_ref->pos];
	// TODO strchr -> ft_strchr
	brk = strchr(&ref_pos[1], quoting);
	if (!brk)
	{
		parser_ref->syntax_error = 1;
		return (-1);
	}
	len = brk - ref_pos + 1;
	hx_buffer_putstr(&parser_ref->buffer, ref_pos, len);
	parser_ref->pos += len;
	return (0);
}

char	*parser_buffer_withdraw_operator(t_parser *parser_ref)
{
	char	*ref_pos;
	size_t	len;
	int		ret;

	ref_pos = &parser_ref->input[parser_ref->pos];
	len = get_operator_size(ref_pos);
	hx_buffer_putstr(&parser_ref->buffer, ref_pos, len);
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
