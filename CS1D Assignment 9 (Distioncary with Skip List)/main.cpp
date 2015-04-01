#include "SkipList.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	SkipList<string> list;

	list.AddData(18, "Laguna Niguel");
	list.AddData(18, "Mission Viejo");
	list.AddData(22, "Lake Forest");
	list.AddData(44, "Irvine");
	list.AddData(44, "San Clemente");
	list.AddData(32, "San Diego");
	list.AddData(49, "Anaheim");
	list.RemoveData(22);

	cout << list.GetData(32)->data << endl;

	cin.ignore(1000, '\n');
	return 0;
}