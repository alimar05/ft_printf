#include "ft_printf.h"

void	ft_putdec_int(va_list arg, t_specifier *specifier)
{
	int			i;
	char		*ptr;
	char		sign;
	char		buffer[10];

	sign = 0;
	if (specifier->size[0] == '\0' && specifier->size[1] == '\0')
	{
		specifier->num_int.num_i = va_arg(arg, int);
		if (specifier->num_int.num_i < 0)
		{
			sign = -1;
			specifier->num_int.num_i *= -1;
		}
		ptr = ft_itoa_base(specifier->num_int.num_i, 10, buffer);
	}
	else if (specifier->size[0] == 'l' && specifier->size[1] == '\0')
	{
		specifier->num_int.num_l = va_arg(arg, long int);
		if (specifier->num_int.num_l < 0)
		{
			sign = -1;
			specifier->num_int.num_l *= -1;
		}
		ptr = ft_itoa_base(specifier->num_int.num_l, 10, buffer);
	}
	else if (specifier->size[0] == 'l' && specifier->size[1] == 'l')
	{
		specifier->num_int.num_ll = va_arg(arg, long long int);
		if (specifier->num_int.num_ll < 0)
		{
			sign = -1;
			specifier->num_int.num_ll *= -1;
		}
		ptr = ft_itoa_base(specifier->num_int.num_ll, 10, buffer);
	}
	i = 0;
	while (*(ptr + i))
		i++;
	if (sign < 0)
	{
		write(1, "-", 1);
		specifier->num_bytes++;
	}
	write(1, ptr, i);
	specifier->num_bytes += i;
}
