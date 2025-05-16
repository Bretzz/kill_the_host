/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:00:12 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/16 17:49:12 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <unistd.h>

int				ft_perror(const char *string);
void			free_mtx(void **mtx);
unsigned int	ip_to_uns(const char *ip);
int				ft_chrnum(const char *s, int c);

size_t			ft_mtxlen(const void **mtx);

#endif