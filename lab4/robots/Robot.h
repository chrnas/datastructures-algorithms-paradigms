/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef ROBOT_H
#define ROBOT_H

#include "Unit.h"
#include <QGraphicsScene>

class Robot : public Unit {
    bool crashed = false;

public:

    Robot(const Point& p): Unit(p){}

    Robot() : Unit(){}

    ~Robot(){};

    /**
     * @brief polymor
     */
    virtual Robot* clone() const {return new Robot{*this};}

    /*
     * did not crash yet
     */
    virtual bool canMove() const;

    /*
     * Crashes and remembers it
     */
    virtual void doCrash();

    /*
     * Return whether the robot crashed
     */
    bool justCrashed() const;

    virtual std::string toString(){
     return "ROBOT";
    }

    /*
    * Draws this robot onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const;


};

#endif // ROBOT_H
