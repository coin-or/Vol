// $Id$
// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

// This is an implementation of the Volume algorithm for LPs like
//    min cx
//    Ax >= b
//    l <= x <= u
// This works best when A is a 0-1 matrix, and x is bounded
// between 0 and 1
// See the references
// F. Barahona, R. Anbil, "The Volume algorithm: producing primal solutions
// with a subgradient method," Mathematical Programming, 87 (2000) 385-399.
// F. Barahona, R. Anbil, "On some difficult linear programs comming from
// set partitioning," IBM report RC 21410, 1999.

#include <cstdio>
#include <fstream>
#include <strstream>
#include <set>
#include <list>
#include <vector>
#include <cmath>
#include <sys/times.h>

#include "VolVolume.hpp"
#include "lp.h"
#include "lpc.h"
#include "reader.h"

using std::ifstream;
using std::ofstream;

void LP_read_data(const LP_parms &lp_par, LP_data_and_hook *lp_data);

int main(int argc, char* argv[]) {

   // read in problem specific parameters and initialize data structures
   LP_parms lp_par("lp.par");
   LP_data_and_hook  lp_data;
   // read data
   LP_read_data(lp_par, &lp_data);

   // create the VOL_problem from the parameter file
   VOL_problem volp("lp.par");
   volp.psize = lp_data.lp_pb.ncols;
   volp.dsize = lp_data.lp_pb.nrows;
   bool ifdual = false;
   if (lp_par.dualfile.length() > 0) {
     // read dual solution
      ifdual = true;
      VOL_dvector& dinit = volp.dsol;
      dinit.allocate(volp.dsize);
      // read from file
      ifstream file(lp_par.dualfile.c_str());
      const int dsize = volp.dsize;
      int idummy;
      for (int i = 0; i < dsize; ++i) {
	 file >> idummy >> dinit[i];
      }
   }

   // Set bounds on the dual variables

   // first the lower bounds to -inf, upper bounds to inf
   volp.dual_lb.allocate(volp.dsize);
   volp.dual_lb = -1e31;
   volp.dual_ub.allocate(volp.dsize);
   volp.dual_ub = 1e31;
   // now go through the relaxed constraints and change the lb of the ax >= b 
   // constrains to 0, and change the ub of the ax <= b constrains to 0.
   VOL_lp &lp_pb=lp_data.lp_pb;
   VOL_dvector &rhs=lp_data.rhs;
   rhs=lp_pb.dlor;
   const double bnd=1.e20;
   for (int i = 0; i < volp.dsize; ++i) {
     if ( lp_pb.dlor[i] < -bnd ) { // constraint i is '<=
       volp.dual_ub[i] = 0;
       rhs[i]=lp_pb.dupr[i];
     }
     if ( lp_pb.dupr[i] > bnd ) { // constraint i is '>=' 
       volp.dual_lb[i] = 0;
       rhs[i]=lp_pb.dlor[i];
     }
   }

   // start time measurement
   double t0;
   struct tms timearr; clock_t tres;
   tres = times(&timearr); 
   t0 = timearr.tms_utime; 

   // invoke volume algorithm
   if (volp.solve(lp_data, ifdual) < 0) {
      cout << "solve failed...\n";
   } else {
      // recompute the violation

     const int n = lp_data.lp_pb.ncols;
     const int m = lp_data.lp_pb.nrows;
     //     const VOL_dvector& rhs = lp_data.lp_pb.rhs;
     const VOL_ivector& mrow = lp_data.lp_pb.mrow;
     const VOL_ivector& mcstrt = lp_data.lp_pb.mcstrt;
     const VOL_dvector& dels = lp_data.lp_pb.dels;

     int i,j,k;

     VOL_dvector v(m);
     for (i = 0; i < m; ++i) {
       v[i] = rhs[i];
     }
     
     for (i = 0; i < n; ++i) {
       const double xx=volp.psol[i];
       const int k1=mcstrt[i];
       const int k2=mcstrt[i+1];
       for ( j=k1; j<k2; ++j ){
	 k=mrow[j];
	 v[k]-= dels[j]*xx;
       }
     }
     
     double vc = 0.0;
     for (i = 0; i < m; ++i){
       if ( ( v[i] > 0.0 && volp.dual_ub[i] == 0.0 ) ||
	    ( v[i] < 0.0 && volp.dual_lb[i] == 0.0 ) )
	 continue;
       vc += fabs(v[i]);
     }
     vc /= m;
     cout << " Average violation of final solution: " << vc << endl;
     
     if (lp_par.dual_savefile.length() > 0) {
       // save dual solution
       ofstream file(lp_par.dual_savefile.c_str());
       const VOL_dvector& u = volp.dsol;
       int n = u.size();
       int i;
       for (i = 0; i < n; ++i) {
	 file << i+1 << " " << u[i] << endl;
       }
     }
     if (lp_par.primal_savefile.length() > 0) {
       // save primal solution
       ofstream file(lp_par.primal_savefile.c_str());
       const VOL_dvector& x = volp.psol;
       int n = x.size();
       int i;
       for (i = 0; i < n; ++i) {
	 if ( x[i] > 1.e-8 )
	   file << i+1 << " " << x[i] << endl;
       }
     }
     // run a couple more heuristics
     double heur_val;
     for (i = 0; i < lp_par.h_iter; ++i) {
       heur_val = DBL_MAX;
       lp_data.heuristics(volp, volp.psol, heur_val);
     }
   }
   
   
   // end time measurement
   tres = times(&timearr);
   double t = (timearr.tms_utime-t0)/100.;
   cout << " Total Time: " << t << " secs \n";
   
   return 0;
}





//############################################################################

//
void LP_read_data(const LP_parms &lp_par, LP_data_and_hook * data)
{
   VOL_lp& lp_pb = (*data).lp_pb;
   reader(lp_par,&lp_pb);
   const int m=lp_pb.nrows;
   (*data).rhs.allocate(m);

}



//############################################################################

//###### USER HOOKS
// compute reduced costs
int
LP_data_and_hook::compute_rc(const VOL_dvector& u, VOL_dvector& rc)
{
   const int n = lp_pb.ncols;
   const VOL_dvector& dcost = lp_pb.dcost;
   const VOL_ivector& mcstrt = lp_pb.mcstrt;
   const VOL_ivector& mrow = lp_pb.mrow;
   const VOL_dvector& dels = lp_pb.dels;

   int i,k=0;
   double redcost;
   for ( i=0; i < n; i++){
     redcost=dcost[i];
     const int k1=mcstrt[i];
     const int k2=mcstrt[i+1];
     double *dd=dels.v+k1;
     double *d2=dels.v+k2;
     int *mm=mrow.v+k1;
     while ( dd != d2 ) {
       k = *mm;
       redcost -= u[k] * (*dd);
       ++dd; ++mm;
     }
     rc[i]=redcost;
   }
   return 0;
}

// IN: dual vector u
// OUT: primal solution to the Lagrangian subproblem (x)
//      optimal value of Lagrangian subproblem (lcost)
//      v = difference between the rhs and lhs when substituting
//                  x into the relaxed constraints (v)
//      objective value of x substituted into the original problem (pcost)
//      xrc
// return value: -1 (volume should quit) 0 ow

int 
LP_data_and_hook::solve_subproblem(const VOL_dvector& u, const VOL_dvector& rc,
				   double& lcost, VOL_dvector& x,
				   VOL_dvector& v, double& pcost)
{
   const VOL_dvector& dcost = lp_pb.dcost;
   const int n = lp_pb.ncols;
   const int m = lp_pb.nrows;
   const VOL_ivector& mrow = lp_pb.mrow;
   const VOL_ivector& mcstrt = lp_pb.mcstrt;
   const VOL_dvector& dels = lp_pb.dels;
   const VOL_dvector& dloc = lp_pb.dloc;
   const VOL_dvector& dupc = lp_pb.dupc;

   int i,k;

   lcost = 0.0;
   for (i = 0; i < m; ++i) {
      lcost += u[i] * rhs[i];
      v[i] = rhs[i];
   }

   pcost = 0.0;
   for (i = 0; i < n; ++i) {
     if ( rc[i] >= 0.0 ) x[i]=dloc[i];
     else x[i]=dupc[i];
     const double xx=x[i];
     lcost += rc[i]*xx;
     pcost += dcost[i] * xx;
     const int k1=mcstrt[i];
     const int k2=mcstrt[i+1];
     double *dd=dels.v+k1;
     double *d2=dels.v+k2;
     int *mm=mrow.v+k1;
     while ( dd != d2 ) {
       k= *mm;
       v[k]-= (*dd)*xx;
       ++mm; ++dd;
     }
   }
   return 0;
}


// IN:  fractional primal solution (x),
//      best feasible soln value so far (icost)
// OUT: integral primal solution (ix) if better than best so far
//      and primal value (icost)
// returns -1 if Volume should stop, 0/1 if feasible solution wasn't/was
//         found.

int
LP_data_and_hook::heuristics(const VOL_problem& p,
			     const VOL_dvector& x, double& icost)
{
  // no heuristic at this moment

   return 0;
}



//#############################################################################
// Constructor of LP_parms
//#############################################################################

// reading parameters specific to LP
LP_parms::LP_parms(const char *filename) :
  fdata(""),
  h_iter(10)
{
  char s[100];
  ifstream file(filename);
  if (!file) {
    cout << "Failure to open file\n";
    exit(2);
  }

  string ss;
  while (1) {
    file.getline(s, 100, '\n');
    string ss;
    ss = s;

    if (ss.find("fdata") == 0) {
      int j = ss.find("=");
      int j1 = ss.length() - j + 1;
      fdata = ss.substr(j+1, j1);

    } else if (ss.find("dualfile") == 0) {
      int j = ss.find("=");
      int j1 = ss.length() - j + 1;
      dualfile = ss.substr(j+1, j1);

    } else if (ss.find("dual_savefile") == 0) {
      int j = ss.find("=");
      int j1 = ss.length() - j + 1;
      dual_savefile = ss.substr(j+1, j1);

    } else if (ss.find("primal_savefile") == 0) {
      int j = ss.find("=");
      int j1 = ss.length() - j + 1;
      primal_savefile = ss.substr(j+1, j1);

    } else if (ss.find("h_iter") == 0) {
      int i = ss.find("=");
      h_iter = atoi(&s[i+1]);
    } else if (ss.find("var_ub") == 0) {
      int i = ss.find("=");
      var_ub = atof(&s[i+1]);
    }

    if (file.eof()) break;
  }
  file.close();
}

