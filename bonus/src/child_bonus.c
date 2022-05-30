/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:47:06 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/05/30 14:47:09 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child(int *p1, char **args, char *input_file)
{
	int	fd;

	close(p1[0]);
	if (dup2(p1[1], 1) == -1)
		cust_perror("Error");
	fd = open(input_file, O_RDONLY);
	if (dup2(fd, 0) == -1)
		cust_perror("Error");
	close(fd);
	execve(is_cmd_exist_and_executable(args[0]), args, NULL);
}

void	middle_child(int *p1, int *p2, char **args)
{
	close(p1[1]);
	close(p2[0]);
	if (dup2(p1[0], 0) == -1)
		cust_perror("Error");
	if (dup2(p2[1], 1) == -1)
		cust_perror("Error");
	execve(is_cmd_exist_and_executable(args[0]), args, NULL);
}

void	last_child(int *p1, char **args, char *output_file)
{
	int	fd;

	close(p1[1]);
	if (dup2(p1[0], 0) == -1)
		cust_perror("Error");
	fd = open(output_file, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (dup2(fd, 1) == -1)
		cust_perror("Error");
	close(fd);
	execve(is_cmd_exist_and_executable(args[0]), args, NULL);
}