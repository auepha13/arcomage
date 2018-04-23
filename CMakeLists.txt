#------------------------------------------------------------------------------
# Arcomage Tribute
# Part of the Arcomage Tribute CMake Build System.
#------------------------------------------------------------------------------
# Main Build Configuration File
#------------------------------------------------------------------------------
# Include some CMake functions
INCLUDE(CheckLibraryExists)
INCLUDE(CheckIncludeFile)
INCLUDE(CheckIncludeFileCXX)
INCLUDE(CheckCCompilerFlag)
INCLUDE(CheckCSourceCompiles)

#------------------------------------------------------------------------------
project(ArcomageTribute)
  
cmake_minimum_required(VERSION 2.8)

 
add_subdirectory(Game)
# No Cmake files (yet)
# add_subdirectory(Tools)
