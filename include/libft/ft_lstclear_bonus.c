/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:13:23 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/15 16:23:04 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*free_node;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		free_node = tmp;
		del(free_node->content);
		tmp = tmp->next;
		free(free_node);
	}
	*lst = tmp;
}
