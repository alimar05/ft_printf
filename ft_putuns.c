/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 11:53:37 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/17 13:32:46 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putuns(va_list arg, t_specifier *specifier)
{
	int		i;
	char	*ptr;
	char	buffer[21];

	specifier->base = 10;
	specifier->view = "";
	specifier->is_uns = 1;
	specifier->view_size = 0;
	ptr = determine_size_num(arg, specifier, buffer);
	STRLEN(ptr, i);
	if (specifier->minus)
		print_no_dec_minus(specifier, ptr, &i);
	else
		print_no_dec_no_minus(specifier, ptr, &i);
}
