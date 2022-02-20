 #include<ESP8266WiFi.h>
    #include <ESP8266HTTPClient.h>
    #define LED 2
    
    ADC_MODE(ADC_VCC);
    const char * ssid = "Pixel_4209"; // example
    const char * password = "02dbc5836a54"; // random example
    int led = 13;
    int buzzer = D1;
    void setup() {
      pinMode(LED, OUTPUT);
      pinMode(led, OUTPUT);
      digitalWrite(led, LOW);
      Serial.begin(115200);
      Serial.println();
      Serial.print("WIFI Connecting to");
      Serial.println(ssid);
      func1();
      func2();      
    }
       
    void func1() {
      WiFi.begin(ssid, password);
      Serial.println();
      Serial.print("Connecting");
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      digitalWrite(led, HIGH);
      Serial.println();
      Serial.println("Wifi Connected Success!");
      Serial.print("Node MCU IP ADDRESS:");
      Serial.println(WiFi.localIP());
    }

    void func2() {
      while (!Serial) {}
      pinMode(buzzer, OUTPUT);
      digitalWrite(buzzer, HIGH);
      Serial.println("Started.");
      Serial.println("---------------------------");

      Serial.println("going to fun");
      func3();
      Serial.println("Going to sleep.");
      ESP.deepSleep(0);
      Serial.println("Should not be showing!");
    }

    void func3() {
      float vcc = ESP.getVcc();
      vcc = (vcc) / (1000.000);
      String myStr;
      myStr = String(vcc);
      get_http(String(myStr));
      digitalWrite(buzzer, LOW);
      delay(10000);
    }

    int get_http(String state) {
      HTTPClient http;
      int ret = 0;
      Serial.print("[HTTP] begin...\n");
      // configure ifttt server and url  should be HTTP only..not https
      // http.begin("http://maker.ifttt.com/trigger/door/with/key/ba7cyUqJABqz5v9M6rjGXq/?value1="+state);

      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();
      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        ret = -1;
        Serial.printf("[HTTP] GET failed, error: %s\n", http.errorToString(httpCode).c_str());
        delay(500); // wait for half sec before retry again
      }

      http.end();
      return ret;
    }
