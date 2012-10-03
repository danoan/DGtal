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

/**
 * @file greedy-plane-segmentation.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/03/25
 *
 * An example file named greedy-plane-segmentation.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

#include <QtGui/qapplication.h>
#include "DGtal/base/Common.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/Display3D.h"

#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/arithmetic/COBANaivePlane.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/DigitalSetBoundary.h"
#include "DGtal/topology/BreadthFirstVisitor.h"
//#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
namespace po = boost::program_options;


///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
  using namespace Z3i;

  //! [greedy-plane-segmentation-parseCommandLine]
  // parse command line ----------------------------------------------
  po::options_description general_opt("Allowed options are: ");
  general_opt.add_options()
    ("help,h", "display this message")
    ("input-file,i", po::value<std::string>()->default_value( examplesPath + "samples/Al.100.vol" ), "the volume file (.vol)" )
    ("threshold,t",  po::value<unsigned int>()->default_value(1), "the value that defines the isosurface in the image (an integer between 0 and 255)." )
    ("width-num,w",  po::value<unsigned int>()->default_value(1), "the numerator of the rational width (a non-null integer)." )
    ("width-den,d",  po::value<unsigned int>()->default_value(1), "the denominator of the rational width (a non-null integer)." );
  
  bool parseOK = true;
  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc, argv, general_opt), vm);  
  } catch ( const std::exception & ex ) {
    parseOK = false;
    trace.info() << "Error checking program options: "<< ex.what()<< endl;
  }
  po::notify(vm);
  if ( ! parseOK || vm.count("help") || ( argc <= 1 ) )
    {
      std::cout << "Usage: " << argv[0]
                << " [-i <fileName.vol>] [-t <threshold>] [-w <num>] [-d <den>]" << std::endl
                << "Segments the surface at given threshold within given volume into digital planes of rational width num/den." << std::endl
                << general_opt << std::endl;
      return 0;
    }
  string inputFilename = vm["input-file"].as<std::string>();
  unsigned int threshold = vm["threshold"].as<unsigned int>();
  unsigned int widthNum = vm["width-num"].as<unsigned int>();
  unsigned int widthDen = vm["width-den"].as<unsigned int>();
  //! [greedy-plane-segmentation-parseCommandLine]

  //! [greedy-plane-segmentation-loadVolume]
  QApplication application(argc,argv);
  typedef ImageSelector < Domain, int>::Type Image;
  Image image = VolReader<Image>::importVol(inputFilename);
  DigitalSet set3d (image.domain());
  SetFromImage<DigitalSet>::append<Image>(set3d, image, threshold,255);
  //! [greedy-plane-segmentation-loadVolume]

  //! [greedy-plane-segmentation-makeSurface]
  trace.beginBlock( "Set up digital surface." );
  // We initializes the cellular grid space used for defining the
  // digital surface.
  KSpace ks;
  bool ok = ks.init( set3d.domain().lowerBound(),
                     set3d.domain().upperBound(), true );
  if ( ! ok ) std::cerr << "[KSpace.init] Failed." << std::endl;
  // We choose the DigitalSetBoundary surface container in order to
  // segment connected or unconnected surfaces.
  typedef DigitalSetBoundary<KSpace,DigitalSet> MyDigitalSurfaceContainer;
  typedef DigitalSurface<MyDigitalSurfaceContainer> MyDigitalSurface;
  SurfelAdjacency<KSpace::dimension> surfAdj( true ); // interior in all directions.
  MyDigitalSurfaceContainer* ptrSurfContainer = 
    new MyDigitalSurfaceContainer( ks, set3d, surfAdj );
  MyDigitalSurface digSurf( ptrSurfContainer ); // acquired
  trace.endBlock();
  //! [greedy-plane-segmentation-makeSurface]

  //! [greedy-plane-segmentation-typedefs]
  typedef int64_t Integer;
  typedef COBANaivePlane<Z3,Integer> NaivePlaneComputer;
  typedef MyDigitalSurface::ConstIterator ConstIterator;
  typedef MyDigitalSurface::Vertex Vertex;
  typedef MyDigitalSurface::SurfelSet SurfelSet;
  typedef SurfelSet::iterator SurfelSetIterator;
  struct SegmentedPlane {
    NaivePlaneComputer plane;
    Color color;
  };
  typedef BreadthFirstVisitor<MyDigitalSurface> Visitor;
  //! [greedy-plane-segmentation-typedefs]

  //! [greedy-plane-segmentation-segment]
  trace.beginBlock( "Segment into planes." );
  std::set<Vertex> processedVertices;
  std::vector<SegmentedPlane> segmentedPlanes;
  std::map<Vertex,SegmentedPlane*> v2plane;
  Point p;
  Dimension axis;
  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int nb = digSurf.size();
  for ( ConstIterator it = digSurf.begin(), itE= digSurf.end(); it != itE; ++it )
    {
      if ( ( (++j) % 50 == 0 ) || ( j == nb ) ) trace.progressBar( j, nb );
      Vertex v = *it;
      if ( processedVertices.find( v ) != processedVertices.end() ) // already in set
        continue; // process to next vertex
      
      segmentedPlanes.resize( ++i );
      SegmentedPlane & segment = segmentedPlanes.back();
      axis = ks.sOrthDir( v );
      segment.plane.init( axis, 500, widthNum, widthDen );
      // The visitor takes care of all the breadth-first traversal.
      Visitor visitor( digSurf, v );
      while ( ! visitor.finished() )
        {
          Visitor::Node node = visitor.current();
          v = node.first;
          if ( processedVertices.find( v ) == processedVertices.end() )
            { // Vertex is not in processedVertices
              axis = ks.sOrthDir( v );
              p = ks.sCoords( ks.sDirectIncident( v, axis ) );
              bool isExtended = segment.plane.extend( p );
              if ( isExtended ) 
                { // surfel is in plane.
                  processedVertices.insert( v );
                  v2plane[ v ] = &segment;
                  visitor.expand();
                }
              else // surfel is not in plane and should not be used in the visit.
                visitor.ignore();
            }
          else // surfel is already in some plane.
            visitor.ignore();
        }
      // Assign random color for each plane.
      segment.color = Color( random() % 256, random() % 256, random() % 256, 255 );
    }
  trace.endBlock();
  //! [greedy-plane-segmentation-segment]

  //! [greedy-plane-segmentation-visualization]
  Viewer3D viewer;
  viewer.show(); 
  for ( std::map<Vertex,SegmentedPlane*>::const_iterator 
          it = v2plane.begin(), itE = v2plane.end();
        it != itE; ++it )
    {
      viewer << CustomColors3D( it->second->color, it->second->color )
             << it->first;
    }
  viewer << Display3D::updateDisplay;
  //! [greedy-plane-segmentation-visualization]
  return application.exec();
}
///////////////////////////////////////////////////////////////////////////////
