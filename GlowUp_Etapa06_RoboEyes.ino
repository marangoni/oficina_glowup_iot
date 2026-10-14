// GlowUp IoT: Ciencia Delas - Expressoes da Natureza
// Etapa 06 — RoboEyes + sensor capacitivo + buzzer ativo
// IFSP - Campus Hortolandia
// ESP32-C3 Super Mini | OLED SSD1306 128x64 I2C 0x3C
// Ajuste calibracao e confirme a corrente do buzzer antes de ligar.

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <FluxGarage_RoboEyes.h>

const int PINO_SDA = 8;
const int PINO_SCL = 9;
const int PINO_SENSOR = 1;
const int PINO_BUZZER = 4;
const int VALOR_SECO = 3800;
const int VALOR_UMIDO = 1326;

// Faixas didaticas relativas: 0-20, 21-45, 46-75, 76-90, 91-100.
const unsigned long INTERVALO_LEITURA = 2000;
const unsigned long INTERVALO_BIPE = 30000;
const unsigned long DURACAO_BIPE = 90;

Adafruit_SSD1306 display(128, 64, &Wire, -1);
RoboEyes<Adafruit_SSD1306> roboEyes(display);

int leituraADC = 0;
int umidade = 0;
int estado = -1;
unsigned long ultimaLeitura = 0;
unsigned long ultimoAlerta = 0;
unsigned long inicioBipe = 0;
int bipesRestantes = 0;
bool buzzerLigado = false;
bool alertaJaEnviado = false;

void iniciarBipes(int quantidade) {
  bipesRestantes = quantidade;
  buzzerLigado = false;
  digitalWrite(PINO_BUZZER, LOW);
}

void atualizarSom(unsigned long agora) {
  // Um bipe por vez, sem delay() para nao congelar os olhos.
  if (buzzerLigado && agora - inicioBipe >= DURACAO_BIPE) {
    digitalWrite(PINO_BUZZER, LOW);
    buzzerLigado = false;
    inicioBipe = agora;
    bipesRestantes--;
  }
  if (!buzzerLigado && bipesRestantes > 0 && agora - inicioBipe >= 160) {
    digitalWrite(PINO_BUZZER, HIGH);
    buzzerLigado = true;
    inicioBipe = agora;
  }
}

void aplicarExpressao(int novoEstado) {
  // Limpa efeitos anteriores antes de aplicar outra expressao.
  roboEyes.setHFlicker(OFF);
  roboEyes.setVFlicker(OFF);
  roboEyes.setSweat(OFF);
  roboEyes.setCuriosity(OFF);
  roboEyes.setPosition(DEFAULT);

  switch (novoEstado) {
    case 0: // Critico seco
      roboEyes.setMood(TIRED);
      roboEyes.setPosition(S);
      break;
    case 1: // Com sede
      roboEyes.setMood(ANGRY);
      break;
    case 2: // Perfeito
      roboEyes.setMood(HAPPY);
      break;
    case 3: // Excesso de agua
      roboEyes.setMood(TIRED);
      roboEyes.setSweat(ON);
      break;
    case 4: // Critico de excesso de agua
      roboEyes.setMood(ANGRY);
      roboEyes.setSweat(ON);
      break;
  }
}

int identificarEstado(int porcentagem) {
  if (porcentagem <= 20) return 0;
  if (porcentagem <= 45) return 1;
  if (porcentagem <= 75) return 2;
  if (porcentagem <= 90) return 3;
  return 4;
}

void atualizarMedicao(unsigned long agora) {
  leituraADC = analogRead(PINO_SENSOR);
  if (VALOR_SECO == VALOR_UMIDO) return;
  umidade = map(leituraADC, VALOR_SECO, VALOR_UMIDO, 0, 100);
  umidade = constrain(umidade, 0, 100);
  int novoEstado = identificarEstado(umidade);

  Serial.print("ADC: "); Serial.print(leituraADC);
  Serial.print(" | Umidade relativa: "); Serial.print(umidade);
  Serial.print("% | Estado: "); Serial.println(novoEstado);

  if (novoEstado != estado) {
    estado = novoEstado;
    aplicarExpressao(estado);
    if (estado == 0 || estado == 1 || estado == 4) {
      iniciarBipes(estado == 4 ? 3 : 2);
      ultimoAlerta = agora;
      alertaJaEnviado = true;
    } else {
      iniciarBipes(0);
      alertaJaEnviado = false;
    }
  } else if ((estado == 0 || estado == 1 || estado == 4) &&
             (!alertaJaEnviado || agora - ultimoAlerta >= INTERVALO_BIPE)) {
    iniciarBipes(estado == 4 ? 3 : 2);
    ultimoAlerta = agora;
    alertaJaEnviado = true;
  }
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  pinMode(PINO_BUZZER, OUTPUT);
  digitalWrite(PINO_BUZZER, LOW);
  Wire.begin(PINO_SDA, PINO_SCL);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED nao encontrado!");
    while (true) delay(1000);
  }
  roboEyes.begin(128, 64, 60);
  // Olhos compactos: ocupam principalmente a regiao azul no bicolor.
  // As animacoes (piscar/suor) podem usar outras linhas do visor.
  roboEyes.setWidth(38, 38);
  roboEyes.setHeight(30, 30);
  roboEyes.setBorderradius(7, 7);
  roboEyes.setSpacebetween(10);
  roboEyes.setAutoblinker(ON, 3, 2);
  roboEyes.setIdleMode(ON, 3, 2);
  roboEyes.setMood(DEFAULT);

  // Primeira medida imediata para escolher a expressao.
  atualizarMedicao(millis());
  ultimaLeitura = millis();
}

void loop() {
  unsigned long agora = millis();
  roboEyes.update(); // Atualizar continuamente: sem delay() no loop.
  atualizarSom(agora);
  if (agora - ultimaLeitura >= INTERVALO_LEITURA) {
    ultimaLeitura = agora;
    atualizarMedicao(agora);
  }
}
