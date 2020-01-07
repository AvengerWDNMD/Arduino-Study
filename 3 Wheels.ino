int dwqv;
int V;
//循迹传感器定义
#define lt 2
#define cr 3
#define rt 4
int l,c,r;
//电机驱动定义
const int Left_motor_back=9;       //左电机后退(IN1) pwm
const int Left_motor_go=10;        //左电机前进(IN2) pwm
const int Left_motor_en=8;         // 右电机使能 非pwm引脚

const int Right_motor_go=6;      // 右电机前进(IN4) pwm
const int Right_motor_back=5;    // 右电机后退(IN3) pwm
const int Right_motor_en=7;      // 右电机使能     非pwm

void setup() {
Serial.begin(9600);
pinMode(lt,INPUT);pinMode(cr,INPUT);pinMode(rt,INPUT);

pinMode(Left_motor_go,OUTPUT); // PIN 10 (PWM)
pinMode(Left_motor_back,OUTPUT); // PIN 9 (PWM)
pinMode(Left_motor_en,OUTPUT);// PIN 8

pinMode(Right_motor_go,OUTPUT);// PIN 6 (PWM) 
pinMode(Right_motor_back,OUTPUT);// PIN 5 (PWM)
pinMode(Right_motor_en,OUTPUT);// PIN 7 
 
}

void loop() {
//allGo(120,120);//测了一下左右电机，基本无差异OK
//电位器调整速
dwqv=analogRead(A0);
V=map(dwqv,0,1023,0,255);//前进速度


 getLCR();
 if(l==0 && c==1 && r==0) {allGo(V,V); }
  else if(l==1 && c==0 && r==0 || (l==1 && c==1 && r==0) )
  {
    while(!(l==0 && c==1 && r==0)|| (l==0 && c==0 && r==0))  
    {
      allGo(0,V+30);//120
      getLCR();      
    }
   brake();
  }
  else if(l==0 && c==0 && r==1 || (l==0 && c==1 && r==1))
  {
    while(!(l==0 && c==1 && r==0) || (l==0 && c==0 && r==0))
    {
      allGo(V+30,0);//120
      getLCR();
    }
    brake();
  }
  else  
  {
   brake();
  }
 
//
}
void getLCR(){ l=digitalRead(lt); c=digitalRead(cr); r=digitalRead(rt);}
void showLCR(){ Serial.print("l=");Serial.print(l);Serial.print(",c=");Serial.print(c);Serial.print(",r=");Serial.println(r);}
//电机驱动函数
//1.前进
void allGo(int lv,int rv)
{
  //PWM比例0~255调速，左右轮差异略增减
  //左边 电机
  digitalWrite(Left_motor_en,1);  // Left_motor_en=8  非pwm
  analogWrite(Left_motor_go,lv); //Left_motor_go=10  pwm
  analogWrite(Left_motor_back,0); //Left_motor_back=9  pwm 
  //右边电机
 digitalWrite(Right_motor_en,1);//Right_motor_en=7 非pwm
 analogWrite(Right_motor_go,rv);//Right_motor_go=6 pwm
 analogWrite(Right_motor_back,0);//Right_motor_back=5 pwm
}
//2停车
void brake(){digitalWrite(Left_motor_go,0);  digitalWrite(Left_motor_back,0);  digitalWrite(Right_motor_go,0);  digitalWrite(Right_motor_back,0); }
void brake1() { digitalWrite(Left_motor_en,0);  digitalWrite(Right_motor_en,0); }
//3后退方式的左右转
void lANDr(int qv,int hv,int fg)
{
  if(fg==1)  //后退方式左转
  {
   digitalWrite(Left_motor_en,1); analogWrite(Left_motor_go,0); analogWrite(Left_motor_back,hv); //左边电机后退
   digitalWrite(Right_motor_en,1); analogWrite(Right_motor_go,qv); analogWrite(Right_motor_back,0);//右边电机前进
   }
  else if(fg==2) //后退方式右转
  {
   digitalWrite(Left_motor_en,1); analogWrite(Left_motor_go,qv); analogWrite(Left_motor_back,0); //左边电机前进
   digitalWrite(Right_motor_en,1); analogWrite(Right_motor_go,0); analogWrite(Right_motor_back,hv);//右边电机后退
  }
  else  { digitalWrite(Left_motor_go,0);  digitalWrite(Left_motor_back,0);  digitalWrite(Right_motor_go,0);  digitalWrite(Right_motor_back,0);  }
}



