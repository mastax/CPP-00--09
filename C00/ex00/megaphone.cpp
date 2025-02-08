/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elel-bah <elel-bah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:54:35 by elel-bah          #+#    #+#             */
/*   Updated: 2025/02/08 17:59:33 by elel-bah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int arc, char **content)
{
	int		y;

	if (arc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << "\n";
		return (0);
	}
	for (int x = 1; content[x]; x++)
	{
		for (y = 0; content[x][y]; y++)
			std::cout << (char)toupper(content[x][y]);
	}
	return (0);
}