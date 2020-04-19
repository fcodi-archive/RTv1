#include <RTv1.h>

void		init_camera(t_camera *camera)
{
	if (!camera)
		return ;
	init_point3d(&camera->pos);
	init_point3d(&camera->direction);
}