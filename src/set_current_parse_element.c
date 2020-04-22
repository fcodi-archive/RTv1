#include <RTv1.h>

_Bool	set_current_parse_object(t_scene_manager *manager, const _Bool add_new)
{
	if (!manager)
		return (FALSE);
	if (manager->object)
	{
		if (!manager->object_keeper->add(manager->object_keeper,
										 manager->object))
			return (FALSE);
		manager->object = NULL;
		if ((add_new && !(manager->object = new_object())))
			return (FALSE);
	}
	else if (add_new && !(manager->object = new_object()))
		return (FALSE);
	return (TRUE);
}

_Bool	set_current_parse_light(t_scene_manager *manager, const _Bool add_new)
{
	if (!manager)
		return (FALSE);
	if (manager->light)
	{
		if (!manager->light_keeper->add(manager->light_keeper, manager->light))
			return (FALSE);
		manager->light = NULL;
		if ((add_new && !(manager->light = new_light())))
			return (FALSE);
	}
	else if (add_new && !(manager->light = new_light()))
		return (FALSE);
	return (TRUE);
}

_Bool	set_current_parse_element(t_scene_manager *manager, const _Bool add_new)
{
	if (!manager)
		return (FALSE);
	if (manager->field == object)
		return (set_current_parse_object(manager, add_new));
	if (manager->field == light)
		return (set_current_parse_light(manager, add_new));
	if (manager->field == camera)
		return (TRUE);
	return (FALSE);
}
