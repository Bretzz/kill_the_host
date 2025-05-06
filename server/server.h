/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: topiana- <topiana-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 23:35:15 by topiana-          #+#    #+#             */
/*   Updated: 2025/05/06 23:42:15 by topiana-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

/* WARNING: we need to catch the 'we are dead' signal from the 'game' so
that every thread can exit cleanly. */

# include "online.h"
# include <pthread.h>

#endif