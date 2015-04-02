#include "SkipList.h"
#include <string>
#include <iostream>

using namespace std;

int main()
{
	cout << "Creating List: \n\n";
	SkipList<string> list;

	cout << "Adding: " << list.AddData(18, "Laguna Niguel")->data.data << endl;
	cout << "Adding: " << list.AddData(18, "Mission Viejo")->data.data << endl;
	cout << "Adding: " << list.AddData(22, "Lake Forest")->data.data << endl;
	cout << "Adding: " << list.AddData(44, "Irvine")->data.data << endl;
	cout << "Adding: " << list.AddData(44, "San Clemente")->data.data << endl;
	cout << "Adding: " << list.AddData(32, "San Diego")->data.data << endl;
	cout << "Adding: " << list.AddData(49, "Anaheim")->data.data << endl;

	cout << "Removing key 22...\n"; list.RemoveData(22);

	cout << "Adding: " << list.AddData(73, "Los Angeles")->data.data << endl;
	cout << "Adding: " << list.AddData(17, "Orange")->data.data << endl;
	cout << "Adding: " << list.AddData(32, "Palm Springs")->data.data << endl;
	cout << "Adding: " << list.AddData(26, "Riverside")->data.data << endl;

	cout << "Removing key 49...\n"; list.RemoveData(49);

	cout << "Adding: " << list.AddData(19, "Brea")->data.data << endl;
	cout << "Adding: " << list.AddData(60, "Santa Ana")->data.data << endl;
	cout << "Adding: " << list.AddData(35, "Tustin")->data.data << endl;
	cout << "Adding: " << list.AddData(52, "Oceanside")->data.data << endl;
	cout << "Adding: " << list.AddData(11, "La Jolla")->data.data << endl;
	cout << "Adding: " << list.AddData(18, "Del Mar")->data.data << endl;
	cout << "Adding: " << list.AddData(22, "Aliso Viejo")->data.data << endl;
	cout << "Adding: " << list.AddData(49, "Laguna Beach")->data.data << endl;

	cout << endl << endl << "Printing entire list: \n";
	quadNode<string>* listPtr = list.GetHead();

	listPtr = listPtr->next;
	while (listPtr->next->next != NULL)
	{
		cout << listPtr->data.data << ": " << listPtr->data.key << endl;
		listPtr = listPtr->next;
	}

	cin.ignore(1000, '\n');
	return 0;
}