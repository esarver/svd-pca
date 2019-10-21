# Advanced Algorithms, Project 2 - Image Compression Using SVD and Dimensionality Reduction Using PCA #


#### Authors: ####
- Quanshu Lu
- Edwin Sarver
- Ying Wang

---

**NOTE:** All instructions assume this project is being used on a Linux-based system.

---

## Building ##
**NOTE**: The google test library is pulled down during the first build 
automatically. Be sure you are connected to the internet before your first build.

In a terminal within the project directory:

```bash
mkdir build # create a build folder in the project directory
cd build # navigate into that build folder
cmake .. # run cmake to generate makefiles
make -j4 # build using 4 concurrent threads (increase the number if desired) 
```

---

## Running the Application ##

In a terminal within the project `build` directory after a build has been completed:

```bash
cd bin

# Convert the given ASCII PGM file to the binary counterpart.
# The binary file will be saved as <filename>_b.pgm
# This will remove any comments in the given ASCII PGM file.
# The input image is assumed to meet the P2 specification for PGM
# images.
./project_two 1 image.pgm

# Convert the given binary PGM file to an ASCII representation
# The ASCII file will be saved as <base_filename>_copy.pgm
./project_two 2 image_b.pgm #this will save to image_copy.pgm

# Using the PGM header information found in the first text-file,
# the matrices found in the second text-file, and the approximation
# rank given by 'k', produce a compressed, binary PGM file called
# image_b.pgm.SVD 
./project_two 3 header.txt SVD.txt k

# Reverse what was done in part 3. 
# This will output header.txt, SVD.txt, and image_k.pgm
# where 'k' is the rank of the approximation.
# image_k.pgm will be readable by any PGM viewer.
./project_two 4 image_b.pgm.SVD 

# Get usage information
./project_two -h
```

---

## Running Unit Tests ##
The tests for this project are written using the google test framework.
There are a couple ways the run the unit tests for this project.

In a terminal within the `build` folder in the project directory after a build has been completed:

#### Option 1: `make test` ####

```bash
make test
```

#### Option 2: `ctest` ####

```bash
ctest # use '-V' option for more information.
```

#### Option 3: Run Test Binaries Individually ####

```bash
cd bin
./*-tests
```

---

**DETERMINE WHETHER THIS WILL STILL BE APPLICABLE**

## Running Benchmarks and Generating Plots

**NOTE**: Python and "pipenv" must be installed in order to successfully carry
          out the following instructions.

In a terminal within the project `build` directory, run:

```bash
make plots
```
