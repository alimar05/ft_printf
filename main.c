/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 13:12:02 by rymuller          #+#    #+#             */
/*   Updated: 2019/02/26 18:34:40 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

static void	specifier_init(t_specifier *specifier)
{
	specifier->minus = 0;
	specifier->plus = 0;
	specifier->null = 0;
	specifier->space = 0;
	specifier->sharp = 0;
	specifier->width = 0;
	specifier->dot = 0;
	specifier->precision = 0;
	specifier->size[0] = '\0';
	specifier->size[1] = '\0';
	specifier->size[2] = '\0';
}

void		ft_atoi_base(size_t num, int base)
{
	int			i;
	char		*ptr;
	char		buffer[9];

	if (num == 0)
		write(1, "0", 1);
	ptr = buffer + 8;
	*ptr = '\0';
	while (num != 0)
	{
		*--ptr = "0123456789abcdef"[num % base];
		num /= base;
	}
	i = 0;
	while (*(ptr + i))
		i++;
	write(1, ptr, i);
}

void		ft_printf(const char *format, ...)
{
	va_list		arg;
	t_specifier	specifier;

	va_start(arg, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			specifier_init(&specifier);
			format = specifier_parse((char *)format, &specifier, arg);
		}
		else
		{
			write(1, format, 1);
			format++;
		}
	}
	/*
	printf("%d\n", specifier.sharp);
	printf("%d\n", specifier.plus);
	printf("%d\n", specifier.minus);
	printf("%d\n", specifier.space);
	printf("%d\n", specifier.null);
	printf("%d\n", specifier.width);
	printf("%d\n", specifier.dot);
	printf("%d\n", specifier.precision);
	printf("%s\n", specifier.size);
	*/
	va_end(arg);
}

int			main(void)
{
//	int		a = 0;

//	printf("|%023p|\n", -234);
//	ft_printf("|%023p|\n", -234);
	printf("|%20s|\n", "999999999999999999");
	ft_printf("|%20s|\n", "99999999999999999999");
	return (0);
}
