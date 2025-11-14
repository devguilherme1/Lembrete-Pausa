#include <WiFi.h>
#include <HTTPClient.h>

// -------------------- WiFi (Wokwi) --------------------
const char* ssid     = "Wokwi-GUEST";
const char* password = "";

// -------------------- Pinos --------------------
const int BUTTON_PIN = 4;  // Botão (INPUT_PULLUP)
const int BUZZER_PIN = 5;  // Buzzer
const int LED_PIN    = 2;  // LED interno

// -------------------- Tempo --------------------
unsigned long startTime = 0;
// 20 s para teste. 
const unsigned long intervalo = 20000;

// -------------------- Estados --------------------
bool alertaMostrado = false;  
bool botaoLiberado  = false; 

// Flags de HTTP (enviadas depois, sem travar o botão)
bool precisaEnviarPausaPendente  = false;
bool precisaEnviarPausaRealizada = false;

// =====================================================
//                      Funções
// =====================================================

void conectarWiFi() {
  Serial.print("Conectando ao WiFi ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado.");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void beepCurto() {
  tone(BUZZER_PIN, 2000);   // 2 kHz
  delay(150);
  noTone(BUZZER_PIN);
}

void enviarHTTP(const String& evento) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado, não enviou HTTP.");
    return;
  }

  HTTPClient http;
  http.begin("https://httpbin.org/status/201"); // endpoint de teste
  http.addHeader("Content-Type", "application/json");

  String body = "{\"evento\":\"" + evento + "\"}";
  int code = http.POST(body);

  Serial.print("HTTP ");
  Serial.print(evento);
  Serial.print(" - código: ");
  Serial.println(code);

  http.end();
}

// =====================================================
//                        SETUP
// =====================================================

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  noTone(BUZZER_PIN);

  conectarWiFi();

  startTime = millis();
  Serial.println("Iniciando contagem de trabalho...");
}

// =====================================================
//                        LOOP
// =====================================================

void loop() {
  unsigned long agora = millis();
  bool tempoEsgotado = (agora - startTime >= intervalo);

  // --------- Quando chega a hora da pausa ---------
  if (tempoEsgotado && !alertaMostrado) {
    alertaMostrado = true;
    botaoLiberado  = true;       // botão já vale
    precisaEnviarPausaPendente = true; // marca que deve registrar esta pausa

    tone(BUZZER_PIN, 2000);      // beep contínuo
    digitalWrite(LED_PIN, HIGH);

    Serial.println("Hora da pausa!");
  }

  // --------- Leitura do botão ---------
  int leitura = digitalRead(BUTTON_PIN);

  // Botão apertado (LOW) e liberado
  if (leitura == LOW && botaoLiberado) {
    botaoLiberado  = false;
    alertaMostrado = false;      // permite próximo alerta
    startTime      = millis();   // reinicia contagem

    // Para o alerta imediatamente
    noTone(BUZZER_PIN);
    digitalWrite(LED_PIN, LOW);

    Serial.println("Botão apertado: reiniciando contagem.");
    beepCurto();

    // Marca para registrar que a pausa foi realizada
    precisaEnviarPausaRealizada = true;
  }

  // Soltou o botão e não estamos em alerta -> libera para próximo clique
  if (leitura == HIGH && !alertaMostrado) {
    botaoLiberado = true;
  }

  // ---------  HTTP depois, sem atrapalhar o botão ---------
  
  if (precisaEnviarPausaPendente && !alertaMostrado) {
    enviarHTTP("pausa_pendente");
    precisaEnviarPausaPendente = false;
  }

  if (precisaEnviarPausaRealizada) {
    enviarHTTP("pausa_realizada");
    precisaEnviarPausaRealizada = false;
  }

  delay(20); // loop mais suave
}