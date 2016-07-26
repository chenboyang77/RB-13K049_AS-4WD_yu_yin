int srfPin = 15; //定义srfPin 发送引脚为15
int z; //定义全局变量z
int Distance; //定义距离寄存器存放测试距离数据
int duration; //定义脉宽寄存器
int data; //定义串口接收寄存器
#define EA 5
#define I2 6
#define I1 7
#define EB 11
#define I4 10
#define I3 9 
int ultrasonic(int distance)
{ 
  digitalWrite(srfPin, LOW); //确保在发送脉冲前保持该引脚为低电平
  delayMicroseconds(2); //保持低电平2ms
  digitalWrite(srfPin, HIGH); //发送一个高脉冲开始测距
  delayMicroseconds(10); //保持10ms
  digitalWrite(srfPin, LOW); //在等待脉冲返回来之前发送低电平
  pinMode(srfPin, INPUT); //调整超声波引脚为输入
  duration = pulseIn(srfPin, HIGH); //从SRF05 回波脉冲在读取在微秒
  distance = duration/58; //除以58 就是我们要得到的厘米数
  return distance; //返回厘米数
}
void BACK() //后退
{
  analogWrite(EA,130);//输入模拟值进行设定速度
  analogWrite(EB,130);
  digitalWrite(I2,HIGH);//使直流电机运转
  digitalWrite(I1,LOW);
  digitalWrite(I3,HIGH);//使直流电机运转
  digitalWrite(I4,LOW);
}
void GO() //前进
{
  analogWrite(EA,100);//输入模拟值进行设定速度
  analogWrite(EB,100);
  digitalWrite(I2,LOW);//使直流电机运转
  digitalWrite(I1,HIGH);
  digitalWrite(I3,LOW);//使直流电机运转
  digitalWrite(I4,HIGH); 
}
void QUICKEN() //加速前进
{
  analogWrite(EA,140); //输入模拟值进行设定速度
  analogWrite(EB,140);
  digitalWrite(I2,LOW);//使直流电机运转
  digitalWrite(I1,HIGH);
  digitalWrite(I3,LOW);//使直流电机运转
  digitalWrite(I4,HIGH); 
}
void FULLSPEED() //全速前进
{
  analogWrite(EA,165); //输入模拟值进行设定速度
  analogWrite(EB,165);
  digitalWrite(I2,LOW);//使直流电机运转
  digitalWrite(I1,HIGH);
  digitalWrite(I3,LOW);//使直流电机运转
  digitalWrite(I4,HIGH); 
}
void LEFT() //左转
{
analogWrite(EA,130);//输入模拟值进行设定速度
analogWrite(EB,130);
digitalWrite(I2,LOW);//使直流电机运转
digitalWrite(I1,HIGH);
digitalWrite(I3,HIGH);//使直流电机运转
digitalWrite(I4,LOW);
}
void RIGHT() //右转
{
  analogWrite(EA,130);//输入模拟值进行设定速度
  analogWrite(EB,130);
  digitalWrite(I2,HIGH);//使直流电机运转
  digitalWrite(I1,LOW);
  digitalWrite(I3,LOW);//使直流电机运转
  digitalWrite(I4,HIGH); 
}
void STOP() //停止
{
  digitalWrite(I2,HIGH);//使直流电机停转
  digitalWrite(I1,HIGH);
  digitalWrite(I3,HIGH);//使直流电机停转
  digitalWrite(I4,HIGH);
}
void PLAYDISTANCE() //发送超声波数据
{
  Distance = ultrasonic(z);
    if(Distance > 0 && Distance <= 10){ //判断测试距离为1 至10CM
      Serial.print('a');} //发送字符'a'
    else if(Distance > 10 && Distance <= 15){ //判断测试距离为11 至15CM
      Serial.print('b');} //发送字符'b'
    else if(Distance > 15 && Distance <= 20){
      Serial.print('c');}
    else if(Distance > 20 && Distance <= 25){
      Serial.print('d');}
    else if(Distance > 25 && Distance <= 30){
      Serial.print('e');}
    else if(Distance > 30 && Distance <= 35){
      Serial.print('f');}
    else if(Distance > 35 && Distance <= 40){
      Serial.print('g');}
    else if(Distance > 40 && Distance <= 45){
      Serial.print('h');}
    else if(Distance > 45 && Distance <= 50){
      Serial.print('i');}
    else if(Distance > 50 && Distance <= 55){
      Serial.print('j');}
    else if(Distance > 55 && Distance <= 60){
      Serial.print('k');}
    else if(Distance > 60 && Distance <= 65){
      Serial.print('l');}
    else if(Distance > 65 && Distance <= 70){
      Serial.print('m');}
    else if(Distance > 70 && Distance <= 75){
      Serial.print('n');}
    else if(Distance > 75 && Distance <= 80){
      Serial.print('o');}
    else if(Distance > 80 && Distance <= 85){
      Serial.print('p');}
    else if(Distance > 85 && Distance <= 90){
      Serial.print('q');}
    else if(Distance > 90 && Distance <= 95){
      Serial.print('r');}
    else{
      Serial.print('~');}
}
void setup()
{
  Serial.begin(115200); //打开串口并设置通信波特率为115200
  pinMode(9,OUTPUT); //定义I3  接口
  pinMode(10,OUTPUT); //定义I4 接口
  pinMode(11,OUTPUT); //定义EB(PWM 调速)接口
  pinMode(5,OUTPUT); //定义EA(PWM 调速)接口
  pinMode(6,OUTPUT); //定义I2接口
  pinMode(7,OUTPUT); //定义I1接口
}
void loop() //主程序开始
{ 
  Distance = ultrasonic(z); //读取超声波值
  data = Serial.read(); //读取串口数据
  switch (data){
     case 'W': //前进命令
          GO(); //前进函数
          Serial.flush(); //刷新串口缓冲区数据
          break;
     case 'X': //后退命令
          BACK(); //后退函数
          Serial.flush(); //刷新串口缓冲区数据
          break;
     case 'A': //左转命令
          LEFT(); //左转函数
          Serial.flush(); //刷新串口缓冲区数据
          break;
     case 'D': //右转命令
          RIGHT(); //右转函数
          Serial.flush(); //刷新串口缓冲区数据
          break;
     case 'S': //停止命令
          STOP(); //停止函数
          Serial.flush(); //刷新串口缓冲区数据
          break;
     case '1': //加速前进命令
          QUICKEN(); //加速前进函数
          Serial.flush(); //刷新串口缓冲区数据
     case '2': //全速前进命令
          FULLSPEED(); //全速前进函数
          Serial.flush(); //刷新串口缓冲区数据
          break;
     case '#': //测试当前距离命令
          PLAYDISTANCE(); //发送当前距离函数
          Serial.flush(); //刷新串口缓冲区数据
          break;
     default:
          break;
}
}
