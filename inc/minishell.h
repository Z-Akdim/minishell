/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zakdim <zakdim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 09:59:21 by zakdim            #+#    #+#             */
/*   Updated: 2021/08/30 09:59:23 by zakdim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <limits.h>
# define BUFFER_SIZE 32
# define STDERR 2

# define TYPE_CD "cd"
# define TYPE_PWD "pwd"
# define TYPE_ECHO "echo"
# define TYPE_ENV "env"
# define TYPE_EXPORT "export"
# define TYPE_UNSET "unset"
# define TYPE_EXITE "exit"
# define RED "\e[1;31m"
# define GRN "\e[1;32m"
# define WHT "\e[0;37m"

typedef struct	s_global
{
	pid_t		pid;
	int			exit_status;
	int			is_ctrl_c;
}				t_global;

typedef struct	s_v
{
	int			index;
	int			i;
	int			k;
	int			j;
	int			c;
	int			n;
	int			deja;
	char		*tmp;
	char		*type;
	char		*arg;
	char		**new_args;
	char		**s1;
	int			i_d_q;
	int			i_s_q;
	int			block_copy;
	char		*correct_args;
	char		*new_line;
	int			*pipefds;
}				t_v;

typedef struct	s_style
{
	char		pwd[1024];
}				t_style;

typedef struct	s_export
{
	char		**tab;
}				t_export;

typedef struct	s_unset
{
	char		**tab;
	int			index;
}				t_unset;

typedef struct	s_dollar
{
	char		*value;
	int			i;
	int			j;
	char		*prefix;
	char		*suffix;
	int			suffixx;
	int			prefixx;
	int			s_quotes;
	char		*new_line;
	char		*tmp;
	int			index;
	int			ret;
}				t_dollar;

typedef struct	s_pipe
{
	char		**args;
	int			fd[2];
	int			fd2;
	int			fdd;
	int			status;
	int			num;
}				t_pipe;

typedef struct	s_echo
{
	char		**args;
}				t_echo;

typedef struct	s_mini
{
	char		*home;
	char		*line;
	char		*command;
	int			dollar_num;
	char		**add_path1;
	char		**sorted_args2;
	char		**args;
	char		**sort_args;
	char		**args_to_sort;
	int			exit_status;
	int			exit;
	int			dollarr;
	int			redirection_fd;
	int			shell_lvl;
	int			first_lvl;
	char		*home_error;
	int			no_style;
	int			redirection_nocommand;
	char		**m_cmd;
	char		*path;
	char		**envp_backup;
	char		**new_envp;
	int			pipe_fd[2];
	char		*home_two;
	char		*oldpwd;
	char		*input_file;
	int			redirection;
	char		*run_path;
	char		**add_path;
	int			std;
	int			check_pipe;
	int			args_num;
	char		**envp_g;
	int			redirection_error;
	char		**redirection_args;
	char		cwd[PATH_MAX];
	int			free_run_path;
	int			free_path;
	t_export	export;
	t_unset		unset;
	t_dollar	d;
	t_pipe		pipe;
	t_style		style;
	t_echo		echo;
	t_v			v;
	t_v			var;
}				t_mini;
t_global	g_v;
int				get_next_line(const int fd, char **line);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s1);
size_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_putchar(char c);
void			ft_putstr(char *str);
int				char_test(char *command, char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_get_args_num(t_mini *m);
int				ft_get_args(t_mini *m);
void			ft_init(t_mini *m);
int				ft_ischar(char c);
void			ft_exit(t_mini *m);
char			**ft_split(char *s, char c);
void			ft_cd(t_mini *m);
void			ft_echo(t_mini *m);
void			ft_get_path(t_mini *m);
void			ft_get_home(t_mini *m);
void			ft_re_init(t_mini *m);
void			ft_run_command(t_mini *m);
void			ft_strjoin2(t_mini *m, char *s2);
void			ft_export(t_mini *m, int i, int j);
void			ft_sort_table(t_mini *m);
void			ft_copy_env(t_mini *m, char **envp);
char			*ft_strcpy(char *dst, char *src);
void			ft_check_args(t_mini *m);
void			ft_unset(t_mini *m);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			ft_remove_unset(t_mini *m, int index);
int				ft_equal_check(char *arg);
void			ft_dollar(t_mini *m);
void			ft_pwd(t_mini *m);
void			ft_check_multi_command(t_mini *m);
void			ft_old_pwd(t_mini *m);
char			*ft_strlcpy(char *dst, char *src, int size);
void			ft_check_pipe_command(t_mini *m, int i);
int				ft_check_redirection(t_mini *m);
void			ft_error(char *error_msg, char *command, char *line);
void			ft_dup2(t_mini *m);
void			ft_command_2(t_mini *m, char *tmp, int index);
void			ft_env(t_mini *m);
void			ft_pipe_run(t_mini *m, int i);
int				ft_check_pipe(t_mini *m, char **envp, int i);
void			ft_init_pipe(t_mini *m);
int				ft_signal(void);
void			ft_ctrl_c(int signum);
void			ft_start_minishell(t_mini *m, int i, int j);
void			ft_dup2(t_mini *m);
void			ft_shell_lvl(t_mini *m, int j, int index);
char			**ft_split_1(char *s, char c, char c1);
int				skip_quots(char *str, char c, int i);
void			ft_sorte_args(t_mini *m);
void			ft_free_all(t_mini *m);
void			ft_skipe_quotes(t_mini *m);
void			ft_ctrl_anti(int signum);
int				syn_error(t_mini *m, int i);
char			*ft_strjoin3(char const *s1, char const s2);
char			*ft_env_shellvl(t_mini *m);
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
void			ft_redirection_nocommand(t_mini *m);
void			ft_check_home(t_mini *m);
void			ft_get_home_2(t_mini *m);
int				ft_quotes(t_mini *m);
void			ft_pwd_refresh(t_mini *m);
void			ft_pwd_refresh_2(t_mini *m);
void			ft_sort_args2(t_mini *m);
void			ft_ctrl_c(int signum);
void			ft_get_pipe_args(t_mini *m, int k);
void			ft_pipe_run2(t_mini *m, int k, int j);
void			ft_copy_env(t_mini *m, char **envp);
char			*ft_env_shellvl(t_mini *m);
void			ft_free_env(t_mini *m);
void			ft_redirection_space(t_mini *m);
int				is_redirection(char *line);
void			ft_init_all_allocation(t_mini *m, int k);
void			ft_sort_args2(t_mini *m);
int				redirection_sorted_args(t_mini *m);
void			ft_get_sort_args(t_mini *m, int i, int j);
void			ft_sorte_args(t_mini *m);
void			ft_copy_export(t_mini *m);
void			ft_pipe(t_mini *m, int i);
void			ft_init_pipe(t_mini *m);
void			ft_redirection_space(t_mini *m);
void			ft_sort_args2(t_mini *m);
void			ft_free_pipe_args(t_mini *m);
void			ft_free_args(t_mini *m);
void			ft_free_echo_args(t_mini *m);
void			ft_free_sort_args(t_mini *m);
void			ft_free_path(t_mini *m);
void			ft_free_sort_args2(t_mini *m);
void			ft_free_args_to_sort(t_mini *m);
void			ft_free_export(t_mini *m);
void			ft_strjoin_export(t_mini *m, char *s2);
void			ft_copy_export_with_quotes(t_mini *m);
void			ft_dollar_test(t_mini *m, int i);
void			ft_run_export(t_mini *m, int i);
void			ft_free_multi_command(t_mini *m);
void			ft_free_args_redirection(t_mini *m, int index);
int				ft_count_pipes(t_mini *m);
void			ft_exit_1(t_mini *m);
void			ft_ctrl_d(void);
int				ft_sp_char(char c);
int				ft_space_nb(t_mini *m, int i, int space_nb);
int				skip_quots(char *str, char c, int i);
void			ft_print_num(void);
void			ft_get_line_value(t_mini *m);
void			ft_get_dollar_value_1(t_mini *m);
void			ft_get_dollar_value(t_mini *m, char *str);
void			ft_dollar_init(t_mini *m);
int				ft_is_alphanum(char c);
void			ft_run_dollar(t_mini *m);
void			ft_do_if(t_mini *m, int i);
void			ft_do_if_2(t_mini *m, int i);
int				num_len(int n);
void			ft_free(char **tab, char *str);
int				ft_nb_antislash(char *arg);
int				ft_count_pipes(t_mini *m);
void			get_input(t_mini *m, int i, int b, int len);
void			ft_putstr_fd(char *s, int fd);
char			*ft_get_num(void);
void			ft_bzero(void *s, size_t n);
char			*clean_join(char *s1, char *s2);
char			*ft_chr(const char *s, int c);
void			*ft_free2(void *ptr);
char			*ft_strtrim(char *s1, char set);
void			ft_do_if_3(t_mini *m);
void			ft_start_minishell_2(t_mini *m);
void			ft_free_no_pipe(t_mini *m);

#endif
