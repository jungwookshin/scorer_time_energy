# scorer_time_energy

A step-by-step tutorial for a custom TOPAS's nTuple scorer to output deposited energy as a function of time (flight time) in 2D histogram.

# Background

This project was motivated by a question from Fernando Hueso about 2D histogram of deposit energy as a function of time. As this can be realized by a custom scorer, it was recommended to develop a custom scorer. Like Fernando, many of TOPAS users want to implement their own scorers. In spite of many extension examples, a step-by-step guide for TOPAS users who don't have much C++ experience. Hope this step-by-step guide will be helpful. 


# Getting started

## System requirements

- TOPAS must be installed. Test version was 3.2.0 (latest as of May, 2019)

- cmake. Test version 3.14.2

- OS
  - Mac OS 10.14.1 (Mojave)

## Getting source from github repository

It is recommended to connect your ssh credential to github so that you can run git command from the terminal.

check github's step-by-step guide (https://help.github.com/articles/adding-a-new-ssh-key-to-your-github-account/)

Once the account setting is done, you can checkout the source code from github repository.

```bash

$ git clone https://github.com/jungwookshin/scorer_time_energy.git {your_extension_directory}

```

{your_extension_directory} needs to be replaced by your own name. 

For example, 

```bash

$ pwd

/opt/sw/topas/extensions

$ git clone https://github.com/jungwookshin/scorer_time_energy.git dt_de

```

For this case, {your_extension_directory} is /opt/sw/topas/extensions/dt_de. 


It is helpful to make a your own directory structure for TOPAS as TOPAS changes its version and you may have another extensions, etc. This is my directory structure for TOPAS development. 

```bash

topas/
├── 3.0.0
├── 3.0.1
├── 3.1.1
├── 3.1.2
├── 3.1.3
├── 3.2.0
└── extensions
   ├── auger
   ├── dt_de
   └── phantom
   
```

I download and put TOPAS releases to /opt/sw/topas/{topas_version} and put /opt/sw/topas/extensions.

## Compile your TOPAS wtih this extension.

I assumed the basic steps described in README.txt of TOPAS release directory are done.

```bash

$ cd {your_topas_directory}
$ cmake -DTOPAS_EXTENSIONS_DIR={your_extension_directory}/ntuple/
$ make -j3

```

In my case, {your_topas_directory} is /opt/sw/topas/3.2.0 and {your_extension_directory} is /opt/sw/topas/extensions/dt_de.


## Step 1

checkout tag-0.1 for skeleton code.

A ntuple scorer is created. NtupleScorer_dTdE.hh and NtupleScorer_dTdE.cc 

This is an initial version.


## Step 2

checkout tag-0.2 for deposit energy and time of flight of a particle


## Step 3

checkout tag-0.3 for store these information to TOPAS's map for thread-safe version.



## Run topas with topas input file

```bash

$ cd {your_topas_directory}
$ ./topas {your_extension_directory}/exec/test_dt_de.txt
$ ls 

myhistogram.root

```

A root file is created.


![example_image](doc/figure/test_my_ntuple2.png)

## Log

