/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 05:40:07 by sidrissi          #+#    #+#             */
/*   Updated: 2025/03/14 17:11:13 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (perror("failed to open /dev/random\n"), NULL);
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
	read_fd = open(random_fd, O_RDONLY, 0644); // should close in executation
	if (unlink(random_fd) || (write_fd < 0) || (read_fd < 0))
		return (perror("unlink faile\n"), 1);
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
	}
	return (close(write_fd), 0);
}

void	ft_herdoc(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == HERDOC)
		{
			if (!current->next || current->next->type != F_HERDOC)
			{
				return ;
			}
			if (open_herdoc(current->next->value))
			{
				return ;
			}
		}
		current = current->next;
	}
}
