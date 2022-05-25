#include "cub3d.h"
#include <sys/time.h>

t_play  init_t_play(t_data *d)
{
    t_play  p;

    p.posx = d->pos[1];
    p.posy = d->pos[0];
   // p = get_dir_x_y(d->orientation, p);
    p.dirx = -1;
    p.diry = 0;
    p.planex = 0;
    p.planey = 0.66; // 66 ou 90 degres? ----> voir le rendue;
    p.time = actual_time();
    p.oldtime = p.time;
    p.map = d->map;
    return (p);
}

t_play  get_dir_x_y(char c, t_play p)
{
   if (c == 'N')
    {
        p.dirx = 0;
        p.diry = 1;
    }
    if (c == 'S')
    {
        p.dirx = 0;
        p.diry = -1;
    }
   if (c == 'E')
    {
        p.dirx = 1;
        p.diry = 0;
    }
   if (c == 'W')
    {
        p.dirx = -1;
        p.diry = 0;
    }
    return (p);
}

/*
void   raycast_loop(t_play *p, int w, int h)
{
    int W;
    int b;

    W = w * 4;
    b = 32;
    p->x = 0;
        p->x = 0;
        while (p->x < w)
        {
            p->camerax = 2 * p->x / (double)w - 1;
            p->raydirx = p->dirx + p->planex * p->camerax;
            p->raydiry = p->diry + p->planey * p->camerax;
            p->mapx = (int)p->posx;
            p->mapy = (int)p->posy;
            p->deltadistx = (p->raydirx == 0) ? 1e30 : fabs(1 / p->raydirx);
            p->deltadisty = (p->raydiry == 0) ? 1e30 : fabs(1 / p->raydiry);  // verifier si la division par 0 est possible (pour les x aussi)
            p->hit = 0;
            if (p->raydirx < 0)
            {
                p->stepx = -1;
                p->sidedistx = (p->posx - p->mapx) * p->deltadistx;
            }
            else
            {
                p->stepx = 1;
                p->sidedistx = (p->mapx + 1 - p->posx) * p->deltadistx;
            }
            if (p->raydiry < 0)
            {
                p->stepy = -1;
                p->sidedisty = (p->posy - p->mapy) * p->deltadisty;
            }
            else
            {
                p->stepy = 1;
                p->sidedisty = (p->mapy + 1 - p->posy) * p->deltadisty;
            }
            while (p->hit == 0)
            {
                if (p->sidedistx < p->sidedisty)
                {
                    p->sidedistx += p->deltadistx;
                    p->mapx += p->stepx;
                    p->side = 0;
                }
                else
                {
                    p->sidedisty += p->deltadisty;
                    p->mapy += p->stepy;
                    p->side = 1;
                }
                if (p->map[p->mapy][p->mapx] != 0)
                    p->hit = 1;
            }
            if (p->side == 0)
                p->perpwalldist = (p->sidedistx - p->deltadistx);
            else
                p->perpwalldist = (p->sidedisty - p->deltadisty);
            p->lineheight = (int)(h / p->perpwalldist);
            p->drawstart = -p->lineheight / 2 + h / 2;
            if (p->drawstart < 0)
                p->drawstart = 0;
            p->drawend = p->lineheight / 2 + h / 2;
            if (p->drawend >= h)
                p->drawend = h - 1;
            if (p->map[p->mapy][p->mapx])
                p->color = 0x00FF0000; // couleur --> rouge
//            if (p->side == 1)
                p->color = p->color / 2;
            verline(p->x, p);
            p->x++;
        }
       p->oldtime = p->time;
       p->time = actual_time();
       printf("%f\n", p->time - p->oldtime);
       p->frametime = 100.0/1000;
       p->movespeed = p->frametime * 10;
       p->rotspeed = p->frametime * 3;
    mlx_hook(p->win, 2, 1L<<0, readkeys, p);
}
*/

void    verline(int x, t_play *p)
{
    while (p->drawstart < p->drawend)
        mlx_pixel_put(p->mlx, p->win, x, p->drawstart++, p->color);
}

double	actual_time(void)
{
	double  		time;
	struct timeval	tm;

	gettimeofday(&tm, NULL);
	time = (tm.tv_sec * 1000) + (tm.tv_usec / 1000);
	return (time);
}


void   raycast_loop(t_play *p, int w, int h)
{
    int x;

    x = 0;
    while (x++ < w)
    {
        p->camerax = 2 * x / (double)(w) - 1; //x-coordinate in camera space
        p->raydirx = p->dirx + p->planex * p->camerax;
        p->raydiry = p->diry + p->planey * p->camerax;
        p->mapx = (int)(p->posx);
        p->mapy = (int)(p->posy);
        p->deltadistx = (p->raydirx == 0) ? 1e30 : fabs(1 / p->raydirx);
        p->deltadisty = (p->raydiry == 0) ? 1e30 : fabs(1 / p->raydiry);
        p->hit = 0; //was there a wall hit?
      if (p->raydirx < 0)
      {
        p->stepx = -1;
        p->sidedistx = (p->posx - p->mapx) * p->deltadistx;
      }
      else
      {
        p->stepx = 1;
        p->sidedistx = (p->mapx + 1.0 - p->posx) * p->deltadistx;
      }
      if (p->raydiry < 0)
      {
        p->stepy = -1;
        p->sidedisty = (p->posy - p->mapy) * p->deltadisty;
      }
      else
      {
        p->stepy = 1;
        p->sidedisty = (p->mapy + 1.0 - p->posy) * p->deltadisty;
      }
      while (p->hit == 0)
      {
        if (p->sidedistx < p->sidedisty)
        {
          p->sidedistx += p->deltadistx;
          p->mapx += p->stepx;
          p->side = 0;
        }
        else
        {
          p->sidedisty += p->deltadisty;
          p->mapy += p->stepy;
          p->side = 1;
        }
        if (p->map[p->mapy][p->mapx] != '0')
            p->hit = 1;
        if (p->side == 0)
            p->perpwalldist = (p->sidedistx - p->deltadistx);
        else
            p->perpwalldist = (p->sidedisty - p->deltadisty);
        p->lineheight = (int)(h / p->perpwalldist);
        p->drawstart = -p->lineheight / 2 + h / 2;
        if (p->drawstart < 0)
            p->drawstart = 0;
        p->drawend = p->lineheight / 2 + h / 2;
        if(p->drawend >= h)
            p->drawend = h - 1;
      }
        p->color = 0x00FF0000;
        p->color = p->color / 2;
        verline(x, p);
    }
        p->movespeed = 0.5;
        p->rotspeed = 0.2;
    	mlx_hook(p->win, 2, 1L<<0, readkeys, p);
    	mlx_loop(p->mlx);
}

int    readkeys(int keys, t_play *p)
{
    mlx_clear_window(p->mlx, p->win);
    printf("pos[%f][%f]\n", p->posy, p->posx);
    if (keys == 126)
    {
        if (p->map[(int)(p->posy + p->diry * p->movespeed)][(int)(p->posx)] == '0')
            p->posy += p->diry * p->movespeed;      
        if (p->map[(int)(p->posy)][(int)(p->posx + p->dirx * p->movespeed)] == '0')
            p->posx += p->dirx * p->movespeed;
    raycast_loop(p, 400, 200);
    }
    if (keys == 125)
    {
        if (p->map[(int)(p->posy - p->diry * p->movespeed)][(int)(p->posx)] == '0')
            p->posy -= p->diry * p->movespeed;
        if (p->map[(int)(p->posy)][(int)(p->posx - p->dirx * p->movespeed)] == '0')
            p->posx -= p->dirx * p->movespeed;
    raycast_loop(p, 400, 200);
    }
    if (keys == 124)
    {
        p->olddirx = p->dirx;
        p->dirx = p->dirx * cos(-p->rotspeed) - p->diry * sin(-p->rotspeed);
        p->diry = p->olddirx * sin(-p->rotspeed) + p->diry * cos(-p->rotspeed);
        p->oldplanx = p->planex;
        p->planex = p->planex * cos(-p->rotspeed) - p->planey * sin(-p->rotspeed);
        p->planey = p->oldplanx * sin(-p->rotspeed) + p->planey * cos(-p->rotspeed);
    raycast_loop(p, 400, 200);
    }
    if (keys == 123)
    {
        p->olddirx = p->dirx;
        p->dirx = p->dirx * cos(p->rotspeed) - p->diry * sin(p->rotspeed);
        p->diry = p->olddirx * sin(p->rotspeed) + p->diry * cos(p->rotspeed);
        p->oldplanx = p->planex;
        p->planex = p->planex * cos(p->rotspeed) - p->planey * sin(p->rotspeed);
        p->planey = p->oldplanx * sin(p->rotspeed) + p->planey * cos(p->rotspeed);
    raycast_loop(p, 400, 200);
    }
//    raycast_loop(p, 400, 200);
    return (0);
}