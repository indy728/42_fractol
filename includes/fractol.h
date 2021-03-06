/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmurray <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 18:43:47 by kmurray           #+#    #+#             */
/*   Updated: 2017/09/11 23:31:27 by kmurray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <pthread.h>

# define GRID 30
# define HEIGHT 3

# define ALPHA params->alpha
# define BETA params->beta
# define GAMMA params->gamma
# define DEG (M_PI / 180 * 5)
# define INV_FILE "unable to read file"
# define ARRAY "input map does not exist or is not valid"
# define KMDB(x) ft_printf("HERE %d\n", x);
# define WINX 1440
# define WINY 928
# define CORES 4
# define THREADS 8
# define MAXTHREADS (CORES * THREADS)

# define MAINWINX 800
# define MAINWINY 576
// JULIA DEFAULTS AND MACROS
# define DCX -.7
# define DCY .27015
# define DMI 512
# define CX julia->cx
# define CY julia->cy

# define ZX params->zx
# define ZY params->zy
# define TMP params->tmp

# define JI julia->max_iter

typedef struct		s_julia
{
	
	double			cx;
	double			cy;
	int				max_iter;
	int				move_x;
	int				move_y;
	float			zoom;
	int				color;
	int				win_x;
	int				win_y;
	float			threshold;
	int				(*key_funct)();
	int				mod;
	int				step;
	int				*steps;
	// unsigned int	(*color_funcs)();
}					t_julia;

typedef struct		s_img
{
	void			*ptr;
	int				*pixels;
	int				bpp;
	int				size_line;
	int				endian;
}					t_img;

typedef struct		s_fractal
{
	void			*mlx;
	void			*win;
	t_img			*img;
	void			*type;
	void			*(*init)();
	void			(*build)();
	int				(*key_funct)();
}					t_fractal;

typedef enum		e_keys
{
	A, S, D, F, H1, G, ZED, X, C, V, B = 11, Q, W, E, R, Y, T,
	ONE, TWO, THREE, FOUR, SIX, FIVE, PLUS, NINE, SEVEN, MINUS, EIGHT, ZERO,
	RBRACK, O, U, LBRACK, I, P, RETURN, ELL, JAY, APOS, K, SEMI,
	BACKSLASH, COMMA, SLASH, N, M, POINT, TAB, SPACE, TILDE, DEL, ESC = 53,
	NP_CLEAR = 71, NP_SLASH = 75, NP_EQUALS = 81,
	NP_ZERO, NP_ONE, NP_TWO, NP_THREE, NP_FOUR, NP_FIVE, NP_SIX,
	NP_SEVEN, NP_EIGHT = 91, NP_NINE,
	HOME = 115, PG_UP, FN_DEL, END = 119, PG_DOWN = 121,
	LEFT = 123, RIGHT, DOWN, UP,
	LCNTRL = 256, LSHIFT, RSHIFT, LCMD, RCMD, LOPT, ROPT, RCNTRL = 269,
	FN = 279
}					t_keys;

// unsigned int color1(int i);
// unsigned int color2(int i);
// unsigned int color3(int i);

// JULIA
void				build_julia(t_fractal *fractal);
t_julia				*init_julia();
int					julia_key_funct(int keycode, t_fractal *fractals);
/*
**  Hook functions to handle user controls for wireframe viewing
*/

void				init_hooks(t_fractal *fractal, int track_mouse);
int					loop_hook(t_fractal *fractal);

void		quit_fractal(t_fractal *fractal);
int			my_key_funct(int keycode, t_fractal *fractal);

/*int					my_key_funct(int keycode, t_param *params);
int					my_expose_funct(t_param *params);
*/
/*
**  Functions for handling images.
*/

void				image_init(t_fractal *fractal);
void				image_put(t_fractal *fractal);
void				img_pixel_put(t_img *img, int x, int y, int color);
void				clear_image(t_fractal *fractal);


// char				*wf_print_legend(t_param *params, char *path, char bottom);

#endif
