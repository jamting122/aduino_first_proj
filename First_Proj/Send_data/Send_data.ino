#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8); // SPI 버스에 nRF24L01 라디오를 설정하기 위해 CE, CSN를 선언.
const byte address[6] = "00001"; //주소값을 5가지 문자열로 변경할 수 있으며, 송신기와 수신기가 동일한 주소로 해야됨.

int TemperaturePin;
int LightPin;
int MoiPin;

void setup() {
  Serial.begin(9600);
  TemperaturePin = A1; //온도핀 설정
  LightPin = A0; //  조도핀 설정
  MoiPin = A2; // 습도핀 설정

  radio.begin();
  radio.openWritingPipe(address); //이전에 설정한 5글자 문자열인 데이터를 보낼 수신의 주소를 설정
  radio.setPALevel(RF24_PA_MIN); //전원공급에 관한 파워레벨을 설정합니다. 모듈 사이가 가까우면 최소로 설정합니다.

  //거리가 가까운 순으로 RF24_PA_MIN / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX 등으로 설정할 수 있습니다.

  //높은 레벨(거리가 먼 경우)은 작동하는 동안 안정적인 전압을 가지도록 GND와 3.3V에 바이패스 커패시터 사용을 권장함.

  radio.stopListening();  //모듈을 송신기로 설정
}

void loop() {
  int Plant; // 식물의 상태변수 4단계.

  int tem = analogRead(TemperaturePin);  //온도센서 읽기.


  Serial.print("온도:");
  Serial.print(tem);
  Serial.println();


  float moi = analogRead(MoiPin);
  Serial.print("습도:");
  Serial.print(moi);
  Serial.println();


  float light = analogRead(LightPin);
  Serial.print("조도:");
  Serial.print(light, DEC);
  Serial.println();


  if (light < 600) {
    if (tem < 70 && tem > 30) { //정상
      if (moi < 800 ) {
        Plant = 0;
      }
      else {
        Plant = 3;
      }
    }
    else {
      if (moi > 800 ) {
        Plant = 2;
      }
      else {
        Plant = 4;
      }
    }
  }

  else {
    Plant = 1;
  }

  radio.write(&Plant, sizeof(Plant)); //해당 메시지를 수신자에게 보냄
  delay(1000);



}
