#include <dht11.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

dht11 DHT;
int digitalValue;
const char* ssid = "neeltron";
const char* password = "***********";
const char *host = "HoloNet-API.neeltron.repl.co";
const int httpsPort = 443;
const char fingerprint[] PROGMEM = "25 DE 41 40 12 C6 E3 8C 9A FD 50 CC 35 CB 03 42 7B FC DD 86";
const int xPin = A0;

void setup() {
  pinMode(5, INPUT);
  Serial.begin(9600);
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int chk = DHT.read(2);
  WiFiClientSecure httpsClient;
  Serial.println(host);
  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  httpsClient.setFingerprint(fingerprint);
  httpsClient.setTimeout(15000); // 15 Seconds
  delay(1000);

  Serial.print("HTTPS Connecting");
  int r = 0; //retry counter
  while ((!httpsClient.connect(host, httpsPort)) && (r < 30)) {
    delay(100);
    Serial.print(".");
    r++;
  }
  if (r == 30) {
    Serial.println("Connection failed");
  }
  else {
    Serial.println("Connected to web");
  }
  String line;
  while (httpsClient.available()) {
    line = httpsClient.readStringUntil('\n');
    Serial.println(line);
  }
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  //  Serial.print("Humidity = ");
  if (DHT.temperature > 40) {
    // link
    String getData, Link;

    Link = "/entry?disaster=volcanic";
    Serial.print("requesting URL: ");
    Serial.println(host + Link);
    httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +
                      "Host: " + host + "\r\n" +
                      "Connection: close\r\n\r\n");

    Serial.println("request sent");

    while (httpsClient.connected()) {
      String line = httpsClient.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("received");
        break;
      }
    }
  }
  int x = analogRead(xPin);
  if ( x < 450 || x > 500 )
  {
    String getData, Link;

    Link = "/entry?disaster=earthquake";
    Serial.print("requesting URL: ");
    Serial.println(host + Link);
    httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +
                      "Host: " + host + "\r\n" +
                      "Connection: close\r\n\r\n");

    Serial.println("request sent");

    while (httpsClient.connected()) {
      String line = httpsClient.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("received");
        break;
      }
    }
  }
  digitalValue = digitalRead(5);
  if (digitalValue > 600) {
    String getData, Link;

    Link = "/entry?disaster=wildfires";
    Serial.print("requesting URL: ");
    Serial.println(host + Link);
    httpsClient.print(String("GET ") + Link + " HTTP/1.1\r\n" +
                      "Host: " + host + "\r\n" +
                      "Connection: close\r\n\r\n");

    Serial.println("request sent");

    while (httpsClient.connected()) {
      String line = httpsClient.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("received");
        break;
      }
    }
  }
  Serial.println(x);
  //  Serial.println(DHT.humidity);
  delay(1000);
}