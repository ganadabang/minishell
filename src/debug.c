// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   debug.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hyeonsok <hyeonsok@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/02/11 16:49:04 by hyeonsok          #+#    #+#             */
// /*   Updated: 2022/02/11 16:49:05 by hyeonsok         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// void	debug_pipeline(t_array *pipeline)
// {
// 	size_t		i;
// 	size_t		j;
// 	char		**argv;
// 	size_t		maxlen;
// 	t_array		*io_files;
// 	size_t		len;
	
// 	printf("\npipeline->len: %zu\n", pipeline->len);
// 	i = 0;
// 	len = pipeline->len;
// 	while (len-- > 0)
// 	{
// 		printf("\nprocess:[%zu]\n", i);
		
// 		argv = (char **)((t_proc *)pipeline->data[i])->argv.data;
// 		maxlen = ((t_proc *)pipeline->data[i])->argv.len;
// 		j = 0;
// 		while (j < maxlen)
// 		{
// 			printf("argv[%zu]: %s\n", j, (char *)argv[j]);
// 			++j;
// 		}
// 		io_files = &((t_proc *)pipeline->data[i])->io_files;
// 		maxlen = io_files->len;
// 		j = 0;
// 		while (j < maxlen)
// 		{
// 			printf("io_type: %d\tfilename: %s\n", \
// 				((t_file *)io_files->data[j])->io_type, \
// 				((t_file *)io_files->data[j])->name);
// 			++j;
// 		}
// 		++i;
// 	}
// 	return ;
// }