!/usr/bin/gnuplot -persist

#  TITLES
set title "as11 melsom 42593249"
set xlabel "x position (in spatial steps)"
set ylabel "density"

# AXES SETTINGS
#set yrange [-0.2:1]
set xrange [0:4000]
#set size square
#set xtics ('-2pi' -2*pi, '-pi' -pi, 0, 'pi' pi, '2pi' 2*pi) 
#set ytics 1
#set tics scale 0.75

# LEGEND
#set key default
#set key top left
#set key outside
#set key top left

# FILE OUTPUT
set term postscript color
set output "as11-problem3-melsom-42593249.ps"

plot "rho-0-j.dat" using 1:2 title "T= 0.0" w l, \
     "rho-1000-j.dat" using 1:2 title "T= 2.0" w l, \
     "rho-2500-j.dat" using 1:2 title "T= 5.0" w l, \
     "rho-5000-j.dat" using 1:2 title "T= 10.0" w l, \
     "rho-7500-j.dat" using 1:2 title "T= 15.0" w l
