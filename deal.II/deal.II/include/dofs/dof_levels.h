//---------------------------------------------------------------------------
//    $Id$
//    Version: $Name$
//
//    Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006 by the deal.II authors
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    further information on this license.
//
//---------------------------------------------------------------------------
#ifndef __deal2__dof_levels_h
#define __deal2__dof_levels_h


#include <base/config.h>
#include <vector>


namespace internal
{
/**
 * A namespace for internal data structures of the DoFHandler group of classes.
 *
 * @ingroup dofs
 */
  namespace DoFHandler
  {
    
/**
 * Store the indices of the degrees of freedom which are located on
 * objects of dimension @p N.  Declare this general template
 * class, but do not actually use it. Rather, only specializations of
 * this class are used.
 *
 * <h3>Information for all DoFLevel classes</h3>
 *
 * The <tt>DoFLevel<N></tt> classes 
 * store the global indices of the degrees of freedom for each cell on a
 * certain level. The index or number of a degree of freedom is the zero-based
 * index of the according value in the solution vector and the row and column
 * index in the global matrix or the multigrid matrix for this level. These
 * indices refer to the unconstrained vectors and matrices, where we have not
 * taken account of the constraints introduced by hanging nodes.
 *
 * The storage format of the degrees of freedom indices (short: DoF
 * indices) is somewhat like a mirror of the data structures of the
 * triangulation classes.  There is a hierarchy of
 * DoFLevel<dim> classes for the different dimensions which
 * have objects named @p line_dofs, @p quad_dofs and so on, in which
 * the indices of DoFs located on lines and quads, respectively, are
 * stored. The indices are stored levelwise. The layout in these
 * arrays is as follows: if for a selected finite element (use
 * DoFHandler::distribute_dofs() to select a finite element)
 * the number of DoFs on each line (without those in the vertices) is
 * @p N, then the length of the @p line_dofs array is @p N times
 * the number of lines on this level. The DoF indices for the @p ith
 * line are at the positions <tt>N*i...(N+1)*i-1</tt>.
 *
 * Since vertices are not associated with a particular level, the
 * indices associated with vertices are not stored in the DoFLevel
 * classes but rather in the DoFHandler::vertex_dofs array.
 *
 * @ingroup dofs
 * @author Wolfgang Bangerth, 1998
 */
    template <int N>
    class DoFLevel
    {
      private:
                                         /**
                                          * Make the constructor private
                                          * to avoid that someone uses
                                          * this class.
                                          */
        DoFLevel ();
    };


/**
 * Store the indices of the degrees of freedom which are located on
 * the lines. See the general template DoFLevel for more information.
 *
 * @ingroup dofs
 * @author Wolfgang Bangerth, 1998
 */
    template <>
    class DoFLevel<1>
    {
      public:
                                         /**
                                          * Store the global indices of
                                          * the degrees of freedom. See
                                          * DoFLevel for detailed
                                          * information.
                                          */
        std::vector<unsigned int> line_dofs;

                                         /**
                                          * Determine an estimate for the
                                          * memory consumption (in bytes)
                                          * of this object.
                                          */
        unsigned int memory_consumption () const;
    };



/**
 * Store the indices of the degrees of freedom which are located on
 * quads. See the general template DoFLevel for more information.
 *
 * @ingroup dofs
 * @author Wolfgang Bangerth, 1998
 */
    template <>
    class DoFLevel<2> : public DoFLevel<1>
    {
      public:
                                         /**
                                          * Store the global indices of
                                          * the degrees of freedom. See
                                          * DoFLevel for detailed
                                          * information.
                                          */
        std::vector<unsigned int> quad_dofs;

                                         /**
                                          * Determine an estimate for the
                                          * memory consumption (in bytes)
                                          * of this object.
                                          */
        unsigned int memory_consumption () const;
    };



/**
 * Store the indices of the degrees of freedom which are located on
 * hexhedra. See the general template DoFLevel for more information.
 *
 * @ingroup dofs
 * @author Wolfgang Bangerth, 1998
 */
    template <>
    class DoFLevel<3> : public DoFLevel<2>
    {
      public:
                                         /**
                                          * Store the global indices of
                                          * the degrees of freedom. See
                                          * DoFLevel for detailed
                                          * information.
                                          */
        std::vector<unsigned int> hex_dofs;

                                         /**
                                          * Determine an estimate for the
                                          * memory consumption (in bytes)
                                          * of this object.
                                          */
        unsigned int memory_consumption () const;
    };
    
  }
  
}

#endif
