/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlecuyer <mlecuyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 14:27:03 by user42            #+#    #+#             */
/*   Updated: 2021/10/19 16:42:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>

int	g_exit_code;

typedef struct s_node
{
	char			*file;
	char			*value;
	char			*label;
	int				flag;
	int				uni;
	struct s_node	*next;
}				t_node;

typedef struct s_charnode
{
	char				direction;
	struct s_charnode	*next;
}						t_charnode;

typedef struct s_quotes
{
	int		quotes[2];
	int		in_quotes;
	int		count;
	int		hang;
	int		start;
	int		punc;
	int		pipe_flag;
	char	c;
	int		i;
	int		flag;
	int		np_uni;
	int		np_stock;
}		t_quotes;

typedef struct s_list
{
	t_node	*head;
}		t_list;

typedef struct s_charlist
{
	t_charnode	*head;
}		t_charlist;

typedef struct s_dir_tools
{
	t_node		*in;
	t_node		*out;
	t_charnode	*temp;
	t_node		*prev;
	int			uni;
}				t_dir_tools;

typedef struct s_exetrio
{
	const char	*path;
	char		*str;
	char *const	*command;
	char		**tab_env;
	int			hang;
	int			orig_stdin;
	int			orig_stdout;
	int			no_cmds;
	int			skip;
	int			last_skip;
	int			last_exec_flag;
	int			dir_stuff_skip;
	int			dir_stuff_check;
	int			j;
	int			ret;
	int			any_bug;
	int			len_tab;
	int			label_added;
	int			assign_var;
	int			last_pid;
	int			prev_cmd;
	int			exec_flag;
	int			**pipefd;
	int			len_exit;
	char		**cmd;
	char		**cmd_str;
	t_list		*input;
	t_list		*output;
	t_charlist	*direction;
	t_list		*e;
}				t_exetrio;

typedef struct s_var
{
	int		i;
	int		j;
	char	*var;
	char	*value;
	int		len_var;
	int		len_value;
	int		len_tot;
	int		s;
	int		quotes;
	int		afword;
	char	*new;
}				t_var;

typedef struct s_counter
{
	int	i;
	int	count;
	int	tp;
}				t_counter;

typedef struct s_qbis
{
	int		dub;
	int		sing;
	int		i;
	int		j;
}				t_qbis;

/**
 * GNL
 **/
int			get_next_line(int fd, char **line, int BUFFER_SIZE);
int			get_next_line_mod(int fd, char **line, int BUFFER_SIZE);
char		*ft_get_strjoin(char const *s1, char const *s2, int store);
char		*ft_substr_gnl(char const *s, unsigned int start, int len);

/**
 * LIST UTILS
 **/
t_node		*ft_lstnew(char *file, int flag, int uni);
t_charnode	*ft_lstnew_char(char c);
void		ft_lstadd_front(t_node *start, t_node *news);
int			ft_copy_to_list(char *pipeline, t_list *list, int here, int uni);
void		ft_lstprinter_laura(t_list *lst);
int			ft_freelist(t_node *head);
void		ft_del_node(t_node *node);
int			ft_freelist_char(t_charnode *head);
void		ft_lstadd_back(t_list *start, t_node *newie);
void		ft_lstadd_back_char(t_charlist *start, t_charnode *newie);
void		ft_lstprinter(t_list *list);
int			ft_freelist_envp(t_node *head);
int			ft_strlcpy(char *dest, const char *src, int size);
void		ft_sortlst_alpha(t_list *lst);
t_list		*ft_duplicate_list(t_list *to_sort, t_list *begin_list);
t_node		*ft_lstnew_forcpy(char *label, char *value);

/**
 * FREES
 **/
void		free_double(char **str);
void		ft_ctrld_free(t_exetrio *exe);
void		ft_free_exe(t_exetrio *exe, int **pipes);
void		ft_frees_in_main(t_exetrio exe, char *possible_free);
int			ft_free_pipes(int **pipes);
void		ft_free_exit_exe(int g_exit_code, int **pipes, t_exetrio exe);
int			ft_free_onetrio(t_exetrio *one);
void		free_tab(char **tab);
int			ft_big_free(int ret, t_exetrio exe);
void		free_loop(t_exetrio *exe);
void		ft_exit_free(t_exetrio *exe);
char		*ft_free_pipeline(char *pipe);

/**
 * INITIALISATION
 **/
int			ft_init_first(t_node *input, t_exetrio *exe);
int			ft_init_last(t_node *output, int uni);
int			init_exetrio(char **command, t_exetrio *exec);
void		ft_initialise_exe(t_exetrio *exe);
void		init_exe_envp(t_exetrio *exe);
void		ft_init_svar(t_var *v, char *str);
void		ft_init_exe_p1(t_exetrio *exe);

/**
 * PARSING
 **/
int			ft_v_counter(t_exetrio *exe, t_var *v, char *s, t_qbis *q);
int			ft_dq_not_only(char *str);
int			ft_punctuation(char *str, t_exetrio *exe);
int			ft_punc_pipe(char *str, t_quotes *box);
void		ft_punc_space(t_quotes *box);
void		ft_punc_chevrons(char *str, t_quotes *box);
int			ft_punc_equal_two(char *str, t_quotes *box);
int			ft_chevrons_before(char *str, t_quotes *box);
void		ft_fill_direction_list(t_exetrio *exe, char *str);
int			ft_is_hang(char *str);
int			ft_unclosed(char *str);
char		**ft_split_quotes(const char *s, char c);
t_quotes	*ft_init_quotes(void);
char		**ft_dequote(char **split);
char		**ft_dequote_orig(char **split);
char		**ft_dequote_export(char **split);
void		ft_dequote_list(t_node *head);
char		**ft_get_env_tab(t_exetrio *exe);
int			ft_check_nb_dollars(char *str);
char		*ft_get_tab_variables(t_exetrio *exe, char *str);
int			ft_in_quotes(char c, int quotes[2]);
int			ft_get_size(char *pipeline);
int			ft_atoi_mod(const char *str, int *ret);
void		ft_free_var(t_var *v);
char		*ft_check_value_for_label(t_exetrio *exe, char *str);
void		ft_get_values(t_exetrio *exe, t_var *v, char *str);
int			ft_str_empty(char *str);
int			dol_multiple(char *str);
int			ft_got_slash(char *str);
char		*parsing_quotes(char *str, int pos);
int			ft_dollar_test(char *str);
int			ft_chevron_test(int i, char *str);
int			ft_excode_two(t_quotes *box);
char		*ft_new_str_quotes(char *old);
int			ft_in_sing_quotes(char *str, int x, t_qbis *q);

/**
 * FT_MINISHELL
 **/
void		ft_diamond(t_dir_tools *tools);
int			ft_get_no_cmds(char **pipe_strings);
int			ft_space_cutter(char *str);
int			ft_is_builtin(char **cmd_line);
int			ft_exit(char **str_status, t_exetrio *exe);
int			ft_cd(char *path, t_exetrio *exe);
int			ft_redirect_in(t_node *input, int **pipefd, t_exetrio *exe);
int			ft_cmd(t_exetrio *exe);
void		ft_connect_pipes(int count, t_exetrio *exe);
int			ft_skipper(int *i, char *pipeline, char *one, char *two);
int			ft_parse_skipper(char *pipeline, int *x);
char		*ft_hang_pipe(char *str, t_exetrio *exe);
int			ft_is_this(char *targets, char c);
int			ft_get_size_out(char *pipeline);
char		*ft_getpath(char **all_paths, char *command);
int			ft_execute_cl(char *argv, t_exetrio *exe);
int			ft_cmd_control_room(char **cmd_line, int index, t_exetrio *exe);
void		failed_dup(int **pipes, t_exetrio *exe);
char		*ft_input_sorter(char *pipeline, t_exetrio exe);
int			ft_herecmp(char *str);
void		ft_cmd_error(char **cmd);
void		close_both(int pipefd[2]);
void		ft_parenting(int counter, int **pipefd, int no_cmds);
void		ft_make_pipefds(int no_cmds, t_exetrio *pipefd);
int			here_doc(char *del, char *file, int **pipefd);
int			ft_error(char *error, int ret);
char		*ft_pathfinder(char *command, char **tab_env);
int			ft_error(char *error, int ret);
char		*ft_get_strjoin(char const *s1, char const *s2, int store);
int			ft_ending(t_exetrio *exe);
int			ft_piperr(t_exetrio *exe, char *error, int ret);
void		ft_echo_get_return(t_exetrio *exe);
void		ft_inchild(int i, t_exetrio *exe);
void		ft_not_inchild(int i, t_exetrio *exe);
int			dol_alone(char *str);
void		ft_get_strsize_for_malloc_cd(t_exetrio *exe, t_var *v, char *str);
void		ft_lstprinter_char(t_charlist *lst);
char		*ft_dollars(t_exetrio exe, char *pipeline, char *new_pipeline);
char		*ft_free_new(char *str, t_var *v);
int			ft_malloc_vnew(t_var *v);
int			ft_directing_stuff(t_exetrio *exe, int i);
char		*ft_replace_w_exitcode(int j, char *new);
int			ft_get_size_dol(t_exetrio *exe, char *str);
int			ft_is_builtin_mod(char **cmd_line);
char		*ft_dollar_check_split(char *str, int *i, int new_i);

/**
 * SIGNALS
 * */

void		sigint_handler(int sig_no);

/**
 * EXPORT
 **/
int			ft_strcmp_diff(const char *s1, const char *s2);
int			check_label_exist(t_exetrio *exe, char *str);
int			ft_parse_errors(char *str);
int			ft_export(t_exetrio *exe, char **str);
t_node		*ft_newnode_envp(char *file, int i);
void		ft_lstprinter_export(t_list *lst);
int			check_label_added(t_exetrio *exe, char *str);
int			ft_check_quotes(char *str);
void		ft_sortlst_alpha(t_list *lst);
char		*handle_quotes(char *str);
void		ft_free_envp_exe(t_exetrio *exe);
void		ft_swap(char **d1, char **d2);
void		ft_error_export(char *str);
int			ft_parse_errors_bis(char *str, int error);
int			ft_init_export(char **str, t_exetrio *exe);

/**
 * ENV
 **/
int			ft_env(t_exetrio *exe, char **str);
void		ft_free_envp(t_exetrio *exe);
void		ft_lstprinter_env(t_list *lst);

/**
 ** UNSET
 */
int			ft_unset(t_exetrio *exe, char **str);
void		ft_error_unset(char *str);

#endif
