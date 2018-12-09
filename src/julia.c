#include "fractol.h"



t_julia		*init_julia()
{
	t_julia	*julia = (t_julia *)ft_memalloc(sizeof(t_julia));
	ZX = 0;
	ZY = 0;
	CX = DCX;
	CY = DCY;
	JI = DMI;
	julia->move_x = 0;
	julia->move_y = 0;
	julia->zoom = 1;
    julia->threshold = 4.0;
    julia->color = 0;
    // julia->color_funcs = (void **)ft_memalloc(sizeof(void *) * 3);
    // julia->color_funcs[0] = &color1;
    // julia->color_funcs[1] = &color2;
    // julia->color_funcs[2] = &color3;

	return (julia);
}

void        build_julia(t_fractal *fractal)
{
    t_julia *julia = (t_julia *)fractal->algo;
	int x = -1;
	int y = -1;
	int i = 0;
	julia->win_x = MAINWINX;
	julia->win_y = MAINWINY;
	
	while (++y < julia->win_y)
	{
		x = -1;
		while (++x < julia->win_x)
		{
			ZX = 1.5 * (x - julia->win_x / 2) / (.5 * julia->zoom * julia->win_x) + julia->move_x;
			ZY = (y - julia->win_y / 2) / (.5 * julia->zoom * julia->win_y) + julia->move_y;
			while (ZX * ZX + ZY * ZY < julia->threshold && ++i < JI)
			{
				julia->tmp = ZX * ZX - ZY * ZY + CX;
				ZY = 2 * ZX * ZY + CY;
				ZX = julia->tmp;
			}
			// color = R | G | B
            // ft_putnbr(i);
            // ft_putstr(" ");
			julia->color = ((i % 256) << 16 | (i * i % 256) << 8 | (255 - i) % 256);
			img_pixel_put(fractal->img, x, y, julia->color);
			i = 0;
		}
	}
    int left = WINX / 2 - MAINWINX / 2;
	int top = WINY / 2 - MAINWINY / 2;
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img->ptr, left, top);
	mlx_destroy_image(fractal->mlx, fractal->img->ptr);
    clear_image(fractal);
}