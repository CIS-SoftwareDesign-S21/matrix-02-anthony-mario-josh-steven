set terminal png size 800,600 
set output 'out.png'

# Key means label...
#set key inside bottom right
set xlabel 'Matrix Size'
set ylabel 'Time (sec)'
set title 'Matrix multiplication algorithm comparison'
plot  "data.txt" using 1:2 title 'MMult' with linespoint, "data.txt" using 1:3 title 'MMult_SIMD' with linespoint, "data.txt" using 1:4 title 'MMult_SIMDw/o3' with linespoint, "data.txt" using 1:5 title 'OpenMP' with linespoint, "data_mpi.txt" using 1:2 title "MPI" with linespoint 
