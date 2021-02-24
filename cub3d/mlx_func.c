#include <mlx.h>
#include "parsing.h"
#include "libft/libft.h"
#include <unistd.h>

int		rgb_to_int_f(t_a *a);
int		rgb_to_int_c(t_a *a);

void  get_data_tex(t_a *a)
{
  if (!(a->t[0].i = MXPM(a->win.mlx, a->NO.p, &a->t[0].w, &a->t[0].h)) ||
  !(a->t[0].addr = ADR(a->t[0].i, &a->t[0].bp, &a->t[0].ll, &a->t[0].end)))
    exit (0);
  if (!(a->t[1].i = MXPM(a->win.mlx, a->SO.p, &a->t[1].w, &a->t[1].h)) ||
  !(a->t[1].addr = ADR(a->t[1].i, &a->t[1].bp, &a->t[1].ll, &a->t[1].end)))
      exit (0);
  if (!(a->t[2].i = MXPM(a->win.mlx, a->WE.p, &a->t[2].w, &a->t[2].h)) ||
  !(a->t[2].addr = ADR(a->t[2].i, &a->t[2].bp, &a->t[2].ll, &a->t[2].end)))
    exit (0);
  if (!(a->t[3].i = MXPM(a->win.mlx, a->EA.p, &a->t[3].w, &a->t[3].h)) ||
  !(a->t[3].addr = ADR(a->t[3].i, &a->t[3].bp, &a->t[3].ll, &a->t[3].end)))
    exit (0);
  if (!(a->t[4].i = MXPM(a->win.mlx, a->S.s, &a->t[4].w, &a->t[4].h)) ||
  !(a->t[4].addr = ADR(a->t[4].i, &a->t[4].bp, &a->t[4].ll, &a->t[4].end)))
    exit (0);
}

////////////////////////////////////////////////////////////////
void bubbleSort(double *num, double *s, int size)
{
  int i;
  int j;
  int temp;
  int t;

  i = -1;
  j = (size - 1);
  while (++i < size - 1)
  {
    while (j > i) // для всех элементов после i-ого
    {
      if (num[j] > num[j - 1]) // если текущий элемент меньше предыдущего
      {
        temp = num[j - 1]; // меняем их местами
        num[j - 1] = num[j];
        num[j] = temp;
        t = s[j - 1]; // меняем их местами
       s[j - 1] = s[j];
        s[j] = t;
      }
      j--;
    }
    j = (size - 1);
  }
}

int		ft_close(t_a *a, int win)
{
    if (win == 1)
		mlx_destroy_window(a->win.mlx, a->win.win);
	exit(0);
	return (1);
}

void            my_mlx_pixel_put(t_a *a, int x, int y, int color)
{
    char    *dst;

    dst = a->img.addr + (y * a->img.ll + x * (a->img.bp / 8));
    *(unsigned int*)dst = color;
}

unsigned int            get_color(t_a *a, int x, int y, int i)
{
    char    *dst;
    unsigned int color;

    dst = a->t[i].addr + (y * a->t[i].ll + x * (a->t[i].bp / 8));
    color = *(unsigned int*)dst;
    return (color);
}


void    ft_clean_window(t_a *a, int f, int c)
{
	int	i;
	int	j;

	f = rgb_to_int_f(a);
  c = rgb_to_int_c(a);
	i = -1;
	while(++i < a->rend.y / 2)
	{
		j = -1;
		while (++j < a->rend.x)
			my_mlx_pixel_put(a, j, i, c);
	}
  while(++i < a->rend.y)
	{
		j = -1;
		while (++j < a->rend.x)
			my_mlx_pixel_put(a, j, i, f);
	}
}

void selecter(t_a *a)
{
  a->ray.deltaDistX = fabs(1 / a->p.rpsX);
  a->ray.deltaDistY = fabs(1 / a->p.rpsY);
  a->ray.hit = 0;
  if(a->p.rpsX < 0)
      {
        a->ray.sX = -1;
        a->ray.sideDistX =  (a->p.x - a->ray.mapX) * a->ray.deltaDistX;
      }
      else
      {
        a->ray.sX = 1;
        a->ray.sideDistX = (a->ray.mapX + 1.0 - a->p.x) * a->ray.deltaDistX;
      }
      if(a->p.rpsY < 0)
      {
        a->ray.sY = -1;
        a->ray.sideDistY = (a->p.y- a->ray.mapY) * a->ray.deltaDistY;
      }
      else
      {
        a->ray.sY = 1;
        a->ray.sideDistY = (a->ray.mapY + 1.0 - a->p.y) * a->ray.deltaDistY;
      }
}

void newselector(t_a *a)
{
  while (a->ray.hit == 0)
  {
    //jump to next map square, OR in x-direction, OR in y-direction
    if(a->ray.sideDistX < a->ray.sideDistY)
    {
      a->ray.sideDistX += a->ray.deltaDistX;
      a->ray.mapX += a->ray.sX;
      a->ray.side = 0;
    }
    else
    {
      a->ray.sideDistY += a->ray.deltaDistY;
      a->ray.mapY += a->ray.sY;
      a->ray.side = 1;
    }
    //Check if ray has a->ray.hit a wa
    if(a->only_m[a->ray.mapY][a->ray.mapX] =='1')
        a->ray.hit = 1;
  }
  if(a->ray.side == 0)
    a->ray.wd = (a->ray.mapX - a->p.x + (1 - a->ray.sX) / 2) / a->p.rpsX;
  else
    a->ray.wd = (a->ray.mapY - a->p.y + (1 - a->ray.sY) / 2) / a->p.rpsY;
}

int init(t_a *a, int x)
{
      a->p.cameraX = 2 * x / (double)a->rend.x - 1; //x-coordinate in camera space
      a->p.rpsX = a->p.dirX + a->p.planeX * a->p.cameraX;
      a->p.rpsY = a->p.dirY + a->p.planeY * a->p.cameraX;
      a->ray.mapX = (int)a->p.x;
      a->ray.mapY = (int)a->p.y;
      selecter(a);
      newselector(a);
       a->draw.lhi = (int)(a->rend.y / a->ray.wd);
       a->draw.drawStart = -a->draw.lhi / 2 + a->rend.y / 2;
      if(a->draw.drawStart < 0)
        a->draw.drawStart = 0;
       a->draw.drawEnd = a->draw.lhi / 2 + a->rend.y / 2;
      if(a->draw.drawEnd >= a->rend.y)
        a->draw.drawEnd = a->rend.y - 1;
      if(a->ray.side == 0)
        a->draw.wallX = a->p.y+ a->ray.wd * a->p.rpsY;
      else
        a->draw.wallX = a->p.x + a->ray.wd * a->p.rpsX;
      a->draw.wallX -= floor((a->draw.wallX));
      return (x);
}

int choose_side(t_a *a, int g)
{
  if (a->ray.sX > 0)
  {
    a->draw.texX = a->t[3].w - (int)(a->draw.wallX * (double)a->t[3].w) - 1;
    a->draw.step = 1.0 * a->t[3].w / a->draw.lhi;
    g = 3;
  }
  else
  {
    a->draw.texX = a->t[2].w - (int)(a->draw.wallX * (double)a->t[2].w) - 1;
    a->draw.step  = 1.0 * a->t[2].w / a->draw.lhi;
    g = 2;
  }
  return (g);
}

int   choose_side1(t_a *a, int g)
{
  if (a->ray.sY > 0)
  {
    a->draw.texX = a->t[1].w - (int)(a->draw.wallX * (double)a->t[1].w) - 1;
    a->draw.step  = 1.0 * a->t[1].w / a->draw.lhi;
    g = 1;
  }
  else
  {
    a->draw.texX = a->t[0].w - (int)(a->draw.wallX * (double)a->t[0].w) - 1;
    a->draw.step = 1.0 * a->t[0].w / a->draw.lhi;
    g = 0;
  }
  return (g);
}

void  draw_walls(t_a *a, int x, int g)
{
  unsigned int color;
  double texPos;
  
  texPos = (a->draw.drawStart - a->rend.y / 2 + a->draw.lhi / 2) * a->draw.step;
  for(int y = a->draw.drawStart; y < a->draw.drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        a->draw.texY = (int)texPos % (a->t[g].h - 1);
        texPos += a->draw.step;
        color = get_color(a, a->draw.texX, a->draw.texY, g);
        my_mlx_pixel_put(a, x , y, color);
      }
}

void spr_init(t_a *a, double spriteOrder[a->s.count], int i)
{
  a->s.X = a->s.buf[(int)spriteOrder[i]].x - a->p.x;
  a->s.Y = a->s.buf[(int)spriteOrder[i]].y - a->p.y;
  a->s.inv = 1.0 / (a->p.planeX * a->p.dirY - a->p.dirX * a->p.planeY); //required for correct matrix multiplication
  a->s.tranX = a->s.inv * (a->p.dirY * a->s.X - a->p.dirX * a->s.Y);
  a->s.tranY = a->s.inv * (-a->p.planeY * a->s.X + a->p.planeX * a->s.Y); //this is actuay the depth ina->ray.side the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])
  a->s.ScreenX = (int)((a->rend.x / 2) * (1 + a->s.tranX / a->s.tranY));
  a->s.move_s = (int)(0.0 / a->s.tranY);
  a->t[4].h = abs((int)(a->rend.y / (a->s.tranY))) / 1; 
  a->draw.drawStartY = -a->t[4].h / 2 + a->rend.y / 2 + a->s.move_s;
if(a->draw.drawStartY < 0)
  a->draw.drawStartY = 0;
a->draw.drawEndY = a->t[4].h / 2 + a->rend.y / 2 + a->s.move_s;
if(a->draw.drawEndY >= a->rend.y)
  a->draw.drawEndY = a->rend.y - 1;

//calculate width of the sprite
a->s.w = abs( (int) (a->rend.y / (a->s.tranY))) / 1;
  a->draw.drawStartX = -a->s.w / 2 + a->s.ScreenX;
if(a->draw.drawStartX < 0)
  a->draw.drawStartX = 0;
a->draw.drawEndX = a->s.w / 2 + a->s.ScreenX;
if(a->draw.drawEndX >= a->rend.x)
  a->draw.drawEndX = a->rend.x - 1;
}

void draw_spr(t_a *a, double Zbuff[a->rend.x], int y, int stripe)
{
  unsigned int color;

  stripe = a->draw.drawStartX;
  y = a->draw.drawStartY;
  while(stripe < a->draw.drawEndX)
  {
    a->draw.texX = (int)(256 * (stripe - (-a->s.w / 2 + a->s.ScreenX))); 
    a->draw.texX = (int)(a->draw.texX * a->t[4].w / a->s.w / 256);
    if (a->s.tranY > 0 && stripe > 0 && stripe < a->rend.x
    && a->s.tranY < Zbuff[stripe])
    while(y < a->draw.drawEndY) //for every pixel of the current stripe
    {
      a->s.d = (y-a->s.move_s) * 256 - a->rend.y * 128; //256 and 128 factors to avoid floats
      a->s.d += a->t[4].h * 128;
      a->draw.texY = ((a->s.d * a->t[4].w) / a->t[4].h) / 256;
      //Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
      color = get_color(a, a->draw.texX, a->draw.texY, 4);
        if((color & 0x00FFFFFF) != 0)  //paint pixel if it isn't black, black is the invisible color
        my_mlx_pixel_put(a, stripe, y, color);
        y++;
    }
    y = a->draw.drawStartY;
    stripe++;
  }
}

 void ft_sprites(t_a *a, double Zbuff[a->rend.x])
 {
   double spriteOrder[a->s.count];// массив для спрайтов
   double spriteDistance[a->s.count];
   int i;
  
    i = -1;
    while(++i < a->s.count)
    {
      spriteOrder[i] = i;
      spriteDistance[i] = pow (a->p.x - a->s.buf[i].x, 2);
      spriteDistance[i] += pow(a->p.y - a->s.buf[i].y, 2); //sqrt not taken, unneeded
    }
  bubbleSort(spriteDistance, spriteOrder, a->s.count);
  i = -1;
  while(++i < a->s.count)
  { 
      spr_init(a, spriteOrder, i);
      draw_spr(a, Zbuff, 0 ,0);
  }
}

int newcub(t_a *a)
{
  double Zbuff[a->rend.x];
  int g;

  g = 0;
  a->img.img = mlx_new_image(a->win.mlx, a->rend.x, a->rend.y);
  a->img.addr = ADR(a->img.img, &a->img.bp, &a->img.ll,
                                 &a->img.end);
  ft_clean_window(a, 0, 0);
  for(int x = 0; x < a->rend.x; x++)
  {
    x = init(a, x);

    if (a->ray.side == 0)
      g = choose_side(a, g);
    else
      g = choose_side1(a, g);
    draw_walls(a, x, g);
      Zbuff[x] = a->ray.wd;
  }
    ft_sprites(a, Zbuff);
  mlx_put_image_to_window(a->win.mlx, a->win.win, a->img.img, 0, 0);
  return (1);   
}
    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void move_forward(t_a *a)
{
  if (a->only_m[(int)(a->p.y + a->p.dirY )][(int)(a->p.x + a->p.dirX)] == '0')
		{
			a->p.x += a->p.dirX * 0.5;
			a->p.y += a->p.dirY * 0.5;
		}
}

void move_back(t_a *a)
{
  if (a->only_m[(int)(a->p.y - a->p.dirY)][(int)(a->p.x - a->p.dirX)] == '0')
		{
			a->p.x -= a->p.dirX * 0.5;
			a->p.y -= a->p.dirY * 0.5;
		}
}

void rotate_l(t_a *a)
{
    double oldDirX;
    double oldPlaneX;
    double rotSpeed;
    
    rotSpeed = 0.05; 
    oldDirX = a->p.dirX;
		a->p.dirX = a->p.dirX * cos(-rotSpeed) - a->p.dirY * sin(-rotSpeed);
		a->p.dirY = oldDirX * sin(-rotSpeed) + a->p.dirY * cos(-rotSpeed);
		oldPlaneX = a->p.planeX;
		a->p.planeX = a->p.planeX * cos(-rotSpeed) - a->p.planeY * sin(-rotSpeed);
		a->p.planeY = oldPlaneX * sin(-rotSpeed) + a->p.planeY * cos(-rotSpeed);
}

void rotate_r(t_a *a)
{
    double oldDirX;
    double oldPlaneX;
    double rotSpeed;
    
    rotSpeed = 0.05; 
    oldDirX = a->p.dirX;
		a->p.dirX = a->p.dirX * cos(rotSpeed) - a->p.dirY * sin(rotSpeed);
		a->p.dirY = oldDirX * sin(rotSpeed) + a->p.dirY * cos(rotSpeed);
		oldPlaneX = a->p.planeX;
		a->p.planeX = a->p.planeX * cos(rotSpeed) - a->p.planeY * sin(rotSpeed);
		a->p.planeY = oldPlaneX * sin(rotSpeed) + a->p.planeY * cos(rotSpeed);
}

int key_press(int key, t_a *a)
 {
	if (key == 13)
    move_forward(a);
	if (key == 1)
    move_back(a);
	if (key == 0)
    rotate_l(a);
	if (key == 2)
     rotate_r(a);
	if (key == 53)
		exit(0);
	return(0);
 }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void             print_map(t_a *a)
{
    a->win.mlx = mlx_init();
    a->win.win = mlx_new_window(a->win.mlx, a->rend.x, a->rend.y, "Cub3D");
    a->img.img = mlx_new_image(a->win.mlx, a->rend.x, a->rend.y);
    a->img.addr = ADR(a->img.img, &a->img.bp, &a->img.ll,
                                 &a->img.end);
    get_data_tex(a);
    newcub(a);
    mlx_hook(a->win.win, 2, 0, key_press, a);
    mlx_hook(a->win.win, 17, 0, ft_close, a);
    mlx_loop_hook(a->win.mlx, (newcub), a);
    mlx_loop(a->win.mlx);
}