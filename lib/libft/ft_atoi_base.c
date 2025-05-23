#include "libft.h"

/*
Extracts the numerical value of a character representing a digit in a
specified base.
Returns the numerical value of the digit if it's valid for the base,
otherwise returns -1.
*/
static int	get_digit(char c, int digit_base)
{
	int	max_digit;

	if (digit_base <= 10)
		max_digit = digit_base + '0';
	else
		max_digit = digit_base - 11 + 'a';
	if (c >= '0' && c <= '9' && c <= max_digit)
		return (c - '0');
	else if (c >= 'a' && c <= 'f' && c <= max_digit)
		return (10 + c - 'a');
	else
		return (-1);
}

/*
Converts a string representation of a number in a specified base
to its integer equivalent. Handles both positive and negative numbers.
Case-insensitive.
*/
int	ft_atoi_base(const char *str, int str_base)
{
	int	result;
	int	sign;
	int	digit;

	result = 0;
	sign = 1;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	digit = get_digit(ft_tolower(*str), str_base);
	while (digit >= 0)
	{
		result = result * str_base;
		result = result + (digit * sign);
		str++;
		digit = get_digit(ft_tolower(*str), str_base);
	}
	return (result);
}
