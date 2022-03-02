/*

*/
#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial soft_ware(A0,A1);  //设置软串口

String aliyun="{\"method\":\"thing.event.property.post\",\"id\":\"123\",\"params\":{\"PM25\":";

String ali = "},\"version\":\"1.0\"}";

char data[4]={0X56,0X71,0X00,0X27}; //设置
char dataa[4]={0X56,0X11,0X00,0X47}; //设置
char dataaa[4]={0X56,0X35,0X00,0X63}; //
int zhongjian;

void setup() {
  // put your setup code here, to run once:
  soft_ware.begin(9600);
  Serial.begin(115200);
  soft_ware.write(data,4);
  soft_ware.write(dataa,4);
  soft_ware.write(dataaa,4);
  soft_ware.listen();
}

String device_A_String="";
void loop() {
  // put your main code here, to run repeatedly:
  if(soft_ware.available()>0){
    if(soft_ware.peek()!='\n')   //在没接收到回车换行的条件下
    {
      device_A_String+=(char)soft_ware.read();   //这段代码是在把字符串联成字符串
    }
    else
    {  
      //这段代码实现从缓冲区读取数据，并将数据发送到计算机显示和软串口发送；
      soft_ware.read();
      int a = device_A_String.substring(7,12).toInt();
      if((zhongjian-a)>1000){
        Serial.print(aliyun+String(a)+ali);
        delay(400);
        // 
        zhongjian = a;
      }
      else{
        zhongjian = a;
      }
      device_A_String="";
    }
  }
}
