/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:57:38 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/30 16:01:41 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <limits.h>
# include <fcntl.h>

# define BIN_PATH "/bin/"
# define USRBIN_PATH "/usr/bin/"

// check.c
char	*is_cmd_exist_and_executable(char *cmd);
void	is_file_exist_and_readable(char *str);
void	is_file_exist_and_writable(char *str);
// stderr.c
void	cust_perror(char *str);
void	cust_write(char *str);
// str_join.c
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
// str_split.c
char	**ft_split(char const *s, char c);
int		count_num_of_strings(char const *s, char c);
// strnstr.c
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif
