#define ldr A5
#define lvd 2
#define lam 3
#define lve 4
#define bz 5
int alert;
int ldrvalue;
int alertAnterior;
bool buzzer;
unsigned long tempo;


void setup()
{
 pinMode(ldr, INPUT);
 pinMode(bz, OUTPUT);
 pinMode(lvd, OUTPUT);
 pinMode(lam, OUTPUT);
 pinMode(lve, OUTPUT); 
 Serial.begin(9600); 
}

void loop()
{
  verificar();
  
  digitalWrite(lvd, (alert == 1));
  digitalWrite(lam, (alert == 2));
  digitalWrite(lve, (alert == 3));
  
  if (alert == 3 && alertAnterior != 3) {
    tempo = millis();
    digitalWrite(bz, HIGH);
    buzzer = 1;
  }
  
  if (alert != 3 && buzzer) {
  digitalWrite(bz, LOW);
  buzzer = false;
  }

  if (buzzer) {
    if (millis() - tempo >= 3000) {
      digitalWrite(bz, LOW);
      buzzer = 0;
    }
  }

  alertAnterior = alert;
} 

void verificar(){
  ldrvalue = analogRead(ldr);
  
  if(ldrvalue <= 200){
    alert = 1;
  }
  if(ldrvalue > 200 && ldrvalue <= 500){
    alert = 2;
  }
  if(ldrvalue > 500){
    alert = 3;
  }
}