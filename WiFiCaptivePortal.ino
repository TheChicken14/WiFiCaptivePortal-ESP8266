#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266WiFi.h>

// #########  CONFIG  #########
#define AP_SSID "Free WiFi 😼"
#define AP_PASS ""

const char *ssid = AP_SSID;
const char *pass = AP_PASS;

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 5, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

void setup()
{
    delay(1000);
    Serial.begin(115200);
    Serial.println();

    // Setup WiFi stuff...
    Serial.println("Configuring WiFi AP...");

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid, pass);

    Serial.print("WiFi AP SSID: ");
    Serial.println(ssid);

    // Setup DNS Server...
    Serial.println("Configuring DNS Server...");

    dnsServer.start(DNS_PORT, "*", apIP);

    Serial.print("My IP is: ");
    Serial.println(apIP);

    // Setup webserver
    webServer.on("/", handleRoot);
    webServer.onNotFound(handleRoot);

    // Start webServer
    webServer.begin();
}

void loop()
{
    dnsServer.processNextRequest();
    webServer.handleClient();
}

void handleRoot()
{
    webServer.send(200, "text/html", "<h1>It works!</h1>");
}
