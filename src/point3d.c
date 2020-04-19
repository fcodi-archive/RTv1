#include <point3d.h>

void		init_point3d(t_point3d *point)
{
	if (!point)
		return ;
	point->x = 0.0;
	point->y = 0.0;
	point->z = 0.0;
}