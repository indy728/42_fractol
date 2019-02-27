#include "fractol.h"

int			julia_key_funct(int keycode, t_fractal *fractal)
{
	// key_ops(keycode, params);
	// if (keycode == ZERO)
	// {
	// 	ALPHA = 0;
	// 	BETA = 0;
	// 	GAMMA = 0;
	// }
	// if (ONE <= keycode && keycode <= EIGHT &&
	// 		keycode != PLUS && keycode != MINUS)
	// 	color_swap(keycode, params);
	if (keycode == ESC)
		quit_fractal(fractal);
	t_julia *julia = (t_julia *)fractal->type;
	if (keycode == A)
		CX += .0005;
	if (keycode == D)
		CX -= .0005;
	if (keycode == W)
		CY += .0005;
	if (keycode == S)
		CY -= .0005;
	if (keycode == RBRACK)
		julia->zoom += .1;
	if (keycode == LBRACK)
		julia->zoom -= .1;
	if (keycode == UP)
		julia->move_y += 5;
	if (keycode == DOWN)
		julia->move_y -= 5;
	if (keycode == LEFT)
		julia->move_x += 5;
	if (keycode == RIGHT)
		julia->move_x -= 5;
	if (keycode == PLUS)
		julia->threshold *= 2;
	if (keycode == MINUS)
		julia->threshold /= 2;
	if (keycode == O)
		julia->step = ft_min(7, julia->step + 1);
	if (keycode == ELL)
		julia->step = ft_max(0, julia->step - 1);
	if (keycode == U)
		julia->mod = ft_min(20000, julia->mod * 2);
	if (keycode == JAY)
		julia->mod = ft_max(8, julia->mod / 2);
	return (0);
}