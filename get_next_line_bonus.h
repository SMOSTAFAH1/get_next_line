/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-09-29 13:06:39 by shashemi          #+#    #+#             */
/*   Updated: 2024-09-29 13:06:39 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_print
{
	char	content[BUFFER_SIZE];
	ssize_t	size_buf;
}	t_print;

void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_cut_tp(t_print *tp, int len_trim);

void	*ft_calloc(size_t count, size_t size);
void	ft_tp_line_ex(t_print *tp, char **line, int len_tp, char *str);
int		ft_tp_line(t_print *tp, char **line);

int		ft_buffer(int fd, t_print *tp, char **line);
char	*get_next_line(int fd);

#endif
