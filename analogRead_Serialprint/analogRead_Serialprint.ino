const int pin = A0; //"A0"のところに可変抵抗を接続したピンを指定してください。
const int btn = 7; //"7"のところにスイッチを接続したピンを指定してください。

//以下は変更しないでください。
float val = 0;
void setup() {
  Serial.begin(9600);
  while (!Serial);
  pinMode(btn, INPUT);
}

void loop() {
  if (digitalRead(btn) == HIGH) {
    Serial.print("Please wait.... ");
    for (int i = 0; i < 100000; i++) {
      val = val + analogRead(pin);
      delayMicroseconds(5);
    }
    val = val / 100000;
    Serial.print("val = ");
    Serial.println(val);
    val = 0;
  }
  delay(10);
}
