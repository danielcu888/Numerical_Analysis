set terminal postscript
set output "bifurcation_ex3.ps"
set xlabel "k"
set ylabel "Attractor, p"
unset key
set title "ex3, p_0 = 0.2"
set yrange [0:1]
set xtics 0.1
set grid
plot "o1.txt" using ($0-$0+1*0.1+1-0.1):2, \
"o2.txt" using ($0-$0+2*0.1+1-0.1):2, \
"o3.txt" using ($0-$0+3*0.1+1-0.1):2, \
"o4.txt" using ($0-$0+4*0.1+1-0.1):2, \
"o5.txt" using ($0-$0+5*0.1+1-0.1):2, \
"o6.txt" using ($0-$0+6*0.1+1-0.1):2, \
"o7.txt" using ($0-$0+7*0.1+1-0.1):2, \
"o8.txt" using ($0-$0+8*0.1+1-0.1):2, \
"o9.txt" using ($0-$0+9*0.1+1-0.1):2, \
"o10.txt" using ($0-$0+10*0.1+1-0.1):2, \
"o11.txt" using ($0-$0+11*0.1+1-0.1):2, \
"o12.txt" using ($0-$0+12*0.1+1-0.1):2, \
"o13.txt" using ($0-$0+13*0.1+1-0.1):2, \
"o14.txt" using ($0-$0+14*0.1+1-0.1):2, \
"o15.txt" using ($0-$0+15*0.1+1-0.1):2, \
"o16.txt" using ($0-$0+16*0.1+1-0.1):2, \
"o17.txt" using ($0-$0+17*0.1+1-0.1):2, \
"o18.txt" using ($0-$0+18*0.1+1-0.1):2, \
"o19.txt" using ($0-$0+19*0.1+1-0.1):2, \
"o20.txt" using ($0-$0+20*0.1+1-0.1):2, \
"o21.txt" using ($0-$0+21*0.1+1-0.1):2, \
"o22.txt" using ($0-$0+22*0.1+1-0.1):2, \
"o23.txt" using ($0-$0+23*0.1+1-0.1):2, \
"o24.txt" using ($0-$0+24*0.1+1-0.1):2, \
"o25.txt" using ($0-$0+25*0.1+1-0.1):2, \
"o26.txt" using ($0-$0+26*0.1+1-0.1):2, \
"o27.txt" using ($0-$0+27*0.1+1-0.1):2, \
"o28.txt" using ($0-$0+28*0.1+1-0.1):2, \
"o29.txt" using ($0-$0+29*0.1+1-0.1):2, \
"o30.txt" using ($0-$0+30*0.1+1-0.1):2