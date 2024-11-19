#include <espnow.h>
#include <ESP8266WiFi.h>

#define SOUND_VELOCITY 0.034 //define sound velocity in cm

const int RainSensor = A0;       // Analog pin for rain sensor
const int Trig1 = 4;             // GPIO5 corresponds to D2
const int Echo1 = 5;             // GPIO4 corresponds to D1
const int Trig2 = 12;             // GPIO12 corresponds to D6
const int Echo2 = 14;             // GPIO14 corresponds to D5
const int VibrationSensor = 16;  // GPIO16 corresponds to D0

long duration;
float distanceCm;

float distanceCm1;
float distanceCm2;

uint previous_condition = 0;
uint present_condition;

uint8_t broadcastAddress[] = { 0x50, 0x02, 0x91, 0x77, 0xE2, 0xC3 }; // REPLACE WITH YOUR RECEIVER MAC Address

// Must match the receiver structure
typedef struct struct_message {
  bool VibVal;
  bool ultraVal;
  int rainVal;
} struct_message;

struct_message myData;  // Create a struct_message called myData

// callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(sendStatus == 0 ? "Delivery Success" : "Delivery Fail");
}

float DistanceMeasurement(const int trigPin, const int echoPin) {
  digitalWrite(trigPin, LOW);  // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);           // Reads the echoPin, returns the sound wave travel time in microseconds
  distanceCm = duration * SOUND_VELOCITY / 2;  // Calculate the distance

  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);  // Prints the distance on the Serial Monitor

  return distanceCm;
}

void setup() {
  Serial.begin(9600);   // Init Serial Monitor
  WiFi.mode(WIFI_STA);  // Set device as a Wi-Fi Station

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Transmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  if (esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0) != 0) {
    Serial.println("Failed to add peer");
    return;
  }

  //Defining the Pins for RainSensor and VibrationSensor
  pinMode(RainSensor, INPUT);              //Setting the RainSensor Pin as Analog input Pin
  pinMode(VibrationSensor, INPUT);  // Setting the vibrationSensor Pin as Digital input pull up Pin

  //Defining the Pins for UltarsonicSensors
  pinMode(Trig1, OUTPUT);
  pinMode(Echo1, INPUT);
  pinMode(Trig2, OUTPUT);
  pinMode(Echo2, INPUT);
}

void loop() {
  //Landslide logic------------------------------------------------------------
  present_condition = digitalRead(VibrationSensor);
  myData.VibVal = (previous_condition != present_condition) ? true : false;
  previous_condition = present_condition;
  Serial.print("Vibration Value: ");
  Serial.println(myData.VibVal);
  //---------------------------------------------------------------------------

  //Collision logic--------------------------------------------------------------
  distanceCm1 = DistanceMeasurement(Trig1, Echo1);
  distanceCm2 = DistanceMeasurement(Trig2, Echo2);

  if (distanceCm1 <= 15 && distanceCm2 <= 15) {
    myData.ultraVal = true;
  } else {
    myData.ultraVal = false;
  }
  //-----------------------------------------------------------------------------

  myData.rainVal = analogRead(RainSensor);
  Serial.print("Rain Value: ");
  Serial.println(myData.rainVal);

  uint8_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));  // Send message via ESP-NOW

  if (result == 0) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }

  delay(1000);
}
