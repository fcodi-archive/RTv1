double		ft_vec_distance(t_vector a, t_vector b)
{
    double	distance;

    distance = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)
                    + (a.z - b.z) * (a.z - b.z));
    return (distance);
}

double		ft_vec_dot(t_vector a, t_vector b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

void	ft_vec_init(t_vector a)
{
    a.x = 0;
    a.y = 0;
    a.z = 0;
}

double		ft_vec_length(t_vector a)
{
    double	len;

    len = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    return (len);
}

double			ft_vec_multiplication(t_vector a, t_vector b, double angle)
{
    double		result;
    double		len_a;
    double		len_b;

    len_a = ft_vec_length(a);
    len_b = ft_vec_length(b);
    result = len_a * len_b * cos(angle);
    return (result);
}

t_vector		ft_vec_multiplication_num(t_vector a, double num)
{
    t_vector	b;

    b.x = a.x * num;
    b.y = a.y * num;
    b.z = a.z * num;
    return (b);
}

t_vector		ft_vec_subtract(t_vector a, t_vector b)
{
    t_vector	c;

    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
    return (c);
}

t_vector		ft_vec_sum(t_vector a, t_vector b)
{
    t_vector	c;

    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    return (c);
}
