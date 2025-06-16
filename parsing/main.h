#ifndef MINI_H
#define MINI_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

typedef enum s_type
{
	PIPE,
	RED_IN,
	RED_OUT,
	HEREDOC,
	APPEND,
	WORD,
} t_type;

typedef enum s_red_type
{
	INPUT,
	OUTPUT,
	RED_HEREDOC,
	RED_APPEND,
} t_red_type;

typedef struct s_redirection
{
	char			*name;
	t_red_type		type;
	struct s_redirection	*next_red;

} t_redirection;

typedef struct s_command
{
	char					**command;
	t_redirection			*red;
	struct s_command		*next_command;
} t_command;

typedef struct s_token
{
	char			*value;
	int				has_space_after;
	t_type			type;
	struct s_token	*next;
} t_token;

t_token *new_token(char *value, int is_space_befor);
void	append_token(t_token **head, t_token *new_node);
void	assign_token_types(t_token *tokens);

//utils:
//--------------//
int		ft_isspace(char c);
int		ft_strlen(const char *s);
char	*my_strcat(char *dest, const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*my_strcpy(char *dest, const char *src);
char	*ft_strdup(const char *s1);
int		ft_strcmp(char *s1, char *s2);
//--------------//


//print:
//--------------//
void	print_tokens(t_token *tokens);
void	print_commands(t_command *cmds);
//--------------//

int			is_single_quoted(const char *str);
int			is_quoted(const char *str);

char		*add_spaces_around_symbols(char *input);
int			check_syntax_errors_raw(char *input);
void		expand_tokens(t_token **tokens);
void		join_tokens_with_no_space(t_token **tokens);
t_command	*extract_all_commands(t_token *tokens);

#endif