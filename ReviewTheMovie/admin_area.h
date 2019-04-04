#ifndef ADMIN_AREA_H_INCLUDED
#define ADMIN_AREA_H_INCLUDED

// include library buatan
#include "list_reviewer.h"
#include "list_movie.h"
#include "list_review.h"

// using namespace
using namespace std;

// prosedur menu admin
void MenuAdmin(ListReviewer &list_reviewer, ListMovie &list_movie, ListReview &list_review);

// prosedur input data movie
void InputDataMovie(ListMovie &list_movie);
// prosedur update data movie
void UpdateDataMovie(ListMovie &list_movie);
// prosedur view data movie
void ViewDataMovie(ListMovie list_movie, ListReview list_review);
// prosedur delete data movie
void DeleteDataMovie(ListReview &list_review, ListMovie &list_movie);
// prosedur view data reviewer
void ViewDataReviewer(ListReviewer list_reviewer, ListReview list_review);
// prosedur delete data reviewer
void DeleteDataReviewer(ListReview &list_review, ListReviewer &list_reviewer);

#endif // ADMIN_AREA_H_INCLUDED