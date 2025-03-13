/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 05:40:07 by sidrissi          #+#    #+#             */
/*   Updated: 2025/03/13 22:25:59 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


static int	open_herdoc(char *delimter)
{
	int		fd_herdoc;
	char	*line;

	fd_herdoc = open("herdoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_herdoc < 0)
		return (printf("can't open ft_herdoc\n"), 1);
	while (1)
	{
		line = readline("> ");
		printf("%s\n", line);
		if (!line)
			break ;
		if (ft_strcmp(line, delimter) == 0)
		{
			free(line);
			break;
		}
		write(fd_herdoc, line, ft_strlen(line));
		write(fd_herdoc, "\n", 1);
		free(line);
	}
	close(fd_herdoc);
	return (0);
}

void    ft_herdoc(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == HERDOC)
		{
			printf("%s\n", current->value);
			if (!current->next || current->next->type != WORD)
				return ;
			open_herdoc(current->next->value);
		}
		current =current->next;
	}
}
