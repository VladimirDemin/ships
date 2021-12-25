#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
int main()
{
	ifstream fin("Ships.in.txt");
	ofstream fout("Ships.out.txt");

	if (!fin)
	{
		cout << "File is not open";
		return 0;
	}

	else
	{
		if (fin.peek() == EOF)
		{
			fout << "Error! The file is empty!";
			return 0;
		}

		int N;
		fin >> N;
		if (N < 1 || N > 10)
		{
			fout << "Error! The number of berths should be from 1 to 10.";
		}
		int first_free_place = 1;//Первое по счету место, свободное для кораблей. 
		vector <string> raid;
		vector <int> place;
		vector <string> ships_in_port;
		place.resize(N);
		ships_in_port.resize(N);

		while (!fin.eof())
		{
			int event;
			fin >> event;
			switch (event)
			{
			case 1:
			{
				string new_ship;
				getline(fin, new_ship);
				if (first_free_place == 0)
				{
					raid.push_back(new_ship);//Если нет свободных мест - отправляем корабль на рейд
				}
				else
				{
					place[first_free_place - 1] = 1;
					ships_in_port[first_free_place - 1] = new_ship;
					int i = first_free_place - 1;
					first_free_place = 0;
					for (; i < N; i++)
					{
						if (place[i] == 0)
						{
							first_free_place = i + 1;//Новое первое по счету свободное место будет с номером на один больше
							break;
						}
					}
				}
				break;
			}
			case 2:
			{
				int ship_number;
				fin >> ship_number;
				if (ship_number < first_free_place || first_free_place == 0)
				{
					first_free_place = ship_number;
				}
				if (raid.size() != 0)//Если корабли стоят в очереди, забираем оттуда первый по счету корабль.
				{
					place[first_free_place - 1] = 1;
					ships_in_port[first_free_place - 1] = raid[0];//добавляем первый элемент очереди.
					raid.erase(raid.begin());//удаляем первый элемент из очереди.
					first_free_place = 0;
				}
				break;
			}
			case 3:
			{
				fout << "Information about the ships on the raid:" << endl;
				if (raid.size())
				{
					for (auto ships : raid)//Перебираем элементы вектора
					{
						fout << ships << endl;
					}
				}
				else
				{
					fout << "There is no ship on the raid." << endl;
				}
				break;

			}
			case 4:
			{
				fout << "Information about the ships on the berths:" << endl;
				for (int i = 0; i < N; i++)
				{
					fout << "Ship on the " << i + 1 << " berth is: ";
					if (place[i] == 1)
					{
						fout << ships_in_port[i] << endl;
					}
					else
					{
						fout << "There is no ship on this berth." << endl;
					}
				}
				break;
			}
			default:
				break;
			}
		}
	}
	fin.close();
	fout.close();
	return 0;
}
