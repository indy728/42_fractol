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
	VAR(int, i, 0);
	i = (x + y * img->size_line / sizeof(int));
	img->pixels[i] = color;
}

t_fractal		*init_fractal(char *title)
{
	VAR(t_fractal*, fractal, (t_fractal *)ft_memalloc(sizeof(t_fractal)));
	fractal->mlx = mlx_init();
	fractal->win = mlx_new_window(fractal->mlx, WINX, WINY, title);
	image_init(fractal);
	return (fractal);
}

void		build_fractal()
{
	VAR(t_fractal*, julia, init_fractal("Julia"));
	VAR(int, x, -1);
	VAR(int, y, -1);
	VAR(int, i, 0);
	VAR(long double, nr, 0);
	VAR(long double, or, 0);
	VAR(long double, ni, 0);
	VAR(long double, oi, 0);
	VAR(int, color, 0);
	while (++y < WINY)
	{
		x = -1;
		while (++x < WINX)
		{
			nr = 1.5 * (x - WINX / 2) / (.5 * WINX);
			ni = (y - WINY / 2) / (.5 * WINY);
			while (++i < 500)
			{
				or = nr;
				oi = ni;
				nr = or * or + oi * oi + 0;
				ni = 2 * or * oi - 0;
				if ((nr * nr + ni * ni) > 4)
					break ;
			}
			color = ((i % 256) << 8 | (i * i % 256) << 16 | (300 - i) % 256);
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
