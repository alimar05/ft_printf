/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:49:22 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/01 17:03:02 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*h_else_hh_size(va_list arg, t_specifier *specifier, char *buffer, char *sign)
{
	if (specifier->size[0] == 'h' && specifier->size[1] == '\0')
	{
		specifier->num_int.num_s = va_arg(arg, int);
		specifier->num_int.num_s = (short)specifier->num_int.num_s;
		if (specifier->num_int.num_s < 0)
		{
			*sign = -1;
			specifier->num_int.num_s *= -1;
		}
		return (ft_itoa_base(specifier->num_int.num_s, 10, buffer));	
	}
	else if (specifier->size[0] == 'h' && specifier->size[1] == 'h')
	{
		specifier->num_int.num_c = va_arg(arg, int);
		specifier->num_int.num_s = (char)specifier->num_int.num_s;
		if (specifier->num_int.num_c < 0)
		{
			*sign = -1;
			specifier->num_int.num_c *= -1;
		}
		return (ft_itoa_base(specifier->num_int.num_c, 10, buffer));
	}
}

static char	*l_else_ll_size(va_list arg, t_specifier *specifier, char *buffer, char *sign)
{
	if (specifier->size[0] == 'l' && specifier->size[1] == '\0')
	{
		specifier->num_int.num_l = va_arg(arg, long int);
		if (specifier->num_int.num_l < 0)
		{
			*sign = -1;
			specifier->num_int.num_l *= -1;
		}
		return (ft_itoa_base(specifier->num_int.num_l, 10, buffer));
	}
	else if (specifier->size[0] == 'l' && specifier->size[1] == 'l')
	{
		specifier->num_int.num_ll = va_arg(arg, long long int);
		if (specifier->num_int.num_ll < 0)
		{
			*sign = -1;
			specifier->num_int.num_ll *= -1;
		}
		return (ft_itoa_base(specifier->num_int.num_ll, 10, buffer));
	}
}

static void	print_minus(t_specifier *specifier, char *ptr, char *sign, int *i)
{
	if (*sign < 0)
	{
		write(1, "-", 1);
		specifier->width--;
		specifier->num_bytes++;
	}
	write(1, ptr, *i);
	specifier->num_bytes += *i;
	while ((*i)++ < specifier->width)
	{
		write(1, " ", 1);
		specifier->num_bytes++;
	}
}

static void	print_no_minus(t_specifier *specifier, char *ptr, char *sign, int *i)
{
	int         j;

	if (*sign < 0)
	{
		specifier->width--;
		specifier->num_bytes++;
	}
	j = *i;
    if (specifier->null && *sign < 0)
        write(1, "-", 1);
	while ((*i)++ < specifier->width)
	{
        if (specifier->null)
            write(1, "0", 1);
        else
		    write(1, " ", 1);
		specifier->num_bytes++;
	}
	if (*sign < 0)
		write(1, "-", 1);
	write(1, ptr, j);
	specifier->num_bytes += j;
}

void	    ft_putdec(va_list arg, t_specifier *specifier)
{
	int			i;
	char		*ptr;
	char		sign;
	char		buffer[21];

	sign = 1;
	if (specifier->size[0] == '\0' && specifier->size[1] == '\0')
	{
		specifier->num_int.num_i = va_arg(arg, int);
		if (specifier->num_int.num_i < 0)
		{
			sign = -1;
			specifier->num_int.num_i *= -1;
		}
		ptr = ft_itoa_base(specifier->num_int.num_i, 10, buffer);
	}
	else if (specifier->size[0] == 'h' && (specifier->size[1] == '\0'
				|| specifier->size[1] == 'h'))
		ptr = h_else_hh_size(arg, specifier, buffer, &sign);
	else if (specifier->size[0] == 'l' && (specifier->size[1] == '\0'
				|| specifier->size[1] == 'l'))
		ptr = l_else_ll_size(arg, specifier, buffer, &sign);
	STRLEN(ptr, i);
	if (specifier->minus)
		print_minus(specifier, ptr, &sign, &i);
	else
		print_no_minus(specifier, ptr, &sign, &i);
}
