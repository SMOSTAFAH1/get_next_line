/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-29 13:07:51 by shashemi          #+#    #+#             */
/*   Updated: 2024-09-29 13:07:51 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src && n > 0)
		return (NULL);
	while (i < n)
	{
		if (!src || !dst)
			return (NULL);
		*(char *)(dst + i) = *(char *)(src + i);
		i++;
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (*(s + i))
	{
		if (*(s + i) == (char)c)
			return ((char *)s + i);
		++i;
	}
	if ((char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	res = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(*res));
	if (!res)
		return (0);
	ft_memcpy(res, s1, len_s1);
	ft_memcpy(res + len_s1, s2, len_s2);
	res[len_s1 + len_s2] = '\0';
	return (res);
}

void	ft_cut_tp(t_print *tp, int len_trim)
{
	char	*str;
	int		len_tp;
	int		i;

	if (!tp || !*tp->content)
		return ;
	len_tp = ft_strlen(tp->content);
	if (len_tp <= len_trim)
	{
		tp->content[0] = '\0';
		return ;
	}
	str = ft_strjoin(tp->content + len_trim, "");
	if (!str)
		return ;
	i = 0;
	while (i < BUFFER_SIZE)
		tp->content[i++] = '\0';
	ft_memcpy(tp->content, str, ft_strlen(str));
	free(str);
}
