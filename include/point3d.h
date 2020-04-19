#ifndef FT_POINT3D_H
# define FT_POINT3D_H

typedef struct			s_point3d
{
	double 				x;
	double 				y;
	double				z;
}						t_point3d;

void	init_point3d(t_point3d *point);

#endif
