// 5/10/2016
//################################################
//protocol for a grid off cells
//class declarations
//################################################

#ifndef GRIDPROTOCOL_H
#define GRIDPROTOCOL_H

#include <set>
#include "currentClampProtocol.h"
#include "node.h"
#include "grid.h"

class GridProtocol : public CurrentClamp {
  public:
	enum Distribution {
		none = 0,
		normal = 1,
		lognormal = 2
	};
	struct IonChanParam {
		Distribution dist;
		double val[2]; 
		/*what these values are depends on dist
		 *  for none: val[0] = starting value, val[1] = increment amount
		 *  for normal & lognormal: val[0] = mean, val[1] = standard deviation
		 */
	};
	struct MIonChanParam : IonChanParam {
		map<pair<int,int>,double> cells; //map from x,y pos -> value
	};

  public:
    GridProtocol();
    GridProtocol(const GridProtocol& toCopy);
    GridProtocol* clone();
    GridProtocol& operator=(const GridProtocol& toCopy);

    bool runTrial() override;
    int stim();
    map<string, CellInitializer>& getCellMap();
    set<pair<int,int>>& getDataNodes();
    set<pair<int,int>>& getStimNodes();
    virtual bool writepars(string file);
    virtual int readpars(string file, set<string> varnames = {});
	virtual void setIonChanParams();
	virtual void writePvars(QXmlStreamWriter& xml);
	virtual void readPvars(QXmlStreamReader& xml);
	void handlePvars(QXmlStreamReader& xml);
	void handlePvar(QXmlStreamReader& xml);
	pair<pair<int,int>,double> handleCell(QXmlStreamReader& xml);

	map<string,MIonChanParam> new_pvars;
//    virtual bool addMeasure(Measure toInsert);

  private:
    map<string, CellInitializer> baseCellMap;
    void CCcopy(const GridProtocol& toCopy);
    set<pair<int,int>> dataNodes;
    set<pair<int,int>> stimNodes;
    string setToString(set<pair<int,int>>& nodes);
    set<pair<int,int>> stringToSet(string nodesList);
    Grid* grid;
    map<pair<int,int>,map<string,Measure>> realMeasures;
};
#endif
