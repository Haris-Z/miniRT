/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_colors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hazunic <hazunic@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 22:20:23 by hazunic           #+#    #+#             */
/*   Updated: 2026/02/26 10:43:29 by hazunic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_COLORS_H
# define PRINT_COLORS_H
// enable disable
# define RT_USE_COLORS 1
// format | reset
# if RT_USE_COLORS
#  define C_RESET		"\033[0m"
#  define C_BOLD		"\033[1m"
#  define C_DIM			"\033[2m"
#  define C_ULINE		"\033[4m"
// std fg colros
#  define C_BLACK		"\033[30m"
#  define C_RED			"\033[31m"
#  define C_GREEN		"\033[32m"
#  define C_YELLOW		"\033[33m"
#  define C_BLUE		"\033[34m"
#  define C_MAGENTA		"\033[35m"
#  define C_CYAN		"\033[36m"
#  define C_WHITE		"\033[37m"
// bright fg colros
#  define C_BRED		"\033[91m"
#  define C_BGREEN		"\033[92m"
#  define C_BYELLOW		"\033[93m"
#  define C_BBLUE		"\033[94m"
#  define C_BMAGENTA	"\033[95m"
#  define C_BCYAN		"\033[96m"
#  define C_BWHITE		"\033[97m"
// bg colors
#  define BG_RED		"\033[41m"
#  define BG_YELLOW		"\033[43m"
#  define BG_BLUE		"\033[44m"
# else
#  define RT_C_RESET	""
#  define RT_C_BOLD		""
#  define RT_C_DIM		""
#  define RT_C_ULINE	""
#  define RT_C_BLACK	""
#  define RT_C_RED		""
#  define RT_C_GREEN	""
#  define RT_C_YELLOW	""
#  define RT_C_BLUE		""
#  define RT_C_MAGENTA	""
#  define RT_C_CYAN		""
#  define RT_C_WHITE	""
#  define RT_C_BRED		""
#  define RT_C_BGREEN	""
#  define RT_C_BYELLOW	""
#  define RT_C_BBLUE	""
#  define RT_C_BMAGENTA	""
#  define RT_C_BCYAN	""
#  define RT_C_BWHITE	""
#  define RT_BG_RED		""
#  define RT_BG_YELLOW	""
#  define RT_BG_BLUE	""
# endif // RT_USE_COLORS

#endif // PRINT_COLORS