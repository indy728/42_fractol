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

// static void	color_swap(int keycode, t_param *params)
// {
// 	if (keycode == ONE)
// 		get_color_scheme(params, 0);
// 	if (keycode == TWO)
// 		get_color_scheme(params, 1);
// 	if (keycode == THREE)
// 		get_color_scheme(params, 2);
// 	if (keycode == FOUR)
// 		get_color_scheme(params, 3);
// 	if (keycode == FIVE)
// 		get_color_scheme(params, 4);
// 	if (keycode == SIX)
// 		get_color_scheme(params, 5);
// 	if (keycode == SEVEN)
// 		get_color_scheme(params, 6);
// 	if (keycode == EIGHT)
// 		get_color_scheme(params, 7);
// 	if (keycode == NINE)
// 		get_color_scheme(params, 8);
// }

// static void	translate(int keycode, t_param *params)
// {
// 	int x;

// 	x = params->grid_size;
// 	if (keycode == LEFT || keycode == RIGHT)
// 		params->startx += (keycode == LEFT) ? -1 * x : x;
// 	else
// 		params->starty += (keycode == UP) ? -1 * x : x;
// }

// static void	key_ops(int keycode, t_param *params)
// {
// 	if (keycode == COMMA || keycode == ELL)
// 		params->beta += (keycode == ELL ? DEG : -1 * DEG);
// 	if (keycode == POINT || keycode == SEMI)
// 		params->alpha += (keycode == POINT ? DEG : -1 * DEG);
// 	if (keycode == SLASH || keycode == APOS)
// 		GAMMA += (keycode == SLASH ? DEG : -1 * DEG);
// 	if (LEFT <= keycode && keycode <= UP)
// 		translate(keycode, params);
// 	if (keycode == PLUS || keycode == MINUS)
// 		params->height += (keycode == PLUS ? 1 : -1);
// 	if (keycode == RBRACK || keycode == LBRACK)
// 		params->grid_size += (keycode == RBRACK ? 1 : -1);
// 	if (keycode == NP_CLEAR || keycode == NP_SEVEN)
// 		color_shift(keycode, &params->rgb->rmax);
// 	if (keycode == NP_ONE || keycode == NP_FOUR)
// 		color_shift(keycode, &params->rgb->rmin);
// 	if (keycode == NP_EQUALS || keycode == NP_EIGHT)
// 		color_shift(keycode, &params->rgb->gmax);
// 	if (keycode == NP_FIVE || keycode == NP_TWO)
// 		color_shift(keycode, &params->rgb->gmin);
// 	if (keycode == NP_SLASH || keycode == NP_NINE)
// 		color_shift(keycode, &params->rgb->bmax);
// 	if (keycode == NP_SIX || keycode == NP_THREE)
// 		color_shift(keycode, &params->rgb->bmin);
// }



void		destroy_fractal_img(t_fractal *fractal)
{
	t_img 	*img = fractal->img;

	free(img->ptr);
	free(img->pixels);
	free(fractal->img);
}

void		quit_fractal(t_fractal *fractal)
{
	destroy_fractal_img(fractal);
	mlx_destroy_window(fractal->mlx, fractal->win);
	ft_putstr("ESC: Ending program.\n");
	free(fractal);
	exit(1);
}

t_fractal		*init_fractal(char *title, void *(*algo)(), void (*build)(), int (*key_funct)())
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
	fractal->init = algo;
	fractal->type = fractal->init();
	fractal->build = build;
	fractal->key_funct = key_funct;
	return (fractal);
}

void		build_fractal(char *title, void *(*algo)(), void (*build)(), int (*key_funct)())
{
	t_fractal	*fractal = init_fractal(title, algo, build, key_funct);
	
	fractal->build(fractal);
	init_hooks(fractal, 1);
	mlx_loop(fractal->mlx);
}

int			main(int ac, char **av)
{
	// VAR(t_list*, fractal_list, NULL);
	// fractal_select(&fractal_list);
	build_fractal("Julia", (void *)&init_julia, &build_julia, &julia_key_funct);
	//list delete;
	return (0);
}
