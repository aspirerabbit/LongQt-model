//################################################
// This header file contains protocol class
// declaration for simulation of excitable cell activity
// with a voltage clamp
//
// Copyright (C) 2015 Thomas J. Hund.
// Updated 07/2015
// Email thomas.hund@osumc.edu
//#################################################

#ifndef voltageClampProtocol_H
#define voltageClampProtocol_H

#include "protocol.h"

class voltageClamp : public Protocol {
  public:
    voltageClamp();
    voltageClamp(const voltageClamp& toCopy);
    voltageClamp* clone();
    voltageClamp& operator=(const voltageClamp& toCopy);

    bool runTrial() override;
  private:
    int clamp();
    void CCcopy(const voltageClamp& toCopy);

    double v1, v2, v3, v4, v5;
    double t1, t2, t3, t4, t5;

};
#endif
