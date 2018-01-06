/*
 * By: JONATHAN BAZAN
 * BIO ELECTRONICA SE ESCRIBE CON B
 * 
 */
#define led 7
#define s0 2  //LEDS
#define s1 3    //FRECUENCIA 
#define s2 4   //RECEPTORES
#define s3 5   //RECEPTORES 
#define out 6  //SEÑAL DE COLOR A ARDUINO
#define push 8
#define muestras 200 
int RGB1 = 0;  //AQUI VA A GURADAR EL VALOR LEIDO DEL ROJO
int RGB2 = 0; //AQUI VA A GURADAR EL VALOR LEIDO DEL VERDE
int RGB3 = 0; //AQUI VA A GURADAR EL VALOR LEIDO DEL BLUE
int RED = 9;  //PINES PARA EL RGB
int GREEN = 10; //PINES PARA EL RGB
int BLUE = 11; //PINES PARA EL RGB
long frecuencia = 0;  
float factor_RGB[3];  
void setup()   
{  
   
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(RED, OUTPUT);   //SALIDAS LOS LEDS
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);  
  pinMode(out, INPUT);  //ENTRADA DEL SENSOR A ARDUINO 
  pinMode(push, INPUT);  //SELECTOR DE CALIBRACION
  //Escala de frecuencia de salida al 2%
  digitalWrite(s0, LOW);  
  digitalWrite(s1, HIGH);  
  //Comunicación Serial
  Serial.begin(9600);
}  
    
void loop() 
{  
  // Para calibrar el sensor se debe presionar el pulsador
  if(digitalRead(push)== HIGH)
  {
    TCS_init(); //RUTINA DE CALIBRACION  
  }
  else
  // El sensor comienza la lectura de color
  {
    // Se encienden los leds del sensor para tener mejor lectura
    digitalWrite(led, HIGH);
    leer_R();
    RGB1 = frecuencia * factor_RGB[0];
    Serial.print("Rojo = ");
    Serial.print(RGB1);
    Serial.print(" ");
    leer_G();
    RGB2 = frecuencia * factor_RGB[1];
    Serial.print("Verde = ");
    Serial.print(RGB2);
    Serial.print(" ");
    leer_B();
    RGB3 = frecuencia * factor_RGB[2];
    Serial.print("Azul = ");
    Serial.println(RGB3);
    delay(500);
    
  }
    //***CARACTERIZACION DE LOS COLORES***//
    if( RGB1>240 & RGB1<265 & RGB2>240 & RGB2<265 & RGB3>240 & RGB3<265)
  {
   analogWrite(RED,255);
   analogWrite(GREEN,255);
   analogWrite(BLUE,255);
    Serial.print("  BLANCO  ");
  }
    if( RGB1>40 & RGB1<55 & RGB2>60 & RGB2<85 & RGB3>40 & RGB3<65)
  {
   analogWrite(RED,0);
   analogWrite(GREEN,128);
   analogWrite(BLUE,0);
    Serial.print("  VERDE FUERTE ");
  } 
     if( RGB1>110 & RGB1<140 & RGB2>80 & RGB2<100 & RGB3>120 & RGB3<150)
  {
   analogWrite(RED,128);
   analogWrite(GREEN,0);
   analogWrite(BLUE,128);
    Serial.print("  MORADO ");
  } 
       if( RGB1>50 & RGB1<79  & RGB2>110 & RGB2<140 & RGB3>145 & RGB3<180)
  {
   analogWrite(RED,0);
   analogWrite(GREEN,128);
   analogWrite(BLUE,255);
    Serial.print("  AZUL CIELO ");
  } 
         if( RGB1>225 & RGB1<260 & RGB2>165 & RGB2<195 & RGB3>65 & RGB3<85)
  {
      analogWrite(RED,250);
   analogWrite(GREEN,64);
   analogWrite(BLUE,1);
    Serial.print("  AMARILLO ");
  } 
           if( RGB1>165 & RGB1<205 & RGB2>40 & RGB2<60 & RGB3>50 & RGB3<70)
  {
   analogWrite(RED,255);
   analogWrite(GREEN,0);
   analogWrite(BLUE,0);
    Serial.print("  ROJO ");
  } 
         if( RGB1>115 & RGB1<140 & RGB2>150 & RGB2<180 & RGB3>65 & RGB3<85)
  {
   analogWrite(RED,128);
   analogWrite(GREEN,255);
   analogWrite(BLUE,0);
    Serial.print("  VERDE LIMON ");
  } 
         if( RGB1>220 & RGB1<270 & RGB2>140 & RGB2<175 & RGB3>150 & RGB3<190)
  {
  analogWrite(RED,100);
   analogWrite(GREEN,0);
   analogWrite(BLUE,20);
    Serial.print("  ROSA CLARO ");
  } 
         if( RGB1>305 & RGB1<360 & RGB2>95 & RGB2<120 & RGB3>60 & RGB3<85)
  {
   analogWrite(RED,255);
   analogWrite(GREEN,30);
   analogWrite(BLUE,1);
    Serial.print("  NARANJA ");
  } 
         if( RGB1>390 & RGB1<435 & RGB2>130 & RGB2<165 & RGB3>160 & RGB3<210)
  {
   analogWrite(RED,255);
   analogWrite(GREEN,0);
   analogWrite(BLUE,125);
    Serial.print("  ROSA FUERTE");
  } 
         if( RGB1>35 & RGB1<50 & RGB2>50 & RGB2<70 & RGB3>80 & RGB3<108)
  {
   analogWrite(RED,0);
   analogWrite(GREEN,0);
   analogWrite(BLUE,160);
    Serial.print(" AZUL REY");
  } 
}
long calcular_frecuencia(int pin) 
{
  
  long freq = 0;
  for(unsigned int j=0; j<muestras; j++) freq+= 500000/pulseIn(pin, HIGH, 150000);
  return freq / muestras;
}

//********RUTINA DE CALIBRACION****//
void TCS_init()
{
  // Iniciamos corrección de balance de blancos
  digitalWrite(s2, HIGH);
  digitalWrite(s3, LOW);
  Serial.println("Calibrando Balance de blancos..");
  // Se encienden los leds del sensor para tener mejor lectura
// digitalWrite(led, HIGH);
//  delay(1000);
  leer_R();
  factor_RGB[0] = 255.0/frecuencia;
  leer_G();
  factor_RGB[1] = 255.0/frecuencia;
  leer_B();
  factor_RGB[2] = 255.0/frecuencia;
   delay(500);
  Serial.println("Sensor calibrado correctamente!!"); 
}

///***LEE EL ROJO** EL SENSOR//
void leer_R()
{
  // Activar lectura de color Rojo
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  frecuencia = calcular_frecuencia(out);
} 

 
void leer_G()
{
  // Activar lectura de color Verde
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  frecuencia = calcular_frecuencia(out);
}
void leer_B()
{
  // Activar lectura de color Azul
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  frecuencia = calcular_frecuencia(out);
}
