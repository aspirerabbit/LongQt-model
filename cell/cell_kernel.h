//################################################
// This header file contains class definition for
// simulation of excitable cell activity. 
//
// Copyright (C) 2011 Thomas J. Hund.
// Updated 11/21/2012
// Email thomas.hund@osumc.edu
//#################################################

#ifndef MODEL_KERNEL
#define MODEL_KERNEL

#include <cmath>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <memory>

#include "iobase.h"

using namespace std;


//######################################################
//Define class for parent cell.
//######################################################
class CellKernel : public std::enable_shared_from_this<CellKernel>
{
  public:
    CellKernel();
    CellKernel(const CellKernel& toCopy);
    virtual ~CellKernel(); 
    
    virtual CellKernel* clone() = 0; //public copy function
  //##### Declare class functions ##############
    virtual double updateV();
    virtual void setV(double v);
    virtual void updateCurr() = 0;
    virtual void updateConc() = 0;
    virtual double tstep(double stimt);
    virtual int externalStim(double stimval);

    //##### Declare class variables ##############
    double vOld;    // Transmembrane potential
    double vNew;
    double t;       // time, ms
    double dt;	  // Time increment
    double iNat;  // Total transmembrane sodium current.
    double iKt;  // Total transmembrane potassium current.
    double iCat;  // Total transmembrane calcium current.
    double iTot;  // Total transmembrane current.
    double iTotold;  // Total transmembrane current.
    
    //##### Declare class params ##############
    double Cm;    // Specific membrane capacitance, uF/cm^2
    double Vcell;  // Total cell Volume, uL.
    double Vmyo;  //  Myoplasmic volume, uL.
    double AGeo;   // Geometric cell surface area.
    double ACap;   // Capacitive cell surface area.
    double Rcg;    // Ratio of capacitive to geometric area.
    double cellRadius, cellLength;
    double dVdt;
    double dVdtmax;
    double Rmyo = 150; //Myoplasmic resistivity.
    
    double dtmin,dtmed,dtmax,dvcut;
    double apTime;
    
    double RGAS;
    double TEMP;
    double FDAY;
    
    //##### Declare maps for vars/params ##############
    map<string, double*> vars;  // map of state vars
    map<string, double*> pars;  // map of params
    virtual double var(string name);
    virtual bool setVar(string name, double val);
    virtual double par(string name);
    virtual bool setPar(string name, double val);
    virtual set<string> getVariables();
    virtual set<string> getConstants();
    virtual const char* type() const = 0;
    void reset();

protected:
    void copyVarPar(const CellKernel& toCopy);
    virtual void Initialize();
private:
    void mkmap();
};
#endif
