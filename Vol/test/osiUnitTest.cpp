// $Id$
// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

#include "CoinPragma.hpp"
#include "OsiConfig.h"

#include <cstdio>
#include <iostream>

#include "OsiUnitTests.hpp"
#include "OsiCuts.hpp"
#include "OsiRowCutDebugger.hpp"

#include "CoinError.hpp"

#include "OsiVolSolverInterface.hpp"

using namespace OsiUnitTest;

//----------------------------------------------------------------
// to see parameter list, call unitTest -usage
//----------------------------------------------------------------

int main (int argc, const char *argv[])

{
  bool exception = false;

  /*
  Start off with various bits of initialisation that don't really belong
  anywhere else.

  First off, synchronise C++ stream i/o with C stdio. This makes debugging
  output a bit more comprehensible. It still suffers from interleave of cout
  (stdout) and cerr (stderr), but -nobuf deals with that.
  */
  std::ios::sync_with_stdio() ;
  /*
  Suppress an popup window that Windows shows in response to a crash. See
  note at head of file.
  */
  WindowsErrorPopupBlocker();

  /*
  Process command line parameters.
  */
  std::map<std::string,std::string> parms ;
  if (processParameters(argc,argv,parms) == false)
    return (1);

  std::string mpsDir = parms["-mpsDir"] ;
  std::string netlibDir = parms["-netlibDir"] ;

  try {
    /*
      Test Osi{Row,Col}Cut routines.
     */
    {
      OsiVolSolverInterface volSi;
      testingMessage( "Testing OsiRowCut with OsiVolSolverInterface\n" );
      OsiRowCutUnitTest(&volSi,mpsDir);
    }
    {
      OsiVolSolverInterface volSi;
      testingMessage( "Testing OsiColCut with OsiVolSolverInterface\n" );
      OsiColCutUnitTest(&volSi,mpsDir);
    }

    /*
      Run the OsiVol class test, which calls the OsiSolverInterfaceCommonUnitTest.
     */
    testingMessage( "Testing OsiVolSolverInterface\n" );
    OsiVolSolverInterfaceUnitTest(mpsDir,netlibDir);
  } catch (CoinError& error) {
    std::cout.flush();
    std::cerr << "Caught CoinError exception: ";
    error.print(true);
    exception = true;
  }

  /*
    We're done. Report on the results.
  */
  std::cout.flush();
  outcomes.print();

  int nerrors;
  int nerrors_expected;
  outcomes.getCountBySeverity(TestOutcome::ERROR, nerrors, nerrors_expected);

  if (nerrors > nerrors_expected)
    std::cerr << "Tests completed with " << nerrors - nerrors_expected << " unexpected errors." << std::endl ;
  else
    std::cerr << "All tests completed successfully\n";

  return (nerrors - nerrors_expected) + (exception ? 1 : 0);
}
