/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:35:53 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/15 14:26:01 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		++count;
		lst = lst->next;
	}
	return (count);
}

// #include <stdlib.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int	x = 0;
// 	t_list	**head = malloc(sizeof(t_list *));
// 	*head = ft_lstnew((void *)&x);
// 	(*head)->next = NULL;
// 	return (0);
// }
