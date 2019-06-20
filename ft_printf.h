/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 10:35:49 by rymuller          #+#    #+#             */
/*   Updated: 2019/04/25 15:37:43 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# define N "\x1b[0m"
# define R "\x1b[31m"
# define G "\x1b[32m"
# define Y "\x1b[33m"
# define B "\x1b[34m"
# define M "\x1b[35m"
# define C "\x1b[36m"
# define W "\x1b[37m"
# define DOUBLE_EXP 2047
# define DOUBLE_MNT_INF 0
# define DOUBLE_MNT_NAN 2251799813685248
# define MAX_DOUBLE 1e+17
# define LONG_DOUBLE_EXP 32767
# define LONG_DOUBLE_MNT_INF 9223372036854775808U
# define LONG_DOUBLE_MNT_NAN 13835058055282163712U
# define MAX_LONG_DOUBLE 1e+20

struct						s_parts_d
{
	unsigned long int		mantissa:52;
	unsigned long int		exponenta:11;
	unsigned long int		sign:1;
};

typedef union				u_num_flt_d
{
	double					num;
	struct s_parts_d		parts;
}							t_num_flt_d;

struct						s_parts_ld
{
	unsigned long int		mantissa:64;
	unsigned long int		exponenta:15;
	unsigned long int		sign:1;
};

typedef union				u_num_flt_ld
{
	long double				num;
	struct s_parts_ld		parts;
}							t_num_flt_ld;

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
	char					type;
	t_num_int				num_int;
	t_num_flt_d				num_flt_d;
	t_num_flt_ld			num_flt_ld;
	unsigned int			base:5;
	char					sign:2;
	unsigned int			is_uns:1;
	unsigned int			is_upcase:1;
	char					*view;
	unsigned int			view_size:2;
	int						num_bytes;
	int						i;
	int						j;
	int						null_count;
}							t_specifier;

size_t						ft_pow(size_t num, size_t n);
void						ft_putadr(va_list arg, t_specifier *specifier);
void						ft_putstr(va_list arg, t_specifier *specifier);
void						ft_putdec(va_list arg, t_specifier *specifier);
void						ft_putoct(va_list arg, t_specifier *specifier);
void						ft_putuns(va_list arg, t_specifier *specifier);
void						ft_puthex(va_list arg, t_specifier *specifier);
void						ft_putbin(va_list arg, t_specifier *specifier);
void						ft_putflt(va_list arg, t_specifier *specifier);
void						ft_putflt_long(va_list arg, t_specifier *specifier,
		size_t *ipart, long double *dpart);
void						ft_putchar(va_list arg, t_specifier *specifier);
char						is_special_cases(t_specifier *specifier,
		size_t mnt, unsigned int exp, unsigned int exponenta);
char						*rounding_ipart(t_specifier *specifier,
		size_t ipart, long double dpart, char *buffer);
char						*rounding_dpart(t_specifier *specifier,
		long double dpart, char *buffer);
char						*determine_size_num(va_list arg,
		t_specifier *specifier, char *buffer);
void						dec_no_minus(t_specifier *specifier,
		char *ptr, int *i);
void						dec_no_minus_dot(t_specifier *specifier,
		char *ptr, int *i);
void						dec_no_minus_null(t_specifier *specifier,
		char *ptr, int *i);
void						dec_no_minus_sign(t_specifier *specifier,
		char *ptr, int *i);
void						dec_no_minus_dot_sign(t_specifier *specifier,
		char *ptr, int *i);
void						dec_no_minus_null_sign(t_specifier *specifier,
		char *ptr, int *i);
void						dec_minus_sign_plus_space_dot(t_specifier \
		*specifier, int *i);
void						print_no_dec_minus(t_specifier *specifier,
		char *ptr, int *i);
void						print_no_dec_no_minus(t_specifier *specifier,
		char *ptr, int *i);
void						null_value(t_specifier *specifier,
		char *ptr, int *i);
void						padding(t_specifier *specifier,
		int boundary, char c, int *i);
void						view(t_specifier *specifier, char *ptr);
char						*specifier_size(char *format,
		t_specifier *specifier);
void						ft_puthex_upcase(va_list arg,
		t_specifier *specifier);
char						*specifier_type(char *format,
		t_specifier *specifier, va_list arg);
char						*ft_itoa_base(t_specifier *specifier_parse,
		long int num, char *buffer);
char						*ft_itoa_base_uns(t_specifier *specifier_parse,
		size_t num, char *buffer);
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
