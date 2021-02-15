#include <mlx.h>
#include "parsing.h"
#include "libft/libft.h"
#include <unistd.h>

int		rgb_to_int_f(t_all *all);
int		rgb_to_int_c(t_all *all);
void    get_data_tex(t_all *all)
{
    if ((all->tex[0].img = mlx_xpm_file_to_image(all->win.mlx, all->NO.p, &all->tex[0].tex_w, &all->tex[0].tex_h)) == NULL ||
    (all->tex[0].addr = mlx_get_data_addr(all->tex[0].img, &all->tex[0].bits_per_pixel, &all->tex[0].line_length, &all->tex[0].endian)) == NULL)
      exit (0);
    if ((all->tex[1].img = mlx_xpm_file_to_image(all->win.mlx, all->SO.p, &all->tex[1].tex_w, &all->tex[1].tex_h)) == NULL ||
    (all->tex[1].addr = mlx_get_data_addr(all->tex[1].img, &all->tex[1].bits_per_pixel, &all->tex[1].line_length, &all->tex[1].endian)) == NULL)
       exit (0);
    if ((all->tex[2].img = mlx_xpm_file_to_image(all->win.mlx, all->WE.p, &all->tex[2].tex_w, &all->tex[2].tex_h)) == NULL ||
    (all->tex[2].addr = mlx_get_data_addr(all->tex[2].img, &all->tex[2].bits_per_pixel, &all->tex[2].line_length, &all->tex[2].endian)) == NULL)
     exit (0);
    if ((all->tex[3].img = mlx_xpm_file_to_image(all->win.mlx, all->EA.p, &all->tex[3].tex_w, &all->tex[3].tex_h)) == NULL ||
    (all->tex[3].addr = mlx_get_data_addr(all->tex[3].img, &all->tex[3].bits_per_pixel, &all->tex[3].line_length, &all->tex[3].endian)) == NULL)
      exit (0);
      if ((all->tex[4].img = mlx_xpm_file_to_image(all->win.mlx, all->S.s, &all->tex[4].tex_w, &all->tex[4].tex_h)) == NULL ||
    (all->tex[3].addr = mlx_get_data_addr(all->tex[4].img, &all->tex[4].bits_per_pixel, &all->tex[4].line_length, &all->tex[4].endian)) == NULL)
      exit (0);
}

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

unsigned int            get_color(t_all *all, int x, int y, int i)
{
    char    *dst;
    unsigned int color;

    dst = all->tex[i].addr + (y * all->tex[i].line_length + x * (all->tex[i].bits_per_pixel / 8));
    color = *(unsigned int*)dst;
    return (color);
}
void    ft_clean_window(t_all *all, int f, int c)
{
	int	i;
	int	j;

	i = -1;
	while(++i < all->rend.y / 2)
	{
		j = -1;
		while (++j < all->rend.x)
			my_mlx_pixel_put(all, j, i, f);
	}
  while(++i < all->rend.y)
	{
		j = -1;
		while (++j < all->rend.x)
			my_mlx_pixel_put(all, j, i, c);
	}
}

int newcub(t_all *all)
{
  double posX = all->plr.x, posY = all->plr.y;  //x and y start position
  double dirX = all->plr.dirX, dirY = all->plr.dirY; //initial direction vector
  double planeX = all->plr.planeX, planeY = all->plr.planeY; //the 2d raycaster version of camera plane
  unsigned int color;

  all->img.img = mlx_new_image(all->win.mlx, all->rend.x, all->rend.y);
  all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length,
                                 &all->img.endian);
    int f = 0;
    int c = 0;
    
		f = rgb_to_int_f(all);
    c = rgb_to_int_c(all);

  ft_clean_window(all, f, c);
    for(int x = 0; x < all->rend.x; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / (double)all->rend.x - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;

      //which box of the map we're in
      int mapX = (int)posX;
      int mapY = (int)posY;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      double deltaDistX = fabs(1 / rayDirX);
      double deltaDistY = fabs(1 / rayDirY);
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(all->only_m[mapY][mapX] > '0')
            hit = 1;
      }

      //Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
      if(side == 0)
        perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
      else
        perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

      //Calculate height of line to draw on screen
      int lineHeight = (int)(all->rend.y / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + all->rend.y / 2;
      if(drawStart < 0)
        drawStart = 0;
      int drawEnd = lineHeight / 2 + all->rend.y / 2;
      if(drawEnd >= all->rend.y)
        drawEnd = all->rend.y - 1;

      //texturing calculations
 //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if(side == 0)
        wallX = posY + perpWallDist * rayDirY;
      else
        wallX = posX + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * 64);
      if(side == 0 && rayDirX > 0)
        texX = 64 - texX - 1;
      if(side == 1 && rayDirY < 0)
        texX = 64 - texX - 1;

      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
      // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * 64 / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - all->rend.y / 2 + lineHeight / 2) * step;
      for(int y = drawStart; y < drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & ( 63);
        texPos += step;
        if (side == 0)
        { 
          if (stepX > 0)
            color = get_color(all, texX, texY, 3);
          else
            color = get_color(all, texX, texY, 0);
        }
         
        else
        {
          if (stepY > 0)
            color = get_color(all, texX, texY, 1);
          else
            color = get_color(all, texX, texY, 2);
        }
          
        my_mlx_pixel_put(all, x , y, color);
      }
    }
    mlx_put_image_to_window(all->win.mlx, all->win.win, all->img.img, 0, 0);
    return (1);
}

int key_press(int key, t_all *all)
 {
	 double FOOT = 0.5;
	 double rotSpeed = 0.05;
	 double planeX = all->plr.planeX;
	 double planeY = all->plr.planeY;
	 double posX = all->plr.x;
	 double posY = all->plr.y;
	 double dirX = all->plr.dirX;
	 double dirY = all->plr.dirY;
	printf("\npress\n");

	if (key == 13)
	{
		printf("%c\n", all->only_m[(int)(posY + dirY)][(int)(posX + dirX)]);
		if (all->only_m[(int)(posY + dirY)][(int)(posX + dirX)] == '0')
		{
			all->plr.x += dirX * FOOT;
			all->plr.y += dirY * FOOT;
		}
  }
	if (key == 1)
	{
		printf("%c\n",all->only_m[(int)posY][(int)(posX - FOOT)]);
		if (all->only_m[(int)(posY - dirY)][(int)(posX - dirX)] == '0')
		{
			all->plr.x -= dirX * FOOT;
			all->plr.y -= dirY * FOOT;
		}
	}
	if (key == 2)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		all->plr.dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		all->plr.dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		all->plr.planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		all->plr.planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	 //right
	if (key == 0)
	 {
	   //both camera direction and camera plane must be rotated
	   double oldDirX = dirX;
	   all->plr.dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
	   all->plr.dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
	   double oldPlaneX = planeX;
	   all->plr.planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
	   all->plr.planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	 }
	if (key == 53)
		exit(0);
	return(0);
 }


void             print_map(t_all *all)
{
  

    all->win.mlx = mlx_init();
    all->win.win = mlx_new_window(all->win.mlx, all->rend.x, all->rend.y, "Cub3D");
    all->img.img = mlx_new_image(all->win.mlx, all->rend.x, all->rend.y);
    all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length,
                                 &all->img.endian);
    get_data_tex(all);
    newcub(all);
    mlx_put_image_to_window(all->win.mlx, all->win.win, all->img.img, 0, 0);
    mlx_hook(all->win.win, 2, 0, key_press, all);
    mlx_hook(all->win.win, 17, 0, ft_close, all);
    mlx_loop_hook(all->win.mlx,  (newcub), all);
    mlx_loop(all->win.mlx);
}