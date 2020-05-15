/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 08:58:08 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 08:58:09 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

t_object	*new_object(void)
{
	t_object	*object;

	if (!(object = (t_object *)ft_memalloc(sizeof(t_object))))
		return (NULL);
	init_point3d(&object->pos);
	init_point3d(&object->direction);
	init_color(&object->color);
	object->type = object_type_none;
	return (object);
}
