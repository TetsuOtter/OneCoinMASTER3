//One Coin M@STER version 2.0.1
//Tech Otter(https://technotter.com)
//Tetsu Otter(https://twitter.com/tetsu_otter)
const int rever = A2; //"A1"にレバーサー可変抵抗を接続したピンを入力してください。
const int mascon = A2; //"A2"にノッチ可変抵抗を接続したピンを入力してください。1ハンドルの場合は下と同じピンを指定してください。
const int brakevr = A2;//"A2"にブレーキ可変抵抗を接続したピンを入力してください。1ハンドルの場合は上と同じピンを指定してください。
const float levN = 500; //"500"のところに中立位置の時のレバーサー可変抵抗の出力値を入力してください。
const float levF = 750; //"750"のところに前進位置の時のレバーサー可変抵抗の出力値を入力してください。
const float levR = 250; //"250"のところに後退位置の時のレバーサー可変抵抗の出力値を入力してください。
const int brnum = 9; //制動段の数(非常ブレーキ含む)に1を足した数を入力してください。
const int nonum = 6; //力行段の数に1を足した数を入力してください。
const int btnum = 2;//ボタンの数を入力してください。最大値は20です。
const int brake[brnum] = {600, 650, 700, 750, 800, 850, 900, 950, 1000}; //{}内に各段における出力値を "N(B0)の位置から順に" 整数で入力してください。
const int notch[nonum] = {550, 500, 400, 300, 200, 100}; //{}内に各段における出力値を "N(P0)の位置から順に" 整数で入力してください。
const int button[btnum] = {2, 3}; //{}内にボタンを接続したピンの番号を入力してください。左からボタン1,ボタン2...となります。


//ここから下は手を触れないでください。
float sikiFN = 0;
float sikiNR = 0;
float where = 0;
float rev = 0;
int wh = 0;
int wh2 = 0;
float reval = 0;
float masal = 0;
float brkal = 0;
float btnari = 0;
float btnhis[btnum];
void setup() {
  for (int i = 0; i < btnum; i++) {
    btnhis[i] = 0;
  }
  Serial.begin(9600);
  while (!Serial);
  sikiFN = levN + (levF - levN) / 2;
  sikiNR = levN - (levN - levR) / 2;
  Serial.print("TORN\r");
  nocom(1);
  nocom(0);
  brcom(6);
}

void loop() {
  ave();
  reverser();
  buttoncom();
  masconhand();
}

void buttoncom() {
  for (int i = 0; i < btnum; i++) {
    if (digitalRead(button[i]) != btnhis[i]) {
      if (digitalRead(button[i]) == HIGH) {
        btnhis[i] = digitalRead(button[i]);
        i = i + 1;
        Serial.print("TOK");
        Serial.print(i);
        Serial.print("D\r");
        i = i - 1;
      } else {
        btnhis[i] = digitalRead(button[i]);
        i = i + 1;
        Serial.print("TOK");
        Serial.print(i);
        Serial.print("U\r");
        i = i - 1;
      }
    }
  }
}

void masconhand() {
  //masal
  float a = 0;
  float b = 0;

  //brakecommand
  for (int i = 0; i <= brnum; i++) {
    if (i == 0) {
      a = (brake[1] - brake[0]) / 2;
      a = a + brake[0];
      if (brkal < a) {
        brcom(0);
        goto brout;
      }
    }
    else if (i < (brnum - 1)) {
      a = (brake[i + 1] - brake[i]) / 2;
      a = a + brake[i];
      b = (brake[i] - brake[i - 1]) / 2;
      b = b + brake[i - 1];
      if (brkal > b && brkal < a) {
        //int s = 50 + i;
        //mascom(s);
        brcom(i);
        goto brout;
      }
    }
    else {
      int s = brnum - 1;
      brcom(s);
      goto brout;
    }
  }
brout:

  //notchcommand
  for (int i = 0; i <= nonum; i++) {
    if (i == 0) {
      a = (notch[0] - notch[1]) / 2;
      a = a + notch[1];
      if (masal > a) {
        nocom(0);
        goto out;
      }
    }
    else if (i < (nonum - 1)) {
      a = (notch[i - 1] - notch[i]) / 2;
      a = a + notch[i];
      b = (notch[i] - notch[i + 1]) / 2;
      b = b + notch[i + 1];
      if (masal > b && masal < a) {
        nocom(i);
        goto out;
      }
    }
    else {
      int s = nonum - 1;
      nocom(s);
      goto out;
    }
  }
out:
  delay(5);
}
void brcom(int command) {
  if (wh != command) {
    Serial.print("TOB");
    Serial.print(command);
    Serial.print("\r");
    wh = command;
  }
}
void nocom(int command) {
  if (wh2 != command) {
    Serial.print("TOP");
    Serial.print(command);
    Serial.print("\r");
    wh2 = command;
  }

}
void reverser() {
  if (reval > sikiFN && rev != 2) {
    Serial.print("TORF\r");
    rev = 2;
  } else if (reval < sikiNR && rev != 1) {
    Serial.print("TORB\r");
    rev = 1;
  } else if (reval > sikiNR && reval < sikiFN && rev != 0) {
    Serial.print("TORN\r");
    rev = 0;
  }
}
void ave() {
  reval = 0;
  masal = 0;
  brkal = 0;
  for (int i = 0; i < 100; i++) {
    reval = reval + analogRead(rever);
    masal = masal + analogRead(mascon);
    brkal = brkal + analogRead(brakevr);
  }
  reval = reval / 100;
  masal = masal / 100;
  brkal = brkal / 100;
}

