/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grabage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidrissi <sidrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:58:28 by sidrissi          #+#    #+#             */
/*   Updated: 2025/02/27 14:14:48 by sidrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = temp;
	}
}

t_token	*deldum(t_token **head)
{
	t_token *temp;

	if (!head)
		return (NULL);
	temp = *head;
	*head = (*head)->next;
	free(temp->value);
	free(temp);
	temp = NULL;
	return (*head);
}