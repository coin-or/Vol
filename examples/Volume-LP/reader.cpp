// $Id$
// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

#include <string>
#include <strstream>
#include <fstream>
#include <vector>
#include <map>
#include "lp.h"
#include "lpc.h"
#include "reader.h"

using namespace std;

int reader(const LP_parms &lp_par, VOL_lp *lp_pb)
{  
  VOL_lp &lp=*lp_pb;
  const int length=300;
  char line[length];  
  const double inf=1.e31;
  const double big=1.e20;
  int nrow=0, ncol=0;
  
  ifstream file(lp_par.fdata.c_str());
  if (!file){
     std::cout << " couldn't open " << lp_par.fdata << std::endl;
     abort();
  }
  // read ROWS section
  std::string s, objname;
  int ifobj=0;
  Rname rownames;
  while (1){
    file.getline(line,length,'\n'); 
    s=line; 
    if( s.find("ROWS")== 0 ) break;
  }
  while(file.getline(line,length,'\n'))
    {
      s=line;
      s+=" ";
      if( s.find("COLUMNS")!=std::string::npos ) break;
      istrstream ll(s.c_str());
      std::string sign;
      std::string name;
      ll >> sign >> name;
      if ( !ifobj && sign=="N" ){
	ifobj=1;
	objname=name;
	continue;
      }
      rownames.add(name, sign);
      ++nrow;
    }
  //---------------------------------------
  // read COLUMNS section
  lp.set_nrows(nrow);
  Cname colnames;
  std::cout << line << std::endl;
  std::string col;
  col="1";
  ncol=0;
  std::string row;
  double xx;
  int j;
  while(1)
    {
      file.getline(line,length,'\n');
      s=line;
      s+=" ";
      istrstream ll(s.c_str());
      std::string ss;
      ll >> ss;
      //std::cout << "--" << ss << "--\n";
      if(ss=="RHS")break;
      if( ss.find("MARK")!=std::string::npos ) continue;
      if( ss!=col ){
	lp.startcol();
	colnames.add(ss);
	col=ss;
	++ncol;
	if ( ncol % 50 == 0 ) std::cout << ncol << std::endl;
      }
      while ( ll >> row ){ 
	if ( row==objname ){
	  ll >> xx;
	  lp.addobj(xx);
	}
	else {
	  j=rownames.original_index(row);
	  ll >> xx;
	  lp.addel(j,xx); 
	}
      }
    }
  // read RHS
  std::cout << line << std::endl;
  int nrows=rownames.nrows;
  VOL_dvector rhs(nrows);
  rhs=0.0;
  std::string ss,rr;
  while(1)
    {
      file.getline(line,length,'\n');
      s=line;
      s+=" ";
      istrstream ll(s.c_str());
      ll >> ss;
      //if( ss=="BOUNDS" || ss=="ENDATA" )break;
      if ( ss.find("BOUNDS")!=std::string::npos || 
	   ss.find("ENDATA")!=std::string::npos ) break;
      while ( 1 ){
	if ( !(ll >> rr) ) break;
	if ( rr.length()==0 ) break;
	if ( !(ll >> xx) ) break;
	j=rownames.original_index(rr);
	rhs[j]=xx;
	//std::cout << icont++ << std::endl;
      }
    }
  for (j=0; j<rownames.nrows; ++j){
    const std::string& sign = rownames.sign[j];
    if ( sign=="E" ) lp.rhs(j,rhs[j],rhs[j]);
    else
      if ( sign=="L" ) lp.rhs(j,-inf,rhs[j]);
      else
	if ( sign=="G" ) lp.rhs(j,rhs[j],inf);
	else
	  if ( sign=="N" ) lp.rhs(j,-inf,big);
	  else {
	    std::cout << " Sign of const " << j << " is " 
		      << sign << std::endl;
	    abort();
	  }
    
  }
  // read BOUNDS
  std::cout << line << std::endl;
  lp.init_bounds(ncol);
  if(ss.find("ENDATA")==std::string::npos){
    std::string aux;
    while(1)
      {
	file.getline(line,length,'\n');
	s=line;
	s+=" ";
	istrstream ll(s.c_str());
	ll >> ss;
	if(ss=="ENDATA")break;
	ll >> aux >> col >> xx;
	j=colnames.original_index(col);
	if ( ss=="UP" ) lp.ub(j,xx);
	else
	  if ( ss=="LO" ) lp.lb(j,xx);
	  else
	    if ( ss=="FX" ){ lp.ub(j,xx); lp.lb(j,xx);}
	    else
	      if ( ss=="FR" ){ lp.ub(j,inf); lp.lb(j,-inf);}
	      else{
		std::cout << " Variable " << j << " " << ss << std::endl;
		abort();
	      }
      }
  }
  lp.finish_up();

  // change bounds for primal variables
  int i;
  //
  int cont=0,contm=0;
  if ( 1 ) {
    const double ub=lp_par.var_ub;
    std::cout << " \n Setting upper bounds to: " << ub 
	      << std::endl << std::endl;
    for ( i=0; i< lp.ncols; ++i){
      if ( lp.dupc[i]==lp.dloc[i] ) continue;
      if ( lp.dupc[i] > ub ) {
	lp.dupc[i]=ub;
	cont++;
      }
      if ( lp.dloc[i] < -ub ) {
	lp.dloc[i]=-ub;
	contm++;
      }
    }  
    std::cout << cont << " bounds have been changed to " << ub << std::endl;
    std::cout << contm << " bounds have been changed to " << -ub << std::endl;
  } 
  return 0;
}
