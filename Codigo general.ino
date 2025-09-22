#include <LiquidCrystal.h>
#include <Keypad.h>
#define PIN1 A8
#define PIN2 A9
#define PIN3 A10
#define PIN4 A11
#define PIN5 A12
#define PIN6 A13
#define PIN7 A14
#define PIN8 52
#define PON 10
double TAR1,TAR2,TAR3,TAR4,TAR5,TAR6,TAR7,TAR8;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); 
//Comandos iniciación Teclado 
const byte filas = 4;
const byte columnas = 4;
char matriz[filas][columnas] =
{
  { '1', '2', '3', 'A'},
  { '4', '5', '6', 'B'},
  { '7', '8', '9', 'C'},
  { '*', '0', '#', 'D'},
};
//antiguamente {9,8,7,6}{5,4,3,2}
byte pinesFilas[filas] = {A8, A9, A10, A11};
byte pinesColumnas[columnas] = {A12, A13, A14, A15};
Keypad teclado = Keypad( makeKeymap(matriz), pinesFilas, pinesColumnas, filas, columnas);
char tecla_presionada;
int posX = 0;
int posY = 0;
int Numero=0;
int Transferencia_act=0;
char presionando;
int veces_presionada = 0;
int mayuscula_activada = 0;
int mostrar_cursorPantalla = 1;
int contador = 0;
//Variables para el control del contador
unsigned long tiempo_anterior = 0;
int periodo = 500;  //500 milisegundos
void setup() {
pinMode(PIN1,INPUT);
pinMode(PIN2,INPUT);
pinMode(PIN3,INPUT);
pinMode(PIN4,INPUT);
pinMode(PIN5,INPUT);
pinMode(PIN6,INPUT);
pinMode(PIN7,INPUT);
pinMode(PIN8,INPUT);
pinMode(PON,OUTPUT);
digitalWrite(PON,HIGH);
lcd.begin(16, 2);
lcd.home();
lcd.setCursor(2, 0);
lcd.print("Electronic");
lcd.setCursor(3, 1);
lcd.print("Monopoly v1");
delay(2000);
lcd.clear();
//tarjetas ya inicializadas con la plata
TAR1=1500;
TAR2=1500;
TAR3=1500;
TAR4=1500;
TAR5=1500;
TAR6=1500;
TAR7=1500;
TAR8=1500;
lcd.setCursor(4, 0);
lcd.print("Tarjetas");
lcd.setCursor(2, 1);
lcd.print("Inicializadas");
lcd.setCursor(4, 0);
delay(2000);
lcd.clear();
}

void loop() {
//ANTIGUAMENTE comandos Salida
//Comandos para designar la variable numero
tecla_presionada=teclado.getKey();
if(Numero==0) lcd.clear();
else lcd.print(Numero);
if(tecla_presionada=='*')
{
  veces_presionada=0;///////////////TESTEAR(Probar si despues de ingresar un numero se puede omitir la tecla)
  Numero=0;
}
if(veces_presionada==0)
   {
     Numero=tecla_presionada;///////////////TESTEAR SI SALTA ERROR A FUTURO PULSANDO TECLAS NO NUMERICAS
   }
    else
   {
     Numero=(Numero*10)+tecla_presionada;
   }
//Comandos Teclado
    //Almacena la tecla presionada
  if (veces_presionada > 0) 
  { contador++;
      if (contador == 1)       
      {
        posX++;
        veces_presionada = 0;
      }
  }
   if (posX > 15)
  {
    posX = 0;
    posY++;
  }
//Mensaje de aviso transferencia
//TransferenciaAct();

//Switch de teclas especiales
switch (tecla_presionada)  
  {
    case 'A':                      
      transaccion(); //////////////////////////////////HACER FUNCION DE TRANSACCION ENTRE JUGADORES
      veces_presionada = 0;
      break;

    case 'B':                     
      salida();
      veces_presionada = 0;
      break;

    case 'C':                     
      sumar(); ////////////////////HACER FUNCIÓN DE SUMAR A TARJETA(CON PREVIA DETECCIÓN SI HAY TARJETA)    
      veces_presionada = 0;
      break;

    case 'D':                   
      restar();////////////////////HACER FUNCION DE RESTAR A TARJETA(CON PREVIA DETECCION SI HAY TARJETA)
      veces_presionada = 0;
      break;
      }


}
void TransferenciaAct()
{
  if((digitalRead(PIN5)==HIGH)
{
lcd.print("Transferencia!");
  delay(2000); 
  lcd.clear();
  lcd.home();
  Transferencia_act=1;
}
else if((digitalRead(PIN6)==LOW||digitalRead(PIN7)==LOW||digitalRead(PIN8)==LOW) && Transferencia_act==1)
{
Transferencia_act=0;
}
}

void transaccion()
{
 if(Transferencia_act=1)
 {
  //Pensar manera de reducir el futuro codigo....
 }
 else
 {
  lcd.clear();
  lcd.print("No hay Tarjeta");
  delay(2000);
  lcd.clear();
 }
}

void sumar()
{
if(digitalRead(PIN1)==HIGH)
{TAR1=TAR1+Numero;
lcd.print("TARJETA1-Suma");}//////AGREGAR SALDO FINAL EN EL SEGUNDO RENGLON
if(digitalRead(PIN1)==HIGH && digitalRead(PIN2)==HIGH)
{TAR2=TAR2+Numero;
lcd.print("TARJETA2-Suma");}
if(digitalRead(PIN1)==HIGH && digitalRead(PIN3)==HIGH)
{TAR3=TAR3+Numero;
lcd.print("TARJETA3-Suma");}
if(digitalRead(PIN1)==HIGH && digitalRead(PIN4)==HIGH)
{TAR4=TAR4+Numero;
lcd.print("TARJETA4-Suma");}
if(digitalRead(PIN2)==HIGH)
{TAR5=TAR5+Numero;
lcd.print("TARJETA5-Suma");}
if(digitalRead(PIN2)==HIGH && digitalRead(PIN3)==HIGH)
{TAR6=TAR6+Numero;
lcd.print("TARJETA6-Suma");}
if(digitalRead(PIN2)==HIGH && digitalRead(PIN4)==HIGH)
{TAR7=TAR7+Numero;
lcd.print("TARJETA7-Suma");}
if(digitalRead(PIN3)==HIGH)
{TAR8=TAR8+Numero;
lcd.print("TARJETA8-Suma");}
delay(2000);
lcd.clear();
}

void restar()
{
if(digitalRead(PIN1)==HIGH)
{TAR1=TAR1-Numero;
lcd.print("TARJETA1-Resta");}////////////////////////////////////AGREGAR SALDO FINAL EN EL SEGUNDO RENGLON
if(digitalRead(PIN1)==HIGH && digitalRead(PIN2)==HIGH)
{TAR2=TAR2-Numero;
lcd.print("TARJETA2-Resta");}
if(digitalRead(PIN1)==HIGH && digitalRead(PIN3)==HIGH)
{TAR3=TAR3-Numero;
lcd.print("TARJETA3-Resta");}
if(digitalRead(PIN1)==HIGH && digitalRead(PIN4)==HIGH)
{TAR4=TAR4-Numero;
lcd.print("TARJETA4-Resta");}
if(digitalRead(PIN2)==HIGH)
{TAR5=TAR5-Numero;
lcd.print("TARJETA5-Resta");}
if(digitalRead(PIN2)==HIGH && digitalRead(PIN3)==HIGH)
{TAR6=TAR6-Numero;
lcd.print("TARJETA6-Resta");}
if(digitalRead(PIN2)==HIGH && digitalRead(PIN4)==HIGH)
{TAR7=TAR7-Numero;
lcd.print("TARJETA7-Resta");}
if(digitalRead(PIN3)==HIGH)
{TAR8=TAR8-Numero;
lcd.print("TARJETA8-Resta");}
delay(2000);
lcd.clear();
}
void salida()
{
if(digitalRead(PIN1)==HIGH)
{TAR1=TAR1+200;
lcd.print("TARJETA1-Salida");}
if(digitalRead(PIN1)==HIGH && digitalRead(PIN2)==HIGH)
{TAR2=TAR2+200;
lcd.print("TARJETA2-Salida");}
if(digitalRead(PIN1)==HIGH && digitalRead(PIN3)==HIGH)
{TAR3=TAR3+200;
lcd.print("TARJETA3-Salida");}
if(digitalRead(PIN1)==HIGH && digitalRead(PIN4)==HIGH)
{TAR4=TAR4+200;
lcd.print("TARJETA4-Salida");}
if(digitalRead(PIN2)==HIGH)
{TAR5=TAR5+200;
lcd.print("TARJETA5-Salida");}
if(digitalRead(PIN2)==HIGH && digitalRead(PIN3)==HIGH)
{TAR6=TAR6+200;
lcd.print("TARJETA6-Salida");}
if(digitalRead(PIN2)==HIGH && digitalRead(PIN4)==HIGH)
{TAR7=TAR7+200;
lcd.print("TARJETA7-Salida");}
if(digitalRead(PIN3)==HIGH)
{TAR8=TAR8+200;
lcd.print("TARJETA8-Salida");}
delay(2000);
lcd.clear();
}
