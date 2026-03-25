#include "textures.h"
#include "parse.h"

static int	read_header(int fd, char ***header)
{
	char	head[32];
	int		bytes;

	ft_bzero(head, 32);
	bytes = read(fd, &head, 31);
	if (bytes < 1)
		return (RT_ERR_READ);
	*header = ft_split_ws(head);
	if (!*header)
		return (RT_ERR_MALLOC);
	return (0);
}

int	parse_tex(const char *t, t_tex *out)
{
	int			fd;
	char		**head;
	int			read_pixels;;
	int			err;
	char		buf[512];

	buf[0] = '\0';
	ft_strlcat(buf, "textures/", sizeof buf);
	ft_strlcat(buf, t, sizeof(buf));
	head = NULL;
	(void) out;
	fd = open(buf, O_RDONLY);
	if (fd < 0)
		return (RT_ERR_OPEN);
	err = read_header(fd, &head);
	if (err)
		return (close(fd), err);
	out->w = ft_atoi(head[1]);
	out->h = ft_atoi(head[2]);
	out->color_depth = ft_atoi(head[3]);
	out->ptr = malloc(out->w * out->h * 3);
	if (!out->ptr)
	{
		free_array(head);
		return (RT_ERR_MALLOC);
	}
	read_pixels = ft_strlen(head[4]);
	ft_memcpy(out->ptr, head[4], read_pixels);
	free_array(head);
	read(fd, out->ptr + read_pixels,(out->w *out->h * 3) - read_pixels);
	return (0);
}

// t_tex	*parse_tex(char *path)
// {
// 	t_tex	*tex;
// 	int		fd;
// 	char	*buf;
// 	char	**dims;
	
// 	buf = get_next_line(fd);
// 	if (!buf || ft_strncmp(buf, "P6", 2))
// 	{
// 		close(fd);
// 		free(buf);
// 		return (NULL);
// 	}
// 	free(buf);
// 	buf = get_next_line(fd);
// 	if (!buf)
// 		return (close(fd), NULL);
// 	dims = ft_split_ws(buf);
// 	free(buf);

// 	int	i;
// 	tex = ft_calloc(1, sizeof(t_tex));
// 	if (!tex)
// 	{
// 		i = 0;
// 		while (dims[i])
// 			free(dims[i++]);
// 		free(dims);
// 		return (close(fd), NULL);
// 	}
// 	if (ft_strtoi(dims[0], &tex->w) || ft_strtoi(dims[1], &tex->h))
// 	{
// 		i = 0;
// 		while (dims[i])
// 			free(dims[i++]);
// 		free(dims);
// 		free(tex);
// 		return (close(fd), NULL);
// 	}


// 	buf = get_next_line(fd);
// 	if (!buf)
// 		return (close(fd), free(tex), NULL);
// 	tex->ptr = malloc(3 * tex->h * tex->w);
// 	free(buf);
// 	if (!tex->ptr)
// 		return (free(tex), close(fd), NULL);
// }