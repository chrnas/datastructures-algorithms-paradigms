/**
 * created by chrna581, Christoffer Näs and miklu523, Mikael Lundgren.
 * This file contains the declaration of the Tour Class
 * A linked list of Nodes. New nodes can be added through the insertNearest or insertSmallest function.
 * See Tour.cpp for implementation of each member.
*/

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

/**
 * Tour Class is a circled linked-list of points.
 *
 */
class Tour {
public:

    /**
     * Default constructor for class Tour
     *
     */
    Tour();

    /**
     * Default destructor for class Tour
     *
     */
    ~Tour();

    /**
     * prints coordinates for a Tour in terminal
     */
    void show() const;

    /**
     * Draws lines beetween the different Points in Tour to show the Tour graphicly in a window.
     *
     * @param scene QGrapicScene component that helps draw the Tour in a window
     */
    void draw(QGraphicsScene *scene) const;

    /**
     * Determines the size of a Tour
     *
     * @return returns an int size representing the number of points in the Tour
     */
    int size() const;

    /**
     * Determines the distance of the Tour
     *
     * @return a double distance representing the distance beetween all the points in the Tour.
     */
    double distance() const;

    /**
     * Inserts a point into a Tour so that the new Points have the nearest distance beetween the Points
     *
     * @param Point p the Point that are about to be inserted.
     */
    void insertNearest(const Point& p);

    /**
     * Inserts a point into a Tour so that the samllest distance beetween the new points ??
     *
     * @param Point p the Point that are about to be inserted.
     */
    void insertSmallest(const Point& p);


    Node *firstNodePtr;

private:

};

#endif // TOUR_H
