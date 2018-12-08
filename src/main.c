/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 16:53:00 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/12 00:08:33 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*void	init_hooks(t_fractal *win, int track_mouse)
{
	mlx_do_key_autorepeatoff(win->mlx);
	mlx_hook(win->ptr, 2, 0, key_press_hook, win);
	mlx_hook(win->ptr, 3, 0, key_release_hook, win);
	mlx_hook(win->ptr, 4, 0, mouse_press_hook, win);
	mlx_hook(win->ptr, 5, 0, mouse_release_hook, win);
//	if (track_mouse)
		mlx_hook(win->ptr, 6, 0, motion_hook, win);
	mlx_hook(win->ptr, 12, 0, expose_hook, win);
	mlx_hook(win->ptr, 17, 0, exit_hook, win);
	mlx_loop_hook(win->mlx, loop_hook, win);
}
*/
void	clear_image(t_fractal *fractal)
{
	VAR(t_img*, img, fractal->img);
	ft_bzero(img, sizeof(t_img));
	img->ptr = mlx_new_image(fractal->mlx, WINX, WINY);
	img->pixels = (int *)mlx_get_data_addr(img->ptr, &img->bpp,
			&img->size_line, &img->endian);
}

void	image_init(t_fractal *fractal)
{
	VAR(t_img*, new, (t_img *)ft_memalloc(sizeof(t_img)));
	if (!new)
	{
		ft_printf("Failed to allocate memory for image pointer.\n");
		exit(0);
//		memdel_and_exit(fractal);
	}
	fractal->img = new;
	clear_image(fractal);
}


void	image_put(t_fractal *fractal)
{
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img->ptr, 0, 0);
	mlx_destroy_image(fractal->mlx, fractal->img->ptr);
	clear_image(fractal);
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	int i = 0;

	i = (x + y * img->size_line / sizeof(int));
	img->pixels[i] = color;
}


t_fractal		*init_fractal(char *title)
{
	// Allocates memory the size of a t_fractal struct that contains a
	// void *mlx, void *win, and a pointer to the t_img struct, which 
	// contains a void *ptr, and int array of pixels, an int for bit per pixel,
	// and int for the size of the line, and an int that represents the endian
	t_fractal* fractal = (t_fractal *)ft_memalloc(sizeof(t_fractal));

	fractal->mlx = mlx_init();
	fractal->win = mlx_new_window(fractal->mlx, WINX, WINY, title);
	// could put protection here in case either prev function fails
	image_init(fractal);
	return (fractal);
}

void		build_fractal()
{
	t_fractal* julia = init_fractal("Julia");
	int x = -1;
	int y = -1;
	int i = 0;
	long double zx = 0;
	long double zy = 0;
	int color = 0;
	int max_iter = 256;
	int move_x = 0;
	int move_y = 0;
	double c_x = -.7;
	double c_y = .27015;
	int zoom = 1;
	long double tmp;
	
	while (++y < WINY)
	{
		x = -1;
		while (++x < WINX)
		{
			zx = 1.5 * (x - WINX / 2) / (.5 * zoom * WINX) + move_x;
			zy = (y - WINY / 2) / (.5 * zoom * WINY) + move_y;
			while (zx * zx + zy * zy < 4 && ++i < max_iter)
			{
				tmp = zx * zx - zy * zy + c_x;
				zy = 2 * zx * zy + c_y;
				zx = tmp;
				// or = zx;
				// oi = zy;
				// zx = tmp * tmp + oi * oi + 0;
				// zy = 2 * tmp * oi - 0;
			}
			// color = R | G | B
			color = ((i % 256) << 16 | (i * i % 256) << 8 | (255 - i) % 256);
			img_pixel_put(julia->img, x, y, color);
			i = 0;
		}
	}
	mlx_put_image_to_window(julia->mlx, julia->win, julia->img->ptr, 0, 0);
	mlx_destroy_image(julia->mlx, julia->img->ptr);
	clear_image(julia);
//	init_hooks(julia);
	mlx_loop(julia->mlx);

}

int			main(int ac, char **av)
{
	// VAR(t_list*, fractal_list, NULL);
	// fractal_select(&fractal_list);
	build_fractal(/*fractal_List*/);
	//list delete;
	return (0);
}
