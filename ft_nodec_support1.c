/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodec_support1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 18:52:19 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/30 17:36:58 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	put_null_or_space(t_specifier *specifier, char *c)
{
	write(1, c, 1);
	specifier->num_bytes++;
}

void		null_value(t_specifier *specifier, char *ptr, int *i)
{
	if (*ptr == '0' && specifier->base == 8 && specifier->sharp
			&& !specifier->precision)
		put_null_or_space(specifier, "0");
	else if (*ptr == '0' && !specifier->precision && specifier->width
			&& specifier->type != 'p')
		put_null_or_space(specifier, " ");
	else if (*ptr == '0' && specifier->type == 'p' && !specifier->precision)
		write(1, "", 0);
	else if (*ptr == '0' && specifier->type == 'p' && specifier->precision)
		put_null_or_space(specifier, "0");
	else if (*ptr == '0' && !specifier->precision && !specifier->width)
		write(1, "", 0);
	else
	{
		write(1, ptr, *i);
		specifier->num_bytes += *i;
	}
}

void		padding(t_specifier *specifier, int boundary, char c, int *i)
{
	int		j;

	j = *i;
	while (j++ < boundary)
	{
		write(1, &c, 1);
		specifier->num_bytes++;
	}
}

void		view(t_specifier *specifier, char *ptr)
{
	if (specifier->sharp && *ptr != '0')
	{
		write(1, specifier->view, specifier->view_size);
		specifier->num_bytes += specifier->view_size;
	}
	else if (*ptr == '0' && specifier->type == 'p')
		write(1, specifier->view, specifier->view_size);
}
