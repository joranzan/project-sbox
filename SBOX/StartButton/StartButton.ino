// 구조체 정의
struct Button {
  int pin;  // 버튼 핀 번호
  int state;  // 버튼 상태를 저장할 변수
  int lastState; // 이전 버튼 상태를 저장할 변수
  unsigned long lastDebounceTime; // 마지막 디바운싱 타임스탬프
};

// 버튼 객체 생성
Button coinInsert = {12, 0, HIGH, 0}; // 코인 삽입 버튼
Button button1p = {11, 0, HIGH, 0};   // 1p 버튼
Button button2p = {13, 0, HIGH, 0};   // 2p 버튼

int coinSignal = 2;
bool isInserted = false;

unsigned long debounceDelay = 50;    // 디바운싱 딜레이

void setup() {
  Serial.begin(115200);
  pinMode(coinInsert.pin, INPUT_PULLUP);
  pinMode(button1p.pin, INPUT_PULLUP);
  pinMode(button2p.pin, INPUT_PULLUP);
  pinMode(coinSignal, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(coinSignal), coinInterrupt, FALLING );  
  
  delay(100);
}

void loop() {
  // 코인 삽입 버튼 업데이트
  updateButton(&coinInsert);
  // 1p 버튼 업데이트
  updateButton(&button1p);
  // 2p 버튼 업데이트
  updateButton(&button2p);

  if(isInserted){
    isInserted = false;
    Serial.println("coin");
    // delay(2000);
  }
}

// 버튼 업데이트 함수
void updateButton(Button *button) {
  int reading = digitalRead(button->pin);

  if (reading != button->lastState) {
    button->lastDebounceTime = millis();
  }

  if ((millis() - button->lastDebounceTime) > debounceDelay) {
    if (reading != button->state) {
      button->state = reading;

      if (button->state == LOW) {
        if (button == &coinInsert) {
          Serial.println("coin");
        } else if (button == &button1p) {
          Serial.println("1p");
        } else if (button == &button2p) {
          Serial.println("2p");
        }
      }
    }
  }

  button->lastState = reading;
}


void coinInterrupt(){
  isInserted = true;
  Serial.println("coinInterrupt");
  delay(1000);
}
