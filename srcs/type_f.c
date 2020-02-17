#include "../includes/ft_printf.h"

void	ft_abs(t_str *line)
{
	line->num_u = ~line->num + 1;
}

void	round_f(t_str *line)
{
	int		i;
	short	nums[100];

	i = 0;
	ft_bzero(nums, sizeof(nums));
	if (line->precision)
		*line->ptr++ = '.';
	while ((line->num_u = (line->num_u % line->num) * 10) && line->prec_f--)
		nums[i++] = line->num_u / line->num;
	if (line->num_u)
	{
		nums[i] = line->num_u / line->num;
		while (nums[i - 1] >= 9)
			if (nums[i] >= 5)
				nums[i-- - 1] += 1;
		nums[i - 1] += nums[i] >= 5 ? 1 : 0;
	}
	while (line->prec_f-- > 0)
		nums[i++] = 0;
	nums[line->precision] = -1;
	i = 0;
	while (nums[i] >= 0)
	 	*line->ptr++ = '0' + (nums[i++] % 10);
	if (!line->base)
		while (line->width-- > line->precision + line->tmp + 1)
			*line->ptr++ = ' ';
}

int	f_type(t_str *line)
{
	int						width;
	union ieee754_double	pre;

	line->num = (uintmax_t)line->num_d;
	if (line->num < 0)
			ft_abs(line);
	line->prec_f = line->precision == -1 ? 6 : line->precision;
	width = line->width;
	if (line->precision)
		line->width -= line->precision == -1 ? 7 : line->precision + 1;
	line->precision = !line->prec_f ? 0 : -1;
	i_type(line, base(line));
	pre.d = line->num_d;
	line->num = 1;
	line->num <<= 52 - (pre.ieee.exponent - 1023); // 52 - exponenta = 52 - (exp - 1023)
	line->num_u = (uintmax_t)pre.ieee.mantissa0 << 32 | pre.ieee.mantissa1;
	line->precision = line->prec_f;
	if ((line->flags == (line->flags | MINUS)) && (line->flags != (line->flags | SPACE)))
	{
		line->ptr -= width ? width - (line->tmp + line->prec_f + 1) : 0;
		line->base = 0;
	}
	line->width = width;
	round_f(line);
	return (EXIT_SUCCESS);
}
