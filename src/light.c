#include <RTv1.h>

t_light 	*new_light(void)
{
	t_light		*light;

	if (!(light = (t_light *)malloc(sizeof(t_light))))
		return (NULL);
	init_point3d(&light->pos);
	light->intensive = 0.0;
	light->type = light_type_none;
	return (light);
}