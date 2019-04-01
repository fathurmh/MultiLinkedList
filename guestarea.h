#ifndef GUESTAREA_H_INCLUDED
#define GUESTAREA_H_INCLUDED

// include library buatan
#include "common.h"
#include "reviewer.h"

// fungsi sign in
loginUser signIn(listReviewer listReviewer);
// prosedur sign up
void signUp(listReviewer &listReviewer);

#endif // GUESTAREA_H_INCLUDED