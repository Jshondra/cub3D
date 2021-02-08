#include <mlx.h>
#include "parsing.h"
#include "libft/libft.h"

int		ft_close(t_all *all, int win)
{
    if (win == 1)
		mlx_destroy_window(all->win.mlx, all->win.win);
	exit(0);
	return (1);
}

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
            if (all->plr.x == l && all->plr.y == k)
                my_mlx_pixel_put(all, l * 20 + i, k * 20 + j, 0x00FFFFFF);
            else
                my_mlx_pixel_put(all,l * 20 + i, k * 20 + j, 0x00FF0000);
            j++;
       }
       j = 0;
       i++;
    }
}


void print_only_map(t_all *all)
{
    int l = 0;
    int k = 0;

    while(all->only_m[k][l])
    {
        while(all->only_m[k][l])
        {
            if (all->only_m[k][l] == '1')
                printer(all, k, l);
            else if (all->plr.x == l && all->plr.y == k)
              printer(all, k, l);
            l++;
        }
        l = 0;
        k++;
    }
}


void print_col(t_all *all, float i, int k)
{
    int j;
    int r;
    int num;
    if (i < 1)
        i = 1;
    r = (int)(all->rend.y / 2);
    j = (int)((float)all->rend.y / i);
    num = r - (int)(j / 2);
printf("j=%d, k=%d\n", j, k);
    while(num < r + (int)(j / 2))
    {
    
        my_mlx_pixel_put(all, k, num, 0x00FF0000);
        num++;

    }
}
void	ft_cast_rays(t_all *all)
{
    float i = 0;
    int k = 0;
	t_plr	ray = all->plr;
	ray.start = ray.dir - (M_PI / 6); 
	ray.end = ray.dir + (M_PI / 6);

  while (ray.start <= ray.end)
	{
		ray.x = all->plr.x; // каждый раз возвращаемся в точку начала
		ray.y = all->plr.y;
		while (all->only_m[(int)(ray.y)][(int)(ray.x)] != '1')
		{
			ray.x += cos(ray.start) * 0.01;
			ray.y += sin(ray.start) * 0.01;
			//my_mlx_pixel_put(all, (ray.x * SCALE), (ray.y * SCALE), 0x990099);
		}
		ray.start += M_PI / 3 / all->rend.x;
        i = sqrt((ray.x - all->plr.x)*(ray.x - all->plr.x) + (ray.y - all->plr.y)*(ray.y - all->plr.y));
        i = i * cos(fabs(ray.start - ray.dir));
        printf("%f\n", i);
        print_col(all, i, k);
        k++;
        i = 0;
    }
}
void    ft_clean_window(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	while(i < all->rend.y)
	{
		j = 0;
		while (j < all->rend.x)
		{
			my_mlx_pixel_put(all, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

int     key_hook(int keycode, t_all *all)
{
    int x = all->plr.x;
    int y = all->plr.y;

    all->only_m[y][x] = '0';
    ft_clean_window(all);
    //mlx_clear_window(all->win.mlx, all->win.win);
    if (keycode == 13 && all->only_m[y][x] == '0') 
		{
            all->plr.x += cos(all->plr.dir)*0.7;
            all->plr.y += sin(all->plr.dir)*0.7;
        }
	if (keycode == 1 && all->only_m[y + 1][x] == '0')
    {
		all->plr.x -= cos(all->plr.dir)*0.7;
        all->plr.y -= sin(all->plr.dir)*0.7;
    }
	if (keycode == 123)
		all->plr.dir -= 0.05;
	if (keycode == 124)
		all->plr.dir += 0.05;
	if (keycode == 53)
	{
		mlx_destroy_window(all->win.mlx, all->win.win);
		exit(0);
	}
	//print_only_map(all);
	ft_cast_rays(all);
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->img.img, 0, 0);
    return(0);
}


void             print_map(t_all *all)
{
    int     img_width;
    int     img_height;
int i =0;
    all->win.mlx = mlx_init();
    all->win.win = mlx_new_window(all->win.mlx, 600, 400, "Hello world!");
    all->img.img = mlx_new_image(all->win.mlx, 600, 400);
    all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length,
                                 &all->img.endian);
   // print_only_map(all);
    ft_cast_rays(all);
    mlx_put_image_to_window(all->win.mlx, all->win.win, all->img.img, 0, 0);
    mlx_hook(all->win.win, 2, 0, key_hook, all);
    mlx_hook(all->win.win, 17, 0, ft_close, all);
    mlx_loop(all->win.mlx);
    while(1)
    {
        i = 0;
    }
}