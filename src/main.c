#include <RTv1.h>

/*
** ***************************************************************************
**	TODO Error handler
** ***************************************************************************
*/

typedef enum	e_return_code
{
	rc_ok,
	rc_allocation_fail,
	rc_null_param,
	rc_wrong_param,
	rc_wrong_element_count,
	rc_invalid_option,
	rc_parse_number_fail
}				t_return_code;

/*
** ***************************************************************************
**	TODO Init scene
** ***************************************************************************
*/

typedef struct		s_scene_manager
{
	t_return_code		rc;
	t_scene				*scene;
	int					fd;
	char				*line;
	t_field				field;
	t_field_option		option;
	char				**parts;
	t_object			*object;
	t_light				*light;
	t_pointer_keeper	*light_keeper;
	t_pointer_keeper	*object_keeper;
}					t_scene_manager;

#include <fcntl.h>

void		init_point3d(t_point3d *point)
{
	if (!point)
		return ;
	point->x = 0.0;
	point->y = 0.0;
	point->z = 0.0;
}

void		init_color(t_color *color)
{
	if (!color)
		return ;
	color->color = 0;
}

t_object 	*new_object(void)
{
	t_object	*object;

	if (!(object = (t_object *)memalloc(sizeof(t_object))))
		return (NULL);
	init_point3d(&object->pos);
	init_point3d(&object->direction);
	init_color(&object->color);
	object->radius = 0.0;
	object->specular = 0.0;
	object->type = object_type_none;
	return (object);
}

t_light 	*new_light(void)
{
	t_light		*light;

	if (!(light = (t_light *)memalloc(sizeof(t_light))))
		return (NULL);
	init_point3d(&light->pos);
	light->intensive = 0.0;
	light->type = light_type_none;
	return (light);
}

void		init_camera(t_camera *camera)
{
	if (!camera)
		return ;
	init_point3d(&camera->pos);
	init_point3d(&camera->direction);
}

void				destroy_scene(t_scene *scene)
{
	size_t		i;

	if (!scene)
		return ;
	i = 0;
	while (scene->object && scene->object[i])
		memfree(scene->object[i++]);
	i = 0;
	while (scene->light && scene->light[i])
		memfree(scene->light[i++]);
	memfree(scene);
}

t_scene				*new_scene(void)
{
	t_scene		*scene;

	if (!(scene = (t_scene *)memalloc(sizeof(t_scene))))
		return (NULL);
	init_camera(&scene->camera);
	scene->object = NULL;
	scene->light = NULL;
	return (scene);
}

void				destroy_scene_manager(t_scene_manager *manager)
{
	if (!manager)
		return ;
	close(manager->fd);
	if (manager->object_keeper)
		destroy_tpointer_keeper(&manager->object_keeper);
	if (manager->light_keeper)
		destroy_tpointer_keeper(&manager->light_keeper);
	memfree(manager->line);
	memfree(manager);
}

t_scene_manager 	*new_scene_manager(void)
{
	t_scene_manager		*manager;

	if (!(manager = (t_scene_manager *)memalloc(sizeof(t_scene_manager)))
	|| !(manager->scene = new_scene())
	|| !(manager->light_keeper = new_tpointer_keeper())
	|| !(manager->object_keeper = new_tpointer_keeper()))
	{
		destroy_scene_manager(manager);
		return (NULL);
	}
	manager->line = NULL;
	manager->field = field_none;
	manager->rc = rc_ok;
	manager->parts = NULL;
	manager->object = NULL;
	manager->light = NULL;
	return (manager);
}

/*
** ***************************************************************************
**	TODO Scene parsing utilities
** ***************************************************************************
*/

/*
**	TODO Parse field
*/

t_field 	parse_field(const char *string)
{
	if (string)
	{
		if (ft_strcmp(string, FIELD_OBJECT))
			return (object);
		if (ft_strcmp(string, FIELD_LIGHT))
			return (light);
		if (ft_strcmp(string, FIELD_CAMERA))
			return (camera);
	}
	return (wrong_field);
}

t_field_option	parse_field_option(const char *string)
{
	if (string)
	{
		if (ft_strcmp(string, FIELD_POS))
			return (pos);
		if (ft_strcmp(string, FIELD_DIRECTION))
			return (direction);
		if (ft_strcmp(string, FIELD_INTENSIVE))
			return (intensive);
		if (ft_strcmp(string, FIELD_RADIUS))
			return (radius);
		if (ft_strcmp(string, FIELD_SPECULAR))
			return (specular);
		if (ft_strcmp(string, FIELD_COLOR))
			return (color);
		if (ft_strcmp(string, FIELD_TYPE))
			return (type);
	}
	return (wrong_option_field);
}

/*
**	TODO Parse option
*/

t_return_code 	parse_color(t_scene_manager *manager)
{
	if (!manager)
		return (rc_null_param);
	if (get_string_array_size(manager->parts) != 4)
		return ((manager->rc = rc_wrong_element_count));
	manager->object->color.r = ft_atoll_base(manager->parts[1], 10);
	manager->object->color.g = ft_atoll_base(manager->parts[2], 10);
	manager->object->color.b = ft_atoll_base(manager->parts[3], 10);
	return ((manager->rc = rc_ok));
}

t_return_code 	set_point3d(t_scene_manager *manager, t_point3d *point)
{
	if (!manager || !point)
		return (rc_null_param);
	if (isnan((point->x = ft_atod_ex(manager->parts[1])))
	|| isnan((point->y = ft_atod_ex(manager->parts[2])))
	|| isnan((point->z = ft_atod_ex(manager->parts[3]))))
		return ((manager->rc = rc_parse_number_fail));
	return ((manager->rc = rc_ok));
}

t_return_code 	parse_point3d(t_scene_manager *manager)
{
	if (!manager)
		return (rc_null_param);
	if (get_string_array_size(manager->parts) != 4)
		return ((manager->rc = rc_wrong_element_count));
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
	return (rc_ok);
}

t_return_code 	parse_double(t_scene_manager *manager)
{
	if (!manager)
		return (rc_null_param);
	if (get_string_array_size(manager->parts) != 2)
		return ((manager->rc = rc_wrong_element_count));
	if (manager->field == object)
	{
		if (manager->option == specular
		&& isnan((manager->object->specular = ft_atod_ex(manager->parts[1]))))
			return ((manager->rc = rc_parse_number_fail));
		if (manager->option == radius
		&& isnan(manager->object->radius = ft_atod_ex(manager->parts[1])))
			return ((manager->rc = rc_parse_number_fail));
	}
	if (manager->field == light && manager->option == intensive
	&& isnan(manager->light->intensive = ft_atod_ex(manager->parts[1])))
		return ((manager->rc = rc_parse_number_fail));
	return ((manager->rc = rc_ok));
}

t_return_code 	parse_object_type(t_scene_manager *manager)
{
	if (!manager)
		return (rc_null_param);
	if (ft_strcmp(manager->parts[1], OBJECT_TYPE_CYLINDER))
		return ((manager->rc = rc_invalid_option));
	if (ft_strcmp(manager->parts[1], OBJECT_TYPE_CONE))
		return ((manager->rc = rc_invalid_option));
	if (ft_strcmp(manager->parts[1], OBJECT_TYPE_PLANE))
		return ((manager->rc = rc_invalid_option));
	if (ft_strcmp(manager->parts[1], OBJECT_TYPE_SPHERE))
		return ((manager->rc = rc_invalid_option));
	return (((manager->rc = rc_ok)));
}

t_return_code 	parse_light_type(t_scene_manager *manager)
{
	if (!manager)
		return (rc_null_param);
	if (ft_strcmp(manager->parts[1], LIGHT_TYPE_AMBIENT))
		return ((manager->rc = rc_invalid_option));
	if (ft_strcmp(manager->parts[1], LIGHT_TYPE_DIRECTIONAL))
		return ((manager->rc = rc_invalid_option));
	if (ft_strcmp(manager->parts[1], LIGHT_TYPE_POINT))
		return ((manager->rc = rc_invalid_option));
	return ((manager->rc = rc_ok));
}

t_return_code 	parse_type(t_scene_manager *manager)
{
	if (manager)
	{
		if (get_string_array_size(manager->parts) != 2)
			return ((manager->rc = rc_wrong_element_count));
		if (manager->field == object)
			return (parse_object_type(manager));
		if (manager->field == light)
			return (parse_light_type(manager));
	}
	return (manager ? rc_ok : rc_null_param);
}

t_return_code 	parse_option(t_scene_manager *manager)
{
	if (!manager)
		return (rc_null_param);
	if (manager->option == type)
		return ((manager->rc = parse_type(manager)));
	if (manager->option == pos || manager->option == direction)
		return ((manager->rc = parse_point3d(manager)));
	if (manager->option == intensive || manager->option == specular
	|| manager->option == radius)
		return ((manager->rc = parse_double(manager)));
	if (manager->option == color)
		return ((manager->rc = parse_color(manager)));
	return (rc_ok);
}

/*
**	TODO Set current parse element
*/

t_return_code	set_current_parse_object(t_scene_manager *manager)
{
	if (!manager)
		return (rc_null_param);
	if (manager->object)
	{
		if (!manager->object_keeper->add(manager->object_keeper,
				manager->object) || !(manager->object = new_object()))
			return (rc_allocation_fail);
	}
	else if (!(manager->object = new_object()))
		return (rc_allocation_fail);
	return (rc_ok);
}

t_return_code	set_current_parse_light(t_scene_manager *manager)
{
	if (!manager)
		return (rc_null_param);
	if (manager->light)
	{
		if (!manager->light_keeper->add(manager->light_keeper,
				manager->light) || !(manager->light = new_light()))
			return (rc_allocation_fail);
	}
	else if (!(manager->light = new_light()))
		return (rc_allocation_fail);
	return (rc_ok);
}

t_return_code 	set_current_parse_element(t_scene_manager *manager)
{
	if (!manager)
		return (rc_null_param);
	if (manager->field == object)
		return (set_current_parse_object(manager));
	if (manager->field == light)
		return (set_current_parse_light(manager));
	return (rc_ok);
}

/*
** ***************************************************************************
**	TODO Scene parsing core
** ***************************************************************************
*/

t_return_code	parse_scene(t_scene_manager *manager)
{
	if (!manager || manager->field == wrong_field)
		return (manager ? (manager->rc = rc_wrong_param) : rc_null_param);
	while (manager->rc == rc_ok && manager->option != wrong_option_field
	&& get_next_line(manager->fd, &manager->line) > 0)
	{
		(manager->parts = ft_strsplit(manager->line, ' ')) ?
		(manager->rc = rc_allocation_fail) : FALSE;
		manager->option = parse_field_option(manager->parts[0]);
		set_current_parse_element(manager);
		parse_option(manager);
		ft_strdel(&manager->line);
	}
	return (manager->rc);
}

t_scene		*init_scene(const char *path)
{
	t_scene_manager		*manager;
	t_scene				*scene;

	manager = new_scene_manager();
	manager ? manager->fd = open(path, O_RDONLY) : FALSE;
	manager ? (scene = manager->scene) : FALSE;
	while (manager && manager->fd != ERROR && manager->field != wrong_field
	&& manager->rc == rc_ok && get_next_line(manager->fd, &manager->line) > 0)
	{
		manager->field = parse_field(manager->line);
		ft_strdel(&manager->line);
		manager->rc = parse_scene(manager);
	}
	if (manager)
	{
		scene->light = (t_light **)manager->light_keeper->convert
				(manager->light_keeper);
		scene->object = (t_object **)manager->object_keeper->convert
				(manager->object_keeper);
	}
	manager ? destroy_scene_manager(manager) : FALSE;
	return (scene);
}

/*
** ***************************************************************************
**	TODO Main
** ***************************************************************************
*/

#include <stdio.h>

int		main(int ac, char **av)
{
	t_scene		*scene = init_scene(av[1]);
	printf("%F\n", scene->object[3]->radius);
	destroy_scene(scene);
	return (0);
}