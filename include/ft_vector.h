#ifndef FT_VECTOR_H
# define FT_VECTOR_H

# include <point3d.h>
# include <libft.h>

//typedef struct  s_vector
//{
//    double      x;
//    double      y;
//    double      z;
//}               t_point3d;

double          ft_vec_distance(t_point3d a, t_point3d b);
double	    	ft_vec_dot(t_point3d a, t_point3d b);
void	        ft_vec_init(t_point3d *a);
double		    ft_vec_length(t_point3d a);
double			ft_vec_multiplication(t_point3d a, t_point3d b, double angle);
t_point3d		ft_vec_multiplication_num(t_point3d a, double num);
t_point3d		ft_vec_subtract(t_point3d a, t_point3d b);
t_point3d		ft_vec_sum(t_point3d a, t_point3d b);

#endif
