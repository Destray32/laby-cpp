#include <iostream>

#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <map>

void PunktyStartoweIni(int&);

int main()
{
	int		n = 0;
	int		iter = 0;
	int		scianyPokoj1 = 0;
	int 	scianyPokoj2 = 0;
	int		ktoryPokoj = 0;

	PunktyStartoweIni(n);

	std::vector<std::pair<int, int>> cordyJedynek(n);
	std::vector<std::string> mapaPokoju(n);
	std::vector<std::pair<int, int> > historiaKordynatow;
	std::map<std::pair<int, int>, std::string> przynalezKord;
	


	std::cout << "Podaj " << n << " wierszy mapy pokoju\n";
	for (int i = 0; i < n; i++)
	{
		std::cin >> mapaPokoju[i];
	}

	std::cout << "\n";
	for (auto w : mapaPokoju)
	{
		std::cout << w << std::endl;
	}

	// dwuwymiarowa tablica
	std::vector<std::vector<int>> v(n, std::vector<int>(n, 0));

	for (int i = 0; i < mapaPokoju.size(); i++)
	{
		for (int j = 0; j < mapaPokoju[i].size(); j++)
		{
			if (mapaPokoju[i][j] == '.')
			{
				v[i][j] = 1;
				cordyJedynek[iter].first = i;
				cordyJedynek[iter].second = j;
				iter++;
			}
			else if (mapaPokoju[i][j] == '#')
			{
				v[i][j] = 0;
			}
		}
	}

	// glowna pêtla - zliczanie scian w pokojach
	std::pair<int, int> ostatnieKordynaty;
	bool h1 = false;
	bool h2 = false;
	bool h3 = false;
	bool h4 = false;
	for (int i = 0; i < mapaPokoju.size(); i++)
	{
		for (int j = 0; j < mapaPokoju[i].size(); j++)
		{

			if (mapaPokoju[i][j] == '.')
			{
				

				switch (ktoryPokoj)
				{
				case 1:
				{
					if (mapaPokoju[i][j + 1] == '#')
					{
						scianyPokoj1++;
					}
					if (mapaPokoju[i][j - 1] == '#')
					{
						scianyPokoj1++;
					}
					if (mapaPokoju[i + 1][j] == '#')
					{
						scianyPokoj1++;
					}
					if (mapaPokoju[i - 1][j] == '#')
					{
						scianyPokoj1++;
					}
				}
				break;
				case 2:
					if (mapaPokoju[i][j + 1] == '#')
					{
						scianyPokoj2++;
					}
					if (mapaPokoju[i][j - 1] == '#')
					{
						scianyPokoj2++;
					}
					if (mapaPokoju[i + 1][j] == '#')
					{
						scianyPokoj2++;
					}
					if (mapaPokoju[i - 1][j] == '#')
					{
						scianyPokoj2++;
					}
					break;
				default:
					break;
				}

				ostatnieKordynaty.first = i;
				ostatnieKordynaty.second = j;

				historiaKordynatow.push_back({ i, j });
			}
		}
	}

	for (auto i : v)
	{
		for (auto j : i)
		{
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "Kordynaty jedynek\n";
	for (auto j : cordyJedynek)
	{
		std::cout << j.first << " " << j.second << std::endl;
	}
	std::cout << "Ilosc scian w pokoju pierwszym :" << scianyPokoj1 << std::endl;
	std::cout << "Ilosc scian w pokoju drugim :" << scianyPokoj2 << std::endl;
	std::cout << "Test: " << cordyJedynek[1].first << " " << cordyJedynek[1].second << std::endl;
	std::cout << "Test: " << cordyJedynek[3].first << " " << cordyJedynek[3].second << std::endl;
	std::cout << "Ktory pokoj" << ktoryPokoj << std::endl;
}
// notatki
// inny sposob na podejscie do problemu:
// najpierw niech program z inputu obliczy gdzie sa jakie pokoje i od razu zna ich wartosc


// !!
// wpisujemy mape pokoju > iterujemy po mapie, gdy napotkamy kropke liczymy dookola sciany
// !!
// TERAZ: Zczytac wspolrzedne kazdej kropki // ZROBIONE
// i zliczyc ile jest scian wokol niej // ZROBIONE

// pytanie: jak okreslic z jestesmy w tym samym pokoju?
// odpowiedz jezeli roznica cordow jest mniejsza niz 2 to jestesmy w tym samym pokoju


void PunktyStartoweIni(int& n)
{
	std::cout << "Podaj ilosc punktow startowych\n";
	std::cin >> n;
}

