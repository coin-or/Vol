# Welcome to the COIN Vol Project

## Introduction

Vol (Volume Algorithm) is an open-source implementation of a subgradient
method that produces primal as well as dual solutions. The primal solution
comes from estimating the volumes below the faces of the dual problem. This is
an approximate method so the primal vector might have small infeasiblities
that are negligible in many practical settings. The original subgradient
algorithm produces only dual solutions.
          
## Background/Download

Vol is written in C++ and is released as open source code under the
[Eclipse Public License](http://www.opensource.org/licenses/eclipse-1.0)(EPL).
To get all of the dependencies and build the `Vol` package, do 

```
git clone https://github.com/coin-or/Vol 
Vol
git clone https://github.com/coin-or-tools/BuildTools
BuildTools/get.dependencies fetch
BuildTools/get.dependencies build
```
To test by building an application, do
```
cd build/Vol/examples/VolUfl
make
./ufl
```

## Included Projects

If you download the Vol package, you get
[these](https://github.com/coin-or/Vol/blob/master/Dependencies)
additional projects.

## Doxygen Documentation

If you have `Doxygen` available, you can build the html documentation by typing
```
make doxydoc
```
in the `Vol` directory. Then open the file `coin-Vol/doxydoc/html/index.html` with a browser.  
Note that this creates the documentation for the `Vol` 
package as a whole. If you
prefer to generate the documentation only for a subset 
of these projects, you can edit the file `Vol/doxydoc/doxygen.conf` to exclude directories  
(using the `EXCLUDE` variable, for example).

If `Doxygen` is not available, you can use the link to the {{{Vol}}} html documentation listed below.

## Documentation

 * [Overview of different directories](Vol/doc/volDoc.pdf)
 * [The Volume Algorithm: Producing Primal Solutions With a Subgradient Method](http://domino.watson.ibm.com/library/cyberdig.nsf/a3807c5b4823c53f85256561006324be/7a1b25774639540a852565be0070cfb5?OpenDocument)
 * [On Some Difficult Linear Programs Coming from Set Partitioning](http://domino.watson.ibm.com/library/cyberdig.nsf/a3807c5b4823c53f85256561006324be/53731ca97769f3838525672f0070dc2b?OpenDocument)
 * [Solving Large Scale Uncapacitated Facility Location Problems](http://domino.watson.ibm.com/library/cyberdig.nsf/a3807c5b4823c53f85256561006324be/08e1ac62bb877f9a852567b500500996?OpenDocument)
 * [Near-Optimal Solutions to Large Scale Facility Location Problems](http://domino.watson.ibm.com/library/cyberdig.nsf/a3807c5b4823c53f85256561006324be/215bca4e7e2406ec852568430076860c?OpenDocument)
 * [Solving Steiner Tree Problems in Graphs with Lagrangian Relaxation](http://domino.watson.ibm.com/library/cyberdig.nsf/a3807c5b4823c53f85256561006324be/4a61544906b57a6d8525696c0057f955?OpenDocument&Highlight=0,barahona)
 * [Vol html documentation](http://www.coin-or.org/Doxygen/Vol/hierarchy.html)
 * [COIN-OR Initiative](http://www.coin-or.org/)

## FAQ

### For what type of problems has VOL been used?

It has been tested with a variety of combinatorial problems like: Crew scheduling, Fleet assignment, Facility location, Steiner trees, Max-Cut, Quadratic knapsack.

### Can one solve a linear program with VOL?

One can get good and fast approximate solutions for combinatorial linear programs. These are LP's where all variables are between 0 and 1.

### Can one solve integer programs with VOL?
VOL gives bounds based on a relaxation of the IP. It also gives primal (fractional) solutions. With this information one can run a heuristic to produce an integer solution, or one can imbed VOL in a branch and bound code.

### Can one do "branch and cut" with VOL?
Yes, as an example, there is an implementation of a cutting plane algorithm for the Max-cut problem, that combines BCP and Vol. 

### Can one use VOL for column generation?
Yes. VOL has been very useful for accelerating column generation procedures, in particular for Crew Scheduling. The dual solutions given by VOL seem to provide faster convergence than if one uses dual solutions given by the Simplex method.

### What platforms does VOL run on?

VOL has been tested on:
 * AIX V4.3 using g++ V2.95.2
 * Linux using g++ V2.95.2.
 * Solaris (SunOS 5.6 and 5.8) using g++ V2.95.2
