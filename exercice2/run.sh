# !/bin/bash

mkdir -p data_v1

mpicc src/pingpong_v1.c

for n in {1..30}
do
    # Échauffement
    for i in {1..5}
    do 
        mpiexec -n 2 ./a.out 32*$n
    done

    for i in {1..33}
    do 
        mpiexec -n 2 ./a.out 32*$n >> data_v1/data$n.dat
    done
done

rm -rf a.out

mkdir -p data_v2

mpicc src/pingpong_v2.c

for n in {1..30}
do
    # Échauffement
    for i in {1..5}
    do 
        mpiexec -n 2 ./a.out 32*$n
    done

    for i in {1..33}
    do 
        mpiexec -n 2 ./a.out 32*$n >> data_v2/data$n.dat
    done
done

rm -rf a.out