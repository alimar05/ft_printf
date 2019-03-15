/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:18:49 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/15 20:30:42 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_minus(t_specifier *specifier, char *ptr, int *i)
{
	int		j;

	j = *i;
	dec_minus_sign_plus_space_dot(specifier, i);
	write(1, ptr, *i);
	specifier->num_bytes += *i;
	padding(specifier, specifier->width, ' ', i);
}

static void	print_no_minus(t_specifier *specifier, char *ptr, int *i)
{
	if (specifier->null && !specifier->dot && specifier->sign > 0)
		dec_no_minus_null(specifier, ptr, i);
	else if (!specifier->null && !specifier->dot && specifier->sign > 0)
		dec_no_minus(specifier, ptr, i);
	else if (specifier->null && !specifier->dot && specifier->sign < 0)
		dec_no_minus_null_sign(specifier, ptr, i);
	else if (!specifier->null && !specifier->dot && specifier->sign < 0)
		dec_no_minus_sign(specifier, ptr, i);
	else if (specifier->dot && specifier->sign > 0)
		dec_no_minus_dot(specifier, ptr, i);
	else if (specifier->dot && specifier->sign < 0)
		dec_no_minus_dot_sign(specifier, ptr, i);
}

void		ft_putdec(va_list arg, t_specifier *specifier)
{
	int		i;
	char	*ptr;
	char	buffer[21];

	ptr = NULL;
	specifier->base = 10;
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
