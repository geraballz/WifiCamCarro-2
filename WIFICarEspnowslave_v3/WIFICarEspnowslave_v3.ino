
#include <ESP8266WiFi.h>
#include <espnow.h>

typedef struct InfoData {
  char command[10];
};

InfoData infoData;

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&infoData, incomingData, sizeof(infoData));
  Serial.print(String(infoData.command));
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(1000);
  Serial.println(WiFi.macAddress());
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
  Serial.println("Setup completed");
}

void loop() {
}

