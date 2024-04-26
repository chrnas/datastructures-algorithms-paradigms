/*
 * TDDD86 Trailbrazer
 * This cpp file includes the implementation of the algorithms: DepthFirstSearch, BreadthFirstSearch, DijkstrasAlgorithm and A-star.
 */

#include "costs.h"
#include "trailblazer.h"
using namespace std;

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    start->setColor(GREEN);
    start->visited = true;
    if(start == end){
        Vertex* pathNode = end;
        while(pathNode != NULL){
            path.push_back(pathNode);
            pathNode = pathNode->previous;
        }
        return path;
    }
    for(Vertex* neighbour : graph.getNeighbors(start)){
        if(!neighbour->visited){
            neighbour->previous = start;
            path = depthFirstSearch(graph, neighbour, end);
            if(path.empty())
            {
                neighbour->setColor(GRAY);
            }
            else{
                return path;
            }
        }
    }
    return path;
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    queue<Vertex*> queue;
    start->visited = true;
    queue.push(start);
    Vertex* current;
    while(!queue.empty()){
        current = queue.front();
        queue.pop();
        current->setColor(GREEN);
        if(current == end){
            Vertex* pathNode = end;
            while(pathNode != NULL){
                path.push_back(pathNode);
                pathNode = pathNode->previous;
            }
            return path;
        }
        for(Vertex* neighbour : graph.getNeighbors(current)){
            if(!neighbour->visited){
                neighbour->visited = true;
                neighbour->previous = current;
                queue.push(neighbour);
                neighbour->setColor(YELLOW);
            }
        }
    }
    return path;
}


vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    PriorityQueue<Vertex*> pqueue;
    pqueue.enqueue(start,0);
    start->visited = true;
    while(!pqueue.isEmpty()){
        Vertex* current = pqueue.dequeue();
        current->setColor(GREEN);
        if(current == end){
            Vertex* pathNode = end;
            while(pathNode != NULL){
                path.push_back(pathNode);
                pathNode = pathNode->previous;
            }
            return path;
        }
        for(Vertex* neighbour : graph.getNeighbors(current)){
            if(!neighbour->visited){
                neighbour->visited = true;
                neighbour->setColor(YELLOW);
                neighbour->previous = current;
                neighbour->cost = graph.getArc(current,neighbour)->cost + current->cost;
                pqueue.enqueue(neighbour, neighbour->cost);
            }
            else if(neighbour->cost > graph.getArc(current,neighbour)->cost + current->cost){
                neighbour->previous = current;
                neighbour->cost  = graph.getArc(current,neighbour)->cost + current->cost;
                pqueue.changePriority(neighbour, neighbour->cost);
            }
        }
    }
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    vector<Vertex*> path;
    PriorityQueue<Vertex*> pqueue;
    pqueue.enqueue(start,0);
    start->visited = true;
    while(!pqueue.isEmpty()){
        Vertex* current = pqueue.dequeue();
        current->setColor(GREEN);
        if(current == end){
            Vertex* pathNode = end;
            while(pathNode != NULL){
                path.push_back(pathNode);
                pathNode = pathNode->previous;
            }
            return path;
        }
        for(Vertex* neighbour : graph.getNeighbors(current)){
            if(!neighbour->visited){
                neighbour->visited = true;
                neighbour->setColor(YELLOW);
                neighbour->previous = current;
                neighbour->cost = graph.getArc(current,neighbour)->cost + current->cost + neighbour->heuristic(end);
                pqueue.enqueue(neighbour, neighbour->cost);
            }
            else if(neighbour->cost > graph.getArc(current,neighbour)->cost + current->cost + neighbour->heuristic(end)){
                neighbour->previous = current;
                neighbour->cost  = graph.getArc(current,neighbour)->cost + current->cost + neighbour->heuristic(end);
                pqueue.changePriority(neighbour, neighbour->cost);
            }
        }
    }
    return path;
}
