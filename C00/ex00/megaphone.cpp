#include <iostream>

int main(int count, char **strings)
{
	int		j;

	if (count == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << "\n";
		return (0);
	}
	for (int i = 1; strings[i]; i++)
	{
		for (j = 0; strings[i][j]; j++)
			std::cout << (char)toupper(strings[i][j]);
	}
	return (0);
}