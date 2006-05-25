#ifndef __NAMES_HPP__
#define __NAMES_HPP__

#include <map>
#include <vector>
#include <string>
#include <iostream>

/* The classes in this file are used for reading in an MPS file.
   Rname is used for storing the names and signs of the constraints.
   Cname is used for storing the names of the variables.
*/

using std::string;
using std::map;
using std::vector;
using std::cout;
using std::endl;

class LP_parms;
class Lp;

// The function that actually reads in the MPS file
int reader(const LP_parms &lp_par, Lp *lp_pb);

//#############################################################################

class Rname {
public:
   int nrows;
   map<string, int> name;
   vector<string> sign;
public:
   Rname() : nrows(0) {}
   ~Rname() {}
   int original_index(const string & Name) {
      map<string, int>::iterator j = name.find(Name);
      if ( j == name.end() ) {
	 cout << " name not found: " << Name << endl;
	 abort();
      }
      return j->second;
   }
   void add(const string &Name, const string &Sign) {
      map<string, int>::iterator j = name.find(Name);
      if ( j==name.end() ){
	 name[Name]=nrows++;
	 sign.push_back(Sign);
      } else {
	 cout << " duplicated row: " << Name << endl;
	 abort();
      }
   }
};

//#############################################################################

class Cname{
private:
   int ncols;
public:
   map<string, int> name;
public:
   Cname() : ncols(0) {}
   ~Cname() {}
   int original_index(const string & Name) {
      map<string, int>::iterator j = name.find(Name);
      if ( j == name.end() ) {
	 cout << " name not found: " << Name << endl;
	 abort();
      }
      return j->second;
   }
   void add(const string &Name) {
      map<string, int>::iterator j = name.find(Name);
      if ( j==name.end() ){
	 name[Name]=ncols++;
      } else {
	 cout << " duplicated row: " << Name << endl;
	 abort();
      }
   }
};

//#############################################################################

#endif
