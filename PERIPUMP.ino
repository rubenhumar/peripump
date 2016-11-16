#include "IRremote.h"
#include "LCD5110_Basic.h"

LCD5110 myGLCD(12,11,10,8,9); //LCD5110 myGLCD(CLK, DIN, DC, RST, CE)
IRrecv irrecv(6);             // create instance of 'irrecv'
decode_results results;       // create instance of 'decode_results'


int dir=2;  //direccion
int stp=3;  //paso
int en=5;  //paso
int ms1=4;  //paso

extern uint8_t arduino_logo[];
extern uint8_t utn_logo[];
extern uint8_t lab_logo[];
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

String main_0 = "PERIPUMP";
String main_1 = "TRASVASAR";
String main_2 = "AJUSTES";

String menu_1 = "Trasvasar";
String menu_2 = "Ajustes";

String menu_1_1 = "Por Volumen";
String menu_1_2 = "Por Tiempo";
String menu_1_3 = "Serial";
String menu_1_4 = "Libre";

String menu_2_1 = "Purgar";
String menu_2_2 = "Calibrar";
String menu_2_3 = "Prueba";

String menu_volver = "Volver";

float vol=0;
float vold=0;
int flu=0;
int sent=1;
int tiempo=0;
int tiempot=0;
int tiempoa=0;
int por=0;
int cant=1;
int s=0;
int se=0;
int t=0;
int p=0;

int v=0;
int vl=0;

int ti=0;
int ml=0;
long pa=0;
int del=0;
int Ms1=0;

float paml=0;
float tml=0;

int i=0;

int ini=0;
int e=0;
int o=0;
int x=0;
int l=0;
int menu=0;

void setup()
{
  
  pinMode(dir , OUTPUT);//direccion
  pinMode(stp , OUTPUT);//paso
  pinMode(en , OUTPUT);//enable
  pinMode(ms1 , OUTPUT);//enable
  
  digitalWrite(ms1, LOW); 
  digitalWrite(en, HIGH); 
  
  Serial.begin(9600);
  Serial.println("PERIPUMP START");
  irrecv.enableIRIn();
  
  myGLCD.InitLCD();

  myGLCD.setContrast(60);
  myGLCD.clrScr();
  myGLCD.drawBitmap(0, 0, arduino_logo, 84, 48);
  delay(2000);
  
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont); //Declara el tipo de fuente a usar
  myGLCD.print("iniciando", CENTER, 0);
  myGLCD.print("|            |", CENTER, 16);
  myGLCD.print("por favor", CENTER, 32);
  myGLCD.print("espere", CENTER, 40);
  delay(250);
    for (int a=0; a<12; a++)
  {
    myGLCD.print("\\", 6+(a*6), 16);
    delay(230);
  }
  
  myGLCD.clrScr();
  myGLCD.drawBitmap(0, 0, utn_logo, 84, 48);
  delay(5000);
  
  myGLCD.clrScr();
  myGLCD.drawBitmap(0, 0, lab_logo, 84, 48);
  delay(8000);

  myGLCD.clrScr();
  Menu();
}


void loop()
{   
  switch(ini){
    
  case 0:
  if (irrecv.decode(&results)){ // se recive señal IR?
    IR();
    irrecv.resume(); // Recivir siguiente valor
    Menu();
    Menu();//translateIR();   // Serial.println(results.value, HEX);  UN Comment to see raw values
  }
    break;
    
  case 1:
  if (irrecv.decode(&results)){ // se recive señal IR?
    ValorIR();
    irrecv.resume(); // Recivir siguiente valor
    Menu();
    Menu();//translateIR();   // Serial.println(results.value, HEX);  UN Comment to see raw values
  }
    break;
    
  case 2: 
  for (int si=0; si<=1500; si++)
  {
      myGLCD.print("FINALIZADO!", CENTER, 0); 
      delay(1000);  
      myGLCD.invertText(true);
      myGLCD.print("FINALIZADO!", CENTER, 0); 
      myGLCD.invertText(false);
      delay(1000); 
       
    if (irrecv.decode(&results)){ // se recive señal IR?
    IR();
    irrecv.resume(); // Recivir siguiente valor
    };   
    if (o==1){
    si=1500;
    o=0;
    ini=0;
    menu=0;
    myGLCD.clrRow(0);
    };      
  };
    ini=0;
    menu=0;
    myGLCD.clrRow(0);
    s=0; 
    break;
};
};





void IR()
{
  switch(results.value){
  case 0xFFA25D:
  e++;
      Serial.println("+"); 
    break;
  case 0xFF629D:
  o=1;
      Serial.println("ok"); 
    break;  
  case 0xFFE21D:
  e--; 
      Serial.println("-"); 
    break;
  default: 
    break;
  }
};  




void TrasIR()
{
   if (irrecv.decode(&results)){ // se recive señal IR?
    irrecv.resume(); // Recivir siguiente valor
  switch(results.value){
  case 0xFF906F:  
   if(Ms1==0){
     digitalWrite(ms1, HIGH); 
     Ms1=1;
   }else{
     digitalWrite(ms1, LOW); 
     Ms1=0;
   }
    Serial.println("EQ");  
    break;
  
  case 0xFFC23D:  
    p=1;
    Serial.println(">||"); 
    break;
  }
};
};  





void ValorIR()
{
switch(results.value){ // toma las acciones de las señaes IR}
  
  case 0xFF629D:
      Serial.println("ok"); 
    o=0;
    ini=0;
    vl=0;
    v=0;
    x=0;
    i=0;
    e++;
    break;
      
  case 0xFF6897:  
    Serial.println("0"); 
    v=0;
    i++;
    break;

  case 0xFF9867:  
    Serial.println("100+"); 
    break;

  case 0xFFB04F:  
    Serial.println("200+"); 
    break;

  case 0xFF30CF:  
    Serial.println("1"); 
    v=1;
    i++;
    break;

  case 0xFF18E7:  
    Serial.println("2");
    v=2;
    i++;
    break;

  case 0xFF7A85:  
    Serial.println("3"); 
    v=3;
    i++;
    break;

  case 0xFF10EF:  
    Serial.println("4"); 
    v=4;
    i++;
    break;

  case 0xFF38C7:  
    Serial.println("5");
    v=5;
    i++;
    break;

  case 0xFF5AA5:  
    Serial.println("6"); 
    v=6;
    i++;
    break;

  case 0xFF42BD:  
    Serial.println("7"); 
    v=7;
    i++;
    break;

  case 0xFF4AB5:  
    Serial.println("8"); 
    v=8;
    i++;
    break;

  case 0xFF52AD:  
    Serial.println("9"); 
    v=9;
    i++;
    break;
  };
  delay(200);
  if ((x+1)==i){
    vl=v;
    i=1;
  }else{
    vl=vl*10+v;
  }
};




void Menu()
{
    switch(menu)  {
    case 0:
    if(e<=-1){
      e=1;
    };
    if(e>=2){
      e=0;
    };
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print(main_0, CENTER, 0); 
  myGLCD.print(menu_1, CENTER, 16);
  myGLCD.print(menu_2, CENTER, 24);
  myGLCD.print("LAB FD 2016", CENTER, 40);
  
   switch(e)  {
//--------------------------------------------------------------
  case 0:
  myGLCD.invertText(true);
  myGLCD.print(menu_1, CENTER, 16); 
  myGLCD.invertText(false);
    if (o==1){
    o=0;
    e=0;
    menu=1;
    }; 
   break;
  case 1:
  myGLCD.print(menu_1, CENTER, 16); 
  myGLCD.invertText(true);
  myGLCD.print(menu_2, CENTER, 24);
  myGLCD.invertText(false);
    if (o==1){
    o=0;
    e=0;
    menu=2;
    };
      break;  
};
   break;  
//--------------------------------------------------------------
    case 1:
    if(e<=-1){
      e=4;
    };
    if(e>=5){
      e=0;
    };
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print(main_1, CENTER, 0); 
  myGLCD.print(menu_1_1, CENTER, 8);
  myGLCD.print(menu_1_2, CENTER, 16);
  myGLCD.print(menu_1_3, CENTER, 24);
  myGLCD.print(menu_1_4, CENTER, 32);
  myGLCD.print(menu_volver, CENTER, 40);
  
   switch(e)  {
  case 0:
  myGLCD.invertText(true);
  myGLCD.print(menu_1_1, CENTER, 8); 
  myGLCD.invertText(false);
      if (o==1){
    o=0;
    myGLCD.clrScr();
    myGLCD.setFont(SmallFont);
    myGLCD.print(menu_1_1, CENTER, 0); 
    menu=3;
    t=0;
    s=0;
    e=6;
    l=0;
    };      
      break;
      
  case 1:
  myGLCD.print(menu_1_1, CENTER, 8); 
  myGLCD.invertText(true);
  myGLCD.print(menu_1_2, CENTER, 16);
  myGLCD.invertText(false);
      if (o==1){
    o=0;
    myGLCD.clrScr();
    myGLCD.setFont(SmallFont);
    myGLCD.print(menu_1_2, CENTER, 0); 
    menu=3;
    t=1;
    s=0;
    l=0;
    };
      break;
        
  case 2:
  myGLCD.print(menu_1_2, CENTER, 16); 
  myGLCD.invertText(true);
  myGLCD.print(menu_1_3, CENTER, 24);
  myGLCD.invertText(false);
      if (o==1){
    myGLCD.clrScr();
    myGLCD.setFont(SmallFont);
    myGLCD.print(menu_1_3, CENTER, 0); 
    o=0;
    menu=3;
    t=0;
    s=1;
    l=0;
    e=0;
    };
      break;  
  case 3:
  myGLCD.print(menu_1_3, CENTER, 24); 
  myGLCD.invertText(true);
  myGLCD.print(menu_1_4, CENTER, 32);
  myGLCD.invertText(false);
      if (o==1){
    myGLCD.clrScr();
    myGLCD.setFont(SmallFont);
    myGLCD.print(menu_1_4, CENTER, 0); 
    o=0;
    menu=3;
    t=0;
    s=0;
    l=1;
    e=6;
    };
      break;  
  case 4:
  myGLCD.print(menu_1_4, CENTER, 32); 
  myGLCD.invertText(true);
  myGLCD.print(menu_volver, CENTER, 40);
  myGLCD.invertText(false);
    if (o==1){
    o=0;
    menu=0;
    };
      break;  
};
      break;  
//-------------------------------------------------------
    case 2:
    if(e<=-1){
      e=3;
    };
    if(e>=4){
      e=0;
    };
  myGLCD.clrScr();
  myGLCD.setFont(SmallFont);
  myGLCD.print(main_2, CENTER, 0); 
  myGLCD.print(menu_2_1, CENTER, 16);
  myGLCD.print(menu_2_3, CENTER, 24);
  myGLCD.print(menu_2_2, CENTER, 32);
  myGLCD.print(menu_volver, CENTER, 40);
  
   switch(e)  {
  case 0:
  myGLCD.invertText(true);
  myGLCD.print(menu_2_1, CENTER, 16); 
  myGLCD.invertText(false);
    if (o==1){
    o=0;
    e=0;
    menu=0;
    Purgar();
    };
      break;
      
  case 1:
  myGLCD.print(menu_2_1, CENTER, 16); 
  myGLCD.invertText(true);
  myGLCD.print(menu_2_3, CENTER, 24);
  myGLCD.invertText(false);
    if (o==1){
    o=0;
    e=0;
    menu=5;
    };
      break;  
      
  case 2:
  myGLCD.print(menu_2_3, CENTER, 24); 
  myGLCD.invertText(true);
  myGLCD.print(menu_2_2, CENTER, 32);
  myGLCD.invertText(false);
        if (o==1){
    myGLCD.clrScr();
    myGLCD.setFont(SmallFont);
    myGLCD.print(menu_2_3, CENTER, 0); 
    o=0;
    e=0;
    menu=4;
    };
        break;  
  case 3:
  myGLCD.print(menu_2_2, CENTER, 32); 
  myGLCD.invertText(true);
  myGLCD.print(menu_volver, CENTER, 40);
  myGLCD.invertText(false);
    if (o==1){
    o=0;
    e=0;
    menu=0;
  };
      break;
};  
      break;  
//---------------------------------------------------------
    case 3:
    if(s==1){
      if(e<=-1){
      e=5;
      };
    }else{
      if(l==1){
      if(e<=1){
      e=5;
      };
      };
      if(e<=0){
      e=5;
      };
    };
    if(e>=6){    
      if(l==1){
      e=2;
      }else{
      e=1;
      };    
      if(s==1){
      e=0;
      };
    };
  myGLCD.setFont(SmallFont);
  myGLCD.print(menu_volver, RIGHT, 40);
  myGLCD.print("Iniciar", LEFT, 40);
  myGLCD.print("Sent.:", LEFT, 32);
  if (se==0){
  myGLCD.print("Ahorario", RIGHT, 32);
  }else{
  myGLCD.print(" Horario", RIGHT, 32);
  }
  myGLCD.print("Flu. :", LEFT, 24);
  myGLCD.printNumI(flu , 52, 24, 2, '0'); 
  myGLCD.print("mls", RIGHT, 24);
  if (t==1){
  myGLCD.print("Tiempo:", LEFT, 16);
  myGLCD.printNumI(tiempo, 50, 16, 4, '0');
  myGLCD.print("s", RIGHT, 16);  
  }else{
  if (l==0){
  myGLCD.print("Vol. :", LEFT, 16); 
  myGLCD.printNumI(vol, 46, 16, 4, '0');
  myGLCD.print("ml", RIGHT, 16);
  }
  }
  if (s==1){
  myGLCD.print("Cant.:", LEFT, 8);
  myGLCD.printNumI(cant, 46, 8, 3, '0');
  myGLCD.print("und", RIGHT, 8);
  }
   switch(e)  {
    
  case 0:
  myGLCD.invertText(true);
  myGLCD.print("Cant.:", LEFT, 8);
  myGLCD.invertText(false);
    if (o==1){
  ini=1;
  x=3;
  cant=vl;
  myGLCD.invertText(true);
  myGLCD.printNumI(cant, 46, 8, 3, '0');
  myGLCD.invertText(false);
  };
      break;  

  case 1:
  myGLCD.invertText(true);
  if (t==1){
  myGLCD.print("Tiempo:", LEFT, 16);
  myGLCD.invertText(false);
      if (o==1){
  ini=1;
  x=4;
  tiempo=vl;
  myGLCD.invertText(true);
  myGLCD.printNumI(tiempo, 50, 16, 4, '0');
  myGLCD.invertText(false);
  };
  }else{
  myGLCD.print("Vol. :", LEFT, 16);
  myGLCD.invertText(false); 
       if (o==1){
  ini=1;
  x=4;
  vol=vl;
  myGLCD.invertText(true);
  myGLCD.printNumI(vol, 46, 16, 4, '0');
  myGLCD.invertText(false);
  };
  };
      break;  

  case 2:
  myGLCD.invertText(true);
  myGLCD.print("Flu. :", LEFT, 24);
  myGLCD.invertText(false);
  if (o==1){
  ini=1;
  x=2;
  flu=vl;
  myGLCD.invertText(true);
  myGLCD.printNumI(flu , 52, 24, 2, '0'); 
  myGLCD.invertText(false);
  };
      break;  

  case 3:
  myGLCD.invertText(true);
  myGLCD.print("Sent.:", LEFT, 32);
  myGLCD.invertText(false);
  if (o==1){
     if (se==0){
      se=1;
     }else{
      se=0;
     };
  myGLCD.invertText(true);
  if (se==1){
  myGLCD.print("Ahorario", RIGHT, 32);
  }else{
  myGLCD.print(" Horario", RIGHT, 32);
  }
  myGLCD.invertText(false);
    delay(500);
    o=0;
  };
       break;  

  case 4:
  myGLCD.invertText(true);
  myGLCD.print("Iniciar", LEFT, 40);
  myGLCD.invertText(false);
        if (o==1){
    o=0;
    menu=0;
    e=0;
    Tras();
    };
      break;  

  case 5:
  myGLCD.invertText(true);
  myGLCD.print(menu_volver, RIGHT, 40);
  myGLCD.invertText(false);
        if (o==1){
    o=0;
    menu=1;
    e=0;
    };
      break;  
    
  };
      break;
//---------------------------------------------------------
    case 4:
    if(e<=-1){
      e=4;
    };
    if(e>=5){
      e=0;
    };
    
  myGLCD.print("del:", LEFT, 8);  
  myGLCD.print("ml:", LEFT, 16);
  myGLCD.print("ti:", LEFT, 24);
  myGLCD.print("pa:", LEFT, 32);
  myGLCD.print(menu_volver, CENTER, 40);

  myGLCD.printNumI(del, 46, 8, 4, '0');
  myGLCD.printNumI(ml, 46, 16, 4, '0');
  myGLCD.printNumI(ti, 46, 24, 4, '0'); 
  myGLCD.printNumI(pa, 46, 32, 6, '0');

   switch(e)  { 

  case 0:
  myGLCD.invertText(true);
  myGLCD.print("del:", LEFT, 8);
  myGLCD.invertText(false);
    if (o==1){
  ini=1;
  x=4;
  del=vl;
  myGLCD.invertText(true);
  myGLCD.printNumI(del, 46, 8, 4, '0');
  myGLCD.invertText(false);
  };
        break; 
        
  case 1:
  myGLCD.invertText(true);
  myGLCD.print("ml:", LEFT, 16);
  myGLCD.invertText(false);
    if (o==1){
  ini=1;
  x=4;
  ml=vl;
  myGLCD.invertText(true);
  myGLCD.printNumI(ml, 46, 16, 4, '0');
  myGLCD.invertText(false);
  };
      break;  

   case 2:
  myGLCD.invertText(true);
  myGLCD.print("ti:", LEFT, 24);
  myGLCD.invertText(false);
    if (o==1){
  ini=1;
  x=4;
  ti=vl;
  myGLCD.invertText(true);
  myGLCD.printNumI(ti, 46, 24, 4, '0');
  myGLCD.invertText(false);
  };
       break;  
 
   case 3:
  myGLCD.invertText(true);
  myGLCD.print("pa:", LEFT, 32);
  myGLCD.invertText(false);
    if (o==1){
  ini=1;
  x=6;
  pa=vl;
  myGLCD.invertText(true);
  myGLCD.printNumI(pa, 46, 32, 6, '0');
  myGLCD.invertText(false);
  };
        break; 
        
   case 4:
  myGLCD.invertText(true);
  myGLCD.print(menu_volver, CENTER, 40);
  myGLCD.invertText(false);
        if (o==1){
    o=0;
    menu=2;
    e=0;
    };
      break;     
  };
      break; 
//---------------------------------------------------------
    case 5:
  myGLCD.clrScr();
  myGLCD.invertText(true);
  myGLCD.print(menu_2_3, CENTER, 0); 
  myGLCD.invertText(false);
 
     myGLCD.print("volumen", CENTER, 8); //tiempo transcurrido
     myGLCD.print("conocido a", CENTER, 16); //tiempo transcurrido
     myGLCD.print("trasvasar:", CENTER, 24); //tiempo transcurrido
         
    if(e<=-1){
      e=1;
    };
    if(e>=2){
      e=0;
    };
    
  myGLCD.print("ml:", LEFT, 32);
  myGLCD.print("ml", RIGHT, 32);
  myGLCD.print("COMENZAR", CENTER, 40);
  myGLCD.printNumI(ml, 46, 32, 4, '0');

   switch(e)  { 
  case 0:
  myGLCD.invertText(true);
  myGLCD.print("ml:", LEFT, 32);
  myGLCD.invertText(false);
    if (o==1){
  ini=1;
  x=4;
  ml=vl;
  myGLCD.invertText(true);
  myGLCD.printNumI(ml, 46, 32, 4, '0');
  myGLCD.invertText(false);
  };
        break; 
        
  case 1:
  myGLCD.invertText(true);
  myGLCD.print("COMENZAR", CENTER, 40);
  myGLCD.invertText(false);
    if (o==1){
  Prueba();
  o=0;
  };
      break; 
   };
   break; 
};
};
  








void Tras()
{
  paml=pa/ml;
  float dela=1/(flu*paml)*1000;
  int pasostotal=paml*vol;

  tiempoa=millis()/1000;
  
  digitalWrite(en, LOW);
  if (se==0){
  digitalWrite(dir, LOW); 
  }else{
  digitalWrite(dir, HIGH);
  };
  
  myGLCD.clrRow(1);     
  myGLCD.clrRow(2); 
  myGLCD.clrRow(3); 
  myGLCD.clrRow(4); 
  myGLCD.clrRow(5); 
 
  myGLCD.setFont(SmallFont);
  myGLCD.print("vol", LEFT, 8);
  myGLCD.print("desp", LEFT, 16);
  myGLCD.print("ml", RIGHT, 16);

 if (t==0){
  myGLCD.print("de:", 15, 24);
  myGLCD.print("ml",56, 24); 
  }else{
  myGLCD.print("en:", 15, 24);
  myGLCD.print("s",56, 24); 
  };

  myGLCD.print("t:", LEFT, 32);
  myGLCD.print("s",34, 32); 

  myGLCD.print("p:", 48, 32);
  myGLCD.print("%", RIGHT, 32); 

 if (s==0){
  myGLCD.print("s:",LEFT, 40);
  if (se==0){
  myGLCD.print("Ahor", 10, 40);
  }else{
  myGLCD.print(" Hor", 10, 40);
  };
  myGLCD.print("v:", 44, 40);
  myGLCD.print("mls",65, 40);
   }else{
  myGLCD.print("cant=", LEFT, 40);
  myGLCD.print("       und", RIGHT, 40); 
  myGLCD.print("/", 43 , 40); 
   };

 if (l==0){
      if(t==0){                                                         //volumen
  for (int c=1; c<=cant; c++)
  {                                                                     //catidad
    TrasIR();
    if (p==0){
  for (int pasos=0; pasos<=pasostotal; pasos++)
  {
    TrasIR();
    if (p==0){
    tiempot=millis()/1000-tiempoa;
    vold=pasos/paml;
    myGLCD.setFont(MediumNumbers);
    myGLCD.printNumI(vold, 24, 8, 4, '0'); //volumen desplazado
    myGLCD.setFont(SmallFont);
    por=100*vold/vol;
    myGLCD.printNumI(vol, CENTER, 24, 4,'0'); //volumen total
    myGLCD.printNumI(tiempot, 9, 32, 4,'0'); //tiempo transcurrido

   if (s==1){
    myGLCD.printNumI(c, 25, 40, 3,'0'); //cantidad
    myGLCD.printNumI(cant, 48, 40, 3,'0'); //cantidad
   }else{
    myGLCD.printNumI(flu, 53, 40, 2,'0'); //caudal
   };
   
    myGLCD.printNumI(por, 60, 32, 3,'0'); //progreso

                 if(pasos%2){
                 digitalWrite(stp, LOW);   
                 }else{               
                 digitalWrite(stp, HIGH); 
                 };
                 delay(dela);
    }else{                          
     pasos=pasostotal; 
    };  
    };
    if (cant>1){
    delay(10000);
    };
    }else{
     c=10000; 
    };
    };
    
    }else{                                                             //tiempo 
      tiempot=millis()/1000-tiempoa;
    for (int pasos=0; tiempot<=tiempo; pasos++)
    {
    TrasIR();
    if (p==0){
    tiempot=millis()/1000-tiempoa;
    vold=pasos/paml;
    por=100*tiempot/tiempo;
    myGLCD.setFont(MediumNumbers);
    myGLCD.printNumI(vold, 24, 8, 4, '0'); //volumen desplazado
    myGLCD.setFont(SmallFont);
    myGLCD.printNumI(tiempot, CENTER, 24, 4,'0'); //tiempo transcurrido
    myGLCD.printNumI(tiempo, 9, 32, 4,'0'); //tiempo
    myGLCD.printNumI(flu, 53, 40, 2,'0'); //caudal
    myGLCD.printNumI(por, 60, 32, 3,'0'); //progreso

                 if(pasos%2){
                 digitalWrite(stp, LOW);   
                 }else{               
                 digitalWrite(stp, HIGH); 
                 };
                 delay(dela);
                 
                     }else{
     tiempot=tiempo; 
    };
    };
    };

    
  }else{                                                                   //libre
        myGLCD.clrRow(2); 
        myGLCD.clrRow(3); 
        myGLCD.clrRow(4); 
        myGLCD.clrRow(5); 
    for (int  pasos=0; pasos<=999999999; pasos++)
    {     
    TrasIR();
    if (p==0){
    tiempot=millis()/1000-tiempoa;
    myGLCD.setFont(SmallFont);
    vold=pasos/paml;
    myGLCD.print("vol desplazado:", CENTER, 8); 
    myGLCD.print("tiempo:", LEFT, 40); 
    
    myGLCD.print("ml", RIGHT, 24);     
    myGLCD.print("s ", RIGHT, 40); 
 
    myGLCD.printNumI(tiempot, 45, 40, 4, '0'); //tiempo transcurrido

    myGLCD.setFont(BigNumbers);
    myGLCD.printNumI(vold, CENTER, 16, 4,'0'); //volumen desplazado
    
                 if(pasos%2){
                 digitalWrite(stp, LOW);   
                 }else{               
                 digitalWrite(stp, HIGH); 
                 };
                 delay(dela); 
    }else{
     pasos=999999999; 
    };
};
};
  digitalWrite(ms1, LOW); 
  Ms1=0;
  digitalWrite(en, HIGH);
  ini=2;
  p=0;
  s=0;
  t=0;
  l=0;
  o=0;
  myGLCD.clrRow(0);
  loop();

  };










void Purgar()
{
  digitalWrite(en, LOW);
  myGLCD.clrScr();
  myGLCD.invertText(true);
  myGLCD.print(menu_2_1, CENTER, 0); 
  myGLCD.invertText(false);
  myGLCD.print("PURGANDO...", CENTER, 24);
  myGLCD.print("fin = >||", CENTER, 40);
   for (int j=0; j<=10000; j++)
    {     
    TrasIR();
   if (p==0){
    digitalWrite(stp, HIGH);   
    delay(10);               
    digitalWrite(stp, LOW); 
    delay(10);
   }else{
     j=10000; 
   };
  };
  digitalWrite(ms1, LOW);
  Ms1=0; 
  myGLCD.setFont(SmallFont);
  digitalWrite(en, HIGH);
  ini=2;
  p=0;
  s=0;
  t=0;
  l=0;
  myGLCD.clrRow(0); 
  loop();
};








void Prueba()
{
  pa=0;
  ti=0;
  if(del==0){
    del=50;
  };
  digitalWrite(en, LOW);
  myGLCD.clrScr();
  myGLCD.invertText(true);
  myGLCD.print(menu_2_3, CENTER, 0); 
  myGLCD.invertText(false);
     myGLCD.print("tiempo=", LEFT, 40);
     myGLCD.print("presione >||", CENTER, 8); //tiempo transcurrido
     myGLCD.print("cuando se", CENTER, 16); //tiempo transcurrido
     myGLCD.print("trasvasen", CENTER, 24); //tiempo transcurrido
     myGLCD.printNumI(ml, 30, 32, 4, '0');
     myGLCD.print("ml", 60, 32); //tiempo transcurrido
   
  tiempoa=millis()/1000;
   for (int j=0; j<=10000; j++)
    {     
    TrasIR();
   if (p==0){
    digitalWrite(stp, HIGH);
    pa++;   
    delay(del);               
    digitalWrite(stp, LOW); 
    pa++;
    delay(del);
    ti=millis()/1000-tiempoa;
    myGLCD.printNumI(ti, RIGHT, 40, 4, '0'); //tiempo transcurrido
    }else{
     j=10000;
    myGLCD.printNumI(ti, RIGHT, 40, 4, '0'); //tiempo transcurrido
   };
};
  digitalWrite(ms1, LOW); 
  Ms1=0;
  digitalWrite(en, HIGH);
  ini=2;
  p=0;
  s=0;
  t=0;
  l=0;
  o=0;
  myGLCD.clrRow(0);
  loop();
};
