#include "ft_printf.h"

void	ft_putoct(va_list arg, t_specifier *specifier)
{
	int		i;
	int		j;
	size_t	num;
	char	*ptr;
	char	buffer[21];

	num = va_arg(arg, size_t);
	ptr = ft_itoa_base(num, 8, buffer);
	STRLEN(ptr, i);
	if (specifier->minus)
	{
        if (specifier->sharp)
        {
            write(1, "0", 1);
            specifier->width--;
			specifier->num_bytes++;
        }
		write(1, ptr, i);
		specifier->num_bytes += i;
		while (i++ < specifier->width)
		{
			write(1, " ", 1);
			specifier->num_bytes++;
		}
	}
	else
	{
		j = i;
        if (specifier->sharp)
        {
            specifier->width--;
			specifier->num_bytes++;
        }
		while (j++ < specifier->width)
		{
			if (specifier->null && !specifier->dot)
				write(1, "0", 1);
			else
				write(1, " ", 1);
			specifier->num_bytes++;
		}
        if (specifier->sharp)
            write(1, "0", 1);
		write(1, ptr, i);
		specifier->num_bytes += i;
	}
}
