//Veri Yapýlarý ve Algoritmalar Dersi Sonbahar 2018 Ödevi.

//Ögrenci1 No: 1030520804
//Ögrenci1 Ýsmi: Emre ATAÞ

//Ögrenci2 No: 1030522894
//Ögrenci2 Ýsmi: Furkan ERAVÞAR

//Ögrenci3 No: 1030522874
//Ögrenci3 Ýsmi: Göksel KÜÇÜKÞAHÝN

//Ögrenci4 No: 1030522880
//Ögrenci4 Ýsmi: Mustafa Berke DEMÝR

//Ders Kodu: BZ205
//Dosya ismi: dllStudent.exe

//DO YOUR BEST OR DO NOT.

#include "pch.h" //önceden derlenmiþ 'Header' dosyalarý
#include <iostream> //input output kütüphaneleri
#include <sstream> //string stream kütüphanesi
#include <ctype.h> //char type kütüphanesi
#include <fstream> //file stream kütüphanesi 

#define notfound 17004453
#define LeadEngineer 1030522874
#define WhoIsTheBest "JellyBeanci"

using namespace std;

class Student {
public:
	int Number = -1;
	string Name = "_Bos_";
	string Surname = "_Bos_";
	string Department = "_NoDefined_";
	Student(void) //constructor
	{
		n = NULL;
		Number = notfound;
	}
	Student(int No, string name, string surname, string dprt) //constructor overload 2
	{
		Name = name;
		Surname = surname;
		Number = No;
		Department = dprt;
	}
	Student(int No) //constructor overload 3
	{
		Number = No;
	}
	void SetStudent(int No, string name, string surname, string dprt);
	string PrintRow(bool group);
	char GetGroup();
private:
	Student* n;
	string GetName(void);
	string GetSurname(void);
	int GetNumber(void);
	char GetSurnamesFirstLetter();
	string GetDepartment();
};

void Student::SetStudent(int No, string name, string surname, string dprt)
{
	Name = name;
	Surname = surname;
	Number = No;
	Department = dprt;
}
string Student::GetName(void)
{
	stringstream s;
	s << Name;
	return s.str();
}
string Student::GetSurname(void)
{
	stringstream s;
	s << Surname;
	return s.str();
}
int Student::GetNumber(void)
{
	return Number;
}
char Student::GetSurnamesFirstLetter()
{
	char x = '0';
	if (Surname != "")
	{
		x = Surname[0];
	}
	x = toupper(x);
	return x;
}
char Student::GetGroup()
{
	//ASCII A = 65, Z = 90...
	char flots = GetSurnamesFirstLetter();
	int val = (int)flots;
	if (val >= 65 && val <= 75)
	{
		return 'A';
	}
	else if (val >= 76 && val <= 90)
	{
		return 'B';
	}
	else
	{
		return 'C';
	}
}
string Student::GetDepartment()
{
	stringstream s;
	s << Department;
	return s.str();
}
string Student::PrintRow(bool group)
{
	//Group True ise Grup ile, False ise Grupsuz yazdýr.
	stringstream s;
	if (group)
	{
		s << GetNumber() << " " << GetName() << " " << GetSurname() << " " << GetDepartment() << " " << GetGroup();
	}
	else
	{
		s << GetNumber() << " " << GetName() << " " << GetSurname() << " " << GetDepartment();
	}
	return s.str();
}

class Node {
public:
	//int data;
	Student data;
	Node* prev;
	Node* next;
};

class List {
public:
	List(void) //Constructor
	{
		first = NULL;
		Size = 0;
	}
	~List(void) //Destructor
	{
		while (IsEmpty() == true)
		{
			DeleteNode(0);
		}
	}
	bool IsEmpty();
	Node* InsertNode(int index, Student data);
	void AddToEnd(Student data);
	void Swap(Node* a, Node* b);
	void Swap(int a, int b);
	Node* FindNode(int index);
	Node* FindNodeWithNumber(int StudentNumber);
	Student GetIndexData(int index);
	Student DeleteNodeAndReturn(int index);
	void DeleteNode(int index);
	void DispayWholeList();
	void DisplayNumbers();
	void DisplayNames();
	void DispayWholeSurnames();
	void Push(Student data);
	Student Pop(void);
	int Size;
private:
	Node* first;
	void PrintChilds();
};

Node* List::InsertNode(int index, Student data) {
	if (index < 0)
	{
		return NULL;
	}
	int CurrentIndex = 1;
	Node* CurrentNode = first;
	while (CurrentNode && index > CurrentIndex)
	{
		CurrentNode = CurrentNode->next;
		CurrentIndex++;
	}
	if (index > 0 && CurrentNode == NULL)
	{
		return NULL;
	}
	//
	Node* newNode = new Node;
	newNode->data = data;
	if (index == 0)
	{
		//baþa ekle.
		newNode->prev = NULL;
		newNode->next = first;
		first = newNode;
		Size++;
	}
	else if (index != 0 && index < Size)
	{
		//araya ekle.
		newNode->next = CurrentNode->next;
		newNode->prev = CurrentNode;
		(CurrentNode->next)->prev = newNode;
		CurrentNode->next = newNode;
		Size++;
	}
	else if (index == Size)
	{
		//sona ekle.
		newNode->next = NULL;
		newNode->prev = CurrentNode;
		CurrentNode->next = newNode;
		Size++;
	}
	return newNode;
}
void List::AddToEnd(Student data) {
	//Index kullanmadan Sona ekle.
	InsertNode(Size, data);
}
Node* List::FindNode(int index) {
	if (index <= 0)
	{
		//eðer aranan deðer 0 veya daha küçükse direkt Boþ deðer dönder.
		return NULL;
	}
	int CurrentIndex = 1;
	Node* CurrentNode = first;
	while (CurrentNode && index > CurrentIndex)
	{
		//CurrentNode Null deðilse ve index, CurrentIndex'den büyükse.
		CurrentNode = CurrentNode->next;
		CurrentIndex++;
	}
	if (index > 0 && CurrentNode == NULL)
	{
		//index 0'dan büyük olduðu halde Current Null geliyorsa; yani Aranan indexte Düðüm yoksa.
		return NULL;
	}
	else
	{
		//Else içine düþmüþse Düðüm bulunmuþ ve için de dolu demektir.
		return CurrentNode;
	}
}
bool List::IsEmpty() {
	//First deðeri Null ise Baðlý bir düðüm yok demektir.
	return first == NULL;
}
void List::DisplayNumbers() {
	int num = 0;
	Node* CurrentNode = first; //baþlangýç noktasý First.
	while (CurrentNode != NULL)
	{
		//Ýçinde bulunduðumuz Düðüm Boþ olmadýðý sürece.
		cout << num + 1 << "-) " << CurrentNode->data.Number << endl; //Düðüm Numarasý + 1 çünkü index = 0  dizini 1. elemaný.
		CurrentNode = CurrentNode->next; //bir ilerlet.
		num++; //counter deðerini 1 artýr.
	}
	cout << "[" << num << "]- Tane Eleman Basari ile Yazdirildi." << endl; //yazdýrma iþlemi.
}
void List::DisplayNames() {
	int num = 0;
	Node* CurrentNode = first; //baþlangýç noktasý First.
	while (CurrentNode != NULL)
	{
		//Ýçinde bulunduðumuz Düðüm Boþ olmadýðý sürece.
		cout << num + 1 << "-) " << CurrentNode->data.Name << endl; //Düðüm Numarasý + 1 çünkü index = 0  dizini 1. elemaný.
		CurrentNode = CurrentNode->next; //bir ilerlet.
		num++; //counter deðerini 1 artýr.
	}
	cout << "[" << num << "]- Tane Eleman Basari ile Yazdirildi." << endl; //yazdýrma iþlemi.
}
void List::DispayWholeList() {
	for (int i = 0; i < Size; i++)
	{
		Student temp = GetIndexData(i);
		cout << i + 1 << "-) " << temp.PrintRow(true) << endl;
	}
	//cout << "Number of nodes in the list: " << Size << endl;
	cout << "[" << Size << "]- Tane Eleman Basari ile Yazdirildi." << endl;
}
void List::DispayWholeSurnames() {
	for (int i = 0; i < Size; i++)
	{
		Student temp = GetIndexData(i);
		cout << i + 1 << "-) " << temp.Surname << endl;
	}
	//cout << "Number of nodes in the list: " << Size << endl;
	cout << "[" << Size << "]- Tane Eleman Basari ile Yazdirildi." << endl;
}
void List::PrintChilds()
{
	//Test için kullanýlýyor.
	for (int i = 1; i <= Size; i++)
	{
		Node* a = FindNode(i);
		if (a->prev != NULL)
		{
			cout << "Sol: \"" << a->prev->data.Number << "\",";
		}
		else
		{
			cout << "    null   ";
		}
		cout << " _(" << a->data.Number << ")_ ,";
		if (a->next != NULL)
		{
			cout << "Sag: \"" << a->next->data.Number << "\"" << endl;
		}
		else
		{
			cout << "    null   " << endl;
		}
	}
}
void List::Swap(Node*a, Node*b) {
	Node* temp = new Node;
	temp->data = a->data;
	a->data = b->data;
	b->data = temp->data;
}
void List::Swap(int a, int b) {
	Node* na = new Node;
	Node* nb = new Node;
	na = FindNode(a);
	nb = FindNode(b);
	Node* temp = new Node;
	temp->data = na->data;
	na->data = nb->data;
	nb->data = temp->data;
}
Student List::GetIndexData(int index) {
	Node* F = FindNode(index + 1);
	if (F != NULL)
	{
		return F->data;
	}
	else
	{
		return Student(-1, "x", "y", "z"); //NullStudent Constructor Taslaðý. eðer bir sorun problemi çýkarsa Null yerine bu deðer dönüyor.
	}
}
Node* List::FindNodeWithNumber(int StudentNumber) {
	//int CurrentIndex = 1; //Index sayacý. //beta.
	Node* CurrentNode = first; //baþlangýç düðümü.
	bool Find = true; //bulununa kadar true olmasý için bool deðiþken.
	while (CurrentNode && Find) //Current Node Null deðilse ve Henüz bulunmamýþsa Döngüye gir.
	{
		if (CurrentNode->data.Number == StudentNumber)
		{
			//eðer Þuan içinde bulunduðumuz düðümün Datasý Parametre olarak aldýðýmýz deðere eþitse;
			Find = false; //bulundu.
			return CurrentNode; //Eþleþen Düðümü Dönder.
		}
		else
		{
			//eþit deðilse.
			//CurrentIndex++;//deðeri bir artýr.
			if (CurrentNode->next) //Currentin saðý boþ olabilir NullPtr exception hatasý almamak için kontrol ediyoruz.
			{
				CurrentNode = CurrentNode->next; //Bi sonraki elemana geç.
			}
			else
			{
				//Eðer Kod buraya düþtüyse demektir ki Currentin saðý YOK.
				//yani son elemaný bulduk.
				//eðer bu deðilse liste de yoktur.
				if (CurrentNode->data.Number == StudentNumber)
				{
					//bulduk.
					Find = false;
					return CurrentNode;
				}
				else
				{
					return NULL; //bulunmamýþ demektir.
				}
			}
		}
	}
	//Normal Þartlar altýnda buraya ihtiyaç yok döngüde her türlü ihtimal düþünüldü.
	//Ama Bir Mühendis olarak "ya tutarsa" diyerek son kez kontrol ediyoruz.
	if (Find == true)
	{
		//bulunamadý.
		return NULL;
	}
	else
	{
		//false ve return edilememiþse sorun yaþamamak için Yeniden Þuanki elemaný Dönderiyor.
		return CurrentNode;
	}
}
Student List::DeleteNodeAndReturn(int index) {
	Node* CurrentNode = FindNode(index + 1); //FindNode Fonksiyonun 0. elemaný First kabul ettiði için 1. eleman FindNode(1) oluyor.
	Student st;
	if (CurrentNode) //eðer varsa.
	{
		if (CurrentNode->prev) //eðer varsa.
		{
			if (CurrentNode->next) //eðer varsa.
			{
				//aradan sil
				(CurrentNode->prev)->next = CurrentNode->next; //(Þuankinin Öncesi)'nin Sonrasý = (eski)Þuanýnkinin Sonrasý.
				(CurrentNode->next)->prev = CurrentNode->prev; //(Þuankinin Sonrasýnýn)'nin Öncesi = (eski)Þuankinin Öncesi.
				Size--; //Bir düðüm eksildiði için Size 1 azalacak.
				st = CurrentNode->data;
				delete CurrentNode; //Þuankini Yok et.
			}
			else //yoksa.
			{
				//en sondan sil.
				(CurrentNode->prev)->next = NULL; //en sol olduðu için saðý NULL yap.
				Size--; //Bir düðüm eksildiði için Size 1 azalacak.
				st = CurrentNode->data;
				delete CurrentNode; //Þuankini Yok et.
			}
		}
		else //yoksa
		{
			//en baþtan sil
			if (first->next)
			{
				if ((first->next)->prev)
				{
					(first->next)->prev = NULL;
				}
			}
			first = CurrentNode->next; //Baþ = Þuankinin Bir saðý.
			st = CurrentNode->data;
			Size--; //Bir düðüm eksildiði için Size 1 azalacak.
			delete CurrentNode; //Þuankini Yok et.
		}
	}
	return st;
}
void List::DeleteNode(int index) {
	Node* CurrentNode = FindNode(index + 1); //FindNode Fonksiyonun 0. elemaný First kabul ettiði için 1. eleman FindNode(1) oluyor.
	if (CurrentNode) //eðer varsa.
	{
		if (CurrentNode->prev) //eðer varsa.
		{
			if (CurrentNode->next) //eðer varsa.
			{
				//aradan sil
				(CurrentNode->prev)->next = CurrentNode->next; //(Þuankinin Öncesi)'nin Sonrasý = (eski)Þuanýnkinin Sonrasý.
				(CurrentNode->next)->prev = CurrentNode->prev; //(Þuankinin Sonrasýnýn)'nin Öncesi = (eski)Þuankinin Öncesi.
				Size--; //Bir düðüm eksildiði için Size 1 azalacak.
				delete CurrentNode; //Þuankini Yok et.
			}
			else //yoksa
			{
				//en sondan sil
				(CurrentNode->prev)->next = NULL; //en sol olduðu için saðý NULL yap.
				Size--; //Bir düðüm eksildiði için Size 1 azalacak.
				delete CurrentNode; //Þuankini Yok et.
			}
		}
		else //yoksa
		{
			//en baþtan sil
			if (first->next)
			{
				if ((first->next)->prev)
				{
					(first->next)->prev = NULL;
				}
			}
			first = CurrentNode->next; //Baþ = Þuankinin Bir saðý.
			Size--; //Bir düðüm eksildiði için Size 1 azalacak.
			delete CurrentNode; //Þuankini Yok et.
		}
	}
}
void List::Push(Student data) {
	InsertNode(0, data);
}
Student List::Pop(void) {
	return DeleteNodeAndReturn(0);
}

class FileOperations {
	//files in must be in same subfolder and in C directory 
	//Dosyalarýn 'Lists' adýnda bir klasörde ve C de olmasý gerekiyor.
	//Tüm listeler ayný github içinde.
private:
	//Bilgisayar Programlama dersini Alan Öðrenciler.
	string pdep = "C:\\Lists\\pro\\department.txt";
	string pno = "C:\\Lists\\pro\\num.txt";
	string pn = "C:\\Lists\\pro\\name.txt";
	string ps = "C:\\Lists\\pro\\surname.txt";

	//Veritabaný Yönetim Sistemi dersini Alan Öðrenciler.
	string vdep = "C:\\Lists\\veri\\department.txt";
	string vno = "C:\\Lists\\veri\\num.txt";
	string vn = "C:\\Lists\\veri\\name.txt";
	string vs = "C:\\Lists\\veri\\surname.txt";

	//2016 senesi Veritabaný Yönetim Sistemleri, Bilgisayar Programlama Alan Öðrenciler.
	string zdep = "C:\\Lists\\old\\department.txt";
	string zno = "C:\\Lists\\old\\num.txt";
	string zn = "C:\\Lists\\old\\name.txt";
	string zs = "C:\\Lists\\old\\surname.txt";

public:
	List LoadData(bool Course)
	{
		List liste;
		ifstream myReadFile;
		string output = "";
		int i = 0;
		//Course: true olursa Bilgisayar Programlama, false ise Veritabaný Yönetim Sistemleri.
		if (Course)
		{
			myReadFile.open(pno);
			if (myReadFile.is_open())
			{
				while (!myReadFile.eof())
				{
					myReadFile >> output;
					int n1 = stoi(output);//sugoi
					liste.AddToEnd(Student(n1));
				}
			}
			myReadFile.close();
			//
			myReadFile.open(pn);
			if (myReadFile.is_open())
			{
				while (!myReadFile.eof())
				{
					myReadFile >> output;
					Node* temp = liste.FindNode(i + 1);
					temp->data.Name = output;
					i++;
				}
			}
			myReadFile.close();
			i = 0;
			//
			myReadFile.open(ps);
			if (myReadFile.is_open())
			{
				while (!myReadFile.eof())
				{
					myReadFile >> output;
					Node* temp = liste.FindNode(i + 1);
					temp->data.Surname = output;
					i++;
				}
			}
			myReadFile.close();
			i = 0;
			//
			myReadFile.open(pdep);
			if (myReadFile.is_open())
			{
				while (!myReadFile.eof())
				{
					myReadFile >> output;
					Node* temp = liste.FindNode(i + 1);
					temp->data.Department = output;
					i++;
				}
			}
			myReadFile.close();
		}
		else
		{
			myReadFile.open(vno);
			if (myReadFile.is_open())
			{
				while (!myReadFile.eof())
				{
					myReadFile >> output;
					int n1 = stoi(output);//sugoi
					liste.AddToEnd(Student(n1));
				}
			}
			myReadFile.close();
			//
			myReadFile.open(vn);
			if (myReadFile.is_open())
			{
				while (!myReadFile.eof())
				{
					myReadFile >> output;
					Node* temp = liste.FindNode(i + 1);
					temp->data.Name = output;
					i++;
				}
			}
			myReadFile.close();
			i = 0;
			//
			myReadFile.open(vs);
			if (myReadFile.is_open())
			{
				while (!myReadFile.eof())
				{
					myReadFile >> output;
					Node* temp = liste.FindNode(i + 1);
					temp->data.Surname = output;
					i++;
				}
			}
			myReadFile.close();
			i = 0;
			//
			myReadFile.open(vdep);
			if (myReadFile.is_open())
			{
				while (!myReadFile.eof())
				{
					myReadFile >> output;
					Node* temp = liste.FindNode(i + 1);
					temp->data.Department = output;
					i++;
				}
			}
			myReadFile.close();
		}
		//
		return liste;
	}
	List LoadOldData()
	{
		List liste;
		ifstream myReadFile;
		string output = "";
		int i = 0;
		myReadFile.open(zno);
		if (myReadFile.is_open())
		{
			while (!myReadFile.eof())
			{
				myReadFile >> output;
				int n1 = stoi(output);//sugoi
				liste.AddToEnd(Student(n1));
			}
		}
		myReadFile.close();
		//
		myReadFile.open(zn);
		if (myReadFile.is_open())
		{
			while (!myReadFile.eof())
			{
				myReadFile >> output;
				Node* temp = liste.FindNode(i + 1);
				temp->data.Name = output;
				i++;
			}
		}
		myReadFile.close();
		i = 0;
		//
		myReadFile.open(zs);
		if (myReadFile.is_open())
		{
			while (!myReadFile.eof())
			{
				myReadFile >> output;
				Node* temp = liste.FindNode(i + 1);
				temp->data.Surname = output;
				i++;
			}
		}
		myReadFile.close();
		i = 0;
		//
		myReadFile.open(zdep);
		if (myReadFile.is_open())
		{
			while (!myReadFile.eof())
			{
				myReadFile >> output;
				Node* temp = liste.FindNode(i + 1);
				temp->data.Department = output;
				i++;
			}
		}
		myReadFile.close();
		return liste;
	}
};

class StringOperation {
public:
	bool StringCompare(string p, string s); //eðer 'p', 's' den önce ise False deðilse True. Eðer p ve s Ayný ise Yine False.
};
bool StringOperation::StringCompare(string p, string s)
{
	//iki stringi de Tamamen büyük harflerden oluþmasý için tüm alt birimlerini toupper() kullanarak büyük harf yapýyorum. 
	for (int i = 0; i < p.length(); i++)
	{
		p[i] = (char)towupper(p[i]);
	}
	for (int i = 0; i < s.length(); i++)
	{
		s[i] = (char)toupper(s[i]);
	}
	if (p == s)
	{
		//ayný ise karþýlaþtýrmaya gerek yok direkt False.
		return false;
	}
	else
	{
		//farklý ise
		//ASCII tablosuna göre 
		//A 65
		//Z 90
		//p = primary (birincil)
		//s = secondary (ikincil)
		int pC = p.length(); //birincil Stringin boyutunu tutan int tipindeki deðiþken
		int sC = s.length(); //ikincil String boyutunu tutan int tipindeki deðiþken
		if (pC > sC) //Eðer birincil Stringin boyu ikincil Stringden daha büyükse;
		{
			for (int i = 0; i < sC; i++) //Kýsa olan string boyu kadar döngüye girer
			{
				if ((int)p[i] < (int)s[i]) //Eðer p'nin i'inci elemanýnýn ascii karþýlýðý s'nin i'inci elemanýndan daha küçükse.
				{
					//p, s den önce ise;
					return false;
				}
				else if ((int)p[i] > (int)s[i]) //Eðer p'nin i'inci elemanýnýn ascii karþýlýðý s'nin i'inci elemanýndan daha büyükse.
				{
					//s, p den önce ise;
					return true;
				}
				else
				{
					continue;
				}
			}
			return true;
		}
		else
		{
			if (pC == sC) //Ýkisinin de boylarý eþitse;
			{
				for (int i = 0; i < sC; i++) //boyutlarý eþit olduðu için ikisinden birinin boyu kadar döngüye girer.
				{
					if ((int)p[i] < (int)s[i]) //Eðer p'nin i'inci elemanýnýn ascii karþýlýðý s'nin i'inci elemanýndan daha küçükse.
					{
						//p, s den önce ise;
						return false;
					}
					else if ((int)p[i] > (int)s[i]) //Eðer p'nin i'inci elemanýnýn ascii karþýlýðý s'nin i'inci elemanýndan daha büyükse.
					{
						//s, p den önce ise;
						return true;
					}
					else
					{
						continue;
					}
				}
				return false;
			}
			else //Eðer ikincil Stringin boyu birincil Stringden daha büyükse;
			{
				//sC > pC
				for (int i = 0; i < pC; i++)
				{
					if ((int)p[i] < (int)s[i]) //Eðer p'nin i'inci elemanýnýn ascii karþýlýðý s'nin i'inci elemanýndan daha küçükse.
					{
						//p, s den önce ise;
						return false;
					}
					else if ((int)p[i] > (int)s[i]) //Eðer p'nin i'inci elemanýnýn ascii karþýlýðý s'nin i'inci elemanýndan daha büyükse.
					{
						//s, p den önce ise;
						return true;
					}
					else
					{
						continue;
					}
				}
				return false;
			}
		}
	}
}

class Sort {
public:
	List Insertion(List InputList); //Sonradan yazýlan Sýralama Algoritmalarýný test etmek için bkz HeapSort.
	List Insertion(List InputList, bool surname); //Soyada göre sýralama yapan Insertion Sort. Quick Sort sonucunu kontrol etmek için.
	List InsertionR(List InputList);
	void QuickSort(List InputList, int start, int end); //Soyada göre sýralama yapan Quick Sort Kodu.
	void HeapSort(List InputList); //Numaraya göre sýramala yapan Heap Sort Kodu.
	List CopyList(List Target); //Var olan Listeyi bozmadan sýralama vs iþlemleri yapmak için var olan listeyi Kopyalayýp dönderen Fonksiyon (Metot).
	void RadixSort(List InputList); //RadixSort
private:
	//heap sort
	int heapSize; //Sub iþlemleri için gerekli Global deðiþken.
	void BuildHeapSortTree(List InputList); //Aðacý inþa eden kod.
	void Heapify(List InputList, int Index); //Aðacý Heapify kurallarýna göre düzenleyen kod.
	//quick sort
	int partition(List A, int start, int end); //Quick sortun Parçalara ayýrmak için kullandýðý Fonksiyon (Metot).
};

List Sort::Insertion(List InputList)
{
	int i;
	int j;
	Student ekle;
	List WPA = CopyList(InputList);
	int Length = InputList.Size;
	for (i = 1;i < Length;i++)
	{
		ekle = WPA.FindNode(i + 1)->data;
		for (j = i - 1;(j >= 0) && (ekle.Number <= WPA.FindNode(j + 1)->data.Number);j--)
		{
			WPA.FindNode(j + 2)->data = WPA.FindNode(j + 1)->data;
		}
		WPA.FindNode(j + 2)->data = ekle;
	}
	return WPA;
}
List Sort::Insertion(List InputList, bool surname) {
	int i;
	int j;
	Student ekle;
	StringOperation sO;
	List WPA;
	int Length = InputList.Size;
	for (i = 1;i <= Length;i++)
	{
		WPA.AddToEnd(InputList.FindNode(i)->data);
	}
	for (i = 1;i < Length;i++)
	{
		ekle = WPA.FindNode(i + 1)->data;
		//(ekle.Number <= WPA.FindNode(j + 1)->data.Number)
		for (j = i - 1;(j >= 0) && !sO.StringCompare(ekle.Surname, WPA.FindNode(j + 1)->data.Surname);j--)
		{
			WPA.FindNode(j + 2)->data = WPA.FindNode(j + 1)->data;
		}
		WPA.FindNode(j + 2)->data = ekle;
	}
	return WPA;
}
List Sort::InsertionR(List InputList) {
	int i;
	int j;
	Student ekle;
	StringOperation sO;
	List WPA;
	int Length = InputList.Size;
	for (i = 1;i <= Length;i++)
	{
		WPA.AddToEnd(InputList.FindNode(i)->data);
	}
	for (i = 1;i < Length;i++)
	{
		ekle = WPA.FindNode(i + 1)->data;
		//(ekle.Number <= WPA.FindNode(j + 1)->data.Number)
		for (j = i - 1;(j >= 0) && !sO.StringCompare(ekle.Name, WPA.FindNode(j + 1)->data.Name);j--)
		{
			WPA.FindNode(j + 2)->data = WPA.FindNode(j + 1)->data;
		}
		WPA.FindNode(j + 2)->data = ekle;
	}
	return WPA;
}
void Sort::QuickSort(List InputList, int start, int end)
{
	int i;
	if (start < end)
	{
		i = partition(InputList, start, end);
		QuickSort(InputList, start, i - 1);
		QuickSort(InputList, i + 1, end);
	}
}
int Sort::partition(List A, int start, int end)
{
	StringOperation sO; //String Üzerinde iþlemler yapmamý saðlayan sýrf bu ödev için yazýlmýþ Control Sýnýfý.
	string x = A.GetIndexData(end).Surname;
	int i = start - 1;
	for (int j = start; j <= end - 1; j++)
	{
		if (!sO.StringCompare(A.GetIndexData(j).Surname, x))
		{
			i++;
			A.Swap(i + 1, j + 1);
		}
	}
	A.Swap(i + 2, end + 1);
	return i + 1;
}
void Sort::BuildHeapSortTree(List InputList)
{
	heapSize = InputList.Size - 1;
	for (int i = heapSize / 2; i >= 0; i--)
	{
		Heapify(InputList, i);
	}
}
void Sort::Heapify(List InputList, int Index)
{
	int Left = 2 * Index + 1;
	int Right = 2 * Index + 2;
	int Largest = Index;
	if (Left <= heapSize && InputList.FindNode(Left + 1)->data.Number > InputList.FindNode(Index + 1)->data.Number)
	{
		Largest = Left;
	}
	if (Right <= heapSize && InputList.FindNode(Right + 1)->data.Number > InputList.FindNode(Largest + 1)->data.Number)
	{
		Largest = Right;
	}
	if (Largest != Index)
	{
		InputList.Swap(Index + 1, Largest + 1);
		Heapify(InputList, Largest);
	}
}
void Sort::HeapSort(List InputList) {
	BuildHeapSortTree(InputList);
	for (int i = InputList.Size - 1; i >= 0; i--)
	{
		InputList.Swap(1, i + 1);
		heapSize--;
		Heapify(InputList, 0);
	}
}
void Sort::RadixSort(List InputList)
{
	int maxlen = 0;
	List BuckedTemp = CopyList(InputList);
	for (int i = 0; i < BuckedTemp.Size; i++)
	{
		Student temp = BuckedTemp.GetIndexData(i);
		if (temp.Name.length() > maxlen)
		{
			maxlen = temp.Name.length();
		}
	}
	for (int i = 0; i < BuckedTemp.Size; i++)
	{
		Node* edt = BuckedTemp.FindNode(i + 1);
		string currentString = edt->data.Name;
		int currentSCount = currentString.length();
		if (maxlen - currentSCount > 0)
		{
			int r = maxlen - currentSCount; //kýsa olan stringin en uzundan farký
			stringstream ss;
			ss << currentString;
			for (int i = 0; i < r; i++)
			{
				ss << '.';//r kadar a ekle
			}
			edt->data.Name = ss.str();
		}
	}
	BuckedTemp.DisplayNames();//test print

	List Listeler[26]; //26 tane liste Listesi ???
	//Nokta 46
	//AltTire = 95
	for (int i = 0; i < maxlen; i++)
	{
		for (int j = 0; j < BuckedTemp.Size; j++)
		{
			Student temp = BuckedTemp.Pop();

			if (temp.Name[i] == '.')
			{
				//a.
				Listeler[0].Push(temp); //eðer '.' ise A gibi davran
				//Listeler[0].AddToEnd(temp);
			}
			else if (temp.Name[i] == '_')
			{
				//z
				Listeler[25].Push(temp); //eðer '_' ise Z gibi davran
				//Listeler[25].AddToEnd(temp);
			}
			else
			{
				//a-z
				int ascii = (int)temp.Name[i] - 65; //eðer a ise 0, z = 25 olucak bu sayede.
				Listeler[ascii].Push(temp);
				//Listeler[ascii].AddToEnd(temp);
			}
		}
	}
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < Listeler[i].Size; j++)
		{
			Student temp = Listeler[i].Pop();
			BuckedTemp.Push(temp);
		}
	}
	cout << "----------------------------------" << endl;

	BuckedTemp.DisplayNames();//test print
	cout << "----------------------------------" << endl;
}
List Sort::CopyList(List Target) {
	List Ret;
	int Length = Target.Size;
	for (int i = 1;i <= Length;i++)
	{
		Ret.AddToEnd(Target.FindNode(i)->data);
	}
	return Ret;
}

class BTreeNode
{
public:
	int *keys;
	int t;
	BTreeNode **C;
	int n;
	bool leaf;

	BTreeNode(int _t, bool _leaf);
	void insertNonFull(int k);
	void splitChild(int i, BTreeNode *y);
	//void traverse();
	void traverse(bool data);
	BTreeNode *search(int k);
	friend class BTree;
};

BTreeNode::BTreeNode(int t1, bool leaf1)
{
	t = t1;
	leaf = leaf1;
	keys = new int[2 * t - 1];
	C = new BTreeNode *[2 * t];
	n = 0;
}
int load[500];int lCount = 0;
void BTreeNode::traverse(bool data)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (leaf == false)
		{
			C[i]->traverse(false);
		}
		load[lCount] = keys[i];
		lCount++;
	}
	if (leaf == false)
	{
		C[i]->traverse(false);
	}
}
BTreeNode* BTreeNode::search(int k)
{
	int i = 0;
	while (i < n && k > keys[i])
	{
		i++;
	}
	if (keys[i] == k)
	{
		return this;
	}
	if (leaf == true)
	{
		return NULL;
	}
	return C[i]->search(k);
}
void BTreeNode::insertNonFull(int k)
{
	int i = n - 1;
	if (leaf == true)
	{
		while (i >= 0 && keys[i] > k)
		{
			keys[i + 1] = keys[i];
			i--;
		}
		keys[i + 1] = k;
		n = n + 1;
	}
	else
	{
		while (i >= 0 && keys[i] > k)
		{
			i--;
		}
		if (C[i + 1]->n == 2 * t - 1)
		{
			splitChild(i + 1, C[i + 1]);
			if (keys[i + 1] < k)
			{
				i++;
			}
		}
		C[i + 1]->insertNonFull(k);
	}
}
void BTreeNode::splitChild(int i, BTreeNode* y)
{
	BTreeNode* z = new BTreeNode(y->t, y->leaf);
	z->n = t - 1;
	for (int j = 0; j < t - 1; j++)
	{
		z->keys[j] = y->keys[j + t];
	}
	if (y->leaf == false)
	{
		for (int j = 0; j < t; j++)
		{
			z->C[j] = y->C[j + t];
		}
	}
	y->n = t - 1;
	for (int j = n; j >= i + 1; j--)
	{
		C[j + 1] = C[j];
	}
	C[i + 1] = z;
	for (int j = n - 1; j >= i; j--)
	{
		keys[j + 1] = keys[j];
	}
	keys[i] = y->keys[t - 1];
	n = n + 1;
}

class BTree
{
	int t;
public:
	BTreeNode *root;
	BTree()
	{
		root = NULL; t = 4;
	}
	void traverse(bool check)
	{
		if (root != NULL) root->traverse(check);
	}
	BTreeNode* search(int k)
	{
		return (root == NULL) ? NULL : root->search(k);
	}
	void insert(int k);
	friend class List;
};
void BTree::insert(int k)
{
	if (root == NULL)
	{
		root = new BTreeNode(t, true);
		root->keys[0] = k;
		root->n = 1;
	}
	else
	{
		if (root->n == 2 * t - 1)
		{
			BTreeNode *s = new BTreeNode(t, false);
			s->C[0] = root;
			s->splitChild(0, root);
			int i = 0;
			if (s->keys[0] < k)
			{
				i++;
			}
			s->C[i]->insertNonFull(k);
			root = s;
		}
		else
		{
			root->insertNonFull(k);
		}
	}
}

class BPlusTree {
public:
	void InsertStudent(Student data);
	void InsertStudent(int Number, string n, string s, string d);
	Student Search(int StudentNumber);
	bool IsExist(int StudentNumber);
	void DisplayTree(void);
	List GetListFromBTree(void);
	void InserFromLoadedData(List data);
	int GetLeafCount(void);
private:
	int* GetListIndexArray(void);
	BTree Keys;
	List Leaf;
};

void BPlusTree::InsertStudent(Student data)
{
	Keys.insert(data.Number);
	Leaf.AddToEnd(data);
}
void BPlusTree::InserFromLoadedData(List data)
{
	for (int i = 0; i < data.Size; i++)
	{
		InsertStudent(data.GetIndexData(i));
	}
}
void BPlusTree::InsertStudent(int Number, string n, string s, string d)
{
	Keys.insert(Number);
	Leaf.AddToEnd(Student(Number, n, s, d));
}
Student BPlusTree::Search(int StudentNumber)
{
	BTreeNode* temp = Keys.search(StudentNumber);
	if (temp)
	{
		//temp != NULL
		return Leaf.FindNodeWithNumber(StudentNumber)->data;
	}
	else
	{
		return NULL;
	}
}
bool BPlusTree::IsExist(int StudentNumber)
{
	BTreeNode* temp = Keys.search(StudentNumber);
	if (temp)
	{
		//temp != NULL
		return true;
	}
	else
	{
		return false;
	}
}
List BPlusTree::GetListFromBTree(void)
{
	int* SortedTreeArray = GetListIndexArray();
	List ret;
	//
	for (int i = 0; i < lCount; i++)
	{
		Node* node = Leaf.FindNodeWithNumber(SortedTreeArray[i]);
		if (node)
		{
			ret.AddToEnd(node->data);
		}
	}
	return ret;
}
void BPlusTree::DisplayTree(void)
{
	List Display = GetListFromBTree();
	Display.DispayWholeList();
}
int* BPlusTree::GetListIndexArray(void)
{
	lCount = 0;
	Keys.root->traverse(false);
	return load;
}
int BPlusTree::GetLeafCount(void)
{
	return Leaf.Size;
}

//Odev için gerekli Özel Fonksiyonlar

class Odev {
public:
	//2. Sorular.
	void SoruIkiA(List pro1, BPlusTree veri)
	{
		FileOperations fo; //dosya yükleme için gerekli class.
		Sort srt; //CopyList için gerekli Class.
		//LoadData listeleri Diskten yüklemeye yarayan Fonksiyon.
		List oldData = fo.LoadOldData(); //eski Ders listesi.
		List SonucP; //Programlama Sonuc Listesi
		List SonucV; //Veritabaný Sonuc Listesi
		for (int i = 0; i < oldData.Size; i++)
		{
			Student p = oldData.GetIndexData(i);
			if (pro1.FindNodeWithNumber(p.Number) != NULL)
			{
				//eðer Null deðilse Bu kiþi önceden de almýþ.
				SonucP.AddToEnd(p);
			}
			if (veri.IsExist(p.Number) == true)
			{
				//eðer True ise Bu kiþi önceden de almýþ.
				SonucV.AddToEnd(p);
			}
		}
		//yazdýrma iþlemleri.
		cout << endl;
		cout << "+-----------------------------------------------+" << endl;
		cout << "|       Bilgisayar Programlama Dersini          |" << endl;
		cout << "|          Onceden de alan Ogrenciler           |" << endl;
		cout << "+-----------------------------------------------+" << endl << endl;
		SonucP.DispayWholeList(); //Programlama Sonuc Listesi.
		cout << "+-----------------------------------------------+" << endl;
		cout << "|      Veritabi Yonetim Sistemi Dersini         |" << endl;
		cout << "|          Onceden de alan Ogrenciler           |" << endl;
		cout << "+-----------------------------------------------+" << endl;
		SonucV.DispayWholeList(); //Veritabaný Sonuc Listesi.
		cout << endl << "+-----------------------------------------------+" << endl << endl;
	}
	void SoruIkiB(List pro1, BPlusTree veri)
	{
		Sort srt; //CopyList için gerekli Class.
		//
		Student temp;
		List Sonuc = srt.CopyList(pro1); // asýl liste üzerinde deðiþiklik yapmamak için Yeni bir listeye kopyalama iþlemi yapýyorum.

		for (int i = 0; i < Sonuc.Size; i++) //Programlama Listesinin Boyutu kadar iþlem yapmam gerek.
		{
			int StudentNumber = Sonuc.GetIndexData(i).Number; //Ogrenci Numarasý üzerinden kontrol edildiði için Listeden i'inci elemanýn numasýný alýyorum.
			if (veri.IsExist(StudentNumber)) //bu numarayý B+ Aðacý üzerinde arýyorum eðer varsa True yoksa False deðer dönderiyor.
			{
				//true ise For a girer. demek ki
				//veritabýný yönetim sistemleri dersini de alýyor
				Sonuc.DeleteNode(i); //bu kiþiyi listeden çýkarýyorum çünkü listenin amacý sadece programlama alanlarý bulmak.
			}
		}
		cout << "+------------------------------------------------+" << endl;
		cout << "|          Sadece Bilgisayar Programlama         |" << endl;
		cout << "|            Dersini alanlarin Listesi           |" << endl;
		cout << "+------------------------------------------------+" << endl;
		Sonuc.DispayWholeList();
		cout << endl << "+------------------------------------------------+" << endl << endl;

	}
	void SoruIkiC(List pro1, BPlusTree veri)
	{
		Sort srt; //CopyList için gerekli Class.
		//LoadData listeleri Diskten yüklemeye yarayan Fonksiyon.
		List ProA; //A grubunda olanlarý yazdýrmak için Liste.
		List ProB; //B grubunda olanlarý yazdýrmak için Liste.
		BPlusTree VeriA; //A grubunda olanlarý yazdýrmak için B+ Aðacý.
		BPlusTree VeriB; //B grubunda olanlarý yazdýrmak için B+ Aðacý.
		//
		for (int i = 0; i < pro1.Size; i++)
		{
			Student p = pro1.GetIndexData(i); //i'inci elemaný p ye ata.
			char Group = p.GetGroup(); //i'inci elemanýn Grubunu bul.
			if (Group == 'A')
			{
				//A Grubunda
				ProA.AddToEnd(p);
			}
			else if (Group == 'B')
			{
				//B Grubunda
				ProB.AddToEnd(p);
			}
			else
			{
				//eðer sorun çýkarsa 'C' deðerini dönderiyor eðer C ise de B olarak sayýlmasýn diye else if olarak kullanýyorum.
			}
		}
		//Programlama Bitti sýra Veritabaný Yönetim Sistemlerinde.
		List temp = veri.GetListFromBTree(); //Aðaç içinde arama yapmak kolay ama i den n kadar git demek biraz sýkýntýlý onun için tüm aðacý listeye kopyalýyoruz.
		for (int i = 0; i < temp.Size; i++)
		{
			Student v = temp.GetIndexData(i); //i'inci elemaný p ye ata.
			char Group = v.GetGroup(); //i'inci elemanýn Grubunu bul.
			if (Group == 'A')
			{
				//A Grubunda
				VeriA.InsertStudent(v); //aðaca ekle
			}
			else if (Group == 'B')
			{
				//B Grubunda
				VeriB.InsertStudent(v); //aðaca ekle
			}
			else
			{
				//eðer sorun çýkarsa 'C' deðerini dönderiyor eðer C ise de B olarak sayýlmasýn diye else if olarak kullanýyorum.
			}
		}
		//Ýki ders de ayrýldý sýra tek tek yazdýrma da.
		//Öncelikle Programlama Tüm Liste.
		cout << endl;
		cout << "+------------------------------------------------+" << endl;
		cout << "|Bilgisayar Programlama Dersini alanlarin Listesi|" << endl;
		cout << "+------------------------------------------------+" << endl;
		pro1.DispayWholeList();
		cout << endl << "+------------------------------------------------+" << endl << endl;
		cout << "<                  Programlama                   >" << endl;
		cout << "<                  -A Grubu-                     >" << endl;
		ProA.DispayWholeList();
		cout << "+------------------------------------------------+" << endl << endl;
		cout << "<                  Programlama                   >" << endl;
		cout << "<                  -B Grubu-                     >" << endl;
		ProB.DispayWholeList();
		cout << "+------------------------------------------------+" << endl;
		cout << "|          Veritabani Yonetim Sistemleri         |" << endl;
		cout << "|            Dersini alanlarin Listesi           |" << endl;
		cout << "+------------------------------------------------+" << endl;
		veri.DisplayTree();
		cout << endl << "+------------------------------------------------+" << endl << endl;
		cout << "<                  Veritabani                    >" << endl;
		cout << "<                  -A Grubu-                     >" << endl;
		VeriA.DisplayTree();
		cout << endl << "+------------------------------------------------+" << endl << endl;
		cout << "<                  Veritabani                    >" << endl;
		cout << "<                  -B Grubu-                     >" << endl;
		VeriB.DisplayTree();
		cout << endl << "+------------------------------------------------+" << endl << endl;
	}
	void SoruIkiD(List pro1, BPlusTree veri)
	{
		Sort srt; //CopyList için gerekli Class.
		//
		List Sonuc; //Baþka Bölümden Kastýnýz Bilgisayar dýþýndakiler olarak hazýrlanmýþtýr.
		for (int i = 0; i < pro1.Size; i++)
		{
			Student p = pro1.GetIndexData(i);
			if (veri.IsExist(p.Number) == true)
			{
				//var yani iki dersi de alýyor.
				Sonuc.AddToEnd(p); //Listeye ekleme
			}
		}
		//Sonuc listesi þuan iki dersi alanlarla doldu.
		cout << "+-----------------------------------------------+" << endl;
		cout << "|       Iki dersi de alan Tum Ogrenciler        |" << endl;
		cout << "+-----------------------------------------------+" << endl << endl;
		Sonuc.DispayWholeList();
		cout << endl << "+------------------------------------------------+" << endl;
		//bize sadece diðer bölümlerdeki öðrenciler lazým onun için listeden bilgisayar Mühleri çýkarmamýz lazým.
		for (int i = Sonuc.Size - 1; i >= 0; i--)
		{
			string department = Sonuc.GetIndexData(i).Department;
			if (department == "BILGISAYARMUH")
			{
				Sonuc.DeleteNode(i);//eðer Bilgisayar Muhse sil
				//Çift anadal yapanlarý da diðer olarak sayýyoruz.
			}
		}
		cout << "+-----------------------------------------------+" << endl;
		cout << "|   Iki dersi de alan Diger Bolum Ogrencileri   |" << endl;
		cout << "+-----------------------------------------------+" << endl << endl;
		Sonuc.DispayWholeList();
		cout << endl << "+------------------------------------------------+" << endl;
	}

	//3. Sorular.
	void SoruUcA(List pro1, BPlusTree veri)
	{
		Sort srt; //QuickSort Ýçin Gerekli Class.
		//
		List Sonuc;
		for (int i = 0; i < pro1.Size; i++)
		{
			Student p = pro1.GetIndexData(i);
			if (veri.IsExist(p.Number) == true)
			{
				//var yani iki dersi de alýyor.
				Sonuc.AddToEnd(p); //Listeye ekleme
			}
		}
		//Sonuc listesi þuan iki dersi alanlarla doldu.
		cout << "+-----------------------------------------------+" << endl;
		cout << "|       Iki dersi de alan Tum Ogrenciler        |" << endl;
		cout << "+-----------------------------------------------+" << endl << endl;
		Sonuc.DispayWholeList();
		cout << endl << "-----------------------------------------------+" << endl << endl;

		srt.QuickSort(Sonuc, 0, Sonuc.Size - 1); //QuickSort(List liste,baþlangýç,bitiþ);
		cout << "+-----------------------------------------------+" << endl;
		cout << "|       Iki dersi de alan Tum Ogrenciler        |" << endl;
		cout << "|          Soyada Gore Siralanmistir            |" << endl;
		cout << "+-----------------------------------------------+" << endl << endl;
		Sonuc.DispayWholeList();
		cout << endl << "+-----------------------------------------------+" << endl << endl;
	}
	void SoruUcB(List pro1, BPlusTree veri)
	{
		Sort srt; //Radix için gerekli
		List Sonuc; //Sonuc listesi
		List temp = veri.GetListFromBTree();
		for (int i = 0; i < temp.Size; i++)
		{
			Student p = temp.GetIndexData(i);
			if (pro1.FindNodeWithNumber(p.Number) == NULL)
			{
				Sonuc.AddToEnd(p);
			}
		}
		//Kalan Sonuç listesi sadece Veritabani alanlardan Oluþuyor.
		cout << "+-----------------------------------------------+" << endl;
		cout << "|     Sadece Veritabani Yonetim Sistemli        |" << endl;
		cout << "|          Dersini Alan Ogrenciler              |" << endl;
		cout << "+-----------------------------------------------+" << endl << endl;
		Sonuc.DispayWholeList();
		cout << endl << "+-----------------------------------------------+" << endl << endl;
		//srt.RadixSort(Sonuc);
		Sonuc = srt.InsertionR(Sonuc);// xd
		cout << "+-----------------------------------------------+" << endl;
		cout << "|     Sadece Veritabani Yonetim Sistemli        |" << endl;
		cout << "|          Dersini Alan Ogrenciler              |" << endl;
		cout << "|      Radix Sort ile Ada gore Siralanmis       |" << endl;
		cout << "+-----------------------------------------------+" << endl << endl;
		Sonuc.DispayWholeList();
		cout << endl << "+-----------------------------------------------+" << endl << endl;

	}
	void SoruUcC(List pro1)
	{
		Sort srt; //HeapSort Ýçin Gerekli Class.
		List Sonuc = srt.CopyList(pro1); //Asil listenin üzerinde iþlem yapmamak için Sort için yeni bir Liste aktarýyorum.
		cout << "+-----------------------------------------------+" << endl;
		cout << "|     Bilgisayar Programlama Dersini alan       |" << endl;
		cout << "|                 Ogrenciler                    |" << endl;
		cout << "+-----------------------------------------------+" << endl << endl;
		Sonuc.DispayWholeList();
		cout << endl << "+-----------------------------------------------+" << endl << endl;
		srt.HeapSort(Sonuc);
		cout << "+-----------------------------------------------+" << endl;
		cout << "|       Bilgisayar Programlama Dersini alan     |" << endl;
		cout << "|Ogrenciler. HeapSort ile Numaraya Gore Siranmis|" << endl;
		cout << "+-----------------------------------------------+" << endl << endl;
		Sonuc.DispayWholeList();
		cout << endl << "+-----------------------------------------------+" << endl << endl;
		//
	}
};

//Arayüz Classý
class UserInterface {
public:
	void printMenu()
	{
		cout << "+-------------------------------------------------------------------------------+" << endl;
		cout << "|                                                                               |" << endl;
		cout << "|                    +----------------------------------+                       |" << endl;
		cout << "|                    |  Veri Yapilari ve Algoritmalar   |                       |" << endl;
		cout << "|                    |    Dersi Sonbahar 2018 Odevi     |                       |" << endl;
		cout << "|                    +----------------------------------+                       |" << endl;
		cout << "|                                                                (c)Jellybeanci |" << endl;
		cout << "+-------------------------------------------------------------------------------+" << endl << endl;
		cout << "(1-) Bilgisayar Programlama dersini Alanlari Yazdir." << endl;
		cout << "(2-) Veritabani Yonetim Sistemleri dersini Alanlari Yazdir." << endl;
		cout << "(3-) 2. Soru->A (Her iki dersi de birden fazla key alan Ogrencileri Listele)" << endl;
		cout << "(4-) 2. Soru->B (Sadece Bilgisayar Programlama dersini alan Ogrencileri Listele)" << endl;
		cout << "(5-) 2. Soru->C (Her iki dersi listesini de, Soyadlarinin ilk harfine göre A-B olarak ayir ve Listele)" << endl;
		cout << "(6-) 2. Soru->D (Bilgisayar Programlama ve Veritabani Yonetim sistemlerini alan Diger Bolum Ogrencilerini Listele)" << endl;
		cout << "(7-) 3. Soru->A (Hizli Siralama algoritmasini kullanarak Her iki dersi de alan Ogrencileri Soyadlarina Gore Sirala )" << endl;
		cout << "(8-) 3. Soru->B (Radix Siralama algoritmasini kullanarak Sadece Veritabni Yonetim sistemleri dersini alan Ogrencileri Adlarina Gore Sirala)" << endl;
		cout << "(9-) 3. Soru->C (Kumeleme Siralama algoritmasini kullanarak Bilgisayar Programlama dersini alan Ogrencileri Numaralarina Gore Sirala)" << endl;
		cout << "(0-) <-CIKIS->" << endl << endl;
		cout << " -> ";
	}
	bool GetInputFromUser(int Index, List Pro, BPlusTree Veri)
	{
		Odev odev;
		bool state = true;
		FileOperations fo;
		switch (Index)
		{
		case 0: {
			_Exit(0); //Çýk
			break;
		}
		case 1: {
			cout << endl;
			cout << "+-----------------------------------------------+" << endl;
			cout << "|       Bilgisayar Programlama Alanlar           " << endl;
			cout << "+-----------------------------------------------+" << endl << endl;
			Pro.DispayWholeList();
			cout << endl << "+-----------------------------------------------+" << endl << endl;
			break;
		}
		case 2: {
			cout << endl;
			cout << "+-----------------------------------------------+" << endl;
			cout << "|      Veritabani ve Yonetim Sistemleri         |" << endl;
			cout << "+-----------------------------------------------+" << endl << endl;
			Veri.DisplayTree();
			cout << endl << "+-----------------------------------------------+" << endl << endl;
			break;
		}
		case 3: {

			odev.SoruIkiA(Pro, Veri);
			break;
		}
		case 4: {
			odev.SoruIkiB(Pro, Veri);
			break;
		}
		case 5: {
			odev.SoruIkiC(Pro, Veri);
			break;
		}
		case 6: {
			odev.SoruIkiD(Pro, Veri);
			break;
		}
		case 7: {
			odev.SoruUcA(Pro, Veri);
			break;
		}
		case 8: {
			odev.SoruUcB(Pro, Veri);
			break;
		}
		case 9: {
			odev.SoruUcC(Pro);
			break;
		}
		default: {
			state = false;
			break;
		}
		}
		return state;
	}
	void TesterUI(List Pro, BPlusTree Veri)
	{
		FileOperations fo;
		List BilgisayarProgramlama = fo.LoadData(true); //true olursa Bilgisayar Programlama, false ise Veritabaný Yönetim Sistemleri.
		BPlusTree veri;
		veri.InserFromLoadedData(fo.LoadData(false)); //true olursa Bilgisayar Programlama, false ise Veritabaný Yönetim Sistemleri.
		Sort srt;
		List pro1 = srt.CopyList(BilgisayarProgramlama);

		//Student GetIndexData(int index);
		Student Ogr = pro1.GetIndexData(17);

		//void GetGroup();
		char Grp = Ogr.GetGroup();
		cout << Ogr.Surname << " Soyisimli kisinin GetGroup()'den donen degeri: " << Grp << endl << endl;

		//string PrintRow(bool group);
		cout << Ogr.PrintRow(false) << endl;
		cout << endl;

		//void SetStudent(int No, string Name, string Surname, string Department); 
		Student yeniOgr;
		yeniOgr.SetStudent(100, "Ibrahim", "Bozbey", "ELEKTRIKMUH");
		cout << yeniOgr.PrintRow(true) << endl;
		cout << endl;

		//bool IsEmpty();
		List yeniListe;
		yeniListe.IsEmpty() ? cout << "BOS LISTE" << endl : cout << "DOLU LISTE" << endl;
		cout << endl;

		//void AddToEnd(Student data);
		yeniListe.AddToEnd(yeniOgr);
		yeniListe.IsEmpty() ? cout << "BOS LISTE" << endl : cout << "DOLU LISTE" << endl;
		cout << endl;

		//void DisplayWholeList();
		yeniListe.DispayWholeList();
		cout << endl;

		//Node* InsertNode(int index, Student data);
		yeniListe.InsertNode(1, Ogr);
		cout << endl;

		//void DisplayNames();
		yeniListe.DisplayNames();
		cout << endl;

		//Node* FindNode(int index);
		Node* fn = pro1.FindNode(12);
		cout << fn->data.PrintRow(true) << endl;
		cout << endl;

		//void Push(Student data);
		yeniListe.Push(fn->data);
		cout << endl;

		//void DisplayNumber();
		yeniListe.DisplayNumbers();
		cout << endl;

		//void DisplayWholeSurnames();
		pro1.DispayWholeSurnames();
		cout << endl;

		//void DeleteNode(int index);
		pro1.DispayWholeList();
		cout << endl;
		pro1.DeleteNode(16);
		pro1.DispayWholeList();
		cout << endl;

		//void Swap(int a, int b);
		pro1.Swap(5, 19);
		pro1.DispayWholeList();
		cout << endl;

		//Node* FindNodeWithNunber(int StudentNumber);
		Node* gks = pro1.FindNodeWithNumber(1030522874);
		cout << gks->data.PrintRow(false) << endl;
		cout << endl;

		//Student Pop();
		Student p = pro1.Pop();
		cout << p.PrintRow(true) << endl;
		cout << endl;

		//
		cout << endl << endl << endl << endl;
		//

		//Class StringOperation 
		StringOperation so;
		//bool so.StringCompare(string p, string s);
		string s1 = "elma";
		string s2 = "Goksel";
		string s3 = "elmaci";
		string s4 = "Mete";

		if (so.StringCompare(s1, s2))
		{
			cout << s2 << ", " << s1 << "'den daha onde" << endl;
		}
		else
		{
			cout << s1 << ", " << s2 << "'den daha onde" << endl;
		}
		cout << endl;

		//
		if (so.StringCompare(s1, s3))
		{
			cout << s3 << ", " << s1 << "'den daha onde" << endl;
		}
		else
		{
			cout << s1 << ", " << s3 << "'den daha onde" << endl;
		}
		cout << endl;

		//
		if (so.StringCompare(s2, s4))
		{
			cout << s4 << ", " << s2 << "'den daha onde" << endl;
		}
		else
		{
			cout << s2 << ", " << s4 << "'den daha onde" << endl;
		}
		cout << endl;

		//
		cout << endl << endl << endl << endl;
		//


		//void QuickSort(List inputList, int start, int end);
		Sort s;
		s.QuickSort(pro1, 0, pro1.Size - 1);
		pro1.DispayWholeList();
		cout << endl;
		
		//void HeapSort(List inputList);
		s.HeapSort(pro1);
		pro1.DispayWholeList();
		cout << endl;

		//List CopyList(List Target);
		List cpyList = s.CopyList(BilgisayarProgramlama);
		cpyList.DispayWholeList();
		cout << endl;

		//
		cout << endl << endl << endl << endl;
		//


		//void DisplayTree();
		veri.DisplayTree();
		cout << endl;

		//void InsertStudent(Student data);
		Student n(17004453, "HUSEYIN", "KIS", "ELEKTRIKMUH");
		veri.InsertStudent(n);
		veri.DisplayTree();
		cout << endl;

		//Student Search(int StudentNumber);
		Student src = veri.Search(17004453);
		cout << src.PrintRow(true) << endl;
		cout << endl;

		//bool IsExist(int StudentNumber);
		bool y = veri.IsExist(1030522874);
		if (y == true)
		{
			cout << 1030522874 << " numarali kisi var." << endl;
		}
		else
		{
			cout << 1030522874 << " numarali kisi yok." << endl;
		}
		cout << endl;
		bool z = veri.IsExist(17004453);
		if (y == true)
		{
			cout << 17004453 << " numarali kisi var." << endl;
		}
		else
		{
			cout << 17004453 << " numarali kisi yok." << endl;
		}
		cout << endl;
	}
};

void main()
{
	//Yeni baþlýyor.
	FileOperations fo; //dosya yükleme için gerekli class.
	//
	//LoadData listeleri Diskten yüklemeye yarayan Fonksiyon.
	List BilgisayarProgramlama = fo.LoadData(true); //true olursa Bilgisayar Programlama, false ise Veritabaný Yönetim Sistemleri.
	BPlusTree Veritabani;
	Veritabani.InserFromLoadedData(fo.LoadData(false)); //true olursa Bilgisayar Programlama, false ise Veritabaný Yönetim Sistemleri.
	//
	system("cls"); //Clear Screen
	int Select = -1; //Index Deðiþkeni
	UserInterface UI; //Arayüz Sýnýr Classý
	//
	//UI.TesterUI(BilgisayarProgramlama,Veritabani); //Ekran Görüntüsü almak için Kullanýldý Son Programda Yeri yok
	//
	do {
		UI.printMenu(); //Menüyü yazdýr
		cin >> Select; //Kullanýcýdan index iste
		if (Select >= 0 && Select <= 9) //index aralýkta mý ?
		{
			//devam
			cout << endl << endl << endl << endl; //Ýki soru arasý boþluk býrakmak için \n.
			continue;
		}
		else //deðilse Uyar ve Baþa Gönder
		{
			cout << "Gecersiz Girdi"; //Uyarý mesajý
			main(); // Recursive Looping
		}
	} while (UI.GetInputFromUser(Select, BilgisayarProgramlama, Veritabani)); //Döngü gerek þartý
}
//END OF THE LINE ~ S3cT0r42