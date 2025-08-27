#ifndef PARSING_H
# define PARSING_H

#include "get_next_line.h"
#include <stdio.h>
#include <mlx.h>
#include <string.h> 
#include <stdlib.h>


typedef struct s_player {
    double pos_x;
    double pos_y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;

typedef struct s_utils
{
    int *c_color;
    int *f_color;
    char **map;
    int no_fd;
    int so_fd;
    int ea_fd;
    int we_fd;
}	t_utils;

typedef struct s_mlx_helper
{
    void *mlx_ptr;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
    int tail;
    int *player_place;
    int *map_h_w;

} t_mlx_helper;




void print_error(int fd);
void check_if_it_texture(char *line);
void check_floor_and_ceiling_color(char *line);
void check_line(char *line);
void read_map(int fd);
t_utils *parser(char *str);
int check_file(char *str);
void print_failed(void);
int count_lines(char *str);
char **read_file(int fd, char *str);
void check_if_in_range(int color);
int f_c_color_helpr(t_utils *util, char *file);
void extract_and_pars_the_floor_and_ceiling_color(t_utils *util, char **file);
long long start_of_map(char **file);
char	**ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void extract_and_pars_the_map(t_utils *util, char **file);
void check_for_valid_character_in_map(char str);
void check_first_line(char **str);
int lent(char **str);
void check_the_last_line(char **str);
void pars_the_map_helper(t_utils *util);
void pars_the_map(t_utils *util);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void free_split(char **split);
void extract_and_pars_the_texture(t_utils *util, char **file);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int	ft_isdigit(int c);

#endif