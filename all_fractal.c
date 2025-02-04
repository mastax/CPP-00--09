#ifndef FRACTOL_H
# define FRACTOL_H

# include "bottons.h"
# include <mlx.h>
# include <unistd.h> 
# include <stdlib.h>

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 200

# define DEFAULT_WIDTH 800
# define DEFAULT_HEIGHT 800

# define BLACK				0x000000
# define DESATURATED_BLUE	0x444444
# define DEEP_BLUE			0x666666
# define TEAL				0x009999
# define LIGHT_TEAL			0x33cccc
# define LIGHT_TEAL_WHITE	0xccffff
# define BLUE_DEEP_1		0x003366
# define STATE_GREY_BLUE	0x1a476f
# define PURPLE				0x800080
# define LIGHT_STEEL_BLUE	0x4d6a8c
# define AIR_FORCE_BLUE		0x66829c
# define PALE_CERULEAN		0x7f99ab
# define PASTEL_BLUE		0x99b1bb
# define POWDER_BLUE		0xb2c9ca
# define LIGHT_GRE_BLUE		0xccdde2
# define VERY_LIGHT_BLUE	0xe6f2f9
# define PURE_WHITE			0xffffff
# define LIGHT_CYAN			0xccffff
# define BRIGHT_CYAN		0x99ffff
# define PERSIAN_GREEN		0x66cccc
# define MIDDLE_GREEN_BLUE	0x339999
# define DARK_CYAN			0x006666

typedef struct x_mlx_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx_data;

typedef struct x_vec2
{
	double	x;
	double	y;
}				t_vector;

typedef struct x_vars
{
	void			*mlx;
	void			*win;
	t_mlx_data		*img;
	t_vector		graph_start;
	t_vector		graph_end;
	t_vector		julia_c;
	int				(*color_func)(const int);
	void			(*fract_func)(struct x_vars *, int, int);
	int				(*inner_fract_func)(t_vector, t_vector);
}				t_vars;

void		exit_program(const int code, const t_vars *var);
void		set_color_pixel(t_mlx_data *data, int x, int y, unsigned int color);
double		ft_dmap(const int value, const int max, \
	const double fmin, const double fmax);

void		ft_calc_zoom(t_vars *var, const double factor);
void		ft_reset_zoom(t_vars *var);

t_vector	vec2_calc_deff(const t_vector a, const t_vector b);
void		vec2_calc_divide(t_vector *refr, const double div);

double		ft_atod(const char *s);
int			ft_is_valid_double_format(char *s);
int			ft_parse_args(t_vars *var, int ac, char **av);

void		ft_puts_fd(const int file_d, const char *s);
void		ft_puts(const char *s);
void		ft_write_str(const int file_d, const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			key_hook(int key, t_vars *var);
int			mouse_hook(int mouse_code, int a, int b, t_vars *var);
int			destroy_hook(t_vars	*var);

int			brot_inner(t_vector position, t_vector c);
void		brot_pixel(t_vars *var, int img_x, int img_y);
void		julia_pixel(t_vars *var, int img_x, int img_y);

int			fract_colorfunc_1(const int idx);
void		draw_pixel(t_vars *var, int idx, int a, int b);
void		iterate_image(t_vars *var);

#endif

//bottons.h
#ifndef BOTTONS_H
# define BOTTONS_H

# define KEYCODE_ESC 53
# define MOUSECODE_SCROLL_UP 5
# define MOUSECODE_SCROLL_DOWN 4

#endif

//drawing.c

#include "fractol.h"

int	fract_colorfunc_1(const int idx)
{
	const int	colors[16] = {
		BLUE_DEEP_1,
		STATE_GREY_BLUE,
		PURPLE,
		LIGHT_STEEL_BLUE,
		AIR_FORCE_BLUE,
		PALE_CERULEAN,
		PASTEL_BLUE,
		POWDER_BLUE,
		LIGHT_GRE_BLUE,
		VERY_LIGHT_BLUE,
		PURE_WHITE,
		LIGHT_CYAN,
		BRIGHT_CYAN,
		PERSIAN_GREEN,
		MIDDLE_GREEN_BLUE,
		DARK_CYAN
	};

	return (colors[idx & 0xf]);
}

void	draw_pixel(t_vars *var, int idx, int a, int b)
{
	unsigned int	color;

	if (idx == MAX_ITER)
		color = 0;
	else
		color = (*var->color_func)(idx);
	set_color_pixel(var->img, a, b, color);
}

void	iterate_image(t_vars *var)
{
	int	a;
	int	b;

	b = 0;
	while (b < HEIGHT)
	{
		a = 0;
		while (a < WIDTH)
		{
			(*var->fract_func)(var, a, b);
			a++;
		}
		b++;
	}
}
//fractol_func.c

int	brot_inner(t_vector position, t_vector c)
{
	double	oldx;
	int		it;

	it = 0;
	while (it < MAX_ITER)
	{
		oldx = position.x;
		position.x = position.x * position.x - position.y * position.y;
		position.y = 2 * oldx * position.y;
		position.x += c.x;
		position.y += c.y;
		if ((position.x * position.x) + (position.y * position.y) > 4)
			break ;
		it++;
	}
	return (it);
}

void	julia_pixel(t_vars *var, int img_x, int img_y)
{
	t_vector	position;

	position.x = ft_dmap(img_x, WIDTH, var->graph_start.x, var->graph_end.x);
	position.y = ft_dmap(img_y, HEIGHT, var->graph_start.y, var->graph_end.y);
	draw_pixel(var, (*var->inner_fract_func)(position, var->julia_c),
		img_x, img_y);
}

void	brot_pixel(t_vars *var, int img_x, int img_y)
{
	int			iteration_count;
	t_vector	position;
	t_vector	c;

	c.x = ft_dmap(img_x, WIDTH, var->graph_start.x, var->graph_end.x);
	c.y = ft_dmap(img_y, HEIGHT, var->graph_start.y, var->graph_end.y);
	position.x = 0.0;
	position.y = 0.0;
	iteration_count = (*var->inner_fract_func)(position, c);
	draw_pixel(var, iteration_count, img_x, img_y);
}

//atod.c

static void	skip_whitespace(char **s)
{
	while (**s == ' ' || (**s >= '\t' && **s <= '\r'))
	{
		(*s)++;
	}
}

static double	atod_postdecimal(const char *s)
{
	double		res;
	double		div;

	res = 0.0;
	div = 1.0;
	while (*s >= '0' && *s <= '9')
	{
		res *= 10.0;
		div *= 10.0;
		res += (double)(*s - '0');
		s++;
	}
	res /= div;
	return (res);
}

double	ft_atod(const char *s)
{
	double	res;
	int		is_nega;

	skip_whitespace((char **)&s);
	is_nega = 0;
	if (*s == '-')
	{
		is_nega = 1;
		s++;
	}
	else if (*s == '+')
		s++;
	res = 0.0;
	while (*s >= '0' && *s <= '9')
	{
		res *= 10.0;
		res += (double)(*s - '0');
		s++;
	}
	if (*s == '.')
		res += atod_postdecimal(s + 1);
	if (is_nega)
		res = -res;
	return (res);
}

int	ft_is_valid_double_format(char *s)
{
	char	*s_before_numberskip;

	skip_whitespace(&s);
	if (*s == '-' || *s == '+')
		s++;
	s_before_numberskip = s;
	while (*s >= '0' && *s <= '9')
		s++;
	if (*s == 0 && s > s_before_numberskip)
		return (1);
	if (*s != '.')
		return (0);
	s++;
	s_before_numberskip = s;
	while (*s >= '0' && *s <= '9')
		s++;
	if (s_before_numberskip == s)
		return (0);
	skip_whitespace(&s);
	return (*s == 0);
}

//hooks.c

int	key_hook(int key, t_vars *var)
{
	if (key == KEYCODE_ESC)
	{
		exit_program(0, var);
		return (0);
	}
	iterate_image(var);
	return (0);
}

int	mouse_hook(int mouse_code, int a, int b, t_vars *var)
{
	(void)a;
	(void)b;
	if (mouse_code == MOUSECODE_SCROLL_DOWN)
		ft_calc_zoom(var, 0.2);
	if (mouse_code == MOUSECODE_SCROLL_UP)
		ft_calc_zoom(var, -0.2);
	iterate_image(var);
	mlx_put_image_to_window(var->mlx, var->win, var->img->img, 0, 0);
	return (0);
}

int	destroy_hook(t_vars	*var)
{
	exit_program(0, var);
	return (0);
}
//main.c

int	ft_parse_args(t_vars *var, int ac, char **av)
{
	const char	*f_type;

	f_type = av[1];
	var->inner_fract_func = &brot_inner;
	if (!ft_strncmp(f_type, "mandelbrot", 10) && ac == 2 && f_type[10] == 0)
		var->fract_func = &brot_pixel;
	else if (!ft_strncmp(f_type, "julia", 5))
	{
		if ((ac < 4 || !ft_is_valid_double_format(av[2])
				|| !ft_is_valid_double_format(av[3])) || ac > 4)
			return (0);
		var->fract_func = &julia_pixel;
		var->julia_c.x = ft_atod(av[2]);
		var->julia_c.y = ft_atod(av[3]);
	}
	else
		return (0);
	return (1);
}

static void	display_valid_args(const char *prog_name)
{
	ft_write_str(1, prog_name);
	ft_puts(" USAGE: ./fractol mandelbrot");
	ft_write_str(1, prog_name);
	ft_puts(" USAGE: ./fractol julia <r_value> <i_value>");
}

static void	ft_init_mlx(t_vars	*var, t_mlx_data *img)
{
	var->color_func = &fract_colorfunc_1;
	var->win = mlx_new_window(var->mlx, WIDTH, HEIGHT, "fract-ol");
	img->img = mlx_new_image(var->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	var->img = img;
	ft_reset_zoom(var);
	mlx_key_hook(var->win, key_hook, var);
	mlx_mouse_hook(var->win, mouse_hook, var);
	mlx_hook(var->win, 17, 0L, destroy_hook, var);
}

int	main(int ac, char **av)
{
	t_vars		var;
	t_mlx_data	d;

	if (ac < 2 || !ft_parse_args(&var, ac, av))
	{
		display_valid_args(av[0]);
		return (0);
	}
	var.mlx = mlx_init();
	if (var.mlx == NULL)
	{
		ft_puts_fd(2, "mlx init failed");
		return (1);
	}
	ft_init_mlx(&var, &d);
	iterate_image(&var);
	mlx_put_image_to_window(var.mlx, var.win, d.img, 0, 0);
	mlx_loop(var.mlx);
	return (0);
}

//functions_helpers:

void	set_color_pixel(t_mlx_data *d, int x, int y, unsigned int color)
{
	char	*dest;

	dest = d->addr + (y * d->line_length + x * (d->bits_per_pixel / 8));
	*((unsigned int *)dest) = color;
}

double	ft_dmap(const int value, const int max, \
	const double fmin, const double fmax)
{
	return (fmin + ((((double)value) / (double)(max)) * (fmax - fmin)));
}

void	exit_program(const int code, const t_vars *var)
{
	mlx_destroy_image(var->mlx, var->img->img);
	mlx_destroy_window(var->mlx, var->win);
	exit(code);
}
//hooks:

t_vector	vec2_calc_deff(const t_vector a, const t_vector b)
{
	t_vector	deff;

	deff.x = b.x - a.x;
	deff.y = b.y - a.y;
	return (deff);
}

void	vec2_calc_divide(t_vector *refr, const double div)
{
	refr->x /= div;
	refr->y /= div;
}

//zoom.c

void	ft_calc_zoom(t_vars *var, const double factor)
{
	t_vector	deff;

	deff = vec2_calc_deff(var->graph_start, var->graph_end);
	vec2_calc_divide(&deff, 2.0);
	var->graph_start.x += deff.x * factor;
	var->graph_start.y += deff.y * factor;
	var->graph_end.x -= deff.x * factor;
	var->graph_end.y -= deff.y * factor;
}

void	ft_reset_zoom(t_vars *var)
{
	var->graph_start.x = -1.0 * (double)WIDTH / ((double)DEFAULT_WIDTH / 2.0);
	var->graph_start.y = -1.0 * (double)HEIGHT
		/ ((double)DEFAULT_HEIGHT / 2.0);
	var->graph_end.x = 1.0 * (double)WIDTH / ((double)DEFAULT_WIDTH / 2.0);
	var->graph_end.y = 1.0 * (double)HEIGHT / ((double)DEFAULT_HEIGHT / 2.0);
}
