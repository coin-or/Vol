#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>
#include <cstdio>
#include "VolVolume.hpp"
#include "lpc.h"

using std::cout;
using std::endl;

VOL_lp::VOL_lp(): mrow(), mcstrt(),
dels(), dcost(), dloc(), dupc(), dlor(), dupr(), intnums()
{}
void VOL_lp::set_nrows(const int n)
{
  nels=0;
  nrows=n;
  ncols=0;
  nints=0;
  dlor.allocate(n);
  dupr.allocate(n);
  check_col.allocate(n);
}
void VOL_lp::intcol(int j){
  intnums[nints++]=j;
}
void VOL_lp::ub(const int i, const double x){
  dupc[i]=x;
}
void VOL_lp::lb(const int i, const double x){
  dloc[i]=x;
}
void VOL_lp::addobj( double xx){
  if ( cost[ncols-1]!= 0.0 ){
    cout << "duplicate element in objective for col " << ncols << endl;
    abort();
  }
  cost[ncols-1]=xx;
}
void VOL_lp::addel(int row, double el){
  if ( el == 0.0 ) return;
  if(row < 0 || row >= nrows){
    cout << " error in addel " << row << " " << nrows << endl;
    abort();
  }
  if ( check_col[row] > 0 ){
    cout << "duplicate element " << endl;
    abort();
  }
  els.push_back(el);
  mr.push_back(row);
  check_col[row]=1;
  ++nels;
}
void VOL_lp::startcol(){
  mc.push_back(nels);
  cost.push_back(0.0);
  check_col=0;
  ++ncols;
}
void VOL_lp::rhs(int row, double lb, double ub){
  if ( lb > ub ){
    cout << "Error in lp.rhs " << row << " " << lb << " "
	 << ub << endl;
    abort();
  }
  dlor[row]=lb;
  dupr[row]=ub;
}
void VOL_lp::finish_up(){
  mrow.allocate(nels);
  dels.allocate(nels);
  int i;
  for ( i=0; i<nels; ++i ){
    mrow[i]=mr[i];
    dels[i]=els[i];
  }

  els.resize(0);
  vector<double> tmp=els;
  els.swap(tmp);

  mr.resize(0);
  vector<int> tmp1=mr;
  mr.swap(tmp1);

  mcstrt.allocate(ncols+1);
  dcost.allocate(ncols);
  for ( int j=0; j<ncols; ++j){
    mcstrt[j]=mc[j];
    dcost[j]=cost[j];
  }

  mc.resize(0);
  vector<int> tmp2=mc;
  mc.swap(tmp2);

  cost.resize(0);
  vector<double> tmp3=cost;
  cost.swap(tmp3);

  mcstrt[ncols]=nels;
  // Fortran indexing
  //for (i=0; i < nels; i++) mrow[i]++;
  //for (i=0; i < nints; i++) intnums[i]++;
  //for (i=0; i <= ncols; i++) mcstrt[i]++;
  //

}
void VOL_lp::init_bounds( const int n ){
  dupc.allocate(n);
  dloc.allocate(n);
  dloc=0.0;
  dupc=1.e31;
}


