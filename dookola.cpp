#include <iostream>

#include <vector>
#include <string>
#include <cstdlib>

void PunktyStartoweIni(int&);

int main()
{
	int		n = 0;
	int		iter = 0;
	int		scianyPokoj1 = 0;
	int 	scianyPokoj2 = 0;
	int		ktoryPokoj = 0;

	PunktyStartoweIni(n);

	std::vector< std::pair<int, int> > cordyJedynek(n);
	std::vector< std::pair<int, int> > cordHis;
	std::vector<std::string> mapaPokoju(n);

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
	for (int i = 0; i < mapaPokoju.size(); i++)
	{
		for (int j = 0; j < mapaPokoju[i].size(); j++)
		{

			if (mapaPokoju[i][j] == '.')
			{
				// sprawdzenie czy punkt dookola nie styka sie z zadna jedynka
				if
					(
					std::find(cordHis.begin(), cordHis.end(), std::make_pair(i, j + 1)) == cordHis.end()	&&
					std::find(cordHis.begin(), cordHis.end(), std::make_pair(i, j - 1)) == cordHis.end()	&&
					std::find(cordHis.begin(), cordHis.end(), std::make_pair(i + 1, j)) == cordHis.end()	&&
					std::find(cordHis.begin(), cordHis.end(), std::make_pair(i - 1, j)) == cordHis.end()
					)
				{
					ktoryPokoj++;
				}

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

				cordHis.push_back({ i, j });
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

	std::cout << "Historia wszystkich kordynatów: \n";
	for (auto h : cordHis)
	{
		std::cout << h.first << " " << h.second << std::endl;
	}

	std::cout << "Kordynaty jedynek\n";
	for (auto j : cordyJedynek)
	{
		std::cout << j.first << " " << j.second << std::endl;
	}
	std::cout << "Ilosc scian w pokoju pierwszym :" << scianyPokoj1 << std::endl;
	std::cout << "Ilosc scian w pokoju drugim :" << scianyPokoj2 << std::endl;
}

// notatki
// nowy algorytm
// jesli nowa jedynka jest oddalona tylko o 1 w osi x lub osi y(tylko i wylacznie w jednym na raz)
// od jakiegokolwiek punktu w historii kordynatów to jest to ten sam pokoj
// jesl nie to jest to inny pokoj

// problem z przekatnymi ale - jesl sprawdzamy po przekatnej to przecie¿ liczby nie sa w 
// historii wiec chyba mozna sprobwac sprawdzania?


void PunktyStartoweIni(int& n)
{
	std::cout << "Podaj ilosc punktow startowych\n";
	std::cin >> n;
}