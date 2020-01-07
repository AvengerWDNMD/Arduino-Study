#include <Servo.h>

Servo servo_12;
Servo servo_13;
int dwqv;
int V;
float L;
float tmp;
float checkdistance_4_7() {
  digitalWrite(4, LOW);
  delayMicroseconds(2);
  digitalWrite(4, HIGH);
  delayMicroseconds(10);
  digitalWrite(4, LOW);
  float distance = pulseIn(7, HIGH) / 58.00;
  delay(10);
  return distance;
}

//电机驱动定义
const int Left_motor_back=3;       //左电机后退(IN1) pwm
const int Left_motor_go=11;        //左电机前进(IN2) pwm
const int Right_motor_go=6;      // 右电机前进(IN4) pwm
const int Right_motor_back=5;    // 右电机后退(IN3) pwm

void setup() {
Serial.begin(9600);
pinMode(2,INPUT);
pinMode(A1,INPUT);pinMode(A2,INPUT);pinMode(A3,INPUT);
pinMode(Left_motor_go,OUTPUT); // PIN 10 (PWM)
pinMode(Left_motor_back,OUTPUT); // PIN 9 (PWM)
pinMode(Right_motor_go,OUTPUT);// PIN 6 (PWM) 
pinMode(Right_motor_back,OUTPUT);// PIN 5 (PWM)
servo_12.attach(12);
servo_13.attach(13);
servo_12.write(0);
servo_13.write(180);
 pinMode(4, OUTPUT);
 pinMode(7, INPUT);
 pinMode(A5,INPUT);


 
}

void loop() {
  int l=0;
  int S=0;
  int R=0;
  l=digitalRead(A1);
  S=digitalRead(A2);
  R=digitalRead(A3);
  if(digitalRead(2)==1){
    allGo(0,0);
    delay(1000);
    servo_12.write(105);
    servo_13.write(120);
    delay(5000);
    servo_13.write(180);
    servo_12.write(0);
    delay(1000);
    
  }
  
  
  
  //getLCR();
int val;
val=analogRead(A4);
//Serial.println(checkdistance_4_7());//光感
if(val<70){
  allGo(0,0);
  servo_13.write(120);
  delay(5000);
  servo_13.write(180);
}

  //showLCR();
  
  
//allGo(120,120);//测了一下左右电机，基本无差异OK
//电位器调整速
dwqv=analogRead(A0);
V=map(dwqv,0,1023,0,255);//前进速度
//Serial.println(V);
//allGo(V,V);
if(digitalRead(8)==1){
  if(digitalRead(A5)==0){
    allGo(0,0);
  }
  else{
   if(l==0 && S==1 && R==0) {allGo(V,V); }
  else if(l==1 && S==0 && R==0 || (l==1 && S==1 && R==0) )
  {
    while(!(l==0 && S==1 && R==0)|| (l==0 && S==0 && R==0))  
    {
      allGo(0,V+30);//120
      l=digitalRead(A1);
      S=digitalRead(A2);
      R=digitalRead(A3);      
    }
   brake();
  }
  else if(l==0 && S==0 && R==1 || (l==0 && S==1 && R==1))
  {
    while(!(l==0 && S==1 && R==0) || (l==0 && S==0 && R==0))
    {
      allGo(V+30,0);//120
      l=digitalRead(A1);
      S=digitalRead(A2);
      R=digitalRead(A3);
    }
    brake();
  }
  else  
  {
   brake();
  }
//allGo(V,V);
//lANDr(120,90,1);

  
 }
}
 else{
  allGo(0,0);
 }
 }


/*void getLCR(){
  l=digitalRead(A1);
  S=digitalRead(A2);
  R=digitalRead(A3);
}*/
/*void getLCR(){
    l=analogRead(A1); 
    if(l>280){l=1;}else{l=0;}
    c=analogRead(A2); 
    if(c>280){c=1;}else{c=0;}
    r=analogRead(A3);
    if(r>280){r=1;}else{r=0;}
  
  }*/
//void showLCR(){ Serial.print("l=");Serial.print(l);Serial.print(",c=");Serial.print(S);Serial.print(",r=");Serial.println(R);}
//电机驱动函数
//1.前进
void allGo(int lv,int rv)
{
  //PWM比例0~255调速，左右轮差异略增减
  //左边 电机
  analogWrite(Left_motor_go,lv); //Left_motor_go=10  pwm
  analogWrite(Left_motor_back,0); //Left_motor_back=9  pwm 
  //右边电机
 analogWrite(Right_motor_go,rv);//Right_motor_go=6 pwm
 analogWrite(Right_motor_back,0);//Right_motor_back=5 pwm
}
//2停车
void brake(){digitalWrite(Left_motor_go,0);  digitalWrite(Left_motor_back,0);  digitalWrite(Right_motor_go,0);  digitalWrite(Right_motor_back,0); }
//3后退方式的左右转
void lANDr(int qv,int hv,int fg)
{
  if(fg==1)  //后退方式左转
  {
    analogWrite(Left_motor_go,0); analogWrite(Left_motor_back,hv); //左边电机后退
    analogWrite(Right_motor_go,qv); analogWrite(Right_motor_back,0);//右边电机前进
   }
  else if(fg==2) //后退方式右转
  {
    analogWrite(Left_motor_go,qv); analogWrite(Left_motor_back,0); //左边电机前进
    analogWrite(Right_motor_go,0); analogWrite(Right_motor_back,hv);//右边电机后退
  }
  else  { digitalWrite(Left_motor_go,0);  digitalWrite(Left_motor_back,0);  digitalWrite(Right_motor_go,0);  digitalWrite(Right_motor_back,0);  }
  
}
