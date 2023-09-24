# include <DHT11.h>
#include <DigiPotX9Cxxx.h>
# define dht_Pin 8
# define trigger_Pin 5
# define echo_Pin 7
# define inc 2 
# define ud 3
# define cs 4
# define check_Resistance A0
int set_Resistance;
int pot_Value;
int pot_Pin=A2;
int dig_Volt;
void setup() {
  Serial.begin(115200);
  pinMode(A2,INPUT);
  set_Resistance=100;  
}

void loop() {
  set_Resistance=analogRead(A2)*(100.0/1023.0);
  delay(1000);
  dht_11(dht_Pin,2000);
  ultrasonic_HC(echo_Pin,trigger_Pin,5,10);
  dig_Pot(inc,ud,cs,set_Resistance);
  Serial.print("Current Voltage Value is : ");
  Serial.println(dig_Volt);
  Serial.println(analogRead(A2));
}
void ultrasonic_HC(int echo_P,int trigger_P,int time_L,int time_H){
  pinMode(echo_P,INPUT);
  pinMode(trigger_P,OUTPUT);
  long duration;
  float distance;
  digitalWrite(trigger_P, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger_P, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_P, LOW);
  duration = pulseIn(echo_P, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(50);
  return distance;

}
void dht_11(int pin_no,int time_delay){
  DHT11 dht11(pin_no);
  int temp_humd[2];
    float humidity = dht11.readHumidity();
    float temperature = dht11.readTemperature();
    if (temperature != -1 && humidity != -1)
    {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" C");

        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    }
    else
    {
        Serial.println("Error reading data");
    }
    delay(time_delay);
    temp_humd[0]=temperature;
    temp_humd[1]=humidity;
    return temp_humd;    
}
void dig_Pot(int INC, int UD, int CS, int value){
  DigiPot pot(INC,UD,CS);
  pot.set(value);
}

