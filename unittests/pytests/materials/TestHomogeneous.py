#!/usr/bin/env python
#
# ======================================================================
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# {LicenseText}
#
# ======================================================================
#

## @file unittests/pytests/materials/TestHomogeneous.py

## @brief Unit testing of Homogenous object.

import unittest

# ----------------------------------------------------------------------
class TestHomogeneous(unittest.TestCase):
  """
  Unit testing of Homogeneous object.
  """

  def test_constructor(self):
    """
    Test constructor.
    """
    from pylith.materials.Homogeneous import Homogeneous
    materials = Homogeneous()
    return


  def test_configure(self):
    """
    Test _configure().
    """
    from pylith.materials.Homogeneous import Homogeneous
    materials = Homogeneous()
    from pylith.materials.ElasticIsotropic3D import ElasticIsotropic3D
    materials.inventory.material = ElasticIsotropic3D()
    materials._configure()
    self.assertEqual(1, len(materials.bin))
    return


# End of file 
