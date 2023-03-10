/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marai <masadevs@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:35:31 by marai             #+#    #+#             */
/*   Updated: 2023/02/19 11:47:43 by marai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/push_swap.h"
#include <stdio.h>
#include <stdlib.h>

ssize_t			is_nodes_ordered(t_node *stack);
void			see_node(t_node *stack);
static ssize_t	push_const_node(t_node *stack_a, t_node *stack_b,
					ssize_t a_activelen);
ssize_t			push_bigger_nodes(t_node *stack1, t_node *stack2,
					ssize_t activelen, ssize_t stacknum);
ssize_t			push_smaller_nodes(t_node *stack1, t_node *stack2,
					ssize_t activelen, ssize_t stacknum);

void	push_swap(t_node *stack_a, t_node *stack_b, ssize_t a_activelen,
		ssize_t b_activelen)
{
	ssize_t	movedlen;

	while (!is_nodes_ordered(stack_a) || b_activelen != 0)
	{
		movedlen = 0;
//		print(stack_a, stack_b);
		while (6 < b_activelen)
		{
			movedlen = push_bigger_nodes(stack_b, stack_a, b_activelen, 0);
			a_activelen += movedlen;
			b_activelen -= movedlen;
		}
		sort_node_under6(stack_b, stack_a, b_activelen, 0);
		while (0 < b_activelen)
		{
			push_headnode(stack_a, stack_b, 1);
			rotate_stack(stack_a, 1);
			b_activelen--;
		}
		b_activelen = push_const_node(stack_a, stack_b, a_activelen);
		a_activelen -= b_activelen;
	}
}

static ssize_t	push_const_node(t_node *stack_a, t_node *stack_b,
		ssize_t a_activelen)
{
	ssize_t	sortedlen;
	ssize_t	stacklen;
	ssize_t	b_activelen;

	stacklen = get_node_len(stack_a);
	sortedlen = stacklen - a_activelen;
	while (sortedlen < (stacklen - 1) / 2)
		stacklen /= 2;
	b_activelen = 0;
	while (b_activelen < stacklen - sortedlen && a_activelen)
	{
		push_headnode(stack_b, stack_a, 0);
		a_activelen--;
		b_activelen++;
	}
	return (b_activelen);
}

ssize_t	push_bigger_nodes(t_node *stack1, t_node *stack2, ssize_t activelen,
		ssize_t stacknum)
{
	ssize_t	i;
	ssize_t	swappednum;
	int		threshold;
	t_node	*nownode1;

	threshold = nth_small_num(stack1, activelen / 2, activelen);
	printf("threshhold %d\n", threshold);
	i = 0;
	swappednum = 0;
	while (i < activelen)
	{
		nownode1 = stack1->next;
		if (threshold < nownode1->compressed_num)
		{
			push_headnode(stack2, stack1, stacknum + 1);
			swappednum++;
		}
		else
			rotate_stack(stack1, stacknum);
		i++;
	}
	return (swappednum);
}

ssize_t	push_smaller_nodes(t_node *stack1, t_node *stack2, ssize_t activelen,
		ssize_t stacknum)
{
	ssize_t	i;
	ssize_t	swappednum;
	int		threshold;
	t_node	*nownode1;

	threshold = nth_small_num(stack1, activelen / 2, activelen);
	i = 0;
	swappednum = 0;
	while (i < activelen)
	{
		nownode1 = stack1->next;
		if (nownode1->compressed_num <= threshold)
		{
			push_headnode(stack2, stack1, stacknum + 1);
			swappednum++;
		}
		else
			rotate_stack(stack1, stacknum);
		i++;
	}
	return (swappednum);
}

ssize_t	is_nodes_ordered(t_node *stack)
{
	t_node	*nownode;
	int		previousnum;

	nownode = stack->next;
	previousnum = stack->next->compressed_num;
	while (nownode != stack)
	{
		if (nownode->compressed_num < previousnum)
			return (0);
		previousnum = nownode->compressed_num;
		nownode = nownode->next;
	}
	return (1);
}

void	see_node(t_node *stack)
{
	t_node	*nownode;

	nownode = stack->next;
	while (nownode != stack)
	{
		printf("inside %d\n", nownode->compressed_num);
		nownode = nownode->next;
	}
}

void	print(t_node *stack_a, t_node *stack_b)
{
	printf("------stack_a num-------\n");
	printf("stack_a num %ld\n", get_node_len(stack_a));
	printf("--------stack_a----------\n");
	see_node(stack_a);
	printf("------stack_b num-------\n");
	printf("stack_b num %ld\n", get_node_len(stack_b));
	printf("--------stack_b----------\n");
	see_node(stack_b);
	printf("\n\n");
}
