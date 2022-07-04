#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h> 
#include<fstream>
using namespace std;


void print_drp(vector <vector<int>> drp, const int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (drp[i][j] == 0)
				cout << "_ ";
			else
				cout << "# ";
		} 
		cout << endl;
	}
}

int counter_of_live(vector <vector<int>> drp, const int size, int x, int y)
{
	int count = 0;
	//считаем живые клетки вокруг
	for (int i = max(x - 1, 0); i <= min(x + 1, size - 1); i++) 
	{
		for (int j = max(y - 1, 0); j <= min(y + 1, size - 1); j++) 
		{
			if (drp[i][j] == 1)
				count++;
		}
	}
	// вычитаем, если рассматриваемая живая, т.к. выше не учли это
	if (drp[x][y] == 1)
		count--;

	return count;
}

int evolution(vector <vector<int>>& drp, const int size)
{
	int dead = 0;
	int live = 0;
	vector <vector<int>> newDrp(21, vector<int>(size));
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			switch (drp[i][j])
			{
			case 0:
			{
				int live = counter_of_live(drp, size, i, j);
				if (live == 3)
				{
					newDrp[i][j] = 1;
				}
				else
				{
					newDrp[i][j] = 0;
				}
				break;
			}
			case 1:
			{
				int live = counter_of_live(drp, size, i, j);
				if (live < 2 || live>3)
				{
					newDrp[i][j] = 0;
					dead++;
				}
				else
				{
					newDrp[i][j] = 1;
				}
				break;
			}
			}
		}
	}
	drp = newDrp;
	return dead;
}

void load(vector <vector<int>>& drp, const int size, int& argc, char* argv[])
{
	ifstream loadf;
	string file_name;

	if (argc > 1)
	{
		file_name = argv[1];	
		loadf.open(file_name);
	}

	while (!(loadf.is_open()))
	{
		cout << "File for load is not found." << endl;
		cout << "Enter file name: ";
		cin >> file_name;
		loadf.open(file_name);
	}

	cout << "Open from " << file_name << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			loadf >> drp[i][j];
		}
	}
	loadf.close();
}

void save(vector <vector<int>>& drp, const int size, int dead, int& argc, char* argv[])
{
	ofstream savef;
	static string file_name;
	static bool check = false;

	if (check == false)
	{
		if (argc > 2)
			savef.open(argv[2], ios::app);

		while (!(savef.is_open()))
		{
			cout << "File for save is not found." << endl;
			cout << "Enter file name: ";
			cin >> file_name;
			savef.open(file_name, ios::app);
		}
		check = true;
	}
	else
	{
		savef.open(file_name, ios::app);
	}

	savef << dead << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (drp[i][j] == 0)
				savef << "_ ";
			else
				savef << "# ";
		}
		savef << endl;
	}
	savef.close();
}

void menu(vector <vector<int>>& drp, const int size, int& argc, char* argv[])
{
	char key;
	int key_int = 0;
	int dead = 0;
	for(;;)
	{
		cout << "Select the number of iterations from 1 to 9" << endl;
		key = _getch();
		key_int = key - '0';
		if (key == 27)
			break;
   		if ((unsigned int)key < 58 && (unsigned int)key > 47) 
		{
			for (int i = 0; i < key_int; i++)
			{
				dead = evolution(drp, size);
			}
			print_drp(drp, size);
			system("pause");
			system("cls");
			save(drp, size, dead, argc, argv);
		}
	
	} 
	
}

int main(int argc, char* argv[])
{
	const int size = 21;
	vector < vector <int> > drp(size, vector <int>(size));
	load(drp, size, argc, argv);
	menu(drp, size, argc, argv);
}

