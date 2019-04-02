#ifndef GUEST_AREA_H_INCLUDED
#define GUEST_AREA_H_INCLUDED

// include library buatan
#include "reviewer.h"
#include "list_movie.h"
#include "review.h"

// using namespace
using namespace std;

// fungsi sign in
LoginUser signIn(listReviewer listReviewer);
// prosedur sign up
void signUp(listReviewer &listReviewer);
// view top 10 movie dengan ulasan terbanyak
void viewTopTenMovie(ListReview ListReview, ListMovie listMovie);

#endif // GUEST_AREA_H_INCLUDED