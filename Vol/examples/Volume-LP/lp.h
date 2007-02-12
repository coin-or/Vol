#ifndef __LP_H__
#define __LP_H__

#include <cfloat>
#include <string>
#include <fstream>

#include "VolVolume.hpp"
#include "lpc.h"

using std::string;

//#############################################################################

// parameters controlled by the user
class LP_parms {
public:
  string fdata; // file with the data
  string dualfile; // file with an initial dual solution
  string dual_savefile; // file to save final dual solution
  string primal_savefile; // file to save primal integer solution
  int h_iter; // number of times that the primal heuristic will be run
  // after termination of the volume algorithm
  double var_ub; // upper bound for the variables
   
  LP_parms(const char* filename);
  ~LP_parms() {}
};

//#############################################################################

class LP_data_and_hook : public VOL_user_hooks { // original data for LP
public:
  VOL_lp lp_pb; // lp data
  VOL_dvector rhs; // right hand side
  VOL_ivector ix;   // best integer feasible solution so far
  double      icost;  // value of best integer feasible solution 
public:
  LP_data_and_hook() : icost(DBL_MAX) {}
  virtual ~LP_data_and_hook() {}  

 public:
   // for all hooks: return value of -1 means that volume should quit
   // compute reduced costs
   int compute_rc(const VOL_dvector& u, VOL_dvector& rc);
   // solve relaxed problem
   int solve_subproblem(const VOL_dvector& u, const VOL_dvector& rc,
			double& lcost, VOL_dvector& x, VOL_dvector&v,
			double& pcost);
  // primal heuristic
   // return DBL_MAX in heur_val if feas sol wasn't/was found 
   int heuristics(const VOL_problem& p, 
		  const VOL_dvector& x, double& heur_val);
};

//#############################################################################

#endif
