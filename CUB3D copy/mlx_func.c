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

int newcub(t_all *all)
{
  double posX = all->plr.x, posY = all->plr.y;  //x and y start position
  double dirX = all->plr.dirX, dirY = all->plr.dirY; //initial direction vector
  double planeX = all->plr.planeX, planeY = all->plr.planeY; //the 2d raycaster version of camera plane
  unsigned int color;
  int buf[all->rend.y][all->rend.x];
  double Zbuff[all->rend.x];
  int numSprites = all->sprite.count;
  double stance[numSprites];
  double spriteOrder[numSprites];
  double spriteDistance[numSprites];
  int texHeight = 64;
  int texWidth = 64;

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
      int side; //was a NS or a Eall->rend.xwall hit?

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
        if(all->only_m[mapY][mapX] =='1')
            hit = 1;
      }

      //Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
      if(side == 0)
        perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
      else
        perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

      //Calculate height of line to draall->rend.xon screen
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
      int texX;
      int texY;
      double step;
      int g = 0;
      if (side == 0)
        { 
          if (stepX > 0)
            {
        texX = all->tex[3].tex_w - (int)(wallX * all->tex[3].tex_w) - 1;
          step = 1.0 * all->tex[3].tex_w / lineHeight;
          g = 3;
        }
          else
             {
           texX = all->tex[2].tex_w - (int)(wallX * all->tex[2].tex_w) - 1;
           step = 1.0 * all->tex[2].tex_w / lineHeight;
           g = 2;
           }
        }
         
        else
        {
          if (stepY > 0)
            {
        texX = all->tex[1].tex_w - (int)(wallX * all->tex[1].tex_w) - 1;
        step = 1.0 * all->tex[1].tex_w / lineHeight;
        g = 1;
        
      }
          else
            {
        texX = all->tex[0].tex_w - (int)(wallX * all->tex[0].tex_w) - 1;
        step = 1.0 * all->tex[0].tex_w / lineHeight;
        g = 0;
        }
        }

      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
      // Hoall->rend.xmuch to increase the texture coordinate per screen pixel
     //step = 1.0 * 64 / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - all->rend.y / 2 + lineHeight / 2) * step;
      for(int y = drawStart; y < drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        texY = (int)texPos % (all->tex[g].tex_h - 1);
        texPos += step;
        my_mlx_pixel_put(all, x , y, color = get_color(all, texX, texY, g));
      }
    
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      // 
      // 
      Zbuff[x] = perpWallDist;
    }
      for(int i = 0; i < numSprites; i++)
    {
      spriteOrder[i] = i;
     spriteDistance[i] = (pow(posX - all->sprite.buf[i].x, 2) + pow(posY - all->sprite.buf[i].y, 2)); //sqrt not taken, unneeded
   // printf("%f", all->sprite.buf[i].x);
    }
    //  printf("%f", all->sprite.buf[0].x);

   bubbleSort(spriteDistance, spriteOrder, numSprites);
   //quickSort(spriteDistance, 0, numSprites-1);
   int temp = numSprites;
   for(int i = 0; i < ((temp - 1) / 2); i++)
   {
      int t;
      t = spriteDistance[temp - 1];
      spriteDistance[temp - 1] = spriteDistance[i];
      spriteDistance[i] = t;
      temp--;
   }

    //after sorting the sprites, do the projection and draw them
    for(int i = 0; i < numSprites; i++)
    {
      //translate sprite position to relative to camera
      double spriteX = all->sprite.buf[(int)spriteOrder[i]].x - posX;
      double spriteY = all->sprite.buf[(int)spriteOrder[i]].y - posY;
      double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication
      double transformX = invDet * (dirY * spriteX - dirX * spriteY);
      double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])
      int spriteScreenX = (int)((all->rend.x / 2) * (1 + transformX / transformY));

      //parameters for scaling and moving the sprites
      #define uDiv 1
      #define vDiv 1
      #define vMove 0.0
      int vMoveScreen = (int)(vMove / transformY);

      //calculate height of the sprite on screen
      int spriteHeight = abs((int)(all->rend.y / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + all->rend.y / 2 + vMoveScreen;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + all->rend.y / 2 + vMoveScreen;
      if(drawEndY >= all->rend.y) drawEndY = all->rend.y - 1;

      //calculate width of the sprite
      int spriteWidth = abs( (int) (all->rend.y / (transformY))) / uDiv;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= all->rend.x) drawEndX = all->rend.x - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
        if(transformY > 0 && stripe > 0 && stripe < all->rend.x && transformY < Zbuff[stripe])
        for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        {
          int d = (y-vMoveScreen) * 256 - all->rend.y * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          int texY = ((d * texHeight) / spriteHeight) / 256;
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
    all->img.img = mlx_new_image(all->win.mlx, all->rend.x, all->rend.y);
    all->img.addr = mlx_get_data_addr(all->img.img, &all->img.bits_per_pixel, &all->img.line_length,
                                 &all->img.endian);
    get_data_tex(all);
    newcub(all);
    mlx_hook(all->win.win, 2, 0, key_press, all);
    mlx_hook(all->win.win, 17, 0, ft_close, all);
    mlx_loop_hook(all->win.mlx, (newcub), all);
    mlx_loop(all->win.mlx);
}