#ifndef ADMINAREA_H
#define ADMINAREA_H

// include library buatan
#include "reviewer.h"
#include "movie.h"

// prosedur menu admin
void menuAdmin(listReviewer &listReviewer, listMovie &listMovie);
// prosedur input data movie
void inputDataMovie(listMovie listMovie);
// prosedur update data movie
void updateDataMovie(listMovie listMovie);
// prosedur view data movie
void viewDataMovie(listMovie listMovie);
// prosedur delete data movie
void deleteDataMovie(listMovie &listMovie);
// prosedur view data reviewer
void viewDataReviewer(listReviewer listReviewer);
// prosedur delete data reviewer
void deleteDataReviewer(listReviewer &listReviewer);

#endif // ADMINAREA_H