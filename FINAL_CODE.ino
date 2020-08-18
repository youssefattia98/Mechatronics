//defining motor pins.
#define L1 10
#define L2 11
#define R1 5
#define R2 6

//definig sensor pins
#define L 7
#define middle 8
#define R 4

#define buzzer 12

int velocityLF = 0;
int velocityRF = 0;
int velocityLB = 0;
int velocityRB = 0;


int x = 0;
char s;

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

void setup() {
  Serial.begin(115200);
  pinMode(L, INPUT);
  pinMode(middle, INPUT);
  pinMode(R, INPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  while (!Serial.available());
  s =  Serial.read();
  switch (s) {
    //Forwrad case
    case 'F':
      proceed(255,  0, 255, 0);
      break;
    //Back case
    case 'B':
      proceed(0, 255, 0, 255);
      break;
    //Right case
    case 'R':
      proceed(255, 0, 0, 0);
      break;
    //Left case
    case 'L':
      proceed(0, 0, 255, 0);
      break;
    //Fowrad Right case
    case 'I':
      proceed(255, 0, 90, 0);
      break;
    //Forwad Left case
    case 'G':
      proceed(90, 0, 255, 0);
      break;
    //Back Right case
    case 'J':
      proceed(0, 255, 0, 90);
      break;
    //Back Left case
    case 'H':
      proceed(0, 90, 0, 255);
      break;
    //stopping case
    case 'S':
      proceed(255, 255, 255, 255);
      break;
    //Buzzer ON case
    case 'V':
      digitalWrite(buzzer, HIGH);
      break;
    //Buzzeer OFF case
    case 'v':
      digitalWrite(buzzer, LOW);
      break;
    //Rotate cw case
    case 'X':
      proceed(255, 0, 0, 255);
      break;
    //Rotate ccw case
    case 'x':
      proceed(0, 255, 255, 0);
      break;
    case 'W':
      do {
        linefollow();
        s =  Serial.read();
      } while (s != 'w');
      break;
  }
}
