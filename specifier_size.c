/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:07:27 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/09 12:30:22 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

static void	ft_abs(t_specifier *specifier)
{
	if (specifier->num_int.num_c < 0)
	{
		specifier->sign = -1;
		specifier->num_int.num_c *= -1;
	}
	else if (specifier->num_int.num_s < 0)
	{
		specifier->sign = -1;
		specifier->num_int.num_s *= -1;
	}
	else if (specifier->num_int.num_i < 0)
	{
		specifier->sign = -1;
		specifier->num_int.num_i *= -1;
	}
	else if (specifier->num_int.num_l < 0)
	{
		specifier->sign = -1;
		specifier->num_int.num_l *= -1;
	}
	else if (specifier->num_int.num_ll < 0)
	{
		specifier->sign = -1;
		specifier->num_int.num_ll *= -1;
	}
}

char		*nul_and_nul_size(va_list arg, t_specifier *specifier, char *buffer)
{
	if (specifier->base == 10 && !specifier->is_uns)
	{
		specifier->num_int.num_i = va_arg(arg, int);
		ft_abs(specifier);
		return (ft_itoa_base(specifier->num_int.num_i,
					specifier->base, buffer, specifier->is_upcase));
	}
	else
		return (ft_itoa_base(va_arg(arg, unsigned int),
					specifier->base, buffer, specifier->is_upcase));
}

char		*h_else_hh_size(va_list arg, t_specifier *specifier, char *buffer)
{
	if (specifier->size[0] == 'h' && specifier->size[1] == '\0')
		if (specifier->base == 10 && !specifier->is_uns)
		{
			specifier->num_int.num_s = va_arg(arg, int);
			ft_abs(specifier);
			return (ft_itoa_base(specifier->num_int.num_s,
						specifier->base, buffer, specifier->is_upcase));
		}
		else
			return (ft_itoa_base((unsigned short)va_arg(arg, unsigned int),
						specifier->base, buffer, specifier->is_upcase));
	else if (specifier->size[0] == 'h' && specifier->size[1] == 'h')
	{
		if (specifier->base == 10 && !specifier->is_uns)
		{
			specifier->num_int.num_c = va_arg(arg, int);
			ft_abs(specifier);
			return (ft_itoa_base(specifier->num_int.num_c,
						specifier->base, buffer, specifier->is_upcase));
		}
		else
			return (ft_itoa_base((unsigned char)va_arg(arg, unsigned int),
						specifier->base, buffer, specifier->is_upcase));
	}
	return (NULL);
}

char		*l_else_ll_size(va_list arg, t_specifier *specifier, char *buffer)
{
	if (specifier->size[0] == 'l' && specifier->size[1] == '\0')
		if (specifier->base == 10 && !specifier->is_uns)
		{
			specifier->num_int.num_l = va_arg(arg, long int);
			ft_abs(specifier);
			return (ft_itoa_base(specifier->num_int.num_l, specifier->base,
						buffer, specifier->is_upcase));
		}
		else
			return (ft_itoa_base(va_arg(arg, unsigned long int),
						specifier->base, buffer, specifier->is_upcase));
	else if (specifier->size[0] == 'l' && specifier->size[1] == 'l')
	{
		if (specifier->base == 10 && !specifier->is_uns)
		{
			specifier->num_int.num_ll = va_arg(arg, long long int);
			ft_abs(specifier);
			return (ft_itoa_base(specifier->num_int.num_ll,
						specifier->base, buffer, specifier->is_upcase));
		}
		else
			return (ft_itoa_base(va_arg(arg, unsigned long long int),
						specifier->base, buffer, specifier->is_upcase));
	}
	return (NULL);
}
