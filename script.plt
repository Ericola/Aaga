set title "temps moyen d'execution pour la somme maximale d'un tableau"
set xlabel "Taille du tableau"
set ylabel "Temps d'execution"
plot "CourbeTMS.txt" using 1:2 title 'naive' with linespoints, \
"CourbeTMS.txt" using 1:3 title 'opti' with linespoints

