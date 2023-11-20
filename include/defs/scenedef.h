#ifndef SCENEDEF_H
# define SCENEDEF_H

# include <MLX42/MLX42.h>
# include "playerdef.h"
# include "vecdef.h"

# define WIDTH 512
# define HEIGHT 512

typedef struct s_scene
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_image_t		*minimap;
	mlx_texture_t	*tex[4];
	t_player		player;
	t_vec			size;
	t_vec			map_size;
	char			*map;
	t_vec			mouse;
}	t_scene;

#endif