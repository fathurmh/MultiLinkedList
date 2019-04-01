#ifndef REVIEW_H
#define REVIEW_H

// include library c++
#include <string>

// include library buatan
#include "movie.h"
#include "reviewer.h"

// using namespace
using namespace std;

// pointer alamat memory review
typedef struct elementReview *addressReview;

// tipe bentukan data review
struct review {
	int id;
	int rating;
    string description;
};

// tipe bentukan elemen review
struct elementReview {
	// variabel data review pada elemen saat ini
	review data;
	// pointer menuju elemen sebelumnya
	addressReview prev;
	// pointer menuju elemen selanjutnya
	addressReview next;
	// pointer menuju elemen reviewer
	addressReviewer reviewer;
	// pointer menuju elemen movie
	addressMovie movie;
};

// tipe bentukan list review
struct listReview {
	// pointer menuju elemen pertama pada list
	addressReview first;
	// pointer menuju elemen terakhir pada list
	addressReview last;
};

// prosedur membuat list baru
void createList(listReview &newListReview);
// fungsi membuat data review
review createReview(int rating, string description);
// fungsi alokasi review
addressReview alokasiReview(review newReview, addressReviewer addressReviewer, addressMovie addressMovie);
// prosedur insert first review
void insertFirst(listReview &listReview, addressReview newAddressReview);
// prosedur insert last review
void insertLast(listReview &listReview, addressReview newAddressReview);
// prosedur update review
void updateReview(addressReview review, int newRating, string newDescription);
// prosedur delete review
void deleteReview(listReview &listReview, addressReview review);
// prosedur delete all review
void deleteAll(listReview &listReview);
// prosedur delete first review
void deleteFirst(listReview &listReview);
// prosedur delete last review
void deleteLast(listReview &listReview);
// fungsi cari review by id pada list
addressReview searchById(listReview &listReview, int id);
// fungsi hitung total elemen pada list
int countList(listReview listReview);
// prosedur cetak data review
void cetakReview(addressReview addressReview);
// prosedur cetak list data review
void cetakList(listReview listReview);

#endif // REVIEW_H
