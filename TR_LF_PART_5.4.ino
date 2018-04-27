int sensor0,sensor1,sensor2,sensor3,sensor4,sensor5,sensor6,sensor7;
int ralat, lastralat;
int kiri1,kiri2,kanan1,kanan2;
int pwmkanan,pwmkiri;
int MV;
int MAXPWM=240;//200
int MINPWM=0;
int intervalPWM= (MAXPWM-MINPWM)/8;
int kp=220;//160
int kd=170;//100
int error;
int P;
int D;

void sensorbaca()
{
  if(sensor3<250)   //kondisi normal lurus
  {
    ralat=0;
 
    //digitalWrite(53,LOW);
    //digitalWrite(52,HIGH);

    //digitalWrite(44,LOW);
    //digitalWrite(45,HIGH);
  }
  /*
  if(sensor2<250)   //kondisi normal belok kiri
  {
    ralat=1;
  }
  
  if(sensor4<250)   //kondisi normal belok kanan
  {
    ralat=-1;
  }
  */
  if(sensor1 <450)   //kondisi bablas belok kiri
  {
    ralat=2;
  }
   if(sensor5<250)   //kondisi bablas belok kanan
  {
    ralat=-2;
 }
}

void PID()
{
  P = kp*ralat;
  D = kd * (ralat-lastralat);
  MV= P + D; //pid
  lastralat=ralat;

  pwmkanan=(MAXPWM)+MV;
  pwmkiri=MAXPWM-MV;

if(pwmkanan>=0)
{
  if(pwmkanan>MAXPWM)
    {
      pwmkanan=MAXPWM;
    }
    analogWrite(6,pwmkanan); //kanan
    digitalWrite(5,LOW);
    digitalWrite(7,HIGH);
}

else
{
  if(pwmkanan<=-255)
  {
    pwmkanan=-255;
  }
  analogWrite(6,(pwmkanan*-1)); //kanan
    digitalWrite(5,LOW);
    digitalWrite(7,LOW);
}

if(pwmkiri>=0)
{
  if(pwmkiri>MAXPWM)
    {
      pwmkiri=MAXPWM;
    }
    analogWrite(3,pwmkiri-10); //kanan
    digitalWrite(4,LOW);
    digitalWrite(2,HIGH);
}
else
{
  if(pwmkiri<=-255)
  {
    pwmkiri=-255;
  }
  analogWrite(3,(pwmkiri*-1)); //kanan
    digitalWrite(4,LOW);
    digitalWrite(2,LOW);
}

}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

//sensor0=analogRead(A1);   //kiri3
sensor1=analogRead(A4);  //kiri2
sensor2=analogRead(A3);  //kiri1
sensor3=analogRead(A2);  //tengah
sensor4=analogRead(A1);  //kanan1
sensor5=analogRead(A0); //kanan2
//sensor6=analogRead(A8); //kanan3b

sensorbaca();
PID();

Serial.print(sensor0);
Serial.print("  ");
Serial.print(sensor1);
Serial.print("  ");
Serial.print(sensor2);
Serial.print("  ");
Serial.print(sensor3);
Serial.print("  ");
Serial.print(sensor4);
Serial.print("  ");
Serial.print(sensor5);
Serial.print("  ");
Serial.print(sensor6);
Serial.print("  ");
Serial.print(pwmkiri);
Serial.print("  ");
Serial.print(pwmkanan);
Serial.print("  ");
Serial.print(ralat);
Serial.print("  ");
Serial.println(MV);
delay(10);
}
