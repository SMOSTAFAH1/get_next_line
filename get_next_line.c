/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-28 12:11:36 by shashemi          #+#    #+#             */
/*   Updated: 2024-09-28 12:11:36 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*free_holded(char **in_hold)
{
	free(*in_hold);
	*in_hold = NULL;
	return (NULL);
}

static char	*update_holded(char **in_hold)
{
	char	*aux;
	char	*new_hold;
	int		offset;

	aux = ft_strchr_nwln(*in_hold);
	if (!aux)
		return (free_holded(in_hold));
	offset = aux - *in_hold + 1;
	new_hold = substr_tweaked(*in_hold, offset, ft_strlen(*in_hold) - offset);
	free_holded(in_hold);
	*in_hold = new_hold;
	return (*in_hold);
}

static char	*extract_line(char *in_hold)
{
	char	*res;
	char	*aux;
	int		offset;

	aux = ft_strchr_nwln(in_hold);
	if (!aux)
	{
		res = ft_strdup(in_hold);
		free(in_hold);
		return (res);
	}
	offset = aux - in_hold + 1;
	res = substr_tweaked(in_hold, 0, offset);
	free(in_hold);
	return (res);
}

static int	read_file(char **in_hold, int fd)
{
	char	*buffer;
	int		flag;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	while (!ft_strchr_nwln(*in_hold))
	{
		flag = read(fd, buffer, BUFFER_SIZE);
		if (flag <= 0)
			break ;
		buffer[flag] = '\0';
		*in_hold = ft_strjoin_tweaked(*in_hold, buffer);
		if (!*in_hold)
		{
			free(buffer);
			return (-1);
		}
	}
	free(buffer);
	return (flag);
}

char	*get_next_line(int fd)
{
	static char	*in_hold = NULL;
	char		*res;
	int			read_res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!in_hold || !ft_strchr_nwln(in_hold))
	{
		read_res = read_file(&in_hold, fd);
		if (read_res < 0)
			return (free_holded(&in_hold));
	}
	if (!in_hold)
		return (NULL);
	res = extract_line(in_hold);
	if (!res)
		return (free_holded(&in_hold));
	update_holded(&in_hold);
	return (res);
}
