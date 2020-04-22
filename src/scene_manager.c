#include <RTv1.h>

t_scene     *destroy_scene_manager(t_scene_manager *manager,
		_Bool with_scene)
{
	t_scene     *scene;

	if (!manager)
		return (NULL);
	scene = manager->scene;
	manager->fd == ERROR ? TRUE : close(manager->fd);
	if (manager->object_keeper && manager->light_keeper)
	{
		manager->scene->object = (t_object **)manager->object_keeper->convert
				(manager->object_keeper);
		manager->scene->light = (t_light **)manager->light_keeper->convert
				(manager->light_keeper);
	}
	if (with_scene || !manager->scene->object || !manager->scene->light)
	{
		destroy_scene(manager->scene);
		scene = NULL;
	}
	manager->object ? free(manager->object) : FALSE;
	manager->light ? free(manager->light) : FALSE;
	free(manager);
	return (scene);
}

t_scene_manager 	*new_scene_manager(const char *path)
{
	t_scene_manager		*manager;

	if (!(manager = (t_scene_manager *)malloc(sizeof(t_scene_manager)))
		|| ((manager->fd = open(path, O_RDONLY)) == ERROR)
		|| !(manager->scene = new_scene())
		|| !(manager->light_keeper = new_tpointer_keeper())
		|| !(manager->object_keeper = new_tpointer_keeper()))
	{
		destroy_scene_manager(manager, TRUE);
		return (NULL);
	}
	manager->was_camera = FALSE;
	init_checklist(manager);
	manager->line = NULL;
	manager->field = field_none;
	manager->parts = NULL;
	manager->object = NULL;
	manager->light = NULL;
	return (manager);
}