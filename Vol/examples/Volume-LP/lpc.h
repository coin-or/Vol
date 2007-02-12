#ifndef __LPC_H__
#define __LPC_H__

#include <vector>
#include "VolVolume.hpp"

using std::vector;

class VOL_lp {
 public:
  int ncols, nrows, nels;
  int maxcols, nints;
  VOL_ivector mrow;
  VOL_ivector mcstrt;
  VOL_dvector dels;
  VOL_dvector dcost;
  VOL_dvector dloc;
  VOL_dvector dupc;
  VOL_dvector dlor;
  VOL_dvector dupr;
  VOL_ivector intnums;
  VOL_ivector check_col;
  vector<int> mr;
  vector<int> mc;
  vector<double> els;
  vector<double> cost;
  VOL_lp();
  ~VOL_lp(){ }
  void build_col(int row, double el);
  void rhs(int row, double lb, double ub);
  void finish_up();
  int n_cols(){ return ncols; }
  void set_nrows( const int n);
  void intcol(int j);
  void addobj( double xx);
  void addel(int row, double el);
  void startcol();
  void ub(const int i, const double x);
  void lb(const int i, const double x);
  void init_bounds( const int n);
};

#endif
