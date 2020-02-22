#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define NOTHING 0
# define BUF_SIZE 1000
# define BUF_LIMIT 999

# define MINUS 1
# define PLUS 2
# define SPACE 4
# define SHARP 8
# define ZERO 16

#include "libft.h"
#include <float.h>
#include <stdarg.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

#ifndef _IEEE754_H

#define _IEEE754_H 1
#include <endian.h>

__BEGIN_DECLS

union ieee754_double
  {
    double d;

    struct
    {
	unsigned int mantissa1:32;
	unsigned int mantissa0:20;
	unsigned int exponent:11;
	unsigned int negative:1;
	} ieee;

};

__END_DECLS

#else
#include <ieee754.h>
#endif

typedef struct			s_str
{
	char				*ptr;
	double				num_d;
	intmax_t			num;
	uintmax_t			num_u;
	int					length;
	int					prec_f;
	int					width;
	int					precision;
	uint16_t			flags;
	char				tmp;
	char				type;
	char				base;
	char				letter;
	char				specifier[2];
	char				str[BUF_SIZE];
}                       t_str;

int		is_type(char chunk);
int     f_type(t_str *line);
int		is_specifier(char chunk);
int		get_res(const char **chunk);
int     c_type(t_str *line, int letter);
int		s_type(t_str *line, char *string);
int		u_type(t_str *line, char u_base);
int		i_type(t_str *line, char base);
int		handler(t_str *line, va_list list);
int     ft_printf(const char *format, ...);
int		p_type(t_str *line, uintmax_t pointer);
int		base_num(t_str *line, intmax_t number);
int		base_num_u(t_str *line, uintmax_t number);
char	base(t_str *line);
char	u_base(t_str *line);
void	ft_abs(t_str *line);
void    sharp(t_str *line);
void	round_f(t_str *line);
void	init_str(t_str *line);
void    print_buf(t_str *line);
void	loop_w(t_str *line, char num);
void	loop_p(t_str *line, char *u_base);
void	get_num(t_str *line, va_list list);
void	get_num_u(t_str *line, va_list list);
void	is_flags(t_str *line, const char **chunk);
void	ptr_mv(t_str *line, char letter);
void    parsing(const char **chunk, t_str *line, va_list list);

#endif
