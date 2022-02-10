// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   mush_getvar.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hyeonsok <hyeonsok@student.42seoul.kr>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/02/08 23:39:14 by hyeonsok          #+#    #+#             */
// /*   Updated: 2022/02/09 16:58:03 by hyeonsok         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "mush/parser.h"

// cd
// {
// 	위치 변경한 후 
// 	현재위치, 올드위치 변경
// }

// export
// {
// 	환경변수 설정하고나서
// 	리스트에 추가함
// 	setenv
// }

// env
// {
// 	현재 리스트 보이기
// }

// declare
// {
// 	정렬된 리스트
// }

// {
// 	unset할때는 var에서도 지우고
// 	env리스트에서도 지우고
// }
// //이부분만 정리되면 무난할 것 같은뎅...
// static char	*mush_getvar_env(t_state *state, const char *key)
// {

// }

// static char	*mush_getvar_shell(t_state *state, const char *key)
// {
// 	if (*key == '?' && strcmp(key, "?"))
// 		return (state->last_status);
// 	if (*key == 'P' && strcmp(key, "PWD"))
// 		return (state->pwd);
// 	if (*key == 'O' && strcmp(key, "OLDPWD"))
// 		return (state->old_pwd);
// 	return (NULL);
// }


// char	*mush_get_env(t_state *state, const char *key)
// {
// 	char	*value;

// 	value = mush_getvar_env(state, key);
// 	if (!value)
// 		value = mush_getvar(state, key);
// 	return (value);
// }