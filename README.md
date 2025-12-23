# ips-PROD

## 1. Installation

**WARNING :** the repertory `include` contains from-sources built libraries required for the project to run ('TestCxx', 'Armadillo' and also 'OpenBLAS' which is needed by 'Armadillo' itself). Those libraires have been compiled locally for this project specifically, and are pushed on this depository **only for demonstration purposes**. OpenBLAS requires to identify your CPU during its compilation, which ultimately will result in **a different build from the one on this depository !!**\
Make sure to follow the instructions below to generated libs adapted to your hardware.

### OpenBLAS

Clone OpenBLAS project from this url : `https://github.com/OpenMathLib/OpenBLAS` and follow the instructions.\
Basically, when you are in OpenBLAS's newly cloned repository, commands to enter in your shell should be :
* `make`
* `make PREFIX=/your/path/to/ips-DEV/include/OpenBLAS-lib install`

### Armadillo

Clone Armadillo project from this url : `https://gitlab.com/conradsnicta/armadillo-code`.\
Basically, when you are in armadillo's newly cloned repository,  commands to enter in your shell should be :
* `cmake . -DCMAKE_INSTALL_PREFIX:PATH=/your/path/to/ips-DEV/include/armadillo-lib`
* `make install`

Be careful that if you've installed OpenBLAS in a local/not standard folder, the cmake command may not find the location of the OpenBLAS' library. They must be a way to specify to camke its correct path but hey, I don't do cmake so I don't know how to do so.\
What you can do is to make an export of your `PATH` environment variable to add the location of the OpenBLAS's library (in our case, in `/your/path/to/ips-DEV/include/OpenBLAS-lib/lib`).

### Other dependencies

BLAS, g++, python, that kind of thing. Also a linux OS is mandatory.

### CxxTest

Clone CxxTest project for this url : `https://github.com/CxxTest/cxxtest`.\
Tests commands are already defined in the Makefile. They work only if the project is set inside the `include` directory.

## 2. Generation of the 3D solution

* `make init` in the root depository to generate the `obj` folder that will contain our necessary obj files for the build, the `out` for the executable and generated `df3`, and will also add the location of the OpenBLAS/armadillo libs to your `LD_LIBRARY_PATH`. Feel free to modify their path if you installed those lib in another place, or just delete the 'export' line if their are installed in your system's lib.
* `make all` to generate the executable in the `out` folder.
* `./out/main` to generate the df3.

## 3. Ploting solution using Pov-RAY

`make visu` to generate the density's view. Result is stored inside `visu.png` file.

## 4. Running unit tests

* `make tests` in the root depository to generate the test exzcutable in the `out` folder.
* `./out/tests` to run the unit tests.