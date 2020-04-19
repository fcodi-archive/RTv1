#include <RTv1.h>

t_object 	*new_object(void)
{
	t_object	*object;

	if (!(object = (t_object *)ft_memalloc(sizeof(t_object))))
		return (NULL);
	init_point3d(&object->pos);
	init_point3d(&object->direction);
	init_color(&object->color);
	object->type = object_type_none;
	return (object);
}