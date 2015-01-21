/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#pragma once

/**
 * @file FuzzySegmentComputer.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2015/01/05
 *
 * Header file for module FuzzySegmentComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(FuzzySegmentComputer_RECURSES)
#error Recursive header files inclusion detected in FuzzySegmentComputer.h
#else // defined(FuzzySegmentComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define FuzzySegmentComputer_RECURSES

#if !defined FuzzySegmentComputer_h
/** Prevents repeated inclusion of headers. */
#define FuzzySegmentComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/surfaces/ParallelStrip.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class FuzzySegmentComputer
/**
 * Description of class 'FuzzySegmentComputer' <p>
 * \brief Aim:
 */


template <typename TSpace, 
          typename TInputPoint,
          typename TInternalScalar>

class FuzzySegmentComputer
{

  // ----------------------- public types --------------------------------------
  BOOST_CONCEPT_ASSERT(( concepts::CSpace< TSpace > ));
  BOOST_CONCEPT_ASSERT(( concepts::CSignedNumber< TInternalScalar > ));
  BOOST_STATIC_ASSERT(( TSpace::dimension == 2 ));
  BOOST_STATIC_ASSERT(( TInputPoint::dimension == 2 ));
  
public:


  typedef TSpace Space;
  typedef TInputPoint InputPoint;
  typedef TInternalScalar InternalScalar;
  typedef InputPoint InputVector;
  typedef InternalScalar InternalVector[ 2 ];

  
  typedef std::set< InputPoint > InputPointSet;
  typedef typename InputPointSet::size_type Size;
  typedef typename InputPointSet::const_iterator ConstIterator;
  typedef typename InputPointSet::iterator Iterator;

  typedef ParallelStrip<Space,true,true> Primitive;
  

  
  // ----------------------- Standard services ------------------------------
public:
  

  /**
   * Constructor.
   */
  FuzzySegmentComputer();



  /**
   * Destructor.
   */
  ~FuzzySegmentComputer();

  


  //-------------------- model of ForwardContainer -----------------------------
public:

  /**
   * @return the number of distinct points in the current fuzzy segment.
   */
  Size size() const;

  /**
   * @return 'true' if and only if this object contains no point.
   */
  bool empty() const;
  
  
  /**
   * @return a const iterator pointing on the first point stored in the current fuzzy segment.
   */
  ConstIterator begin() const;


  /**
   * @return a const iterator pointing after the last point stored in the current fuzzy segment.
   */
  ConstIterator end() const;


  /**
   * NB: std version.
   * @return the maximal allowed number of points in the current fuzzy segment.
   * @see maxSize
   */
  Size max_size() const;

  
  /**
   * same as max_size
   * @return the maximal allowed number of points in the current fuzzy segment.
   */
  Size maxSize() const;  
  



  //-------------------- model of CBidirectionalSegmentComputer ----------------

public:
  
  /**
   * Initialisation.
   * @param aThickness the thickness of the fuzzy segment.
   * @param it an iterator on 2D points
   */
  void init(double aThickness, const ConstIterator& it);  


  
  /**
   * Tests whether the current fuzzy segment can be extended at the front.
   *  
   * @return 'true' if yes, 'false' otherwise.
   */
  bool isExtendableFront();


  /**
   * Tests whether the current fuzzy segment can be extended at the front.
   * Computes the parameters of the extended fuzzy segment if yes.
   * @return 'true' if yes, 'false' otherwise.
   */
  bool extendFront();

  
  /**
   * Tests whether the current fuzzy segment can be extended at the back.
   *  
   * @return 'true' if yes, 'false' otherwise.
   */
  bool isExtendableBack();


  /**
   * Tests whether the current fuzzy segment can be extended at the back.
   * Computes the parameters of the extended fuzzy segment if yes.
   * @return 'true' if yes, 'false' otherwise.
   */
  bool extendBack();
  
 

  //-------------------- Primitive services -----------------------------
  
  
   /**
      @return the current primitive recognized by this computer,
      which is a ParallelStrip of axis width smaller than the one
      specified at instanciation.
   */
  Primitive primitive() const;
  


  
    // ----------------------- Interface --------------------------------------
public:

  
  std::vector<InputPoint> getConvexHull() const;


    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ------------------------- Protected Datas ------------------------------
protected:
  
  /**
   * begin iterator (associated to input data)
   **/
  ConstIterator myBegin;

  /**
   * begin iterator (associated to input data)
   **/
  ConstIterator myEnd;
  
    

  

    // ------------------------- Private Datas --------------------------------
private:

  /**
   * The set of points contained in the fuzzy segment which can be changed during computations.
   *
   **/
  mutable InputPointSet myPointSet; 
  
  bool myIsValid;

  double myThickness;
  
  

  /**
   *  Melkman algorithm main dequeu 
   *
   **/

  std::deque<InputPoint> myMelkmanQueue;
  
  bool myIsMelkmanInitialized;
  
  // Used in melkmanMainDiagonal()
  double myConvexHullHeight;  
  double myConvexHullWidth;
  

  InputPoint myEdgeP, myEdgeQ, myVertexS;
  InputPoint myEdgePh, myEdgeQh, myVertexSh;
  InputPoint myEdgePw, myEdgeQw, myVertexSw;


  


    // ------------------------- Hidden services ------------------------------
protected:







    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    FuzzySegmentComputer ( const FuzzySegmentComputer & other );
  
    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
  FuzzySegmentComputer & operator= ( const FuzzySegmentComputer & other );


  /**
   *  Used to check if the initialisation with 3 non aligned points is well done.
   *
   **/     
   bool melkmanIsWellInitialized() const;


  /**
   *  Melkman main diagonal
   *  @return the main diagonal width of a convex set
   *
   **/     
   double melkmanMainDiagonal();
  
  
  /**
   * Melkman
   * Add a point in a convex using one step of Melkman algorithm.
   * @param[in] aPoint the point to be added.
   */
  void melkmanAddPoint( const InputPoint &aPoint );



  /**
   * Melkman
   * Check if the 3 init point of the queue are given in the correct order (else it re order it).
   *
   * (it checks only the 3 first points of myMelkmanQueue)
   **/
  void melkmanInitCheck( ) ; 


  /**
   * IsConvexValid
   * Depending on connexity, return true if a convex is valid.
   * @param aThick the thickness of reference
   */
  bool melkmanIsConvexValid() ;
  
  
  /**
   * Test if a point aP2 is Left|On|Right of an infinite line (defined from fron two points aP0 and aP1).
   *
   * @param[in] aP0 the first point defining the line.
   * @param[in] aP1 the second point defining the line.
   * @param[in] aP2 the point to be tested.
   */
  InternalScalar melkmanIsLeft(const InputPoint &aP0, const InputPoint &aP1, const InputPoint &aP2) const;
  
  

    // ------------------------- Internals ------------------------------------
private:

}; // end of class FuzzySegmentComputer


/**
 * Overloads 'operator<<' for displaying objects of class 'FuzzySegmentComputer'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'FuzzySegmentComputer' to write.
 * @return the output stream after the writing.
 */
template <typename TSpace, typename TInputPoint, typename TInternalScalar>
std::ostream&
operator<< ( std::ostream & out, const FuzzySegmentComputer<TSpace, TInputPoint, TInternalScalar> & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#if !defined(BUILD_INLINE)
#include "DGtal/geometry/curves/FuzzySegmentComputer.ih"
#endif


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined FuzzySegmentComputer_h

#undef FuzzySegmentComputer_RECURSES
#endif // else defined(FuzzySegmentComputer_RECURSES)
