#ifndef LIST_REVIEW_H_INCLUDED
#define LIST_REVIEW_H_INCLUDED

// include library c++
#include <string>

// include library buatan
#include "list_reviewer.h"
#include "list_movie.h"

// using namespace
using namespace std;

// pointer menuju elemen reviewer
#define REVIEWER(p) p->reviewer
// pointer menuju elemen movie
#define MOVIE(p) p->movie

// pointer alamat memory review
typedef struct ElementReview *AddressReview;

// tipe bentukan data review
struct Review {
    int id;
    int rating;
    string description;
};

// tipe bentukan elemen review
struct ElementReview {
    // variabel data review pada elemen saat ini
    Review data;
    // pointer menuju elemen selanjutnya
    AddressReview next;
    // pointer menuju elemen reviewer
    AddressReviewer reviewer;
    // pointer menuju elemen movie
    AddressMovie movie;
};

// tipe bentukan list review
struct ListReview {
    // pointer menuju elemen pertama pada list
    AddressReview first;
};

// prosedur membuat list baru
void CreateList(ListReview &list_review);
// fungsi membuat data review
Review CreateReview(int rating, string description);

// fungsi alokasi
AddressReview Allocate(Review review, AddressReviewer address_reviewer, AddressMovie address_movie);
// fungsi alokasi array
AddressReview *Allocate(int size);
// prosedur dealokasi
void Deallocate(AddressReview &address_review);
// prosedur dealokasi array
void Deallocate(AddressReview *(&address_review));

// prosedur insert first
void InsertFirst(ListReview &list_review, AddressReview address_review);
// prosedur insert last
void InsertLast(ListReview &list_review, AddressReview address_review);

// prosedur update review
void UpdateReview(AddressReview address_review, int new_rating, string new_description);

// prosedur delete first
void DeleteFirst(ListReview &list_review);
// prosedur delete last
void DeleteLast(ListReview &list_review);
// prosedur delete last
void DeleteReview(ListReview &list_review, AddressReview address_review);
// prosedur delete all
void DeleteAll(ListReview &list_review);
// prosedur delete reviewer with all reviews
void DeleteReviewerWithReview(ListReview &list_review, ListReviewer &list_reviewer, AddressReviewer address_reviewer);
// prosedur delete movie with all reviews
void DeleteMovieWithReview(ListReview &list_review, ListMovie &list_movie, AddressMovie address_movie);

// fungsi cari review by id pada list
AddressReview FindById(ListReview list_review, int id);
// fungsi cari review by movie id pada list
AddressReview *FindByMovieId(ListReview list_review, int id);
// fungsi cari review by reviewer id pada list
AddressReview *FindByReviewerId(ListReview list_review, int id);
// fungsi generate top 10 movie
ListMovie TopTenMovies(ListMovie list_movie, ListReview list_review);

// fungsi hitung total elemen pada list
int Count(ListReview list_review);
// fungsi hitung total elemen pada array
int Count(AddressReview *address_review);

// prosedur cetak data review
void Cetak(AddressReview address_review);
// prosedur cetak data review with reviewer
void CetakWithReviewer(AddressReview address_review);
// prosedur cetak data review with movie
void CetakWithMovie(AddressReview address_review);
// prosedur cetak list data review
void Cetak(ListReview list_review);
// prosedur cetak list data review dan reviewernya
void CetakReviewerWithReview(ListReview list_review, AddressReviewer address_reviewer);
// prosedur cetak list data review dan movienya
void CetakMovieWithReview(ListReview list_review, AddressMovie address_movie);

#endif // LIST_REVIEW_H_INCLUDED
