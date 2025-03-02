#ifdef DEBUG_MODE
  const unsigned long timeScale = 1000;  
#else
  const unsigned long timeScale = 1;     
#endif

#define DATA_PIN 15     
#define SYNC_PIN 2      
#define PB1_PIN 16     
#define PB2_PIN 17      

unsigned long aTime = 700;      
unsigned long bTime = 500;     
int cPulses = 9;                
unsigned long dTime = 2500;     
unsigned long syncOnTime = 50;  

bool outputEnable = false;     
bool outputSelect = false;     

void setup() {
  Serial.begin(115200);
 
  pinMode(DATA_PIN, OUTPUT);
  pinMode(SYNC_PIN, OUTPUT);
  
  pinMode(PB1_PIN, INPUT_PULLUP);
  pinMode(PB2_PIN, INPUT_PULLUP);


  digitalWrite(DATA_PIN, LOW);
  digitalWrite(SYNC_PIN, LOW);
  
  Serial.println("Waveform Generator Starting...");
}

void loop() {
  
  if (digitalRead(PB1_PIN) == LOW) {
    outputEnable = !outputEnable;
    Serial.print("Output Enable toggled: ");
    Serial.println(outputEnable ? "ON" : "OFF");
    delay(300);  
  }
  if (digitalRead(PB2_PIN) == LOW) {
    outputSelect = !outputSelect;
    Serial.print("Waveform Mode toggled: ");
    Serial.println(outputSelect ? "Alternative (Reverse)" : "Normal");
    delay(300);  
  }


  if (outputEnable) {
    if (!outputSelect) {
      generateNormalWaveform();
    } else {
      generateAlternativeWaveform();
    }
  } else {

    digitalWrite(DATA_PIN, LOW);
    digitalWrite(SYNC_PIN, LOW);
    delay(100);
  }
}

void generateNormalWaveform() {
  for (int i = 1; i <= cPulses; i++) {
    unsigned long pulseOn = aTime + (i - 1) * 50;
    digitalWrite(DATA_PIN, HIGH);
    delayMicroseconds(pulseOn * timeScale);
    digitalWrite(DATA_PIN, LOW);
    delayMicroseconds(bTime * timeScale);
  }
  delayMicroseconds(dTime * timeScale);
  
  digitalWrite(SYNC_PIN, HIGH);
  delayMicroseconds(syncOnTime * timeScale);
  digitalWrite(SYNC_PIN, LOW);
}


void generateAlternativeWaveform() {
  for (int i = cPulses; i >= 1; i--) {
    unsigned long pulseOn = aTime + (i - 1) * 50;
    digitalWrite(DATA_PIN, HIGH);
    delayMicroseconds(pulseOn * timeScale);
    digitalWrite(DATA_PIN, LOW);
    delayMicroseconds(bTime * timeScale);
  }
  delayMicroseconds(dTime * timeScale);
  
  digitalWrite(SYNC_PIN, HIGH);
  delayMicroseconds(syncOnTime * timeScale);
  digitalWrite(SYNC_PIN, LOW);
}
