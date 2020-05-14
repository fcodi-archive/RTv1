/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcodi <fcodi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 09:00:23 by fcodi             #+#    #+#             */
/*   Updated: 2020/05/12 20:31:50 by fcodi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <RTv1.h>

_Bool	parse_option(t_scene_manager *manager)
{
	if (!manager || manager->checklist[manager->option])
		return (FALSE);
	if (manager->option == option_separator)
		return (TRUE);
	if (manager->option == type)
		return ((manager->checklist[manager->option] = parse_type(manager)));
	if (manager->option == pos || manager->option == direction || manager->option == norm)
		return ((manager->checklist[manager->option] = parse_point3d(manager)));
	if (manager->option == intensive || manager->option == specular
		|| manager->option == radius)
		return ((manager->checklist[manager->option] = parse_double(manager)));
	if (manager->option == color)
		return ((manager->checklist[manager->option] = parse_color(manager)));
	return (FALSE);
}
