//#include <Adafruit_Sensor.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);  // Pass the oneWire reference to Dallas Temperature.


unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;

#if SIMULATED_DATA

void initSensor()
{
    // use SIMULATED_DATA, no sensor need to be inited
}

float readTemperature()
{
    return random(20, 30);
}

float readHumidity()
{
    return random(30, 40);
}

float readPHValue() {

  return random(1, 15);
}


float readGasValue() {

   return random(1, 15);
}

float readTemperatureLiq() {

  return random(20, 40);
}


float readTurbidity() {

  return random(20, 40);
}


#else

static DHT dht(DHT_PIN, DHT_TYPE);
void initSensor()
{
    dht.begin();

     sensors.begin();
}

float readPHValue () {

 for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(A0);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;  //convert the millivolt into pH value
  phValue=phValue-4;

 return phValue;

}


float readTurbidity() {

  int val = analogRead(A0); 

 return map(val, 0, 2800, 5, 1);;
}


float readGasValue() {
  return  analogRead(A0); 
}

float readTemperatureLiq()
{

   sensors.requestTemperatures();  
    return sensors.getTempCByIndex(0);
}


float readTemperature()
{
    return dht.readTemperature();
}

float readHumidity()
{
    return dht.readHumidity();
}

#endif

bool readMessage(int messageId, char *payload)
{
    float temperature = readTemperature();
    float humidity = readHumidity();
    float ph = readPHValue();


    float gas = readGasValue();

    float temperatureLiq = readTemperatureLiq();

    float turbidity = readTurbidity();
    
    
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["deviceId"] = DEVICE_ID;
    root["messageId"] = messageId;
    bool temperatureAlert = false;

    // NAN is not the valid json, change it to NULL
    if (std::isnan(temperature))
    {
        root["temperature"] = NULL;
    }
    else
    {
        root["temperature"] = temperature;
        if (temperature > TEMPERATURE_ALERT)
        {
            temperatureAlert = true;
        }
    }


    if (std::isnan(ph))
    {
        root["ph"] = NULL;
    }
    else
    {
        root["ph"] = ph;
        
    }


    if (std::isnan(gas))
    {
        root["gas"] = NULL;
    }
    else
    {
        root["gas"] = gas;
        
    }


        if (std::isnan(turbidity))
    {
        root["turbidity"] = NULL;
    }
    else
    {
        root["turbidity"] = turbidity;
        
    }


        if (std::isnan(temperatureLiq))
    {
        root["temperatureLiq"] = NULL;
    }
    else
    {
        root["temperatureLiq"] = temperatureLiq;
        if (temperatureLiq > TEMPERATURE_ALERT)
        {
            temperatureAlert = true;
        }
    }
    

    if (std::isnan(humidity))
    {
        root["humidity"] = NULL;
    }
    else
    {
        root["humidity"] = humidity;
    }
    root.printTo(payload, MESSAGE_MAX_LEN);
    return temperatureAlert;
}

void parseTwinMessage(char *message)
{
    StaticJsonBuffer<MESSAGE_MAX_LEN> jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(message);
    if (!root.success())
    {
        Serial.printf("Parse %s failed.\r\n", message);
        return;
    }

    if (root["desired"]["interval"].success())
    {
        interval = root["desired"]["interval"];
    }
    else if (root.containsKey("interval"))
    {
        interval = root["interval"];
    }
}
