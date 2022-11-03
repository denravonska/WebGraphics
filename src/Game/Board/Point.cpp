#include "Point.h"


void Point::closeDistance(Point to) {
    if (file < to.file)
        file++;
    else if (file > to.file)
        file--;
    if (rank < to.rank)
        rank++;
    else if (rank > to.rank)
        rank--;
}

bool Point::isInsideBoard() {
    return file >= 0 && file <= 7 && rank >= 0 && rank <= 7;
}