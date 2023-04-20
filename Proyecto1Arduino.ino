#include <TM1637Display.h>

#define CLK 5
#define DIO 4
int LecturaX=0;
int LecturaY=0;
int LecturaPot=0;
int BT;
int sieteSegmentos, buzzer, led;
TM1637Display display(CLK,DIO);
int sirenPin=7;
int sirenTime=5; //1ms
int ledPin=6;
int oleada=0;

void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);//analogo en x
  pinMode(A1,INPUT);// analogo en y
  pinMode(10,INPUT); // analogo presionado
  pinMode(A2,INPUT); //POTENCIOMETRO
  //pinMode(4,);// siete segmentos clk 
  //pinMode(5,); //siete segmentos dio
  pinMode(ledPin,OUTPUT); // led solo 
  pinMode(sirenPin,OUTPUT); //buzzer pasivo
  display.setBrightness(5);

}

void loop() {
  display.showNumberDec(oleada);
  LecturaX=analogRead(A0);
  LecturaY=analogRead(A1);
  BT=digitalRead(10);
  LecturaPot=analogRead(A2);

  Serial.print(LecturaX);
  Serial.print(",");
  Serial.print(LecturaY);
  Serial.print(",");
  Serial.print(BT);
  Serial.print(",");
  Serial.println(LecturaPot);

  // Leer los datos desde C++
    if (Serial.available() > 0)
    {
        // Leer los datos enviados desde C++
        String data = Serial.readStringUntil('\n');

        // Analizar los datos recibidos
        sscanf(data.c_str(), "%d,%d,%d", &sieteSegmentos, &buzzer, &led);

        // Encender el siete segmentos
        if (sieteSegmentos == 1)
        {
          oleada+=1;
          display.showNumberDec(oleada);
          sieteSegmentos=0;
        }else if(sieteSegmentos==2){
          display.showNumberDec(0);}
        else
        {
            // Apagar el siete segmentos
            // ...
        }

        // Encender el buzzer
        if (buzzer == 1)
        {
                 digitalWrite(sirenPin,HIGH);
                 delay(sirenTime);
                 digitalWrite(sirenPin,LOW);
                 delay(sirenTime);
                 buzzer=0;
        }
        else
        {
            // Apagar el buzzer
            // ...
        }

        // Encender el led
        if (led == 1)
        {
            digitalWrite(ledPin,HIGH);
            led=0;
        }
        else
        {
            digitalWrite(ledPin,LOW);
        }
    }
  delay(100);
}
