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

void	*ft_calloc(size_t count, size_t size)
{
	void	*puntero;
	char	*ch;
	size_t	i;

	puntero = malloc(count * size);
	if (!puntero)
		return (NULL);
	ch = puntero;
	i = 0;
	while (i < (count * size))
	{
		ch[i] = '\0';
		i++;
	}
	return (puntero);
}

void	ft_tp_line_ex(t_print *tp, char **line, int len_tp, char *str)
{
	char	*tmp_tp;

	if (str && *line)
	{
		tmp_tp = (char *)ft_calloc(len_tp, sizeof(tmp_tp));
		ft_memcpy(tmp_tp, tp->content, len_tp);
		str = ft_strjoin(*line, "");
		free(*line);
		*line = ft_strjoin(str, tmp_tp);
		free(tmp_tp);
		free(str);
	}
	else
	{
		len_tp = ft_strlen(tp->content);
		str = ft_strjoin(*line, "");
		free(*line);
		*line = ft_strjoin(str, tp->content);
		free(str);
	}
	ft_cut_tp(tp, len_tp);
}

int	ft_tp_line(t_print *tp, char **line)
{
	char	*str;
	int		len_tp;

	str = ft_strchr(tp->content, '\n');
	len_tp = str - tp->content + 1;
	if (str && !*line)
	{
		str = (char *)ft_calloc(len_tp, sizeof(str));
		ft_memcpy(str, tp->content, len_tp);
		ft_cut_tp(tp, len_tp);
		*line = str;
	}
	else if (str && *line)
		ft_tp_line_ex(tp, &(*line), len_tp, str);
	else if (*tp->content && *line != NULL)
		ft_tp_line_ex(tp, &(*line), len_tp, str);
	else
	{
		len_tp = ft_strlen(tp->content);
		*line = ft_strjoin(tp->content, "");
		ft_cut_tp(tp, len_tp);
	}
	return (1);
}

int	ft_buffer(int fd, t_print *tp, char **line)
{
	if (!*tp->content)
		tp->size_buf = read(fd, tp->content, BUFFER_SIZE);
	if (tp->size_buf < 0)
		return (-1);
	if (*tp->content)
		ft_tp_line(tp, (&(*line)));
	if ((!tp->size_buf && !*line) || (!*tp->content && !tp->size_buf && *line))
		return (0);
	else if (!ft_strchr(*line, '\n'))
		ft_buffer(fd, tp, &(*line));
	return (1);
}

char	*get_next_line(int fd)
{
	static t_print	*tp;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!tp)
		tp = (t_print *)ft_calloc(sizeof(t_print), 1);
	if (!tp)
		return (NULL);
	line = (NULL);
	ft_buffer(fd, &(*tp), &line);
	if (line)
		return (line);
	else if ((!line && !((*tp)).size_buf) || (*tp).size_buf < 0)
	{
		if (tp)
			free(tp);
		tp = (NULL);
		return (NULL);
	}
	return (line);
}
