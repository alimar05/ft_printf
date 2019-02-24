/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:35:49 by rymuller          #+#    #+#             */
/*   Updated: 2019/02/24 19:04:52 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

typedef struct		s_specifier
{
	unsigned int	minus:1;
	unsigned int	plus:1;
	unsigned int	null:1;
	unsigned int	space:1;
	unsigned int	sharp:1;
	unsigned int	width;
	unsigned int	dot:1;
	unsigned int	precision;
	char			size[3];
}					t_specifier;

void				ft_putstr(va_list arg, t_specifier *specifier);
void				ft_putchar(va_list arg, t_specifier *specifier);
char				*specifier_parse(char *format, t_specifier *specifier, va_list arg);

#endif
