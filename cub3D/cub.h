/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: livlamin <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 13:26:38 by livlamin      #+#    #+#                 */
/*   Updated: 2020/12/14 11:11:19 by livlamin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "./mlx/mlx.h"
# include "./libft/libft.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>

# define KEY_A 0
# define KEY_D 2
# define KEY_S 1
# define KEY_W 13
# define KEY_UP 126
# define KEY_DOWN 0
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_SHIFT 17
# define KEY_SPACE 49
# define KEY_ESC 53

# define NO 0
# define EA 1
# define SO 2
# define WE 3
# define SP 4

# define UDIV 1
# define VDIV 1
# define VMOVE 0.0

/*
** posx & posy = start pos vector player
** dirx & dir y = direction vector player
** planex & planey =  camera plane of the player
** time = time current frame
** old_time = ime previous frame
** v = links boven scherm  x op scherm
** W = breedte scherm Y op scherm
** camerax =  x-coordinatie in camera space
** mapx = boxX map
** mapy = boxY map
** sidedistx = length of ray from current position to next x or y-side
** deltadistx = length of ray from one x or y-side to next x or y-side
** hit = wall hit?
** side =NS or EW hit?
** stepx = wwhat direction to step in x or y-direction (either +1 or -1)
*/

typedef struct	s_ray {
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		time;
	double		old_time;
	double		frame_time;
	int			x;
	double		camerax;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	double		oldplanex;
	double		olddirx;
	double		x_temp;
}				t_ray;

typedef struct	s_win {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*mlx;
	void		*mlx_win;
	int			color;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			width;
	int			height;
	double		mov_speed;
	double		rot_speed;
	char		**map;
	int			forward;
	int			backward;
	int			left;
	int			right;
	int			destroy;
	int			cam_left;
	int			cam_right;
	char		**map_ff;
	int			screen_w;
	int			screen_h;
	double		map_w;
}				t_win;

typedef struct	s_tex {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			tex_width;
	int			tex_height;
	char		*texture;
}				t_tex;

typedef struct	s_texpos
{
	int			texnum;
	double		wallx;
	int			tex_x;
	double		step;
	double		texpos;
	int			tex_y;
}				t_texpos;

typedef struct	s_parser
{
	char		*file;
	int			start_dir;
	char		*res;
	char		*floor;
	char		*ceiling;
	char		*saver;
	size_t		ycounter;
	int			dir_check;
	int			map_check;
	int			rgb_check;
	int			floor_col;
	int			ceiling_col;
	int			screenshot;
	int			map_nl_check;
	int			newline;
}				t_parser;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;

}				t_sprite;

typedef struct	s_sp
{
	size_t		numb_sprites;
	double		*zbuffer;
	t_sprite	*sprites;
	int			*sprite_order;
	double		*sprite_dist;
	double		spritex;
	double		spritey;
	double		invdet;
	double		transformx;
	double		transformy;
	int			spritescreenx;
	int			sprite_height;
	int			spritewidth;
	int			drawstarty;
	int			drawstartx;
	int			drawendx;
	int			drawendy;
	int			stripe;
	int			sp_tex_x;
	int			sp_tex_y;
	int			vmove_screen;
}				t_sp;

typedef struct	s_mega {
	t_win		win;
	t_ray		ray;
	t_tex		tex[5];
	t_texpos	texpos;
	t_parser	parser;
	t_sp		sp;
}				t_mega;

int				ft_cub(t_mega *mega);
void			ft_my_mlx_pixel_put(t_win *win, int x, int y, int color);
int				ft_close_window(t_mega *mega);
void			ft_raycast(t_mega *mega);
void			ft_textures(t_mega *mega, int dir);
unsigned int	ft_my_mlx_pixel_get(t_tex tex, t_mega *mega, int x, int y);
void			ft_draw_walls(t_mega *mega, int dir);
int				get_next_line(int fd, char **line);
int				ft_ini_win(t_mega *mega);
int				ft_ini_ray(t_mega *mega);
int				ft_ini_textures(t_tex *tex, int i);
int				ft_ini_parser(t_mega *mega);
int				ft_ini_all_textures(t_mega *mega);
int				ft_ini_sprite(t_mega *mega);
int				ft_ini_sp(t_mega *mega);
int				ft_error_message(int message);
int				ft_check_rgb(t_mega *mega, char *color, int r, int g);
int				ft_check_data(t_mega *mega);
int				flood_fill(int x, int y, char fill, t_mega *mega);
int				ft_read_cubfile(t_mega *mega, char *line, int gnl_return);
int				ft_save_map(char *line, t_mega *mega, int x, char *temp);
int				ft_press(int keycode, t_mega *mega);
int				ft_release(int keycode, t_mega *mega);
char			*ft_free_line(char *line);
void			ft_create_sprites(t_mega *mega);
void			ft_sort_sprites(t_mega *mega);
void			ft_calc_dist_sprites(t_mega *mega, size_t sp);
void			ft_get_addr_textures(t_mega *mega);
void			ft_upload_textures(t_mega *mega);
int				ft_movement(t_mega *mega);
void			ft_calc_pos_dir(t_mega *mega);
void			ft_calc_step_side_d(t_mega *mega);
void			ft_dda(t_mega *mega);
int				ft_calc_dir(t_mega *mega);
void			ft_calculate_dist(t_mega *mega);
void			ft_make_screenshot(t_mega *mega);
char			**ft_create_map(t_mega *mega, int y);
char			**ft_reverse_map(t_mega *mega, int y, int x);
char			**ft_reverse_map_ff(t_mega *mega, int y, int x);

#endif
