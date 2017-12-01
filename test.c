#include "Includes/libft.h"
#include <locale.h>

int	main(void)
{
	setlocale(LC_ALL, "");
	ft_printf("%s", "lel\n");
	ft_printf("%s\ntest : [%S]\n", "test", L"⾶⾶oklm⾶");
	return (0);
}
