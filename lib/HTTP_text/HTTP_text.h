#include <Arduino.h>

const String header_shared = "Content-Type: text/html\r\n"
                "Connection: close\r\n"
                "\r\n";

const String header_ok = "HTTP/1.1 200 OK\r\n" + header_shared;

const String header_404 = "HTTP/1.1 404 Page Not Found\r\n" + header_shared;

const String header_503 = "HTTP/1.1 503 Internal Server Error\r\n" + header_shared;

const String page_ok =  "<!DOCTYPE HTML>\r\n"
                  "<html>\r\n"
                  "<head>\r\n"
                  "<title>ESP32 Webserver</title>\r\n"
                  "</head>\r\n"
                  "<body>\r\n"
                  "<h1>If you see this, it works.</h1>\r\n"
                  "</body>\r\n"
                  "</html>\r\n";

const String page_404 = "<!DOCTYPE HTML>\r\n"
                  "<html>\r\n"
                  "<head>\r\n"
                  "<title>404 - You fucked up!</title>\r\n"
                  "</head>\r\n"
                  "<body>\r\n"
                  "<h1>You've made a fucky-wucky! 404!</h1>\r\n"
                  "</body>\r\n"
                  "</html>\r\n";

const String page_503 = "<!DOCTYPE HTML>\r\n"
                  "<html>\r\n"
                  "<head>\r\n"
                  "<title>503 - I fucked up!</title>\r\n"
                  "</head>\r\n"
                  "<body>\r\n"
                  "<h1>I've made a fucky-wucky! 503!</h1>\r\n"
                  "</body>\r\n"
                  "</html>\r\n";
