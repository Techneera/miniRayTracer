/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:29:38 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/04/15 15:17:40 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// #include <stdio.h>
// #include <stdlib.h>
// int	main(void)
// {
// 	char	arr[] = "JULIOSOUZA";
// 	size_t	i = 0;
// 	t_list	**head = malloc(sizeof(t_list *));
// 	t_list	*tmp;
// 	
// 	*head = ft_lstnew((void *)&arr[i++]);
// 	tmp = *head;
// 	while (arr[i] && tmp != NULL)
// 	{
// 		tmp->next = ft_lstnew((void *)&arr[i]);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	t_list	*last_node = ft_lstlast(*head);	
// 	printf("%c\n", *(char *)last_node->content);
// 	printf("%d\n", ft_lstsize(*head));
// 	return (0);	
// }
