#include <RTv1.h>
#include <stdio.h>

int		main(int ac, char **av)
{
	t_scene		*scene = init_scene(av[1]);
	if (scene && scene->object && scene->object[3])
	{
		for (int i = 0; scene->object[i]; i++)
			printf("%F %F %F\n",
			   scene->object[i]->direction.x,
			   scene->object[i]->direction.y,
			   scene->object[i]->direction.z);
		destroy_scene(scene);
	}
	return (0);
}