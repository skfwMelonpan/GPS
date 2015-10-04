#include <SoftwareSerial.h>
// 2:RX,3:TXでシリアル通信する宣言
SoftwareSerial mySerial(2, 3);

long int Tido = 35436681;
long int Tkeido = 139337911;

String inputString = "";

String Data[16];

float deg;
long int ido,keido;

char moji;

void setup() {
  // 9600 bpsで接続（パソコンとの通信
  Serial.begin(9600);         
  // 9600 bpsで接続（GT-720Fとの通信）
  mySerial.begin(9600);
  // シリアル通信のテスト
  Serial.println("Program Setting");
}

void loop() {
  int i=0;
  
  if(mySerial.available()){
    moji = mySerial.read();
    if(moji=='$'){
      inputString = "";
      i=0;
      while(1){
        moji = mySerial.read();
        if(moji==-1){
          continue;
        }
        else if(moji==','){
          Data[i]=inputString;
          inputString = "";
          if(Data[0]!="GPRMC") break;
          i++;
        }
        else if(moji=='\r' || moji=='\n'){
          ido = Data[3].substring(5, 9).toInt() + Data[3].substring(0, 4).toInt()*10000;
          keido = Data[5].substring(6, 10).toInt() + Data[5].substring(0, 5).toInt()*10000;
          deg = Data[8].toFloat();

          Serial.print(ido);    Serial.print("\t");
          Serial.print(keido);  Serial.print("\t");
          Serial.println(deg);
          
          break;
        }
        else inputString += moji;
      }
    }
  }
}

