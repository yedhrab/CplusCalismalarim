#pragma once
#include <stdlib.h>

class Makine {
	public:
		bool* dizi;
		bool z;

		int boyut = 0;

		// Aray�z
		void ba�lat();

		// Veri alma fonksiyonlar�
		void bitAl();

		// Dizi i�lemleri fonksiyonlar�
		void diziyiOlu�tur();
		void diziyiGeni�let();
		void diziyeEkle(bool x);

		// Kontrol fonksiyonlar�
		void zyiG�ster();
		void diziyiG�ster();
		void sonland�r();
};
		