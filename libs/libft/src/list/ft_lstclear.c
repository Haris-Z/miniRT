/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:58:07 by hazunic           #+#    #+#             */
/*   Updated: 2025/03/04 12:18:29 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current_node;
	t_list	*next;

	if (lst == NULL)
		return ;
	current_node = *lst;
	while (current_node != NULL)
	{
		next = current_node->next;
		if (del != NULL)
			del(current_node->content);
		free(current_node);
		current_node = next;
	}
	*lst = NULL;
}
