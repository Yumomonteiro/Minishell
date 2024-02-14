/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:31:17 by yude-oli          #+#    #+#             */
/*   Updated: 2024/01/29 14:02:13 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			x;
	long int	y;

	y = 0;
	x = 1;
	if ((*str == 43 || *str == 45) && ft_isdigit(*(str + 1)))
	{
		if (*str == 45)
			x *= -1;
		str++;
	}
	while (*str <= 57 && *str >= 48)
	{
		if (!ft_isdigit(*str) && *str != '\0')
			ft_display_exit();
		y = (y * 10) + ((*str - 48) % 10);
		str++;
	}
	if (!ft_isdigit(*str) && *str != '\0')
		ft_display_exit();
	y *= x;
	if (y > 2147483647 || y < -2147483648)
		ft_display_exit();
	return ((int) y);
}
/*
int main(void)
{
	char str[] = "-132132fafa";
	printf("%d\n", ft_atoi(str));
	return (0);
}*/