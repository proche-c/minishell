/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 19:04:07 by proche-c          #+#    #+#             */
/*   Updated: 2023/10/05 00:34:53 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <limits.h>
# include <unistd.h> //getcwd , fstat
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h> // SEÑALES
# include <stdlib.h> // EXIT
# include <dirent.h> // OPENDIR
# include <sys/param.h> // MAXPATHLEN
# include <fcntl.h> //OPEN
# include <sys/types.h> //fstat
# include <sys/stat.h> //stat, fstat
# include "../libft/libft.h"
# include <readline/readline.h>
# include <termios.h>
# include <stdbool.h>
# define ANSI_COLOR_SHELL     "\x1b[96m"
# define ANSI_COLOR_RESET   "\x1b[0m"
# define PIPE 1 // |
# define FILE_OUT 2 // >
# define FILE_IN 3 // <
# define DFILE_OUT 4 // >>
# define DFILE_IN 5 // <<
# define BUILTIN 6 // Identifica si es tipo builtin
# define NULLVAR 7 // |
# define TILDE 8 // |
# define READ 0
# define WRITE 1
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"
# define TRUE 1
# define FALSE 0
# define DEBUG FALSE
# define TEST_MODE TRUE
# define SIMPLE 0
# define APPEND 1

int	g_returnvalue;

typedef struct s_quo
{
	int				pos;
	int				first;
	struct s_quo	*next;
}	t_quo;

typedef struct s_down
{
	char			*arg;
	struct s_down	*next;
}	t_down;

typedef struct s_data
{
	int				type;
	int				num_args;
	char			*cmd;
	int				cmd_type;
	char			**args;
	t_quo			*quo;
	t_down			*down;
	struct s_data	*next;
}	t_data;

typedef struct s_envp
{
	int				type;
	char			*key;
	char			*value;
	int				unseted;
	struct s_envp	*next;
}	t_envp;

typedef struct s_master
{
	struct s_data	*list;
	struct s_envp	*envp;
	char			*str;
	char			**elem;
	int				num_elem;
	int				num_pipes;
	int				num_cmds;
	int				num_redir;
	int				fd_redir;
	int				redir_type;
	int				executed_cmds;
	int				executed_pipes;
	int				error;
	char			**bin_paths;
	char			**env;
	int				**pipes;
	int				execute;
	int				pwdflag;
	char			*home;
	int				test_mode;
	int				priority_g_return;
}	t_master;

/*	Signals	*/
void	ft_cc(int num);
void	ft_cc_execute(int num);
void	ft_cr(int num);
void	ft_cr_execute(int num);
void	ft_signals(void);

/*	minishell	*/
void	ft_signals_execute(void);

/*	Envp	*/
char	*ft_get_key(char *str);
char	*ft_get_value(char *str);
int		ft_len_envp(char **envp);
void	ft_order_envp(char **envp);
char	**ft_create_new_envp_char(char **envp);
void	ft_create_envp(t_master *master, char **envp);
void	ft_update_envp(t_master *master);

// * PARSE

/* check_d_redir	*/
int		ft_get_redirs(t_master *master);
char	*ft_get_end(t_master *master);
char	*ft_get_start(t_master *master, char *end);
void	ft_process_redir(t_master *master, char *end, char *start, int redirs);
void	ft_check_double_redir_input(t_master *master);

/*	Check_pipes	*/
void	ft_check_start_pipe(t_master *master);
void	ft_check_double_pipe(t_master *master);
void	ft_check_double_re_pipe(t_master *master, char c);
void	ft_check_single_re_pipe(t_master *master, char c);

/*	Check_redir	*/
void	ft_check_re_pipes(t_master *master);
int		ft_check_redir_end(t_master *master);
int		ft_check_double_redir(t_master *master);

/*	Check_str	*/
void	ft_check_quote(t_master *master);
void	ft_check_end_pipe(t_master *master);
void	ft_check_pipes(t_master *master);
void	ft_check_str(t_master *master);

/*	commands	*/ // 2 funciones estatic
char	*ft_parse_cmd(char *strmaster, t_master *master, t_data *data);
t_data	*ft_get_cmds(t_master *master, t_data *new_data, int k);

/*	Data	*/
void	ft_is_builtins(t_data *new_data);
t_data	*ft_get_data(t_master *master, t_data *new_data, int j);
int		ft_is_an_env(t_data *new_data);
t_data	*ft_get_redir(t_master *master, t_data *new_data, int j);

/*	Dollar		*/
char	*ft_replace_dollar_1(t_master *master, char *str, int i);
char	*ft_replace_dollar_2(t_master *master, char *str, int i);
char	*ft_replace_dollar_3(t_master *master, char *str, int i);
char	*ft_replace_dollar_4(t_master *master, char *str, int i);

/* double_redir	*/
void	ft_init_case(t_master *master, t_data *node, t_data *pipe, t_down *d);
void	ft_give_values(t_master *master, t_data *node, t_data *p, t_data *t);
void	ft_delete_node(t_data *temp);
void	ft_create_case_double_redir_input(t_master *master, char *str);
char	*ft_get_new_str(char *str, char *buf);

/*	Entry	*/
void	ft_get_value_list(t_master *master);
void	ft_get_entry(t_master *master);

/*	Parse	*/
void	ft_value_master(t_master *master, char *str);
void	ft_parse_exec(t_master *master, char *str);
int		ft_spaces(char *str);
void	ft_check_list(t_master *master);

/*	Path	*/
t_envp	*ft_find_path(t_master *master);

/*  quotes  */
int		ft_count_quotes(char *str, int start, int end, char *q);
int		ft_count_dquotes(char *str, int start, int end, char *q);
void	ft_eval_quotes_value(char *value, int i, t_quo *initial, t_quo *auxq);
char	*ft_get_real_quotes(t_quo *quo, t_master *master, int len);
void	ft_get_val_quo(t_quo *quo, char *result);

/*	Replace_tilde		*/
char	*ft_parse_tilde(t_master *master, char *strmaster, t_data *data);
void	ft_exec_tilde(t_master *master, char *strmaster, t_data *data);
char	*ft_replace_tilde(t_master *master, char *aux, int i);
void	ft_eval_tilde(t_master *master, char *dir);

/*	Replace var	*/
int		ft_has_dollar(char *str);
char	*ft_search_var(char *str);
void	ft_replace_var(t_master *master);
int		ft_len_var(char *str, int i);
int		ft_len_var_quoted(char *str, int i);

/*	Replace		*/
char	*ft_parse_dollar(t_master *master, char *strmaster, int i, t_quo *ini);
char	*ft_get_new_master(t_master *master, char *aux, int i, t_quo *ini);
char	*ft_replace_dollar(t_master *master, char *str, int i, int caso);
char	*ft_get_esp_var(char *str, int i, t_master *master);
int		ft_esp_var(char *str, int j);

/*	Separate_cmd	*/
char	**ft_separate_cmd(t_master *master, char *strclean, t_data *data);
int		ft_get_num_cmds(char *strclean, char *realq);
char	**ft_assign_cmds(t_master *master, char **strin, int num_cmds);
char	*ft_get_parsed_cmd(char **strin, int i, int len, char *result);

/*	Separate	*/
void	ft_assign_str_2(t_master *master, char *str, char **result); // ? Static
void	ft_separate_str(t_master *master);

/*	Utils Dollar		*/
int		ft_with_dollar(char *str);
int		ft_get_caso(char *aux, int i, char *value);
int		ft_get_len_itoa(void);
int		ft_get_new_pos(t_master *master, char *str, int i);
int		ft_blank(char *str);

/*	Utils Parse	*/
int		ft_get_num_elem(char *str);
int		ft_char_resv(char *str, int i);

/*	Utils_quotes		*/
int		ft_find_quote(char *str, int j, int end);
int		ft_is_quoted(char *str, int i);
int		ft_find_quote_rev(char *str, int i);
int		ft_find_dquote_rev(char *str, int i);
int		ft_find_quotes_rev(char *str, int i);

/*	Utils Replace		*/
char	*ft_get_val(char *aux, int i, t_master *master, int len_var);
char	*ft_get_val_1(char *str, int i, t_master *master, int len_var);
char	*ft_get_val_2(char *str, int i, t_master *master, int len_var);
char	*ft_get_var(char *str, int i, t_master *master, int len_var);

/*	Utils_separate_cmd	*/
char	**ft_init_cmd(t_master *master);
int		ft_get_new_i(char **strin, int i);
int		ft_get_len_cmd(char **strin, int i, int new_i);
int		ft_stop(char *str, int k, char *q);

/*	utils_tilde		*/
int		ft_is_tilde(char *str, int i);
int		ft_with_tilde(char *str);

// * EXECUTE
void	ft_is_redir_3(t_master *master, t_data *list);
t_data	*ft_no_pipes(t_master *master, t_data *list);
int		ft_is_absolute_path(char *str);
void	ft_execute_relative_path(t_master *master, t_data *list);
void	ft_handle_single_builtin(t_master *master, t_data *list);
void	ft_handle_first_cmd(t_master *master, t_data *list, int *pid);
void	ft_handle_last_cmd(t_master *master, t_data *list, int *pid);
void	ft_handle_middle_cmd(t_master *master, t_data *list, int *pid);
void	ft_handle_return_values(int status_waitpid, t_data *list);

/*	Execute	*/
void	ft_big_execute(t_master *master);

/*	Execute Builtins	*/
void	ft_exec_builtins(t_master *master, t_data	*list, int fd);

/*	Pipes	*/
void	ft_create_pipes(t_master *master);

/*	Redirections	*/
t_data	*ft_redirections(t_master *master, t_data *list);

/*	Utils Execute	*/
void	ft_get_args_for_execve2(t_data *list_node);
void	ft_complete_char_to_execute(t_master	*master);
void	ft_num_cmds(t_master *master);
void	ft_get_paths_vesionvictor(t_master *master, t_data *list);
void	ft_prev_execute_builtins(t_master *master, t_data *list);
void	ft_prev_execute_cmds(t_master *master, t_data *list);
void	ft_execute_cmd_real(t_master *master, t_data *list);
int		ft_is_directory(char *path);

/* CMD */
void	ft_cmd_redir_output(t_master *master, t_data *list);
void	ft_cmd_redir_input(t_master *master, t_data *list);

/*	CMD 1	*/
void	ft_cmd_1(t_master *master, t_data *list);

/*	CMD 2	*/
void	ft_cmd_2(t_master *master, t_data *list);

/*	CMD 3	*/
void	ft_cmd_3(t_master *master, t_data *list);

/* Redirection input simple */
t_data	*ft_redir_input_simple(t_master *master, t_data *list);

// * BUILTINS

/*	cd	*/
void	ft_is_cd(t_master *master, t_data *list);
void	ft_cd(t_master *master, char *dir);
void	ft_cd_error_is_null(char *dir);
void	ft_cd_export(t_master *master, char *oldpwd);

/*	Echo	*/
void	ft_echo(t_data *data, int fd);

/*	Env	*/
void	ft_is_env(t_master *master, t_data *list, int fd);
void	ft_env(t_envp *envp, int fd);

/*	Export	*/
void	ft_is_export(t_master *master, t_data *list, int fd);
int		ft_has_equal(char *str);
void	ft_export(t_envp *envp, int fd);
void	ft_export_with_var(t_master *master, char *arg);

/*	Envp Utils	*/
char	*ft_get_key(char *str);
char	*ft_get_value(char *str);
int		ft_len_envp(char **envp);
void	ft_order_envp(char **envp);
int		ft_search_equal(char *str);
char	*ft_get_value_envp(t_master *master, char	*key);

/*	Export Utils	*/
void	ft_temp_type(t_envp *temp, char *aux, int fd);
int		ft_check_first_value(char *key, char *arg);
char	*ft_get_value_export(t_master *master, char *key);

/*	Pwd	*/
void	ft_pwd(t_master *master);
void	ft_pwd_0(void);
void	ft_pwd_1(t_master *master);
//void	ft_pwd_2(void);
char	*ft_my_path(void);

/*	Unset	*/
void	ft_is_unset(t_master *master, t_data *list);
char	*ft_search(char *str);
void	ft_unset(t_master *master, t_envp *envp, char *arg);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/*	Utils envp	*/
int		ft_is_in_envp(t_envp *envp, char *str);
char	*ft_get_value_without_quotes(char *str);

/*	Exit	*/
void	ft_exit(t_master *master, t_data *list);
void	ft_real_exit(t_master *master, int num, int print);

// * CLEAN

/* Clean lists */
void	ft_clean_down_node(t_down *down);
void	ft_clean_data_node(t_data *data);
void	ft_clean_data_node_2(t_data *data);
void	ft_clean_list(t_master *master);
void	ft_delete_next_node_data(t_data	*list);

/*	clean_env	*/
void	ft_clean_envp_node(t_envp *envp);
void	ft_clean_env(t_master *master);
void	ft_clean_envp(t_master *master);

/* clean */
void	ft_clean_pipes(t_master *master);
void	ft_clean_elem_char(t_master *master);
void	ft_clean_master_middle(t_master *master);
void	ft_clean_master_all(t_master *master);
void	ft_clean_env_char(t_master *master);

/* Clean_parse */
void	ft_free_strin(char **strin);
void	ft_free_quo(t_data *data);

// * UTILS

/* Compare str */
int		ft_compare_upper_lower(char *str, char *to_compare);

/*	Errors	*/
void	ft_syntax_error(t_master *master);
void	ft_syntax_error_2(t_master *master, int check);
void	ft_syntax_error_3(t_master *master, int check);
void	ft_tilde_error(t_master *master, char *mse);
void	ft_tilde_error_2(t_master *master, char *mse);

// * LISTS

/* args */
void	ft_add_arg(t_down *next_down, t_data *next, t_data *start);
void	ft_recount_args(t_data *temp, t_data *next, t_data *start);
void	ft_add_down(t_master *master, t_data *temp, t_down *down, int pipes);
int		ft_how_many_args(t_master *master, t_data *list);
void	ft_fix_args(t_master *master, t_data *list);

/* casew */
void	ft_exec_files_1(t_master *master, char *file1, char *file2);
void	ft_exec_files_2(t_master *master, char *aux);
void	ft_exec_files_3(t_master *master, char *aux);
void	ft_exec_files_4(t_master *master, char *aux);
void	ft_exec_files_5(t_master *master, int casew);

/* envp */
t_envp	*ft_new_envp(char *key, char *value);
t_envp	*ft_lst_last(t_envp *list);
int		ft_envpsize(t_envp *lst);

/* files */
void	ft_create_file(char *filename);
void	ft_pre_create_file(t_master *master, t_data *temp);
void	ft_create_and_put(t_master *master, char *file_name, char *str);
void	ft_create_and_put_append(t_master *master, char *file_name, char *str);
void	ft_execute_casew(t_master *master, int casew);

/* parse */
t_data	*ft_new_cmd(t_master *master);
t_quo	*ft_new_quo(void);
t_down	*ft_down_new(t_master *master, char *str);

/* redir */
int		ft_words_after_redir(t_data *list);
int		ft_redirections_until_next_pipe(t_master *master, t_data *list);
void	ft_delete_redir(t_master *master, t_data *list);

/* lists */
int		ft_compare_redouble(char *str1, char *str2, int x);
bool	are_equal(const char *str, unsigned long long now_it);
void	ft_assign_all(t_master *master, char *str_c, int type);
void	ft_check_args_re(t_master *master);

/* Returns */
void	ft_return_error(char *str1, char *str2);
void	ft_return_error_3(char *str1, char *str2, char *str3);

/*	ft_strjoin_3	*/
char	*ft_strjoin_3(char *s1, char *s2, char *s3, t_master *master);

/*	Home	*/
int		ft_num_x(char *str, char x);

/*	Test mode	*/
void	ft_test_mode(t_master *master, int argc, char **argv);

// * LIBFT
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_isspace(char c);

int		ft_has_char(char *str, char x);
void	ft_cd_error(char *dir);
int		ft_new_num_exit(int num);
int		ft_isalldigit(char *str);
int		ft_check_errors_exit(t_master *master, t_data *list);
void	ft_put_str_2(char *str1, char *str2, int nl, int fd);
void	ft_put_str_3(char *str1, char *str2, int nl, int fd);
void	ft_export_with_var_aux(t_master *master, char *key, char *arg);
void	ft_export_with_var_normal_case(t_master *master, char *key, char *arg);
void	ft_replace_var_envp(t_envp *envp, char *key, char *value);
void	ft_add_var_envp(t_envp *envp, char *str, char *key, char *value);
void	ft_replace_var_envp(t_envp *envp, char *key, char *value);
void	ft_pre_while(t_master *master, t_data *list);
t_data	*ft_check_pre_execute(t_master *master, t_data *list);
int		ft_export_aux(t_master *master, char *temp, char *key, char *arg);
void	ft_type_envp(t_envp	*new_envp, char	*envp, char *value);
void	ft_clean_args(t_data *list_node);

#endif
