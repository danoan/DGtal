if (WITH_CAIRO AND WITH_EIGEN AND WITH_QGLVIEWER)

    set(DGTAL_EXAMPLES_SRC_DEC
        exampleDECSurface
        exampleDiscreteExteriorCalculusUsage
        exampleDiscreteExteriorCalculusSolve
        exampleDiscreteExteriorCalculusChladni
        exampleHeatLaplace
        )

    foreach(FILE ${DGTAL_EXAMPLES_SRC_DEC})
        add_executable(${FILE} ${FILE})
        target_link_libraries (${FILE} DGtal ${DGtalLibDependencies})
    endforeach()

endif()

if (WITH_EIGEN)
	set(DGTAL_EXAMPLES_SRC2_DEC
        examplePropagation
	exampleSurfaceATNormals
        )

    foreach(FILE ${DGTAL_EXAMPLES_SRC2_DEC})
        add_executable(${FILE} ${FILE})
        target_link_libraries (${FILE} DGtal ${DGtalLibDependencies})
    endforeach()
endif()
