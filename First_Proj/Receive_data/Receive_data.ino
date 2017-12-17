//nrf24l01(통신모듈) 라이브러리
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//서보모터 라이브러리
#include <Servo.h>
Servo myservo;
int angle = 0;
int Plant =0;


RF24 radio(7, 8); // SPI 버스에 nRF24L01 라디오를 설정하기 위해 CE, CSN 선언.
const byte address[6] = "00001"; //주소값을 5가지 문자열로 변경할 수 있으며, 송신기과 수신기가 동일한 주소로 해야됨.



void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN); //전원공급에 관한 파워레벨을 설정합니다. 모듈 사이가 가까우면 최소로 설정합니다.

  //거리가 가까운 순으로 RF24_PA_MIN / RF24_PA_LOW / RF24_PA_HIGH / RF24_PA_MAX 등으로 설정할 수 있습니다.

  //높은 레벨(거리가 먼 경우)은 작동하는 동안 안정적인 전압을 가지도록 GND와 3.3V에 바이패스 커패시터 사용을 권장함
  radio.startListening(); //모듈을 수신기로 설정

  //서보모터 설정
  myservo.attach(A3);

  //LED 핀들의 설정을 해줍니다.
  pinMode(9, OUTPUT);

}
void loop() {

    delay(5000);
      
    radio.read(&Plant, sizeof(Plant));
   

    Serial.println(Plant);
    

  switch (Plant){
    
    case 0: // 모두 정상
     if(angle != 0){
      angle = 0;
      myservo.write(angle);
     // delay(1000)
      break;
    }
    break;
    case 1: // 조도이상 -> 45도 회전
    if(angle != 45){
      angle = 45;
      myservo.write(angle);
   //   delay(1000);
      break;
    }
    break;
    case 2: // 온도이상 -> 90도 회전
    if(angle != 90){
      angle = 90;
      myservo.write(angle);
      //delay(1000);
      break;
    }
    break;
    case 3: // 습도이상 -> 135도 회전
      if(angle != 135){
        angle = 135;
        myservo.write(angle);
       // delay(1000);
        break;
      }
      break;
    case 4: //  온도,습도이상 -> 180도 회전
    if(angle != 180){
      angle = 180;
      myservo.write(angle);
    //  delay(1000);
      break;
    }     break;

      
  }
}
