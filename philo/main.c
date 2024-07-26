/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateo <mateo@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 06:45:06 by mateo             #+#    #+#             */
/*   Updated: 2024/04/20 11:29:21 by mateo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_meta	*meta;

	if (argc < 5 || argc > 6)
		return (exit_error(ERR_ARGS, 0), 1);
	if (check_arg(argc, argv) == 0)
		return (exit_error(ERR_INVALID, 0), 1);
	meta = init_meta(argc, argv);
	if (!meta)
		return (1);
	if (start(meta) != 0)
		return (1);
	stop(meta);
	return (0);
}
