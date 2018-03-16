#!/bin/bash

# *** Usage: ./gen.py <number_of_airports> <density> <min f/od> <max f/od> <max_hops> <alfa_error>
#        Ex: ./gen.py         10             100         1          3          4           2

for n in 4; do
  echo "generating instance with $n airports"
  ./gen.py $n 100 1 2 4 5
  mkdir $n
  mv *.csv ./$n/
done
