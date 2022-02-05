/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 01:58:30 by hyeonsok          #+#    #+#             */
/*   Updated: 2022/02/05 12:35:03 by hyeonsok         ###   ########.fr       */
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

int	parser_buffer_write_quoted(t_parser *ref_parser, char quoting)
{
	char	*ref_pos;
	char	*brk;
	size_t	len;

	ref_pos = &ref_parser->input[ref_parser->pos];
	// TODO strchr -> ft_strchr
	brk = strchr(&ref_pos[1], quoting);
	if (!brk)
	{
		ref_parser->syntax_error = 1;
		return (-1);
	}
	len = brk - ref_pos + 1;
	hx_buffer_putstr(&ref_parser->buffer, ref_pos, len);
	ref_parser->pos += len;
	return (0);
}

char	*parser_buffer_withdraw_operator(t_parser *ref_parser)
{
	char	*ref_pos;
	size_t	len;
	int		ret;

	ref_pos = &ref_parser->input[ref_parser->pos];
	len = get_operator_size(ref_pos);
	hx_buffer_putstr(&ref_parser->buffer, ref_pos, len);
	ref_parser->pos += len;
	return (hx_buffer_withdraw(&ref_parser->buffer));
}

void	parser_buffer_write_char(t_parser *ref_parser, char ch)
{
	hx_buffer_putchar(&ref_parser->buffer, ch);
	ref_parser->pos += 1;
	return ;
}

char	*parser_buffer_withdraw_word(t_parser *ref_parser)
{
	return (hx_buffer_withdraw(&ref_parser->buffer));
}
