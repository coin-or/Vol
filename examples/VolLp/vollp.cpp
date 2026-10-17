// $Id$
// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

#include "VolVolume.hpp"
#include "CoinHelperFunctions.hpp"
#include "CoinPackedMatrix.hpp"
#include "CoinMpsIO.hpp"

//#############################################################################

class lpHook : public VOL_user_hooks {
private:
   lpHook(const lpHook&);
   lpHook& operator=(const lpHook&);
private:
   /// Pointer to dense vector of structural variable upper bounds
   double  *colupper_;
   /// Pointer to dense vector of structural variable lower bounds
   double  *collower_;
   /// Pointer to dense vector of objective coefficients
   double  *objcoeffs_;
   /// Pointer to dense vector of right hand sides
   double  *rhs_;
   /// Pointer to dense vector of senses
   char    *sense_;

   /// The problem matrix in a row ordered form
   CoinPackedMatrix rowMatrix_;
   /// The problem matrix in a column ordered form
   CoinPackedMatrix colMatrix_;

public:
   lpHook(const double* clb, const double* cub, const double* obj,
	  const double* rhs, const char* sense, const CoinPackedMatrix& mat);
   virtual ~lpHook();
   
public:
   // for all hooks: return value of -1 means that volume should quit
   /** compute reduced costs    
       @param u (IN) the dual variables
       @param rc (OUT) the reduced cost with respect to the dual values
   */
   virtual int compute_rc(const VOL_dvector& u, VOL_dvector& rc);

   /** Solve the subproblem for the subgradient step.
       @param dual (IN) the dual variables
       @param rc (IN) the reduced cost with respect to the dual values
       @param lcost (OUT) the lagrangean cost with respect to the dual values
       @param x (OUT) the primal result of solving the subproblem
       @param v (OUT) b-Ax for the relaxed constraints
       @param pcost (OUT) the primal objective value of <code>x</code>
   */
   virtual int solve_subproblem(const VOL_dvector& dual, const VOL_dvector& rc,
				double& lcost, VOL_dvector& x, VOL_dvector& v,
				double& pcost);
   /** Starting from the primal vector x, run a heuristic to produce
       an integer solution  
       @param x (IN) the primal vector
       @param heur_val (OUT) the value of the integer solution (return 
       <code>DBL_MAX</code> here if no feas sol was found 
   */
   virtual int heuristics(const VOL_problem& p, 
			  const VOL_dvector& x, double& heur_val) {
      return 0;
   }
};
 
//#############################################################################

lpHook::lpHook(const double* clb, const double* cub, const double* obj,
	       const double* rhs, const char* sense,
	       const CoinPackedMatrix& mat)
{
   const int colnum = mat.getNumCols();
   const int rownum = mat.getNumRows();

   colupper_ = new double[colnum];
   collower_ = new double[colnum];
   objcoeffs_ = new double[colnum];
   rhs_ = new double[rownum];
   sense_ = new char[rownum];

   std::copy(clb, clb + colnum, collower_);
   std::copy(cub, cub + colnum, colupper_);
   std::copy(obj, obj + colnum, objcoeffs_);
   std::copy(rhs, rhs + rownum, rhs_);
   std::copy(sense, sense + rownum, sense_);

   if (mat.isColOrdered()) {
      colMatrix_.copyOf(mat);
      rowMatrix_.reverseOrderedCopyOf(mat);
   } else {
      rowMatrix_.copyOf(mat);
      colMatrix_.reverseOrderedCopyOf(mat);
   }
}

//-----------------------------------------------------------------------------

lpHook::~lpHook()
{
   delete[] colupper_;
   delete[] collower_;
   delete[] objcoeffs_;
   delete[] rhs_;
   delete[] sense_;
}

//#############################################################################

int
lpHook::compute_rc(const VOL_dvector& u, VOL_dvector& rc)
{
   rowMatrix_.transposeTimes(u.v, rc.v);
   const int psize = rowMatrix_.getNumCols();

   for (int i = 0; i < psize; ++i)
      rc[i] = objcoeffs_[i] - rc[i];
   return 0;
}

//-----------------------------------------------------------------------------

int
lpHook::solve_subproblem(const VOL_dvector& dual, const VOL_dvector& rc,
			 double& lcost, VOL_dvector& x, VOL_dvector& v,
			 double& pcost)
{
   int i;
   const int psize = x.size();
   const int dsize = v.size();

   // compute the lagrangean solution corresponding to the reduced costs
   for (i = 0; i < psize; ++i)
      x[i] = (rc[i] >= 0.0) ? collower_[i] : colupper_[i];

   // compute the lagrangean value (rhs*dual + primal*rc)
   lcost = 0;
   for (i = 0; i < dsize; ++i)
      lcost += rhs_[i] * dual[i];
   for (i = 0; i < psize; ++i)
      lcost += x[i] * rc[i];

   // compute the rhs - lhs 
   colMatrix_.times(x.v, v.v);
   for (i = 0; i < dsize; ++i)
      v[i] = rhs_[i] - v[i];

   // compute the lagrangean primal objective
   pcost = 0;
   for (i = 0; i < psize; ++i)
      pcost += x[i] * objcoeffs_[i];

   return 0;
}

//#############################################################################

int
main(int argc, char * argv[])
{
   const char extension[4] = "mps";

   if (argc != 2) {
      printf("Usage: vollp <MPS file name>\n      (omitting the .mps)\n");
      exit(1);
   }

   CoinMpsIO mpsio;
   mpsio.readMps(argv[1], extension);

   printf("\n\n\n\n ============== Starting volume =================\n\n\n\n");

   VOL_problem volprob;
   const CoinPackedMatrix* mat = mpsio.getMatrixByCol();
   const int psize = mat->getNumCols();
   const int dsize = mat->getNumRows();
   char * sense = new char[dsize];
   memcpy(sense, mpsio.getRowSense(), dsize);

   // Set the lb/ub on the duals
   volprob.dsize = dsize;
   volprob.psize = psize;
   volprob.dual_lb.allocate(dsize);
   volprob.dual_ub.allocate(dsize);
   int i;
   for (i = 0; i < dsize; ++i) {
      switch (sense[i]) {
       case 'E':
	 volprob.dual_lb[i] = -1.0e31;
	 volprob.dual_ub[i] = 1.0e31;
	 break;
       case 'L':
	 volprob.dual_lb[i] = -1.0e31;
	 volprob.dual_ub[i] = 0.0;
	 break;
       case 'G':
	 volprob.dual_lb[i] = 0.0;
	 volprob.dual_ub[i] = 1.0e31;
	 break;
       default:
	 printf("Volume Algorithm can't work if there is a non ELG row\n");
	 abort();
      }
   }

   lpHook myHook(mpsio.getColLower(), mpsio.getColUpper(),
		 mpsio.getObjCoefficients(),
		 mpsio.getRightHandSide(), mpsio.getRowSense(), *mat);

   volprob.solve(myHook, false /* no warmstart */);

   //------------- extract the solution ---------------------------

   printf("Best lagrangean value: %f\n", volprob.value);

   double avg = 0;
   for (i = 0; i < dsize; ++i) {
      switch (sense[i]) {
       case 'E':
	 avg += CoinAbs(volprob.viol[i]);
	 break;
       case 'L':
	 if (volprob.viol[i] < 0)
	    avg +=  (-volprob.viol[i]);
	 break;
       case 'G':
	 if (volprob.viol[i] > 0)
	    avg +=  volprob.viol[i];
	 break;
      }
   }
      
   printf("Average primal constraint violation: %f\n", avg/dsize);

   // volprob.dsol contains the dual solution (dual feasible)
   // volprob.psol contains the primal solution
   //              (NOT necessarily primal feasible)

   return 0;
}
