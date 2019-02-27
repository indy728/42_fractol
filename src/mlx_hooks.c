#include "fractol.h"

int		loop_hook(t_fractal *fractal)
{
	build_julia(fractal);
	return (0);
}

void	init_hooks(t_fractal *fractal, int track_mouse)
{
	mlx_do_key_autorepeatoff(fractal->mlx);
	mlx_hook(fractal->win, 2, 0, fractal->key_funct, fractal);
	// mlx_hook(fractal->win, 3, 0, key_release_hook, fractal);
// 	mlx_hook(fractal->ptr, 4, 0, mouse_press_hook, fractal);
// 	mlx_hook(fractal->ptr, 5, 0, mouse_release_hook, fractal);
// //	if (track_mouse)
// 		mlx_hook(fractal->ptr, 6, 0, motion_hook, fractal);
// 	mlx_hook(fractal->ptr, 12, 0, expose_hook, fractal);
// 	mlx_hook(fractal->ptr, 17, 0, exit_hook, fractal);
	mlx_loop_hook(fractal->mlx, loop_hook, fractal);
}