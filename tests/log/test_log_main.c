/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_log_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:07:31 by hazunic           #+#    #+#             */
/*   Updated: 2026/01/07 18:45:45 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_error.h"

void	test_log(void);

int	main(void)
{
	test_log();
	return (0);
}

/* add rest */
void	test_log(void)
{
	rt_log_error(E_USAGE, ERR_USAGE, 0);
	rt_log_error(E_OK, "test", 0);
}