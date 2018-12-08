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

typedef struct		s_julia
{
	long double 	zx;
	long double 	zy;
	long double 	tmp;
	double			cx;
	double			cy;
	int				max_iter;
	int				move_x;
	int				move_y;
	int				zoom;
	int				color;
}					t_julia;

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
	return (julia);
}

void		build_fractal()
{
	t_fractal	*fractal = init_fractal("Julia");
	t_julia		*julia = init_julia();
	int x = -1;
	int y = -1;
	int i = 0;
	
	while (++y < WINY)
	{
		x = -1;
		while (++x < WINX)
		{
			ZX = 1.5 * (x - WINX / 2) / (.5 * julia->zoom * WINX) + julia->move_x;
			ZY = (y - WINY / 2) / (.5 * julia->zoom * WINY) + julia->move_y;
			while (ZX * ZX + ZY * ZY < 4 && ++i < JI)
			{
				julia->tmp = ZX * ZX - ZY * ZY + CX;
				ZY = 2 * ZX * ZY + CY;
				ZX = julia->tmp;
			}
			// color = R | G | B
			julia->color = ((i % 256) << 16 | (i * i % 256) << 8 | (255 - i) % 256);
			img_pixel_put(fractal->img, x, y, julia->color);
			i = 0;
		}
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img->ptr, 0, 0);
	mlx_destroy_image(fractal->mlx, fractal->img->ptr);
	clear_image(fractal);
//	init_hooks(fractal);
	mlx_loop(fractal->mlx);

}

int			main(int ac, char **av)
{
	// VAR(t_list*, fractal_list, NULL);
	// fractal_select(&fractal_list);
	build_fractal(/*fractal_List*/);
	//list delete;
	return (0);
}
