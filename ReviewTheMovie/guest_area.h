#ifndef GUEST_AREA_H_INCLUDED
#define GUEST_AREA_H_INCLUDED

// include library buatan
#include "list_reviewer.h"
#include "list_movie.h"
#include "list_review.h"

// using namespace
using namespace std;

// fungsi sign in
LoginUser SignIn(ListReviewer list_reviewer, AddressReviewer &address_reviewer);
// prosedur sign up
void SignUp(ListReviewer &list_reviewer);

// view top 10 movie dengan ulasan terbanyak
void ViewTopTenMovie(ListMovie list_movie, ListReview list_review);

#endif // GUEST_AREA_H_INCLUDED