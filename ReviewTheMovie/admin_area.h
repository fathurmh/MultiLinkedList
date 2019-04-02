#ifndef ADMIN_AREA_H_INCLUDED
#define ADMIN_AREA_H_INCLUDED

// include library buatan
#include "list_reviewer.h"
#include "list_movie.h"
#include "list_review.h"

// prosedur menu admin
void menuAdmin(ListReviewer &listReviewer, ListMovie &listMovie, ListReview ListReview);
// prosedur input data movie
void inputDataMovie(ListMovie listMovie);
// prosedur update data movie
void updateDataMovie(ListMovie listMovie);
// prosedur view data movie
void viewDataMovie(ListMovie listMovie, ListReview listReview);
// prosedur delete data movie
void deleteDataMovie(ListMovie &listMovie);
// prosedur view data reviewer
void viewDataReviewer(ListReviewer listReviewer);
// prosedur delete data reviewer
void deleteDataReviewer(ListReviewer &listReviewer);

#endif // ADMIN_AREA_H_INCLUDED