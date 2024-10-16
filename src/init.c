/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najeuneh < najeuneh@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:25:44 by najeuneh          #+#    #+#             */
/*   Updated: 2024/10/11 15:34:26 by najeuneh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cube3d.h"

size_t	ft_strlen2(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	if (s == NULL)
		return (0);
	str = (char *)s;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	len = (ft_strlen2(s1) + ft_strlen2(s2));
	i = 0;
	j = 0;
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (free(str), free(s1), NULL);
	while (s1 != NULL && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 != NULL && s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free (s1);
	return (str);
}

char	*recup_map(int fd)
{
	char	*line;
	char	*buffer;
	int		bs;

	bs = 0;
	line = NULL;
	buffer = malloc(sizeof(char) * (1 + 1));
	if (!buffer)
		return (line);
	while (bs >= 0)
	{
		bs = read(fd, buffer, 1);
		if (bs == -1)
			return (free(buffer), free(line), NULL);
		if (bs == 0)
			break ;
		buffer[bs] = '\0';
		line = ft_strjoin(line, buffer);
		if (!line)
			return (free(buffer), NULL);
	}
	line = ft_strjoin(line, buffer);
	close(fd);
	return (free(buffer), line);
}

void	player_pos(char *line, t_data *data)
{
	int	i;

	data->pl_x = 0;
	data->pl_y = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 'P')
			return ;
		else if (line[i] == '\n')
		{
			data->pl_x = 0;
			data->pl_y++;
			i++;
		}
		else
		{
			i++;
			data->pl_x++;
		}
	}
}

t_data	init_map(int map)
{
	t_data	data;
	int		x;
	int		y;

	x = 0;
	y = 0;
	data.dirX = -1;
	data.dirY = 0;
	data.planeX = 0;	
	data.planeY = 0.66;	
	data.line = recup_map(map);
	data.map = ft_split(data.line, '\n');
	while (data.map[y][x])
		x++;
	data.map_x = x;
	while (data.map[y])
		y++;
	data.map_y = y;
	player_pos(data.line, &data);	
	return (data);
}
