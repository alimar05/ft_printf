/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:35:49 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/15 18:54:35 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

typedef struct				s_num_int
{
	char					num_c;
	short					num_s;
	int						num_i;
	long int				num_l;
	long long int			num_ll;
}							t_num_int;

typedef struct				s_specifier
{
	unsigned int			minus:1;
	unsigned int			plus:1;
	unsigned int			null:1;
	unsigned int			space:1;
	unsigned int			sharp:1;
	int						width;
	unsigned int			dot:1;
	int						precision;
	char					size[3];
	t_num_int				num_int;
	unsigned int			base:5;
	char					sign:2;
	unsigned int			is_uns:1;
	unsigned int			is_upcase:1;
	char					*view;
	char					view_size;
	int						num_bytes;
}							t_specifier;

void						ft_putadr(va_list arg, t_specifier *specifier);
void						ft_putstr(va_list arg, t_specifier *specifier);
void						ft_putdec(va_list arg, t_specifier *specifier);
void						ft_putoct(va_list arg, t_specifier *specifier);
void						ft_putuns(va_list arg, t_specifier *specifier);
void						ft_puthex(va_list arg, t_specifier *specifier);
void						ft_putbin(va_list arg, t_specifier *specifier);
void						ft_putchar(va_list arg, t_specifier *specifier);
void						dec_no_minus(t_specifier *specifier, char *ptr, int *i);
void						dec_no_minus_dot(t_specifier *specifier, char *ptr, int *i);
void						dec_no_minus_null(t_specifier *specifier, char *ptr, int *i);
void						dec_no_minus_sign(t_specifier *specifier, char *ptr, int *i);
void						dec_no_minus_dot_sign(t_specifier *specifier, char *ptr, int *i);
void						dec_no_minus_null_sign(t_specifier *specifier, char *ptr, int *i);
void						dec_minus_sign_plus_space_dot(t_specifier *specifier, int *i);
void						print_no_dec_minus(t_specifier *specifier, char *ptr, int *i);
void						print_no_dec_no_minus(t_specifier *specifier, char *ptr, int *i);
void						null_value(t_specifier *specifier, char *ptr, int *i);
void						padding(t_specifier *specifier, int boundary, char c, int *i);
void						view(t_specifier *specifier, char *ptr);
char						*specifier_size(char *format,
		t_specifier *specifier);
void						ft_puthex_upcase(va_list arg,
		t_specifier *specifier);
char						*specifier_type(char *format,
		t_specifier *specifier, va_list arg);
char						*ft_itoa_base(t_specifier *specifier_parse, long int num, 
		char *buffer);
char						*ft_itoa_base_uns(t_specifier *specifier_parse, size_t num, 
		char *buffer);
char						*specifier_parse(char *format,
		t_specifier *specifier, va_list arg);
char						*nul_and_nul_size(va_list arg,
		t_specifier *specifier, char *buffer);
char						*h_else_hh_size(va_list arg,
		t_specifier *specifier, char *buffer);
char						*l_else_ll_size(va_list arg,
		t_specifier *specifier, char *buffer);
# define STRLEN(ptr, i) i = 0; while (*(ptr + i)) i++
#endif
