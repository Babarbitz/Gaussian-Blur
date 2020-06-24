# 4F03 A4, Lucas Zacharewicz

This program takes a ppm file and applys image blur

In order to use the code I have provide please look to the makefile:

1. "make single" will produce a binary hw4 that is compiled without openmp which
   will allow the program to run in without multithread support
2. "make multi" will produce a binary hw4 that is compiled with openmp which
   allows it to run in parallel

# Some preliminary testing on my machine

Single threaded times for fox.ppm between 1.7 - 2.4 seconds
Multi threaded times for fox.ppm between 0.5 - 0.7 seconds

Both of those times are the real time values from running:

```
time ./hw4 50 fox.ppm out.ppm
```
