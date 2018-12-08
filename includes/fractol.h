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

# define GRID 30
# define HEIGHT 3

# define ALPHA params->alpha
# define BETA params->beta
# define GAMMA params->gamma
# define DEG (M_PI / 180 * 5)
# define INV_FILE "unable to read file"
# define ARRAY "input map does not exist or is not valid"
# define KMDB(x) ft_printf("HERE %d\n", x);
# define WINX 1300
# define WINY 1300

// JULIA DEFAULTS AND MACROS
# define DCX -.7
# define DCY .27015
# define DMI 512

# define ZX julia->zx
# define ZY julia->zy
# define CX julia->cx
# define CY julia->cy
# define TMP julia->tmp
# define JI julia->max_iter



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

/*
**  Hook functions to handle user controls for wireframe viewing
*/

/*int					my_key_funct(int keycode, t_param *params);
int					my_expose_funct(t_param *params);
*/
/*
**  Functions for handling images.
*/

/*void				image_init(t_param *params);
void				image_put(t_param *params);
void				img_pixel_put(t_img *img, int x, int y, int color);
char				*wf_print_legend(t_param *params, char *path, char bottom);
*/
#endif
