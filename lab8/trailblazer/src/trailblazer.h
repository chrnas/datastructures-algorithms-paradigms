/*
 * TDDD86 Trailblazer
 * This file declares the functions you will write in this assignment.
 *
 * Please do not modify this provided file. Your turned-in files should work
 * with an unmodified version of all provided code files.
 *
 * Author: Marty Stepp
 * Slight modifications by Tommy Farnqvist
 */

#ifndef _trailblazer_h
#define _trailblazer_h

#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <pqueue.h>
#include "BasicGraph.h"

/**
 * @brief depthFirstSearch traverse graph according to depth first search algorithm and paints nodes during the steps of the algorithm.
 * @param graph The graph that are traversed.
 * @param start Start node of the traversal.
 * @param end End Node of the traversal, ends algorithm when traversed.
 * @return A vector with Nodes representing the shortest path according to depth first search algorithm.
 */
vector<Node*> depthFirstSearch(BasicGraph& graph, Node* start, Node* end);

/**
 * @brief breadthFirstSearch traverse graph according to breadth first search algorithm and paints nodes during the steps of the algorithm.
 * @param graph The graph that are traversed.
 * @param start Start node of the traversal.
 * @param end End Node of the traversal, ends algorithm when traversed.
 * @return A vector with Nodes representing the shortest path according to breadth first search algorithm.
 */
vector<Node*> breadthFirstSearch(BasicGraph& graph, Node* start, Node* end);

/**
 * @brief dijkstrasAlgorithm traverse graph according to djikstras algorithm and paints nodes during the steps of the algorithm.
 * @param graph The graph that are traversed.
 * @param start Start node of the traversal.
 * @param end End Node of the traversal, ends algorithm when traversed.
 * @return A vector with Nodes representing the shortest path according to djiktras algorithm.
 */
vector<Node*> dijkstrasAlgorithm(BasicGraph& graph, Node* start, Node* end);

/**
 * @brief aStar traverse graph according to A* algorithm and paints nodes during the steps of the algorithm.
 * @param graph The graph that are traversed.
 * @param start Start node of the traversal.
 * @param end End Node of the traversal, ends algorithm when traversed.
 * @return A vector with Nodes representing the shortest path according to A* algorithm.
 */
vector<Node*> aStar(BasicGraph& graph, Node* start, Node* end);

#endif
