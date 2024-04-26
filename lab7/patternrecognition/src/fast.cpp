/*
 * TDDD86 Pattern Recognition
 * This program computes and plots all line segments involving 3 or more points in the line.
 * in a file using Qt.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"

// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

// TAGEN KOD FRÅN NÄTET: cmp()
// Comparator function to sort pairs
// according to second value
bool cmp(pair<Point, double>& a,
         pair<Point, double>& b)
{
    return a.second < b.second;
}

/**
 * @brief fastRender Goes throught a text file with points and plots out line segments with three or more points within.
 * @param argc
 * @param argv
 * @return 
 */
int fastRender(int argc, char *argv[]) {
    QApplication a(argc, argv);
    string filename = "input100.txt"; // open file
    ifstream input;
    input.open(filename);

    vector<Point> points; // the vector of points
    // read points from file
    int N;
    int x;
    int y;
    input >> N;
    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Fast Pattern Recognition");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();

    vector<std::pair<Point, double>> slopeFromStartToPoint;
    // iterate through all points and check slopes
    for (int i = 0 ; i < N ; ++i) {
        Point pivot = points[i];
        for(int z = 0; z < N; ++z){
            if(z != i){// Calculate and add all the slopes to a list with their representive point.
                pair<Point, double> pointAndSlope(points[z], pivot.slopeTo(points[z]));

                slopeFromStartToPoint.push_back(pointAndSlope);
            }
        }
        sort(slopeFromStartToPoint.begin(), slopeFromStartToPoint.end(), cmp); // Sort the point slope list from smallest to biggest.
        auto it = slopeFromStartToPoint.begin();
        if(it != slopeFromStartToPoint.end()){
            vector<Point> pointsOnALine;
            double slope = it->second;
            pointsOnALine.push_back(it->first);
            it++;
            while(it != slopeFromStartToPoint.end()){ // Render out all the lines that have three or more points within.
                it++;
                if(slope == it->second){
                    pointsOnALine.push_back(it->first);
                    if((int)pointsOnALine.size() >= 3){
                        render_line(scene, pivot, pointsOnALine.front());
                        pointsOnALine.clear();
                    }
                }
                else{
                    pointsOnALine.clear();
                }
                slope = it->second;
                pointsOnALine.push_back(it->first);
            }
        }
        slopeFromStartToPoint.clear(); // Clear the point slope list to give room for another pivot point.
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;
    return a.exec(); // start Qt event loop
}
