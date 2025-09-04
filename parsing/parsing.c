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
void find_player(t_utils *util, int *player_place)
{
    int i = 0;
    int j = 0;
    t_utils *tmp = util;



  
    while (tmp->map[i])
    {
   
        j = 0;
        while (tmp->map[i][j])
        {
    
            if (tmp->map[i][j] == 'N' || tmp->map[i][j] == 'S' || tmp->map[i][j] == 'E' || tmp->map[i][j] == 'W')
                {
             
                    player_place[0] = i;
             
                    player_place[1] = j;
                   
                    tmp->player_place[0] = i;
                
                    tmp->player_place[1] = j;
                   
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

// void draw_map(t_utils *util, t_mlx_helper *mlx_utils) =======
// {
//     int x, y, offset;
//     int map_height = lent(util->map);
//     int scale = 20; 

//     int map_y = 0;
//     while (map_y < map_height)
//     {
//         int map_width = strlen(util->map[map_y]);
//         int map_x = 0;
//         while (map_x < map_width)
//         {
//             int py = 0;
//             while (py < scale)
//             {
//                 int px = 0;
//                 while (px < scale)
//                 {
//                     int screen_x = map_x * scale + px;
//                     int screen_y = map_y * scale + py;

              

//                     if (screen_x < 1000 && screen_y < 1000)
//                     {
//                         offset = (screen_y * mlx_utils->line_len) + (screen_x * (mlx_utils->bpp / 8));

//                         if (util->map[map_y][map_x] == '1')
//                             *(int *)(mlx_utils->addr + (offset) ) = 0x8D9797; // Wall
//                         else if (util->map[map_y][map_x] == '0')
//                             *(int *)(mlx_utils->addr + (offset)) = 0x000000; // Floor
//                         else if (util->map[map_y][map_x] == 'N' || util->map[map_y][map_x] == 'S' || 
//                                 util->map[map_y][map_x] == 'E' || util->map[map_y][map_x] == 'W')
//                             *(int *)(mlx_utils->addr + (offset)) = 0x008000; // Player
//                     }

//                     px++;
//                 }
//                 py++;
//             }

//             map_x++;
//         }
//         map_y++;
//     }
// }






void cast_rays(t_player *player, t_utils *util, t_mlx_helper *mlx_utils)
{
    int x;
    int y;
    double new_x;
    double ray_dir_x;
    double ray_dir_y;
    double distan_wall_x;
    double distan_wall_y;
    int map_x;
    int map_y;
    int step_x;        
    int step_y;      
    double side_dist_x; 
    double side_dist_y;
    int hit;
    int side;
    double perp_wall_dist; 
    int line_height;        
    int draw_start; 
    int offset;        
    int draw_end;          

    //ray_direction = player_direction + camera_plane * camera_coordinate
    x = 0;
    while (x < 1000)
    {
        new_x = 2 * x / (double)(1000) - 1;
        ray_dir_x = player->dir_x + player->plane_x * new_x;
        ray_dir_y = player->dir_y + player->plane_y * new_x;
        map_x = (int)(player->pos_x);
        map_y = (int)(player->pos_y);
        distan_wall_x = fabs(1 / ray_dir_x);  // how far the ray must travel to reach the next grid line
        distan_wall_y = fabs(1 / ray_dir_y);   // how far the ray must travel to reach the next grid line

        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (player->pos_x - map_x) * distan_wall_x; //distance to next VERTICAL line ( | )
        }
        else if (ray_dir_x > 0)
        {
            step_x = +1;
            side_dist_x = (map_x + 1.0 - player->pos_x) * distan_wall_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (player->pos_y - map_y) * distan_wall_y; //distance to next HORIZONTAL line ( ___ )
        }
        else if (ray_dir_y > 0)
        {
            step_y = +1;
            side_dist_y = (map_y + 1.0 - player->pos_y) * distan_wall_y;
        }
        
        hit = 0;
        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                //Step in X direction (move to next vertical grid line)
                side_dist_x += distan_wall_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                //Step in Y direction (move to next horizontal grid line)
                side_dist_y += distan_wall_y;
                map_y += step_y;
                side = 1;
      
            }
            if (util->map[map_y][map_x] == '1')
                hit = 1;
        }

        if (side == 0)
            perp_wall_dist = (map_x - player->pos_x + (1 - step_x) / 2) / ray_dir_x;
        else if (side == 1)
            perp_wall_dist = (map_y - player->pos_y + (1 - step_y) / 2) / ray_dir_y;

        line_height = (int)(1000/perp_wall_dist);
        draw_start = (-line_height / 2) + (1000 / 2);
        draw_end = line_height / 2 + 1000 / 2;

        if (draw_start < 0)
            draw_start = 0;
        if (draw_end >= 1000)
            draw_end = 999;

        y = 0;
        while (y < 1000)
        {
            offset = (y * mlx_utils->line_len) + (x * (mlx_utils->bpp / 8));
            if (y < draw_start)
            {
               
                *(int *)(mlx_utils->addr + (offset)) = 0x87CEEB;
            }
            else if (y >= draw_start && y <= draw_end)
            {
                *(int *)(mlx_utils->addr + (offset) ) = 0x8B4513;
            }
            else if (y > draw_end)
            {
                *(int *)(mlx_utils->addr + (offset)) = 0x228B22;
            }
            y++;
        }
        x++;
    }
}

void intit_player(t_utils *utils, t_player *player, t_mlx_helper *mlx_utils)
{
    player->pos_x = mlx_utils->player_place[0] + 0.5;
    player->pos_y =  mlx_utils->player_place[1] + 0.5;

    if (utils->map[mlx_utils->player_place[0]][mlx_utils->player_place[1]] == 'N')
    {
        player->dir_x = -1;
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = 0.66;
    }
    else if (utils->map[mlx_utils->player_place[0]][mlx_utils->player_place[1]] == 'S')
    {
        player->dir_x = 1;
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = -0.66;
    }
    else if (utils->map[mlx_utils->player_place[0]][mlx_utils->player_place[1]] == 'E')
    {
        player->dir_x = 0;
        player->dir_y = 1;
        player->plane_x = 0.66;
        player->plane_y = 0;
    }
    else if (utils->map[mlx_utils->player_place[0]][mlx_utils->player_place[1]] == 'W')
    {
        player->dir_x = 0;
        player->dir_y = -1;
        player->plane_x = -0.66;
        player->plane_y = 0;
    }

}

int move(int keycode, void *util)
{
    t_utils *info = (t_utils *)util;

    if (keycode == 119) // W key - move forward
    {
        // Move player forward

        info->map[info->player_place[0]][info->player_place[1]-1] = info->map[info->player_place[0]][info->player_place[1]];
         info->map[info->player_place[0]][info->player_place[1]] = '0';
         info->player_place[1] = info->player_place[1] - 1;
    }
    else if (keycode == 115) // S key - move backward  
    {
        info->map[info->player_place[0]][info->player_place[1]+1] = info->map[info->player_place[0]][info->player_place[1]];
        info->map[info->player_place[0]][info->player_place[1]] = '0';
        info->player_place[1] = info->player_place[1] + 1;
    }
    // else if (keycode == 97) // A key - turn left
    // {
    //     // Rotate player left
    // }
    // else if (keycode == 100) // D key - turn right
    // {
    //     // Rotate player right
    // }
    // else if (keycode == 65307) // ESC key
    // {
    //     exit(0); // Quit the game
    // }
    return 0;
}

int main(int argc, char *argv[])
{

        t_utils *util;
    t_mlx_helper *mlx_utils;
        t_player player;
    
    mlx_utils = malloc(sizeof(t_mlx_helper));
      util = malloc(sizeof(util));
    mlx_utils->player_place = malloc(2 * sizeof(int));
    util->player_place = malloc(2 * sizeof(int));
    mlx_utils->map_h_w =  malloc(2 * sizeof(int));
    util = parser(argv[1]);

   print_config(util);
   printf("helppppp 0\n");
    mlx_utils->mlx_ptr = mlx_init();
    printf("helppppp 1\n");
    if (!mlx_utils->mlx_ptr)
        return(write(2, "mlx_init failed\n", 17));
    printf("helppppp 2\n");

       mlx_utils->win = mlx_new_window(mlx_utils->mlx_ptr, 1000, 1000, "cub3D");
           printf("helppppp 3\n");
        mlx_utils->img = mlx_new_image(mlx_utils->mlx_ptr, 1000, 1000);
            printf("helppppp 4\n");

        mlx_utils->addr = mlx_get_data_addr(mlx_utils->img, &mlx_utils->bpp, &mlx_utils->line_len, &mlx_utils->endian);
            printf("helppppp 5\n");

       find_player(util, mlx_utils->player_place);
           printf("helppppp 6\n");


       intit_player(util, &player, mlx_utils);

           printf("helppppp 7\n");

        
       //find_h_w_for_map(util->map, mlx_utils->map_h_w);

       //draw_map(util, mlx_utils);
    
           cast_rays(&player, util, mlx_utils);

               printf("helppppp 8\n");

          mlx_hook(mlx_utils->win, 2, 1L<<0, move, util);

              printf("helppppp 9\n");

        mlx_put_image_to_window( mlx_utils->mlx_ptr,  mlx_utils->win,  mlx_utils->img, 0, 0);
            printf("helppppp 10\n");


      mlx_loop( mlx_utils->mlx_ptr);

}




















