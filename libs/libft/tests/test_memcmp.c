/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:17:39 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/19 18:24:34 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <limits.h>
#include "libft.h"

/* normalize comparison to -1/0/+1 (only sign matters) */
static int sgn(int x)
{
	return (x > 0) - (x < 0);
}

static void run_case(const char *label,
					 const void *a, const void *b, size_t n)
{
	int	r_std;
	int	r_ft;

	r_std = memcmp(a, b, n);
	r_ft  = ft_memcmp(a, b, n);

	printf("%-32s n=%zu  memcmp=%d (%2d)  ft=%d (%2d)%s\n",
		   label, n, r_std, sgn(r_std), r_ft, sgn(r_ft),
		   (sgn(r_std) != sgn(r_ft)) ? "  <-- MISMATCH" : "");
}

int main(void)
{
	/* 1) Equal buffers */
	{
		char a[] = "hello";
		char b[] = "hello";
		run_case("equal bytes", a, b, sizeof a);          /* incl. '\0' */
		run_case("equal prefix only", a, b, 3);
		run_case("n==0 equal", a, b, 0);
	}

	/* 2) First difference early/middle/late */
	{
		char a[] = "hello";
		char b[] = "hezzo";
		run_case("diff early", a, b, sizeof a);
		run_case("diff middle", a, b, 4);
		run_case("diff after n", a, b, 2);                /* expect 0 */
	}

	/* 3) Embedded NULs: memcmp sees bytes after '\0' */
	{
		unsigned char a[] = { 'a', 0x00, 'b', 0x7F };
		unsigned char b[] = { 'a', 0x00, 'c', 0x7F };
		run_case("embed NUL equal prefix", a, b, 2);
		run_case("embed NUL diff after",   a, b, 3);
	}

	/* 4) Bytes >= 128 (signedness pitfall if you forget unsigned) */
	{
		unsigned char a[] = { 0x80, 0x00 };
		unsigned char b[] = { 0x7F, 0x00 };
		run_case("0x80 vs 0x7F", a, b, 2);               /* expect > 0 */
		run_case("0x80 vs 0x7F (1 byte)", a, b, 1);
	}

	/* 5) Overlapping regions (legal for memcmp) */
	{
		char buf[] = "ABCDEFGH";
		run_case("overlap: buf vs buf+1",
				 buf, buf + 1, 7); /* compares "ABCDEFG" vs "BCDEFGH" */
		run_case("overlap: buf+1 vs buf",
				 buf + 1, buf, 7);
		run_case("overlap equal slice",
				 buf, buf, 8);
	}

	/* 6) Different lengths but same prefix */
	{
		char a[] = "prefix\0rest";
		char b[] = "prefix\0REZT";
		run_case("same prefix up to NUL", a, b, 6);      /* 'p'..'x' */
		run_case("include the NUL byte",  a, b, 7);      /* now equal */
		run_case("beyond NUL differ",     a, b, 10);
	}

	/* 7) Binary buffer fuzz (small) */
	{
		unsigned char a[64], b[64];
		for (size_t i = 0; i < sizeof a; ++i) {
			a[i] = (unsigned char)(i * 37u);
			b[i] = a[i];
		}
		run_case("bin equal 64", a, b, 64);
		b[37] ^= 0xFF;
		run_case("bin diff at 37", a, b, 64);
		run_case("bin cut before diff", a, b, 30);       /* expect 0 */
	}

	/* 8) n == 0 with NULL is OK (don’t deref) */
	{
		run_case("NULL/NULL n=0", NULL, NULL, 0);
		/* DO NOT do n>0 with NULL: undefined behavior */
	}
	return (0);
}
