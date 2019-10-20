/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfalia-f <sfalia-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:17:05 by sfalia-f          #+#    #+#             */
/*   Updated: 2019/10/19 22:35:20 by sfalia-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_any_array(size_t count, size_t n)
{
	t_array	*res;

	if (!count || !(res = ft_memalloc(n)))
		return (0);
	if (!(res->ptr = ft_memalloc(SIZE(void*, count))))
	{
		free(res);
		return (0);
	}
	res->max = count;
	return (res);
}

void	*ft_array(size_t count)
{
	return (ft_any_array(count, sizeof(t_array)));
}

void	*ft_array_push(void *ary, void *ptr)
{
	t_array	*ary_tmp;
	void	**tmp;

	ary_tmp = ary;
	if (!ary_tmp)
		return (0);
	if (ary_tmp->len >= ary_tmp->max)
	{
		ary_tmp->max *= 3;
		if (!(tmp = ft_memalloc(SIZE(void*, ary_tmp->max))))
			return (0);
		ft_memcpy(tmp, ary_tmp->ptr, SIZE(void*, ary_tmp->len));
		free(ary_tmp->ptr);
		ary_tmp->ptr = tmp;
	}
	return (ary_tmp->ptr[ary_tmp->len++] = ptr);
}

void	*ft_array_free(void *ary)
{
	t_array	*ary_tmp;

	ary_tmp = ary;
	if (ary_tmp && ary_tmp->ptr)
		free(ary_tmp->ptr);
	free(ary_tmp);
	return (0);
}
