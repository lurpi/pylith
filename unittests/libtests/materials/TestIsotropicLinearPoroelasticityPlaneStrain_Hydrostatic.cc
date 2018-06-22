// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
// Charles A. Williams, GNS Science
// Matthew G. Knepley, University of Chicago
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2015 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestIsotropicLinearPoroelasticityPlaneStrain.hh" // Implementation of cases

#include "pylith/materials/IsotropicLinearPoroelasticityPlaneStrain.hh" // USES IsotropicLinearElasticityPlaneStrain
#include "pylith/topology/Field.hh" // USES pylith::topology::Field::Discretization
#include "spatialdata/spatialdb/UserFunctionDB.hh" // USES UserFunctionDB
#include "spatialdata/spatialdb/GravityField.hh" // USES GravityField
#include "spatialdata/units/Nondimensional.hh" // USES Nondimensional

// forward declarations
namespace pylith {
    namespace materials {
        class TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic;

        class TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP1;
        class TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP2;
        class TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP3;
        class TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP4;

        class TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ1;
        class TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ2;
        class TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ3;
        class TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ4;

    } // materials
} // pylith

// ----------------------------------------------------------------------
class pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic :
    public pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain {

    /// Spatial database user functions for auxiiliary subfields (includes derived fields).
    static const double SMALL;
    static const double GACC;
    static const double YMAX;

    // Density
    static double density(const double x,
                          const double y) {
        return 2500.0;
    } // density
    static const char* density_units(void) {
        return "kg/m**3";
    } // density_units

    // Vs
    static double vs(const double x,
                     const double y) {
        return 3000.0;
    } // vs
    static const char* vs_units(void) {
        return "m/s";
    } // vs_units

    // Vp
    static double vp(const double x,
                     const double y) {
        return sqrt(3.0)*vs(x,y); // 5196 m/s
    } // vp
    static const char* vp_units(void) {
        return "m/s";
    } // vp_units

    // shear modulus
    static double shearModulus(const double x,
                               const double y) {
        return density(x,y) * vs(x,y) * vs(x,y); // 22.5E+09 Pa
    } // shearModulus
    static const char* shearModulus_units(void) {
        return "Pa";
    } // shearModulus_units

    // bulk modulus
    static double bulkModulus(const double x,
                              const double y) {
        return density(x,y)*(vp(x,y)*vp(x,y) - 4.0/3.0*vs(x,y)*vs(x,y)); // 37.5E+09 Pa
    } // bulkModulus
    static const char* bulkModulus_units(void) {
        return "Pa";
    } // bulkModulus_units
    
    // isotropic permeability
    static double isotropicPermeability(const double x,
                              const double y) {
        return 10.0*pow(10,-13); // 1 Darcy
    } // isotropicPermeability
    static const char* isotropicPermeability_units(void) {
        return "m**2";
    } // isotropicPermeability_units
    
    // porosity
    static double porosity(const double x,
                              const double y) {
        return 0.1;
    } // porosity
    static const char* porosity_units(void) {
        return "none";
    } // porosity_units

    // fluid density
    static double fluidDensity(const double x,
                              const double y) {
        return 1000.0;
    } // fluidDensity
    static const char* fluidDensity_units(void) {
        return "kg/m**3";
    } // fluidDensity_units    
    
    // fluid viscosity
    static double fluidViscosity(const double x,
                              const double y) {
        return 10.0*pow(10,-4);
    } // fluidViscosity
    static const char* fluidViscosity_units(void) {
        return "Pa*s";
    } // fluidViscosity_units  
    
    // fluid bulk modulus
    static double fluidBulkModulus(const double x,
                              const double y) {
        return 2.0*pow(10,9);
    } // fluidBulkModulus
    static const char* fluidBulkModulus_units(void) {
        return "Pa";
    } // fluidBulkModulus_units
    
    // biot coefficient
    static double biotCoefficient(const double x,
                              const double y) {
        return 1;
    } // biotCoefficient
    static const char* biotCoefficient_units(void) {
        return "none";
    } // biotCoefficient_units        

    // Spatial database user functions for solution subfields.
    
    // source density
    static double sourceDensity(const double x,
                                      const double y) {
        return -density(x,y)*0.0;   // may need to be changed, will q be in different direction?
    } // sourceDensity
    static const char* sourceDensity_units(void) {
        return "m**3/s";
    } // sourceDensity_units
    
    // body force
    static double bodyForce(const double x,
                                      const double y) {
        return -density(x,y)*0.0;   // may need to be changed,  be in different direction?
    } // body force
    static const char* bodyForce_units(void) {
        return "Pa*m*m";
    } // bodyForce_units
    

    static double referenceMeanStress(const double x,
                                      const double y) {
        return -density(x,y) * GACC * (YMAX-y);
    } // referenceMeanStress
    static double referenceShearStress(const double x,
                                       const double y) {
        return 0.0;
    } // referenceShearStress
    static const char* stress_units(void) {
        return "Pa";
    } // stress_units
    static double referenceStrain(const double x,
                                  const double y) {
        return 0.0;
    } // referencStrain
    static const char* strain_units(void) {
        return "none";
    } // strain_units

    static double gravityAcc_x(const double x,
                               const double y) {
        return 0.0;
    } // gravityAcc_x
    static double gravityAcc_y(const double x,
                               const double y) {
        return -GACC;
    } // gravityAcc_y
    static const char* acc_units(void) {
        return "m/s**2";
    } // acc_units


    // Displacement
    static double disp_x(const double x,
                         const double y) {
        return 0.0;
    } // disp_x
    static double disp_y(const double x,
                         const double y) {
        return 0.0;
    } // disp_y
    static const char* disp_units(void) {
        return "m";
    } // disp_units

    static double disp_dot_x(const double x,
                             const double y) {
        return 0.0;
    } // disp_dot_x
    static double disp_dot_y(const double x,
                             const double y) {
        return 0.0;
    } // disp_dot_y
    static const char* disp_dot_units(void) {
        return "m/s";
    } // disp_dot_units


    // Displacement + perturbation
    static double disp_perturb_x(const double x,
                                 const double y) {
        return disp_x(x, y) + SMALL;
    } // disp_perturb_x
    static double disp_perturb_y(const double x,
                                 const double y) {
        return disp_y(x, y) + SMALL;
    } // disp_perturb_y
    
    // Pressure
    static double poro_pres(const double x,
                         const double y) {
        return 0.0;
    } // poro_pres
    static const char* poro_pres_units(void) {
        return "Pa";
    } // poro_pres

    static double poro_pres_dot(const double x,
                             const double y) {
        return 0.0;
    } // poro_pres_dot
    static const char* poro_pres_dot_units(void) {
        return "Pa/s";
    } // poro_pres_dot_units
    
    // poro_pres + perturbation
    static double poro_pres_perturb(const double x,
                                 const double y) {
        return poro_pres(x, y) + SMALL;
    } // poro_pres_perturb
 
    // trace strain
    static double trace_strain(const double x,
                         const double y) {
        return 0.0;
    } // trace_strain
    static const char* trace_strain_units(void) {
        return "none";
    } // trace_strain

    static double trace_strain_dot(const double x,
                             const double y) {
        return 0.0;
    } // trace_strain_dot
    static const char* trace_strain_dot_units(void) {
        return "1/s";
    } // trace_strain_dot_units

    // trace_strain + perturbation
    static double trace_strain_perturb(const double x,
                                 const double y) {
        return trace_strain(x, y) + SMALL;
    } // trace_strain_perturb


protected:

    void setUp(void) {
        TestIsotropicLinearPoroelasticityPlaneStrain::setUp();
        _mydata = new TestIsotropicLinearPoroelasticityPlaneStrain_Data(); CPPUNIT_ASSERT(_mydata);

        // dimension set in base class.
        // meshFilename set in derived class.
        _mydata->boundaryLabel = "boundary";

        CPPUNIT_ASSERT(_mydata->normalizer);
        _mydata->normalizer->lengthScale(1.0e+03);
        _mydata->normalizer->timeScale(2.0);
        _mydata->normalizer->pressureScale(2.25e+10);
        _mydata->normalizer->computeDensityScale();

        delete _mydata->gravityField; _mydata->gravityField = new spatialdata::spatialdb::GravityField();
        _mydata->gravityField->gravityDir(0.0, -1.0, 0.0);
        _mydata->gravityField->gravityAcc(GACC);

        _mydata->t = 1.0;
        _mydata->dt = 0.05;
        _mydata->tshift = 1.0 / _mydata->dt;

        // solnDiscretizations set in derived class.

        _mydata->numAuxSubfields = 14;
        static const char* _auxSubfields[14] = {"density", "shear_modulus", "bulk_modulus", "isotropicPermeability", 
        "porosity", "fluidDensity", "fluidViscosity", "fluidBulkModulus", "biotCoefficient", "gravitational_acceleration", 
         "body_force","source_density", "reference_stress", "reference_strain" };
        _mydata->auxSubfields = _auxSubfields;
        static const pylith::topology::Field::Discretization _auxDiscretizations[14] = {
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // density
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // shear_modulus
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // bulk_modulus
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // isotropicPermeability
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // porosity
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluidDensity
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluidViscosity
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluidBulkModulus
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // biotCoefficient
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // gravitational_acceleration
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // body_force
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // source_density
            {1, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_stress
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_strain
        };
        _mydata->auxDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_auxDiscretizations);

        CPPUNIT_ASSERT(_mydata->auxDB);
        _mydata->auxDB->addValue("density", density, density_units());
        _mydata->auxDB->addValue("vp", vp, vp_units());
        _mydata->auxDB->addValue("vs", vs, vs_units());
        _mydata->auxDB->addValue("shear_modulus", shearModulus, shearModulus_units());
        _mydata->auxDB->addValue("bulk_modulus", bulkModulus, bulkModulus_units());
        _mydata->auxDB->addValue("isotropicPermeability", isotropicPermeability, isotropicPermeability_units());
        _mydata->auxDB->addValue("porosity", porosity, porosity_units());
        _mydata->auxDB->addValue("fluidDensity", fluidDensity, fluidDensity_units());
        _mydata->auxDB->addValue("fluidViscosity", fluidViscosity, fluidViscosity_units());
        _mydata->auxDB->addValue("fluidBulkModulus", fluidBulkModulus, fluidBulkModulus_units());
        _mydata->auxDB->addValue("biotCoefficient", biotCoefficient, biotCoefficient_units());        
        _mydata->auxDB->addValue("reference_stress_xx", referenceMeanStress, stress_units());
        _mydata->auxDB->addValue("reference_stress_yy", referenceMeanStress, stress_units());
        _mydata->auxDB->addValue("reference_stress_zz", referenceMeanStress, stress_units());
        _mydata->auxDB->addValue("reference_stress_xy", referenceShearStress, stress_units());
        _mydata->auxDB->addValue("reference_strain_xx", referenceStrain, strain_units());
        _mydata->auxDB->addValue("reference_strain_yy", referenceStrain, strain_units());
        _mydata->auxDB->addValue("reference_strain_zz", referenceStrain, strain_units());
        _mydata->auxDB->addValue("reference_strain_xy", referenceStrain, strain_units());
        _mydata->auxDB->addValue("gravitational_acceleration_x", gravityAcc_x, acc_units()); // test of subfield.
        _mydata->auxDB->addValue("gravitational_acceleration_y", gravityAcc_y, acc_units());
        _mydata->auxDB->addValue("source_density", sourceDensity, sourceDensity_units()); // test of subfield.
        _mydata->auxDB->addValue("body_force", bodyForce, bodyForce_units());

        CPPUNIT_ASSERT(_mydata->solnDB);
        _mydata->solnDB->addValue("displacement_x", disp_x, disp_units());
        _mydata->solnDB->addValue("displacement_y", disp_y, disp_units());
        _mydata->solnDB->addValue("displacement_dot_x", disp_dot_x, disp_dot_units());
        _mydata->solnDB->addValue("displacement_dot_y", disp_dot_y, disp_dot_units());        
        _mydata->solnDB->addValue("poro_pres", poro_pres, poro_pres_units());
        _mydata->solnDB->addValue("poro_pres_dot", poro_pres_dot, poro_pres_dot_units());
        _mydata->solnDB->addValue("trace_strain", trace_strain, trace_strain_units());
        _mydata->solnDB->addValue("trace_strain_dot", trace_strain_dot, trace_strain_dot_units());

        CPPUNIT_ASSERT(_mydata->perturbDB);
        _mydata->perturbDB->addValue("displacement_x", disp_perturb_x, disp_units());
        _mydata->perturbDB->addValue("displacement_y", disp_perturb_y, disp_units());
        _mydata->perturbDB->addValue("displacement_dot_x", disp_dot_x, disp_dot_units());
        _mydata->perturbDB->addValue("displacement_dot_y", disp_dot_y, disp_dot_units());
        _mydata->perturbDB->addValue("poro_pres", poro_pres_perturb, poro_pres_units());
        _mydata->perturbDB->addValue("poro_pres_dot", poro_pres_dot, poro_pres_dot_units());
        _mydata->perturbDB->addValue("trace_strain", trace_strain_perturb, trace_strain_units());
        _mydata->perturbDB->addValue("trace_strain_dot", trace_strain_dot, trace_strain_dot_units());

        CPPUNIT_ASSERT(_mymaterial);
        _mymaterial->useInertia(false);
        _mymaterial->useBodyForce(false);
        _mymaterial->useReferenceState(true);

        _mymaterial->label("Isotropic Linear Poroelasticity Plane Strain");
        _mymaterial->id(24);
    } // setUp

}; // TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic
const double pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic::SMALL = 0.1;
const double pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic::GACC = 9.80665;
const double pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic::YMAX = +4.0e+3;

// ----------------------------------------------------------------------

class pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP1 :
    public pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic {

    CPPUNIT_TEST_SUB_SUITE(TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP1,
                           TestIsotropicLinearPoroelasticityPlaneStrain);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic::setUp();
        CPPUNIT_ASSERT(_mydata);

        _mydata->meshFilename = "data/tri_fourcells.mesh";

        _mydata->numSolnSubfields = 3;
        static const pylith::topology::Field::Discretization _solnDiscretizations[3] = {
            {1, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // disp
            {1, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // pore_pressure
            {1, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // trace_strain
        };  // {basisOrder, quadOrder, isBasisContinuous?, feSpace}
        _mydata->solnDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_solnDiscretizations);

        _initializeMin();
    } // setUp

}; // TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP1
CPPUNIT_TEST_SUITE_REGISTRATION(pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP1);


/*
// ----------------------------------------------------------------------
class pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP2 :
    public pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic {

    CPPUNIT_TEST_SUB_SUITE(TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP2,
                           TestIsotropicLinearPoroelasticityPlaneStrain);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic::setUp();
        CPPUNIT_ASSERT(_mydata);

        _mydata->meshFilename = "data/tri_fourcells.mesh";

        _mydata->numSolnSubfields = 1;
        static const pylith::topology::Field::Discretization _solnDiscretizations[3] = {
            {2, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // disp
            {2, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // pore_pressure
            {2, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // trace_strain
        };  // {basisOrder, quadOrder, isBasisContinuous?, feSpace}
        _mydata->solnDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_solnDiscretizations);

        static const pylith::topology::Field::Discretization _auxDiscretizations[14] = {
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // density
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // shear_modulus
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // bulk_modulus
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // isotropicPermeability
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // porosity
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_density
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_viscosity
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_bulk_modulus
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // biot_coefficient
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // gravitational_acceleration
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // body_force
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // source_density
            {1, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_stress
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_strain
        };
        _mydata->auxDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_auxDiscretizations);

        _initializeMin();
    } // setUp

}; // TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP2
CPPUNIT_TEST_SUITE_REGISTRATION(pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP2);


// ----------------------------------------------------------------------
class pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP3 :
    public pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic {

    CPPUNIT_TEST_SUB_SUITE(TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP3,
                           TestIsotropicLinearPoroelasticityPlaneStrain);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic::setUp();
        CPPUNIT_ASSERT(_mydata);

        _mydata->meshFilename = "data/tri_fourcells.mesh";

        _mydata->numSolnSubfields = 1;
        static const pylith::topology::Field::Discretization _solnDiscretizations[3] = {
            {3, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // disp
            {3, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // pore_pressure
            {3, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // trace_strain
        };  // {basisOrder, quadOrder, isBasisContinuous?, feSpace}
        _mydata->solnDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_solnDiscretizations);

        static const pylith::topology::Field::Discretization _auxDiscretizations[14] = {
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // density
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // shear_modulus
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // bulk_modulus
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // isotropicPermeability
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // porosity
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_density
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_viscosity
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_bulk_modulus
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // biot_coefficient
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // gravitational_acceleration
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // body_force
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // source_density
            {1, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_stress
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_strain
        };
        _mydata->auxDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_auxDiscretizations);

        _initializeMin();
    } // setUp

}; // TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP3
CPPUNIT_TEST_SUITE_REGISTRATION(pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP3);


// ----------------------------------------------------------------------
class pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP4 :
    public pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic {

    CPPUNIT_TEST_SUB_SUITE(TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP4,
                           TestIsotropicLinearPoroelasticityPlaneStrain);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic::setUp();
        CPPUNIT_ASSERT(_mydata);

        _mydata->meshFilename = "data/tri_fourcells.mesh";

        _mydata->numSolnSubfields = 1;
        static const pylith::topology::Field::Discretization _solnDiscretizations[3] = {
            {4, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // disp
            {4, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // pore_pressure
            {4, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // trace_strain
        };  // {basisOrder, quadOrder, isBasisContinuous?, feSpace}
        _mydata->solnDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_solnDiscretizations);

        static const pylith::topology::Field::Discretization _auxDiscretizations[14] = {
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // density
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // shear_modulus
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // bulk_modulus
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // isotropicPermeability
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // porosity
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_density
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_viscosity
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_bulk_modulus
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // biot_coefficient
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // gravitational_acceleration
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // body_force
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // source_density
            {1, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_stress
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_strain
        };
        _mydata->auxDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_auxDiscretizations);

        _initializeMin();
    } // setUp

}; // TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP4
CPPUNIT_TEST_SUITE_REGISTRATION(pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_TriP4);


// ----------------------------------------------------------------------
class pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ1 :
    public pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic {

    CPPUNIT_TEST_SUB_SUITE(TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ1,
                           TestIsotropicLinearPoroelasticityPlaneStrain);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic::setUp();
        CPPUNIT_ASSERT(_mydata);

        _mydata->meshFilename = "data/quad_aligned.mesh";

        _mydata->numSolnSubfields = 1;
        static const pylith::topology::Field::Discretization _solnDiscretizations[3] = {
            {1, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // disp
            {1, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // pore_pressure
            {1, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // trace_strain
        };  // {basisOrder, quadOrder, isBasisContinuous?, feSpace}
        _mydata->solnDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_solnDiscretizations);

        static const pylith::topology::Field::Discretization _auxDiscretizations[14] = {
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // density
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // shear_modulus
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // bulk_modulus
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // isotropicPermeability
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // porosity
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_density
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_viscosity
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_bulk_modulus
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // biot_coefficient
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // gravitational_acceleration
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // body_force
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // source_density
            {1, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_stress
            {0, 1, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_strain
        };
        _mydata->auxDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_auxDiscretizations);

        _initializeMin();
    } // setUp

}; // TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ1
CPPUNIT_TEST_SUITE_REGISTRATION(pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ1);


// ----------------------------------------------------------------------
class pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ2 :
    public pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic {

    CPPUNIT_TEST_SUB_SUITE(TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ2,  TestIsotropicLinearPoroelasticityPlaneStrain);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic::setUp();
        CPPUNIT_ASSERT(_mydata);

        _mydata->meshFilename = "data/quad_aligned.mesh";

        _mydata->numSolnSubfields = 1;
        static const pylith::topology::Field::Discretization _solnDiscretizations[3] = {
            {2, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // disp
            {2, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // pore_pressure
            {2, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // trace_strain
        };  // {basisOrder, quadOrder, isBasisContinuous?, feSpace}
        _mydata->solnDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_solnDiscretizations);

        static const pylith::topology::Field::Discretization _auxDiscretizations[14] = {
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // density
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // shear_modulus
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // bulk_modulus
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // isotropicPermeability
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // porosity
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_density
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_viscosity
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_bulk_modulus
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // biot_coefficient
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // gravitational_acceleration
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // body_force
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // source_density
            {1, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_stress
            {0, 2, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_strain
        };
        _mydata->auxDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_auxDiscretizations);

        _initializeMin();
    } // setUp

}; // TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ2
CPPUNIT_TEST_SUITE_REGISTRATION(pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ2);


// ----------------------------------------------------------------------
class pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ3 :
    public pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic {

    CPPUNIT_TEST_SUB_SUITE(TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ3,
                           TestIsotropicLinearPoroelasticityPlaneStrain);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic::setUp();
        CPPUNIT_ASSERT(_mydata);

        _mydata->meshFilename = "data/quad_aligned.mesh";

        _mydata->numSolnSubfields = 1;
        static const pylith::topology::Field::Discretization _solnDiscretizations[3] = {
            {3, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // disp
            {3, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // pore_pressure
            {3, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // trace_strain
        };  // {basisOrder, quadOrder, isBasisContinuous?, feSpace}
        _mydata->solnDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_solnDiscretizations);

        static const pylith::topology::Field::Discretization _auxDiscretizations[14] = {
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // density
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // shear_modulus
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // bulk_modulus
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // isotropicPermeability
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // porosity
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_density
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_viscosity
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_bulk_modulus
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // biot_coefficient
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // gravitational_acceleration
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // body_force
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // source_density
            {1, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_stress
            {0, 3, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_strain
        };
        _mydata->auxDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_auxDiscretizations);

        _initializeMin();
    } // setUp

}; // TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ3
CPPUNIT_TEST_SUITE_REGISTRATION(pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ3);


// ----------------------------------------------------------------------
class pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ4 : public pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic { // TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ4

    CPPUNIT_TEST_SUB_SUITE(TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ4,
                           TestIsotropicLinearPoroelasticityPlaneStrain);
    CPPUNIT_TEST_SUITE_END();

    void setUp(void) {
        TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic::setUp();
        CPPUNIT_ASSERT(_mydata);

        _mydata->meshFilename = "data/quad_aligned.mesh";

        _mydata->numSolnSubfields = 1;
        static const pylith::topology::Field::Discretization _solnDiscretizations[3] = {
            {4, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // disp
            {4, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // pore_pressure
            {4, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // trace_strain
        };  // {basisOrder, quadOrder, isBasisContinuous?, feSpace}
        _mydata->solnDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_solnDiscretizations);

        static const pylith::topology::Field::Discretization _auxDiscretizations[14] = {
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // density
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // shear_modulus
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // bulk_modulus
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // isotropicPermeability
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // porosity
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_density
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_viscosity
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // fluid_bulk_modulus
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // biot_coefficient
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // gravitational_acceleration
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // body_force
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // source_density
            {1, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_stress
            {0, 4, true, pylith::topology::Field::POLYNOMIAL_SPACE}, // reference_strain
        };
        _mydata->auxDiscretizations = const_cast<pylith::topology::Field::Discretization*>(_auxDiscretizations);

        _initializeMin();
    } // setUp

}; // TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ4
CPPUNIT_TEST_SUITE_REGISTRATION(pylith::materials::TestIsotropicLinearPoroelasticityPlaneStrain_Hydrostatic_QuadQ4);

*/

// End of file
