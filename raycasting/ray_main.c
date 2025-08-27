#include <mlx.h>
#include <libc.h>


//void *mlx_init(void)
//void *mlx_new_window(void *mlx_ptr, int width, int height, char *title)
//int mlx_loop(void *mlx_ptr)
//int mlx_hook(void *win_ptr, int event, int mask, int (*f)(...), void *param)
//int mlx_loop_hook(void *mlx_ptr, int (*f)(void *), void *param)
//void *mlx_new_image(void *mlx_ptr, int width, int height)
//char *mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *line_length, int *endian)
//int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y)
//int mlx_destroy_image(void *mlx_ptr, void *img_ptr)
//int mlx_destroy_window(void *mlx_ptr, void *win_ptr) and int mlx_destroy_display(void *mlx_ptr)
//void *mlx_xpm_file_to_image(void *mlx_ptr, char *filename, int *width, int *height)

int main()
{
    void *mlx_ptr;
    void *win;
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;

    mlx_ptr = mlx_init();
    if (!mlx_ptr)
        return(write(2, "mlx_init failed\n", 17));

        win = mlx_new_window(mlx_ptr, 800, 600, "cub3D");
        img = mlx_new_image(mlx_ptr, 800, 600);
        addr = mlx_get_data_addr(img, &bpp, &line_len, &endian);

        mlx_loop(mlx_ptr);



}