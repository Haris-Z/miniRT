/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:23:13 by hazunic           #+#    #+#             */
/*   Updated: 2025/06/12 02:37:33 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	if (lst == NULL || new == NULL )
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last_node = ft_lstlast(*lst);
	last_node->next = new;
}

/*
int	main(void)
{
	printf("file:\t%s\n", __FILE__);
	t_list	*head;
	t_list *second;
	t_list *third;

	head = ft_lstnew("first");
	second = ft_lstnew("second");
	third = ft_lstnew("third");
	
	ft_lstadd_back(&head, second);
	ft_lstadd_back(&head, third);

	t_list *tmp;
	
	tmp = head;
	printf("List : \t");
	int i = 0;
	while (tmp != NULL)
	{
		char *content = tmp->content;
		printf("node[%d]:\tcontent = [\"%s\"] \t| next
		 = [%p]\n\t",i , content, tmp->next);
		tmp = tmp->next;
		i++;
	}
	printf("\n");
	return (0);
}
*/