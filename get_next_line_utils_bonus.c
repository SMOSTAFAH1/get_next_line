/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-01 11:28:02 by shashemi          #+#    #+#             */
/*   Updated: 2024-10-01 11:28:02 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

/**
 * Checks if a string contains a newline character.
 * 
 * @param s The string to check.
 * @return 1 if the string contains a newline character, 0 otherwise.
 */
int	contains_newline(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/**
 * Joins two strings into a new string.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @return A new string that is the concatenation of s1 and s2,
 * or NULL if allocation fails.
 */
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*s;
	int		len;
	int		i;

	len = 0;
	if (!s1 && !s2)
		return (NULL);
	while (s1 && s1[len])
		len++;
	i = 0;
	while (s2 && s2[i])
		i++;
	s = ft_calloc(len + i + 1, sizeof * s);
	if (!s)
		return (NULL);
	len = -1;
	while (s1 && s1[++len])
		s[len] = s1[len];
	i = -1;
	while (s2 && s2[++i])
		s[len + i] = s2[i];
	return (s);
}

/**
 * Duplicates a string.
 * 
 * @param s1 The string to duplicate.
 * @return A new string that is a duplicate of s1, or NULL if allocation fails.
 */
char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	if (!s1)
		return (ft_strdup(""));
	i = 0;
	while (s1[i])
		i++;
	s2 = ft_calloc(i + 1, sizeof * s2);
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	return (s2);
}

/**
 * Allocates memory and initializes it to zero.
 * 
 * @param count The number of elements to allocate.
 * @param size The size of each element.
 * @return A pointer to the allocated memory, or NULL if allocation fails.
 */
void	*ft_calloc(size_t count, size_t size)
{
	void			*r;
	unsigned char	*p;
	size_t			total;

	total = count * size;
	r = malloc(total);
	if (!r)
		return (NULL);
	p = (unsigned char *)r;
	while (total != 0)
	{
		*p = 0;
		p++;
		total--;
	}
	return (r);
}

/**
 * Frees multiple strings and sets their pointers to NULL.
 * 
 * @param str The first string to free.
 * @param str2 The second string to free.
 * @param str3 The third string to free.
 */
void	ft_free_strs(char **str, char **str2, char **str3)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	if (str2 && *str2)
	{
		free(*str2);
		*str2 = NULL;
	}
	if (str3 && *str3)
	{
		free(*str3);
		*str3 = NULL;
	}
}
