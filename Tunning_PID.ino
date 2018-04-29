int batas[6]={110,110,110,110,110,110};
int sensor[6]={0,0,0,0,0,0};
byte sensorBiner=B000000;
int s[6];
int lpwm=0;
int L=3;
int L_in2=2;
int L_in1=4;
int rpwm=0;
int R=6;
int R_in2=5;
int R_in1=7;
float kp=5,ki=0,kd=2;
float error,P,I,D,MV,PV;
float MAXPWM=130;
float MINPWM=0;
float intervalPWM = (MAXPWM - MINPWM) / 8;
int sp=0; // set point
float rate;
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
  sensorBiner=B000000;
  
  if(analogRead(A0)<batas[0])
  {
    sensorBiner|=B000001;
  }
  if(analogRead(A1)<batas[1])
  {
    sensorBiner|=B000010;
  }
  if(analogRead(A2)<batas[2])
  {
    sensorBiner|=B000100;
  }
  if(analogRead(A3)<batas[3])
  {
    sensorBiner|=B001000;
  }
  if(analogRead(A4)<batas[4])
  {
    sensorBiner|=B010000;
  }
  if(analogRead(A5)<200)
  {
    sensorBiner|=B100000;
  }
  
}
void kondisi()
{
  switch(sensorBiner)
  {
    //case B000001:
      //    PV=-3;break;
          
    case B000010:
          PV=-2;break;
          
    case B000100:
          PV=-1;break;
          
    case B001100:
          PV=0;break;
          
    case B001000:
          PV=1;break;
          
    case B010000:
          PV=2;break;
       
    //case B100000:
    //      PV=3;break;
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
        
    } else if (MV > 0) { // alihkan ke kiri
        rpwm = MAXPWM - ((intervalPWM - 20) * MV);
        lpwm = (MAXPWM - (intervalPWM * MV) - 15);
 
        if (lpwm < MINPWM) lpwm = MINPWM;
        if (lpwm > MAXPWM) lpwm = MAXPWM;
        if (rpwm < MINPWM) rpwm = MINPWM;
        if (rpwm > MAXPWM) rpwm = MAXPWM;
       
    } else if (MV < 0) { // alihkan ke kanan
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
  Serial.println(sensorBiner);
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
  Serial.println("_________________");    
 
  /*
  if(sensorBiner|=B000001)
    { Serial.println("putar kiri");
      /*
        digitalWrite(L_in2,HIGH);
        digitalWrite(L_in1,LOW);
        analogWrite(L,MAXPWM);
        digitalWrite(R_in2,HIGH);
        digitalWrite(R_in1,LOW);
        analogWrite(R,0);
        
    }
  else if(sensorBiner|=B100000)
    { Serial.println("putar kanan");
      /*
        digitalWrite(L_in2,HIGH);
        digitalWrite(L_in1,LOW);
        analogWrite(L,0);
        digitalWrite(R_in2,HIGH);
        digitalWrite(R_in1,LOW);
        analogWrite(R,MAXPWM);
        
    }*/
delay(1000);
}

