#include "ft_printf.h"

void	ft_putdec_int(va_list arg, t_specifier *specifier)
{
	int		i;
	__int128	num;
	char		*ptr;
	char		sign;
	char		buffer[21];

	sign = 0;
	num = va_arg(arg, __int128);
	if (num < 0)
	{
		sign = -1;
		num *= -1;
	}
	ptr = ft_itoa_base(num, 10, buffer);
	i = 0;
	while (*(ptr + i))
		i++;
	if (sign < 0)
		write(1, "-", 1);
	write(1, ptr, i);
}
