// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
// This is an implementation of the Volume algorithm for uncapacitated
// facility location problems. See the references
// F. Barahona, R. Anbil, "The Volume algorithm: producing primal solutions
// with a subgradient method," IBM report RC 21103, 1998.
// F. Barahona, F. Chudak, "Solving large scale uncapacitated facility
// location problems," IBM report RC 21515, 1999.

//#include <valarray>
#include <cstdio>
#include <set>
#include <list>
#include <vector>
#include <cmath>
#ifndef WIN32
#include <sys/times.h>
#endif

#include "ufl.hpp"

void UFL_read_data(const char* fname, UFL& data);

int main(int argc, char* argv[]) {

   // read in problem specific parameters and initialize data structures
   UFL_parms ufl_par("ufl.par");
   UFL  ufl_data;
   // read data
   UFL_read_data(ufl_par.fdata.c_str(), ufl_data);

   // create the VOL_problem from the parameter file
   VOL_problem volp("ufl.par");
   volp.psize = ufl_data.nloc + ufl_data.nloc*ufl_data.ncust;
   volp.dsize = ufl_data.ncust;
   bool ifdual = false;
   if (ufl_par.dualfile.length() > 0) {
     // read dual solution
      ifdual = true;
      VOL_dvector& dinit = volp.dsol;
      dinit.allocate(volp.dsize);
      // read from file
      FILE * file = fopen(ufl_par.dualfile.c_str(), "r");
      if (!file) {
	 printf("Failure to open file: %s\n ", ufl_par.dualfile.c_str());
	 abort();
      }
      const int dsize = volp.dsize;
      int idummy;
      for (int i = 0; i < dsize; ++i) {
	 fscanf(file, "%i%lf", &idummy, &dinit[i]);
      }
      fclose(file);
   }

#if 0
   // This would be the right place to set bounds on the dual variables
   // For UFL all the relaxed constraints are equalities, so the bounds are 
   // -/+inf, which happens to be the Volume default, so we don't have to do 
   // anything.
   // Otherwise the code to change the bounds would look something like this:

   // first the lower bounds to -inf, upper bounds to inf
   volp.dual_lb.allocate(volp.dsize);
   volp.dual_lb = -1e31;
   volp.dual_ub.allocate(volp.dsize);
   volp.dual_ub = 1e31;
   // now go through the relaxed constraints and change the lb of the ax >= b 
   // constrains to 0, and change the ub of the ax <= b constrains to 0.
   for (i = 0; i < volp.dsize; ++i) {
     if ("constraint i is '<=' ") {
       volp.dual_ub[i] = 0;
     }
     if ("constraint i is '>=' ") {
       volp.dual_lb[i] = 0;
     }
   }
#endif

#ifndef WIN32
   // start time measurement
   double t0;
   struct tms timearr; clock_t tres;
   tres = times(&timearr); 
   t0 = timearr.tms_utime; 
#endif

   // invoke volume algorithm
   if (volp.solve(ufl_data, ifdual) < 0) {
      printf("solve failed...\n");
   } else {
      // recompute the violation
      const int n = ufl_data.nloc;
      const int m = ufl_data.ncust;

      VOL_dvector v(volp.dsize);
      const VOL_dvector& psol = volp.psol;
      v = 1;
      int i,j,k=n;
      for (j = 0; j < n; ++j){
	for (i = 0; i < m; ++i) {
	  v[i] -= psol[k];
	  ++k;
	}
      }

      double vc = 0.0;
      for (i = 0; i < m; ++i)
         // MS Visual C++ has difficulty compiling 
         //   vc += std::abs(v[i]);
         // so just use standard fabs.
         vc += fabs(v[i]);
      vc /= m;
      printf(" Average violation of final solution: %f\n", vc);

      if (ufl_par.dual_savefile.length() > 0) {
	// save dual solution
	 FILE* file = fopen(ufl_par.dual_savefile.c_str(), "w");
	 const VOL_dvector& u = volp.dsol;
	 int n = u.size();
	 int i;
	 for (i = 0; i < n; ++i) {
	    fprintf(file, "%8i  %f\n", i+1, u[i]);
	 }
	 fclose(file);
      }

      // run a couple more heuristics
      double heur_val;
      for (i = 0; i < ufl_par.h_iter; ++i) {
	 heur_val = DBL_MAX;
	 ufl_data.heuristics(volp, psol, heur_val);
      }
      // save integer solution
      if (ufl_par.int_savefile.length() > 0) {
	 FILE* file = fopen(ufl_par.int_savefile.c_str(), "w");
	 const VOL_ivector& x = ufl_data.ix;
	 const int n = ufl_data.nloc;
	 const int m = ufl_data.ncust;
	 int i,j,k=n;
	 fprintf(file, "Open locations\n");
	 for (i = 0; i < n; ++i) {
	   if ( x[i]==1 )
	    fprintf(file, "%8i\n", i+1);
	 }
	 fprintf(file, "Assignment of customers\n");
	 for (i = 0; i < n; ++i) {
	   for (j = 0; j < m; ++j) {
	     if ( x[k]==1 ) 
	       fprintf(file, "customer %i  location %i\n", j+1, i+1);
	     ++k;
	   }
	 }
	 fclose(file);
      }
   }

   printf(" Best integer solution value: %f\n", ufl_data.icost);
   printf(" Lower bound: %f\n", volp.value);
   
#ifndef WIN32
   // end time measurement
   tres = times(&timearr);
   double t = (timearr.tms_utime-t0)/100.;
   printf(" Total Time: %f secs\n", t);
#endif

   return 0;
}





//############################################################################

//
void UFL_read_data(const char* fname, UFL& data) {

   FILE * file = fopen(fname, "r");
   if (!file) {
      printf("Failure to open ufl datafile: %s\n ", fname);
      abort();
   }


   VOL_dvector& fcost = data.fcost;
   VOL_dvector& dist = data.dist;

   int& nloc = data.nloc;
   int& ncust = data.ncust;
   int len;
#if 1
   char s[500];
   fgets(s, 500, file);
   len = strlen(s) - 1;
   if (s[len] == '\n')
      s[len] = 0;
   // read number of locations and number of customers
   sscanf(s,"%d%d",&nloc,&ncust);
    
   fcost.allocate(nloc);
   dist.allocate(nloc*ncust);
   double cost;
   int i,j,k;
   // read location costs
   for (i = 0; i < nloc; ++i) { 
     fgets(s, 500, file);
     len = strlen(s) - 1;
     if (s[len] == '\n')
	s[len] = 0;
     sscanf(s,"%lf",&cost);
     fcost[i]=cost;
   }
   dist=1.e7;
   while(fgets(s, 500, file)){
     len = strlen(s) - 1;
     if (s[len] == '\n')
	s[len] = 0;
     // read cost of serving a customer from a partucular location
     k=sscanf(s,"%d%d%lf",&i,&j,&cost);
     if(k!=3) break;
     if(i==-1)break;
     dist[(i-1)*ncust + j-1]=cost;
   }
#else
   fscanf(file, "%i%i", &ncust, &nloc);
   fcost.allocate(nloc);
   dist.allocate(nloc*ncust);
   int i,j;
   for ( j=0; j<ncust; ++j){
     for ( i=0; i<nloc; ++i){
       fscanf(file, "%f", &dist[i*ncust + j]);
     }
   }
   for ( i=0; i<nloc; ++i)
     fscanf(file, "%f", &fcost[i]);
#endif
   fclose(file);

   data.fix.allocate(nloc);
   data.fix = -1;
}

//############################################################################

//###### USER HOOKS
// compute reduced costs
int
UFL::compute_rc(const VOL_dvector& u, VOL_dvector& rc)
{
   int i,j,k=0;
   for ( i=0; i < nloc; i++){
     rc[i]=fcost[i];
     for (j = 0; j < ncust; ++j) {
       rc[nloc+k]= dist[k] - u[j];
       ++k;
     }
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
UFL::solve_subproblem(const VOL_dvector& u, const VOL_dvector& rc,
		      double& lcost, 
		      VOL_dvector& x, VOL_dvector& v, double& pcost)
{
   int i,j;

   lcost = 0.0;
   for (i = 0; i < ncust; ++i) {
      lcost += u[i];
      v[i]=1;
   }

   VOL_ivector sol(nloc + nloc*ncust);

   // produce a primal solution of the relaxed problem
   const double * rdist = rc.v + nloc;
   double sum;
   int k=0, k1=0;
   double value=0.;
   int xi;
   for ( i=0; i < nloc; ++i ) {
     sum=0.;
     for ( j=0; j < ncust; ++j ) {
       if ( rdist[k]<0. ) sum+=rdist[k];
       ++k;
     }
     if (fix[i]==0) xi=0;
     else 
       if (fix[i]==1) xi=1;
       else 
	 if ( fcost[i]+sum >= 0. ) xi=0;
	 else xi=1;
     sol[i]=xi;
     value+=(fcost[i]+sum)*xi;
     for ( j=0; j < ncust; ++j ) {
       if ( rdist[k1] < 0. ) sol[nloc+k1]=xi;
       else sol[nloc+k1]=0;
       ++k1;
     }
   }

   lcost += value;

   pcost = 0.0;
   x = 0.0;
   for (i = 0; i < nloc; ++i) {
     pcost += fcost[i] * sol[i];
     x[i] = sol[i];
   }

   k = 0;
   for ( i=0; i < nloc; i++){
     for ( j=0; j < ncust; j++){
       x[nloc+k]=sol[nloc+k];
       pcost+= dist[k]*sol[nloc+k];
       v[j]-=sol[nloc+k];
       ++k;
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
// We use randomized rounding. We look at x[i] as the probability
// of opening facility i.
int
UFL::heuristics(const VOL_problem& p,
		const VOL_dvector& x, double& new_icost)
{
   VOL_ivector nsol(nloc + nloc*ncust);
   nsol=0;
   int i,j;
   double r,value=0;
   for ( i=0; i < nloc; ++i){ // open or close facilities
#ifndef WIN32
     r=drand48();
#else
     r=rand();
#endif
     if (r < x[i]) nsol[i]=1;
     else nsol[i]=0;
     value+=fcost[i]*nsol[i];
   }
   double xmin;
   int imin;
   for ( j=0; j < ncust; ++j){ // assign customers to locations
     xmin=1.e31;
     imin=-1;
     for ( i=0; i < nloc; ++i){
       if ( nsol[i]==0 ) continue;
       if ( dist[i*ncust+j] < xmin ){ xmin=dist[i*ncust+j]; imin=i; }
     }
     value+=xmin;
     if ( imin >=0 ) nsol[nloc+imin*ncust+j]=1;
   }

   new_icost = value;
   if (value < icost) {
      icost = value;
      ix = nsol;
   }
   printf("int sol %f\n", new_icost);

   return 0;
}

