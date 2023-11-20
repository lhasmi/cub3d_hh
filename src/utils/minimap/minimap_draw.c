#include "MLX42/MLX42.h"
#include "scene.h"
#include "vec.h"
#include "draw.h"
#include "player.h"

#define MAP_SCALE 10

static uint32_t	minimap_get_tile_color(char tile)
{
	if (tile == '1')
		return (0xffffffff);
	return (0x222222ff);
}

static void	minimap_draw_tile(t_scene *scene, t_vec position)
{
	char		tile;
	uint32_t	color;
	t_vec		origin;
	t_vec		player;
	t_vec		middle;

	tile = scene_get(scene, position);
	color = minimap_get_tile_color(tile);
	middle = vec_mult_scalar(scene->map_size, MAP_SCALE / 2);
	player = vec_correct(vec_mult_scalar(scene->player.position, MAP_SCALE), 1.0);
	position = vec_mult_scalar(position, MAP_SCALE);
	origin = vec_add(position, vec_sub(middle, player));
	draw_square(scene->minimap, origin, MAP_SCALE, color);
}

void	minimap_draw(t_scene *scene)
{
	uint32_t	ix;
	uint32_t	iy;
	t_vec		position;
	t_vec		middle;

	ix = 0;
	middle = vec_mult_scalar(scene->map_size, MAP_SCALE / 2);
	draw_square(scene->minimap, vec_create(0, 0, 0), 10 * MAP_SCALE, 0x000000ff);
	while (ix < scene->map_size.y)
	{
		iy = 0;
		while (iy < scene->map_size.y)
		{
			// position = vec_sub(vec_create(ix, iy, 0), scene->player.position);
			position = vec_create(ix, iy, 0);
			minimap_draw_tile(scene, position);
			iy++;
		}
		ix++;
	}
	// position = vec_sub(vec_create(5, 7, 0), scene->player.position);
	// minimap_draw_tile(scene, position);

	draw_square(scene->minimap, vec_sub(middle, vec_create(3, 3, 0)), 7, 0xff7800ff);
	// draw_square(scene->minimap, vec_sub(vec_mult_scalar(scene->player.position, MAP_SCALE), vec_create(3, 3, 0)), 7, 0xff7800ff);
}

void	minimap_draw_ray(t_scene *scene, t_vec vec)
{
	t_vec	start;
	t_vec	end;

	start = vec_mult_scalar(scene->map_size, MAP_SCALE / 2);
	// start = vec_mult_scalar(scene->player.position, MAP_SCALE);
	end = vec_add(start, vec_mult_scalar(vec, MAP_SCALE));
	draw_line(scene->minimap, start, end, 0xff0000ff);
}