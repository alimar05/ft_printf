/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:35:49 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/01 15:17:56 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

typedef union		u_num_int
{
	short			num_s;
	int				num_i;
	long int		num_l;
	long long int	num_ll;
}					t_num_int;

typedef struct		s_specifier
{
	unsigned int	minus:1;
	unsigned int	plus:1;
	unsigned int	null:1;
	unsigned int	space:1;
	unsigned int	sharp:1;
	int				width;
	unsigned int	dot:1;
	int				precision;
	char			size[3];
	t_num_int		num_int;
	int				num_bytes;
}					t_specifier;

void				ft_putadr(va_list arg, t_specifier *specifier);
void				ft_putstr(va_list arg, t_specifier *specifier);
void				ft_putchar(va_list arg, t_specifier *specifier);
void				ft_putdec_int(va_list arg, t_specifier *specifier);
char				*ft_itoa_base(size_t num, size_t base, char *buffer);
char				*specifier_parse(char *format, t_specifier *specifier,
		va_list arg);
#endif
