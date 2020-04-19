#ifndef RTV1_H
# define RTV1_H

# include <SDL.h>
# include <math.h>
# include <libft.h>

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

typedef struct				s_sdl
{
	SDL_Window		*win;
	SDL_Surface		*sur;
	SDL_Event		event;
}							t_sdl;

typedef struct			s_point3d
{
	double 	x;
	double 	y;
	double	z;
}						t_point3d;

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

#define FIELD_OPTION_COUNT 7

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

typedef struct			s_scene
{
	t_camera			camera;
	t_light				**light;
	t_object			**object;
}						t_scene;

#endif
