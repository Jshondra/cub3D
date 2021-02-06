#include <mlx.h>
#include "parsing.h"
#include "libft/libft.h"

void            my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
    char    *dst;

    dst = all->img.addr + (y * all->img.line_length + x * (all->img.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
void        printer(t_all *all, int k, int l)
{
    int i = 0;
    int j = 0;

    while(i < 20)
    {
       while(j < 20)
       {
            if (ft_strchr("1", all->only_m[k][l]))
                my_mlx_pixel_put(all, i, j, 0x00FFFFFF);
            else
                my_mlx_pixel_put(all, i, j, 0x00FF0000);
            j++;
       }
       j = 0;
       i++;
    }
}

void             print_map(t_all *all)
{
    void    *mlx;
    void    *mlx_win;
   
    int     img_width;
    int     img_height;

    int i = 20;
 
    int j = 20;
    mlx = mlx_init();

    mlx_win = mlx_new_window(mlx, 800, 800, "Hello world!");
    all->img.img = mlx_new_image(mlx, 800, 800);
    all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length,
                                 &all->img.endian);
    int k = 0;
    int l = 0;
    while(all->only_m[k][l])
    {
        while(all->only_m[k][l])
        {
            if (ft_strchr ("1NESW", all->only_m[k][l]))
            {
                printer(all, k, l);
                mlx_put_image_to_window(mlx, mlx_win, all->img.img, i, j);
            }
            i += 19;
            l++;
        }
        l = 0;
        k++;
        j += 19;
        i = 20;
    }
    mlx_loop(mlx);
}