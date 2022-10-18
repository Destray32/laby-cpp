#include <iostream>

void WprowadzenieDanych(float& a, float& b);

int main()
{
	float     a, b;
	bool	czyKonty = true;
	char	status;

	while (czyKonty) {

		WprowadzenieDanych(a, b);

		if (a == 0)
			b == 0 ? std::cout << "Nieskonczona ilosc M.Z\n" : std::cout << "Brak M.Z\n";
		else
			std::cout << "MZF to: " << -(b / a) << "\n";
		
		std::cout << "Czy chcesz kontynuować? Y/N\n";
		std::cin >> status;
		
		status == 'Y' ? czyKonty = true : czyKonty = false;
	}
	return 0;
}

void WprowadzenieDanych(float& a, float& b)
{
	std::cout << "Podaj a\n";
	std::cin >> a;
	std::cout << "Podaj b\n";
	std::cin >> b;

	return;
}