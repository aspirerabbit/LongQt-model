#ifndef INEXCITABLECELL_H
#define INEXCITABLECELL_H

#include "cell.h"

class InexcitableCell : public Cell {
public:
    InexcitableCell();
    InexcitableCell(const InexcitableCell& toCopy);
    virtual ~InexcitableCell();

    virtual InexcitableCell* clone() override; //public copy function

    virtual void updateCurr();
    virtual void updateConc();

    virtual const char* type() const;

protected:
    virtual void Initialize();
};

#endif // INEXCITABLECELL_H
