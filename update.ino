//including the libries needed
#include <LiquidCrystal.h>
#include <Servo.h>

//defining LCD pins.
const int rs = 2, en = 4, d4 = 7, d5 = 8, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int a = 0;

byte wheelone[8] = {
  B00001,
  B00010,
  B00010,
  B11111,
  B01100,
  B10010,
  B10010,
  B01100
};
byte wheeltwo[8] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B00110,
  B01001,
  B01001,
  B00110
};

byte armopen[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B01110,
  B00010,
  B01110,
  B00001
};

byte armclose[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B01110,
  B11010,
  B01110,
  B00001
};


//defining motor pins.
#define L1 10
#define L2 11
#define R1 9
#define R2 6

//definifing servos
Servo gripper;
Servo arm;
#define closed 95 //gripper
#define opened 150 //gripper
#define catching 100 //gripper
#define back 170 //arm
#define front 0 //arm

//defining ultrasonic pins.
#define trig A3
#define echo A4


//definig sensor pins.
#define L A2
#define middle A1
#define R A0

//defining buzzer pin.
#define buzzer A7

int velocityLF = 0;
int velocityRF = 0;
int velocityLB = 0;
int velocityRB = 0;

long duration, cm;
int x = 0;
char s;

void opengrip() {
  for (int pos = closed; pos <= opened; pos += 1) {
    gripper.write(pos);
    delay(15);
  }
}
void closegrip() {
  for (int pos = opened; pos >= closed; pos -= 1) {
    gripper.write(pos);
    delay(15);
  }
}
void catchgrip() {
  for (int pos = opened; pos >= catching; pos -= 1) {
    gripper.write(pos);
    delay(15);
  }
}
void armfront() {

  for (int pos = back; pos >= front; pos -= 1) {
    arm.write(pos);
    delay(15);
  }
}
void armback() {
  for (int pos = front; pos <= back; pos += 1) {
    arm.write(pos);
    delay(15);
  }
}

void proceed(int velocityLF, int velocityLB, int velocityRF, int velocityRB) {
  analogWrite(L1, velocityLF);
  analogWrite(L2, velocityLB);

  analogWrite(R1, velocityRF);
  analogWrite(R2, velocityRB);
}

void linefollow() {
  //middle
  if (digitalRead(middle) == HIGH && digitalRead(L) == LOW  && digitalRead(R) == LOW) {
    proceed(255, 0, 255, 0);
  }

  //left
  else if (digitalRead(middle) == LOW && digitalRead(L) == HIGH && digitalRead(R) == LOW) {
    proceed(0, 255, 255, 0);
    x == 1;

  }
  //Right
  else if (digitalRead(middle) == LOW && digitalRead(L) == LOW && digitalRead(R) == HIGH) {
    proceed(255, 0, 0, 255);
    x == 2;
  }
  else {
    if (x == 1) {
      proceed(0, 255, 255, 0);
    }
    else if (x == 2) {
      proceed(255, 0, 0, 255);
    }
  }
}

void distnace() {
  digitalWrite(trig, LOW);
  digitalWrite(trig, HIGH);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  cm = (duration / 2) / 29.1;
  cm = constrain(cm, 8, 400);
}

void LCDdisplay() {
  for (int i = 0; i < 6; i++) {
    lcd.setCursor(i, 0);
    lcd.print("I'M BOR3I");
    lcd.setCursor(i + 9, 0);
    if (a % 2 == 0) {
      lcd.write(byte(3));
    }
    else
      lcd.write(byte(4));
    lcd.setCursor(i + 9, 1);
    lcd.write(byte(0));
    lcd.setCursor(i + 10, 1);
    lcd.write(byte(1));
    delay(500);
    lcd.clear();
    a++;
  }
  for (int i = 5; i > -1; i--) {
    lcd.setCursor(i, 0);
    lcd.print("I'M BOR3I");
    lcd.setCursor(i + 9, 0);
    if (a % 2 == 0) {
      lcd.write(byte(3));
    }
    else
      lcd.write(byte(4));
    lcd.setCursor(i + 9, 1);
    lcd.write(byte(0));
    lcd.setCursor(i + 10, 1);
    lcd.write(byte(1));
    delay(500);
    lcd.clear();
    a++;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Made by:");
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Youssef Attia");
  lcd.setCursor(0, 1);
  lcd.print("16105131");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Youssra Adel");
  lcd.setCursor(0, 1);
  lcd.print("16106054");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ziad El-Tohamy");
  lcd.setCursor(0, 1);
  lcd.print("16104846");
  delay(750);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Abdallah Aly");
  lcd.setCursor(0, 1);
  lcd.print("16105849");
  delay(500);
  lcd.clear();
  lcd.print("Ready to use");
}

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.createChar(0, wheelone);
  lcd.createChar(1, wheeltwo);
  lcd.createChar(3, armopen);
  lcd.createChar(4, armclose);
  pinMode(L, INPUT);
  pinMode(middle, INPUT);
  pinMode(R, INPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  gripper.attach(3);
  arm.attach(5);
  armback();
  opengrip();
  LCDdisplay();
}

void loop() {
  while (!Serial.available());
  s =  Serial.read();
  switch (s) {
    //Forwrad case
    case 'F':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Moving forward");
      Serial.println("i am here");
      proceed(255,  0, 255, 0);
      break;
    //Back case
    case 'B':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Moving Backwards");
      proceed(0, 255, 0, 255);
      break;
    //Right case
    case 'R':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Moving Right");
      proceed(255, 0, 0, 0);
      break;
    //Left case
    case 'L':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Moving Left");
      proceed(0, 0, 255, 0);
      break;
    //Fowrad Right case
    case 'I':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Moving forward left");
      proceed(255, 0, 90, 0);
      break;
    //Forwad Left case
    case 'G':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Moving forward Right ");
      proceed(90, 0, 255, 0);
      break;
    //Back Right case
    case 'J':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Moving backwards left tilt");
      proceed(0, 255, 0, 90);
      break;
    //Back Left case
    case 'H':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Moving backwards right tilt");
      proceed(0, 90, 0, 255);
      break;
    //stopping case
    case 'S':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Stoping");
      proceed(255, 255, 255, 255);
      delay(15);
      proceed(0, 0, 0, 0);
      break;
    //arm front
    case 'W':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Arm front");
      armfront();
      break;
    //arm back
    case 'w':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Arm back");
      armback();
      break;
    //gripper close
    case 'U':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Gripper closed");
      closegrip();
      break;
    //gripper opened
    case 'u':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Gripper opened");
      opengrip();
      break;
    case 'X':
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Autonomous mode");
      do {
        distnace();
        if (cm <= 17) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Obstacle found!");
          proceed(255, 255, 255, 255);
          delay(15);
          proceed(0, 0, 0, 0);
          armfront();
          closegrip();
          armback();
          opengrip();
        }
        else
          linefollow();
        s =  Serial.read();
      } while (s != 'x');
      break;
  }
}
