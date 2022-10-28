#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void DodajStack(int posX, int posY, std::vector<std::pair<int, int> >& kontenerStack);
bool PrzeszukajHistorie(int posX, int posY, std::vector<std::pair<int, int> >& kontenerHistori);
void DodajHistorie(int posX, int posY, std::vector<std::pair<int, int> >& kontenerHistori, std::vector<std::pair<int, int> >& kontenerStack, size_t stackSize);

int main()
{
	int		n = 0;
	int		liczbaScian = 0;
	std::pair<int, int> punktStartowy{ 0,0 };
	std::vector<std::pair<int, int> > punktyStack, hisPunktow;

	// pierwsze dane wejsciowe: ilosc punktów startowych
	std::cin >> n;
	std::vector<std::string> mapaPokoju(n);

	std::cout << "Podaj " << n << " wierszy mapy pokoju\n";

	for (int i = 0; i < n; i++)
	{
		std::cin >> mapaPokoju[i];
	}

	std::cout << "Podaj punkt startowy\n";
	std::cin >> punktStartowy.first >> punktStartowy.second;
	punktyStack.push_back(punktStartowy);


	// na poczatku na staku jest punkt startowy
	while (!punktyStack.empty())
	{
		std::cout << "Ostatni punkt na stacku x: " << punktyStack[punktyStack.size() - 1].first << " y: " << punktyStack[punktyStack.size() - 1].second << '\n';
		size_t stackSize = punktyStack.size() - 1;

		std::cout << "Punkty na stacku\n";
		for (auto s_v : punktyStack)
		{
			std::cout << s_v.first << " " << s_v.second << '\n';
		}

		std::cout << "Punkty w historii\n";
		for (auto h_v : hisPunktow)
		{
			std::cout << h_v.first << " " << h_v.second << '\n';
		}


		// gora
		if (mapaPokoju[punktyStack[stackSize].first - 1][punktyStack[stackSize].second] == '.' && PrzeszukajHistorie(punktyStack[stackSize].first - 1, punktyStack[stackSize].second, hisPunktow))
		{
			// poprzedni punkt pushujemy do historii
			DodajHistorie(punktyStack[stackSize].first, punktyStack[stackSize].second, hisPunktow, punktyStack, stackSize);

			// dodajemy punkt do którego chcemy przejœæ na stack
			DodajStack(punktyStack[stackSize].first - 1, punktyStack[stackSize].second, punktyStack);
			
		}
		// prawo
		else if (mapaPokoju[punktyStack[stackSize].first][punktyStack[stackSize].second + 1] == '.' && PrzeszukajHistorie(punktyStack[stackSize].first, punktyStack[stackSize].second + 1, hisPunktow))
		{
			DodajHistorie(punktyStack[stackSize].first, punktyStack[stackSize].second, hisPunktow, punktyStack, stackSize);

			DodajStack(punktyStack[stackSize].first, punktyStack[stackSize].second + 1, punktyStack);

		}
		// dó³
		else if (mapaPokoju[punktyStack[stackSize].first + 1][punktyStack[stackSize].second] == '.' && PrzeszukajHistorie(punktyStack[stackSize].first + 1, punktyStack[stackSize].second, hisPunktow))
		{
			DodajHistorie(punktyStack[stackSize].first, punktyStack[stackSize].second, hisPunktow, punktyStack, stackSize);

			DodajStack(punktyStack[stackSize].first + 1, punktyStack[stackSize].second, punktyStack);

		}
		// lewo
		else if (mapaPokoju[punktyStack[stackSize].first][punktyStack[stackSize].second - 1] == '.' && PrzeszukajHistorie(punktyStack[stackSize].first, punktyStack[stackSize].second - 1, hisPunktow))
		{
			DodajHistorie(punktyStack[stackSize].first, punktyStack[stackSize].second, hisPunktow, punktyStack, stackSize);

			DodajStack(punktyStack[stackSize].first, punktyStack[stackSize].second - 1, punktyStack);

		}
		// brak valid pokojow w poblizu
		else
		{
			DodajHistorie(punktyStack[stackSize].first, punktyStack[stackSize].second, hisPunktow, punktyStack, stackSize);
			punktyStack.pop_back();
		}

		std::cin.get();
	}

	std::cout << "\n";
	for (auto w : mapaPokoju)
	{
		std::cout << w << std::endl;
	}

	for (auto punkt : hisPunktow)
	{
		if (mapaPokoju[punkt.first - 1][punkt.second] == '#')
		{
			liczbaScian++;
		}
		if (mapaPokoju[punkt.first][punkt.second + 1] == '#')
		{
			liczbaScian++;
		}
		if (mapaPokoju[punkt.first + 1][punkt.second] == '#')
		{
			liczbaScian++;
		}
		if (mapaPokoju[punkt.first][punkt.second - 1] == '#')
		{
			liczbaScian++;
		}
	}

	std::cout << "ILOSC SCIAN w pokoju z podanego punktu startowego: " << liczbaScian;

	return 0;
}

void DodajStack(int posX, int posY, std::vector<std::pair<int, int> >& kontenerStack)
{
	kontenerStack.push_back({ posX, posY });
}

bool PrzeszukajHistorie(int posX, int posY, std::vector<std::pair<int, int> >& kontenerHistori)
{
	return std::find(kontenerHistori.begin(), kontenerHistori.end(), std::make_pair(posX, posY)) == kontenerHistori.end();
}

void DodajHistorie(int posX, int posY, std::vector<std::pair<int, int> >& kontenerHistori, std::vector<std::pair<int, int> >& kontenerStack, size_t stackSize)
{
	if (PrzeszukajHistorie(posX, posY, kontenerHistori))
		kontenerHistori.push_back(kontenerStack[stackSize]);
}

