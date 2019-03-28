/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 13:12:02 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/28 15:05:35 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <float.h>

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
	specifier->sign = 1;
	specifier->is_uns = 0;
	specifier->is_upcase = 0;
	specifier->num_int.num_c = 0;
	specifier->num_int.num_s = 0;
	specifier->num_int.num_i = 0;
	specifier->num_int.num_l = 0;
	specifier->num_int.num_ll = 0;
}

char		*ft_itoa_base(t_specifier *specifier, long int num, char *buffer)
{
	char		*ptr;
	size_t		temp;

	if (num == 0)
		return ("0");
	if (num < 0)
	{
		temp = num * -1;
		specifier->sign = -1;
	}
	else
		temp = num;
	ptr = buffer + 21;
	*ptr = '\0';
	while (temp != 0)
	{
		*--ptr = "0123456789"[temp % specifier->base];
		temp /= specifier->base;
	}
	return (ptr);
}

char		*ft_itoa_base_uns(t_specifier *specifier, size_t num, char *buffer)
{
	char		*ptr;

	if (num == 0)
		return ("0");
	ptr = buffer + 21;
	*ptr = '\0';
	while (num != 0)
	{
		if (!specifier->is_upcase)
			*--ptr = "0123456789abcdef"[num % specifier->base];
		else
			*--ptr = "0123456789ABCDEF"[num % specifier->base];
		num /= specifier->base;
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
	double	d;

	d = 12.12234789;
	printf("%d\n", printf("|%20.15f|", d));
	printf("%d\n", ft_printf("|%20.15f|", d));

//	printf("%d\n", printf("|%#0500f|", -DBL_MAX));
//	printf("%d\n", ft_printf("|%#0500f|", -DBL_MAX));

//	printf("%d\n", printf("|%+10.5d|", 18446744073709551615));
//	printf("%d\n", ft_printf("|%+10.5d|", 18446744073709551615));
//	printf("%d\n", printf("|%lx|", 9223372036854775808));
//	printf("%d\n", ft_printf("|%lx|", 9223372036854775808));
//	printf("%d\n", printf("|%ld|", 9223372036854775808));
//	printf("%d\n", ft_printf("|%ld|", 9223372036854775808));
	return (0);
}
