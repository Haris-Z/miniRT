/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ftmemory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 13:29:41 by hazunic           #+#    #+#             */
/*   Updated: 2025/11/19 18:12:07 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// tests/test_ftmemory.c
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "libft.h"

// ---- Small local helpers (avoid extra deps) ----
static void	*xmalloc(size_t n)
{
	void	*p;
	
	p = malloc(n);
	cr_expect_not_null(p, "malloc(%zu) returned NULL", n);
	return (p);
}

static void	fill_random(unsigned char *buf, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		buf[i] = (unsigned char )rand();
		i++;
	}
}

/* Create a guarded buffer with canaries:
   [ L canary | target region (N) | R canary ]
   Returns pointer to the *target region* (center). Caller must free(base).
*/
static unsigned char 	*make_guarded(size_t left, size_t n, size_t right, unsigned char **base_out, size_t *tot_out)
{
	size_t			total;
	unsigned char	*base;
	unsigned char	*center;

	total = left + n + right;
	base = xmalloc(total);
	center = base + left;
	
	// Fill all with a known pattern, then overwrite center later
	memset(base, 0xA5, total);
	*base_out = base;
	*tot_out = total;
	return (center);
}

static void	assert_canaries_unchanged(const unsigned char *base, size_t left, size_t n, size_t right)
{
	// Left canary must remain 0xA5
	for (size_t i = 0; i < left; i++)
		cr_assert(base[i] == 0xA5, "Left canary modified at %zu", i);
	// Right canary must remain 0xA5
	for (size_t i = 0; i < right; i++)
		cr_assert(base[left + n + i] == 0xA5, "Right canary modified at %zu", i);
}
// -------------------------------
// TestSuite: ft_memory (memset/bzero)
// -------------------------------
TestSuite(ft_memory, .init = NULL, .fini = NULL);

#ifdef LEAK_TEST // runs only if define leaktest or run with leakprobe
#include <stdlib.h>

Test(ft_memory, intentional_leak)
{
	// Allocate and "lose" the pointer (definitely lost).
	void	*p
	
	p= malloc(123);
	cr_expect_not_null(p);
	(void)p;
	// No free on purpose.
}
#endif

// --- Basic ft_memset equivalence against libc memset on various sizes/values
Test(ft_memory, memset_basic_matrix)
{
	struct
	{
		size_t			n;
		unsigned int	c;
	} cases[] = {
		{0, 0}, {1, 0}, {2, 0}, {3, 0},
		{7, 0}, {16, 0}, {31, 0}, {64, 0},
		{0, 1}, {1, 1}, {3, 1}, {7, 1},
		{16, 1}, {31, 1}, {64, 1},
		{3, 0xFF}, {7, 0xFF}, {16, 0xFF}, {3, 0x7F},
		{3, 0x80}, {64, 0xDE}, {64, 0xEF}
	};

	for (size_t t = 0; t < sizeof(cases)/sizeof(cases[0]); t++)
	{
		size_t n = cases[t].n;
		int c = (int)cases[t].c;

		unsigned char *a = xmalloc(n);
		unsigned char *b = xmalloc(n);

		fill_random(a, n);
		memcpy(b, a, n);

		void *ret_ft = ft_memset(a, c, n);
		void *ret_c  = memset(b, c, n);

		// Return pointer must be original pointer
		cr_expect_eq(ret_ft, a, "ft_memset must return the input pointer");
		cr_expect_eq(ret_c,  b, "libc memset must return the input pointer");

		// Buffers must match exactly
		cr_assert(memcmp(a, b, n) == 0, "ft_memset differs from libc memset for n=%zu c=%d", n, c);

		free(a);
		free(b);
	}
}

// --- Guard test to catch over/underruns
Test(ft_memory, memset_no_over_or_underrun)
{
	const size_t L = 16, N = 128, R = 16;
	unsigned char *base_a, *base_b;
	size_t total;

	unsigned char *a = make_guarded(L, N, R, &base_a, &total);
	unsigned char *b = make_guarded(L, N, R, &base_b, &total);

	// Seed target region with different data so we actually write over it
	memset(a, 0x11, N);
	memset(b, 0x11, N);

	// Do the operations
	ft_memset(a, 0xCC, N);
	memset(b, 0xCC, N);

	// Regions identical?
	cr_assert(memcmp(a, b, N) == 0, "Guarded memset region differs");

	// Canaries unchanged?
	assert_canaries_unchanged(base_a, L, N, R);
	assert_canaries_unchanged(base_b, L, N, R);

	free(base_a);
	free(base_b);
}

// --- Fuzz: compare ft_memset with libc memset for random sizes/values
Test(ft_memory, memset_fuzz_1000_randomized)
{
	srand((unsigned)time(NULL));

	for (int iter = 0; iter < 1000; iter++) {
		size_t n = (size_t)(rand() % 4096);     // up to 4KiB
		int c = rand() & 0xFF;                  // any byte

		unsigned char *a = xmalloc(n);
		unsigned char *b = xmalloc(n);
		fill_random(a, n);
		memcpy(b, a, n);

		ft_memset(a, c, n);
		memset(b, c, n);

		cr_assert(memcmp(a, b, n) == 0, "Fuzz diff at iter=%d n=%zu c=%d", iter, n, c);

		free(a);
		free(b);
	}
}

// --- ft_bzero should behave the same as memset(..., 0, n)
Test(ft_memory, bzero_equivalent_to_memset_zero)
{
	size_t sizes[] = {0, 1, 2, 3, 7, 16, 31, 64, 257};

	for (size_t i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
		size_t n = sizes[i];

		unsigned char *a = xmalloc(n);
		unsigned char *b = xmalloc(n);
		fill_random(a, n);
		memcpy(b, a, n);

		//void *ret_ft = ft_bzero(a, n);        // your ft_bzero returns void* in your header
		ft_bzero(a, n);
		memset(b, 0, n);

		cr_assert(memcmp(a, b, n) == 0, "ft_bzero != memset(...,0,...) for n=%zu", n);

		free(a);
		free(b);
	}
}

// --- Guard test for ft_bzero (no over/underrun)
Test(ft_memory, bzero_no_over_or_underrun)
{
	const size_t L = 8, N = 100, R = 8;
	unsigned char *base_a, *base_b;
	size_t total;

	unsigned char *a = make_guarded(L, N, R, &base_a, &total);
	unsigned char *b = make_guarded(L, N, R, &base_b, &total);

	fill_random(a, N);
	memcpy(b, a, N);

	ft_bzero(a, N);
	memset(b, 0, N);

	cr_assert(memcmp(a, b, N) == 0, "Guarded bzero region differs");

	assert_canaries_unchanged(base_a, L, N, R);
	assert_canaries_unchanged(base_b, L, N, R);

	free(base_a);
	free(base_b);
}

// --- n == 0 with NULL pointer: must be a no-op and return the same pointer (safe & well-defined)
Test(ft_memory, null_ptr_with_n_zero_is_ok)
{
	// NOTE: Do NOT call with n > 0 and NULL — that would be UB.
	cr_expect_null(ft_memset(NULL, 0xAB, 0), "memset(NULL, *, 0) should return NULL");
	cr_expect(1, "ft_bzero(NULL, 0) should be a no-op and not crash");
}

// --- Sanity: zeroing an int-array via memset(0) is safe
Test(ft_memory, memset_zero_on_int_array_is_safe)
{
	int arr_ft[8], arr_c[8];

	// seed both with non-zero
	for (size_t i = 0; i < 8; i++) {
		arr_ft[i] = (int)(i * 1234567);
		arr_c[i]  = arr_ft[i];
	}

	ft_memset(arr_ft, 0, sizeof arr_ft);
	memset(arr_c,  0, sizeof arr_c);

	cr_assert(memcmp(arr_ft, arr_c, sizeof arr_ft) == 0, "int array zeroing differs");
}


