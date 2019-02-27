#include "fractol.h"

typedef struct		s_julia_params
{
	long double 	zx;
	long double 	zy;
	long double 	tmp;
}					t_julia_params;

typedef struct	s_thread
{
	t_img		*img;
	int			thread_num;
	struct s_julia_params	*params;
	void		*algo;
}				t_thread;

t_julia_params	*init_julia_params()
{
	t_julia_params	*params = (t_julia_params *)ft_memalloc(sizeof(t_julia_params));
	
	ZX = 0;
	ZY = 0;
	TMP;
	return(params);
}

t_julia		*init_julia()
{
	t_julia	*julia = (t_julia *)ft_memalloc(sizeof(t_julia));
	
	CX = DCX;
	CY = DCY;
	JI = DMI;
	julia->move_x = 0;
	julia->move_y = 0;
	julia->zoom = 1;
    julia->threshold = 4.0;
    julia->color = 0;
	julia->mod = 256;
	julia->step = 2;
	julia->steps = (int *)ft_memalloc(sizeof(int) * 8);
	int dummy[8] = {24, 12, 8, 6, 4, 3, 2, 1};
	int i = -1;
	while (++i < 8)
	{
		julia->steps[i] = dummy[i];
	}

	// julia->shift = 0

	return(julia);
}

unsigned int	julia_color(t_julia *julia, int i)
{
	unsigned int color = 0;
	int shift = 0;

	while (shift < 24)
	{
		color += (i * 42) % julia->mod << shift;
		// shift += julia->step;
		shift += julia->steps[julia->step];
	}
	return (color);
}

void		*julia_runner(void *thread_struct)
{
	int x;
	t_thread	*julia_thread = (t_thread *)thread_struct;
	int		y = julia_thread->thread_num * MAINWINY / MAXTHREADS - 1;
	int		ymax = y + 1 + MAINWINY / MAXTHREADS;
	t_julia	*julia = (t_julia *)(julia_thread->algo);
	t_julia_params *params = julia_thread->params;
	// double tmp;
	int i= 0;

	while (++y < ymax)
	{
		x = -1;
		while (++x < julia->win_x)
		{
			ZX = 1.5 * (x - julia->move_x - julia->win_x / 2) / (.5 * julia->zoom * julia->win_x);
			ZY = (y - julia->move_y - julia->win_y / 2) / (.5 * julia->zoom * julia->win_y);
			while (ZX * ZX + ZY * ZY < julia->threshold && ++i < JI)
			{
				TMP = ZX * ZX - ZY * ZY + CX;
				ZY = 2 * ZX * ZY + CY;
				ZX = TMP;
			}
			// julia_color(julia, i);
			img_pixel_put(julia_thread->img, x, y, julia_color(julia, i));
			i = 0;
		}
	}
	return (0);
}

void        build_julia(t_fractal *fractal)
{
	mlx_clear_window(fractal->mlx, fractal->win);
    t_julia *julia = (t_julia *)fractal->type;
	julia->win_x = MAINWINX;
	julia->win_y = MAINWINY;
	pthread_t threads[MAXTHREADS];
	t_thread julia_threads[MAXTHREADS];
	for (int i = 0 ; i < MAXTHREADS ; i++)
	{
		julia_threads[i].thread_num = i;
		julia_threads[i].img = fractal->img;
		julia_threads[i].params = init_julia_params();
		julia_threads[i].algo = (void *)julia;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&threads[i], &attr, julia_runner, &julia_threads[i]);
	}
	for (int i = 0 ; i < MAXTHREADS ; i++)
	{
		pthread_join(threads[i], NULL);
	}
	
	// while (++y < julia->win_y)
	// {
	// 	x = -1;
	// 	while (++x < julia->win_x)
	// 	{
	// 		ZX = 1.5 * (x - julia->win_x / 2) / (.5 * julia->zoom * julia->win_x) + julia->move_x;
	// 		ZY = (y - julia->win_y / 2) / (.5 * julia->zoom * julia->win_y) + julia->move_y;
	// 		while (ZX * ZX + ZY * ZY < julia->threshold && ++i < JI)
	// 		{
	// 			julia->tmp = ZX * ZX - ZY * ZY + CX;
	// 			ZY = 2 * ZX * ZY + CY;
	// 			ZX = julia->tmp;
	// 		}
	// 		// color = R | G | B
    //         // ft_putnbr(i);
    //         // ft_putstr(" ");
	// 		julia_color(julia, i);
	// 		// julia->color = ((i % 256) << 16 | (i * i % 256) << 8 | (255 - i) % 256);
	// 		// julia->color = (i << 21) | (i << 10) | i * 8
	// 		// julia->color = (i % 128 << 23) | (i % 28 << 21) |
	// 		// (i % 128 << 19) | (i % 28 << 17) |
	// 		// (i % 128 << 15) | (i % 28 << 13) |
	// 		// (i % 128 << 11) | (i % 28 << 9) |
	// 		// (i % 128 << 7) | (i % 28 << 5) |
	// 		// (i % 128 << 3) | i*8;
	// 		// int d = 1024;
	// 		// julia->color = (i % d << 23) | (i % d << 21) |
	// 		// (i % d << 19) | (i % d << 17) |
	// 		// (i % d << 15) | (i % d << 13) |
	// 		// (i % d << 11) | (i % d << 9) |
	// 		// (i % d << 7) | (i % d << 5) |
	// 		// (i % d << 3) | i % d;
	// 		img_pixel_put(fractal->img, x, y, julia->color);
	// 		// if (x == julia->win_x / 2 && !((y - 8) % 18))
	// 		// {
	// 		// 	printf("Thread: %d y == %d, x == %d, i == %d\n", 1, y, x, i);
	// 		// }
	
	// 		i = 0;
	// 	}
	// }
    int left = WINX / 2 - MAINWINX / 2;
	int top = WINY / 2 - MAINWINY / 2;
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img->ptr, left, top);
	mlx_destroy_image(fractal->mlx, fractal->img->ptr);
    clear_image(fractal);
}