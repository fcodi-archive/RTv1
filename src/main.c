#include <RTv1.h>

/*
** ***************************************************************************
**	TODO Init scene
** ***************************************************************************
*/

typedef struct		s_scene_manager
{
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
	_Bool				checklist[FIELD_OPTION_COUNT];
	_Bool				was_camera;
}						t_scene_manager;

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

	if (!(object = (t_object *)malloc(sizeof(t_object))))
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

	if (!(light = (t_light *)malloc(sizeof(t_light))))
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
	if (scene->object)
	{
		while (scene->object[i])
			free(scene->object[i++]);
		free(scene->object);
	}
	i = 0;
	if (scene->light)
	{
		while (scene->light[i])
			free(scene->light[i++]);
		free(scene->light);
	}
	free(scene);
}

t_scene				*new_scene(void)
{
	t_scene		*scene;

	if (!(scene = (t_scene *)ft_memalloc(sizeof(t_scene))))
		return (NULL);
/*	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		return (NULL);
	init_camera(&scene->camera);
	scene->object = NULL;
	scene->light = NULL;*/
	return (scene);
}

void				destroy_scene_manager(t_scene_manager *manager,
		const _Bool with_scene)
{
	if (!manager)
		return ;
	manager->fd == ERROR ? TRUE : close(manager->fd);
	if (manager->object_keeper && manager->light_keeper)
	{
		manager->scene->object = (t_object **)manager->object_keeper->convert
				(manager->object_keeper);
		manager->scene->light = (t_light **)manager->light_keeper->convert
				(manager->light_keeper);
	}
	if (with_scene || (!manager->scene->object || !manager->scene->light))
	{
		destroy_scene(manager->scene);
		manager->scene = NULL;
	}
	manager->object ? free(manager->object) : FALSE;
	manager->light ? free(manager->light) : FALSE;
	free(manager);
}

void				init_option_checklist(t_scene_manager *manager)
{
	int		i;

	if (!manager)
		return ;
	i = 0;
	while (i < FIELD_OPTION_COUNT)
		manager->checklist[i++] = FALSE;
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
	init_option_checklist(manager);
	manager->line = NULL;
	manager->field = field_none;
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
		if (!*string)
			return (separator);
		if (!ft_strcmp(string, FIELD_OBJECT))
			return (object);
		if (!ft_strcmp(string, FIELD_LIGHT))
			return (light);
		if (!ft_strcmp(string, FIELD_CAMERA))
			return (camera);
	}
	return (wrong_field);
}

t_field_option	parse_field_option(const char *string)
{
	if (string)
	{
		if (!*string)
			return (option_separator);
		if (!ft_strcmp(string, FIELD_POS))
			return (pos);
		if (!ft_strcmp(string, FIELD_DIRECTION))
			return (direction);
		if (!ft_strcmp(string, FIELD_INTENSIVE))
			return (intensive);
		if (!ft_strcmp(string, FIELD_RADIUS))
			return (radius);
		if (!ft_strcmp(string, FIELD_SPECULAR))
			return (specular);
		if (!ft_strcmp(string, FIELD_COLOR))
			return (color);
		if (!ft_strcmp(string, FIELD_TYPE))
			return (type);
	}
	return (wrong_option_field);
}

/*
**	TODO Parse option
*/

_Bool	is_valid_color_integer(intmax_t integer)
{
	const uint8_t	byte = (uint8_t)integer;

	return (byte == integer ? TRUE : FALSE);
}

#define COLOR_COUNT 3

_Bool	parse_current_color(t_color *color, char **numbers)
{
	intmax_t	integer[COLOR_COUNT];
	int			i;

	if (!color || !numbers || !*numbers)
		return (FALSE);
	i = -1;
	while (++i < COLOR_COUNT)
		if (!is_valid_color_integer(
				(integer[i] = ft_atoll_base(numbers[i], 10))))
			return (FALSE);
	color->r = integer[0];
	color->g = integer[1];
	color->b = integer[2];
	return (TRUE);
}

_Bool	parse_color(t_scene_manager *manager)
{
	char	**integers;
	_Bool	result;

	if (!manager)
		return (FALSE);
	if (get_string_array_size(manager->parts) != 4
	|| !(integers = parse_integers(manager->line)))
		return (FALSE);
	if ((result = get_string_array_size(integers) == 3 ? TRUE : FALSE))
		result = parse_current_color(&manager->object->color, integers);
	ft_astr_del(integers);
	return (result);
}

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

_Bool	parse_double(t_scene_manager *manager)
{
	if (!manager)
		return (FALSE);
	if (get_string_array_size(manager->parts) != 2)
		return (FALSE);
	if (manager->field == object)
	{
		if (manager->option == specular
		&& isnan((manager->object->specular = ft_atod_ex(manager->parts[1]))))
			return (FALSE);
		if (manager->option == radius
		&& isnan(manager->object->radius = ft_atod_ex(manager->parts[1]))
		|| manager->object->radius < 0)
			return (FALSE);
	}
	if (manager->field == light && manager->option == intensive
	&& isnan(manager->light->intensive = ft_atod_ex(manager->parts[1])))
		return (FALSE);
	return (TRUE);
}

_Bool	parse_object_type(t_scene_manager *manager)
{
	if (!manager)
		return (FALSE);
	if (!ft_strcmp(manager->parts[1], OBJECT_TYPE_CYLINDER))
		manager->object->type = cylinder;
	else if (!ft_strcmp(manager->parts[1], OBJECT_TYPE_CONE))
		manager->object->type = cone;
	else if (!ft_strcmp(manager->parts[1], OBJECT_TYPE_PLANE))
		manager->object->type = plane;
	else if (!ft_strcmp(manager->parts[1], OBJECT_TYPE_SPHERE))
		manager->object->type = sphere;
	else
		return (FALSE);
	return (TRUE);
}

_Bool	parse_light_type(t_scene_manager *manager)
{
	if (!manager)
		return (FALSE);
	if (!ft_strcmp(manager->parts[1], LIGHT_TYPE_AMBIENT))
		manager->light->type = ambient;
	else if (!ft_strcmp(manager->parts[1], LIGHT_TYPE_DIRECTIONAL))
		manager->light->type = directional;
	else if (!ft_strcmp(manager->parts[1], LIGHT_TYPE_POINT))
		manager->light->type = point;
	else
		return (FALSE);
	return (TRUE);
}

_Bool	parse_type(t_scene_manager *manager)
{
	if (manager)
	{
		if (get_string_array_size(manager->parts) != 2)
			return (FALSE);
		if (manager->field == object)
			return (parse_object_type(manager));
		if (manager->field == light)
			return (parse_light_type(manager));
	}
	return (FALSE);
}

_Bool	parse_option(t_scene_manager *manager)
{
	if (!manager || manager->checklist[manager->option])
		return (FALSE);
	if (manager->option == option_separator)
		return (TRUE);
	if (manager->option == type)
		return ((manager->checklist[manager->option] = parse_type(manager)));
	if (manager->option == pos || manager->option == direction)
		return ((manager->checklist[manager->option] = parse_point3d(manager)));
	if (manager->option == intensive || manager->option == specular
	|| manager->option == radius)
		return ((manager->checklist[manager->option] = parse_double(manager)));
	if (manager->option == color)
		return ((manager->checklist[manager->option] = parse_color(manager)));
	return (FALSE);
}

/*
**	TODO Set current parse element
*/

_Bool	is_valid_object_checklist(t_scene_manager *manager)
{
	if (manager && manager->checklist[type] && manager->checklist[color]
	&& manager->checklist[specular] && manager->checklist[pos]
	&& manager->checklist[radius] && manager->checklist[direction])
		return (TRUE);
	return (FALSE);
}

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

_Bool	is_valid_light_checklist(t_scene_manager *manager)
{
	if (manager && manager->checklist[type] && manager->checklist[intensive]
	&& manager->checklist[pos])
		return (TRUE);
	return (FALSE);
}

_Bool	set_current_parse_light(t_scene_manager *manager, const _Bool add_new)
{
	if (!manager)
		return (FALSE);
	if (manager->light)
	{
		if (!manager->light_keeper->add(manager->light_keeper, manager->light))
				return (NULL);
		manager->light = NULL;
		if ((add_new && !(manager->light = new_light())))
			return (FALSE);
	}
	else if (add_new && !(manager->light = new_light()))
		return (FALSE);
	return (TRUE);
}

_Bool	is_valid_camera_checklist(t_scene_manager *manager)
{
	if (manager && manager->checklist[pos] && manager->checklist[direction])
		return (TRUE);
	return (FALSE);
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

/*
** ***************************************************************************
**	TODO Scene parsing core
** ***************************************************************************
*/

_Bool	is_valid_checklist(t_scene_manager *manager)
{
	_Bool	result;

	result = FALSE;
	if (!manager)
		return (result);
	if (manager->field == camera)
		result = is_valid_camera_checklist(manager);
	if (manager->field == object)
		result = is_valid_object_checklist(manager);
	if (manager->field == light)
		result = is_valid_light_checklist(manager);
	init_option_checklist(manager);
	return (result);
}

_Bool	parse_scene(t_scene_manager *manager)
{
	_Bool	result;

	if (!manager)
		return (FALSE);
	result = TRUE;
	init_option_checklist(manager);
	while (result && get_next_line(manager->fd, &manager->line) > 0)
	{
		if (!(manager->parts = ft_strsplit(manager->line, ' ')))
			result = FALSE;
		manager->option = *manager->line ? parse_field_option(*manager->parts)
				: option_separator;
		if (!result || manager->option == wrong_option_field
		|| !parse_option(manager))
			result = FALSE;
		manager->parts ? ft_astr_del(manager->parts) : FALSE;
		ft_strdel(&manager->line);
		if (manager->option == option_separator)
			break ;
	}
	result = is_valid_checklist(manager);
	return (result);
}

t_scene		*init_scene(const char *path)
{
	t_scene_manager		*manager;
	t_scene				*scene;
	int					result;

	if (!path || !(manager = new_scene_manager(path)))
		return (NULL);
	while ((result = get_next_line(manager->fd, &manager->line)) > 0)
	{
		manager->field = parse_field(manager->line);
		ft_strdel(&manager->line);
		if ((result = manager->field == wrong_field ? ERROR : result) == ERROR
		|| ((result = manager->was_camera && manager->field == camera ?
				ERROR :	result)	== ERROR)
		|| (manager->field == separator)
		|| !(set_current_parse_element(manager, TRUE))
		|| (result = parse_scene(manager) ? 0 : ERROR) == ERROR)
			break ;
		manager->field == camera
		? (manager->was_camera = TRUE) : FALSE;
	}
	result = manager->was_camera ? result : ERROR;
	!result ? result = !set_current_parse_element(manager, FALSE) : FALSE;
	scene = !result ? (manager->scene) : NULL;
	destroy_scene_manager(manager, result == 0 ? FALSE : TRUE);
	return (scene);
}

/*
** ***************************************************************************
**	TODO Main
** ***************************************************************************
*/

#include <stdio.h>

_Bool	test_atof(float (*atof)(const char *string))
{
	float	number;

	if (!atof)
		return (FALSE);
	if (!isnan((number = atof(NULL))))
		return (FALSE);
	if (!isnan((number = atof(""))))
		return (FALSE);
	if (!isnan((number = atof(".123"))))
		return (FALSE);
	if (isnan((number = atof("-0"))) && (number != -0.0f || number != 0.0f))
		return (FALSE);
	if (isnan((number = atof("-0.0123"))) && number != -0.123f)
		return (FALSE);
	if (isnan((number = atof("-0123"))) && number != -123.0f)
		return (FALSE);
	return (TRUE);
}

int		main(int ac, char **av)
{
	t_scene		*scene = init_scene(av[1]);
	if (scene && scene->object && scene->object[3])
	{
		for (int i = 0; scene->object[i]; i++)
			printf("%F %F %F\n",
			   scene->object[i]->direction.x,
			   scene->object[i]->direction.y,
			   scene->object[i]->direction.z);
		destroy_scene(scene);
	}
	return (0);
}