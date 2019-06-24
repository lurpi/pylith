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

/** @file libsrc/materials/IsotropicLinearPoroelasticity.hh
 *
 * @brief C++ class for isotropic linear incompressible elasticity.
 */

#if !defined(pylith_materials_isotropiclinearporoelasticity_hh)
#define pylith_materials_isotropiclinearporoelasticity_hh

#include "materialsfwd.hh" // forward declarations

#include "pylith/materials/RheologyPoroelasticity.hh" // ISA RheologyIncompressibleElasticity

class pylith::materials::IsotropicLinearPoroelasticity : public pylith::materials::RheologyPoroelasticity {
    friend class TestIsotropicLinearPoroelasticity; // unit testing

    // PUBLIC METHODS //////////////////////////////////////////////////////////////////////////////////////////////////
public:

    /// Default constructor.
    IsotropicLinearPoroelasticity(void);

    /// Destructor.
    ~IsotropicLinearPoroelasticity(void);

    /// Deallocate PETSc and local data structures.
    void deallocate(void);

    /** Include reference stress/strain?
     *
     * @param value Flag indicating to include reference stress/strain.
     */
    void useReferenceState(const bool value);

    /** Use reference stress and strain in computation of stress and
     * strain?
     *
     * @returns True if using reference stress and strain, false otherwise.
     */
    bool useReferenceState(void) const;

    /** Get auxiliary factory associated with physics.
     *
     * @return Auxiliary factory for physics object.
     */
    pylith::materials::AuxiliaryFactoryPoroelastic* getAuxiliaryFactory(void);

    /** Add rheology subfields to auxiliary field.
     *
     * @param[inout] auxiliaryField Auxiliary field.
     */
    void addAuxiliarySubfields(void);

    /** Get stress kernel for RHS residual, G(t,s).
     *
     * @param[in] coordsys Coordinate system.
     *
     * @return RHS residual kernel for stress.
     */
    PetscPointFunc getKernelRHSResidualEffectiveStress(const spatialdata::geocoords::CoordSys* coordsys) const;

    /** Get pressure kernel for RHS residual, G(t,s).
     *
     * @param[in] coordsys Coordinate system.
     *
     * @return RHS residual kernel for pressure.
     */
    PetscPointFunc getKernelRHSResidualPressure(const spatialdata::geocoords::CoordSys* coordsys) const;

    /** Get elastic constants kernel for RHS Jacobian G(t,s).
     *
     * @param[in] coordsys Coordinate system.
     *
     * @return RHS Jacobian kernel for elastic constants.
     */
    PetscPointJac getKernelRHSJacobianElasticConstants(const spatialdata::geocoords::CoordSys* coordsys) const;

    /** Get inverse of the bulk modulus kernel for RHS Jacobian G(t,s).
     *
     * @param[in] coordsys Coordinate system.
     *
     * @return RHS Jacobian kernel for inverse of bulk modulus.
     */
    PetscPointJac getKernelRHSJacobianInverseBulkModulus(const spatialdata::geocoords::CoordSys* coordsys) const;

    /** Get stress kernel for derived field.
     *
     * @param[in] coordsys Coordinate system.
     *
     * @return Project kernel for computing stress subfield in derived field.
     */
    PetscPointFunc getKernelDerivedCauchyStress(const spatialdata::geocoords::CoordSys* coordsys) const;

    /** Get stress kernel for derived field.
     *
     * @param[in] coordsys Coordinate system.
     *
     * @return Project kernel for computing stress subfield in derived field.
     */
    PetscPointJac getKernelRHSJacobianBiotCoefficient(const spatialdata::geocoords::CoordSys* coordsys) const;

    /** Get stress kernel for derived field.
     *
     * @param[in] coordsys Coordinate system.
     *
     * @return Project kernel for computing stress subfield in derived field.
     */
    PetscPointJac getKernelRHSJacobianDarcyConductivity(const spatialdata::geocoords::CoordSys* coordsys) const;

    /** Get stress kernel for derived field.
     *
     * @param[in] coordsys Coordinate system.
     *
     * @return Project kernel for computing stress subfield in derived field.
     */
    //PetscPointFunc getKernelRHSDarcyVelocity(const spatialdata::geocoords::CoordSys* coordsys) const;

    // PROTECTED METHODS ///////////////////////////////////////////////////////////////////////////////////////////////
protected:

    /** Get auxiliary factory associated with physics.
     * @return Auxiliary factory for physics object.
     */
    pylith::feassemble::AuxiliaryFactory* _getAuxiliaryFactory(void);

    // PRIVATE MEMBERS /////////////////////////////////////////////////////////////////////////////////////////////////
private:

    pylith::materials::AuxiliaryFactoryPoroelastic* _auxiliaryFactory; ///< Factory for auxiliary subfields.
    bool _useReferenceState; ///< Flag to use reference stress and strain.

    // NOT IMPLEMENTED /////////////////////////////////////////////////////////////////////////////////////////////////
private:

    IsotropicLinearPoroelasticity(const IsotropicLinearPoroelasticity&); ///< Not implemented.
    const IsotropicLinearPoroelasticity& operator=(const IsotropicLinearPoroelasticity&); ///< Not implemented

};

// class IsotropicLinearPoroelasticity

#endif // pylith_materials_isotropiclinearporoelasticity_hh

// End of file
