# Vol 1.5

[![A COIN-OR Project](https://coin-or.github.io/coin-or-badge.png)](https://www.coin-or.org)

Projects such as this one are maintained by a small group of volunteers under
the auspices of the non-profit [COIN-OR Foundation](https://www.coin-or.org)
and we need your help! Please consider [sponsoring our
activities](https://github.com/sponsors/coin-or) or [volunteering](mailto:volunteer@coin-or.org) to help!

[![Latest Release](https://img.shields.io/github/v/release/coin-or/Vol?sort=semver)](https://github.com/coin-or/Vol/releases)

_This file is auto-generated from [config.yml](.coin-or/config.yml) using the 
[generate_readme](.coin-or/generate_readme) script.
To make changes, please edit [config.yml](.coin-or/config.yml) or the generation scripts
[here](.coin-or/generate_readme) and [here](https://github.com/coin-or/coinbrew/blob/master/scripts/generate_readme)._

Vol (Volume Algorithm) is an open-source implementation of a subgradient
method that produces primal as well as dual solutions. The primal solution
comes from estimating the volumes below the faces of the dual problem. This is
an approximate method so the primal vector might have small infeasiblities
that are negligible in many practical settings. The original subgradient
algorithm produces only dual solutions.

Vol consists of the library `libVol`, which implements the Volume Algorithm,
and `libOsiVol`, an [Osi](https://github.com/coin-or/Osi) interface to it.

Vol is written in C++ and is released as open source under the [Eclipse Public License 2.0](http://www.opensource.org/licenses/EPL-2.0).

It is distributed under the auspices of the [COIN-OR Foundation](https://www.coin-or.org).

The Vol development site is https://github.com/coin-or/Vol.

## CURRENT BUILD STATUS

[![Windows Builds](https://github.com/coin-or/Vol/actions/workflows/windows-ci.yml/badge.svg?branch=stable/1.5)](https://github.com/coin-or/Vol/actions/workflows/windows-ci.yml?query=branch%3Astable/1.5)

[![Linux and MacOS Builds](https://github.com/coin-or/Vol/actions/workflows/linux-ci.yml/badge.svg?branch=stable/1.5)](https://github.com/coin-or/Vol/actions/workflows/linux-ci.yml?query=branch%3Astable/1.5)

## DOWNLOAD

What follows is a quick start guide for obtaining or building
Vol on common platforms. More detailed information is
available [here](https://coin-or.github.io/user_introduction.html).

### Docker image

There is a Docker image that provides Vol, as well as other projects
in the [COIN-OR Optimization
Suite](https://github.com/coin-or/COIN-OR-OptimizationSuite) [here](https://hub.docker.com/repository/docker/coinor/coin-or-optimization-suite)

### Binaries

For newer releases, binaries will be made available as assets attached to
releases in Github
[here](https://github.com/coin-or/Vol/releases). Older binaries
are archived as part of Vol
[here](https://www.coin-or.org/download/binary/Vol).

 * *Linux* (see https://repology.org/project/coin-or-vol/versions for a complete listing): 
   * arch:
     ```
     $ sudo pacman -S  coin-or-vol
     ```
   * Debian/Ubuntu:
     ```
     $ sudo apt-get install  coinor-libvol-dev
     ```
   * Fedora/Redhat/CentOS:
     ```
     $ sudo dnf install  coin-or-Vol coin-or-Vol-devel
     ```
 * *Windows*: The easiest way to get Vol on Windows is to download an archive as described above.
 * *Mac OS X*: The easiest way to get Vol on Mac OS X is through [Homebrew](https://brew.sh).
     ```
     $ brew tap coin-or-tools/coinor
     $ brew install coin-or-tools/coinor/vol
     ```

Due to license incompatibilities, pre-compiled binaries lack some 
functionality. If binaries are not available for your platform for the latest 
version and you would like to request them to be built and posted, feel free 
to open a discussion on Github. 

### Source

Source code can be obtained either by

 * Downloading a snapshot of the source code for the latest release version of Vol from the
 [releases](https://github.com/coin-or/Vol/releases) page,
 * Cloning this repository from [Github](https://github.com/coin-or/Vol), or 
 * Using the [coinbrew](https://github.com/coin-or/coinbrew) script to get the project and all dependencies (recommended, see below).   

### Dependencies

Vol has a number of dependencies, which are detailed in
[config.yml](.coin-or/config.yml). Dependencies on other COIN-OR projects are
automatically downloaded when obtaining the source with `coinbrew`. For some
of the remaining third-party dependencies, automatic download scripts and
build wrappers are provided (and will also be automatically run for required
and recommended dependencies), while other libraries that are aeasy to obtain
must be installed using an appropriate package manager (or may come with your
OS by default). 

## BUILDING from source

These quick start instructions assume you are in a bash shell. 

### Using `coinbrew`

To download and build Vol from source, execute the 
following on the command line. 
```
wget https://raw.githubusercontent.com/coin-or/coinbrew/master/coinbrew
chmod u+x coinbrew
./coinbrew fetch Vol@1.5
./coinbrew build Vol
```
For more detailed instructions on coinbrew, see https://coin-or.github.io/coinbrew.
The `coinbrew` script will fetch the additional projects specified in the Dependencies section of [config.yml](.coin-or/config.yml).

### Without `coinbrew` (Expert users)

 * Download the source code, e.g., by cloning the git repo https://github.com/coin-or/Vol
 * Download and install the source code for the dependencies listed in [config.yml](.coin-or/config.yml)
 * Build the code as follows (make sure to set PKG_CONFIG_PTH to install directory for dependencies).

```
./configure -C
make
make test
make install
```

### Examples

The `examples` directory has three applications of Vol:
 * `VolUfl`: uncapacitated facility location,
 * `Volume-LP`: approximate solutions of linear programs,
 * `VolLp`: approximate solutions of linear programs read from MPS files.

After building and installing Vol, the examples can be built by running
`make` in the corresponding subdirectory of the build directory, e.g.,
```
cd build/Vol/1.5/examples/VolUfl
make
./ufl
```

## Doxygen Documentation

If you have `Doxygen` available, you can build a HTML documentation by typing

`make doxydoc` 

in the build directory. If Vol was built via `coinbrew`, then the build
directory will be `./build/Vol/1.5` by default. The doxygen documentation main file
is found at `<build-dir>/doxydoc/html/index.html`.

If you don't have `doxygen` installed locally, you can use also find the
documentation [here](http://coin-or.github.io/Vol/Doxygen).

## Documentation

 * [Overview of different directories](Vol/doc/volDoc.pdf)
 * [The Volume Algorithm: Producing Primal Solutions With a Subgradient Method](http://domino.watson.ibm.com/library/cyberdig.nsf/a3807c5b4823c53f85256561006324be/7a1b25774639540a852565be0070cfb5?OpenDocument)
 * [On Some Difficult Linear Programs Coming from Set Partitioning](http://domino.watson.ibm.com/library/cyberdig.nsf/a3807c5b4823c53f85256561006324be/53731ca97769f3838525672f0070dc2b?OpenDocument)
 * [Solving Large Scale Uncapacitated Facility Location Problems](http://domino.watson.ibm.com/library/cyberdig.nsf/a3807c5b4823c53f85256561006324be/08e1ac62bb877f9a852567b500500996?OpenDocument)
 * [Near-Optimal Solutions to Large Scale Facility Location Problems](http://domino.watson.ibm.com/library/cyberdig.nsf/a3807c5b4823c53f85256561006324be/215bca4e7e2406ec852568430076860c?OpenDocument)
 * [Solving Steiner Tree Problems in Graphs with Lagrangian Relaxation](http://domino.watson.ibm.com/library/cyberdig.nsf/a3807c5b4823c53f85256561006324be/4a61544906b57a6d8525696c0057f955?OpenDocument&Highlight=0,barahona)

## FAQ

### For what type of problems has Vol been used?

It has been tested with a variety of combinatorial problems like: Crew
scheduling, Fleet assignment, Facility location, Steiner trees, Max-Cut,
Quadratic knapsack.

### Can one solve a linear program with Vol?

One can get good and fast approximate solutions for combinatorial linear
programs. These are LP's where all variables are between 0 and 1.

### Can one solve integer programs with Vol?

Vol gives bounds based on a relaxation of the IP. It also gives primal
(fractional) solutions. With this information one can run a heuristic to
produce an integer solution, or one can imbed Vol in a branch and bound code.

### Can one do "branch and cut" with Vol?

Yes, as an example, there is an implementation of a cutting plane algorithm
for the Max-cut problem, that combines [Bcp](https://github.com/coin-or/Bcp)
and Vol.

### Can one use Vol for column generation?

Yes. Vol has been very useful for accelerating column generation procedures,
in particular for Crew Scheduling. The dual solutions given by Vol seem to
provide faster convergence than if one uses dual solutions given by the
Simplex method.


## Project Links

 * [Code of Conduct](https://www.coin-or.org/code-of-conduct/)
 * [COIN-OR Web Site](http://www.coin-or.org/)
 * [COIN-OR general discussion forum](https://github.com/orgs/coin-or/discussions)
 * [Vol Discussion forum](https://github.com/coin-or/Vol/discussions)
 * [Report a bug](https://github.com/coin-or/Vol/issues/new)
 * [Doxygen generated documentation](http://coin-or.github.io/Vol/Doxygen)

