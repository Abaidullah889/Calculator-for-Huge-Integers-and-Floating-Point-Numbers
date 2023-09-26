#include "Bscs22133HugeFloat.h"
#include "Bscs22133HexaInt.h"
#include"Bscs22133HexaFloat.h"
#include<iostream>
#include<fstream>
using namespace std;

void LoadAllFloats(string filename,HugeFloat*&N, int&fsize)
{
	ifstream rdr(filename);
	rdr >> fsize;
	N = new HugeFloat[fsize];
	for (int i = 0; i < fsize; i++)
	{
		while (rdr.peek() == '\n' || rdr.peek() == ' ' || rdr.peek() == '	')
		{
			rdr.ignore();
		}
		N[i].Load(rdr);
	}
}
void PrintAllFloats(HugeFloat* N, int size)
{
	cout << size<<endl;
	for (int i = 0; i < size; i++)
	{
		N[i].Pirnt();
		cout << endl;
	}
}
void WriteAllHugeFloat(HugeFloat* k, int isize)
{
	ofstream wtr("bscs22133writeHugeFloat.txt");
	wtr << isize;
	wtr << endl;
	for (int i = 0; i < isize; i++)
	{
		wtr << k[i];
		wtr << endl;
	}
}


void LoadAllHexaInt(string filename, HexaInt*& N, int& fsize)
{
	int base;
	ifstream rdr(filename);
	rdr >> base;
	while (rdr.peek() == '\n' || rdr.peek() == ' ' || rdr.peek() == '	')
	{
		rdr.ignore();
	}
	rdr >> fsize;
	N = new HexaInt[fsize];
	for (int i = 0; i < fsize; i++)
	{
		while (rdr.peek() == '\n' || rdr.peek() == ' ' || rdr.peek() == '	')
		{
			rdr.ignore();
		}
		N[i].Load(rdr);
		N[i].Setbase(base);
	}
}
void PrintAllHexaInt(HexaInt* N, int size)
{
	cout << size << endl;
	for (int i = 0; i < size; i++)
	{
		N[i].Print();
		cout << endl;
	}
}
void WriteAllHexaInt(HexaInt* k, int isize)
{
	ofstream wtr("bscs22133writeHexaInt.txt");
	wtr << isize;
	wtr << endl;
	for (int i = 0; i < isize; i++)
	{
		wtr << k[i];
		wtr << endl;
	}
}

void LoadAllHexaFloat(string filename, HexaFloat*& N, int& fsize)
{
	static int base;
	ifstream rdr(filename);
	rdr >> base;
	while (rdr.peek() == '\n' || rdr.peek() == ' ' || rdr.peek() == '	')
	{
		rdr.ignore();
	}
	rdr >> fsize;
	N = new HexaFloat[fsize];
	for (int i = 0; i < fsize; i++)
	{
		while (rdr.peek() == '\n' || rdr.peek() == ' ' || rdr.peek() == '	')
		{
			rdr.ignore();
		}
		N[i].Load(rdr);
		N[i].Setbase(base);
	}
}
void PrintAllHexaFloat(HexaFloat* N, int size)
{
	cout << size << endl;
	for (int i = 0; i < size; i++)
	{
		N[i].Print();
		cout << endl;
	}
}
void WriteAllHexaFloat(HexaFloat* k, int isize)
{
	ofstream wtr("bscs22133writeHexaFloat.txt");
	wtr << isize;
	wtr << endl;
	for (int i = 0; i < isize; i++)
	{
		wtr << k[i];
		wtr << endl;
	}
}

int main1()
{

	HugeFloat *i;
	HugeFloat K;
	int isize;
	LoadAllFloats("input.txt", i, isize);
	PrintAllFloats(i, isize);
	int  j=0,z=0;
	int choice = 0;
	bool y=false;
	char c;
	cout << endl << endl;
	do
	{
		cout << "\n1.Print";
		cout << "\t\t 2.(+) \t\t 3.(+=) \t 4.(-) \t\t 5.(-=) \t 6.(++) \t 7.(--) \n8.(=) \t\t 9.(!) \t\t 10.(==) \t 11.(<)\t\t 12.(<=) \t 13.(>) \t 14.(>=)\n15.(*)\t\t 16.(*=)\t 17.(/)\t\t 18.(/=) \t 19.(Write)";
		cout << "\n \n-1 to exit program\n \n";
		cout << "\n->Note All Calculations are done using storing Huge Integers in Single Pointer. \n \n";

		cout << "Enter your choice in Main: ";
		cin >> choice;

		if (choice == 1)
		{
			try
			{
				PrintAllFloats(i, isize);
			}
			catch (invalid_argument& e)
			{
				cout << e.what();
			}
		}
		else if (choice == 2)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			K = i[z] + i[j];
			cout << " Result= ";
			cout << K;
		}
		else if (choice == 3)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			i[z] += i[j];
			cout << " Result= ";
			cout << i[z];
		}
		else if (choice == 4)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			K = i[z] - i[j];
			cout << " Result= ";
			cout << K;
		}
		else if (choice == 5)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			i[z] -= i[j];
			cout << " Result= ";
			cout << i[z];

		}
		else if (choice == 6)
		{
			cout << "Enter the Huge-Intger index: ";
			cin >> j;
			i[j]++;
			cout << i[j];
		}
		else if (choice == 7)
		{
			cout << "Enter the Huge-Intger index: ";
			cin >> j;
			i[j]--;
			cout << i[j];
		}
		else if (choice == 8)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			i[z] = i[j];
		}
		else if (choice == 9)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			!i[z];
			cout << !i[z];
		}
		else if (choice == 10)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			y = i[z] == i[j];
			cout << ((y == true) ? "true" : "false");
		}
		else if (choice == 11)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			y = i[z] < i[j];
			cout << ((y == true) ? "true" : "false");
		}
		else if (choice == 12)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			y = i[z] <= i[j];
			cout << ((y == true) ? "true" : "false");
		}
		else if (choice == 13)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			y = i[z] > i[j];
			cout << ((y == true) ? "true" : "false");
		}
		else if (choice == 14)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			y = i[z] >= i[j];
			cout << ((y == true) ? "true" : "false");
		}
		else if (choice == 15)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			K = i[z] * i[j];
			cout << " Result= ";
			cout << K;
		}
		else if (choice == 16)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			i[z] *= i[j];
			cout << " Result= ";
			cout << i[z];
		}
		else if (choice == 17)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			K = i[z] / i[j];
			cout << " Result= ";
			cout << K;
		}
		else if (choice == 18)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			i[z] /= i[j];
			cout << " Result= ";
			cout << i[z];
		}
		else if (choice == 19)
		{
			WriteAllHugeFloat(i, isize);
		}
		cout << endl;
		cout << "Do you want to continue y/n :";
		cin >> c;


		if (c == 'y')
		{
			system("cls");
			PrintAllFloats(i, isize);
			cout << endl;
		}
		else
		{
			break;
		}

	} while (choice != -1);





//cout << K;*/
//
//	/*bool y;*/
//	//y=N[1].EqualQuantityWise(N[0]);
//	K=i[0]/i[1];
//	//cout <<y<<endl;
//	//cout << endl;
//	//N[0].Pirnt();
//	//N[1].TrimFromLast();
//	cout << K;
//	//N[0].Pirnt();

	return 0;
}
int main2()
{

	HexaInt* i;
	HexaInt K;
	int isize;
	LoadAllHexaInt("hexa.txt", i, isize);
	PrintAllHexaInt(i, isize);
	int  j = 0, z = 0;
	int choice = 0;
	bool y = false;
	char c;
	cout << endl << endl;
	do
	{
		cout << "\n1.Print";
		cout << "\t\t 2.(+) \t\t 3.(+=) \t 4.(-) \t\t 5.(-=) \t 6.(++) \t 7.(--) \n8.(!) \t\t 9.(==) \t 10.(<)\t\t 11.(<=) \t 12.(>) \t 13.(>=)\n14.(*)\t\t 15.(*=)\t 16.(/)\t\t 17.(/=) \t 18.(Write)";
		cout << "\n \n-1 to exit program\n \n";
		cout << "\n->Note All Calculations are done using storing Huge Integers in Single Pointer. \n \n";

		cout << "Enter your choice in Main: ";
		cin >> choice;

		if (choice == 1)
		{
			try
			{
				PrintAllHexaInt(i, isize);
			}
			catch (invalid_argument& e)
			{
				cout << e.what();
			}
		}
		else if (choice == 2)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			K = i[z] + i[j];
			cout << " Result= ";
			cout << K;
		}
		else if (choice == 3)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			i[z] += i[j];
			cout << " Result= ";
			cout << i[z];
		}
		else if (choice == 4)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			K = i[z] - i[j];
			cout << " Result= ";
			cout << K;
		}
		else if (choice == 5)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			i[z] -= i[j];
			cout << " Result= ";
			cout << i[z];

		}
		else if (choice == 6)
		{
			cout << "Enter the Huge-Intger index: ";
			cin >> j;
			i[j]++;
			cout << i[j];
		}
		else if (choice == 7)
		{
			cout << "Enter the Huge-Intger index: ";
			cin >> j;
			i[j]--;
			cout << i[j];
		}
		else if (choice == 8)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			!i[z];
			cout << !i[z];
		}
		else if (choice == 9)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			y = i[z] == i[j];
			cout << ((y == true) ? "true" : "false");
		}
		else if (choice == 10)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			y = i[z] < i[j];
			cout << ((y == true) ? "true" : "false");
		}
		else if (choice == 11)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			y = i[z] <= i[j];
			cout << ((y == true) ? "true" : "false");
		}
		else if (choice == 12)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			y = i[z] > i[j];
			cout << ((y == true) ? "true" : "false");
		}
		else if (choice == 13)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			y = i[z] >= i[j];
			cout << ((y == true) ? "true" : "false");
		}
		else if (choice == 14)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			K = i[z] * i[j];
			cout << " Result= ";
			cout << K;
		}
		else if (choice == 15)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			i[z] *= i[j];
			cout << " Result= ";
			cout << i[z];
		}
		else if (choice == 16)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			K = i[z] / i[j];
			cout << " Result= ";
			cout << K;
		}
		else if (choice == 17)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			i[z] /= i[j];
			cout << " Result= ";
			cout << i[z];
		}
		else if (choice == 18)
		{
			WriteAllHexaInt(i, isize);
		}
		cout << endl;
		cout << "Do you want to continue y/n :";
		cin >> c;


		if (c == 'y')
		{
			system("cls");
			PrintAllHexaInt(i, isize);
			cout << endl;
		}
		else
		{
			break;
		}

	} while (choice != -1);


	return 0;
}
int main3()
{
	HexaFloat* i;
	HexaFloat K;
	int isize;
	LoadAllHexaFloat("hexafloat.txt", i, isize);
	PrintAllHexaFloat(i, isize);


	int  j = 0, z = 0;
	int choice = 0;
	bool y = false;
	char c;
	cout << endl << endl;
	do
	{
		cout << "\n1.Print";
		cout << "\t\t 2.(+) \t\t 3.(+=) \t 4.(-) \t\t 5.(-=) \t 6.(++) \t 7.(--) \n8.(=) \t\t 9.(!) \t\t 10.(==) \t 11.(<)\t\t 12.(<=) \t 13.(>) \t 14.(>=)\n15.(*)\t\t 16.(*=)\t 17.(/)\t\t 18.(/=) \t 19.(Write)";
		cout << "\n \n-1 to exit program\n \n";
		cout << "\n->Note All Calculations are done using storing Huge Integers in Single Pointer. \n \n";

		cout << "Enter your choice in Main: ";
		cin >> choice;

		if (choice == 1)
		{
			try
			{
				PrintAllHexaFloat(i, isize);
			}
			catch (invalid_argument& e)
			{
				cout << e.what();
			}
		}
		else if (choice == 2)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			K = i[z] + i[j];
			cout << " Result= ";
			cout << K;
		}
		else if (choice == 3)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			i[z] += i[j];
			cout << " Result= ";
			cout << i[z];
		}
		else if (choice == 4)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			K = i[z] - i[j];
			cout << " Result= ";
			cout << K;
		}
		else if (choice == 5)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			i[z] -= i[j];
			cout << " Result= ";
			cout << i[z];

		}
		else if (choice == 6)
		{
			cout << "Enter the Huge-Intger index: ";
			cin >> j;
			i[j]++;
			cout << i[j];
		}
		else if (choice == 7)
		{
			cout << "Enter the Huge-Intger index: ";
			cin >> j;
			i[j]--;
			cout << i[j];
		}
		else if (choice == 8)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			i[z] = i[j];
		}
		else if (choice == 9)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			!i[z];
			cout << !i[z];
		}
		else if (choice == 10)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			y = i[z] == i[j];
			cout << ((y == true) ? "true" : "false");
		}
		else if (choice == 11)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			y = i[z] < i[j];
			cout << ((y == true) ? "true" : "false");
		}
		else if (choice == 12)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			y = i[z] <= i[j];
			cout << ((y == true) ? "true" : "false");
		}
		else if (choice == 13)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			y = i[z] > i[j];
			cout << ((y == true) ? "true" : "false");
		}
		else if (choice == 14)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			y = i[z] >= i[j];
			cout << ((y == true) ? "true" : "false");
		}
		else if (choice == 15)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			K = i[z] * i[j];
			cout << " Result= ";
			cout << K;
		}
		else if (choice == 16)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			i[z] *= i[j];
			cout << " Result= ";
			cout << i[z];
		}
		else if (choice == 17)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			K = i[z] / i[j];
			cout << " Result= ";
			cout << K;
		}
		else if (choice == 18)
		{
			cout << "Enter first index Number: ";
			cin >> z;
			cout << "Enter Second index Number: ";
			cin >> j;
			i[z] /= i[j];
			cout << " Result= ";
			cout << i[z];
		}
		else if (choice == 19)
		{
			WriteAllHexaFloat(i, isize);
		}
		cout << endl;
		cout << "Do you want to continue y/n :";
		cin >> c;


		if (c == 'y')
		{
			system("cls");
			PrintAllHexaFloat(i, isize);
			cout << endl;
		}
		else
		{
			break;
		}

	} while (choice != -1);











	//K = i[0]*(i[1]);
	//i[0] /= i[1];
	//i[0].Print();
	//cin >> K;
	//cout << K;
	//K.Print();

	return 0;
}

int main()
{
	int n = 0;
	cout << "1. For Huge-Foat Calculator: "<<endl;
	cout << "2. For Hexa-Int Calculator: "<<endl;
	cout << "3. For Hexa-Float Calculator: "<<endl;
	cout << endl;
	cout << "Enter the choice: ";
	cin >> n;

	if (n == 1)
	{
		system("cls");
		main1();
	}
	else if (n == 2)
	{
		system("cls");
		main2();
	}
	else if (n == 3)
	{
		system("cls");
		main3();
	}
}