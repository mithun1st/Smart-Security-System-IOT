#include<LiquidCrystal.h>
#include <Servo.h>
#include <dht.h>

LiquidCrystal lcd(33, 31, 29, 27, 25, 23);
Servo door;
dht d;

const byte red = 10, green = 9, blue = 8, buz = 36, light = 2, fan = 3, srv = 37, dht = A0, pir = A8;

int count = 0;
bool pState = false;

String pas = "alpha", ext = "close"; //input (system on and exit code)

void setup() {
  pinMode(pir, INPUT);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(buz, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(fan, OUTPUT);

  door.attach(srv);

  lcd.begin(16, 2);

  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  digitalWrite(buz, 1);
  lcd.setCursor(1, 0);

  lcd.print("Mahadi Hassan");
  lcd.setCursor(4, 1);
  lcd.print("MITHUN");
  delay(1000);

  digitalWrite(buz, 0);

  lcd.noDisplay();
  delay(200);
  lcd.display();

}

void loop() {

  String s = "";
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Enter Command:");
  lcd.setCursor(0, 1);
  lcd.print(">> ");

  Serial.println("Enter Command:");

    for (int i = 0; !(Serial2.available() || Serial3.available()); i++) {
    delay(100);
    if (i == 5) {
      lcd.cursor();
    }
    if (i == 10) {
      lcd.noCursor();
      i = 0;
    }
  }

  while (Serial2.available()) {
    s +=  (char)Serial2.read();
    delay(50);
    count = 0;
  }
  while (Serial3.available()) {
    s +=  (char)Serial3.read();
    delay(50);
    count = 0;
  }


  if (s != pas && s != "") {
    lcd.print(s);
    digitalWrite(green, 1);
    digitalWrite(buz, 1);
    delay(200);

    Serial.println(s);

    digitalWrite(buz, 0);
    delay(1500);
    digitalWrite(blue, 0);
    digitalWrite(green, 0);
  }

  if (s != "") {
    lcd.clear();
    digitalWrite(blue, 0);

    if (s == pas) {

      digitalWrite(blue, 1);
      digitalWrite(green, 1);
      digitalWrite(buz, 1);
      delay(200);


      lcd.setCursor(0, 0);
      lcd.print("Enter Command:");
      lcd.setCursor(0, 1);
      lcd.print(">> ******");

      digitalWrite(buz, 0);
      delay(2000);
      digitalWrite(blue, 0);
      digitalWrite(green, 0);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Command Accecpt");
      lcd.setCursor(3, 1);
      lcd.print("welcome");

      Serial.println("Command Accecpt");

      digitalWrite(buz, 1);
      digitalWrite(green, 1);
      delay(700);
      for (int i = 0; i < 2; i++) {
        digitalWrite(buz, 0);
        digitalWrite(green, 0);
        lcd.noDisplay();
        delay(500);

        digitalWrite(buz, 1);
        digitalWrite(green, 1);
        lcd.display();
        delay(500);
      }
      digitalWrite(buz, 0);
      digitalWrite(green, 0);
      delay(500);
      digitalWrite(green, 1);
      lcd.clear();

      Serial.println("System is ON");

      while (s != ext) {
        lcd.setCursor(0, 0);
        lcd.print("Your System");
        lcd.setCursor(0, 1);
        lcd.print("is on: ");
        delay(100);


        s = "";
        while (Serial2.available()) {
          s +=  (char)Serial2.read();
          delay(50);
          count = 0;
        }
        while (Serial3.available()) {
          s +=  (char)Serial3.read();
          delay(50);
          count = 0;
        }

        //pir
        if (digitalRead(pir) && pState) {
          digitalWrite(buz, 1);
          digitalWrite(red, 1);
          delay(100);
          digitalWrite(red, 0);
          digitalWrite(buz, 0);
          delay(100);

          Serial.println("Detected  ! ! !");
        }



        if (s != "") {


          if (s == ext) {
            digitalWrite(blue, 1);
            digitalWrite(buz, 1);
            lcd.print("log off...");
            delay(1000);
            digitalWrite(buz, 0);
            delay(200);
            digitalWrite(blue, 0);

            Serial.println("Log OFF . . .");
          }


          //-------------------------------      input Section

          else if (s == "a1") {
            digitalWrite(light, 1);
            stateDisplay("Light ON");

            Serial.println("Light ON . . .");
          }
          else if (s == "a0") {
            digitalWrite(light, 0);
            stateDisplay("Light OFF");

            Serial.println("Light OFF . . .");
          }

          else if (s == "b1") {
            digitalWrite(fan, 1);
            stateDisplay("Fan ON");

            Serial.println("Fan ON . . .");
          }
          else if (s == "b0") {
            digitalWrite(fan, 0);
            stateDisplay("Fan OFF");

            Serial.println("Fan OFF . . .");
          }

          else if (s == "c1") {
            doorOpen();
            stateDisplay("Door OPEN");

            Serial.println("Door OPEN . . .");
          }
          else if (s == "c0") {
            doorClose();
            stateDisplay("DoorCLOSE");

            Serial.println("Door CLOSE . . .");
          }

          else if (s == "p.on") {
            stateDisplay("Pir ON");
            pState = true;

            Serial.print("Motion Sensor ON . . .");
          }
          else if (s == "p.off") {
            stateDisplay("Pir OFF");
            pState = false;

            Serial.print("Motion Sensor OFF . . .");
          }


          else if (s == "d.on") {
            digitalWrite(blue, 1);
            digitalWrite(buz, 1);
            lcd.setCursor(0, 0);
            lcd.print("  Temperature  ");
            lcd.setCursor(0, 1);
            lcd.print("   Humidity    ");
            delay(100);
            digitalWrite(buz, 0);
            delay(2000);
            lcd.clear();
            digitalWrite(blue, 0);

            Serial.println("DHT11 Sensor ON . . .");

            do {
              d.read11(dht);
              lcd.setCursor(0, 0);
              lcd.print("  Temp = ");
              lcd.print((int)d.temperature);
              lcd.print(" c");
              lcd.setCursor(0, 1);
              lcd.print("   Humi = ");
              lcd.print((int)d.humidity);
              delay(2000);

              Serial.print("Temperature = ");
              Serial.println(d.temperature);
              Serial.print("Humidity = ");
              Serial.println((String)d.humidity + "\n");
            }
            while (!(Serial2.available() || Serial3.available()));
          }
          else if (s == "d.off") {
            stateDisplay("DHT11 OFF");
          }


          //else if (input Function)


          else {
            Serial.print("keyWord not Found !! ");

            digitalWrite(blue, 1);
            digitalWrite(buz, 1);
            lcd.print("incorrect");
            lcd.setCursor(12, 0);
            lcd.print("-x-");
            delay(1000);
            lcd.clear();
            digitalWrite(buz, 0);
            digitalWrite(blue, 0);
          }

        }

        //dim light
        if (count > 40) {
          analogWrite(green, 30);
        }
        else {
          digitalWrite(green, 1);
        }
        count++;

      }
      digitalWrite(green, 0);
      digitalWrite(buz, 1);
      delay(700);
      digitalWrite(buz, 0);
      digitalWrite(green, 0);
      lcd.display();
    }

    else {
      lcd.noDisplay();
      delay(200);
      lcd.display();
      lcd.setCursor(0, 0);
      lcd.print("Access Denied !!");
      lcd.setCursor(4, 1);
      lcd.print("error");

      Serial.println("Command ERROR !!");


      for (int i = 0; i < 5; i++) {
        digitalWrite(buz, 1);
        digitalWrite(red, 1);
        delay(150);
        digitalWrite(red, 0);
        digitalWrite(buz, 0);
        delay(150);
      }
      lcd.noDisplay();
      digitalWrite(buz, 1);
      delay(500);
      lcd.display();
      digitalWrite(buz, 0);
    }
  }

  //dim light
  if (count > 4) {
    analogWrite(blue, 30);
  }
  else {
    digitalWrite(blue, 1);
  }
  count++;
}

//function
void doorOpen() {
  door.write(0);
}
void doorClose() {
  door.write(180);
}

void stateDisplay(String a) {
  digitalWrite(blue, 1);
  digitalWrite(buz, 1);
  lcd.print(a);
  lcd.setCursor(12, 0);
  lcd.print("- :)");
  delay(100);
  digitalWrite(buz, 0);
  delay(2000);
  lcd.clear();
  digitalWrite(blue, 0);
}
