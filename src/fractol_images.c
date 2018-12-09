#include "fractol.h"

void	clear_image(t_fractal *fractal)
{
	VAR(t_img*, img, fractal->img);
	ft_bzero(img, sizeof(t_img));
	img->ptr = mlx_new_image(fractal->mlx, WINX, WINY);
	img->pixels = (int *)mlx_get_data_addr(img->ptr, &img->bpp,
			&img->size_line, &img->endian);
}

void	    image_init(t_fractal *fractal)
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


void	    image_put(t_fractal *fractal)
{
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img->ptr, 0, 0);
	mlx_destroy_image(fractal->mlx, fractal->img->ptr);
	clear_image(fractal);
}

void	    img_pixel_put(t_img *img, int x, int y, int color)
{
	int i = 0;

	i = (x + y * img->size_line / sizeof(int));
	img->pixels[i] = color;
}