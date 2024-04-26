/**
 * created by chrna581, Christoffer Näs and miklu523, Mikael Lundgren.
 * This file contains the implementation of the Tour Class
 * A linked list of Nodes. New nodes can be added through the insertNearest or insertSmallest function.
 * See Tour.h for comments for each member.
*/

#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{
    firstNodePtr = nullptr;
}

Tour::~Tour()
{
    if(firstNodePtr != nullptr)
    {
        Node *start = firstNodePtr;
        firstNodePtr = firstNodePtr->next;
        Node *next;
        while(firstNodePtr != start)
        {
            next = firstNodePtr->next;
            delete firstNodePtr;
            firstNodePtr = next;
        }
        delete firstNodePtr;
    }
}

void Tour::show() const
{
    if(firstNodePtr != nullptr){

        Node* curr = firstNodePtr;
        do{
            cout << "(" << curr->point.x << "," << curr->point.y << ")" <<endl;
            curr = curr->next;
        }while(curr != firstNodePtr);

    }
}

void Tour::draw(QGraphicsScene *scene) const
{
    if(firstNodePtr != nullptr){
        Node* curr = firstNodePtr;
        do{
            curr->point.drawTo(curr->next->point,scene);
            curr = curr->next;
        }
        while(curr != firstNodePtr);

    }
}

int Tour::size() const
{
    int size = 0;
    if(firstNodePtr != nullptr){

        Node* curr = firstNodePtr;
        do{
            curr = curr->next;
            size ++;
        }
        while(curr != firstNodePtr);
    }
    cout << size <<endl;
    return size;
}

double Tour::distance() const
{
    double distance = 0;
    if(firstNodePtr != nullptr){
        Node* curr = firstNodePtr;
        do{
            distance += curr->point.distanceTo(curr->next->point);
            curr = curr->next;
        }
        while(curr != firstNodePtr);
    }
    cout << distance <<endl;
    return distance;
}

void Tour::insertNearest(const Point& p)
{
    if(firstNodePtr != nullptr){
        Node *nearestNode = firstNodePtr;
        double nearestDistance = firstNodePtr->point.distanceTo(p);

        Node* curr = firstNodePtr->next;
        while(curr != firstNodePtr){
            double distanceCurr = curr->point.distanceTo(p);
            if(nearestDistance > distanceCurr){
                nearestDistance = distanceCurr;
                nearestNode = curr;
            }
            curr = curr->next;
        }
        nearestNode->next = new Node(p, nearestNode->next);
    }
    else{
        firstNodePtr = new Node(p, nullptr);
        firstNodePtr->next = firstNodePtr;

    }
}

void Tour::insertSmallest(const Point &p)
{
    if(firstNodePtr != nullptr){
        Node *nearestNode = firstNodePtr;

        double distanceBetween = (firstNodePtr->point.distanceTo(p) + firstNodePtr->next->point.distanceTo(p)) - firstNodePtr->point.distanceTo(firstNodePtr->next->point);


        Node* curr = firstNodePtr->next;
        while(curr != firstNodePtr){
            double distanceBetweenCurr = (curr->point.distanceTo(p) + curr->next->point.distanceTo(p)) - curr->point.distanceTo(curr->next->point);
            if(distanceBetween > distanceBetweenCurr){
                distanceBetween = distanceBetweenCurr;
                nearestNode = curr;
            }
            curr = curr->next;
        }
        nearestNode->next = new Node(p, nearestNode->next);
    }
    else{
        firstNodePtr = new Node(p, nullptr);
        firstNodePtr->next = firstNodePtr;
    }

}


