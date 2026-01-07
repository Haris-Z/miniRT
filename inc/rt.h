
#ifndef RT_H
# define RT_H

# define RT_WINDOW_NAME	"miniRT"
# define SCREEN_WIDTH	800 // 1920 
# define SCREEN_HEIGHT	600 // 1080 // full screen

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

//# include "../minilibx-linux/mlx.h"
# include "mlx.h"
// # include "rt_keys.h"
// # include "vec3.h"
// # include "ray.h"
// # include "color.h"
// # include "scene.h"
# include "parser.h"

/* add spp */
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

/* add int flags and  */
typedef struct s_app
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		w;
	int		h;
	int		should_quit;
	t_scene	scene;
	// err_context
	// state
	// flag
}	t_app;

/* app */
int		rt_app_init(t_app *app, int w, int h, const char *title);
int		rt_app_run(t_app *app);
void	rt_app_destroy(t_app *app);

/* mlx image wrapper */
int		rt_img_create(t_app *app, t_img *img, int w, int h);
void	rt_img_destroy(t_app *app, t_img *img);
void	rt_img_put_pixel(t_img *img, int x, int y, int color);

/* events */
int		rt_on_keypress(int keycode, void *param);
int		rt_on_destroy(void *param);
int		rt_on_expose(void *param);
int		rt_on_loop(void *param);

int		rt_error(const char *msg);

#endif
