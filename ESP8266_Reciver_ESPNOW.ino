#include <espnow.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>

const int buzzerPin = 16;  // D0

bool VibrationVal = false;
bool UltrasonicVal = false;
int SensorVal = 0;

unsigned long lastReceivedTime = 0;          // Track last data received time
const unsigned long timeoutDuration = 5000;  // 5 seconds

// Must match the sender structure
typedef struct struct_message {
  bool VibVal;
  bool ultraVal;
  int rainVal;
} struct_message;

struct_message myData;  // Create a struct_message called myData

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C LCD initialization

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);

  // Update values from received data
  VibrationVal = myData.VibVal;
  UltrasonicVal = myData.ultraVal;
  SensorVal = myData.rainVal;

  Serial.print("VibrationVal: ");
  Serial.println(VibrationVal);
  Serial.print("Ultrasonic: ");
  Serial.println(UltrasonicVal);
  Serial.print("RainVal: ");
  Serial.println(SensorVal);

  // Update last received time
  lastReceivedTime = millis();
}

void displayRainAmountAndSoundBuzzer(int SensorVal) {
  // Variables for buzzer and LCD behavior
  int buzzerDuration = 0;  // Number of beep cycles
  int buzzerDelay = 0;     // Delay between ON and OFF states
  bool isRaining = false;  // Indicates whether it's raining
  String rainStatus = "";

  // Determine rain level based on SensorVal
  if (SensorVal < 800) {
    rainStatus = "HIGH";  // Heavy rain
    buzzerDuration = 6;
    buzzerDelay = 200;
    isRaining = true;
  } else if (SensorVal >= 800 && SensorVal < 950) {
    rainStatus = "MEDIUM";  // Moderate rain
    buzzerDuration = 4;
    buzzerDelay = 300;
    isRaining = true;
  } else if (SensorVal >= 950 && SensorVal < 1024) {
    rainStatus = "LOW";  // Light rain
    buzzerDuration = 2;
    buzzerDelay = 400;
    isRaining = true;
  } else {
    rainStatus = "NONE";  // No rain
    isRaining = false;
  }

  if (isRaining) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RAIN LEVEL: " + rainStatus);
    lcd.setCursor(0, 1);
    lcd.print("RAIN DETECTED");
    delay(1000);  // Delay to allow users to see both lines
    Serial.println("Rain detected: " + rainStatus);

    // Activate buzzer with distinct beeping pattern
    for (int i = 0; i < buzzerDuration; i++) {
      digitalWrite(buzzerPin, HIGH);
      delay(buzzerDelay);
      digitalWrite(buzzerPin, LOW);
      delay(buzzerDelay);
    }
  } else {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SAFE RIDE");
    lcd.setCursor(4, 1);
    lcd.print("NO RAIN");
    delay(1000);  
    Serial.println("No rain detected.");
    digitalWrite(buzzerPin, LOW);
  }
}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);  // Set device as a Wi-Fi Station
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("HELLO :)");
  lcd.setCursor(4, 1);
  lcd.print("WELCOME");
  delay(2000);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("---------------");
    lcd.setCursor(1, 1);
    lcd.print("...ERROR...");
    delay(5000);
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  unsigned long currentTime = millis();

  // Check if data was received recently, otherwise display "Waiting for connection"
  if (currentTime - lastReceivedTime > timeoutDuration) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Waiting for");
    lcd.setCursor(0, 1);
    lcd.print("connection...");
    digitalWrite(buzzerPin, LOW);
    delay(1000);
    lcd.clear();
  } else {
    if (VibrationVal) {
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("DANGER");
      Serial.println("Landslide");
      lcd.setCursor(3, 1);
      lcd.print("LANDSLIDE");
      for (int i = 0; i < 10; i++) {
        digitalWrite(buzzerPin, HIGH);
        delay(300);
        digitalWrite(buzzerPin, LOW);
        delay(200);
        digitalWrite(buzzerPin, HIGH);
        delay(100);
        digitalWrite(buzzerPin, LOW);
        delay(100);
      }
      lcd.clear();
    }

    if (UltrasonicVal) {
      lcd.clear();
      Serial.println("Go Slow");
      lcd.setCursor(4, 0);
      lcd.print("GO SLOW");
      lcd.setCursor(1, 1);
      lcd.print("VEHICLE AHEAD");
      for (int i = 0; i < 10; i++) {
        digitalWrite(buzzerPin, HIGH);
        delay(100);
        digitalWrite(buzzerPin, LOW);
        delay(100);
        digitalWrite(buzzerPin, HIGH);
        delay(300);
        digitalWrite(buzzerPin, LOW);
        delay(200);
      }
      lcd.clear();
    } else {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("ROAD IS CLEAR");
      lcd.setCursor(3, 1);
      lcd.print("SAFE RIDE");
      digitalWrite(buzzerPin, LOW);
      delay(1000);
    }

    displayRainAmountAndSoundBuzzer(SensorVal);
  }
}