#include "parsing.h"
#include <mlx.h>

int check_file(char *str)
{
    int fd;
    // int valid_extension = 0;

    fd = open(str, O_RDONLY);
    if(fd == -1)
    {
        write(2, "File doesn't exist or can't be opened\n", 39);
        exit(2);
    }
    // int i = 0;
    size_t len = strlen(str);
    if (len < 4 || strcmp(str + len - 4, ".cub") != 0)
    {
        write(2, "Not valid extension\n", 21);
        exit(2);
    }

    return fd;
}
void print_failed(void)
{
    write(2, "File doesn't exist or can't be opened\n", 39);
    exit(2);
}

int count_lines(char *str)
{
    int fd_2;
    char *tmp;
    int count = 0;
    fd_2 = open(str, O_RDONLY);
    if(fd_2 == -1)
        print_failed();
    while ((tmp = get_next_line(fd_2)) != NULL)
    {
        free(tmp);
        count++;
    }
    close(fd_2);
    return count;
}
char **read_file(int fd, char *str)
{
    char **file;
    char *line;
    int lent;
   
    int i = 0;
   
    lent = count_lines(str);
    file = malloc(sizeof(char *) * (lent+ 1));
    if (!file)
        return NULL;
    line = get_next_line(fd);
    while (line != NULL)
    {
        file[i] = strdup(line);
        free(line);
        i++;
        line = get_next_line(fd);
    }
    file[i] = NULL;
    return file;
}

t_utils *parser(char *str)
{
    t_utils *util;
    int fd;
    util =  malloc(sizeof(t_utils));

    util->c_color = malloc(3 * sizeof(int));
    util->f_color = malloc(3 * sizeof(int));
    util->no_fd = -1;
    util->so_fd = -1;
    util->ea_fd = -1;
    util->we_fd = -1;
    util->map = NULL;

    fd = check_file(str);
    char **file = read_file(fd, str);
    extract_and_pars_the_texture(util, file);
    extract_and_pars_the_floor_and_ceiling_color(util, file);
    extract_and_pars_the_map(util, file);

    return util;
}
void print_config(t_utils *util)
{
    printf("NO TEXTURE : [%d]\n", util->no_fd);
    printf("SO TEXTURE : [%d]\n", util->so_fd);
    printf("WE TEXTURE : [%d]\n", util->we_fd);
    printf("NO TEXTURE : [%d]\n", util->ea_fd);
    printf("F COLORES : [%d] [%d] [%d]\n", util->f_color[0], util->f_color[1], util->f_color[2]);
    printf("C COLORES : [%d] [%d] [%d]\n", util->c_color[0], util->c_color[1], util->c_color[2]);


    int i = 0;
    printf("Map :  \n");
    while(util->map[i])
    {
        printf("[%s]\n", util->map[i]);
        i++;
    }

}
void find_player(char **map, int *player_place)
{
    int i = 0;
    int j = 0;


    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
                {
                    player_place[0] = i;
                    player_place[1] = j;
                    break;
                }
            j++;
        }
        i++;
    }

}

void find_h_w_for_map(char **map, int *map_h_w)
{
    int i = lent(map) -  1;
    int j = 0;
    int r = 0;

    while (map[j])
    {
        r = 0;
        while (map[j][r])
        {
            r++;
        }
        j++;
    }
    map_h_w[0] = i;
    map_h_w[1] = r - 1;
    
}

// void draw_map(t_utils *util, t_mlx_helper *mlx_utils)
// {
//     int x;
//     int y;
//     int offset;

//     y = 0;
//     while (y < 800)
//     {
//         x = 0;
//         while (x < 800)
//         {
//             if (util->map[y][x] == '1')
//             {
//                 offset = (y * mlx_utils->line_len)+ (x * (mlx_utils->bpp / 8));
//                  *(int *)(mlx_utils->addr + offset) = 0x8D9797
//             }
//             else if (util->map[y][x] == '0')
//             {
//                  offset = (y * mlx_utils->line_len)+ (x * (mlx_utils->bpp / 8));
//                   *(int *)(mlx_utils->addr + offset) =  0x000000
//             }
//             else if (util->map[y][x] == 'N' || util->map[y][x] == 'S' || util->map[y][x] == 'E' || util->map[y][x] == 'W')
//             {
//                 offset = (y * mlx_utils->line_len)+ (x * (mlx_utils->bpp / 8));
//                  *(int *)(mlx_utils->addr + offset) = 0x008000
//             }
           


//         }
//     }

// }

void draw_map(t_utils *util, t_mlx_helper *mlx_utils)
{
    int x, y, offset;
    int map_height = lent(util->map);
    int scale = 20; 

    int map_y = 0;
    while (map_y < map_height)
    {
        int map_width = strlen(util->map[map_y]);
        int map_x = 0;
        while (map_x < map_width)
        {
            int py = 0;
            while (py < scale)
            {
                int px = 0;
                while (px < scale)
                {
                    int screen_x = map_x * scale + px;
                    int screen_y = map_y * scale + py;

                    if (screen_x < 1000 && screen_y < 1000)
                    {
                        offset = (screen_y * mlx_utils->line_len) + (screen_x * (mlx_utils->bpp / 8));

                        if (util->map[map_y][map_x] == '1')
                            *(int *)(mlx_utils->addr + offset) = 0x8D9797; // Wall
                        else if (util->map[map_y][map_x] == '0')
                            *(int *)(mlx_utils->addr + offset) = 0x000000; // Floor
                        else if (util->map[map_y][map_x] == 'N' || util->map[map_y][map_x] == 'S' || 
                                util->map[map_y][map_x] == 'E' || util->map[map_y][map_x] == 'W')
                            *(int *)(mlx_utils->addr + offset) = 0x008000; // Player
                    }

                    px++;
                }
                py++;
            }

            map_x++;
        }
        map_y++;
    }
}



int main(int argc, char *argv[])
{

        t_utils *util;
    t_mlx_helper *mlx_utils;
        t_player player;
    
    mlx_utils = malloc(sizeof(t_mlx_helper));
    mlx_utils->player_place = malloc(2 * sizeof(int));
    mlx_utils->map_h_w =  malloc(2 * sizeof(int));
    util = parser(argv[1]);

   print_config(util);
    mlx_utils->mlx_ptr = mlx_init();
    if (!mlx_utils->mlx_ptr)
        return(write(2, "mlx_init failed\n", 17));

       mlx_utils->win = mlx_new_window(mlx_utils->mlx_ptr, 1000, 1000, "cub3D");
        mlx_utils->img = mlx_new_image(mlx_utils->mlx_ptr, 1000, 1000);
        mlx_utils->addr = mlx_get_data_addr(mlx_utils->img, &mlx_utils->bpp, &mlx_utils->line_len, &mlx_utils->endian);
       find_player(util->map, mlx_utils->player_place);
       player.pos_x = mlx_utils->player_place[0] * 0.5;
       player.pos_y =  mlx_utils->player_place[1] * 0.5;
       //find_h_w_for_map(util->map, mlx_utils->map_h_w);

        draw_map(util, mlx_utils);
        mlx_put_image_to_window( mlx_utils->mlx_ptr,  mlx_utils->win,  mlx_utils->img, 0, 0);

      mlx_loop( mlx_utils->mlx_ptr);

}
