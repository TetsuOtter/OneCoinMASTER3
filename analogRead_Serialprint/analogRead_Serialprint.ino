const int pin = A0; //"A0"のところに可変抵抗を接続したピンを指定してください。
const int btn = 7; //"7"のところにスイッチを接続したピンを指定してください。
//シリアルモニタ右下の「~~~~bps」が「9600bps」であることを確認してください。
//スイッチをONにした約3秒後に結果が返ってきます。
//もう少し早く返答してほしい場合は、下の「1000」を小さくしてください。
const float reptimes = 1000;
//以下は変更しないでください。
double val = 0;
void setup() {
  Serial.begin(9600);
  while (!Serial);
  pinMode(btn, INPUT);
}

void loop() {
  if (digitalRead(btn) == HIGH) {
    Serial.print("Please wait.... ");
    for (int i = 0; i < reptimes; i++) {
      val = val + analogRead(pin);
      delay(2);
    }
    val = val / reptimes;
    Serial.print("val = ");
    Serial.println(val);
    val = 0;
  }
  delay(10);
}
