#ifndef RTV1_H
# define RTV1_H

# include <fcntl.h>
# include <libft.h>
# include <color.h>
# include <point3d.h>
# include <ft_SDL.h>
# include <ft_vector.h>

#define PROJECT_NAME "RTv1"

#define COLOR_COUNT 3
#define FIELD_CAMERA "camera:"
#define FIELD_LIGHT "light:"
#define FIELD_OBJECT "object:"
#define FIELD_OPTION "\t"
#define FIELD_SEPARATOR ""
#define FIELD_TYPE "\ttype:"
#define FIELD_DIRECTION "\tdirection:"
#define FIELD_POS "\tpos:"
#define FIELD_INTENSIVE "\tintensive:"
#define FIELD_SPECULAR "\tspecular:"
#define FIELD_RADIUS "\tradius:"
#define FIELD_COLOR "\tcolor:"
#define FIELD_OPTION_SEPARATOR FIELD_SEPARATOR
#define FIELD_TYPE_COUNT 6
#define FIELD_OPTION_TYPE_COUNT 9


# define FOV						M_PI / 2.0

# define MIN						0.0001f
# define MAX						10000000.0

typedef struct			s_camera
{
	t_point3d	pos;
	t_point3d	direction;
}						t_camera;

typedef enum			e_light_type
{
	ambient,
	directional,
	point,
	light_type_none,
	light_type_wrong = -1
}						t_light_type;

#define LIGHT_TYPE_AMBIENT "ambient"
#define LIGHT_TYPE_DIRECTIONAL "directional"
#define LIGHT_TYPE_POINT "point"
#define LIGHT_TYPE_COUNT 3
#define LIGHT_OPTION_COUNT 3

typedef struct			s_light
{
	t_light_type	type;
	double 			intensive;
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

#define OBJECT_TYPE_COUNT 4
#define OBJECT_TYPE_CONE "cone"
#define OBJECT_TYPE_CYLINDER "cylinder"
#define OBJECT_TYPE_PLANE "plane"
#define OBJECT_TYPE_SPHERE "sphere"

typedef struct			s_object
{
	t_object_type	type;
	t_color			color;
	double			specular;
	t_point3d		pos;
	double 			radius;
	t_point3d		direction;
}						t_object;

typedef enum			s_field
{
	camera,
	light,
	object,
	option,
	separator,
	field_none,
	wrong_field
}						t_field;

#define FIELD_OPTION_COUNT wrong_option_field

typedef enum 			s_field_option
{
	pos,
	direction,
	type,
	intensive,
	color,
	specular,
	radius,
	option_separator,
	field_option_none,
	wrong_option_field
}						t_field_option;

typedef struct				s_math
{
	t_point3d				dir;
	t_point3d				point;
	t_point3d				normal;
	t_object				*closest_obj;
	t_object				*closest_obj_2;
	double					closest_t;
	double					closest_t_2;
}							t_math;

typedef struct				s_root
{
	double					a;
	double					b;
}							t_root;




typedef struct			s_scene
{
	t_camera			camera;
	t_light				**light;
	t_object			**object;
	t_sdl               *sdl;
	t_math              *math;
}						t_scene;

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

t_scene		*init_scene(const char *path);
_Bool		parse_scene(t_scene_manager *manager);

t_scene		*new_scene(void);
void		destroy_scene(t_scene *scene);

t_scene_manager 	*new_scene_manager(const char *path);
t_scene             *destroy_scene_manager(t_scene_manager *manager,
		_Bool with_scene);

void	init_checklist(t_scene_manager *manager);
_Bool	is_valid_checklist(t_scene_manager *manager);

t_light 	*new_light(void);
_Bool	parse_light_type(t_scene_manager *manager);
_Bool	set_current_parse_light(t_scene_manager *manager, const _Bool add_new);
_Bool	is_valid_light_checklist(t_scene_manager *manager);

t_object 	*new_object(void);
_Bool	parse_object_type(t_scene_manager *manager);
_Bool	set_current_parse_object(t_scene_manager *manager, const _Bool add_new);
_Bool	is_valid_object_checklist(t_scene_manager *manager);

void		init_camera(t_camera *camera);
_Bool	is_valid_camera_checklist(t_scene_manager *manager);

_Bool	parse_color(t_scene_manager *manager);
_Bool	parse_point3d(t_scene_manager *manager);
_Bool	parse_double(t_scene_manager *manager);
_Bool	parse_type(t_scene_manager *manager);
_Bool	parse_option(t_scene_manager *manager);
t_field 	parse_field(const char *string);
t_field_option	parse_field_option(const char *string);

_Bool	set_current_parse_element(t_scene_manager *manager, const _Bool
add_new);



t_point3d		cone_normal(t_object *obj, t_point3d point);
t_point3d		cylinder_normal(t_object *obj, t_point3d point);
t_point3d		sphere_normal(t_object *obj, t_point3d point);
t_point3d		plane_normal(t_object *obj, t_point3d point);
t_point3d		get_normal(t_object *obj, t_point3d point);
void			closest_object(t_scene *scene);
t_point3d		calculate_direction(int x, int y, int width, int height);
t_root			hit_cone(t_point3d dir, t_point3d campos, t_object *cone);
t_root			hit_cylinder(t_point3d dir, t_point3d campos, t_object *cylinder);
t_root			hit_sphere(t_point3d dir, t_point3d campos, t_object *sphere);
t_root			hit_plane(t_point3d dir, t_point3d campos, t_object *plane);
t_root			hit_obj(t_point3d dir, t_point3d campos, t_object *obj);
int				ray_trace(t_scene *scene);
void			render(t_scene *scene);
double			compute_light(t_point3d view, t_scene *scene);


#endif
