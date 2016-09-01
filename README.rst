This is a project to try and automatically translate CellML models into the required `BeatBox <http://empslocal.ex.ac.uk/people/staff/vnb262/software/BeatBox/>`_ source files.
Please consider this very much a **work in progress**.

Building from Source
====================

The following is a list of requirements required for building on all platforms

 #. Toolchain (Visual Studio, GNU/GCC, Clang)
 #. Git distributed version control system
 #. CMake version 3.3 or greater

CellML2BeatBox uses a super build system to build all requirements and c2bb itself.  This is a two stage process, first the requirements are configured and built and second c2bb is configured and built.

For all systems first acquire the c2bb source code::

  git clone --recursive https://github.com/nickerso/c2bb [here]

then create a sibling directory to the source where all the building of c2bb will take place::

  mkdir build
  cd build

See the platform specific section for the configuration and build phase of c2bb.  The default build of c2bb is a release build use the CMAKE_BUILD_TYPE variable to configure the build type for c2bb's requirements and C2BB_BUILD_TYPE to configure the build type for c2bb itself.  This of course is only relevant to single configuration builds like ninja and make.

Windows
-------

Ninja Generator
+++++++++++++++

When choosing to use the Ninja generator on Windows make sure you set the environment correctly using the ``vcvarsall.bat`` script, for example to set a 64 bit build for Visual Studio 2015 in a cmd window::

"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64

Configure the requirements build (or phase 1)::

  cmake -G Ninja ..\c2bb

start the requirements build::

  cmake --build .

(Don't forget the fullstop at the end of the command above it is important.)

Next configure c2bb::

  cmake -G Ninja -DUSE_SUPERBUILD=FALSE -DC2BB_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=<absoulte-path-to-build-directory>/local/cmake -DBUILD_TESTING=TRUE ..\c2bb

start the build::

  cmake --build .

To check the build run the tests with the following command::

  ctest

Visual Studio
+++++++++++++

Follow these instructions for building 64 bit CSim from the command line using Visual Studio.

Configure the requirements build::

  cmake -G"Visual Studio 14 2015 Win64" ..\c2bb

start the requirements build::

  cmake --build . --config Release

Next configure c2bb::

  cmake -G"Visual Studio 14 2015 Win64" -DUSE_SUPERBUILD=FALSE -DC2BB_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=<absoulte-path-to-build-directory>/local/cmake -DBUILD_TESTING=TRUE ..\c2bb

start the build::

  cmake --build .  --config Release

To check the build run the tests with the following command::

  ctest

It is also possible to build c2bb from the Visual Studio solution in the build directory.
