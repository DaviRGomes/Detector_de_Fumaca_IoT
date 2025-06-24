#define BLYNK_TEMPLATE_ID "TMPL2ucB-5jH4"
#define BLYNK_TEMPLATE_NAME "Sensor de fumaça"
#define BLYNK_AUTH_TOKEN "rkufgsBJU6SsfBi1etLKD8taw7LA3Hqo"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Configuração dos pinos (NodeMCU)
#define MQ2_PIN A0
#define LED_PIN D4

char ssid[] = "DRG 123";
char pass[] = "17D451243a02";

// Variáveis de controle
const int WARNING_LEVEL = 300;  // Aviso inicial
const int DANGER_LEVEL = 1000;  // Nível para acionar LED e alarme
const int NUM_READINGS = 5;
int readings[NUM_READINGS];
int readIndex = 0;
int total = 0;
int average = 0;
bool dangerState = false;

BlynkTimer timer;

void initReadings() {
  for (int i = 0; i < NUM_READINGS; i++) {
    readings[i] = analogRead(MQ2_PIN);
    total += readings[i];
    delay(10);
  }
}

void checkGas() {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(MQ2_PIN);
  total = total + readings[readIndex];
  readIndex = (readIndex + 1) % NUM_READINGS;
  average = total / NUM_READINGS;
  
  // Envia o valor suavizado para o Blynk (V0)
  Blynk.virtualWrite(V0, average);
  
  // Lógica de alertas
  if (average > DANGER_LEVEL && !dangerState) {
    dangerState = true;
    digitalWrite(LED_PIN, HIGH);
    Blynk.virtualWrite(V1, 1); // Alarme perigo (V1)
    Blynk.virtualWrite(V2, 1); // LED virtual (V2)
    Blynk.logEvent("danger_alert", String("PERIGO! Nível crítico: ") + average + "ppm");
    Serial.print("[PERIGO] Nível crítico: ");
    Serial.print(average);
    Serial.println("ppm");
  } 
  else if (average <= DANGER_LEVEL && dangerState) {
    dangerState = false;
    digitalWrite(LED_PIN, LOW);
    Blynk.virtualWrite(V1, 0); // Desliga alarme
    Blynk.virtualWrite(V2, 0); // Desliga LED virtual
    Serial.println("[NORMAL] Nível seguro");
  }
  
  // Aviso prévio (sem ativar LED físico)
  if (average > WARNING_LEVEL && average <= DANGER_LEVEL) {
    Blynk.virtualWrite(V3, 1); // Aviso (V3)
    Serial.print("[AVISO] Nível elevado: ");
    Serial.print(average);
    Serial.println("ppm");
  } else {
    Blynk.virtualWrite(V3, 0);
  }
  
  Serial.print("Nível de gás: ");
  Serial.print(average);
  Serial.println("ppm");
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  pinMode(MQ2_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  initReadings();
  
  Serial.println("Aquecendo sensor MQ-2 (aguarde 20s)...");
  delay(20000);
  
  Serial.println("Conectando ao WiFi e Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  if (WiFi.status() != WL_CONNECTED || !Blynk.connected()) {
    Serial.println("Falha na conexão. Reiniciando...");
    delay(3000);
    ESP.restart();
  }
  
  timer.setInterval(1000, checkGas);
  Serial.println("Sistema MQ-2 pronto com alarmes");
}

void loop() {
  Blynk.run();
  timer.run();
}