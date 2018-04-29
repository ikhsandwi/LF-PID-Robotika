int batas[5]={170,170,170,170,170};
int sensor[5]={0,0,0,0,0};
byte sensorBiner=B00000;
int s[6];
int jeda=1000;
int lpwm;
int L=3;
int L_in2=2;
int L_in1=4;
int rpwm;
int R=6;
int R_in2=7;
int R_in1=5;
float kp=2,ki=0,kd=0;
float error,P,I,D,MV,PV;
int MAXPWM=100;
int MINPWM=0;
float intervalPWM = (MAXPWM - MINPWM) / 8;
int sp=0; // set point
int rate;
int putar=0;
#define buzzer 13
#define button 12
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(L,OUTPUT);
  pinMode(R,OUTPUT);
  pinMode(L_in1,OUTPUT);
  pinMode(L_in2,OUTPUT);
  pinMode(R_in1,OUTPUT);
  pinMode(R_in2,OUTPUT);
  pinMode(12,INPUT);
  pinMode(13,OUTPUT);
  digitalWrite(buzzer, LOW);
  
}

// the loop routine runs over and over again forever:
void baca()
{
  sensorBiner=B00000;
  
 
  if(analogRead(A0)<250)
  {
    sensorBiner|=B00001;
  }
  if(analogRead(A1)<250)
  {
    sensorBiner|=B00010;
  }
  if(analogRead(A2)<250)
  {
    sensorBiner|=B00100;
  }
  if(analogRead(A3)<250)
  {
    sensorBiner|=B01000;
  }
  if(analogRead(A4)<350)
  {
    sensorBiner|=B10000;
  }
  
}
void kondisi()
{
  switch(sensorBiner)
  {
    case B00001:
    case B00011:
          PV=3;break;   
    case B00010:
          PV=2;break;
    case B00110:
          PV=1;break;
    case B00100:
          PV=0;break;  
    case B01100:
          PV=-1;break;
    case B01000:
          PV=-2;break;  
    case B10000: 
    case B11000:  
          PV=-3;break;
  }
    
}

void PID_program()
{
  int lasterror;
  error=sp-PV;
  P=kp*error;
  I=I+error;
  I=I*ki;
  rate =error-lasterror;
  D=rate*kd;
  lasterror=error;
  MV=P+I+D; 
  MV = P;
  if (MV == 0) 
  { //lurus, maju cepat
        lpwm = MAXPWM;
        rpwm = MAXPWM;
    
  }
  else if (MV==10||MV==15) 
  { // alihkan ke kiri
        rpwm = MAXPWM - ((intervalPWM - 20) * MV);
        lpwm = (MAXPWM - (intervalPWM * MV) - 15);
    
        if (lpwm < MINPWM) lpwm = MINPWM;
        if (lpwm > MAXPWM) lpwm = MAXPWM;
        if (rpwm < MINPWM) rpwm = MINPWM;
        if (rpwm > MAXPWM) rpwm = MAXPWM;
  }
  else if (MV==-10||MV==-15) 
  { // alihkan ke kanan
        lpwm = MAXPWM + ( ( intervalPWM - 20 ) * MV);
        rpwm = MAXPWM + ( ( intervalPWM * MV ) - 15 );
   
        if (lpwm < MINPWM) lpwm = MINPWM;
        if (lpwm > MAXPWM) lpwm = MAXPWM;
        if (rpwm < MINPWM) rpwm = MINPWM;
        if (rpwm > MAXPWM) rpwm = MAXPWM;
    }
    

} 
void loop()
{
  baca();
  kondisi();
  PID_program();
  Serial.print("pv =");
  Serial.println(PV);
  Serial.print("eror =");
  Serial.println(error);
  Serial.print("P =");
  Serial.println(P);
  Serial.print("I =");
  Serial.println(I);
  Serial.print("D =");
  Serial.println(D);
  Serial.print("MV =");
  Serial.println(MV);
  Serial.print("lpwm =");
  Serial.println(lpwm);
  Serial.print("rpwm =");
  Serial.println(rpwm);
  Serial.println(putar);
  /*
    digitalWrite(L_in2,HIGH);
    digitalWrite(L_in1,LOW);
    digitalWrite(R_in2,HIGH);
    digitalWrite(R_in1,LOW);
    analogWrite(R,rpwm);
    analogWrite(L,lpwm);  
  */
  if(PV==0)
  {
    digitalWrite(L_in2,HIGH);
    digitalWrite(L_in1,LOW);
    digitalWrite(R_in2,HIGH);
    digitalWrite(R_in1,LOW);
    analogWrite(R,rpwm);
    analogWrite(L,lpwm);  
  }
  if(PV==1)
  {
    digitalWrite(L_in2,HIGH);
    digitalWrite(L_in1,LOW);
    digitalWrite(R_in2,HIGH);
    digitalWrite(R_in1,LOW);
    analogWrite(R,rpwm);
    analogWrite(L,lpwm);  
  }
  if(PV==2)
  {
    digitalWrite(L_in2,HIGH);
    digitalWrite(L_in1,LOW);
    digitalWrite(R_in2,HIGH);
    digitalWrite(R_in1,LOW);
    analogWrite(R,rpwm);
    analogWrite(L,lpwm);  
  }
  if(PV==-1)
  {
    digitalWrite(L_in2,HIGH);
    digitalWrite(L_in1,LOW);
    digitalWrite(R_in2,HIGH);
    digitalWrite(R_in1,LOW);
    analogWrite(R,rpwm);
    analogWrite(L,lpwm);  
  }
  if(PV==-2)
  {
   digitalWrite(L_in2,HIGH);
    digitalWrite(L_in1,LOW);
    digitalWrite(R_in2,HIGH);
    digitalWrite(R_in1,LOW);
    analogWrite(R,rpwm);
    analogWrite(L,lpwm);  
  }
  /*
  if(PV==-3)
  {
    
        digitalWrite(L_in2,HIGH);
        digitalWrite(L_in1,LOW);
        digitalWrite(R_in2,HIGH);
        digitalWrite(R_in1,LOW);
        analogWrite(R,rpwm);
        analogWrite(L,lpwm);
       Serial.println("putarkiri");
    
  }
  
  if(PV==3)
  {
    
        digitalWrite(L_in2,HIGH);
        digitalWrite(L_in1,LOW);
        digitalWrite(R_in2,HIGH);
        digitalWrite(R_in1,LOW);
        analogWrite(L,lpwm);
        analogWrite(R,rpwm);
    Serial.println("putarkanan");
    
  }
  */
  Serial.println("_________________");    
  delay(jeda);
  
}

