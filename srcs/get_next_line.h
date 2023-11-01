/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:24:58 by jongmlee          #+#    #+#             */
/*   Updated: 2023/10/17 12:32:50 by jongmlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> // for test

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5000
# endif

# if BUFFER_SIZE <= 0
#  error "invalid BUFFER_SIZE"
# endif

size_t	gnl_strlen(const char *s);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_strdup(const char *s1);
char	*gnl_substr(char *s, unsigned int start, size_t len);
char	*gnl_strchr(const char *s, char c);
size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);
char	*get_next_line(int fd);
char	*ret_newline(char **backup, char *nl_loc);
char	*ret_eof(char **backup);
void	*gnl_del(char **s);

#endif