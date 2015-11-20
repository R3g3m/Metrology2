#include <iostream>
using namespace std;

char name[10][80];
char phone[10][20];
float hours[10];
float wage[10];

int menu();
void enter(), report();

int main()
{
	int choice;
	do {
		choice = menu();

		switch(choice) {
		case 0: break;
		case 1: enter();
			break;
		case 2: report();
			break;
		default: cout << "Poprobyite escho raz.\n\n";
		}
	} while(choice !=0);

	return 0;
}
int menu()
{
	int choice;

	cout << "0. Vb|hod iz programmb|\n";
	cout << "1. Vvod informacii\n";
	cout << "2. Generrirovanie otcheta\n";
	cout << "\nVb|berite komandu: ";
	cin >> choice;
	return choice;
}
void enter()
{
	int i;
	char temp[80];

	for(i=0; i<10; i++) {
		cout << "Vvedite familiiy: ";
		cin >> name[i];
		cout << "Vvedite telefon: ";
		cin  >> phone[i];
		cout << "Vvedite kolichestvo otrabotannb|h chasov: ";
		cin >> hours[i];
		cout << "Vvedite oklad: ";
		cin >> wage[i];
	}
}
void report()
{
	int i;

	for(i=0; i<10; i++) {
		cout << name[i] << " " << phone[i] << "\n";
		cout << "Zarabotnaia plata za nedely: " << wage[i] * hours[i] << "\n";
	}
}
