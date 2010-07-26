# Install script for directory: $(SRCROOT)/Samples

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "$(SRCROOT)")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("$(SRCROOT)/Samples/BSP/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/CelShading/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/BezierPatch/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/CameraTrack/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/Character/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/Compositor/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/CubeMapping/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/Dot3Bump/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/DynTex/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/FacialAnimation/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/Fresnel/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/Grass/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/Instancing/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/Lighting/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/OceanDemo/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/ParticleFX/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/ShaderSystem/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/Shadows/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/SkeletalAnimation/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/SkyBox/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/SkyDome/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/SkyPlane/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/Smoke/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/SphereMapping/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/Terrain/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/TextureFX/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/Transparency/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/VolumeTex/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/Water/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/DeferredShading/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/Isosurf/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/ParticleGS/cmake_install.cmake")
  INCLUDE("$(SRCROOT)/Samples/Browser/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

