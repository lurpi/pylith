#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
# Charles A. Williams, GNS Science
# Matthew G. Knepley, University of Chicago
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file tests/2d/quad4/TestRigidBody.py
##
## @brief Test suite for testing pylith with rigid body motion for
## large deformations in 2-D.

import numpy

from pylith.tests import run_pylith

from TestQuad4 import TestQuad4
from rigidbody_soln import AnalyticalSoln
from rigidbody_gendb import GenerateDB

# Local version of PyLithApp
from pylith.apps.PyLithApp import PyLithApp
class RigidBodyApp(PyLithApp):
  def __init__(self):
    PyLithApp.__init__(self, name="lgdeformrigidbody")
    return


class TestRigidBody(TestQuad4):
  """
  Test suite for testing pylith with 2-D rigid body motion.
  """

  def setUp(self):
    """
    Setup for test.
    """
    TestQuad4.setUp(self)
    run_pylith(RigidBodyApp, GenerateDB)
    self.outputRoot = "lgdeformrigidbody"
    self.soln = AnalyticalSoln()
    return


  def calcDisplacements(self, vertices):
    """
    Calculate displacement field given coordinates of vertices.
    """
    return self.soln.displacement(vertices)


  def calcStateVar(self, name, vertices, cells):
    """
    Calculate state variable.
    """
    ncells = self.mesh['ncells']
    pts = numpy.zeros( (ncells, 2), dtype=numpy.float64)
    if name == "total_strain":
      stateVar = self.soln.strain(pts)
    elif name == "stress":
      stateVar = self.soln.stress(pts)
    else:
      raise ValueError("Unknown state variable '%s'." % name)

    return stateVar


# ----------------------------------------------------------------------
if __name__ == '__main__':
  import unittest
  from TestLgDeformRigidBody import TestRigidBody as Tester

  suite = unittest.TestSuite()
  suite.addTest(unittest.makeSuite(Tester))
  unittest.TextTestRunner(verbosity=2).run(suite)


# End of file 
