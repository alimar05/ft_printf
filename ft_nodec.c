/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 14:17:16 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/17 16:34:20 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_puthex(va_list arg, t_specifier *specifier)
{
	int		i;
	char	*ptr;
	char	buffer[21];

	specifier->base = 16;
	specifier->view = "0x";
	specifier->view_size = 2;
	ptr = determine_size_num(arg, specifier, buffer);
	STRLEN(ptr, i);
	if (specifier->minus)
		print_no_dec_minus(specifier, ptr, &i);
	else
		print_no_dec_no_minus(specifier, ptr, &i);
}

void		ft_puthex_upcase(va_list arg, t_specifier *specifier)
{
	int		i;
	char	*ptr;
	char	buffer[21];

	specifier->base = 16;
	specifier->view = "0X";
	specifier->view_size = 2;
	specifier->is_upcase = 1;
	ptr = determine_size_num(arg, specifier, buffer);
	STRLEN(ptr, i);
	if (specifier->minus)
		print_no_dec_minus(specifier, ptr, &i);
	else
		print_no_dec_no_minus(specifier, ptr, &i);
}

void		ft_putoct(va_list arg, t_specifier *specifier)
{
	int		i;
	char	*ptr;
	char	buffer[21];

	specifier->base = 8;
	specifier->view = "0";
	specifier->view_size = 1;
	ptr = determine_size_num(arg, specifier, buffer);
	STRLEN(ptr, i);
	if (specifier->minus)
		print_no_dec_minus(specifier, ptr, &i);
	else
		print_no_dec_no_minus(specifier, ptr, &i);
}

void		ft_putbin(va_list arg, t_specifier *specifier)
{
	int		i;
	char	*ptr;
	char	buffer[21];

	specifier->base = 2;
	specifier->view = "0b";
	specifier->view_size = 2;
	ptr = determine_size_num(arg, specifier, buffer);
	STRLEN(ptr, i);
	if (specifier->minus)
		print_no_dec_minus(specifier, ptr, &i);
	else
		print_no_dec_no_minus(specifier, ptr, &i);
}

void		ft_putadr(va_list arg, t_specifier *specifier)
{
	int		i;
	char	*ptr;
	char	buffer[21];

	ptr = NULL;
	specifier->base = 16;
	specifier->sharp = 1;
	specifier->type = 'p';
	specifier->view = "0x";
	specifier->view_size = 2;
	ptr = ft_itoa_base_uns(specifier, va_arg(arg, size_t), buffer);
	STRLEN(ptr, i);
	if (*ptr == '0')
	{
		specifier->num_bytes += specifier->view_size;
		specifier->width -= specifier->view_size;
	}
	if (specifier->minus)
		print_no_dec_minus(specifier, ptr, &i);
	else
		print_no_dec_no_minus(specifier, ptr, &i);
}
