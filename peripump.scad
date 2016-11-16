// Bomba peristáltica Planetaria (personalizable)
// Por Drmn4ea (drmn4ea al correo de Google)
//
// Publicado bajo la licencia Creative Commons - Reconocimiento - Compartir bajo la misma licencia (http://creativecommons.org/licenses/by-sa/3.0/)
//
// Adaptado de engranajes planetarios de Emmett Lalish Teniendo en http://www.thingiverse.com/thing:53451


// -------- Ajustes relacionados con la impresora ------------

// Liquidación para generar entre las partes no conectadas. Si los engranajes print 'pegados' o son difíciles de separar, tratar de incrementar este valor. Si existe juego excesivo entre ellos, tratar de bajarlo. (Por defecto: 0,15 mm)
tol = 0.15;

// Voladizo autorizado para la retirada voladizo; entre 0 y 0.999 (0 = ninguno, 0,5 = 45 grados, 1 = infinito)
allowed_overhang = 0.8;


// -------- Los detalles de los tubos utilizados en la bomba, en mm ------------

// Diámetro exterior de su tubo en mm
tubing_od = 6.5;

// Espesor de la pared de la tubería
tubing_wall_thickness = 1;

// Cantidad que el tubo debe ser comprimido por los rodillos, como proporción del espesor total (0 = sin desplazamiento de la mezcla, 1,0 = desplazamiento de la mezcla completa)
tubing_squish_ratio = 0.1;

// --------  Ajustes de geometría de la pieza  ------------

// Diámetro exterior aproximado de anillo en mm
D = 53;

// Espesor en mm  es decir,
T = 18;

// Número de engranajes planetarios
number_of_planets = 4;

// Número de dientes de engranajes planetarios
number_of_teeth_on_planets = 6;

// Número de dientes en engranaje solar (aproximado)
approximate_number_of_teeth_on_sun=8;

// Angulo de PRESION
P = 45; // [30:60]

// Relación máxima profundidad de los dientes
DR = 0.5 * 1; 

// Número de dientes para girar a través de
nTwist = 2;

// Orificio de eje:
// Lados de tipo (100 para circulo)
wh = 6;
// Diametro circunscrito(*0.86 para compatibilidad con alen)
w = 9.5;

// Oreja de soporte:
// Disposicion(no requiere = 0,0)
ejex = 1;
ejey = 0;
// Distancia
dor = 65;
// Diámetro 
or = 4;
// Cantidad
cor = 2;
// Sobre Altura (solo hacia +z)(no requiere = 0)
sor = 25;

// tubo exterior de empalme de manguera (no requiere = 0)
te=1;
// Diámetro exterior
ted=10.5;
// longitud extra al diametro
tel=5;



// Sistema de acople con eje (modo inexacto!!) :
// 1- Medio eje en mitad de altura(no requiere = 0)
me = 0;
// 2- Sobre eje (solo hacia +z)(no requiere = 0)
se = 0;
// Diámetro circunscrito 
sed = 7;
// Lados de tipo (100 para circulo)
cse = 6;
// Longitud
led = 10;
// dimenciones de tuerca
espt=1;
ancht=5;
// dimenciones de tornillo
diamt=2;



// ----------------End of customizable values -----------------

m=round(number_of_planets);
np=round(number_of_teeth_on_planets);
ns1=approximate_number_of_teeth_on_sun;
k1=round(2/m*(ns1+np));
k= k1*m%2!=0 ? k1+1 : k1;
ns=k*m/2-np;
echo(ns);
nr=ns+2*np;
pitchD=0.9*D/(1+min(PI/(2*nr*tan(P)),PI*DR/nr));
pitch=pitchD*PI/nr;
echo(pitch);
helix_angle=atan(2*nTwist*pitch/T);
echo(helix_angle);

phi=$t*360/m;

        difference(){
        translate([0,-D/3.1,T/2])    
    cube([D*1.25,D/2,T],center=true); 
   translate([0,0,-0.1])
   cylinder(r=D/2,T+sor+1,$fn=100);};        
   
   difference(){
        translate([0,-D/3.1,(T+sor)/2])    
    cube([D*1.25,D/2,T+sor],center=true); 
        translate([0,0,-0.1])
   cylinder(r=D/1.75,T+sor+1,$fn=100);};
  
   difference(){
    translate([0,-D/2-6,(T+sor)/2])    
    cube([D*2.1,4,T+sor+4],center=true); 
       
for (x=[1,-1]){
       translate([50*x,.1,5])
       rotate([90,0,0]) 
   cylinder(r=or/2,100,$fn=100);   
          translate([50*x,.1,38])
       rotate([90,0,0]) 
   cylinder(r=or/2,100,$fn=100);};};
   
           difference(){
        translate([D/1.7,-30.5,0])    
    cube([20,20,T+sor],center=false); 
   translate([D,-12,-0.1])
   cylinder(r=20,T+sor+1,$fn=100);}; 
   
              difference(){
        translate([-D/1.7-20,-30.5,0])    
    cube([20,20,T+sor],center=false); 
   translate([-D,-12,-0.1])
   cylinder(r=20,T+sor+1,$fn=100);};
   
   
  
              //orejas de soporte
 for (i=[0:cor]){
rotate([0,0,i*360/cor])
    difference(){
     difference(){
        difference(){
            hull(){
                translate([ejex*D/2,ejey*D/2,T/2+sor/2])
                cube([2*or,2*or,T+sor],center=true); 
                translate([ejex*(dor/2),ejey*(dor/2),0])
                cylinder(r=or,T+sor,$fn=100); }
        translate([ejex*(dor/2),ejey*(dor/2),-0.1])
        cylinder(r=or/2,T+0.2+sor,$fn=100);}
    translate([0,0,-0.1])
    cylinder(r=D/2,T+1+sor,$fn=100);}
    translate([0,0,T-0.1])
        cylinder(r=D/1.8,sor+1,$fn=100);}
}     


// sistema de acople con eje:

// 1- medio eje en mitad de altura
difference(){
     translate([0,0,0])
cylinder(r=(w/2)*1.2*me,T/2,$fn=wh);
    translate([0,w/2,T/3])
cube([w*1.5,w,T],center=true);}


// 2- sobre eje
translate([0,0,T]){
difference(){
difference(){
difference(){
rotate([0,0,180/cse])
cylinder(r=sed*se,led,$fn=cse);
translate([0,0,-0.25])
cylinder(r=w/2,led+led*1.2,center=true,$fn=wh);}
 
 translate([0,0,led/2])    
 rotate([0,90,0])
 cylinder(r=diamt/2,8,$fn=100);}

 rotate([0,90,0])
 translate([led,led,sed/2]) 
 cube([ancht*2,ancht,espt],center=true);}
}
 


// tubo exterior de empalme de manguera
difference(){
     translate([0,0,T/2]){
         difference(){
 	exitholes(outerring_outer_radius-tubing_od/4,ted, len=(D/2)+tel*te);
 	exitholes(outerring_outer_radius-tubing_od/4,tubing_od*1.2, len=(D/1.8)+tel*te);}}
    cylinder(r=D/2,T,$fn=100);
    }
   
    
// compute some parameters related to the tubing
tubing_squished_width = tubing_od * (PI/2);
tubing_depth_clearance = 2*(tubing_wall_thickness*(1-tubing_squish_ratio));

// temporary variables for computing the outer radius of the outer ring gear teeth
// used to make the clearance for the peristaltic squeezer feature on the planets
outerring_pitch_radius = nr*pitch/(2*PI);
outerring_depth=pitch/(2*tan(P));
outerring_outer_radius = tol<0 ? outerring_pitch_radius+outerring_depth/2-tol : outerring_pitch_radius+outerring_depth/2;

// temporary variables for computing the outer radius of the planet gear teeth
// used to make the peristaltic squeezer feature on the planets
planet_pitch_radius = np*pitch/(2*PI);
planet_depth=pitch/(2*tan(P));
planet_outer_radius = tol<0 ? planet_pitch_radius+planet_depth/2-tol : planet_pitch_radius+planet_depth/2;

// temporary variables for computing the inside & outside radius of the sun gear teeth
// used to make clearance for planet squeezers
sun_pitch_radius = ns*pitch/(2*PI);
sun_base_radius = sun_pitch_radius*cos(P);
echo(sun_base_radius);
sun_depth=pitch/(2*tan(P));
sun_outer_radius = tol<0 ? sun_pitch_radius+sun_depth/2-tol : sun_pitch_radius+sun_depth/2;
sun_root_radius1 = sun_pitch_radius-sun_depth/2-tol/2;
sun_root_radius = (tol<0 && sun_root_radius1<sun_base_radius) ? sun_base_radius : sun_root_radius1;
sun_min_radius = max (sun_base_radius,sun_root_radius);


    
// debug raw gear shape for generating overhang removal
//translate([0,0,5])
//{
//	//halftooth (pitch_angle=5,base_radius=1, min_radius=0.1,	outer_radius=5,	half_thick_angle=3);
//	gear2D(number_of_teeth=number_of_teeth_on_planets, circular_pitch=pitch, pressure_angle=P, depth_ratio=DR, clearance=tol);
//}

translate([0,0,T/2])
{
	// outer ring
	difference()
	{
		// HACK: Add tubing depth clearance value to the total OD, otherwise the outer part may be too thin. FIXME: This is a quick n dirty way and makes the actual OD not match what the user entered...
		cylinder(r=D/2 + tubing_depth_clearance,h=T,center=true,$fn=100);
  		exitholes(outerring_outer_radius-tubing_od/4,tubing_od*1.2, len=100);
		union()
        		{
			// HACK: On my printer, it seems to need extra clearance for the outside gear, trying double...
			herringbone(nr,pitch,P,DR,-2*tol,helix_angle,T+0.2);
			cylinder(r=outerring_outer_radius+tubing_depth_clearance,h=tubing_squished_width,center=true,$fn=100);
			// overhang removal for top teeth of outer ring: create a frustum starting at the top surface of the "roller" cylinder 
			// (which will actually be cut out of the outer ring) and shrinking inward at the allowed overhang angle until it reaches the
			// gear root diameter.
			translate([0, 0, tubing_squished_width/2])
                    			{
				cylinder(r1=outerring_outer_radius+tubing_depth_clearance, r2=outerring_depth,h=abs(outerring_outer_radius+tubing_depth_clearance - outerring_depth)/tan(allowed_overhang*90),center=false,$fn=100);
   			}
		}
	}



	// sun gear
	rotate([0,0,(np+1)*180/ns+phi*(ns+np)*2/ns])
	
	difference()
	{

		// the gear with band cut out of the middle
		difference()
		{
			mirror([0,1,0])
				herringbone(ns,pitch,P,DR,tol,helix_angle,T);
				// center hole
				cylinder(r=w/2,h=T+1,center=true,$fn=wh);
				// gap for planet squeezer surface
				difference()
				{
					cylinder(r=sun_outer_radius,h=tubing_squished_width,center=true,$fn=100);
					cylinder(r=sun_min_radius-tol,h=tubing_squished_width,center=true,$fn=100);
				}
		}

		// on the top part, cut an angle on the underside of the gear teeth to keep the overhang to a feasible amount
		translate([0, 0, tubing_squished_width/2])
		{
			difference()
			{
				// in height, numeric constant sets the amount of allowed overhang after trim.
				//h=abs((sun_min_radius-tol)-sun_outer_radius)*(1-allowed_overhang)
				// h=tan(allowed_overhang*90)
				cylinder(r=sun_outer_radius,h=abs((sun_min_radius-tol)-sun_outer_radius)/tan(allowed_overhang*90),center=false,$fn=100);
				cylinder(r1=sun_min_radius-tol, r2=sun_outer_radius,h=abs((sun_min_radius-tol)-sun_outer_radius)/tan(allowed_overhang*90),center=false,$fn=100);
			}
		}
	
	}



	// planet gears

	for(i=[1:m])
	{

		rotate([0,0,i*360/m+phi])
		{
		
			translate([pitchD/2*(ns+np)/nr,0,0])
			{
				rotate([0,0,i*ns/m*360/np-phi*(ns+np)/np-phi])
				{
					union()
					{
						herringbone(np,pitch,P,DR,tol,helix_angle,T);
						// Add a roller cylinder in the center of the planet gears.
						// But also constrain overhangs to a sane level, so this is kind of a mess...
						intersection()
						{
							// the cylinder itself
							cylinder(r=planet_outer_radius,h=tubing_squished_width-tol,center=true,$fn=100);

							// Now deal with overhang on the underside of the planets' roller cylinders.
							// create the outline of a gear where the herringbone meets the cylinder;
							// make its angle match the twist at this point.
							// Then difference this flat gear from a slightly larger cylinder, extrude it with an
							// outward-growing angle, and cut the result from the cylinder.
							planet_overhangfix(np, pitch, P, DR, tol, helix_angle, T, tubing_squished_width, allowed_overhang);

						}

					}

				}
			}
		}
	}
	
}


module planet_overhangfix(
	number_of_teeth=15,
	circular_pitch=10,
	pressure_angle=28,
	depth_ratio=1,
	clearance=0,
	helix_angle=0,
	gear_thickness=5,
	tubing_squished_width,
	allowed_overhang)

{

	height_from_bottom =  (gear_thickness/2) - (tubing_squished_width/2);
	pitch_radius = number_of_teeth*circular_pitch/(2*PI);
	twist=tan(helix_angle)*height_from_bottom/pitch_radius*180/PI; // the total rotation angle at that point - should match that of the gear itself



	translate([0,0, -tubing_squished_width/2]) // relative to center height, where this is used
	{
		// FIXME: This calculation is most likely wrong...
		//rotate([0, 0, helix_angle * ((tubing_squished_width-(2*tol))/2)])
		rotate([0, 0, twist])
		{
			// want to extrude to a height proportional to the distance between the root of the gear teeth
			// and the outer edge of the cylinder
			linear_extrude(height=tubing_squished_width-clearance,twist=0,slices=6, scale=1+(1/(1-allowed_overhang)))
			{
				gear2D(number_of_teeth=number_of_teeth, circular_pitch=circular_pitch, pressure_angle=pressure_angle, depth_ratio=depth_ratio, clearance=clearance);
			}
		}
	}
}

module exitholes(distance_apart, hole_diameter)
{
	translate([distance_apart, len/2, 0])
	{
		rotate([90, 0, 0])
		{
			cylinder(r=hole_diameter/2,h=len,center=true,$fn=100);
		}
	}
	
	mirror([1,0,0])
	{
		translate([distance_apart, len/2, 0])
		{
			rotate([90, 0, 0])
			{
				cylinder(r=hole_diameter/2,h=len,center=true,$fn=100);
			}
		}
	}
}

module rack(
	number_of_teeth=15,
	circular_pitch=10,
	pressure_angle=28,
	helix_angle=0,
	clearance=0,
	gear_thickness=5,
	flat=false){
addendum=circular_pitch/(4*tan(pressure_angle));

flat_extrude(h=gear_thickness,flat=flat)translate([0,-clearance*cos(pressure_angle)/2])
	union(){
		translate([0,-0.5-addendum])square([number_of_teeth*circular_pitch,1],center=true);
		for(i=[1:number_of_teeth])
			translate([circular_pitch*(i-number_of_teeth/2-0.5),0])
			polygon(points=[[-circular_pitch/2,-addendum],[circular_pitch/2,-addendum],[0,addendum]]);
	}
}

//module monogram(h=1)
//linear_extrude(height=h,center=true)
//translate(-[3,2.5])union(){
//	difference(){
//		square([4,5]);
//		translate([1,1])square([2,3]);
//	}
//	square([6,1]);
//	translate([0,2])square([2,1]);
//}

module herringbone(
	number_of_teeth=15,
	circular_pitch=10,
	pressure_angle=28,
	depth_ratio=1,
	clearance=0,
	helix_angle=0,
	gear_thickness=5){
union(){
	//translate([0,0,10])
	gear(number_of_teeth,
		circular_pitch,
		pressure_angle,
		depth_ratio,
		clearance,
		helix_angle,
		gear_thickness/2);
	mirror([0,0,1])
		gear(number_of_teeth,
			circular_pitch,
			pressure_angle,
			depth_ratio,
			clearance,
			helix_angle,
			gear_thickness/2);
}}

module gear (
	number_of_teeth=15,
	circular_pitch=10,
	pressure_angle=28,
	depth_ratio=1,
	clearance=0,
	helix_angle=0,
	gear_thickness=5,
	flat=false){
pitch_radius = number_of_teeth*circular_pitch/(2*PI);
twist=tan(helix_angle)*gear_thickness/pitch_radius*180/PI;

flat_extrude(h=gear_thickness,twist=twist,flat=flat)
	gear2D (
		number_of_teeth,
		circular_pitch,
		pressure_angle,
		depth_ratio,
		clearance);
}

module flat_extrude(h,twist,flat){
	if(flat==false)
		linear_extrude(height=h,twist=twist,slices=twist/6, scale=1)child(0);
	else
		child(0);
}

module gear2D (
	number_of_teeth,
	circular_pitch,
	pressure_angle,
	depth_ratio,
	clearance){
pitch_radius = number_of_teeth*circular_pitch/(2*PI);
base_radius = pitch_radius*cos(pressure_angle);
depth=circular_pitch/(2*tan(pressure_angle));
outer_radius = clearance<0 ? pitch_radius+depth/2-clearance : pitch_radius+depth/2;
root_radius1 = pitch_radius-depth/2-clearance/2;
root_radius = (clearance<0 && root_radius1<base_radius) ? base_radius : root_radius1;
backlash_angle = clearance/(pitch_radius*cos(pressure_angle)) * 180 / PI;
half_thick_angle = 90/number_of_teeth - backlash_angle/2;
pitch_point = involute (base_radius, involute_intersect_angle (base_radius, pitch_radius));
pitch_angle = atan2 (pitch_point[1], pitch_point[0]);
min_radius = max (base_radius,root_radius);

intersection(){
	rotate(90/number_of_teeth)
		circle($fn=number_of_teeth*3,r=pitch_radius+depth_ratio*circular_pitch/2-clearance/2);
	union(){
		rotate(90/number_of_teeth)
			circle($fn=number_of_teeth*2,r=max(root_radius,pitch_radius-depth_ratio*circular_pitch/2-clearance/2));
		for (i = [1:number_of_teeth])rotate(i*360/number_of_teeth){
			halftooth (
				pitch_angle,
				base_radius,
				min_radius,
				outer_radius,
				half_thick_angle);		
			mirror([0,1])halftooth (
				pitch_angle,
				base_radius,
				min_radius,
				outer_radius,
				half_thick_angle);
		}
	}
}}

module halftooth (
	pitch_angle,
	base_radius,
	min_radius,
	outer_radius,
	half_thick_angle){
index=[0,1,2,3,4,5];
start_angle = max(involute_intersect_angle (base_radius, min_radius)-5,0);
stop_angle = involute_intersect_angle (base_radius, outer_radius);
angle=index*(stop_angle-start_angle)/index[len(index)-1];
p=[[0,0],
	involute(base_radius,angle[0]+start_angle),
	involute(base_radius,angle[1]+start_angle),
	involute(base_radius,angle[2]+start_angle),
	involute(base_radius,angle[3]+start_angle),
	involute(base_radius,angle[4]+start_angle),
	involute(base_radius,angle[5]+start_angle)];

difference(){
	rotate(-pitch_angle-half_thick_angle)polygon(points=p);
	square(2*outer_radius);
}}

// Mathematical Functions
//===============

// Finds the angle of the involute about the base radius at the given distance (radius) from it's center.
//source: http://www.mathhelpforum.com/math-help/geometry/136011-circle-involute-solving-y-any-given-x.html

function involute_intersect_angle (base_radius, radius) = sqrt (pow (radius/base_radius, 2) - 1) * 180 / PI;

// Calculate the involute position for a given base radius and involute angle.

function involute (base_radius, involute_angle) =
[
	base_radius*(cos (involute_angle) + involute_angle*PI/180*sin (involute_angle)),
	base_radius*(sin (involute_angle) - involute_angle*PI/180*cos (involute_angle))
];
