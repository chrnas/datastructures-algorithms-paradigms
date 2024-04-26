/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include "Robot.h"
#include <QGraphicsScene>

class Junk : public Robot {
public:
    Junk(const Point& p): Robot(p){}

    ~Junk(){};

    virtual Junk* clone() const {return new Junk{*this};}

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const;

    std::string toString(){
        return "JUNK";
    }

    /*
     * Crashes and remembers it
     */
    void doCrash();

    /*
     * Return whether the robot crashed
     */
    bool justCrashed() const;

    /*
    * Does not move.
    */
    void moveTowards(const Unit&);

    bool canMove() const;
};



#endif // JUNK_H
