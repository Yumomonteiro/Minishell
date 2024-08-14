/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:03:59 by yude-oli          #+#    #+#             */
/*   Updated: 2023/10/06 18:18:12 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

/*#include <stdio.h>
int main() {
	char testChar = '$'; //

	if (ft_isalnum(testChar)) {
		printf("%c é alfanumérico.\n", testChar);
	} else {
		printf("%c não é alfanumérico.\n", testChar);
	}

	return 0;
}
*/