CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC = parsing/main.c parsing/tokenization.c parsing/grabage.c parsing/error.c\
	parsing/expand.c parsing/ft_rename.c parsing/ft_herdoc.c\
	libft/ft_putstr_fd.c libft/ft_strlen.c libft/ft_cmp.c libft/ft_strjoin.c\
	libft/linked_list.c libft/ft_substr.c libft/ft_strdup.c libft/ft_isprint.c\
	libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_strncmp.c\
	libft/ft_strndup.c libft/ft_allocate.c libft/ft_strcat.c libft/ft_strncpy.c\
	libft/ft_memset.c libft/ft_strcmp.c\

OBJ = $(SRC:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lreadline

parsing/%.o: parsing/%.c include/minishell.h
	$(CC) $(FLAGS) -c $< -o $@

libft/%.o: libft/%.c include/minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

######################################################################

# CC = cc
# FLAGS = -Wall -Wextra -Werror
# RM = rm -f

# SRC = parsing/main.c parsing/tokenization.c parsing/grabage.c \
# 	libft/ft_putstr_fd.c libft/ft_strlen.c \
# 	libft/linked_list.c libft/ft_substr.c libft/ft_strdup.c\

# OBJ = $(SRC:.c=.o)

# NAME = minishell

# all: $(NAME)

# $(NAME): $(OBJ)
# 	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -lreadline

# parsing/%.o: parsing/%.c include/minishell.h
# 	$(CC) $(FLAGS) -c $< -o $@

# libft/%.o: libft/%.c include/minishell.h
# 	$(CC) $(FLAGS) -c $< -o $@

# clean:
# 	$(RM) $(OBJ)

# fclean: clean
# 	$(RM) $(NAME)

# re: fclean all

######################################################################





# #include "../include/minishell.h"

# // int	sp(char c)
# // {
# // 	return (c == ' ' || c == '>' || c == '<' || c == '|');
# // }

# int	sp(char c)
# {
# 	return ((c != '\'' && c != '\"') &&
# 			!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z'));
# }

# void handle_quotes(char *line, int *i, t_token **head)
# {
# 	char	quote;
# 	int		j;
# 	char	*word;

# 	word = NULL;
# 	quote = line[*i];
# 	(*i)++;
# 	j = *i;
# 	while (line[*i] && line[*i] != quote)
# 		(*i)++;
# 	if (line[*i] == quote)
# 	{
# 		word = ft_substr(line, j, *i - j);
# 		ft_lstadd_back(head, ft_lstnew(word, WORD));
# 	}
# 	(*i)++;
# }

# void handle_words(char *line, int *i, t_token **head)
# {
# 	char	*word;
# 	int		j;

# 	word = NULL;
# 	j = *i;
# 	while (line[*i] && !sp(line[*i]) && line[*i] != '\'' && line[*i] != '\"')
# 		(*i)++;
# 	word = ft_substr(line, j, *i - j);
# 	ft_lstadd_back(head, ft_lstnew(word, WORD));
# }

# void handle_special_chars(char *line, int *i, t_token **head)
# {
# 	char	*word;
# 	int		j;

# 	word = NULL;
# 	j = *i;
# 	while (line[*i] && line[*i] == line[j])
# 		(*i)++;
# 	word = ft_substr(line, j, *i - j);
# 	ft_lstadd_back(head, ft_lstnew(word, SHAPE));
# }

# t_token *tokenization(char *line, int i)
# {
# 	int		j;
# 	t_token	*head;

# 	head = NULL;
# 	head = ft_lstnew(ft_strdup("."), START);
# 	j = 0;
# 	while (line[i])
# 	{
# 		if (line[i] == '\'' || line[i] == '\"')
# 			handle_quotes(line, &i, &head);
# 		else if (sp(line[i]))
# 		{
# 			if ((line[i] != '\'' && line[i] != '\"') &&
# 			!(line[i] >= 'a' && line[i] <= 'z') && !(line[i] >= 'A' && line[i] <= 'Z'))
# 				handle_special_chars(line, &i, &head);
# 			else
# 				i++;
# 		}
# 		else
# 			handle_words(line, &i, &head);
# 	}
# 	// head = ft_lstdel(head);	
# 	return (head);
# }




# /*

# * khaasni nhadli ila 3tytk no9ta t3taaabr shape

# * khasni nzid case fi node li kadol 3la ana dak word rah bda bi '\'' ola bda b double '\"'

# * khasni nremove the first .
# */