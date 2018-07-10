/*
 *  Simple HTTP get webclient test
 */

#include <ESP8266WiFi.h>
#include <EasyTransfer.h>

//create object
EasyTransfer ET; 

struct SEND_DATA_STRUCTURE{
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int16_t before;
  int16_t after;
};

//give a name to the group of data
SEND_DATA_STRUCTURE mydata;

//Hotspot
const char* ssid     = "Verizon-MiFi6620L-4E6A";
const char* password = "29734ccd";

const char* host = "hourlypricing.comed.com";

const int time_delay = 10000;
 
void setup() {
  Serial.begin(115200);
  delay(100);
 
  // We start by connecting to a WiFi network
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  //Easy Transfer
  ET.begin(details(mydata), &Serial);
  
  pinMode(2, OUTPUT);
}
 
int value = 0;
 
void loop() {
  delay(time_delay);
  ++value;
 
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  //String url = "/testwifi/index.html";
  String url = "/api?type=currenthouraverage&format=text";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + "\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    String price = stringToPrice(line);

    int dprice = (int)(price.toFloat() * 10);
    mydata.after = dprice % 10;
    dprice = (dprice - (dprice % 10))/10;
    mydata.before = dprice; 
    
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");

  ET.sendData();
  delay(60000);
}

String stringToPrice(String s) {
  int pos = 0;
  String toReturn;
  while (s.substring(pos, pos + 1) != ":") {
    pos++;
  }
  pos++;
  toReturn = s.substring(pos, pos + 3);
  return toReturn;
}
