// 5/10/2016
//################################################
//cell type for a grid, used by grid protocol to
// run a simulaiton on a grid of cells
// class declarations
//################################################

#ifndef GRIDCELL_H
#define GRIDCELL_H

#include <cellGrid.h>

class gridCell: public Cell {
  public:
    gridCell();
    gridCell(gridCell& toCopy);
    ~gridCell();

    void Initialize();
    gridCell* clone();

    virtual void updateConc();
    virtual void updateCurr();
    virtual double updateV();
    virtual int externalStim(double stimval); //stimulates every cell
    virtual double tstep(double stimt);

//cell io functions
    virtual bool setOutputfileConstants(string filename);
    virtual bool setOuputfileVariables(string filename);
    virtual bool setConstantSelection(set<string> new_selection);
    virtual bool setVariableSelection(set<string> new_selection);
    virtual set<string> getConstantSelection();
    virtual set<string> getVariableSelection();
    virtual void writeConstants();
    virtual void writeVariables();

  private:
    Grid grid;
    char buffer[500];
    double dx; //0.01
    double dy;
    int np; //1
    int tcount;//0
};
#endif