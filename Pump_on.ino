/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/communication-between-two-esp32
 */

// ESP32 : TCP SERVER + AN Motor
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "CodeBlue";          // your working WiFi
const char* password = "jaijaiMahadev"; // your working password

#define MOTOR_PIN 23   // Use your motor pin

WebServer server(80);  // HTTP server running on port 80


// ----------- ENDPOINT: /disease -----------
void handleDisease() {
  digitalWrite(MOTOR_PIN, HIGH);   // Motor ON
  server.send(200, "text/plain", "Motor ON - Disease detected");
  Serial.println("Motor turned ON (Disease)");
}

// ----------- ENDPOINT: /healthy ----------
void handleHealthy() {
  digitalWrite(MOTOR_PIN, LOW);    // Motor OFF
  server.send(200, "text/plain", "Motor OFF - Healthy");
  Serial.println("Motor turned OFF (Healthy)");
}

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(MOTOR_PIN, LOW);    // off initially

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  // WiFi connection loop
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Still connecting...");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // Register endpoints
  Serial.println();
 
  server.on("/disease", handleDisease);
  server.on("/healthy", handleHealthy);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();   // listens for Python requests
}
