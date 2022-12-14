#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// do sleepowania
#include <chrono>
#include <thread>

void DodajStack(int posX, int posY, std::vector<std::pair<int, int> >& kontenerStack);
bool PrzeszukajHistorie(int posX, int posY, std::vector<std::pair<int, int> >& kontenerHistori);
void DodajHistorie(int posX, int posY, std::vector<std::pair<int, int> >& kontenerHistori, std::vector<std::pair<int, int> >& kontenerStack, size_t stackSize);
int GlownaPetla(std::vector<std::pair<int, int> >& punktyStack, std::vector<std::pair<int, int> >& hisPunktow, const std::vector<std::string>& mapaPokoju);

int main()
{
	int		n = 0;
	int		lPunktowStar = 0;
	int		liczbaScian = 0;
	std::pair<int, int> punktStartowy{ 0,0 };
	
	std::vector<std::pair<int, int> > punktyStack, hisPunktow;
	std::vector<int> sciany;

	// pierwsze dane wejsciowe
	std::cout << "Podaj jaka ilosc wierszy ma miec pokoj: \n";
	std::cin >> n;
	std::vector<std::string> mapaPokoju(n);

	// podawanie ilosci punktow startowych
	std::cout << "Podaj ilosc punktow startowych: \n";
	std::cin >> lPunktowStar;
	std::vector<std::pair<int, int> > punktyStartowe(lPunktowStar);

	std::cout << "Podaj " << n << " wierszy mapy pokoju\n";

	for (int i = 0; i < n; i++)
	{
		std::cin >> mapaPokoju[i];
	}
	
	std::cout << '\n';

	// zapelnianie kontenera z pozycjami startowymi
	int wielkoscKont = punktyStartowe.size();
	std::cout << "Podaj " << lPunktowStar << " punktow startowych: \n";
	for (int i = 0; i < wielkoscKont; i++)
	{
		std::pair<int, int> punkt;
		std::cin >> punkt.first >> punkt.second;

		punktyStartowe[i] = punkt;
	}

	std::cout << "\n\n\n";

	// p?tla 
	int iteracje = 0;
	while (iteracje < lPunktowStar)
	{
		liczbaScian = 0;
		punktyStack.push_back(punktyStartowe[iteracje]);

		liczbaScian = GlownaPetla(punktyStack, hisPunktow, mapaPokoju);

		iteracje++;

		sciany.push_back(liczbaScian);
	}

	std::cout << "\nLiczby scian dla podanych punktow startowych\n";
	for (auto sciana : sciany)
	{
		std::cout << sciana << "\n";
	}
	return 0;
}

/* void DodajStack
* Funkcja dodaje do konteneru stacku wybrane pozycje podane jako argumenty
*/
void DodajStack(int posX, int posY, std::vector<std::pair<int, int> >& kontenerStack)
{
	kontenerStack.push_back({ posX, posY });
}

/* bool PrzeszukajHistorie
* Funkcja sprawdza czy sprecyzowana pozycja (x,y) wyst?puje w kontenerze trackuj?cym histori?. True je?li nie znajduje si?, false 
*/
bool PrzeszukajHistorie(int posX, int posY, std::vector<std::pair<int, int> >& kontenerHistori)
{
	return std::find(kontenerHistori.begin(), kontenerHistori.end(), std::make_pair(posX, posY)) == kontenerHistori.end();
}

/* void DodajHistori?
* Funkcja dodaje pozycj? do historii, po uprzednim sprawdzeniu czy pozycja ta nie pojawi?a si? ju? wcze?niej w historii
*/
void DodajHistorie(int posX, int posY, std::vector<std::pair<int, int> >& kontenerHistori, std::vector<std::pair<int, int> >& kontenerStack, size_t stackSize)
{
	if (PrzeszukajHistorie(posX, posY, kontenerHistori))
		kontenerHistori.push_back(kontenerStack[stackSize]);
}

/* int GlownaPetla
* Glowna petla zawieraj?ca ca?a logik? i algorytm chodzenia po pokoju. Zwraca ilo?? ?cian w aktualnej instancji dla aktualnie przerabianego
* punktu startowego
*/
int GlownaPetla(std::vector<std::pair<int, int> >& punktyStack, std::vector<std::pair<int, int> >& hisPunktow, const std::vector<std::string>& mapaPokoju)
{
	int liczbaScian = 0;
	int iteracje = 0;

	// glowna petla dzialajaca tylko gdy istnieje pozycja na stacku
	while (!punktyStack.empty())
	{
		std::cout << "\033[1A\033[2K";
		std::cout << "\033[1A\033[2K";
		std::cout << "\033[1A\033[2K";
		std::cout << "\033[1A\033[2K";

		std::cout << "Ostatni punkt na stacku " << "x: " << punktyStack[punktyStack.size() - 1].first << " y: " << punktyStack[punktyStack.size() - 1].second << '\n';
		size_t stackSize = punktyStack.size() - 1;

		std::cout << "Punkty na stacku\n";
		for (auto s_v : punktyStack)
		{
			std::cout << s_v.first << " " << s_v.second << " | ";
		}
		std::cout << '\n';

		//std::cout << "Punkty w historii\n\r";
		//for (auto h_v : hisPunktow)
		//{
		//	std::cout << h_v.first << " " << h_v.second;
		//}
		
		// gora
		if (mapaPokoju[punktyStack[stackSize].first - 1][punktyStack[stackSize].second] == '.' && PrzeszukajHistorie(punktyStack[stackSize].first - 1, punktyStack[stackSize].second, hisPunktow))
		{
			// poprzedni punkt pushujemy do historii
			DodajHistorie(punktyStack[stackSize].first, punktyStack[stackSize].second, hisPunktow, punktyStack, stackSize);

			// dodajemy punkt do kt?rego chcemy przej?? na stack
			DodajStack(punktyStack[stackSize].first - 1, punktyStack[stackSize].second, punktyStack);

		}
		// prawo
		else if (mapaPokoju[punktyStack[stackSize].first][punktyStack[stackSize].second + 1] == '.' && PrzeszukajHistorie(punktyStack[stackSize].first, punktyStack[stackSize].second + 1, hisPunktow))
		{
			DodajHistorie(punktyStack[stackSize].first, punktyStack[stackSize].second, hisPunktow, punktyStack, stackSize);

			DodajStack(punktyStack[stackSize].first, punktyStack[stackSize].second + 1, punktyStack);

		}
		// d??
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

		/*std::this_thread::sleep_for(std::chrono::milliseconds(400));*/ // czasowe ograniczenie
		std::cin.get();
	}

	// zliczenie scian kawa?k?w pokoju znajdujacych sie w historii
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

	iteracje++;

	// clearowanie dla nastepnej instancji petli
	punktyStack.clear();
	hisPunktow.clear();
	return liczbaScian;
}

