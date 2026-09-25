#include "ft_printf.h"

int  ft_putchar(char c)
{
  return (write(1, &c, 1));
}

int  ft_putnbr(long nb)
{
  long  num;
  int  len;
  int  aux;

  len = 0;
  if (nb < 0)
  {
    if (ft_putchar('-') == -1)
	    return (-1);
    len++;
	  nb *= -1;
  }
  num = nb % 10 + '0';
  if (nb > 9)
  {
    aux = ft_putnbr(nb / 10);
    if (aux == -1)
      return (-1);
    len += aux;
  }
  if (ft_putchar(num) == -1)
	  return (-1);
  len++;
  return (len);
}

int  ft_putnbr_hexa(unsigned long nbr, char up)           // печатает число в hexadecimal, то есть в шестнадцатеричной системе.
{
  int  len;
  int  mod;                                              // хранит остаток от деления числа на 16
  char  *base;                                           // указатель на строку, содержащую hexadecimal символы.
  int  aux;

  mod = 0;
  len = 0;
  if (up == 'X')
      base = "0123456789ABCDEF";
  else
		base = "0123456789abcdef";
  if (nbr > 15)
	{
		aux = ft_putnbr_hexa((nbr / 16), up);
		if (aux == -1)
			return (-1);
		len += aux;
	}
	mod = nbr % 16;
	if (write(1, &base[mod], 1) == -1)
		return (-1);
	len += 1;
	return (len);
}
  
int	ft_putstr(char *str1)
{
	int	len;

	if (!str1)
	{
		if (write (1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	len = 0;
	while (*str1 != '\0')
	{
		if (write(1, str1, 1) == -1)
			return (-1);
		len++;
		str1++;
	}
	return (len);
}

int	ft_putptr(void *ptr)                                  // 0x Это стандартный префикс, показывающий: / Следующая часть числа записана в hexadecimal 
{
	int	len;
	int	aux;

	len = 0;
	aux = 0;
	if (ft_putstr("0x") == -1)
		return (-1);
	len += 2;                                            // потому что 0 х первые 2 симвоал 
	aux = ft_putnbr_hexa((unsigned long)ptr, 'x');       // передаём адрес в нашу уже разобранную функцию ft_putnbr_hexa() Она умеет переводить число в hexadecimal.
	if (aux == -1)
		return (-1);
	len += aux;
	return (len);
}


    
