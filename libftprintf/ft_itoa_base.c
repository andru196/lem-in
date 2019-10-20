/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycorrupt <ycorrupt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 14:52:41 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/06/25 22:04:52 by ycorrupt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(long long int n, int base)
{
	char				*result;
	unsigned long long	copy_n;
	int					r;

	copy_n = n < 0 && base == 10 ? -(long long int)n : (unsigned long long)n;
	r = n < 0 && base == 10 ? 2 : 1;
	while (copy_n /= (base == 0 ? 10 : base))
		r++;
	if (!(result = (char *)malloc(sizeof(char) * (r + 1))))
		return (NULL);
	copy_n = n < 0 && base == 10 ? -(long long int)n : (unsigned long long)n;
	if (n < 0 && base == 10)
		result[0] = '-';
	result[r] = '\0';
	result[0] = copy_n == 0 ? '0' : result[0];
	while (copy_n)
	{
		n = copy_n % (base == 0 ? 10 : base);
		result[r - 1] = n + (n > 9 ? 'a' - 10 : '0');
		--r;
		copy_n /= (base == 0 ? 10 : base);
	}
	return (result);
}
