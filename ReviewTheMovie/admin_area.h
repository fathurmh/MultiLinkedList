#ifndef ADMIN_AREA_H_INCLUDED
#define ADMIN_AREA_H_INCLUDED

// include library buatan
#include "reviewer.h"
#include "list_movie.h"
#include "review.h"

// prosedur menu admin
void menuAdmin(listReviewer &listReviewer, ListMovie &listMovie, ListReview ListReview);
// prosedur input data movie
void inputDataMovie(ListMovie listMovie);
// prosedur update data movie
void updateDataMovie(ListMovie listMovie);
// prosedur view data movie
void viewDataMovie(ListMovie listMovie, ListReview listReview);
// prosedur delete data movie
void deleteDataMovie(ListMovie &listMovie);
// prosedur view data reviewer
void viewDataReviewer(listReviewer listReviewer);
// prosedur delete data reviewer
void deleteDataReviewer(listReviewer &listReviewer);

#endif // ADMIN_AREA_H_INCLUDED