/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:13:12 by anammal           #+#    #+#             */
/*   Updated: 2023/09/11 13:13:21 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_err(char const *err_msg)
{
	if (err_msg)
		ft_putendl_fd((char *)err_msg, STDERR_FILENO);
	else
		perror("ERROR");
	exit(EXIT_FAILURE);
}

// void	exit_err_heap(void	*ptr, void (*f)(void *))
// {
// 	f(ptr);
// 	exit_err("ERROR: can not allocate needed memory");
// }

// void	exit_err_heap2(t_list **ptr)
// {
// 	f(ptr, free);
// 	exit_err("ERROR: can not allocate needed memory");
// }
