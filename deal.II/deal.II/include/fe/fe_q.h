//---------------------------------------------------------------
//    $Id$
//    Version: $Name$
//
//    Copyright (C) 1998, 1999, 2000, 2001 by the deal.II authors
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    further information on this license.
//
//---------------------------------------------------------------
#ifndef __deal2__fe_q_h
#define __deal2__fe_q_h

#include <base/polynomial.h>
#include <fe/fe.h>

template <int dim> class TensorProductPolynomials;
template <int dim> class MappingQ;



/**
 * Implementation of Lagrange finite elements @p{Qp} that yield the
 * finite element space of continuous, piecewise polynomials of degree
 * @p{p}. This class is realized using tensor product polynomials
 * based on equidistant support points.
 *
 * The constructor of this class takes the degree @p{p} of this finite
 * element.
 *
 * @sect3{Implementation}
 *
 * The constructor creates a @ref{TensorProductPolynomials} object
 * that includes the tensor product of @p{LagrangeEquidistant}
 * polynomials of degree @p{p}. This @p{TensorProductPolynomials}
 * object provides all values and derivatives of the shape functions.
 *
 * Furthermore the constructor filles the @p{interface_constraints},
 * the @p{prolongation} (embedding) and the @p{restriction}
 * matrices. These are implemented only up to a certain degree, that
 * is listed in the following:
 *
 * @begin{itemize}
 * @item @p{dim==1}
 *   @begin{itemize}
 *   @item the @p{interface_constraints} are not needed
 *   @item the @p{prolongation} matrices up to degree 4, and
 *   @item the @p{restriction} matrices up to degree 4.
 *   @end{itemize}
 * @item @p{dim==2}
 *   @begin{itemize}
 *   @item the @p{interface_constraints} up to degree 4,
 *   @item the @p{prolongation} matrices up to degree 3, and
 *   @item the @p{restriction} matrices up to degree 4.
 *   @end{itemize}
 * @item @p{dim==3}
 *   @begin{itemize}
 *   @item the @p{interface_constraints} up to degree 2,
 *   @item the @p{prolongation} matrices up to degree 2, and
 *   @item the @p{restriction} matrices up to degree 4.
 *   @end{itemize}
 * @end{itemize}
 *
 * @sect3{Numbering of the degrees of freedom (DoFs)}
 *
 * The original ordering of the shape functions represented by the
 * @ref{TensorProductPolynomials} is a tensor product
 * numbering. However, the shape functions on a cell are renumbered
 * beginning with the shape functions whose support points are at the
 * vertices, then on the line, on the quads, and finally (for 3d) on
 * the hexes. To be explicite, these numberings are listed in the
 * following:
 *
 * @sect4{Q1 elements}
 * @begin{itemize}
 * @item 1D case:
 *   @begin{verbatim}
 *      0-------1
 *   @end{verbatim}
 *
 * @item 2D case:
 *   @begin{verbatim}
 *      3-------2
 *      |       |
 *      |       |
 *      |       |
 *      0-------1
 *   @end{verbatim}
 *
 * @item 3D case:
 *   @begin{verbatim}
 *         7-------6        7-------6
 *        /|       |       /       /|
 *       / |       |      /       / |
 *      /  |       |     /       /  |
 *     3   |       |    3-------2   |
 *     |   4-------5    |       |   5
 *     |  /       /     |       |  /
 *     | /       /      |       | /
 *     |/       /       |       |/
 *     0-------1        0-------1
 *
 *   The respective coordinate values of the support points of the degrees
 *   of freedom are as follows:
 *   @begin{itemize}
 *   @item Index 0: @p{[0, 0, 0]};
 *   @item Index 1: @p{[1, 0, 0]};
 *   @item Index 2: @p{[1, 0, 1]};
 *   @item Index 3: @p{[0, 0, 1]};
 *   @item Index 4: @p{[0, 1, 0]};
 *   @item Index 5: @p{[1, 1, 0]};
 *   @item Index 6: @p{[1, 1, 1]};
 *   @item Index 7: @p{[0, 1, 1]};
 *   @end{itemize}
 * @end{itemize}
 * @sect4{Q2 elements}
 * @begin{itemize}
 * @item 1D case:
 *   @begin{verbatim}
 *      0---2---1
 *   @end{verbatim}
 *
 * @item 2D case:
 *   @begin{verbatim}
 *      3---6---2
 *      |       |
 *      7   8   5
 *      |       |
 *      0---4---1
 *   @end{verbatim}
 *
 * @item 3D case:
 *   @begin{verbatim}
 *         7--14---6        7--14---6
 *        /|       |       /       /|
 *      19 |       13     19      1813
 *      /  15      |     /       /  |
 *     3   |       |    3---10--2   |
 *     |   4--12---5    |       |   5
 *     |  /       /     |       9  /
 *    11 16      17     11      | 17
 *     |/       /       |       |/
 *     0---8---1        0---8---1
 *
 *         *-------*        *-------*
 *        /|       |       /       /|
 *       / |  21   |      /  24   / |
 *      /  |       |     /       /  |
 *     *   |       |    *-------*   |
 *     |25 *-------*    |       |23 *
 *     |  /       /     |   20  |  /
 *     | /  22   /      |       | /
 *     |/       /       |       |/
 *     *-------*        *-------* 
 *   @end{verbatim}
 *   The center vertex has number 26.
 *
 *   The respective coordinate values of the support points of the degrees
 *   of freedom are as follows:
 *   @begin{itemize}
 *   @item Index 0: @p{[0, 0, 0]};
 *   @item Index 1: @p{[1, 0, 0]};
 *   @item Index 2: @p{[1, 0, 1]};
 *   @item Index 3: @p{[0, 0, 1]};
 *   @item Index 4: @p{[0, 1, 0]};
 *   @item Index 5: @p{[1, 1, 0]};
 *   @item Index 6: @p{[1, 1, 1]};
 *   @item Index 7: @p{[0, 1, 1]};
 *   @item Index 8: @p{[1/2, 0, 0]};
 *   @item Index 9: @p{[1, 0, 1/2]};
 *   @item Index 10: @p{[1/2, 0, 1]};
 *   @item Index 11: @p{[0, 0, 1/2]};
 *   @item Index 12: @p{[1/2, 1, 0]};
 *   @item Index 13: @p{[1, 1, 1/2]};
 *   @item Index 14: @p{[1/2, 1, 1]};
 *   @item Index 15: @p{[0, 1, 1/2]};
 *   @item Index 16: @p{[0, 1/2, 0]};
 *   @item Index 17: @p{[1, 1/2, 0]};
 *   @item Index 18: @p{[1, 1/2, 1]};
 *   @item Index 19: @p{[0, 1/2, 1]};
 *   @item Index 20: @p{[1/2, 0, 1/2]};
 *   @item Index 21: @p{[1/2, 1, 1/2]};
 *   @item Index 22: @p{[1/2, 1/2, 0]};
 *   @item Index 23: @p{[1, 1/2, 1/2]};
 *   @item Index 24: @p{[1/2, 1/2, 1]};
 *   @item Index 25: @p{[0, 1/2, 1/2]};
 *   @item Index 26: @p{[1/2, 1/2, 1/2]}; 
 *   @end{itemize}
 * @end{itemize}
 * @sect4{Q3 elements}
 * @begin{itemize}
 * @item 1D case:
 *   @begin{verbatim}
 *      0--2--3--1
 *   @end{verbatim}
 *
 * @item 2D case:
 *   @begin{verbatim}
 *      3--8--9--2
 *      |        |
 *      11 14 15 7
 *      |        |
 *      10 12 13 6
 *      |        |
 *      0--4--5--1
 *   @end{verbatim}
 *   Note the reverse ordering of degrees of freedom on the left and
 *   upper line.
 * @end{itemize}
 * @sect4{Q4 elements}
 * @begin{itemize}
 * @item 1D case:
 *   @begin{verbatim}
 *      0--2--3--4--1
 *   @end{verbatim}
 *
 * @item 2D case:
 *   @begin{verbatim}
 *      3--10-11-12-2
 *      |           |
 *      15 22 23 24 9
 *      |           |
 *      14 19 20 21 8
 *      |           |
 *      13 16 17 18 7
 *      |           |
 *      0--4--5--6--1
 *   @end{verbatim}
 * @end{itemize}
 * Note the reverse ordering of degrees of freedom on the left and upper
 * line.
 *
 * @author Wolfgang Bangerth, 1998, Ralf Hartmann, Guido Kanschat, 2001
 */
template <int dim>
class FE_Q : public FiniteElement<dim>
{
  public:
				     /**
				      * Constructor for tensor product
				      * polynomials of degree @p{p}.
				      */
    FE_Q (const unsigned int p);
    
				     /**
				      * Destructor.
				      */
    ~FE_Q ();

//TODO:[RH] make get_renumber private or move it some other place    
				     /**
				      * Read-only access to the
				      * renumber vector.
				      */
    const std::vector<unsigned int> & get_renumber() const;

				     /**
				      * Return the polynomial degree
				      * of this finite element,
				      * i.e. the value passed to the
				      * constructor.
				      */
    unsigned int get_degree () const;
    
				     /**
				      * Determine an estimate for the
				      * memory consumption (in bytes)
				      * of this object.
				      *
				      * This function is made virtual,
				      * since finite element objects
				      * are usually accessed through
				      * pointers to their base class,
				      * rather than the class itself.
				      */
    virtual unsigned int memory_consumption () const;

  protected:    
				     /**
				      * @p{clone} function instead of
				      * a copy constructor.
				      *
				      * This function is needed by the
				      * constructors of @p{FESystem}.
				      */
    virtual FiniteElement<dim> * clone() const;
  
				     /**
				      * Prepare internal data
				      * structures and fill in values
				      * independent of the cell.
				      */
    virtual
    typename Mapping<dim>::InternalDataBase *
    get_data (const UpdateFlags,
	      const Mapping<dim>& mapping,
	      const Quadrature<dim>& quadrature) const ;

				     /**
				      * Implementation of the same
				      * function in
				      * @ref{FiniteElement}.
				      */
    virtual void
    fill_fe_values (const Mapping<dim> &mapping,
		    const typename DoFHandler<dim>::cell_iterator &cell,
		    const Quadrature<dim>                &quadrature,
		    typename Mapping<dim>::InternalDataBase      &mapping_internal,
		    typename Mapping<dim>::InternalDataBase      &fe_internal,
		    FEValuesData<dim>& data) const;
    
				     /**
				      * Implementation of the same
				      * function in
				      * @ref{FiniteElement}.
				      */
    virtual void
    fill_fe_face_values (const Mapping<dim> &mapping,
			 const typename DoFHandler<dim>::cell_iterator &cell,
			 const unsigned int                    face_no,
			 const Quadrature<dim-1>                &quadrature,
			 typename Mapping<dim>::InternalDataBase      &mapping_internal,
			 typename Mapping<dim>::InternalDataBase      &fe_internal,
			 FEValuesData<dim>& data) const ;
    
				     /**
				      * Implementation of the same
				      * function in
				      * @ref{FiniteElement}.
				      */
    virtual void
    fill_fe_subface_values (const Mapping<dim> &mapping,
			    const typename DoFHandler<dim>::cell_iterator &cell,
			    const unsigned int                    face_no,
			    const unsigned int                    sub_no,
			    const Quadrature<dim-1>                &quadrature,
			    typename Mapping<dim>::InternalDataBase      &mapping_internal,
			    typename Mapping<dim>::InternalDataBase      &fe_internal,
			    FEValuesData<dim>& data) const ;

  private:

				     /**
				      * Declare a nested class which
				      * will has static definitions of
				      * various matrices such as
				      * constraint and embedding
				      * matrices. The definition of
				      * the various static fields are
				      * in the files @p{fe_q_[123]d.cc}
				      * in the source directory.
				      */
    struct Matrices
    {
					 /**
					  * Embedding matrices. For
					  * each element type (the
					  * first index) there are as
					  * many embedding matrices as
					  * there are children per
					  * cell. The first index
					  * starts with linear
					  * elements and goes up in
					  * polynomial degree. The
					  * array may grow in the
					  * future with the number of
					  * elements for which these
					  * matrices have been
					  * computed. If for some
					  * element, the matrices have
					  * not been computed then you
					  * may use the element
					  * nevertheless but can not
					  * access the respective
					  * fields.
					  */
	static const double * const
	embedding[][GeometryInfo<dim>::children_per_cell];

					 /**
					  * Number of elements (first
					  * index) the above field
					  * has. Equals the highest
					  * polynomial degree for
					  * which the embedding
					  * matrices have been
					  * computed.
					  */
	static const unsigned int n_embedding_matrices;

					 /**
					  * As the
					  * @p{embedding_matrices}
					  * field, but for the
					  * interface constraints. One
					  * for each element for which
					  * it has been computed.
					  */
	static const double * const constraint_matrices[];

					 /**
					  * Like
					  * @p{n_embedding_matrices},
					  * but for the number of
					  * interface constraint
					  * matrices.
					  */
	static const unsigned int n_constraint_matrices;
    };
    
				     /**
				      * Only for internal use. Its
				      * full name is
				      * @p{get_dofs_per_object_vector}
				      * function and it creates the
				      * @p{dofs_per_object} vector that is
				      * needed within the constructor to
				      * be passed to the constructor of
				      * @p{FiniteElementData}.
				      */
    static std::vector<unsigned int> get_dpo_vector(const unsigned int degree);
    
				     /**
				      * Map tensor product data to shape
				      * function numbering.
				      *
				      * The node values are ordered such
				      * that vertices are first,
				      * followed by lines,
				      * quadrilaterals and
				      * hexahedra. Furthermore, the
				      * ordering inside each group may
				      * be confused, too. Therefore,
				      * this function computes a mapping
				      * from lexicographic ordering
				      * (x,y,z) to the shape function
				      * structure.
				      *
				      * This function is made
				      * static. This allows other
				      * classes (like e.g. @p{MappingQ})
				      * to call this functions without a
				      * need to create a
				      * FiniteElement. This function
				      * needs some data from the base
				      * class @p{FiniteElementData} of
				      * this @p{FE_Q} class. But this
				      * data cannot be accessed to by a
				      * static function. Hence this
				      * function needs an additional
				      * @p{FiniteElementData} argument.
				      */
    static void build_renumbering (const FiniteElementData<dim> &fe_data,
				   const unsigned int            degree,
				   std::vector<unsigned int>    &numbering);

				     /**
				      * Map tensor product data to
				      * shape function numbering on
				      * first face.
				      *
				      * This function does the same as
				      * @p{build_renumbering}, only on
				      * the first face.
				      *
				      * It is used to compute the
				      * order of face support points.
				      *
				      * In 1d, this function does
				      * nothing.
				      */
    static void build_face_renumbering (const unsigned int              degree,
					std::vector<unsigned int>      &numbering);

				     /**
				      * Initialize the
				      * @p{unit_support_points} field
				      * of the @ref{FiniteElementBase}
				      * class. Called from the
				      * constructor.
				      */
    void initialize_unit_support_points ();

				     /**
				      * Initialize the
				      * @p{unit_face_support_points} field
				      * of the @ref{FiniteElementBase}
				      * class. Called from the
				      * constructor.
				      */
    void initialize_unit_face_support_points ();
    
				     /**
				      * Compute flags for initial
				      * update only.
				      */
    virtual UpdateFlags update_once (UpdateFlags flags) const;
  
				     /**
				      * Compute flags for update on
				      * each cell.
				      */
    virtual UpdateFlags update_each (UpdateFlags flags) const;
    
				     /**
				      * Degree of the polynomials.
				      */  
    const unsigned int degree;

				     /**
				      * Mapping from lexicographic to
				      * shape function numbering.
				      */
    std::vector<unsigned int> renumber;
    
				     /**
				      * Mapping from lexicographic to
				      * shape function numbering on first face.
				      */
    std::vector<unsigned int> face_renumber;

				     /**
				      * Pointer to the tensor
				      * product polynomials.
				      */
    TensorProductPolynomials<dim>* poly;

				     /**
				      * Fields of cell-independent data.
				      */
    class InternalData : public FiniteElementBase<dim>::InternalDataBase
    {
      public:
					 /**
					  * Array with shape function values
					  * in quadrature points. There is one
					  * vector for each shape function, containing
					  * values for each quadrature point.
					  */
	std::vector<std::vector<double> > shape_values;

					 /**
					  * Array with shape function gradients
					  * in quadrature points. There is one
					  * vector for each shape function, containing
					  * values for each quadrature point.
					  */				      
	std::vector<std::vector<Tensor<1,dim> > > shape_gradients;
    };
    
				     /**
				      * Allow access from other dimensions.
				      */
    template <int dim1> friend class FE_Q;
  
				     /**
				      * Allows @p{MappingQ} class to
				      * access to @p{build_renumbering}
				      * function.
				      */
    friend class MappingQ<dim>;
};




template<int dim>
inline
const std::vector<unsigned int> &
FE_Q<dim>::get_renumber() const
{
  return renumber;
}



#endif

