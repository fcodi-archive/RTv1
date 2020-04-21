#ifndef FT_VECTOR_H
# define FT_VECTOR_H

typedef struct  s_vector
{
    double      x;
    double      y;
    double      z;
}               t_vector;

double          ft_vec_distance(t_vector a, t_vector b);
double	    	ft_vec_dot(t_vector a, t_vector b);
void	        ft_vec_init(t_vector a);
double		    ft_vec_length(t_vector a);
double			ft_vec_multiplication(t_vector a, t_vector b, double angle);
t_vector		ft_vec_multiplication_num(t_vector a, double num);
t_vector		ft_vec_subtract(t_vector a, t_vector b);
t_vector		ft_vec_sum(t_vector a, t_vector b);

#endif
