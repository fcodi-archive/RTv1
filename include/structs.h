/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owl <owl@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 05:13:08 by bbear             #+#    #+#             */
/*   Updated: 2020/05/15 05:14:16 by owl              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct			s_camera
{
	t_point3d	pos;
	t_point3d	direction;
	t_point3d	norm;
}						t_camera;

typedef enum			e_light_type
{
	ambient,
	directional,
	point,
	light_type_none,
	light_type_wrong = -1
}						t_light_type;

typedef struct			s_light
{
	t_light_type	type;
	double			intensive;
	t_point3d		pos;
}						t_light;

typedef enum			e_object_type
{
	cone,
	cylinder,
	plane,
	sphere,
	object_type_none,
	object_type_wrong = -1
}						t_object_type;

typedef struct			s_object
{
	t_object_type	type;
	t_color			color;
	double			specular;
	t_point3d		pos;
	double			radius;
	t_point3d		direction;
}						t_object;

typedef struct			s_math
{
	t_point3d			dir;
	t_point3d			point;
	t_point3d			normal;
	t_object			*closest_obj;
	t_object			*closest_obj_2;
	double				closest_t;
	double				closest_t_2;
}						t_math;

typedef struct			s_root
{
	double				a;
	double				b;
}						t_root;

typedef struct			s_img
{
	t_point3d			up;
	t_point3d			down;
	t_point3d			left;
	t_point3d			right;
	t_point3d			border_x;
	t_point3d			border_y;
}						t_img;

typedef struct			s_scene
{
	t_camera			camera;
	t_light				**light;
	t_object			**object;
	t_sdl				*sdl;
	t_math				*math;
}						t_scene;

typedef enum	e_field
{
	camera,
	light,
	object,
	option,
	separator,
	field_none,
	wrong_field
}				t_field;

typedef enum	e_field_option
{
	pos,
	direction,
	type,
	intensive,
	color,
	specular,
	radius,
	norm,
	option_separator,
	field_option_none,
	wrong_option_field
}				t_field_option;

# define FIELD_OPTION_COUNT wrong_option_field

typedef struct			s_scene_manager
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

#endif
