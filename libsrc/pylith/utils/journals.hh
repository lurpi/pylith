// -*- C++ -*-
//
// ======================================================================
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
// ======================================================================
//

/**
 * @file libsrc/utils/journals.hh
 *
 * @brief Macros for easy use of JournalingComponent.
 */

#if !defined(pylith_utils_journals_hh)
#define pylith_utils_journals_hh

#include "journal/debug.h"
#include "journal/info.h"
#include "journal/warning.h"
#include "journal/error.h"


#define PYLITH_COMPONENT_DEBUG(msg) \
    do { \
        journal::debug_t debug(PyreComponent::name()); \
        debug << journal::at(__HERE__) \
              << "Component '"<<PyreComponent::identifier()<<"': " \
              << msg << journal::endl; \
    } while (0)

#define PYLITH_COMPONENT_INFO(msg) \
    do { \
        journal::info_t info(PyreComponent::name()); \
        info << journal::at(__HERE__) \
             << "Component '"<<PyreComponent::identifier()<<"': " \
             << msg << journal::endl; \
    } while (0)

#define PYLITH_COMPONENT_WARNING(msg) \
    do { \
        journal::warning_t warning(PyreComponent::name()); \
        warning << journal::at(__HERE__) \
                << "Component '"<<PyreComponent::identifier()<<"': " \
                << msg << journal::endl; \
    } while (0)

#define PYLITH_COMPONENT_ERROR(msg) \
    do { \
        journal::error_t error(PyreComponent::name()); \
        error << journal::at(__HERE__) \
              << "Component '"<<PyreComponent::identifier()<<"': " \
              << msg << journal::endl; \
    } while (0)

#define PYLITH_JOURNAL_DEBUG(msg) \
    do { \
        journal::debug_t debug(GenericComponent::name()); \
        debug << journal::at(__HERE__) \
              << msg << journal::endl; \
    } while (0)

#define PYLITH_JOURNAL_INFO(msg) \
    do { \
        journal::info_t info(GenericComponent::name()); \
        info << journal::at(__HERE__) \
             << msg << journal::endl; \
    } while (0)

#define PYLITH_JOURNAL_WARNING(msg) \
    do { \
        journal::warning_t warning(GenericComponent::name()); \
        warning << journal::at(__HERE__) \
                << msg << journal::endl; \
    } while (0)

#define PYLITH_JOURNAL_ERROR(msg) \
    do { \
        journal::error_t error(GenericComponent::name()); \
        error << journal::at(__HERE__) \
              << msg << journal::endl; \
    } while (0)

#endif // pylith_utils_journals_hh

// End of file
