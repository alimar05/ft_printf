/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdec_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:49:22 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/01 17:03:02 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putdec_int(va_list arg, t_specifier *specifier)
{
	int			i;
	int			j;
	char		*ptr;
	char		sign;
	char		buffer[10];

	sign = 1;
	if (specifier->size[0] == 'h' && specifier->size[1] == '\0')
	{
		specifier->num_int.num_s = va_arg(arg, int);
		specifier->num_int.num_s = (short)specifier->num_int.num_s;
		if (specifier->num_int.num_s < 0)
		{
			sign = -1;
			specifier->num_int.num_s *= -1;
		}
		ptr = ft_itoa_base(specifier->num_int.num_s, 10, buffer);
	}
	else if (specifier->size[0] == 'h' && specifier->size[1] == 'h')
	{
		specifier->num_int.num_c = va_arg(arg, int);
		specifier->num_int.num_s = (char)specifier->num_int.num_s;
		if (specifier->num_int.num_c < 0)
		{
			sign = -1;
			specifier->num_int.num_c *= -1;
		}
		ptr = ft_itoa_base(specifier->num_int.num_c, 10, buffer);
	}
	else if (specifier->size[0] == '\0' && specifier->size[1] == '\0')
	{
		specifier->num_int.num_i = va_arg(arg, int);
		if (specifier->num_int.num_i < 0)
		{
			sign = -1;
			specifier->num_int.num_i *= -1;
		}
		ptr = ft_itoa_base(specifier->num_int.num_i, 10, buffer);
	}
	else if (specifier->size[0] == 'l' && specifier->size[1] == '\0')
	{
		specifier->num_int.num_l = va_arg(arg, long int);
		if (specifier->num_int.num_l < 0)
		{
			sign = -1;
			specifier->num_int.num_l *= -1;
		}
		ptr = ft_itoa_base(specifier->num_int.num_l, 10, buffer);
	}
	else if (specifier->size[0] == 'l' && specifier->size[1] == 'l')
	{
		specifier->num_int.num_ll = va_arg(arg, long long int);
		if (specifier->num_int.num_ll < 0)
		{
			sign = -1;
			specifier->num_int.num_ll *= -1;
		}
		ptr = ft_itoa_base(specifier->num_int.num_ll, 10, buffer);
	}
	i = 0;
	while (*(ptr + i))
		i++;
	if (specifier->minus)
	{
		if (sign < 0)
		{
			write(1, "-", 1);
			specifier->width--;
			specifier->num_bytes++;
		}
		write(1, ptr, i);
		specifier->num_bytes += i;
		while (i++ < specifier->width)
		{
			write(1, " ", 1);
			specifier->num_bytes++;
		}
	}
	else
	{
		if (sign < 0)
		{
			specifier->width--;
			specifier->num_bytes++;
		}
		j = i;
		while (i++ < specifier->width)
		{
			write(1, " ", 1);
			specifier->num_bytes++;
		}
		if (sign < 0)
			write(1, "-", 1);
		write(1, ptr, j);
		specifier->num_bytes += j;
	}
}
