/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ada-mata <ada-mata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:04:43 by yude-oli          #+#    #+#             */
/*   Updated: 2024/02/28 13:46:23 by ada-mata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new)
	{
		new->data = content;
		new->next = NULL;
		return (new);
	}
	else
		return (0);
}
/*
#include <stdio.h>
int main()
{
	// Criar um novo nó com a string "Hello, World!"
	t_list *new_node = ft_lstnew("Hello, World!");

	// Verificar se o nó foi criado com sucesso
	if (new_node)
	{
		// Imprimir o valor do nó
		printf("Conteúdo do nó: %s\n", (char *)new_node->content);

		// Liberar a memória alocada para o nó
		free(new_node);
	}
	else
	{
		printf("Falha ao criar o nó.\n");
	}

	return 0;
}
*/