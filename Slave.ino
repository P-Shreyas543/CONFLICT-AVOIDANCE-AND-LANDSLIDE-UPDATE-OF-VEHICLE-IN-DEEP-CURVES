#include <esp_now.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>

#define buzzerPin 4  // buzzer Pin as Output
#define clearPin 2   // pushbutton Pin

int i;
int SensorVal;
bool VibrationVal;
bool UltrasonicVal;

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

// Must match the sender structure
typedef struct test_struct {
  int rainVal;
  bool VibVal;
  bool ultraVal;
} test_struct;

// Create a struct_message called myData
test_struct myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  int previous_condition = 0;  // Initialize previous_condition for landslide sensor
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);

  // Vibration Sensor
  Serial.print("VibrationVal: ");
  Serial.println(myData.VibVal);
  VibrationVal = myData.VibVal;

  // ultrasonic sensor
  Serial.print("Ultrasonic: ");
  Serial.println(myData.ultraVal);
  UltrasonicVal = myData.ultraVal;

  // Rain Sensor
  Serial.print("RainVal: ");
  Serial.println(myData.rainVal);
  SensorVal = myData.rainVal;
}
void setup() {
  Serial.begin(115200);
  Serial.print("MAC Address : ");
  Serial.println(WiFi.macAddress());

  //Initialize I2C 16x2 LCD Display
  lcd.init();           // initialize LCD
  lcd.backlight();      // turn on LCD backlight
  lcd.begin(16, 2);     // Make sure backlight is on
  lcd.setCursor(4, 0);  //Set cursor to character 2 on line 0
  lcd.print("HELLO :)");
  lcd.setCursor(4, 1);  //Move cursor to character 2 on line 1
  lcd.print("WELCOME");
  delay(5000);

  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Define pinmode
  pinMode(buzzerPin, OUTPUT);
  pinMode(clearPin, INPUT);
  digitalWrite(clearPin, LOW);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    lcd.clear();
    lcd.setCursor(1, 0);  //Set cursor to character 2 on line 0
    lcd.print("---------------");
    lcd.setCursor(1, 1);  //Move cursor to character 2 on line 1
    lcd.print("...ERROR...");
    delay(5000);
    return;
  }
  // Once ESPNow is successfully Init, we will register for recv CB to
  esp_now_register_recv_cb(OnDataRecv);  // get recv packer info
}

void loop() {
  if (VibrationVal) {
    lcd.clear();
    while (digitalRead(clearPin) == LOW) {
      lcd.setCursor(4, 0);
      lcd.print("DANGER");
      Serial.println("Landslide");
      lcd.setCursor(3, 1);
      lcd.print("LANDSLIDE");
      digitalWrite(buzzerPin, HIGH);
    }
  }
  if (UltrasonicVal) {
    lcd.clear();
    while (digitalRead(clearPin) == LOW) {
      Serial.println("Go Slow");
      lcd.setCursor(4, 0);
      lcd.print("GO SLOW");
      lcd.setCursor(1, 1);
      lcd.print("VEHICLE A HEAD");
      digitalWrite(buzzerPin, HIGH);
      delay(25);  //wait for 25ms
      digitalWrite(buzzerPin, LOW);
      delay(25);  //wait for 25ms
    }
  } else {
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("ROAD IS CLEAR");
    digitalWrite(buzzerPin, LOW);
    delay(1000);
  }
  if (SensorVal > 2500) {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("NO RAIN");
    delay(1000);
  }
  if (SensorVal <= 2500 && SensorVal > 1800) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AMOUNT: LOW");
    lcd.setCursor(0, 1);
    lcd.print("IT IS RAINING");
    for (i = 0; i < 20; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(50);  //wait for 10ms
      digitalWrite(buzzerPin, LOW);
      delay(50);  //wait for 10ms
    }
  }
  if (SensorVal <= 1800 && SensorVal > 860) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AMOUNT: MEDIUM");
    lcd.setCursor(0, 1);
    lcd.print("IT IS RAINING");
    for (i = 0; i < 20; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(50);  //wait for 10ms
      digitalWrite(buzzerPin, LOW);
      delay(50);  //wait for 10ms
    }
  }
  if (SensorVal < 860) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AMOUNT: HIGH");
    lcd.setCursor(0, 1);
    lcd.print("IT IS RAINING");
    for (i = 0; i < 40; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(25);  //wait for 25ms
      digitalWrite(buzzerPin, LOW);
      delay(25);  //wait for 25ms
    }
  }
}
