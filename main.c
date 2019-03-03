/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 13:12:02 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/01 17:03:08 by rymuller         ###   ########.fr       */
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

char		*ft_itoa_base(size_t num, size_t base, char *buffer)
{
	char		*ptr;

	if (num == 0)
		return ("0");
	ptr = buffer + 21;
	*ptr = '\0';
	while (num != 0)
	{
		*--ptr = "0123456789abcdef"[num % base];
		num /= base;
	}
	return (ptr);
}

int		ft_printf(const char *format, ...)
{
	va_list		arg;
	t_specifier	specifier;

	va_start(arg, format);
	specifier.num_bytes = 0;
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
			specifier.num_bytes++;
		}
	}
	va_end(arg);
	return (specifier.num_bytes);
}

int			main(void)
{
	printf("%d\n", printf("|%020o|", -18111142));
	printf("%d\n", ft_printf("|%020o|", -18111142));
	return (0);
}
