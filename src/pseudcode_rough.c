main
	mush_state_create()
	loop
	{
		mush_setup_interactive()
		input = readline()
		mush_setup_meanwhile_exec()
		mush_parser_create()
		mush_state_with_parser()
		mush_job_create();
		job->pipeline = mush_parse_line() {
			loop
			{
				pretokens = parser_tokenize //give token_type; word or redirection or pipe
				tokens = mush_parser_tokenize() { // give word_type or redirection_type
					let buffer
					let token_array
					while input != '\0'
					{
						pretoken = get_next_pretoken
						if (token_type == redirection)
						{
							type = get_io_redirection_type();
							if (type == io_here)
							{
								io_here_end = get_next_word();
								parser_read_heredoc();
								token_array_push("./.here_tmp")
								continue;
							}
							token_array_push(get_next_word(), redirection_type);
						}
						if (pretoken with no quoting)
							word = pretoken_to_word_string(no_single_quoted)
						else (pretoken with quoting)
						{
							words = pretoken_to_words()// splited "" '' ex hell"o   world"'!' => hell, "o   world", '!'
							foreach words
							{
								str = quoting_to_word_string(pretoken, is_single_quoted?)
								buffer_putstr(str)
								free(str)
							}
							token = buffer_withdraw()
							token_array_push(token);
						}
					}
				}
				parser_create_pipeline(parser)
				{
					...
				}
				parser_synstax_error()
				{
					...
				}
		mush_state_destroy_parser()
		mush_state_with_job()
		mush_execute_job()
		{
			if mush_builtin_search
				return mush_execute_builtin()
			return mush_execute_pipeline() {
			loop
			{
				process_open_pipe()
				fork()
				if errno != 0 then error
				if pid == 0
					process_command_expansion()
					process_io_redirect()
					if mush_builtin_search() return exit(process_execute_builtin())
						process_execute_simple_command()//child exits
				if (pid > 0)
					process_close_pipe()
			}
			close(last_pipe in fd)
			pl_update_status()
			return (last_status);
		}
		}
		mush_newline_when_signaled
	}
	mush_state_destroy()
	mush_setup_default()
	mush_print_exit()
	return ;
}
