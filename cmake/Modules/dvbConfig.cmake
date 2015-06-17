INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_DVB dvb)

FIND_PATH(
    DVB_INCLUDE_DIRS
    NAMES dvb/api.h
    HINTS $ENV{DVB_DIR}/include
        ${PC_DVB_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    DVB_LIBRARIES
    NAMES gnuradio-dvb
    HINTS $ENV{DVB_DIR}/lib
        ${PC_DVB_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DVB DEFAULT_MSG DVB_LIBRARIES DVB_INCLUDE_DIRS)
MARK_AS_ADVANCED(DVB_LIBRARIES DVB_INCLUDE_DIRS)

