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
 * @file DSLSubsegment.h
 * @author Isabelle Sivignon (\c isabelle.sivignon@gipsa-lab.grenoble-inp.fr )
 * gipsa-lab Grenoble Images Parole Signal Automatique (CNRS, UMR 5216), CNRS, France
 *
 * @date 2012/07/17
 *
 *
 */

#if defined(DSLSubsegment_RECURSES)
#error Recursive header files inclusion detected in DSLSubsegment.h
#else // defined(DSLSubsegment_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DSLSubsegment_RECURSES

#if !defined DSLSubsegment_h
/** Prevents repeated inclusion of headers. */
#define DSLSubsegment_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/arithmetic/IntegerComputer.h"

#include <iomanip> 

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class DSLSubsegment
/**
 * Description of class 'DSLSubsegment' <p>
 * \brief Aim: Given a Digital Straight line and two endpoints A and B
 * on this line, compute the minimal characteristics of the digital
 * subsegment [AB] in logarithmic time. Two algorithms are implemented:
 * one is based on the local computation of lower and upper convex
 * hulls, the other is based on a dual transformation and uses the Farey
 * fan.
 * @tparam TInteger is the type of integer used
 * @tparam TNumber is the type of number used to represent the input DSL characteristics.
 */


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
  
  template <typename TInteger, typename TNumber>
    class DSLSubsegment
  {
      // ----------------------- Standard services ------------------------------
    public:
      
      /**
       * Destructor.
     */
      ~DSLSubsegment(){};
      
    // ----------------------- Interface --------------------------------------
    public:
      
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
      
      /**
       * Number types
       */
      typedef TNumber Number;
      typedef TInteger Integer;
      typedef long double LongDoubleType;
      
      
      /** 
       * A ray is defined as a 2D integer vector (x,y) such that
       * Ray(x,y) is the straight line beta = -x alpha +y  in the (alpha,beta)-space.
       */
      typedef DGtal::PointVector<2,Integer> Ray;
      
      /** 
       * 2D integer point
       */
      typedef DGtal::PointVector<2,Integer> Point;
      
      /** 
       * 2D real point
       */
      typedef DGtal::PointVector<2,Number> PointF;

      /** 
       * 2D integer vector
       */
      typedef DGtal::PointVector<2,Integer> Vector;
      
      /**
       * 2D real vector 
       */
      typedef DGtal::PointVector<2,Number> VectorF;
      
      /** 
       * Check that Number type verifies the Euclidean Rign concept and
       * Integer type verifies the Integer concept 
       */
      BOOST_CONCEPT_ASSERT((CEuclideanRing<Number>));
      BOOST_CONCEPT_ASSERT((CInteger<Integer>));

  protected:
      /**
       * The minimal characteristics of the subsegment AB of the
       * DSL(a,b,mu) are (myA,myB,myMu).
       *
       */
      Integer myA;
      
      /**
       * The minimal characteristics of the subsegment AB of the
       * DSL(a,b,mu) are (myA,myB,myMu).
       *
       */
      Integer myB;
      
      /**
       * The minimal characteristics of the subsegment AB of the
       * DSL(a,b,mu) are (myA,myB,myMu).
       *
       */
      Integer myMu;
      
      /** 
       * Precision used for floating-point geometrical predicates (when
       * TNumber is not an integer type)
       */
      Number myPrecision;
      
  public:
      /**  
       * Constructor
       * Given the parameters of a DSL 0 <= ax -by + mu < b, and two points A and B of this DSL,
       * compute the parameters of the DSS [AB]. The algorithm used
       * depends on the value of the boolean (Farey fan if true, local
       * convex hull otherwise).
       * @param Number a
       * @param Number b
       * @param Number mu
       * @param Point A
       * @param Point B
       * @param boolean farey
       */
      DSLSubsegment(Number a, Number b, Number mu, Point A, Point B, bool farey);

      /**
       * Constructor
       * Given a straight line of equation y = alpha x + beta, and two
       * points A and B of the OBQ digitization of this line, compute
       * the parameters of the DSS [AB]. The algorithm implemented uses
       * the Farey fan. Requires a precision parameter for floating-point geometrical predicates
       * @param Number alpha
       * @param Number beta
       * @param Point A
       * @param Point B
       * @param Number precision
       */
      DSLSubsegment(Number alpha, Number beta, Point A, Point B, Number precision = 1e-10);
       
       
  protected: 
      /**
       * Function called by the constructor when the input parameters
       * are integers and the Farey Fan algorithm is used.
       * @param Number a
       * @param Number b
       * @param Number mu
       * @param Point A
       * @param Point B  
      */
      void DSLSubsegmentFareyFan(Number a, Number b, Number mu, Point A, Point B);
      
      /**
       * Function called by the constructor when the input parameters
       * are integers and the local convex hull algorithm is used.
       * @param Number a
       * @param Number b
       * @param Number mu
       * @param Point A
       * @param Point B
       */
      void DSLSubsegmentLocalCH(Number a, Number b, Number mu, Point A, Point B);
      
      
      /**
       * Constructor.
       * Forbidden by default (protected to avoid g++ warnings).
       */
      DSLSubsegment();
      
      
      /** 
       * Class Ray Implements the concept of Ray in the dual space (alpha,beta)
       */
      class RayC
      {
      public :
	
	/** 
	 * slope of the ray
	 */
	Integer x;
	
	/** 
	 * intercept of the ray
	 */
	Integer y;
	
	/**
	 * Default constructor.
	 * not valid
	 */
	RayC();
	
	/**
	 * Constructor of the ray R(alpha,beta): beta = -alpha x0 + y0
	 * @param Integer x0
	 * @param Integer y0
	 */
	RayC(const Integer x0, const Integer y0);
	
	/**
	 * Constructor of the ray passing through the point (p/q,r/q)
	 * and of given slope
	 * @param Integer p
	 * @param Integer q
	 * @param Integer r
	 * @param Integer slope
	 */
	RayC(const Integer p, const Integer q, const Integer r, const Integer slope);
	
	~RayC();
	
      };
      
      /** 
       * Position of a point wrt a ray
       */
      typedef enum Position
      {
	ABOVE,
	BELOW,
	ONTO
      } Position;
      
      
      /**
       * Compute the intersection between the line of direction v
       * passing through P and the vertical line x = n.
       * The intersection point is of the form P + \alpha*v and the
       * function returns the value floor(alpha).
       * @param Point P
       * @param Vector v
       * @param Integer n
       * @return Integer
       */
      Integer intersectionVertical(Point P, Vector v, Integer n);
      
      
      /**
       * Compute the intersection between the line of direction v
       * passing through P and the line y = (aL[1]/aL[0])*x +r 
       * The intersection point is of the form P + \alpha*v and the
       * function returns the value floor(alpha).
       * @param Point P 
       * @param Vector V
       * @param Vector aL 
       * @param Integer r
       * @return Integer
       */
      Integer intersection(Point P, Vector v, Vector aL, Integer r);
      
      /**
       * Compute the intersection between the line of direction v
       * passing through P and the line y = s*x 
       * The intersection point is of the form P + \alpha*v and the
       * function returns the value floor(alpha).
       * @param Point P
       * @param Vector v
       * @param Number s
       * @return Integer
       */
      Integer intersection(Point P, Vector v, Number s);
      
      /**
       * Update the Bezout vector v of u according to the new point A in the
       * case of integer parameters. Follows algorithm presented in
       * [Charrier,Buzer, 2007]
       * @param Vector u 
       * @param Point A
       * @param Vector l directional vector of the line
       * @param Integer r intercept of the line
       * @param Vector* v bezout vector updated in this function
       */
      void update(Vector u, Point A, Vector l, Integer r, Vector *v);
      
      /**
       * Update the Bezout vector v of u according to the new point A in the
       * case of floating-point parameters. Follows algorithm presented in
       * [Charrier,Buzer, 2007]
       *
       * @param Vector u 
       * @param Point A
       * @param Number slope of the line
       * @param Vector* v bezout vector updated in this function
       */
      void update(Vector u, Point A, Number s, Vector *v);
      
      /**
       * Compute the lower integer convex hull of the line of directional vector
       * l and intercept mu between the points A and B. The algorithm
       * works in two steps (from left to right and right to left). Each
       * step returns the two closest points, and these four points are
       * returned by the function.
       * @param Vector l directional vector of the straight line
       * @param Integer mu intercept of the straight line
       * @param Point A left-most bound of the CH
       * @param Point B right-most bound of the CH
       * @param Point* last-but-one point of the CH from left to right
       * @param Point* last point of the CH from left to right
       * @param Point* last point of the CH from right to left
       * @param Point* last-but-one point of the CH from right to left
       *
       */
      void lowerConvexHull(Vector l, Integer mu, Point A, Point B, Point *prevInfL, Point *infL, Point *infR, Point *prevInfR);
      
      /**
       * Compute the left part of the upper and lower convex hulls of
       * the line of directional vector l and intercept r, between x=0
       * and x=n. Returns the upper and lower closest
       * points. Implementation of Charrier and Buzer algorithm
       * (Discrete Applied Mathematics, 2009) 
       * @param Vector l directional vector of the line
       * @param Integer r intercept of the line
       * @param Integer n maximal value of x-coordinate
       * @param Point* inf closest point below the line
       * @param Point* sup closest point above the line
       */
      void convexHullApprox(Vector l, Integer r, Integer n, Point *inf, Point *sup);
      
      /**
       * Compute the left part of the upper and lower convex hulls of
       * the line of slope s, between x=0
       * and x=n. Returns the upper and lower closest points. 
       * @param Number s slope of the line (interpect is equal to zero here)
       * @param Integer n maximal value of x-coordinate
       * @param Point* inf closest point below the line
       * @param Point* sup closest point above the line
       */
      void convexHullApprox(Number s, Integer n, Point *inf, Point *sup);
      
      /**
       * Compute the left part of the upper and lower convex hulls of
       * the line of slope s, between x=0
       * and x=n. Returns the last two points computed.
       * Implementation of Charrier and Buzer algorithm
       * (Discrete Applied Mathematics, 2009)  
       * @param Vector l directional vector of the line
       * @param Integer r intercept of the line
       * @param Integer n maximal value of x-coordinate
       * @param Point* inf closest point below the line
       * @param Point* sup closest point above the line
       * @param Point* prevInf second-closest point below the line
       * @param Point* prevSup second-closest point above the line
       */
      void convexHullApproxTwoPoints(Vector l, Integer r, Integer n, Point *inf, Point *sup, Point *prevInf, Point *prevSup, bool inv);
      
      
      /**
       * Compute the left part of the upper and lower convex hulls of
       * the line of directional vector l, between x=0 and x=n. Returns
       * the last two points computed. Implementation of Har-Peled
       * algorithm (Computational Geometry: Theory and Applications, 1998)
       *
       * @param Vector l directional vector of the line (intercept is zero)
       * @param Integer n maximal value of x-coordinate
       * @param Point* inf closest point below the line
       * @param Point* sup closest point above the line
       */
      void convexHullHarPeled(Vector l, Integer n, Point *inf, Point *sup);
      
      
      /**
       * Compute the term following fp/fq in the Farey series of order n. 
       * @param Integer fp numerator
       * @param Integer fq denominator
       * @param Integer n order the the Farey Series
       * @return Point (q,p) such that p/q follows fp/fq in the Farey Series of order n
       */
      Point nextTermInFareySeriesEuclid(Integer fp, Integer fq, Integer n);
      
      
      /**
       * Compute the ray of highest slope passing through a given point
       * (p/q,r/q) in O(1) knowing the ray of smallest  
       * slope and the order of the Farey fan
       * @param Integer p numerator of x-coordinate
       * @param Integer q denominator of x- and y-coordinates
       * @param r numerator of y-coordinate
       * @param Integer smallestSlope of the rays passing through
       * (p/q,r/q)
       * @param Integer n order of the Farey fan
       * @return Ray
       */
      RayC rayOfHighestSlope(Integer p, Integer q, Integer r, Integer smallestSlope, Integer n);
      
      /**
       * Compute the ceil of the slope of the line through (f=p/q,r/q)
       * and point (a/b,mu/b) -  O(1) - Number must be an Integer type.
       * @param Integer p numerator of x-coordinate of the first point
       * @param Integer q denominator of x- and y-coordinates of the
       * first point
       * @param Integer r numerator of y-coordinate of the first point
       * @param Number a numerator of x-coordinate of the second point
       * @param Number b denominator of x- and y-coordinates of the
       * second point
       * @param Number mu numerator of y-coordinate of the second point
       * @return Integer ceil of the slope of the line passing through
       * the two points
       */
      Integer slope(Integer p, Integer q, Integer r, Number a, Number b, Number mu);
      
      /**
       * Compute the ceil of the slope of the line through (f=p/q,r/q)
       * and floating-point point (alpha,beta) -  O(1)
       *
       * @param Integer p numerator of x-coordinate of the first point
       * @param Integer q denominator of x- and y-coordinates of the
       * first point
       * @param Integer r numerator of y-coordinate of the first point
       * @param Number alpha x-coordinate of the second point
       * @param Number beta y-coordinate of the second point
       * @return Integer ceil of the slope of the line passing through
       * the two points
       */
      Integer slope(Integer p, Integer q, Integer r, Number alpha, Number beta);
      
      
      /**
       * Compute the position of the point (a/b,mu/b) with respect to a
       * ray r. Number must be an Integer type
       * @param Ray r
       * @param Number a numerator of x-coordinate
       * @param Number b denominator of x- and y-coordinates
       * @param Number mu numerator of x-coordinate
       * @return Potision equal to BELOW, ABOVE or ONTO
       */
      Position positionWrtRay(RayC r, Number a, Number b, Number mu);
      
      
      /**
       * Compute the position of the floating-point point(alpha,beta) with respect to a
       * ray r. 
       * @param Ray r
       * @param Number alpha x-coordinate
       * @param Number beta y-coordinate
       * @return Potision equal to BELOW, ABOVE or ONTO
       */
      Position positionWrtRay(RayC r, Number alpha, Number beta);
      
      /**
       * Computes the ray of smallest slope emanating from the point (f=p/q,
       * r/q) using the knowledge of the next fraction g in the Farey Series.
       * Complexity O(1)
       * @param Integer fp numerator of the point x-coordinate
       * @param Integer fq denominator of the point x- and
       * y-coordinates
       * @param Integer gp numerator of the fraction following fp/fq in
       * the Farey Series
       * @param Integer gq denominator of the fraction following fp/fq in
       * the Farey Series 
       * @param Integer r numerator of the point y-coordinate
       * @return Ray of smallest slope passing through the point
       */ 
      RayC smartRayOfSmallestSlope(Integer fp, Integer fq, Integer gp, Integer gq, Integer r); 
      
     
      /** 
       * Performs a dichotomy among the rays of smallest slope passing
       * through the points (fp/fq,r/fq), r in [0,fq] in order to locate
       * the point lambda(a/b,mu/b) in the ladder. Implements line 3 of
       * Algorithm 1 in [Sivignon, DGCI 2013]. Return an integer h such
       * that either i) lambda is in between the rays passing through
       * the point (fp/fq,h/fq) and flagRayFound is set to false or ii)
       * lambda is below all the rays passing through the point
       * (fp/fq,h+1/fq) and above all the rays passing through the point
       * (fp/fq,h/fq) and flagRayFound is set to false. In case i),
       * function localizeRay is used afterwards to localize lambda in
       * between the rays. In case ii), the
       * ray under lambda has been found and no further search is
       * needed. The Number type must verify the CInteger concept
       * (otherwise, see overloaded function). 
       * @param integer fp, numerator of the smallest fraction of the ladder
       * @param integer fq, denominator of the smallest fraction of the
       * ladder
       * @param integer gp, numerator of the greatest fraction of the
       * ladder
       * @param integer gq, denominator of the greatest fraction of the
       * ladder
       * @param number a
       * @param number b
       * @param number mu
       * @param integer n, order of the Farey Fan
       * @param pointer on a boolean, used to check whether localizeRay
       * should be called ot not
       * @return an integer 
       */
      Integer smartFirstDichotomy(Integer fp, Integer fq, Integer gp, Integer gq, Number a, Number b, Number mu, Integer n, bool *flagRayFound);
      
      /**  
       * Performs a dichotomy among the rays of smallest slope passing
       * through the points (fp/fq,r/fq), r in [0,fq] in order to locate
       * the point lambda(alpha,beta) in the ladder. Implements line 3 of
       * Algorithm 1 in [Sivignon, DGCI 2013]. Return an integer h such
       * that either i) lambda is in between the rays passing through
       * the point (fp/fq,h/fq) and flagRayFound is set to false or ii)
       * lambda is below all the rays passing through the point
       * (fp/fq,h+1/fq) and above all the rays passing through the point
       * (fp/fq,h/fq) and flagRayFound is set to false. In case i),
       * function localizeRay is used afterwards to localize lambda in
       * between the rays. In case ii), the
       * ray under lambda has been found and no further search is
       * needed. 
       * @param integer fp, numerator of the smallest fraction of the ladder
       * @param integer fq, denominator of the smallest fraction of the
       * ladder
       * @param integer gp, numerator of the greatest fraction of the
       * ladder
       * @param integer gq, denominator of the greatest fraction of the
       * ladder
       * @param number alpha
       * @param number beta
       * @param integer n, order of the Farey Fan
       * @param pointer on a boolean, used to check whether localizeRay
       * should be called ot not
       * @return integer 
       */
      Integer smartFirstDichotomy(Integer fp, Integer fq, Integer gp, Integer gq, Number alpha, Number beta, Integer n, bool *flagRayFound);
      
      
      
      /**
       * Compute the closest ray below the point (a/b,mu/b) passing
       * through the point (fp/fq,r/fq) in the Farey fan of order n
       *
       * @param integer fp, numerator of the smallest fraction of the ladder
       * @param integer fq, denominator of the smallest fraction of the
       * ladder
       * @param integer gp, numerator of the greatest fraction of the
       * ladder
       * @param integer gq, denominator of the greatest fraction of the
       * ladder
       * @param number a
       * @param number b
       * @param number mu
       * @param integer n, order of the Farey Fan
       * @return ray
       */
      RayC localizeRay(Integer fp, Integer fq, Integer gp, Integer gq, Integer r, Number a, Number b, Number mu,  Integer n);

      
      /**
       * Compute the closest ray below the point (alpha,beta) passing
       * through the point (fp/fq,r/fq) in the Farey fan of order n
       *
       * @param integer fp, numerator of the smallest fraction of the ladder
       * @param integer fq, denominator of the smallest fraction of the
       * ladder
       * @param integer gp, numerator of the greatest fraction of the
       * ladder
       * @param integer gq, denominator of the greatest fraction of the
       * ladder
       * @param number alpha
       * @param number beta
       * @param integer n, order of the Farey Fan
       * @return Ray
       */
      RayC localizeRay(Integer fp, Integer fq, Integer gp, Integer gq, Integer r, Number alpha, Number beta, Integer n);
      
      
      /**
       * Compute the ray passing through from (f=fp/fq,h/fq) just above
       * r. The knowledge of h is not necessary.
       * Complexity O(1)
       * 
       * @param integer fp
       * @param integer fq
       */
      
      RayC raySup(Integer fp, Integer fq, RayC r);
      
      
      /**
       * The two fractions f and g together with the ray r define a segment
       *  PQ. PQ is part of the lower boundary of exactly one cell of the
       *  FareyFan. This cell represents a DSS. This function computes the
       * vertex of the cell that represents the minimal characteristics
       *  of the DSS.
       * Optimized version of the algorithm presented in the paper
       *  "Walking in the Farey Fan to compute the characteristics of
       *  discrete straight line subsegment" (Isabelle Sivignon, DGCI
       *  2013, Springer LNCS 7749)
       * Complexity of nextTermInFareySeriesEuclid
       *
       * @param integer fp, numerator of the smallest fraction of the ladder
       * @param integer fq, denominator of the smallest fraction of the
       * ladder
       * @param integer gp, numerator of the greatest fraction of the
       * ladder
       * @param integer gq, denominator of the greatest fraction of the
       * ladder
       * @param ray r
       * @param integer n, order of the Farey Fan
       * @param Integer*  numerator of the x-coordinate of
       * the result
       * @param Integer*  denominator of the x- and y-
       * coordinates of the result
       * @param Integer* , numerator of the y-coordinate of
       * the result
       * @param Boolean found, used for optimization (true if r is the ray
       * of smallest slope on point P, false otherwise). Its value comes
       * from the smartFirstDichotomy function.
       */
      void findSolutionWithoutFractions(Integer fp, Integer fq, Integer gp, Integer gq, RayC r, Integer n, Integer *resAlphaP, Integer *resAlphaQ, Integer *resBetaP, bool found);  // resBetaQ = resAlphaQ  
      
      /**
       * Corresponds to the algorithm presented in "Walking in the Farey Fan
       * to compute the characteristics of  discrete straight line
       * subsegment" (Isabelle Sivignon, DGCI 2013, Springer LNCS 7749)
       *
       * @param integer fp, numerator of the smallest fraction of the ladder
       * @param integer fq, denominator of the smallest fraction of the
       * ladder
       * @param integer gp, numerator of the greatest fraction of the
       * ladder
       * @param integer gq, denominator of the greatest fraction of the
       * ladder
       * @param ray r
       * @param integer n, order of the Farey Fan
       * @param Integer* numerator of the x-coordinate of
       * the result
       * @param Integer* denominator of the x- and y-
       * coordinates of the result
       * @param Integer* numerator of the y-coordinate of
       * the result
       */
      void shortFindSolution(Integer fp, Integer fq, Integer gp, Integer gq, RayC r, Integer n, Integer *resAlphaP, Integer *resAlphaQ, Integer *resBetaP);  // resBetaQ = resAlphaQ  
      
      
      

      // ------------------------- Accessors ------------------------------
      
  public:
      
      /**
       * @return an Integer of value @a myA.
       */
      Integer getA() const;
      /**
       * @return an Integer of value @a myB.
       */
      Integer getB() const;
      /**
       * @return an Integer of value @a myMu.
       */
      Integer getMu() const;


  };
  
   
}// namespace DGtal



  //Includes inline functions.
#include "DSLSubsegment.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DSLSubsegment_h

#undef DSLSubsegment_RECURSES
#endif // else defined(DSLSubsegment_RECURSES)
