#include <color.h>

void		init_color(t_color *color)
{
	if (!color)
		return ;
	color->color = 0;
}

_Bool	is_valid_color_byte(intmax_t integer)
{
	const uint8_t	byte = (uint8_t)integer;

	return (byte == integer ? TRUE : FALSE);
}