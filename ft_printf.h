/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:35:49 by rymuller          #+#    #+#             */
/*   Updated: 2019/02/27 12:53:08 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

typedef struct	s_specifier
{
	int			minus:1;
	int			plus:1;
	int			null:1;
	int			space:1;
	int			sharp:1;
	int			width;
	int			dot:1;
	int			precision;
	char		size[3];
}				t_specifier;

void			ft_putadr(va_list arg, t_specifier *specifier);
void			ft_putstr(va_list arg, t_specifier *specifier);
void			ft_putchar(va_list arg, t_specifier *specifier);
char			*ft_atoi_base(size_t num, int base, char *buffer);
char			*specifier_parse(char *format, t_specifier *specifier, va_list arg);

#endif
