add_subdirectory(determinant)

set(DGTAL_TESTS_SRC
  testRayIntersection
  testPreimage
  testSphericalAccumulator
  testHullFunctions2D
  testPolarPointComparatorBy2x2DetComputer
  testConvexHull2D
  testConvexHull2DThickness
  testConvexHull2DReverse)

set(DGTAL_TESTS_QSRC
  testSphericalAccumulatorQGL)

foreach(FILE ${DGTAL_TESTS_SRC})
  DGtal_add_test(${FILE})
endforeach()


if (WITH_VISU3D_QGLVIEWER)
  foreach(FILE ${DGTAL_TESTS_QSRC})
    DGtal_add_test(${FILE} ONLY_ADD_EXECUTABLE)
  endforeach()
endif()
