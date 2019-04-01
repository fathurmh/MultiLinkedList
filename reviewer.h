#ifndef REVIEWER_H
#define REVIEWER_H

// include library c++
#include <string>

// using namespace
using namespace std;

// pointer alamat memory reviewer
typedef struct elementReviewer *addressReviewer;

// tipe bentukan data reviewer
struct reviewer {
	int id;
    string nama;
    string username;
    string password;
};

// tipe bentukan elemen reviewer
struct elementReviewer {
	// variabel data reviewer pada elemen saat ini
	reviewer data;
	// pointer menuju elemen sebelumnya
	addressReviewer prev;
	// pointer menuju elemen selanjutnya
	addressReviewer next;
};

// tipe bentukan list reviewer
struct listReviewer {
	// pointer menuju elemen pertama pada list
	addressReviewer first;
	// pointer menuju elemen terakhir pada list
	addressReviewer last;
};

// prosedur membuat list baru
void createList(listReviewer &newListReviewer);
// fungsi membuat data reviewer
reviewer createReviewer(string nama, string username, string password);
// fungsi alokasi reviewer
addressReviewer alokasiReviewer(reviewer newReviewer);
// prosedur insert first reviewer
void insertFirst(listReviewer &listReviewer, addressReviewer newAddressReviewer);
// prosedur insert last reviewer
void insertLast(listReviewer &listReviewer, addressReviewer newAddressReviewer);
// prosedur delete reviewer
void deleteReviewer(listReviewer &listReviewer, addressReviewer reviewer);
// prosedur delete all reviewer
void deleteAll(listReviewer &listReviewer);
// prosedur delete first reviewer
void deleteFirst(listReviewer &listReviewer);
// prosedur delete last reviewer
void deleteLast(listReviewer &listReviewer);
// fungsi cari reviewer by username pada list
addressReviewer searchByUsername(listReviewer &listReviewer, string username);
// fungsi cari reviewer by id pada list
addressReviewer searchById(listReviewer &listReviewer, int id);
// fungsi hitung total elemen pada list
int countList(listReviewer listReviewer);
// prosedur cetak data reviewer
void cetakReviewer(addressReviewer addressReviewer);
// prosedur cetak list data reviewer
void cetakList(listReviewer listReviewer);

#endif // REVIEWER_H