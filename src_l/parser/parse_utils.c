/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:48:43 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/23 20:57:32 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_cub_file_empty(const char *filepath)
{
	int		fd;
	char	*line;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	if (line == NULL)
	{
		close(fd);
		return (1); // File is empty
	}
	free(line);
	close(fd);
	return (0); // File is not empty
}

bool	is_wspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (true);
	return (false);
}

int	open_file(char *file, t_map *map_i, char *err_message)
{
	int	fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		free_map_exit(map_i, err_message, 1);
	return (fd);
}

bool	is_path_valid(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	// printf("fd: %d\n", fd);// DEBUG
	// printf("\n********\npath: %s\n lenght %zu\n********\n", path, ft_strlen(path));// DEBUG
	if (path == NULL || *path == '\0' || ft_strlen(path) < 5)
		return false;
	char *ext = ft_strrchr(path, '.');
	if (ext == NULL || (ft_strcmp(ext, ".png") != 0 && ft_strcmp(ext, ".xpm") != 0))
		return false;
	if (fd == -1)
		return (false);
	else
	{
		close(fd);
		return (true);
	}
}

//  the is_color_valid() function would check that each of color.red,
	// color.green, and color.blue is between 0 and 255.
bool	is_color_valid(int color)
{
	if (color < 0 || color > 255)
		return (false);
	if (color < 0 || color > 255)
		return (false);
	if (color < 0 || color > 255)
		return (false);
	return (true);
}

bool	is_cub(char *filename)
{
	int	len;

	// • Your program must take as a first argument a scene description file with the .cub extension.
	len = ft_strlen(filename);
	if (len >= 4 && filename[len - 4] == '.' && filename[len - 3] == 'c'
		&& filename[len - 2] == 'u' && filename[len - 1] == 'b')
		return (true);
	else
		return (false);
}

void	free_map_resources(t_map *map)
{
	int	i;

	i = 0;
	while (map->tiles && i < map->rows)
	{
		if (map->tiles[i])
		{
			printf("freeing map->tiles[%d]\n", i);// DEBUG
			free(map->tiles[i]);
			map->tiles[i] = NULL;
		}
		i++;
	}
	if (map->tiles)
	{
		printf("freeing map->tiles\n");// DEBUG
		free(map->tiles);
		map->tiles = NULL;
	}
	if (map->floor_color){
		printf("freeing map->floor_color\n");// DEBUG
		free(map->floor_color);
	}
	if (map->ceiling_color){
		printf("freeing map->ceiling_color\n");// DEBUG
		free(map->ceiling_color);
	}
	if (map->no_texture)
	{
		printf("freeing map->no_texture\n");// DEBUG
		free(map->no_texture);
	}
	if (map->so_texture)
	{
		printf("freeing map->so_texture\n");// DEBUG
		free(map->so_texture);
	}
	if (map->we_texture)
	{
		printf("freeing map->we_texture\n");// DEBUG
		free(map->we_texture);
	}
	if (map->ea_texture)
	{
		printf("freeing map->ea_texture\n");// DEBUG
		free(map->ea_texture);
	}
	if(map)
	{
		printf("freeing map\n");// DEBUG
		free(map);
		map = NULL;
	}
}

void	free_map_exit(t_map *map, char *error_message, int status)
{
	if (status != 0)
	{
		free_map_resources(map);
		ft_error(error_message);
		exit(status);
	}
	else
		printf("%s\n", error_message);//Debug
}

// void	free_map_exit(t_map *map, char *str, int d)
// {
// 	int	i;

// 	i = 0;
// 	while ((*map).tiles && (*map).tiles[i])
// 	{
// 		free((*map).tiles[i]);
// 		i++;
// 	}
// 	if ((*map).tiles)
// 		free((*map).tiles);
// 	if (d == 1)
// 	{
// 		ft_error(str);
// 		exit(1);
// 	}
// 	if (d == 0)
// 		ft_printf("%s\n", str);
// 	return ;
// }

int	rgb_to_hex(int r, int g, int b)
{
	int	alpha;

	alpha = 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | alpha);
}

// void	set_keyhooks(mlx_key_data_t keydata, void *param)
// {
// 	t_img		*img = NULL;
// 	(void)param;

// 	//  The left and right arrow keys of the keyboard must allow you to look left and
// 	// right in the maze.
// 	if (keydata.key == MLX_KEY_LEFT)
// 	{
// 		img->angle -= 0.1;
// 		if (img->angle < 0)
// 			img->angle += 2 * PI;
// 	}
// 	if (keydata.key == MLX_KEY_RIGHT)
// 	{
// 		img->angle += 0.1;
// 		if (img->angle > 2 * PI)
// 			img->angle -= 2 * PI;
// 	}
// 	// ◦ Pressing ESC must close the window and quit the program cleanly.
// 	// ◦ Clicking on the red cross on the window’s frame must close the window and
// 	// quit the program cleanly.
// 	// void mlx_close_hook(mlx_t* mlx, mlx_closefunc func, void* param);
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
// 		mlx_close_window(img->mlx);
// }

// // ◦ The W, A, S, and D keys must allow you to move the point of view through
// // the maze.
// void	set_keyhooks_bis(mlx_key_data_t keydata, void *param)
// {
// 	t_img		*img = NULL;
// 	t_mapreqs	*mapreqs = NULL;

// 	(void)param;
// 	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
// 	{
// 		mapreqs->pos_x += 10 * cos(img->angle);
// 		mapreqs->pos_y += 10 * sin(img->angle);
// 	}
// 	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
// 	{
// 		mapreqs->pos_x -= 10 * cos(img->angle);
// 		mapreqs->pos_y -= 10 * sin(img->angle);
// 	}
// 	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
// 	{
// 		mapreqs->pos_x += 10 * cos(img->angle + PI / 2);
// 		mapreqs->pos_y += 10 * sin(img->angle + PI / 2);
// 	}
// 	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
// 	{
// 		mapreqs->pos_x += 10 * cos(img->angle - PI / 2);
// 		mapreqs->pos_y += 10 * sin(img->angle - PI / 2);
// 	}
// // }
// void	free_and_delete(char **arr, t_img *img)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// 	mlx_delete_image(img->mlx, img->no_image);
// 	mlx_delete_image(img->mlx, img->so_image);
// 	mlx_delete_image(img->mlx, img->we_image);
// 	mlx_delete_image(img->mlx, img->ea_image);
// 	mlx_delete_image(img->mlx, img->exit_image);
// 	mlx_delete_image(img->mlx, img->floor_image);
// 	mlx_delete_texture(img->no_texture);
// 	mlx_delete_texture(img->so_texture);
// 	mlx_delete_texture(img->we_texture);
// 	mlx_delete_texture(img->ea_texture);
// }

// // This is a simple valid map:
// // 111111
// // 100101
// // 101001
// // 1100N1
// // 111111

//
	// ◦ The map must be composed of only 6 possible characters: 0 for an empty space,
// // 1 for a wall, and N,S,E or W for the player’s start position and spawning
// // orientation.
// bool	check_map_characters(t_map map_i)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < map_i.height)
// 	{
// 		j = 0;
// 		while (j < map_i.width)
// 		{
// 			if (map_i.tiles[i][j] != '0' && map_i.tiles[i][j] != '1'
// 				&& map_i.tiles[i][j] != 'N' && map_i.tiles[i][j] != 'S'
// 				&& map_i.tiles[i][j] != 'E' && map_i.tiles[i][j] != 'W')
// 				return (false);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (true);
// }
// // ◦ The map must be closed/surrounded by walls,
	// if not the program must return
// // an error.
// bool	map_closed(t_map map_i)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < map_i.height)
// 	{
// 		j = 0;
// 		while (j < map_i.width)
// 		{
// 			if (map_i.tiles[i][j] == '0')
// 			{
// 				if (i == 0 || i == map_i.height - 1)
// 					return (false);
// 				if (j == 0 || j == map_i.width - 1)
// 					return (false);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (true);
// }

// // ◦ Except for the map content,
	// each type of element can be separated by one or
// // more empty line(s).
// // ◦ Except for the map content which always has to be the last, each type of
// // element can be set in any order in the file.
// // ◦ Except for the map,
// // each type of information from an element can be separated
// // by one or more space(s).
//
	// ◦ The map must be parsed as it looks in the file. Spaces are a valid part of the
//
	// map and are up to you to handle. You must be able to parse any kind of map,
// // as long as it respects the rules of the map.
//
	// Each element (except the map) firsts information is the type identifier (com-
// // posed by one or two character(s)),
// // followed by all specific informations for each
// // object in a strict order such as :
// // ∗ North texture:
// // NO ./path_to_the_north_texture
// // · identifier: NO
// // · path to the north texure
// // ∗ South texture:
// // SO ./path_to_the_south_texture
// // · identifier: SO
// // · path to the south texure
// // ∗ West texture:
// // WE ./path_to_the_west_texture
// // · identifier: WE
// // · path to the west texure
// // ∗ East texture:
// // EA ./path_to_the_east_texture
// // · identifier: EA
// // · path to the east texure
// // ∗ Floor color:
// // F 220,100,0
// // · identifier: F
// // · R,G,B colors in range [0,255]: 0, 255, 255
