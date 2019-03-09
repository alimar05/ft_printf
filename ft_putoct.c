/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putoct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:22:46 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/09 12:32:51 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_minus(t_specifier *specifier, char *ptr, int *i)
{
	if (specifier->sharp)
	{
		write(1, "0", 1);
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

static void	print_no_minus(t_specifier *specifier, char *ptr, int *i)
{
	int		j;

	j = *i;
	if (specifier->sharp)
	{
		specifier->width--;
		specifier->num_bytes++;
	}
	while (j++ < specifier->width)
	{
		if (specifier->null && !specifier->dot)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		specifier->num_bytes++;
	}
	if (specifier->sharp)
		write(1, "0", 1);
	write(1, ptr, *i);
	specifier->num_bytes += *i;
}

void		ft_putoct(va_list arg, t_specifier *specifier)
{
	int		i;
	char	*ptr;
	char	buffer[21];

	ptr = NULL;
	specifier->base = 8;
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
