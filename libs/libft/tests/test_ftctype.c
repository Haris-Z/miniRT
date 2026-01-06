/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ftctype.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 13:23:53 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/21 11:55:25 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <ctype.h>
#include "libft.h"

TestSuite(Character_class_tests);

/* --- Boundary tests for each function --- */
Test(Character_class_tests, isalpha_boundaries)
{
	cr_log_info("ISALPHA: isalpha_boundaries: input AZ-az | A - 1 | Z + 1 | a - 1 | z + 1");
	cr_expect(ft_isalpha('A') == 1);
	cr_expect(ft_isalpha('Z') == 1);
	cr_expect(ft_isalpha('a') == 1);
	cr_expect(ft_isalpha('z') == 1);
	cr_expect(ft_isalpha('A' - 1) == 0);
	cr_expect(ft_isalpha('Z' + 1) == 0);
	cr_expect(ft_isalpha('a' - 1) == 0);
	cr_expect(ft_isalpha('z' + 1) == 0);
}

Test(Character_class_tests, isdigit_boundaries)
{
	cr_expect(ft_isdigit('0') == 1);
	cr_expect(ft_isdigit('9') == 1);
	cr_expect(ft_isdigit('0' - 1) == 0);
	cr_expect(ft_isdigit('9' + 1) == 0);
}

Test(Character_class_tests, isascii_boundaries)
{
	cr_log_info("ISASCII: isascii_boundaries: input | 0 | 127 | -1 | 128 |");
	cr_expect(ft_isascii(0) == 1);
	cr_expect(ft_isascii(127) == 1);
	cr_expect(ft_isascii(-1) == 0);
	cr_expect(ft_isascii(128) == 0);
}

Test(Character_class_tests, isprint_boundaries)
{
	cr_expect(ft_isprint(32) == 1);   /* space */
	cr_expect(ft_isprint(126) == 1);  /* '~'   */
	cr_expect(ft_isprint(31) == 0);   /* before space */
	cr_expect(ft_isprint(127) == 0);  /* DEL */
}

/* --- Out-of-range ints: must be safe and deterministic --- */
Test(Character_class_tests, out_of_range_integers)
{
	/* negatives */
	cr_log_info("TESTING: negative numbers");
	cr_expect(ft_isalpha(-128) == 0);
	cr_expect(ft_isdigit(-1) == 0);
	cr_expect(ft_isalnum(-42) == 0);
	cr_expect(ft_isascii(-1) == 0);
	cr_expect(ft_isprint(-7) == 0);

	/* > 255 */
	cr_log_info("TESTING: > 255");
	cr_expect(ft_isalpha(256) == 0);
	cr_expect(ft_isdigit(1000) == 0);
	cr_expect(ft_isalnum(1024) == 0);
	cr_expect(ft_isascii(200) == 0);
	cr_expect(ft_isprint(9999) == 0);
}

/* --- Invariants between your own functions --- */
Test(Character_class_tests, invariants_relationships)
{
	int c;

	c = -1;
	while (c <= 300)
	{
		int alnum = ft_isalnum(c);
		int alpha = ft_isalpha(c);
		int digit = ft_isdigit(c);
		int pr    = ft_isprint(c);
		int asc   = ft_isascii(c);

		cr_expect(alnum == (alpha || digit), "isalnum != alpha||digit at %d", c);
		if (pr)
			cr_expect(asc == 1, "printable but not ascii at %d", c);
		c++;
	}
}

/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	int	c;

	c = 0;
	while (c < 128)
	{
		if (iscntrl(c))
			printf("ASCII %3d (0x%02X) is control\n", c, c);
		c++;
	}
	return (0);
}
*/