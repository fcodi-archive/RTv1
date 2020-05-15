/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 09:50:51 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 20:30:36 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <fcntl.h>
# include "libft.h"
# include "color.h"
# include "point3d.h"
# include "ft_sdl.h"
# include "ft_vector.h"
# include "structs.h"
# include <math.h>

# define PROJECT_NAME "RTv1"

# define COLOR_COUNT 3
# define FIELD_CAMERA "camera:"
# define FIELD_LIGHT "light:"
# define FIELD_OBJECT "object:"
# define FIELD_OPTION "\t"
# define FIELD_SEPARATOR ""
# define FIELD_TYPE "\ttype:"
# define FIELD_DIRECTION "\tdirection:"
# define FIELD_POS "\tpos:"
# define FIELD_INTENSIVE "\tintensive:"
# define FIELD_SPECULAR "\tspecular:"
# define FIELD_RADIUS "\tradius:"
# define FIELD_COLOR "\tcolor:"
# define FIELD_NORM "\tnorm:"
# define FIELD_OPTION_SEPARATOR FIELD_SEPARATOR
# define FIELD_TYPE_COUNT 6
# define FIELD_OPTION_TYPE_COUNT 9

# define FOV						M_PI / 3.0
# define MIN						0.0001f
# define MAX						10000000.0

# define LIGHT_TYPE_AMBIENT "ambient"
# define LIGHT_TYPE_DIRECTIONAL "directional"
# define LIGHT_TYPE_POINT "point"
# define LIGHT_TYPE_COUNT 3
# define LIGHT_OPTION_COUNT 3

# define OBJECT_TYPE_COUNT 4
# define OBJECT_TYPE_CONE "cone"
# define OBJECT_TYPE_CYLINDER "cylinder"
# define OBJECT_TYPE_PLANE "plane"
# define OBJECT_TYPE_SPHERE "sphere"

t_scene			*init_scene(const char *path);
_Bool			parse_scene(t_scene_manager *manager);

t_scene			*new_scene(void);
void			destroy_scene(t_scene *scene);

t_scene_manager *new_scene_manager(const char *path);
t_scene			*destroy_scene_manager(t_scene_manager *manager,
				_Bool with_scene);

void			init_checklist(t_scene_manager *manager);
_Bool			is_valid_checklist(t_scene_manager *manager);

t_light			*new_light(void);
_Bool			parse_light_type(t_scene_manager *manager);
_Bool			set_current_parse_light(t_scene_manager *manager,
				const _Bool add_new);
_Bool			is_valid_light_checklist(t_scene_manager *manager);

t_object		*new_object(void);
_Bool			parse_object_type(t_scene_manager *manager);
_Bool			set_current_parse_object(t_scene_manager *manager,
				const _Bool add_new);
_Bool			is_valid_object_checklist(t_scene_manager *manager);

void			init_camera(t_camera *camera);
_Bool			is_valid_camera_checklist(t_scene_manager *manager);

_Bool			parse_color(t_scene_manager *manager);
_Bool			parse_point3d(t_scene_manager *manager);
_Bool			parse_double(t_scene_manager *manager);
_Bool			parse_type(t_scene_manager *manager);
_Bool			parse_option(t_scene_manager *manager);
t_field			parse_field(const char *string);
t_field_option	parse_field_option(const char *string);

_Bool			set_current_parse_element(t_scene_manager *manager,
						const _Bool add_new);

t_point3d		cone_normal(t_object *obj, t_point3d point);
t_point3d		cylinder_normal(t_object *obj, t_point3d point);
t_point3d		sphere_normal(t_object *obj, t_point3d point);
t_point3d		plane_normal(t_object *obj, t_point3d point);
t_point3d		get_normal(t_object *obj, t_point3d point);
void			closest_object(t_scene *scene);
t_root			hit_cone(t_point3d dir, t_point3d campos, t_object *cone);
t_root			hit_cylinder(t_point3d dir, t_point3d campos,
				t_object *cylinder);
t_root			hit_sphere(t_point3d dir, t_point3d campos, t_object *sphere);
t_root			hit_plane(t_point3d dir, t_point3d campos, t_object *plane);
t_root			hit_obj(t_point3d dir, t_point3d campos, t_object *obj);
int				ray_trace(t_scene *scene);
void			render(t_scene *scene);
double			compute_light(t_point3d view, t_scene *scene);
void			define_screen(t_img *img, t_camera *camera);
t_point3d		find_direction(t_camera *camera, int x, int y, t_img *img);
t_point3d		rotate(t_point3d axis, t_point3d vector, double angle);
int				color_parse(t_scene *scene);
int				set_color_rgb(int red, int green, int blue);

#endif
