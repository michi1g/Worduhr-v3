#include "Arduino.h"

const char *VER = "2.3.2";  // Software Version

#pragma once

#ifdef UHR_114_Alternative
#define UHR_Type UHR_114_Alternative_t
#endif

#ifdef UHR_114
#define UHR_Type UHR_114_t
#endif

#ifdef UHR_125
#define UHR_Type UHR_125_t
#endif

#ifdef UHR_169
#define UHR_Type UHR_169_t
#endif

#ifdef UHR_242
#define UHR_Type UHR_242_t
#endif


#ifdef Grb
#define LED_STRIPE_TYP   NeoGrbFeature
#endif
#ifdef Brg
#define LED_STRIPE_TYP   NeoBrgFeature
#endif
#ifdef Rgb
#define LED_STRIPE_TYP   NeoRgbFeature
#endif
#ifdef Rbg
#define LED_STRIPE_TYP   NeoRbgFeature
#endif
#ifdef Grbw
#define LED_STRIPE_TYP   NeoGrbwFeature
#endif

enum uhrzeit_t {
    ESIST = 0,
    VOR = 1,
    NACH = 2,
    UHR = 3,

    FUENF = 4,
    ZEHN = 5,
    VIERTEL = 6,
    ZWANZIG = 7,
    HALB = 8,
    EINS = 9,

    H_EIN = 10,
    H_ZWEI = 11,
    H_DREI = 12,
    H_VIER = 13,
    H_FUENF = 14,
    H_SECHS = 15,
    H_SIEBEN = 16,
    H_ACHT = 17,
    H_NEUN = 18,
    H_ZEHN = 19,
    H_ELF = 20,
    H_ZWOELF = 21
};

struct GLOBAL {
    uint8_t sernr;
    char ssid[25];
    char passwd[25];
    unsigned int prog;
    uint8_t param1;
    uint8_t param2;
    uint8_t prog_init;
    uint16_t conf;
    uint8_t rgb[4][4];
    uint8_t rr;
    uint8_t gg;
    uint8_t bb;
    uint8_t ww;
    uint8_t hell;
    int ldr;
    int ldrCal;
    char apikey[33];
    char cityid[8];
    int geschw;
    uint8_t client_nr;
    uint8_t zeige_sek;
    uint8_t zeige_min;
    char zeitserver[30];
    char hostname[30];
    char ltext[30];
    uint8_t hh;
    uint8_t h6;
    uint8_t h8;
    uint8_t h12;
    uint8_t h16;
    uint8_t h18;
    uint8_t h20;
    uint8_t h22;
    uint8_t h24;
};
GLOBAL G = {};

#ifdef UHR_242
const char* server = "api.openweathermap.org";  // Openweather server's address
const char* resource1 = "/data/2.5/forecast?id="; // Openweather API URL part 1
const char* resource2 = "&units=metric&APPID="; // Openweather API URL part 2
const char* resource3 = "&cnt=8"; // Openweather API forecast time
char resource[40];
char response[6000];       //fixed size buffer
WiFiClient client;
unsigned int weather_tag    = 600;    //counter fuer Wetterdaten abrufen
int wtemp_6;
int wtemp_12;
int wtemp_18;
int wtemp_24;
int wwetter_6;
int wwetter_12;
int wwetter_18;
int wwetter_24;
int wstunde;
int wetterswitch;
#endif

struct UHR_114_Alternative_t {
    uint8_t NUM_PIXELS = 114;
    uint8_t NUM_SMATRIX = 114;
    uint8_t ROWS_MATRIX = 11;
    uint8_t NUM_RMATRIX = 0;
};

struct UHR_114_t {
    uint8_t NUM_PIXELS = 114;
    uint8_t NUM_SMATRIX = 114;
    uint8_t ROWS_MATRIX = 11;
    uint8_t NUM_RMATRIX = 0;
};

struct UHR_125_t {
    uint8_t NUM_PIXELS = 125;
    uint8_t NUM_SMATRIX = 125;
    uint8_t ROWS_MATRIX = 12;
    uint8_t NUM_RMATRIX = 0;
};

struct UHR_169_t {
    uint8_t NUM_PIXELS = 169;
    uint8_t NUM_SMATRIX = 121;
    uint8_t ROWS_MATRIX = 11;
    uint8_t NUM_RMATRIX = 48;
};

struct UHR_242_t {
    uint8_t NUM_PIXELS = 242;
    uint8_t NUM_SMATRIX = 242;
    uint8_t ROWS_MATRIX = 22;
    uint8_t NUM_RMATRIX = 0;
};

// fix Eisbaeeer
#ifdef UHR_242 
    uint8_t NUM_PIXELS = 242;
    uint8_t NUM_SMATRIX = 242;
    uint8_t ROWS_MATRIX = 22;
    uint8_t NUM_RMATRIX = 0;                
#endif

UHR_Type Uhrtype;

// LDR 
unsigned long waitUntilLDR = 0;
int autoBrightnessEnabled = 1;
int ldrVal = 50;
int oneseconddelay = 1000;

// Telnet vars
bool ConnectionEstablished; // Flag for successfully handled connection
#define MAX_TELNET_CLIENTS 2
WiFiServer TelnetServer(23);
WiFiClient TelnetClient[MAX_TELNET_CLIENTS];

const char *ssid_ap = "Uhr";
const char *password_ap = "12345678";
//--OTA--
const char *host = "webupdate";
//--OTA--

unsigned char wlan_client = false;
unsigned char wlan_status = 99;
unsigned char wlan_ssid = false;

unsigned int _sekunde = 0;
unsigned int _minute = 0;
unsigned int _stunde = 0;
unsigned int last_sekunde = 100;
unsigned int last_minute = 100;
unsigned int last_stunde = 100;

unsigned int count_millis48 = 0;
unsigned long previous48 = 0;
const long interval48 = 1250;
unsigned int _sekunde48 = 0;
unsigned int last_sekunde48 = 100;

unsigned long unix_time = 0;

unsigned int count_millis = 0;
unsigned int count_tag = 0;
unsigned int count_delay = 0;
unsigned char ntp_flag = false;

unsigned long previousMillis = 0;
const long interval = 1000;   // 1 Sekunde

uint32_t uhrzeit;

#ifndef UHR_169
unsigned int rmatrix[]{};
#endif

char str[300];
char s[5];

enum ledPositions {
    Foreground = 0,
    Background = 1,
    Frame = 2,
    Effect = 3
};

enum Command {
    COMMAND_IDLE = 0,
    COMMAND_MODE_WORD_CLOCK = 1,
    COMMAND_SET_INITIAL_VALUES = 20,
    COMMAND_SET_TIME = 30,
    COMMAND_SET_WEATHER_DATA = 90,
    COMMAND_SET_LDR = 91,
    COMMAND_SET_HOSTNAME = 92,
    COMMAND_SET_SETTING_SECOND = 93,
    COMMAND_SET_MINUTE = 94,
    COMMAND_SET_BRIGHTNESS = 95,
    COMMAND_SET_MARQUEE_TEXT = 96,
    COMMAND_SET_TIMESERVER = 97,
    COMMAND_SET_WIFI_DISABLED = 98,
    COMMAND_SET_WIFI_AND_RESTART = 99,
    COMMAND_RESET = 100,

    COMMAND_MODE_SECONDS = 200,
    COMMAND_MODE_MARQUEE = 201,
    COMMAND_MODE_RAINBOW = 202,
    COMMAND_MODE_CHANGE = 203,
    COMMAND_MODE_COLOR = 204,

    COMMAND_BRIGHTNESS = 251,
    COMMAND_SPEED = 252,
    COMMAND_LEDS = 253,
    COMMAND_POSITION = 254,

    COMMAND_REQUEST_CONFIG_VALUES = 300,
    COMMAND_REQUEST_COLOR_VALUES = 301,
    COMMAND_REQUEST_WIFI_LIST = 302,
};

int dim[20] = {30, 50, 70, 90, 110, 130, 140, 160, 200, 255, 255, 200, 160, 100, 80, 60, 40, 20, 10, 0};
int diff[20] = {-30, -20, -20, -20, -20, -20, -10, -20, -40, -55, 0, 55, 40, 60, 20, 20, 20, 20, 10, 10};

NeoPixelBus <LED_STRIPE_TYP, NeoEsp8266Dma800KbpsMethod> strip(NUM_PIXELS,2 /* LED Data PIN, FIX durch die Liebary für den ESP8266 */);

//-- WebSocketserver
WebPage_Adapter webSocket = WebPage_Adapter(80);

//--OTA--
ESP8266WebServer httpServer(81);
ESP8266HTTPUpdateServer httpUpdater;
//--OTA--
