#include "cub3d.h"

t_play  init_t_play(t_data *d)
{
    t_play  p;

    p.posx = d->pos[1];
    p.posy = d->pos[0];
    p = get_dir_x_y(d->orientation, p);
    p.planex = 0;
    p.planey = 0.66; // 66 ou 90 degres? ----> voir le rendue;
    p.time = 0;
    p.oldtime = 0;
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

void   raycast_loop(t_play *p, t_data *d, int w, int h)
{
    int x;
    int W;
    int b;

    W = w * 4;
    b = 32;
    x = 0;
    while (1)
    {
        while (x < w)
        {
            p->camerax = 2 * x / (double)w - 1;
            p->raydirx = p->dirx + p->planex * p->camerax;
            p->raydiry = p->diry + p->planey * p->camerax;
            p->mapx = (int)p->posx;
            p->mapy = (int)p->posy;
            p->deltadistx = fabs(1 / p->raydirx);
            p->deltadisty = fabs(1 / p->raydiry);  // verifier si la division par 0 est possible (pour les x aussi)
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
                if (d->map[p->mapy][p->mapx] > 0)
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
            if (d->map[p->mapy][p->mapx])
                p->color = 0x00FF0000; // couleur --> rouge
            if (p->side == 1)
                p->color = p->color / 2;
            verline(x, p);
            x++;
            printf("x == %d\n", x);
        }
        mlx_loop(p->mlx);
//        x = 0;

    }
}

void    verline(int x, t_play *p)
{
    while (p->drawstart < p->drawend)
        mlx_pixel_put(p->mlx, p->win, x, p->drawstart++, p->color);
}