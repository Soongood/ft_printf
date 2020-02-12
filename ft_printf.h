#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define NOTHING 0
# define ERROR 1
# define OK 0

# define MINUS 1
# define PLUS 2
# define SPACE 4
# define SHARP 8
# define ZERO 16

#include "libft.h"
#include <ieee754.h>
#include <stdarg.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct			s_str
{
	double				num_d;
	char				*ptr;
	intmax_t			num;
	uintmax_t			num_u;
	uint16_t			flags;
	char				tmp;
	char				base;
	int					prec_f;
	int					width;
	int					precision;
	char				letter;
	char				specifier[2];
	char				type[1];
	char				str[5000];
}                       t_str;

int     ft_printf(const char *format, ...);
int		is_specifier(char chunk);
int		is_type(char chunk);
int		base_num_u(t_str *line, uintmax_t number);
int		base_num(t_str *line, intmax_t number);
int     f_type(t_str *line);
int     c_type(t_str *line, int letter);
int		s_type(t_str *line, char *string);
int		p_type(t_str *line, uintmax_t pointer);
int		u_type(t_str *line, char u_base);
int		i_type(t_str *line, char base);
int		handler(t_str *line, va_list list);
char	base(t_str *line);
char	u_base(t_str *line);
void	is_flags(t_str *line, const char **chunk);
void    sharp(t_str *line);
void	loop_w(t_str *line, char num);
void	loop_p(t_str *line, char *u_base);
void	round_f(t_str *line);
void    parsing(const char **chunk, t_str *line, va_list list);
void	get_num(t_str *line, va_list list);
void	get_num_u(t_str *line, va_list list);

#endif