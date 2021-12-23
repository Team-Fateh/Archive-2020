
int frequency = 100; 
double delayTime = 1000 / (frequency * 2);
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(11, LOW);
  digitalWrite(13, HIGH);
  delay(delayTime);

  digitalWrite(13, LOW);
  digitalWrite(11, HIGH);
  delay(delayTime);

  int output_r = analogRead(A5);
  float output = output_r * (5.0 / 1023.0);
  Serial.println(output);
}
