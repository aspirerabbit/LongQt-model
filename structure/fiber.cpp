#include "fiber.h"
#include "tridag.h"

Fiber::Fiber(int size) {
    unsigned int i = static_cast<int>(nodes.size());
    nodes.resize(size, NULL);
    B.resize(size +1);
    for(;i < nodes.size(); i++) {
        nodes[i] = make_shared<Node>();
        B[i] = 0;
    }
    B[size] = 0;
}
Fiber::Fiber(const Fiber& o) {
    this->B = o.B;
    this->nodes.resize(o.nodes.size());
    for(unsigned int i = 0; i < o.nodes.size(); ++i) {
        this->nodes[i] = make_shared<Node>(*o.nodes[i]);
    }
}
Fiber::~Fiber() {}
//#############################################################
// Solve PDE for Vm along fiber using tridiagonal solver.
//#############################################################
void Fiber::updateVm(double& dt) {
    int i;
    int nn = static_cast<int>(nodes.size());
    if(nn <= 1) { return;}

	diffuseTop(0);
    nodes[0]->r = (B[1]*dt-2)*nodes[0]->cell->vOld-B[1]
		*dt*nodes[1]->cell->vOld+dt/nodes[0]->cell->Cm
		*(nodes[0]->cell->iTotold+nodes[0]->cell->iTot);
    for(i=0;i<nn;i++){
        nodes[i]->d1 = B[i]*dt;
        nodes[i]->d2 = -(B[i]*dt+B[i+1]*dt+2);
        nodes[i]->d3 = B[i+1]*dt;
        if(i>0&&i<(nn-1)) {
			diffuse(i);
            nodes[i]->r = -B[i]*dt*nodes[i-1]->cell->vOld+(B[i]*dt+B[i+1]*dt-2)
				*nodes[i]->cell->vOld-B[i+1]*dt*nodes[i+1]->cell->vOld+
				dt/nodes[i]->cell->Cm*
				(nodes[i]->cell->iTotold+nodes[i]->cell->iTot);
		}
    }
	diffuseBottom(nn-1);
    nodes[nn-1]->r = -B[nn-1]*dt*nodes[nn-2]->cell->vOld+(B[nn-1]*dt-2)*nodes[nn-1]->cell->vOld+dt/nodes[nn-1]->cell->Cm*(nodes[nn-1]->cell->iTotold+nodes[nn-1]->cell->iTot);

    tridag(nodes);

    for(i=0;i<nn;i++){
        nodes[i]->cell->iTotold=nodes[i]->cell->iTot;
        nodes[i]->cell->dVdt=(nodes[i]->vNew-nodes[i]->cell->vOld)/dt;
        //##### Conservation for multicellular fiber ############
        nodes[i]->dIax=-(nodes[i]->cell->dVdt+nodes[i]->cell->iTot);
        nodes[i]->cell->iKt=nodes[i]->cell->iKt+nodes[i]->dIax;
        nodes[i]->cell->setV(nodes[i]->vNew);
   }
}
shared_ptr<Node> Fiber::operator[](int pos) {
    if(0 <= pos&&pos < nodes.size()) {
        return this->nodes[pos];
    } else {
        return shared_ptr<Node>();
    }
}
shared_ptr<Node> Fiber::at(int pos) {
    return this->nodes.at(pos);
}

int Fiber::size() const{
    return nodes.size();
}
void Fiber::diffuseBottom(int node) {
	nodes[node]->cell->iTot-=
		B[node]*(nodes[node-1]->cell->vOld-nodes[node]->cell->vOld);
}
void Fiber::diffuseTop(int node) {
	nodes[node]->cell->iTot-=
		-B[node+1]*(nodes[node]->cell->vOld-nodes[node+1]->cell->vOld);
}
void Fiber::diffuse(int node) {
	nodes[node]->cell->iTot-=
		B[node]*(nodes[node-1]->cell->vOld-nodes[node]->cell->vOld)
		-B[node+1]*(nodes[node]->cell->vOld-nodes[node+1]->cell->vOld);
}
/*
//#############################################################
// Dynamic time step for one-dimensional fiber.
//#############################################################
int Fiber::tstep()
{
  int i,j;
  int vmflag=0;
  
  for(i=0;i<nn;i++){
     nodes[i]->cell->t=nodes[i]->cell->t+dt;
     nodes[i]->cell->dt=dt;
     if(nodes[i]->cell->dVdt>1.0||(nodes[i]->cell->t>(nodes[i]->cell->stimt-1.0)&&nodes[i]->cell->t<nodes[i]->cell->stimt))
	vmflag=2;
     else if(nodes[i]->cell->vOld>-50&&vmflag!=2)
        vmflag=1;
  }	
  
  if(vmflag==2)
      dt=dtmin;
  else if(vmflag==1)
      dt=dtmed;
  else
      dt=dtmax;
     
  if(nodes[0]->cell->t>tMax)
     return 0;
  else
     return 1;
}*/

Fiber::const_iterator Fiber::begin() const{
    return nodes.begin();
}

Fiber::const_iterator Fiber::end() const{
    return nodes.end();
}
