#include <stdio.h>
#include <stdlib.h>

/**
 * �kili a�a� yap�s�
 * @author Yunus Emre AK
 */


/**
 * �kili a�a� yap�s�nda, daldaki de�erden 
 *		k���k ise soluna
 *		b�y�k ise sa��na yaz�l�r.
 *
 *    		 11
 *   		/  \
 *  	   7    14
 *        / \   / \
 *       3   8  12  18
 *
 */
typedef struct _dal{
	int veri;
	
	_dal* solundaki;
	_dal* sagindaki;
}dal;

// Kullan�c� aray�z�n�deki yaz�lar� olu�turan fonksiyon (Anla��labilirlik i�in.)
void menu();
// Kullan�c� aray�z�n� olu�turan fonksiyon (Anla��labilirlik i�in.)
void loop(dal **);
// A�ac� olu�turmak i�in kullan�lan fonksiyon.
void create(dal **);
// Bellek ay�rmak i�in fonksiyon. (Tamamen kolayl�k ama�l�d�r.)
dal* get_leaf();
// �kili a�a� yap�s�na veri ekleme fonksiyonu. 
void insert(dal*);
// A�actaki verileri s�ralay�p ekrana yazan fonksiyon (Anla��labilirlik i�in.)
void sort_disploy(dal*);
// A�acta veri arama ve verinin bulunda�� dal� geri d�nd�ren fonksiyon.
dal* search(dal*, int);
// A�ac�n dallar� silen fonksiyon.
void destroy_leaf(dal*);
// A�ac� komple silen fonksiyon
void destroy_tree(dal**);


int main(){
	dal *agacim = NULL;	
		
	loop(&agacim);
}

// Fonksiyonlar;
dal* get_leaf(){
	return (dal*)malloc(sizeof(dal));
}

void insert(dal* gelen_dal, int veri){
	// E�er gelen dal bo� ise, yeni dal olu�turup veriyi at�yoruz.
	if(gelen_dal == NULL){
		printf("\n Agac yapisi mevcut degil. Lutfen once agaci olusturunuz.");
		
		return;
	}
	
	// �ncelikle gelen verinin baslang�� verimizden k���k olma durumunu inceliyoruz.
	if(veri < gelen_dal->veri){
		/**
		 *  E�er gelen veri, ba� veriden "k���kse" dallar�ndaki di�er verileriyle de k�yaslamam�z 
		 * laz�m. Bu k�yaslama i�lemi, k���k olma durumunu inceledi�imiz i�in a�ac�n 
		 * ba�lang�c�n�n�n sol taraf�nda dal olmayana kadar devam etmeli.
		 */
		if(gelen_dal->solundaki != NULL)
			/**
			 *  E�er dal�n sonundaki null de�ilse, tekrardan ekleme fonksiyonunu �a��rca��z.
			 * Bu sayede her alt dal i�in ba�lang�� dal�na uygulam�� oldu�umuz i�lemler
			 * uygulanacak.
			 */
			insert(gelen_dal->solundaki, veri);
		/**
		 *  E�er dal�n solunda ba�ka dal yoksa, soluna yeni bir dal ulu�turup veriyi at�yaca��z.
	     *           11
		 *   		/  
	 	 *    (Yeni Dal) 
	 	 *    /       \
	 	 *   NULL      NULL
		 */
		else{
			// Yeni dal�m�z i�in gelen dal�n soluna dal olu�turuyoruz.
			gelen_dal->solundaki = get_leaf();
			// Gelen dal�n soluna eklenen dala, gelen veriyi at�yoruz.
			gelen_dal->solundaki->veri = veri;
			/**
			 *  Gelen dal�n solunda olu�turulan daldan sonra dal olmad��� i�in her y�n�ne 
			 * de NULL at�yoruz.
			 */
			gelen_dal->solundaki->solundaki = NULL;
			gelen_dal->solundaki->sagindaki = NULL;
		}		
	}	
	
		/**
		 *  E�er gelen veri, ba� veriden "k���k de�ilse" dallar�ndaki di�er verileriyle de k�yaslamam�z 
		 * laz�m. Bu k�yaslama i�lemi, k���k olma durumunu inceledi�imiz i�in a�ac�n 
		 * ba�lang�c�n�n�n sa� taraf�nda dal olmayana kadar devam etmeli.
		 */
	else{
		if(gelen_dal->sagindaki != NULL)
			/**
			 *  E�er dal�n sonundaki null de�ilse, tekrardan ekleme fonksiyonunu �a��rca��z.
			 * Bu sayede her alt dal i�in ba�lang�� dal�na uygulam�� oldu�umuz i�lemler
			 * uygulanacak.
			 */
			insert(gelen_dal->sagindaki, veri);
			
		/**
		 *  E�er dal�n sa��nda ba�ka dal yoksa, sa��nda yeni bir dal ulu�turup veriyi at�yaca��z.
	     *           11
		 *   			\  
	 	 *    		  (Yeni Dal) 
	 	 *    		   /       \
	 	 *   		 NULL      NULL
		 */
		else{
			// Yeni dal�m�z i�in gelen dal�n sa��na dal olu�turuyoruz.
			gelen_dal->sagindaki = get_leaf();
			// Gelen dal�n sa��na olu�turulan yeni dala veriyi at�yoruz.
			gelen_dal->sagindaki->veri = veri;
			/**
			 *  Gelen dal�n sa��nda olu�turulan daldan sonra dal olmad��� i�in her y�n�ne 
			 * de NULL at�yoruz.
			 */
			gelen_dal->sagindaki->sagindaki = NULL;
			gelen_dal->sagindaki->solundaki = NULL;
		}
	}	 
}

dal *search(dal* gelen_dal, int istenen_veri){
	// Sadece gelen dalda veri oldu�u s�rece i�lem yapabiliriz.
	if(gelen_dal != NULL){
		// �lk olarak istenen veri gelen dal�n verisi olup olmad���n� kontrol ediyoruz.
		if(gelen_dal->veri == istenen_veri)
			return gelen_dal;
		
		/**
		 *  E�er istenen veri gelen daldan k���kse;
		 * Ekleme yaparken k���k verileri gelen dal�n soluna ekledi�imiz i�in, bu fonksiyonu
		 * gelen dal�n solundaki dal� parametre vererek tekrar �a��raca��z.
		 */
		if(istenen_veri < gelen_dal->veri)
			search(gelen_dal->solundaki, istenen_veri);
			
		/**
		 *  E�er istenen veri gelen daldan k���k de�ilse yani gelen daldan b�y�k veya dala e�itse;
		 * Ekleme yaparken k���k olmayan verileri gelen dal�n sa��na ekledi�imiz i�in, bu fonksiyonu
		 * gelen dal�n sa��ndaki dal� parametre vererek tekrar �a��raca��z.
		 */
		else
			search(gelen_dal->sagindaki, istenen_veri);
		
		// Hi�bir ko�ul ger�ekle�miyorsa, istenen veri dalda mevcut de�il demektir.
	}
	else 
		return NULL;
}

void destroy_leaf(dal *gelen_dal){
/**
* (Agac�n k�k� (en �st verisi) g�nderilirse, t�m a�ac� siler.)
*     		 11                   11
*   		/  \                /     \
*  	   7    14     ->      7        14
*        / \   / \           /  \    /    \
*       3   8  12  18      NULL NULL NULL NULL
* 
* Alttan �ste do�ru silme i�lemi yapmal�y�z.
*
*/

	// �ncelikle gelen dal bo� (NULL) de�ilse i�lem yap�l�r.
	if(gelen_dal != NULL){
		/**
		*  A�ac�n verileri silmeden �nce a�ac�n dallar�n� temizlememiz gerekiyor,
		* aksi halde di�er dallara eri�imimiz kesilecek ve dallar i�in ayr�lan bellekleri
		* serbest b�rakamayaca��z. Bu sebeple bu fonksiyonu a�ac�n hem sa��ndaki hem de 
		* solundaki dallar� i�in tekrar �a��rmam�z, en sonda a�ac�n verisini silmemiz 
		* gerekir.
		*/
		destroy_leaf(gelen_dal->sagindaki);
		destroy_leaf(gelen_dal->solundaki);
		
		
		// Sa��ndaki ve solundaki t�m dallar silindikten sonra, a�ac�n ba� verisi silinir.
		free(gelen_dal);
		
		
	}
}

void destroy_tree(dal **gelen_agac){
	// �ncelikle gelen dal bo� (NULL) de�ilse i�lem yap�l�r.
	if(*gelen_agac != NULL){
		 // Agacin dallar�n� sildiriyoruz.
		 destroy_leaf(*gelen_agac);
		 		 
		 // Gelen agacta dal kalmad��� i�in agaca NULL at�yoruz.
		 *gelen_agac = NULL;
	}
}

void display_tree(dal *gelen_dal){
	if(gelen_dal != NULL){
		if(gelen_dal->solundaki != NULL)
			printf("| %d", gelen_dal->solundaki->veri);
		if(gelen_dal->sagindaki != NULL)
			printf("| %d", gelen_dal->sagindaki->veri);
	}
}

void sort_display(dal *gelen_dal){
	if(gelen_dal == NULL){
		printf("\nGosterilecek agac yok.");
		
		return;
	}
	
	if(gelen_dal->solundaki != NULL){
		sort_display(gelen_dal->solundaki);
	}
	
	printf("%d-",gelen_dal->veri);
	
	if(gelen_dal->sagindaki != NULL)
		sort_display(gelen_dal->sagindaki);
}

void menu(){
		printf("\n***************************\n");
	// G�rsel hizalama i�in "%30s" 30 karakterlik alana sa�a dayal� yazd�rd�k.
	printf("->%30s\n"," Agaci olusturmak icin 1'e");
	printf("->%30s\n"," Agaca sayi eklemek icin 2'e");
	printf("->%30s\n"," Agaci gostermek icin 3'e");
	printf("->%30s\n"," Agaci silmek icin 4'e");
	printf("->%30s\n"," Cikmak icin 0'a");
}

void loop(dal **agacim){	
		int x = 5;
		
		while(x !=0){
		
		menu();
		
		/**
		 *  Dipnot : Bo�luk %c (" %c") yaz�l�rsa, �ncesinde bas�lan enter'� veri olarak ("\n") g�rmez, hatalar engellenir.
	 	 * %d kullan�m� i�in bir sat�r atlatma karakteri alg�lama durumu olmaz.	
		 */
		scanf("%d", &x);
		
		switch(x){
			case 1:
				create(agacim);
				
				break;
				
			case 2:
				printf("\nLutfen eklemek istediginiz veriyi giriniz:\t");
				
				int eklenecek_veri;
				
				scanf(" %d",&eklenecek_veri);
				
				insert(*agacim, eklenecek_veri);
				
				break;
			
			case 3:
				printf("Agacin verilerinin siralanmis hali:\n");
				sort_display(*agacim);
				
				break;
			
			case 4:
				printf("\nAgac silindi.\n");
				
				destroy_tree(agacim);
				
				break;
				
			default:
				break;
		}
	}
}

void create(dal **agac){
	if(*agac == NULL)
		*agac =get_leaf();
	
	printf("\nAgacin ilk verisini giriniz:\t");
	
	int bas_veri;
	
	scanf(" %d", &bas_veri);
	
	(*agac)->veri = bas_veri;	
	(*agac)->sagindaki = NULL;
	(*agac)->solundaki = NULL;
	
	printf("\nAgac %d verisiyle olusturuldu.", bas_veri);
}

void print_leaf(dal *gelen_dal){
	if(gelen_dal != NULL){
		if(gelen_dal->solundaki != NULL)
			printf("%d ", gelen_dal->solundaki);
		if(gelen_dal->sagindaki != NULL)
			printf("%d ", gelen_dal->sagindaki);
	}
}

int degree_of_tree(dal **gelen_agac){
	int i = 0;
	
	if(gelen_agac == NULL)
		return i;
	
	if(has_leaf(*gelen_agac))
		i++;
	
	if(has_leaf())
		i++;
}

bool has_leaf(dal *gelen_dal){
	if(gelen_dal->solundaki != NULL || gelen_dal->sagindaki != NULL)
		return true;
	
	return false;
}

void print_tree(dal **gelen_agac){
	printf("%d", *gelen_agac->veri)
	print_leaf(*gelen_agac);
}

