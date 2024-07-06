//Transmitter code for ESP-NOW

#include <esp_now.h>
#include <WiFi.h>
#define vibrPin 4
#define rainPin 34

// REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
uint8_t broadcastAddress1[] = { 0xE4, 0x65, 0xB8, 0x78, 0xE9, 0xEC };  //Enter your Receiver board MAC Address

// ULTRASONIC SENSOR PINS
const int trigPin1 = 5;
const int echoPin1 = 18;
const int trigPin2 = 21;
const int echoPin2 = 19;

int previous_condition = 0;
int present_condition;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034

long duration1;
long duration2;
float distanceCm1;
float distanceCm2;

typedef struct test_struct {
  int rainVal;
  bool VibVal;
  bool ultraVal;
} test_struct;

test_struct test;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  Serial.begin(115200);

  //--------------------------------------------------------------------------------------------
  pinMode(vibrPin, INPUT);    // Sets the vibrPin as Input
  pinMode(rainPin, INPUT);    // Sets the rainPin as Input
  pinMode(trigPin1, OUTPUT);  // Sets the trigPin1 as an Output
  pinMode(echoPin1, INPUT);   // Sets the echoPin1 as an Input
  pinMode(trigPin2, OUTPUT);  // Sets the trigPin2 as an Output
  pinMode(echoPin2, INPUT);   // Sets the echoPin2 as an Input
  //--------------------------------------------------------------------------------------------

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  // register peer
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // register first peer
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  //Ultrasonic Sensor1 distance ------------------------------------------------
  digitalWrite(trigPin1, LOW);  // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);        // Reads the echoPin, returns the sound wave travel time in microseconds
  distanceCm1 = duration1 * SOUND_SPEED / 2;  // Calculate the distance
  Serial.print("Distance1 (cm): ");           // Prints the distance in the Serial Monitor
  Serial.println(distanceCm1);

  // Ultrasonic Sensor2 distance -----------------------------------------------
  digitalWrite(trigPin2, LOW);  // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);        // Reads the echoPin, returns the sound wave travel time in microseconds
  distanceCm2 = duration2 * SOUND_SPEED / 2;  // Calculate the distance
  Serial.print("Distance2 (cm): ");           // Prints the distance in the Serial Monitor
  Serial.println(distanceCm2);

  //Send the data----------------------------------------------------------------
  esp_err_t result = esp_now_send(0, (uint8_t *)&test, sizeof(test_struct));

  //Collision logic--------------------------------------------------------------
  if (distanceCm1 < 10 && distanceCm2 < 10) {
    test.ultraVal = true;
  } else {
    test.ultraVal = false;
  }

  //Landslide logic------------------------------------------------------------
  present_condition = digitalRead(vibrPin);
  Serial.print("Vibration VAlue: ");
  Serial.println(digitalRead(vibrPin));
  if (previous_condition != present_condition) {
    test.VibVal = true;
    previous_condition = present_condition;
  } else {
    test.VibVal = false;
  }

  test.rainVal = analogRead(rainPin);
  Serial.print("Rain Value: ");
  Serial.println(analogRead(rainPin));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }

  delay(50);
}