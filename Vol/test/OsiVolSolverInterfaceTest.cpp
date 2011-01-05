// $Id$
// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>

#include "OsiVolSolverInterface.hpp"

//#############################################################################

//--------------------------------------------------------------------------
// test EKKsolution methods.
int
OsiVolSolverInterfaceUnitTest(const std::string & mpsDir, const std::string & netlibDir)
{

  // Do common solverInterface testing
  {
    OsiVolSolverInterface m;
    return OsiSolverInterfaceCommonUnitTest(&m, mpsDir,netlibDir);
  }

}
