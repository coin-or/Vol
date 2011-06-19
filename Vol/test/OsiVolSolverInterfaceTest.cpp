// $Id$
// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

#include "OsiVolSolverInterface.hpp"

//--------------------------------------------------------------------------
void OsiVolSolverInterfaceUnitTest(const std::string & mpsDir, const std::string & netlibDir)
{
  // Do common solverInterface testing
  {
    OsiVolSolverInterface m;
    OsiSolverInterfaceCommonUnitTest(&m, mpsDir,netlibDir);
  }
}
