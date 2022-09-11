# Intersection-between-cylinder-and-plane-PCL
These algorithms make it possible to find the intersection between a plane and a cylinder. The principle is to estimate the influence of perpendicularity if the plane is not perpendicular to the cylinder. The programs are implemented in C++/PCL.


To execute the programs, we have to first delete the build directory and create another build directory every time we change computer or path file. Then in the new build directory, we can run cmake .. and make to compile and ./main to execute all the programs.


There are seven .cpp files in the source repertory, and their header files in the entete repertory. The most important file is effectively the main.cpp. In this main file, we have some global parameters where we can change their values or not, depending with what we want. These parameters are explain within the main file.


We don't need to change anything in the six other .cpp files. But if we want to understand what each contains, here is a short summary and each function is commented :

FIGURE.CPP : contains all functions to draw graphics

PBPLOTS.CPP : contains functions algorithms allow us to plot data

SUPPORTLIB.CPP : also contains functions for plotting
PBPLOTS.CPP and SUPPORTLIB.CPP are two files that I found online allow to plot data on C++ in 2D

VISUALISATION.CPP : contains functions to visualize 3D data with PCL

FUNCTIONSEARCHINTERSECTION.CPP : contains all the function allow to find the intersection between the plane and the cylinder.

CIRCLE_REGRESSION.CPP : contains all the functions to estimate the circle according to the intersections points obtained. It is with this case who we estimate the influence of perpedicularity.
