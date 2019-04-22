#include <iostream>
#include "makine.h"

using namespace std;

// Yunus Emre Ak
// Sefa Yalc�ndag
// Niyazi Eren

int main () {
	Makine makine;

	makine.ba�lat();
}

void Makine::ba�lat() {
	while (true) {
		cout << "x'i gir: ";
		
		bitAl();
		system("cls");
		zyiG�ster();
		diziyiG�ster();
		sonland�r();
	}
}

void Makine::diziyiOlu�tur() {
	dizi = (bool*)malloc(sizeof(bool));

	boyut = 1;
}

void Makine::diziyiGeni�let() {
	if (dizi == NULL) 
		diziyiOlu�tur();
	else 
		dizi = (bool*)realloc(dizi, sizeof(bool) * ++boyut);
}

void Makine::diziyeEkle(bool x) {
	diziyiGeni�let();
	dizi[boyut - 1] = x;
}

void Makine::zyiG�ster() {
	if (boyut >= 3 &&
		dizi[boyut - 3] == 0 &&
		dizi[boyut - 2] == 1 &&
		dizi[boyut - 1] == 1
		)
		z = 1;
	else
		z = 0;

	cout << "z = " << z << endl;
}

void Makine::bitAl() {
	bool x;
	cin >> x;
	diziyeEkle(x);
}

void Makine::diziyiG�ster() {
	cout << "Dizi: ";

	for (int i = 0; i < boyut; i++)
		cout << dizi[i];

	cout << endl << "-----------------\n";
}

void Makine::sonland�r() {
	if (boyut >= 3 &&
		dizi[boyut - 3] == 1 &&
		dizi[boyut - 2] == 0 &&
		dizi[boyut - 1] == 0) {

		cout << "100 dizisi yakalandi. Makine sonlandirildi" << endl;
		system("pause");
		exit(0);
	}
}