#ifndef REVIEWER_AREA_H_INCLUDED
#define REVIEWER_AREA_H_INCLUDED

// include library buatan
#include "list_reviewer.h"
#include "list_movie.h"
#include "list_review.h"

// using namespace
using namespace std;

// prosedur menu reviewer
void MenuReviewer(ListReviewer list_reviewer, ListMovie list_movie, ListReview &list_review, AddressReviewer current_address_reviewer);

// prosedur input review
void InputDataReview(ListReview &list_review, ListMovie list_movie, AddressReviewer current_address_reviewer);
// prosedur update review
void UpdateDataReview(ListReview &list_review, AddressReviewer current_address_reviewer);
// prosedur delete review
void DeleteDataReview(ListReview &list_review, AddressReviewer current_address_reviewer);
// prosedur view review history
void ViewReviewHistory(ListReview list_review, AddressReviewer current_address_reviewer);
// prosedur update account
void UpdateAccount(ListReviewer list_reviewer, AddressReviewer current_address_reviewer);


#endif // REVIEWER_AREA_H_INCLUDED