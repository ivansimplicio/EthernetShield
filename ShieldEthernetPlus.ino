#include <SPI.h>
#include <Ethernet.h>
#include <LiquidCrystal.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x83, 0xEA };
IPAddress ip(192, 168, 0, 123);
EthernetServer server(80); // ou  = EthernetServer(80);
LiquidCrystal lcd(7,6,5,4,3,2);
#define LAMP 9


void setup() {
  pinMode(LAMP, OUTPUT);
  Ethernet.begin(mac, ip); //inicia biblioteca e configurações de rede
  server.begin(); //habilita o servidor a conexões com clientes
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Endereco local:");
  lcd.setCursor(0,1);
  lcd.print(Ethernet.localIP());
}

void loop() {
  EthernetClient cliente = server.available(); //obtém um cliente que está conectado ao servidor e tem dados disponíveis para leitura
  String dados;
  
  if(cliente){
    while(cliente.connected()){ //verifica se o cliente está conectado (ainda tem dados a serem lidos)
      if(cliente.available()){ //retorna o número de bytes disponíveis para leitura
        char byteDados = cliente.read();
        dados += byteDados;
         
        // CÓDIGO DA PÁGINA EM HTML AQUI
        if(byteDados == '\n'){
          cliente.print("<HTML>");
        
          cliente.print("<HEAD>");
          cliente.print("<STYLE> h1{ font-family: Courier; text-decoration: none;} </STYLE>");
          cliente.print("<TITLE> CONTROLE RESIDENCIAL </TITLE>");
          cliente.print("</HEAD>");
          
          cliente.print("<BODY>");
          cliente.print("<h1> CONTROLE RESIDENCIAL </h1>");
          cliente.print("<a href=\"/0001\"> <input type=\"button\" value=\"LIGAR LAMPADA\"> </a>");
          cliente.print("<a href=\"/0000\"> <input type=\"button\" value=\"DESLIGAR LAMPADA\"> </a>");
          cliente.print("<p style=\"font-family: Courier\"> Desenvolvido por Ivan Simplicio</p>");
          cliente.print("</BODY>");
          
          cliente.print("</HTML>");
          cliente.stop();
         
          if(dados.indexOf("0001") > 0){
            digitalWrite(LAMP, HIGH);
            //Serial.print(dados);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("LAMPADA - ON");
          }else if(dados.indexOf("0000") > 0){
            digitalWrite(LAMP, LOW);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("LAMPADA - OFF");
          }
        }
        // ATÉ AQUI
      }
    }
  }
}
