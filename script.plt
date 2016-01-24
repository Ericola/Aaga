set title "temps d'execution pour MinMax en Java"
set xlabel "Taille du tableau"
set ylabel "Temps d'execution"
plot "CourbeMinMaxJ" using 1:2 title 'naive' with linespoints, \
"CourbeMinMaxJ" using 1:3 title 'opti' with linespoints

