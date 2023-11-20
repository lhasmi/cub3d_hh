/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhasmi <lhasmi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:53:40 by lhasmi            #+#    #+#             */
/*   Updated: 2023/11/07 20:58:14 by lhasmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char    **manual_realloc_2D_array(char **old_array, int old_rows, int new_rows, int new_cols)
{
    char **new_array;
    int i;
    
    (void)new_cols; // To silence the unused parameter warning (for now
    new_array = NULL;
    new_array = (char **)malloc(sizeof(char *) * new_rows);
    if (!new_array)
    {
        ft_error("Error: Could not allocate memory for new array");
        return (NULL);
    }
    i = 0;
    while (i < old_rows) 
    {
        new_array[i] = ft_strdup(old_array[i]);
        free(old_array[i]);
        i++;
    }
    while (i < new_rows) 
    {
        new_array[i] = NULL;
        i++;
    }
    free(old_array);
    return (new_array);
}
// printf("call of the t_map content in the realloc 2D: map->tiles[0] = %s\n", new_array[0]);// Debug

void update_map_cols(t_map *map, int new_row_length) 
{
    if (new_row_length > map->cols)
        map->cols = new_row_length;
}

void fill_map_tiles(t_map *map, int fd, char *first_line)
{
    int i = 0;
    char *line = first_line;

    map->tiles = (char **)malloc(sizeof(char *));
    if (!map->tiles) 
        free_map_exit(map, "Error: Memory allocation failed in fill map tiles 1", 0);
    while (line) 
    {
        update_map_cols(map, ft_strlen(line));
        map->tiles = manual_realloc_2D_array(map->tiles, i, i + 1, map->cols);
        if (!map->tiles) 
            free_map_exit(map, "Error: Memory allocation failed in fill map tiles 2", 0);
        map->tiles[i] = line;
        i++;
        map->rows++;
        if (!(line = get_next_line(fd)))
            break;
    }
    map->tiles = manual_realloc_2D_array(map->tiles, i, i + 1, map->cols);
    if (!map->tiles) 
        free_map_exit(map, "Error: Memory allocation failed in fill map tiles 3", 0);
    map->tiles[i] = NULL;
}
    // printf("call of the t_map content in the fill tiles 1: map->tiles[0] = %s\n", map->tiles[0]);// Debug
    // printf("call of the t_map content in the fill tiles 2: map->tiles[0] = %s\n", map->tiles[0]);// Debug