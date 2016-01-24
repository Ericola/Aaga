set title "temps moyen d'execution MinMax pour un tableau d'arbre unaire-binaire"
set xlabel "Nombres d'arbres dans le tableau"
set ylabel "Temps d'execution"
plot "Courbe.txt" using 1:2 title 'naiveMinMax' with linespoints, \
"Courbe.txt" using 1:3 title 'optiMinMax' with linespoints

