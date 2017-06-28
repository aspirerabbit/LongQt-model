/*
 * A container for cells that also keeps some of the information about the cells
 */
#ifndef NODE_H
#define NODE_H

#include "cell.h"
#include "cellutils.h"
#include <memory>

struct Node {
    Node() {};
	Node(const Node& other);
	~Node() {};

	void setCondConst(int X, double dx, CellUtils::Side s, bool perc = true, double val = 1);
//	void updateV(double dt);
    unique_ptr<Cell> cell = unique_ptr<Cell>(new Cell());
    double rd = 1.5; // gap junctional disk resistance.
	double condConst[4] = {0,0,0,0};
//## default value cannot be deterimined by constructor
    double dIax = 0;
	int np = 1; //number of cells in each node
	//can't change atm
//    double x = 0;
//    double y = 0;
    double d1 = 0; //off-diagonal for tridag solver
    double d2 = 0; //diagonal elements for tridag solver
    double d3 = 0; //off-diagonal for tridag solver
    double r = 0; //right side of eqn for tridag solver
    double vNew = 0; //vOld(t+1) for tridag solver
    string nodeType ="";

};
#endif
