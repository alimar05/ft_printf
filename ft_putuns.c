/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 11:53:37 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/08 14:57:27 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_minus(t_specifier *specifier, char *ptr, int *i)
{
	write(1, ptr, *i);
	specifier->num_bytes += *i;
	while ((*i)++ < specifier->width)
	{
		write(1, " ", 1);
		specifier->num_bytes++;
	}
}

static void	print_no_minus(t_specifier *specifier, char *ptr, int *i)
{
	int		j;

	if (specifier->sign < 0)
	{
		specifier->width--;
		specifier->num_bytes++;
	}
	j = *i;
	while ((*i)++ < specifier->width)
	{
        if (specifier->null)
            write(1, "0", 1);
        else
		    write(1, " ", 1);
		specifier->num_bytes++;
	}
	write(1, ptr, j);
	specifier->num_bytes += j;
}

void	    ft_putuns(va_list arg, t_specifier *specifier)
{
	int		i;
	char	*ptr;
	char	buffer[21];

	ptr = NULL;
	specifier->base = 10;
	specifier->is_uns = 1;
	if (specifier->size[0] == '\0' && specifier->size[1] == '\0')
		ptr = null_and_null_size(arg, specifier, buffer);
	else if (specifier->size[0] == 'h' && (specifier->size[1] == '\0'
				|| specifier->size[1] == 'h'))
		ptr = h_else_hh_size(arg, specifier, buffer);
	else if (specifier->size[0] == 'l' && (specifier->size[1] == '\0'
				|| specifier->size[1] == 'l'))
		ptr = l_else_ll_size(arg, specifier, buffer);
	STRLEN(ptr, i);
	if (specifier->minus)
		print_minus(specifier, ptr, &i);
	else
		print_no_minus(specifier, ptr, &i);
}
