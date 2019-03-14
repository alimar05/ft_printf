/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 12:52:42 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/14 13:58:42 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_minus(t_specifier *specifier, char *ptr, int *i)
{
	if (*ptr != '0' && specifier->sharp)
	{
		write(1, "0x", 2);
		specifier->width -= 2;
		specifier->num_bytes += 2;
	}
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

	if (*ptr != '0' && specifier->sharp)
	{
		specifier->width -= 2;
		specifier->num_bytes += 2;
	}
	if (*ptr != '0' && specifier->sharp && specifier->null && !specifier->dot)
		write(1, "0x", 2);
	j = *i;
	while (j++ < specifier->width)
	{
		if (specifier->null && !specifier->dot)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		specifier->num_bytes++;
	}
	if (*ptr != '0' && specifier->sharp && (!specifier->null || specifier->dot))
		write(1, "0x", 2);
	write(1, ptr, *i);
	specifier->num_bytes += *i;
}

void		ft_puthex(va_list arg, t_specifier *specifier)
{
	int		i;
	char	*ptr;
	char	buffer[21];

	ptr = NULL;
	specifier->base = 16;
	if (specifier->size[0] == '\0' && specifier->size[1] == '\0')
		ptr = nul_and_nul_size(arg, specifier, buffer);
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
