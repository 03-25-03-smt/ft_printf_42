#include "ft_printf.h"

static int	ft_conversion(const char type, va_list vargs)                      // const char type / type — это символ после %.
{
	if (type == 'c')
		return (ft_putchar(va_arg(vargs, int)));                                   // va_arg(vargs, int) Возьми следующий аргумент из vargs и считай, что он имеет тип int
	else if (type == 'u')                                                        // %u означает - unsigned decimal integer.
		return (ft_putnbr(va_arg(vargs, unsigned int)));
	else if ((type == 'i') || (type == 'd'))                                     // %d & %i оба получают int / оба conversion
		return (ft_putnbr(va_arg(vargs, int)));
	else if (type == 's')
		return (ft_putstr(va_arg(vargs, char *)));
	else if (type == 'x' || type == 'X')
		return (ft_putnbr_hexa(va_arg(vargs, unsigned int), type));
	else if (type == 'p')                                                        // Берём следующий аргумент как: void * и передаём его в: ft_putptr() 
		return (ft_putptr(va_arg(vargs, void *)));
	else if (type == '%')                                                        // %% не требует никакого аргумента. / Например: ft_printf("100%%"); должно вывести: 100%
		return (ft_putchar('%'));
	return (-1);                                                                // Это означает: Переданный type не поддерживается.
}

int	ft_printf(char const *str, ...)                                           //  char const *str Это первая обязательная переменная — форматная строка. / ... — variadic arguments. -> после str можно передать сколько угодно аргументов
{
	va_list	vargs;                                                              // Хранит информацию, необходимую для работы с ...
	int		len;                                                                  // Общее количество символов, которое ft_printf() уже напечатал.
	int		check;                                                                // Сюда помещается результат: ft_conversion(...)

	va_start(vargs, str);                                                      // Это инициализация работы с ....
	len = 0;
	while (*str)
	{
		if (*str == '%')
		{
			check = ft_conversion(*(++str), vargs);
			if (check == -1)
				return (-1);
			len += check;
		}
		else
		{
			if (write(1, str, 1) == -1)
				return (-1);
			len++;
		}
		str++;
	}
	va_end(vargs);
	return (len);
}
