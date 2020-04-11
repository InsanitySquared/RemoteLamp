#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "Donut-Sloth Network"
#define STAPSK  "CatTheC00kie28"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.1.7";
const uint16_t port = 30002;

char buffr[512];

int nPart;

WiFiClient client;

void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());



  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  // This will send a string to the server
  if (client.connected()) {
    client.print("lp");
  }

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  // not testing 'client.connected()' since we do not need to send data here
  int i=0;
  while (client.available()) {
    buffr[i] = static_cast<char>(client.read());
    Serial.print(buffr[i]);
    i=i+1;
  }

  Serial.println();
  
  if((buffr[0]!='o')&&(buffr[1]!='k')){
    Serial.println("wrong server ack");
    return;
  }

  while (client.available() == 0) {}
  Serial.println("more data");
  i=0;
  while (client.available()) {
    buffr[i] = static_cast<char>(client.read());
    Serial.print(buffr[i]);
    i=i+1;
  }
  delay(10);
  if((buffr[0]=='n')&&(buffr[1]=='s')){
    client.print("np");
    delay(10);
    while (client.available() == 0) {}
    Serial.println("more data");
    i=0;
    while (client.available()) {
      buffr[i] = static_cast<char>(client.read());
      Serial.print(buffr[i]);
      i=i+1;
    }
    nPart=atoi(buffr);
  }
  Serial.println(nPart*3);

  //int g=1;
  //while(g<=nPart){
    //pinMode((g+11), OUTPUT);
    //digitalWrite((g+11), LOW);
  //}

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  int y=1;
  if(y<=nPart){
    while (client.available() == 0) {}
    Serial.println("more data");
    int i=0;
    while (client.available()) {
      buffr[i] = static_cast<char>(client.read());
      Serial.print(buffr[i]);
      i=i+1;
    }
    if((buffr[0]=='l')&&(buffr[1]=='f')){
      Serial.println("Got fire command boss man sir!");
      digitalWrite(LED_BUILTIN, LOW);
      //digitalWrite((y+11)),HIGH);
      if (!client.connected()) {
        Serial.println("server dead");
      }
      client.print("dn");
      return;
    }
    y=y+1;
  }
  Serial.println();
  Serial.println("DONEEE!!");
  client.stop();
}
