
//Altura
h=20;
//Dimensiones interior
di=4.2;
ti=40;
//Dimensiones exterior
de=9.2;
te=6;


difference(){
cylinder(r=de/2,h,$fn=te);
cylinder(r=di/2,h+1.2,$fn=ti);}