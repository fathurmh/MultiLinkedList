#ifndef GUEST_AREA_H_INCLUDED
#define GUEST_AREA_H_INCLUDED

// include library buatan
#include "common.h"
#include "reviewer.h"
#include "movie.h"
#include "review.h"

// fungsi sign in
loginUser signIn(listReviewer listReviewer);
// prosedur sign up
void signUp(listReviewer &listReviewer);
// view top 10 movie dengan ulasan terbanyak
void viewTopTenMovie(ListReview ListReview, listMovie listMovie);

#endif // GUEST_AREA_H_INCLUDED