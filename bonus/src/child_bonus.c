/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiyamamo <hiyamamo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:53:56 by hiyamamo          #+#    #+#             */
/*   Updated: 2022/06/03 12:12:14 by hiyamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_child(t_param *pa, char **exec_args)
{
	int		fd;
	char	*cmd_path;

	if (close(pa->p[0][0]) == -1)
		cust_perror("Error(first_child: close p[0][0])");
	if (dup2(pa->p[0][1], 1) == -1)
		cust_perror("Error(first_child: dup2 p[0][1])");
	fd = open(pa->argv[1], O_RDONLY);
	if (fd == -1)
		cust_perror("Error(first_child: open fd)");
	if (dup2(fd, 0) == -1)
		cust_perror("Error(first_child: dep2 fd)");
	if (close(fd) == -1)
		cust_perror("Error(first_child: close fd)");
	cmd_path = is_cmd_exist_and_executable(pa->pathenv, exec_args[0]);
	if (execve(cmd_path, exec_args, pa->envp) == -1)
		exit(127);
	free(cmd_path);
}

void	middle_child(int *p1, int *p2, t_cmd_param *cmd_p, t_param *pa)
{
	char	*cmd_path;

	if (close(p1[1]) == -1)
		cust_perror("Error(middle_child: close p1[1])");
	if (close(p2[0]) == -1)
		cust_perror("Error(middle_child: close p2[0])");
	if (dup2(p1[0], 0) == -1)
		cust_perror("Error(middle_child: dup2 p1[0])");
	if (dup2(p2[1], 0) == -1)
		cust_perror("Error(middle_child: dup2 p2[1])");
	cmd_path = is_cmd_exist_and_executable(pa->pathenv, cmd_p->exec_args[0]);
	if (execve(cmd_path, cmd_p->exec_args, pa->envp) == -1)
		exit(127);
	free(cmd_path);
}

void	last_child(int *p1, t_cmd_param *cmd_p, char *output, t_param *pa)
{
	int		fd;
	char	*cmd_path;

	if (close(p1[1]) == -1)
		cust_perror("Error(last_child: close p1[1])");
	if (dup2(p1[0], 0) == -1)
		cust_perror("Error(last_child: dup2 p1[0])");
	fd = open(output, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (fd == -1)
		cust_perror("Error(last_child: open fd)");
	if (dup2(fd, 1) == -1)
		cust_perror("Error(last_child: dup2 fd)");
	if (close(fd) == -1)
		cust_perror("Error(last_child: close fd)");
	cmd_path = is_cmd_exist_and_executable(pa->pathenv, cmd_p->exec_args[0]);
	if (execve(cmd_path, cmd_p->exec_args, pa->envp) == -1)
		exit(127);
	free(cmd_path);
}
