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
    (all->tex[4].addr = mlx_get_data_addr(all->tex[4].img, &all->tex[4].bits_per_pixel, &all->tex[4].line_length, &all->tex[4].endian)) == NULL)
      exit (0);
}

//int cmp(const void *a, const void *b) {
  //   return *(int*)a - *(int*)b;
 //}

////////////////////////////////////////////////////////////////
void bubbleSort(double *num, double *s, int size)
{
  // Для всех элементов
  for (int i = 0; i < size - 1; i++)
  {
    for (int j = (size - 1); j > i; j--) // для всех элементов после i-ого
    {
      if (num[j] > num[j - 1]) // если текущий элемент меньше предыдущего
      {
        int temp = num[j - 1]; // меняем их местами
        num[j - 1] = num[j];
        num[j] = temp;
       int t = s[j - 1]; // меняем их местами
       s[j - 1] = s[j];
        s[j] = t;
      }
    }
  }
}

// void quickSort(double *numbers, int left, int right)
// {
//   double pivot; // разрешающий элемент
//   double l_hold = left; //левая граница
//   double r_hold = right; // правая граница
//   pivot = numbers[left];
//   while (left < right) // пока границы не сомкнутся
//   {
//     while ((numbers[right] >= pivot) && (left < right))
//       right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
//     if (left != right) // если границы не сомкнулись
//     {
//       numbers[left] = numbers[right]; // перемещаем элемент [right] на место разрешающего
//       left++; // сдвигаем левую границу вправо
//     }
//     while ((numbers[left] <= pivot) && (left < right))
//       left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
//     if (left != right) // если границы не сомкнулись
//     {
//       numbers[right] = numbers[left]; // перемещаем элемент [left] на место [right]
//       right--; // сдвигаем правую границу вправо
//     }
//   }
//   numbers[left] = pivot; // ставим разрешающий элемент на место
//   pivot = left;
//   left = l_hold;
//   right = r_hold;
//   if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
//     quickSort(numbers, left, pivot - 1);
//   if (right > pivot)
//     quickSort(numbers, pivot + 1, right);
// }

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

void selecter(t_all *all)
{
  all->ray.deltaDistX = fabs(1 / all->plr.rayposX);
  all->ray.deltaDistY = fabs(1 / all->plr.rayposY);
  all->ray.hit = 0;
  if(all->plr.rayposX < 0)
      {
        all->ray.stepX = -1;
        all->ray.sideDistX =  (all->plr.x - all->ray.mapX) * all->ray.deltaDistX;
      }
      else
      {
        all->ray.stepX = 1;
        all->ray.sideDistX = (all->ray.mapX + 1.0 - all->plr.x) * all->ray.deltaDistX;
      }
      if(all->plr.rayposY < 0)
      {
        all->ray.stepY = -1;
        all->ray.sideDistY = (all->plr.y- all->ray.mapY) * all->ray.deltaDistY;
      }
      else
      {
        all->ray.stepY = 1;
        all->ray.sideDistY = (all->ray.mapY + 1.0 - all->plr.y) * all->ray.deltaDistY;
      }
}

void newselector(t_all *all)
{
  while (all->ray.hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if(all->ray.sideDistX < all->ray.sideDistY)
        {
          all->ray.sideDistX += all->ray.deltaDistX;
          all->ray.mapX += all->ray.stepX;
          all->ray.side = 0;
        }
        else
        {
          all->ray.sideDistY += all->ray.deltaDistY;
          all->ray.mapY += all->ray.stepY;
          all->ray.side = 1;
        }
        //Check if ray has all->ray.hit a wall
        if(all->only_m[all->ray.mapY][all->ray.mapX] =='1')
            all->ray.hit = 1;
      }
      if(all->ray.side == 0)
        all->ray.perpWallDist = (all->ray.mapX - all->plr.x + (1 - all->ray.stepX) / 2) / all->plr.rayposX;
      else
        all->ray.perpWallDist = (all->ray.mapY - all->plr.y+ (1 - all->ray.stepY) / 2) / all->plr.rayposY;
}

int init(t_all *all, int x)
{
      all->plr.cameraX = 2 * x / (double)all->rend.x - 1; //x-coordinate in camera space
      all->plr.rayposX = all->plr.dirX + all->plr.planeX * all->plr.cameraX;
      all->plr.rayposY = all->plr.dirY + all->plr.planeY * all->plr.cameraX;
      all->ray.mapX = (int)all->plr.x;
      all->ray.mapY = (int)all->plr.y;
      selecter(all);
      newselector(all);
       all->draw.lineHeight = (int)(all->rend.y / all->ray.perpWallDist);
       all->draw.drawStart = -all->draw.lineHeight / 2 + all->rend.y / 2;
      if(all->draw.drawStart < 0)
        all->draw.drawStart = 0;
       all->draw.drawEnd = all->draw.lineHeight / 2 + all->rend.y / 2;
      if(all->draw.drawEnd >= all->rend.y)
        all->draw.drawEnd = all->rend.y - 1;
      if(all->ray.side == 0)
        all->draw.wallX = all->plr.y+ all->ray.perpWallDist * all->plr.rayposY;
      else
        all->draw.wallX = all->plr.x + all->ray.perpWallDist * all->plr.rayposX;
      all->draw.wallX -= floor((all->draw.wallX));
      return (x);
}

int choose_side(t_all *all, int g)
{
  if (all->ray.stepX > 0)
  {
    all->draw.texX = all->tex[3].tex_w - (int)(all->draw.wallX * all->tex[3].tex_w) - 1;
    all->draw.step = 1.0 * all->tex[3].tex_w / all->draw.lineHeight;
    g = 3;
  }
  else
  {
    all->draw.texX = all->tex[2].tex_w - (int)(all->draw.wallX * all->tex[2].tex_w) - 1;
    all->draw.step  = 1.0 * all->tex[2].tex_w / all->draw.lineHeight;
    g = 2;
  }
  return (g);
}

int   choose_side1(t_all *all, int g)
{
  if (all->ray.stepY > 0)
  {
    all->draw.texX = all->tex[1].tex_w - (int)(all->draw.wallX * all->tex[1].tex_w) - 1;
    all->draw.step  = 1.0 * all->tex[1].tex_w / all->draw.lineHeight;
    g = 1;
  }
  else
  {
    all->draw.texX = all->tex[0].tex_w - (int)(all->draw.wallX * all->tex[0].tex_w) - 1;
    all->draw.step = 1.0 * all->tex[0].tex_w / all->draw.lineHeight;
    g = 0;
  }
  return (g);
}

void  draw_walls(t_all *all, int x, int g)
{
  unsigned int color;
  double texPos = (all->draw.drawStart - all->rend.y / 2 + all->draw.lineHeight / 2) * all->draw.step;
  for(int y = all->draw.drawStart; y < all->draw.drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        all->draw.texY = (int)texPos % (all->tex[g].tex_h - 1);
        texPos += all->draw.step;
        color = get_color(all, all->draw.texX, all->draw.texY, g);
        my_mlx_pixel_put(all, x , y, color);
      }
}

// void ft_sprites(t_all *all)
// {
//     double spriteOrder[all->sprite.count];// массив для спрайтов
//     double spriteDistance[all->sprite.count];// массив для спрайтов
//    for(int i = 0; i < all->sprite.count; i++)
//     {
//       spriteOrder[i] = i;
//       spriteDistance[i] = (pow (all->plr.x - all->sprite.buf[i].x, 2) + pow(all->plr.y - all->sprite.buf[i].y, 2)); //sqrt not taken, unneeded
//     }
//    bubbleSort(spriteDistance, spriteOrder, all->sprite.count);
//     //after sorting the sprites, do the projection and draw them
//     for(int i = 0; i < all->sprite.count; i++)
//     {
//       //translate sprite position to relative to camera
//       double all->sprite.X = all->sprite.buf[(int)spriteOrder[i]].x - all->plr.x;
//       double all->sprite.Y = all->sprite.buf[(int)spriteOrder[i]].y - all->plr.y;
//       double all->sprite.inv = 1.0 / (all->plr.planeX * all->plr.dirY - all->plr.dirX * all->plr.planeY); //required for correct matrix multiplication
//       double all->sprite.tranX = all->sprite.inv * (all->plr.dirY * all->sprite.X - all->plr.dirX * all->sprite.Y);
//       double all->sprite.tranY = all->sprite.inv * (-all->plr.planeY * all->sprite.X + all->plr.planeX * all->sprite.Y); //this is actually the depth inall->ray.side the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])
//       int all->sprite.ScreenX = (int)((all->rend.x / 2) * (1 + all->sprite.tranX / all->sprite.tranY));

//       //parameters for scaling and moving the sprites
//       #define uDiv 1
//       #define vDiv 1
//       #define vMove 0.0
//       all->sprite.move_s = (int)(vMove / all->sprite.tranY);

//       //calculate height of the sprite on screen
//       all->tex[4].tex_h = abs((int)(all->rend.y / (all->sprite.tranY))) / vDiv; //using "all->sprite.tranY" instead of the real distance prevents fisheye
//       //calculate lowest and highest pixel to fill in current stripe
//        all->draw.drawStartY = -all->tex[4].tex_h / 2 + all->rend.y / 2 + all->sprite.move_s;
//       if(all->draw.drawStartY < 0) all->draw.drawStartY = 0;
//        all->draw.drawEndY = all->tex[4].tex_h / 2 + all->rend.y / 2 + all->sprite.move_s;
//       if(all->draw.drawEndY >= all->rend.y) all->draw.drawEndY = all->rend.y - 1;

//       //calculate width of the sprite
//       int spriteWidth = abs( (int) (all->rend.y / (all->sprite.tranY))) / uDiv;
//        all->draw.drawStartX = -spriteWidth / 2 + all->sprite.ScreenX;
//       if(all->draw.drawStartX < 0) all->draw.drawStartX = 0;
//        all->draw.drawEndX = spriteWidth / 2 + all->sprite.ScreenX;
//       if(all->draw.drawEndX >= all->rend.x) all->draw.drawEndX = all->rend.x - 1;

//       //loop through every vertical stripe of the sprite on screen
//       for(int stripe = all->draw.drawStartX; stripe < all->draw.drawEndX; stripe++)
//       {
//         int texX = (int)(256 * (stripe - (-spriteWidth / 2 + all->sprite.ScreenX)) * all->tex[g].tex_w / spriteWidth) / 256;
//         if(all->sprite.tranY > 0 && stripe > 0 && stripe < all->rend.x && all->sprite.tranY < Zbuff[stripe])
//         for(int y = all->draw.drawStartY; y < all->draw.drawEndY; y++) //for every pixel of the current stripe
//         {
//           int d = (y-all->sprite.move_s) * 256 - all->rend.y * 128 + all->tex[4].tex_h * 128; //256 and 128 factors to avoid floats
//           int texY = ((d * all->tex[g].tex_w) / all->tex[4].tex_h) / 256;
//           //Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
//           color = get_color(all, texX, texY, 4);
//             if((color & 0x00FFFFFF) != 0)  //paint pixel if it isn't black, black is the invisible color
//             my_mlx_pixel_put(all, stripe, y, color);
//         }
//       }
//   }
// }

int newcub(t_all *all)
{
  unsigned int color;
  double Zbuff[all->rend.x];
  double spriteOrder[all->sprite.count];// массив для спрайтов
  double spriteDistance[all->sprite.count];// массив для спрайтов
  int g = 0;
 
  all->img.img = mlx_new_image(all->win.mlx, all->rend.x, all->rend.y);
  all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length,
                                 &all->img.endian);
    int f = 0;
    int c = 0;
		f = rgb_to_int_f(all);
    c = rgb_to_int_c(all);
    ft_clean_window(all, c, f);
    for(int x = 0; x < all->rend.x; x++)
    {
      x = init(all, x);

      if (all->ray.side == 0)
        g = choose_side(all, g);
      else
        g = choose_side1(all, g);
      draw_walls(all, x, g);
       Zbuff[x] = all->ray.perpWallDist;
    }
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      for(int i = 0; i < all->sprite.count; i++)
    {
      spriteOrder[i] = i;
     spriteDistance[i] = (pow (all->plr.x - all->sprite.buf[i].x, 2) + pow(all->plr.y - all->sprite.buf[i].y, 2)); //sqrt not taken, unneeded
   // printf("%f", all->sprite.buf[i].x);
    }
    //  printf("%f", all->sprite.buf[0].x);

   bubbleSort(spriteDistance, spriteOrder, all->sprite.count);
    for(int i = 0; i < all->sprite.count; i++)
    {
      //translate sprite position to relative to camera
        all->sprite.X = all->sprite.buf[(int)spriteOrder[i]].x - all->plr.x;
        all->sprite.Y = all->sprite.buf[(int)spriteOrder[i]].y - all->plr.y;
        all->sprite.inv = 1.0 / (all->plr.planeX * all->plr.dirY - all->plr.dirX * all->plr.planeY); //required for correct matrix multiplication
        all->sprite.tranX = all->sprite.inv * (all->plr.dirY * all->sprite.X - all->plr.dirX * all->sprite.Y);
        all->sprite.tranY = all->sprite.inv * (-all->plr.planeY * all->sprite.X + all->plr.planeX * all->sprite.Y); //this is actually the depth inall->ray.side the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])
        all->sprite.ScreenX = (int)((all->rend.x / 2) * (1 + all->sprite.tranX / all->sprite.tranY));
        all->sprite.move_s = (int)(0.0 / all->sprite.tranY);
        all->tex[4].tex_h = abs((int)(all->rend.y / (all->sprite.tranY))) / 1; 
        all->draw.drawStartY = -all->tex[4].tex_h / 2 + all->rend.y / 2 + all->sprite.move_s;
      if(all->draw.drawStartY < 0) all->draw.drawStartY = 0;
       all->draw.drawEndY = all->tex[4].tex_h / 2 + all->rend.y / 2 + all->sprite.move_s;
      if(all->draw.drawEndY >= all->rend.y) all->draw.drawEndY = all->rend.y - 1;

      //calculate width of the sprite
      int spriteWidth = abs( (int) (all->rend.y / (all->sprite.tranY))) / 1;
       all->draw.drawStartX = -spriteWidth / 2 + all->sprite.ScreenX;
      if(all->draw.drawStartX < 0) all->draw.drawStartX = 0;
       all->draw.drawEndX = spriteWidth / 2 + all->sprite.ScreenX;
      if(all->draw.drawEndX >= all->rend.x) all->draw.drawEndX = all->rend.x - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = all->draw.drawStartX; stripe < all->draw.drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + all->sprite.ScreenX)) * all->tex[g].tex_w / spriteWidth) / 256;
        if(all->sprite.tranY > 0 && stripe > 0 && stripe < all->rend.x && all->sprite.tranY < Zbuff[stripe])
        for(int y = all->draw.drawStartY; y < all->draw.drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y-all->sprite.move_s) * 256 - all->rend.y * 128 + all->tex[4].tex_h * 128; //256 and 128 factors to avoid floats
          int texY = ((d * all->tex[g].tex_w) / all->tex[4].tex_h) / 256;
          //Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
          color = get_color(all, texX, texY, 4);
            if((color & 0x00FFFFFF) != 0)  //paint pixel if it isn't black, black is the invisible color
            my_mlx_pixel_put(all, stripe, y, color);
        }
      }
  }
   mlx_put_image_to_window(all->win.mlx, all->win.win, all->img.img, 0, 0);
    return (1);   
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void move_forward(t_all *all)
{
  if (all->only_m[(int)(all->plr.y + all->plr.dirY )][(int)(all->plr.x + all->plr.dirX)] == '0')
		{
			all->plr.x += all->plr.dirX * 0.5;
			all->plr.y += all->plr.dirY * 0.5;
		}
}

void move_back(t_all *all)
{
  if (all->only_m[(int)(all->plr.y - all->plr.dirY)][(int)(all->plr.x - all->plr.dirX)] == '0')
		{
			all->plr.x -= all->plr.dirX * 0.5;
			all->plr.y -= all->plr.dirY * 0.5;
		}
}

void rotate_l(t_all *all)
{
    double oldDirX;
    double oldPlaneX;
    double rotSpeed;
    
    rotSpeed = 0.05; 
    oldDirX = all->plr.dirX;
		all->plr.dirX = all->plr.dirX * cos(-rotSpeed) - all->plr.dirY * sin(-rotSpeed);
		all->plr.dirY = oldDirX * sin(-rotSpeed) + all->plr.dirY * cos(-rotSpeed);
		oldPlaneX = all->plr.planeX;
		all->plr.planeX = all->plr.planeX * cos(-rotSpeed) - all->plr.planeY * sin(-rotSpeed);
		all->plr.planeY = oldPlaneX * sin(-rotSpeed) + all->plr.planeY * cos(-rotSpeed);
}

void rotate_r(t_all *all)
{
    double oldDirX;
    double oldPlaneX;
    double rotSpeed;
    
    rotSpeed = 0.05; 
    oldDirX = all->plr.dirX;
		all->plr.dirX = all->plr.dirX * cos(rotSpeed) - all->plr.dirY * sin(rotSpeed);
		all->plr.dirY = oldDirX * sin(rotSpeed) + all->plr.dirY * cos(rotSpeed);
		oldPlaneX = all->plr.planeX;
		all->plr.planeX = all->plr.planeX * cos(rotSpeed) - all->plr.planeY * sin(rotSpeed);
		all->plr.planeY = oldPlaneX * sin(rotSpeed) + all->plr.planeY * cos(rotSpeed);
}

int key_press(int key, t_all *all)
 {
	if (key == 13)
    move_forward(all);
	if (key == 1)
    move_back(all);
	if (key == 0)
    rotate_l(all);
	if (key == 2)
     rotate_r(all);
	if (key == 53)
		exit(0);
	return(0);
 }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void             print_map(t_all *all)
{
    all->win.mlx = mlx_init();
    all->win.win = mlx_new_window(all->win.mlx, all->rend.x, all->rend.y, "Cub3D");
   // all->img.img = mlx_new_image(all->win.mlx, all->rend.x, all->rend.y);
  //  all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length,
   //                              &all->img.endian);
    get_data_tex(all);
    newcub(all);
    mlx_hook(all->win.win, 2, 0, key_press, all);
    mlx_hook(all->win.win, 17, 0, ft_close, all);
    mlx_loop_hook(all->win.mlx, (newcub), all);
    mlx_loop(all->win.mlx);
}