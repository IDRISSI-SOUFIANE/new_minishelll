/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:15:46 by sidrissi          #+#    #+#             */
/*   Updated: 2025/03/13 22:07:31 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int	check_quotes(char *line, int i, int count_quote)
{
	char	quote;

	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			count_quote++;
			i++;
			while (line[i] && line[i] != quote)
				i++;
			if (line[i] == quote)
				count_quote++;
			else
				break ;
			i++;
		}
		else
			i++;
	}
	if (count_quote % 2)
		return (1);
	return (0);
}

int	lexing(char *line)
{
	int		i;
	int		count_quote;
	t_token	*tokens;
	
	i = 0;
	count_quote = 0;
	if (check_quotes(line, i, count_quote))
		return (ft_putstr_fd("missing of Quotation\n", 2), 1);
	tokens = tokenization(line, i);
	if (NULL == tokens) // you can remove it and free (NULL) if you need more line
		return (0); // if tokens = NULL so return (0); to continue reading => new prompt
	if (error1(tokens))
	{
		free_tokens(tokens);
		return (1);
	}

	expand(tokens);

	ft_rename(tokens);

	ft_herdoc(tokens);

	// t_token *temp;

	// temp = tokens;
	// while (temp)
	// {
	// 	printf("value: %s\t type: %d \n", temp->value, temp->type);
	// 	temp = temp->next;
	// }
	free_tokens(tokens);
	return (0);
}


int main(int ac , char **av, char **env)
{
	((void)ac, (void)av, (void)env);

	char	*line;
	while (1)
	{
		line = readline("Minishell: ");
		if (line == NULL)
			break ;
		lexing(line);
		// lexing(line, env);
		// if (lexing(line))
		// 	return (free(line), 1);

		// parsing line


		// executre
		
		if (line[0] !=  '\0')
			add_history(line);
		free(line);
	}
	return (0);
}
