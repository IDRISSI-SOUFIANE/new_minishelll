/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 05:40:07 by sidrissi          #+#    #+#             */
/*   Updated: 2025/03/15 03:07:11 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../include/minishell.h"

static char	*get_word(int fd)
{
	char	*name;
	int		count;
	char	buffer;

    name = malloc(name_length + 1);
    if (!name)
	{
		return (close(fd), perror("failed malloc"), NULL);
	}
	count = 0;
	while (count < name_length)
	{
		if (read(fd, &buffer, 1) < 0)
		{
			close(fd);
			perror("read failed\n");
			return (NULL);
		}
		if (ft_isalnum(buffer))
			name[count++] = buffer;
	}
	name[name_length] = '\0';
	close(fd);
	return (name);
}
	
static char	*generate_name()
{
	int	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
		return (perror("failed to open /dev/random"), NULL);
	return (get_word(fd));
}
static int	open_herdoc(char *delimter)
{
	int		write_fd;
	int		read_fd;
	char	*random_fd;
	char	*line;

	random_fd = generate_name();
	write_fd = open(random_fd, O_WRONLY | O_CREAT , 0644);
	read_fd = open(random_fd, O_RDONLY, 0644);
	if (unlink(random_fd) || (write_fd < 0) || (read_fd < 0))
		return (perror("faile"), 1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimter) == 0)
		{
			free(line);
			break;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	} // remove delimter
	return (close(write_fd), 0);
}
void	remove_delimter(t_token **tokens, int	pos)
{
	t_token	*prev;
	t_token	*current;
	int		i;

	i = 1;
	prev = *tokens;
	while (i < pos - 1)
	{
		prev = prev->next;
		i++;
	}
	current = prev->next;
	prev->next = current->next;
	free(current);
}

void	ft_herdoc(t_token *tokens)
{
	t_token	*current;
	int		i;

	i = 1;
	current = tokens;
	while (current)
	{
		if (current->type == HERDOC)
		{
			if (!current->next || current->next->type != F_HERDOC)
				return ;
			if (!open_herdoc(current->next->value))
			{
				remove_delimter(&tokens, i);
				// remove_delimter(&tokens, i);
			}
			else
				return ;
		}
		i++;
		current = current->next;
	}
}
*/

#include "../include/minishell.h"

static char	*generate_name(void)
{
	char	*name;
	int		fd;

	// Create a temporary file using mkstemp
	name = strdup("/tmp/minishell_heredoc_XXXXXX");
	if (!name)
		return (perror("strdup failed"), NULL);
	fd = mkstemp(name);
	if (fd < 0)
	{
		free(name);
		return (perror("mkstemp failed"), NULL);
	}
	close(fd); // Close the file descriptor, we only need the name
	return (name);
}

static int	open_herdoc(char *delimiter)
{
	char	*filename;
	int		fd;
	char	*line;

	// Generate a unique filename
	filename = generate_name();
	if (!filename)
		return (1);

	// Open the file for writing
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("minishell: heredoc");
		free(filename);
		return (1);
	}

	// Read input from stdin and write to the file
	while (1)
	{
		line = readline("> ");
		if (!line) // Handle EOF (Ctrl+D)
		{
			printf("minishell: warning: here-document delimited by end-of-file (wanted `%s`)\n", delimiter);
			break;
		}
		if (ft_strcmp(line, delimiter) == 0) // Check for delimiter
		{
			free(line);
			break;
		}
		write(fd, line, strlen(line)); // Write the line to the file
		write(fd, "\n", 1); // Add a newline
		free(line);
	}

	// Clean up
	close(fd);
	free(filename);
	return (0);
}

static void	remove_heredoc_tokens(t_token **tokens, t_token *heredoc_token)
{
	t_token	*prev;
	t_token	*current;

	// Find the previous token
	prev = NULL;
	current = *tokens;
	while (current && current != heredoc_token)
	{
		prev = current;
		current = current->next;
	}

	if (!current) // HERDOC token not found
		return;

	// Remove HERDOC token
	if (prev)
		prev->next = current->next;
	else
		*tokens = current->next;
	free(current->value);
	free(current);

	// Remove delimiter token
	if (prev)
	{
		current = prev->next;
		prev->next = current->next;
		free(current->value);
		free(current);
	}
	else
	{
		current = *tokens;
		*tokens = current->next;
		free(current->value);
		free(current);
	}
}

void	ft_herdoc(t_token **tokens)
{
	t_token	*current;
	// t_token	*next;

	current = *tokens;
	while (current)
	{
		if (current->type == HERDOC)
		{
			if (!current->next || current->next->type != F_HERDOC)
			{
				printf("minishell: syntax error: missing delimiter after HERDOC\n");
				return;
			}
			if (open_herdoc(current->next->value) != 0)
			{
				printf("minishell: heredoc failed\n");
				return;
			}
			// Remove HERDOC and delimiter tokens
			remove_heredoc_tokens(tokens, current);
			// Reset current to the head of the list
			current = *tokens;
		}
		else
		{
			current = current->next;
		}
	}
}