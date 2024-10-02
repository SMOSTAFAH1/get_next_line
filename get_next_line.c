/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-01 10:44:46 by shashemi          #+#    #+#             */
/*   Updated: 2024-10-01 10:44:46 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

/**
 * @brief Extrae y devuelve una nueva cadena que contiene los caracteres
 *        de una cadena hasta el primer salto de línea ('\n') o el final
 *        de la cadena (`\0`). Incluye el salto de línea si se encuentra.
 *
 * @param s La cadena de entrada desde la que se extraerá el contenido.
 * @return Un puntero a una nueva cadena con el contenido antes del salto
 *         de línea, o NULL si no se pudo reservar memoria.
 */
char	*get_before_newline(const char *s)
{
	char	*res;
	int		i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] && s[i] == '\n')
		i++;
	res = ft_calloc(i + 1, sizeof (*res));
	if (!res)
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		res[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}

/**
 * @brief Devuelve una nueva cadena que contiene todos los caracteres
 *        después del primer salto de línea ('\n') en una cadena dada.
 *        Si no hay salto de línea, devuelve una cadena vacía.
 *
 * @param s La cadena de entrada desde la que se extraerá el contenido.
 * @return Un puntero a una nueva cadena con el contenido después del salto
 *         de línea, o NULL si no se pudo reservar memoria.
 */
char	*get_after_newline(const char *s)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	while (s && s[j])
		j++;
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] && s[i] == '\n')
		i++;
	res = ft_calloc((j - i) + 1, sizeof (*res));
	if (!res)
		return (NULL);
	j = 0;
	while (s[i + j])
	{
		res[j] = s[i + j];
		j++;
	}
	return (res);
}

/**
 * @brief Lee desde un archivo utilizando un buffer de tamaño `BUFFER_SIZE`
 *        y concatena el contenido leído con el contenido ya guardado en
 *        `keep`. La función sigue leyendo hasta encontrar un salto de línea
 *        o el final del archivo.
 *
 * @param fd Descriptor de archivo desde el cual se leerá.
 * @param keep Puntero al contenido acumulado estático.
 * @param tmp Puntero temporal usado para manipular y liberar memoria.
 * 
 * @return Esta función no retorna ningún valor, pero actualiza `keep`
 *         con el contenido leído del archivo.
 */
void	ft_read_line(int fd, char **keep, char **tmp)
{
	char	*buf;
	int		r;

	buf = malloc(sizeof (*buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return ;
	r = 1;
	while (r > 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
		{
			ft_free_strs(&buf, keep, tmp);
			return ;
		}
		buf[r] = '\0';
		*tmp = ft_strdup(*keep);
		ft_free_strs(keep, 0, 0);
		*keep = ft_strjoin(*tmp, buf);
		ft_free_strs(tmp, 0, 0);
		if (contains_newline(*keep))
			break ;
	}
	ft_free_strs(&buf, 0, 0);
}

/**
 * @brief Procesa el contenido acumulado en `keep`, separando una línea completa
 *        (incluyendo el salto de línea, si está presente), y actualiza `keep`
 *        con el contenido restante después del salto de línea.
 *
 * @param keep Puntero al contenido acumulado estático.
 * @param tmp Puntero temporal usado para manipular y liberar memoria.
 * @return Un puntero a la línea extraída desde `keep` (incluyendo el salto de
 * 		   línea si existe) o NULL en caso de error.
 */
char	*ft_parse_line(char **keep, char **tmp)
{
	char	*line;

	*tmp = ft_strdup(*keep);
	ft_free_strs(keep, 0, 0);
	*keep = get_after_newline(*tmp);
	line = get_before_newline(*tmp);
	ft_free_strs(tmp, 0, 0);
	return (line);
}

/**
 * @brief Lee una línea de un archivo descrito por `fd`. Esta función lee
 *        hasta que encuentra un salto de línea o el final del archivo.
 *        Utiliza una variable estática `keep` para retener la información
 *        entre llamadas sucesivas a la función.
 *
 * @param fd El descriptor de archivo desde el cual se leerá.
 * @return Un puntero a la siguiente línea leída desde el archivo, o NULL
 *         si hay un error, si se alcanza el final del archivo o si no
 *         se pudo asignar memoria.
 */
char	*get_next_line(int fd)
{
	static char	*keep = NULL;
	char		*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = NULL;
	tmp = NULL;
	ft_read_line(fd, &keep, &tmp);
	if (keep != NULL && *keep)
		line = ft_parse_line(&keep, &tmp);
	if (!line || *line == '\0')
	{
		ft_free_strs(&keep, &line, &tmp);
		return (0);
	}
	return (line);
}
