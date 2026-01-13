/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbylund <tbylund@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:42:52 by tbylund           #+#    #+#             */
/*   Updated: 2024/10/19 16:23:53 by tbylund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp_list;

	if (lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		temp_list = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		(*lst) = temp_list;
	}
	*lst = NULL;
}
