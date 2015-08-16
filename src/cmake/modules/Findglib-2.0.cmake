# - Try to find glib2.0
# Once done this will define
#  glib-2.0_FOUND - System has glib-2.0
#  glib-2.0_INCLUDE_DIRS - The  glib-2.0 include directories
#  glib-2.0_LIBRARIES - The libraries needed to use glib-2.0
#  glib-2.0_DEFINITIONS - Compiler switches required for using glib-2.0

set(PACKAGE_NAME "glib-2.0")

find_package(PkgConfig)
pkg_check_modules(PC_GLIB QUIET glib-2.0)
set(${PACKAGE_NAME}_DEFINITIONS ${PC_GLIB_CFLAGS_OTHER})

find_path(${PACKAGE_NAME}_INCLUDE_DIR glib.h glibconfig.h
          HINTS ${PC_GLIB_INCLUDEDIR} ${PC_GLIB_INCLUDE_DIRS})
find_path(${PACKAGE_NAME}_CONFIG_INCLUDE_DIR glibconfig.h
          HINTS ${PC_GLIB_INCLUDEDIR} ${PC_GLIB_INCLUDE_DIRS})

find_library(${PACKAGE_NAME}_LIBRARY NAMES glib-2.0
             HINTS ${PC_GLIB_LIBDIR} ${PC_GLIB_LIBRARY_DIRS} )

set(${PACKAGE_NAME}_LIBRARIES ${${PACKAGE_NAME}_LIBRARY} )
set(${PACKAGE_NAME}_INCLUDE_DIRS ${${PACKAGE_NAME}_INCLUDE_DIR} ${${PACKAGE_NAME}_CONFIG_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set glib-2.0_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(${PACKAGE_NAME} DEFAULT_MSG
                                  ${PACKAGE_NAME}_LIBRARIES
                                  ${PACKAGE_NAME}_INCLUDE_DIRS)

mark_as_advanced(${PACKAGE_NAME}_INCLUDE_DIRS ${PACKAGE_NAME}_LIBRARIES ${PACKAGE_NAME}_DEFINITIONS )

