// make NO CHANGES to this file

#include <fstream>
#include <iostream>
#include "quack.h"

using namespace std;

static fstream	arrayFile;
static char		*prefix("--> ");

static void push(Quack *quack, bool front, char ch)
{
	const char	*fnStr(front ? "pushFront" : "pushBack");
	bool		ok;

	if (front)
		ok = quack->pushFront(ch);
	else
		ok = quack->pushBack(ch);
	cout << prefix << fnStr << ' ' << ch << (ok ? "" : " failed") << endl;

	arrayFile << left << fnStr << '(' << ch << ')' << setw(7) << setfill(' ') << ' ';
	if (! front)
		arrayFile << ' ';
	quack->printArray(arrayFile);
}

static void pop(Quack *quack, bool front)
{
	const char	*fnStr(front ? "popFront" : "popBack");
	bool		ok;
	char		ch;

	if (front)
		ok = quack->popFront(ch);
	else
		ok = quack->popBack(ch);
	if (ok)
		cout << prefix << fnStr << ' ' << ch;
	else
		cout << prefix << fnStr << " failed";
	cout << endl;

	arrayFile << left << fnStr << " -> ";
	if (ok)
		arrayFile << ch;
	else
		arrayFile << "?";
	arrayFile << setw(6) << setfill(' ') << ' ';
	if (! front)
		arrayFile << ' ';
	quack->printArray(arrayFile);
}

static void rotate(Quack *quack, int n)
{
	char	*fnStr("rotate");

	cout << prefix << fnStr << ' ' << n << endl;
	quack->rotate(n);

	arrayFile << left << fnStr << '(' << n << ')' << setw(9) << setfill(' ') << ' ';
	if (n > 0)
		arrayFile << ' ';
	quack->printArray(arrayFile);
}

int main(int argc, char **argv)
{
	if (argc > 1)				// turn off cout
		std::cout.setstate(std::ios_base::badbit);

	arrayFile.open("array.txt", ios::out);
	if (! arrayFile.is_open()) {
		cout << "could not open array file" << endl;
		return -1;
		}

	Quack	*quack = new Quack(7);

    cout << "CS260 - Assignment 2 " << (Quack::PREMIUM_VERSION ? "Premium" : "Regular")
		 << " - " << Quack::YOUR_NAME << endl << endl;

	cout << quack;
	push(quack, true, 'a');
	push(quack, true, 'b');
	push(quack, true, 'c');
	push(quack, true, 'd');
	push(quack, false, 'z');
	push(quack, true, 'e');
	cout << endl << quack;
	cout << "# of items: " << quack->itemCount() << endl << endl;
	pop(quack, true);
	cout << endl << quack;
	pop(quack, true);
	cout << endl << quack;
	push(quack, false, 'f');
	cout << endl << quack;
	push(quack, false, 'g');
	cout << endl << quack;
	rotate(quack, 2);
	cout << endl << quack;
	rotate(quack, -3);
	cout << endl << quack;
	cout << prefix << "reverse" << endl;
	quack->reverse();
	arrayFile << setw(19) << setfill(' ') << left << "reverse";
	quack->printArray(arrayFile);
	cout << endl << quack;
	push(quack, true, 'y');
	cout << endl << quack;
	rotate(quack, 3);
	cout << endl << quack;
	rotate(quack, -4);
	cout << endl << quack;
	cout << "# of items: " << quack->itemCount() << endl << endl;
	while (quack->itemCount() > 0) {
		pop(quack, false);
		cout << endl << quack;
		}
	cout << "# of items: " << quack->itemCount() << endl << endl;
	delete quack;

	if (Quack::PREMIUM_VERSION) {
		cout << prefix << "PREMIUM" << endl << endl;
		arrayFile << endl << prefix << "PREMIUM" << endl;

		quack = new Quack(5, 3);
		push(quack, false, 'a');
		push(quack, false, 'b');
		push(quack, false, 'c');
		push(quack, false, 'd');
		push(quack, false, 'e');
		cout << endl << quack;
		cout << "growing" << endl << endl;
		push(quack, false, 'f');
		push(quack, false, 'g');
		cout << endl << quack;
		pop(quack, true);
		pop(quack, false);
		cout << endl << quack;
		delete quack;

		quack = new Quack(6, 5);
		push(quack, false, 'z');
		push(quack, false, 'y');
		push(quack, false, 'x');
		push(quack, true,  'a');
		push(quack, true,  'b');
		push(quack, true,  'c');
		cout << endl << quack;
		cout << prefix << "growing" << endl << endl;
		push(quack, false, 'g');
		push(quack, false, 'h');
		push(quack, true,  'j');
		push(quack, true,  'k');
		cout << endl << quack;
		delete quack;
		}

	cout << endl;

	arrayFile.close();
	return 0;
}
