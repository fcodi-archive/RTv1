#include <RTv1.h>

_Bool	set_point3d(t_scene_manager *manager, t_point3d *point)
{
	char	**doubles;
	_Bool	result;

	result = TRUE;
	if (!manager || !point || get_string_array_size(manager->parts) != 4
		|| !(doubles = parse_floats_ex(manager->line))
		|| get_string_array_size(doubles) != 3)
		return (FALSE);
	if (isnan((point->x = ft_atod_ex(doubles[0])))
		|| isnan((point->y = ft_atod_ex(doubles[1])))
		|| isnan((point->z = ft_atod_ex(doubles[2]))))
		result = FALSE;
	ft_astr_del(doubles);
	return (result);
}

_Bool	parse_point3d(t_scene_manager *manager)
{
	if (!manager)
		return (FALSE);
	if (get_string_array_size(manager->parts) != 4)
		return (FALSE);
	if (manager->field == object)
	{
		if (manager->option == pos)
			return (set_point3d(manager, &manager->object->pos));
		if (manager->option == direction)
			return (set_point3d(manager, &manager->object->direction));
	}
	if (manager->field == light && manager->option == pos)
		return (set_point3d(manager, &manager->light->pos));
	if (manager->field == camera)
	{
		if (manager->option == pos)
			return (set_point3d(manager, &manager->scene->camera.pos));
		if (manager->option == direction)
			return (set_point3d(manager, &manager->scene->camera.direction));
	}
	return (TRUE);
}
