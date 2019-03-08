/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 12:46:46 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/08 14:55:55 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_minus(t_specifier *specifier, char *ptr, int *i)
{
	write(1, "0x", 2);
	write(1, ptr, *i);
	specifier->num_bytes += *i + 2;
	while ((*i)++ < specifier->width - 2)
	{
		write(1, " ", 1);
		specifier->num_bytes++;
	}
}

static void	print_no_minus(t_specifier *specifier, char *ptr, int *i)
{
	int		j;

	j = *i;
	if (specifier->null && !specifier->dot)
		write(1, "0x", 2);
	while (j++ < specifier->width - 2)
	{
		if (specifier->null && !specifier->dot)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		specifier->num_bytes++;
	}
	if (!(specifier->null && !specifier->dot))
		write(1, "0x", 2);
	write(1, ptr, *i);
	specifier->num_bytes += *i + 2;
}

void		ft_putadr(va_list arg, t_specifier *specifier)
{
	int		i;
	size_t	num;
	char	*ptr;
	char	buffer[21];

	ptr = NULL;
	num = va_arg(arg, size_t);
	ptr = ft_itoa_base(num, 16, buffer, specifier->is_upcase);
	STRLEN(ptr, i);
	if (specifier->minus)
		print_minus(specifier, ptr, &i);
	else
		print_no_minus(specifier, ptr, &i);
}
