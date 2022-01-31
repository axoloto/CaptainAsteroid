########## MACROS ###########################################################################
#############################################################################################


macro(conan_find_apple_frameworks FRAMEWORKS_FOUND FRAMEWORKS FRAMEWORKS_DIRS)
    if(APPLE)
        foreach(_FRAMEWORK ${FRAMEWORKS})
            # https://cmake.org/pipermail/cmake-developers/2017-August/030199.html
            find_library(CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND NAME ${_FRAMEWORK} PATHS ${FRAMEWORKS_DIRS} CMAKE_FIND_ROOT_PATH_BOTH)
            if(CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND)
                list(APPEND ${FRAMEWORKS_FOUND} ${CONAN_FRAMEWORK_${_FRAMEWORK}_FOUND})
            else()
                message(FATAL_ERROR "Framework library ${_FRAMEWORK} not found in paths: ${FRAMEWORKS_DIRS}")
            endif()
        endforeach()
    endif()
endmacro()


function(conan_package_library_targets libraries package_libdir deps out_libraries out_libraries_target build_type package_name)
    unset(_CONAN_ACTUAL_TARGETS CACHE)
    unset(_CONAN_FOUND_SYSTEM_LIBS CACHE)
    foreach(_LIBRARY_NAME ${libraries})
        find_library(CONAN_FOUND_LIBRARY NAME ${_LIBRARY_NAME} PATHS ${package_libdir}
                     NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
        if(CONAN_FOUND_LIBRARY)
            conan_message(STATUS "Library ${_LIBRARY_NAME} found ${CONAN_FOUND_LIBRARY}")
            list(APPEND _out_libraries ${CONAN_FOUND_LIBRARY})
            if(NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
                # Create a micro-target for each lib/a found
                string(REGEX REPLACE "[^A-Za-z0-9.+_-]" "_" _LIBRARY_NAME ${_LIBRARY_NAME})
                set(_LIB_NAME CONAN_LIB::${package_name}_${_LIBRARY_NAME}${build_type})
                if(NOT TARGET ${_LIB_NAME})
                    # Create a micro-target for each lib/a found
                    add_library(${_LIB_NAME} UNKNOWN IMPORTED)
                    set_target_properties(${_LIB_NAME} PROPERTIES IMPORTED_LOCATION ${CONAN_FOUND_LIBRARY})
                    set(_CONAN_ACTUAL_TARGETS ${_CONAN_ACTUAL_TARGETS} ${_LIB_NAME})
                else()
                    conan_message(STATUS "Skipping already existing target: ${_LIB_NAME}")
                endif()
                list(APPEND _out_libraries_target ${_LIB_NAME})
            endif()
            conan_message(STATUS "Found: ${CONAN_FOUND_LIBRARY}")
        else()
            conan_message(STATUS "Library ${_LIBRARY_NAME} not found in package, might be system one")
            list(APPEND _out_libraries_target ${_LIBRARY_NAME})
            list(APPEND _out_libraries ${_LIBRARY_NAME})
            set(_CONAN_FOUND_SYSTEM_LIBS "${_CONAN_FOUND_SYSTEM_LIBS};${_LIBRARY_NAME}")
        endif()
        unset(CONAN_FOUND_LIBRARY CACHE)
    endforeach()

    if(NOT ${CMAKE_VERSION} VERSION_LESS "3.0")
        # Add all dependencies to all targets
        string(REPLACE " " ";" deps_list "${deps}")
        foreach(_CONAN_ACTUAL_TARGET ${_CONAN_ACTUAL_TARGETS})
            set_property(TARGET ${_CONAN_ACTUAL_TARGET} PROPERTY INTERFACE_LINK_LIBRARIES "${_CONAN_FOUND_SYSTEM_LIBS};${deps_list}")
        endforeach()
    endif()

    set(${out_libraries} ${_out_libraries} PARENT_SCOPE)
    set(${out_libraries_target} ${_out_libraries_target} PARENT_SCOPE)
endfunction()


########### VARIABLES #######################################################################
#############################################################################################


set(spdlog_INCLUDE_DIRS_RELEASE "C:/Users/adrid/.conan/data/spdlog/1.9.2/_/_/package/26b885d7ef0883598f1d5dc9d2e504e10115011f/include")
set(spdlog_INCLUDE_DIR_RELEASE "C:/Users/adrid/.conan/data/spdlog/1.9.2/_/_/package/26b885d7ef0883598f1d5dc9d2e504e10115011f/include")
set(spdlog_INCLUDES_RELEASE "C:/Users/adrid/.conan/data/spdlog/1.9.2/_/_/package/26b885d7ef0883598f1d5dc9d2e504e10115011f/include")
set(spdlog_RES_DIRS_RELEASE )
set(spdlog_DEFINITIONS_RELEASE "-DSPDLOG_COMPILED_LIB"
			"-DSPDLOG_FMT_EXTERNAL")
set(spdlog_LINKER_FLAGS_RELEASE_LIST
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:>"
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:>"
        "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:>"
)
set(spdlog_COMPILE_DEFINITIONS_RELEASE "SPDLOG_COMPILED_LIB"
			"SPDLOG_FMT_EXTERNAL")
set(spdlog_COMPILE_OPTIONS_RELEASE_LIST "" "")
set(spdlog_COMPILE_OPTIONS_C_RELEASE "")
set(spdlog_COMPILE_OPTIONS_CXX_RELEASE "")
set(spdlog_LIBRARIES_TARGETS_RELEASE "") # Will be filled later, if CMake 3
set(spdlog_LIBRARIES_RELEASE "") # Will be filled later
set(spdlog_LIBS_RELEASE "") # Same as spdlog_LIBRARIES
set(spdlog_SYSTEM_LIBS_RELEASE )
set(spdlog_FRAMEWORK_DIRS_RELEASE )
set(spdlog_FRAMEWORKS_RELEASE )
set(spdlog_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
set(spdlog_BUILD_MODULES_PATHS_RELEASE )

conan_find_apple_frameworks(spdlog_FRAMEWORKS_FOUND_RELEASE "${spdlog_FRAMEWORKS_RELEASE}" "${spdlog_FRAMEWORK_DIRS_RELEASE}")

mark_as_advanced(spdlog_INCLUDE_DIRS_RELEASE
                 spdlog_INCLUDE_DIR_RELEASE
                 spdlog_INCLUDES_RELEASE
                 spdlog_DEFINITIONS_RELEASE
                 spdlog_LINKER_FLAGS_RELEASE_LIST
                 spdlog_COMPILE_DEFINITIONS_RELEASE
                 spdlog_COMPILE_OPTIONS_RELEASE_LIST
                 spdlog_LIBRARIES_RELEASE
                 spdlog_LIBS_RELEASE
                 spdlog_LIBRARIES_TARGETS_RELEASE)

# Find the real .lib/.a and add them to spdlog_LIBS and spdlog_LIBRARY_LIST
set(spdlog_LIBRARY_LIST_RELEASE spdlog)
set(spdlog_LIB_DIRS_RELEASE "C:/Users/adrid/.conan/data/spdlog/1.9.2/_/_/package/26b885d7ef0883598f1d5dc9d2e504e10115011f/lib")

# Gather all the libraries that should be linked to the targets (do not touch existing variables):
set(_spdlog_DEPENDENCIES_RELEASE "${spdlog_FRAMEWORKS_FOUND_RELEASE} ${spdlog_SYSTEM_LIBS_RELEASE} fmt::fmt")

conan_package_library_targets("${spdlog_LIBRARY_LIST_RELEASE}"  # libraries
                              "${spdlog_LIB_DIRS_RELEASE}"      # package_libdir
                              "${_spdlog_DEPENDENCIES_RELEASE}"  # deps
                              spdlog_LIBRARIES_RELEASE            # out_libraries
                              spdlog_LIBRARIES_TARGETS_RELEASE    # out_libraries_targets
                              "_RELEASE"                          # build_type
                              "spdlog")                                      # package_name

set(spdlog_LIBS_RELEASE ${spdlog_LIBRARIES_RELEASE})

foreach(_FRAMEWORK ${spdlog_FRAMEWORKS_FOUND_RELEASE})
    list(APPEND spdlog_LIBRARIES_TARGETS_RELEASE ${_FRAMEWORK})
    list(APPEND spdlog_LIBRARIES_RELEASE ${_FRAMEWORK})
endforeach()

foreach(_SYSTEM_LIB ${spdlog_SYSTEM_LIBS_RELEASE})
    list(APPEND spdlog_LIBRARIES_TARGETS_RELEASE ${_SYSTEM_LIB})
    list(APPEND spdlog_LIBRARIES_RELEASE ${_SYSTEM_LIB})
endforeach()

# We need to add our requirements too
set(spdlog_LIBRARIES_TARGETS_RELEASE "${spdlog_LIBRARIES_TARGETS_RELEASE};fmt::fmt")
set(spdlog_LIBRARIES_RELEASE "${spdlog_LIBRARIES_RELEASE};fmt::fmt")

set(CMAKE_MODULE_PATH "C:/Users/adrid/.conan/data/spdlog/1.9.2/_/_/package/26b885d7ef0883598f1d5dc9d2e504e10115011f/" ${CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH "C:/Users/adrid/.conan/data/spdlog/1.9.2/_/_/package/26b885d7ef0883598f1d5dc9d2e504e10115011f/" ${CMAKE_PREFIX_PATH})

set(spdlog_COMPONENTS_RELEASE spdlog::libspdlog)

########### COMPONENT libspdlog VARIABLES #############################################

set(spdlog_libspdlog_INCLUDE_DIRS_RELEASE "C:/Users/adrid/.conan/data/spdlog/1.9.2/_/_/package/26b885d7ef0883598f1d5dc9d2e504e10115011f/include")
set(spdlog_libspdlog_INCLUDE_DIR_RELEASE "C:/Users/adrid/.conan/data/spdlog/1.9.2/_/_/package/26b885d7ef0883598f1d5dc9d2e504e10115011f/include")
set(spdlog_libspdlog_INCLUDES_RELEASE "C:/Users/adrid/.conan/data/spdlog/1.9.2/_/_/package/26b885d7ef0883598f1d5dc9d2e504e10115011f/include")
set(spdlog_libspdlog_LIB_DIRS_RELEASE "C:/Users/adrid/.conan/data/spdlog/1.9.2/_/_/package/26b885d7ef0883598f1d5dc9d2e504e10115011f/lib")
set(spdlog_libspdlog_RES_DIRS_RELEASE )
set(spdlog_libspdlog_DEFINITIONS_RELEASE "-DSPDLOG_COMPILED_LIB"
			"-DSPDLOG_FMT_EXTERNAL")
set(spdlog_libspdlog_COMPILE_DEFINITIONS_RELEASE "SPDLOG_COMPILED_LIB"
			"SPDLOG_FMT_EXTERNAL")
set(spdlog_libspdlog_COMPILE_OPTIONS_C_RELEASE "")
set(spdlog_libspdlog_COMPILE_OPTIONS_CXX_RELEASE "")
set(spdlog_libspdlog_LIBS_RELEASE spdlog)
set(spdlog_libspdlog_SYSTEM_LIBS_RELEASE )
set(spdlog_libspdlog_FRAMEWORK_DIRS_RELEASE )
set(spdlog_libspdlog_FRAMEWORKS_RELEASE )
set(spdlog_libspdlog_BUILD_MODULES_PATHS_RELEASE )
set(spdlog_libspdlog_DEPENDENCIES_RELEASE fmt::fmt)
set(spdlog_libspdlog_LINKER_FLAGS_LIST_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:>
)

########## COMPONENT libspdlog FIND LIBRARIES & FRAMEWORKS / DYNAMIC VARS #############

set(spdlog_libspdlog_FRAMEWORKS_FOUND_RELEASE "")
conan_find_apple_frameworks(spdlog_libspdlog_FRAMEWORKS_FOUND_RELEASE "${spdlog_libspdlog_FRAMEWORKS_RELEASE}" "${spdlog_libspdlog_FRAMEWORK_DIRS_RELEASE}")

set(spdlog_libspdlog_LIB_TARGETS_RELEASE "")
set(spdlog_libspdlog_NOT_USED_RELEASE "")
set(spdlog_libspdlog_LIBS_FRAMEWORKS_DEPS_RELEASE ${spdlog_libspdlog_FRAMEWORKS_FOUND_RELEASE} ${spdlog_libspdlog_SYSTEM_LIBS_RELEASE} ${spdlog_libspdlog_DEPENDENCIES_RELEASE})
conan_package_library_targets("${spdlog_libspdlog_LIBS_RELEASE}"
                              "${spdlog_libspdlog_LIB_DIRS_RELEASE}"
                              "${spdlog_libspdlog_LIBS_FRAMEWORKS_DEPS_RELEASE}"
                              spdlog_libspdlog_NOT_USED_RELEASE
                              spdlog_libspdlog_LIB_TARGETS_RELEASE
                              "RELEASE"
                              "spdlog_libspdlog")

set(spdlog_libspdlog_LINK_LIBS_RELEASE ${spdlog_libspdlog_LIB_TARGETS_RELEASE} ${spdlog_libspdlog_LIBS_FRAMEWORKS_DEPS_RELEASE})