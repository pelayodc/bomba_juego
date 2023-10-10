#include <Keypad.h>
//#include <WiFi.h>
//#include <WebServer.h>

/* Put your SSID & Password */
const char* ssid = "Bomba"; // Enter SSID here
const char* password = "bombitapa"; //Enter Password here

//IPAddress local_ip(192,168,20,1);
//IPAddress gateway(192,168,20,1);
//IPAddress subnet(255,255,255,0);

// declaramos un objeto de la librería WebServer para acceder a sus métodos.
// el constructor toma como parámetro 80 que es el pueto por donde escuchará el servidor
//WebServer server(80);

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {14, 26, 17, 16}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {4, 0, 2, 15}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

const int pinBuzzer=23;
const int pinRed1=19;
const int pinRed2=21;
const int pinGreen=22;

const int pinRGBRed = 32;
const int pinRGBGreen = 33;
const int pinRGBBlue = 13;

int fallos=0;
bool jugando=false;

bool reiniciar=false;
int pos=0;

bool started = false;
bool checkPoint = false;
int fase = 0;
long timerMorse;

long delayed = 1500;

void setup(){
  Serial.begin(115200);
  pinMode(pinBuzzer,OUTPUT);
  pinMode(pinRed1,OUTPUT);
  pinMode(pinRed2,OUTPUT);
  pinMode(pinGreen,OUTPUT);
  pinMode(pinRGBRed,OUTPUT);
  pinMode(pinRGBGreen,OUTPUT);
  pinMode(pinRGBBlue,OUTPUT);
  digitalWrite(pinBuzzer,HIGH);

  analogWrite(pinRGBRed,255);
  analogWrite(pinRGBGreen,255);
  analogWrite(pinRGBBlue,255);

  int fallos=0;
  // configuramos un punto de acceso APSoft para establecer una red Wi-Fi con
  // su SSID, contraseña, dirección IP, máscara de subred IP y puerta de enlace IP.
  //WiFi.softAP(ssid, password);
  //WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  /*
  Para manejar las solicitudes del cliente, debemos especificar el código que se ejecutará en el
  servidor dependiendo de la ruta enviada en la solicutud
  (se asocia la UIR de la petición con la acción callback que se ejecutará), para ello se utiliza el
  método "on" que tiene dos parámetros:
  - ruta
  - código que se ejecutará cuando se reciba esa ruta.
  La primera instrucción indica que cuando el servidor reciba una solicitud sobre el directorio raiz
  (/) disparará la función handle_OnConnect()
  La segunda instrucción indica que cuando se reciba la ruta "/H" se ejecutará handle_led1on() y así
  sucesivamente. La última instrucción señala la función a
  ejecutar cuando no se proporciona una ruta válida.
  */
 // server.on("/", handle_OnConnect);
 // server.on("/H", handle_ledon);
 // server.on("/L", handle_ledoff);
 // server.onNotFound(handle_NotFound);

  // para iniciar el servidor
  //server.begin();
  //Serial.println("HTTP server started...");
  
}

void ganar() {
  digitalWrite(pinGreen,HIGH);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,LOW);
  //TODO sonido victoria
}

void loop(){
  combinacionNumerica();
  laberinto();
  colores();
  simon();
  morse();
  ganar();
}

void morse() {
  timerMorse= millis();
  char password[5]= "3532";
  pos=0;
  char answer[5]="----";
  jugando=true;
  while(jugando) {
    mostrarMorse();
    char key = keypad.getKey();
    if (key){
      Serial.println(key);
      if(key=='*'){
        if(pos!=4) {
          fallar();
          pos=0;
        } else {
        //Comprobar
          Serial.println(answer);
          Serial.println(password);
          bool fail=false;
          for(int i=0;i<4;i++) {
            if(answer[i]!=password[i]) {
            	pos=0;
              fallar();
              fail=true;
              break;
            }
          }
          if(!fail) {
          	superado();
          }
        }
      } else if(key=='#') {
        pos=0;
      } else {
        if(pos<=3) {
          answer[pos]=key;
          pos+=1;
        } else {
          digitalWrite(pinBuzzer,LOW);
          delay(100);
          digitalWrite(pinBuzzer,HIGH);
        }
      }
  	}
  }
}

long punto =400;
long raya = 1000;
long entre=400;
long espacio = 1500;
long reinicio = 4000;

void mostrarMorse() {
  switch(fase) {
    case 0:
      if(millis()-timerMorse>=reinicio) {
        encenderLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 1:
      if(millis()-timerMorse>=punto) {
        apagarLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 2:
      if(millis()-timerMorse>=entre) {
        encenderLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 3:
      if(millis()-timerMorse>=raya) {
        apagarLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 4:
      if(millis()-timerMorse>=espacio) {
        encenderLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 5:
      if(millis()-timerMorse>=raya) {
        apagarLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 6:
      if(millis()-timerMorse>=entre) {
        encenderLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 7:
      if(millis()-timerMorse>=punto) {
        apagarLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 8:
      if(millis()-timerMorse>=entre) {
        encenderLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 9:
      if(millis()-timerMorse>=raya) {
        apagarLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 10:
      if(millis()-timerMorse>=entre) {
        encenderLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 11:
      if(millis()-timerMorse>=punto) {
        apagarLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 12:
      if(millis()-timerMorse>=espacio) {
        encenderLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 13:
      if(millis()-timerMorse>=raya) {
        apagarLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 14:
      if(millis()-timerMorse>=entre) {
        encenderLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 15:
      if(millis()-timerMorse>=raya) {
        apagarLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 16:
      if(millis()-timerMorse>=espacio) {
        encenderLuz();
        timerMorse= millis();
        fase++;
      }
    break;
    case 17:
      if(millis()-timerMorse>=punto) {
        apagarLuz();
        timerMorse= millis();
        fase=0;
      }
    break;
  }
}

void mostrarLuz() {
  switch(fase) {
    case 0:
      if(millis()-timerMorse>=0) {
        analogWrite(pinRGBRed,0);
        analogWrite(pinRGBGreen,0);
        analogWrite(pinRGBBlue,255);
        timerMorse= millis();
        fase++;
      }
    break;
    case 1:
      if(millis()-timerMorse>=delayed) {
        analogWrite(pinRGBRed,255);
        analogWrite(pinRGBGreen,255);
        analogWrite(pinRGBBlue,0);
        timerMorse= millis();
        fase++;
      }
    break;
    case 2:
      if(millis()-timerMorse>=delayed) {
        analogWrite(pinRGBRed,0);
        analogWrite(pinRGBGreen,255);
        analogWrite(pinRGBBlue,128);
        timerMorse= millis();
        fase++;
      }
    break;
    case 3:
      if(millis()-timerMorse>=delayed) {
        analogWrite(pinRGBRed,0);    
        analogWrite(pinRGBGreen,0);
        analogWrite(pinRGBBlue,255);
        timerMorse= millis();
        fase++;
      }
    break;
    case 4:
      if(millis()-timerMorse>=delayed) {
        analogWrite(pinRGBRed,0);
        analogWrite(pinRGBGreen,255);
        analogWrite(pinRGBBlue,255);
        timerMorse= millis();
        fase++;
      }
    break;
    case 5:
      if(millis()-timerMorse>=delayed) {
        analogWrite(pinRGBRed,255);
        analogWrite(pinRGBGreen,0);
        analogWrite(pinRGBBlue,255);
        checkPoint=true;
        timerMorse= millis();
        fase++;
      }
    break;
    case 6:
      if(millis()-timerMorse>=delayed) {
        analogWrite(pinRGBRed,255);
        analogWrite(pinRGBGreen,255);
        analogWrite(pinRGBBlue,0);
        timerMorse= millis();
        fase++;
      }
    break;
    case 7:
      if(millis()-timerMorse>=delayed) {
        analogWrite(pinRGBRed,0);
        analogWrite(pinRGBGreen,255);
        analogWrite(pinRGBBlue,128);
        timerMorse= millis();
        fase++;
      }
    break;
    case 8:
      if(millis()-timerMorse>=delayed) {
        analogWrite(pinRGBRed,0);
        analogWrite(pinRGBGreen,0);
        analogWrite(pinRGBBlue,255);
        timerMorse= millis();
        fase=0; //Check
      }
    break;     
  }
}

void checkPress() {
  if (keypad.getKeys())
  {
    for (int i = 0; i < LIST_MAX; i++) // Scan the whole key list.
    {
      if ( keypad.key[i].stateChanged )   // Only find keys that have changed state.
      {
        int state = keypad.key[i].kstate;
        char character = keypad.key[i].kchar;
        byte index = keypad.key[i].kcode;
        switch (state)    // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
        {
          case PRESSED:
            timerMorse=millis();
            started=true;
            break;

          case RELEASED:
            started=false;
            checkValid();
            break;
        }
      }
    }
  }
}

bool ignoreFirst = true;

void checkValid() {
  if((fase == 0 || fase == 1 || fase == 4) && checkPoint) {
    superado();
    jugando=false;
  } else {
    fase = 0;
    checkPoint=false;
    if(!ignoreFirst) {
      fallar();
    } else {
      ignoreFirst=false;
    }
  }
}

void apagarLuz(){
  analogWrite(pinRGBRed,255);
  analogWrite(pinRGBGreen,255);
  analogWrite(pinRGBBlue,255);
}

void encenderLuz(){
  analogWrite(pinRGBRed,0);
  analogWrite(pinRGBGreen,0);
  analogWrite(pinRGBBlue,255);
}

void simon() {
  int ronda=0;
  pos=0;
  jugando=true;
  while(jugando) {
      mostrarSimon(ronda);
      reiniciar=false;
      pos=0;
      while(pos<=ronda && !reiniciar){
        long timer = millis();
        char key = keypad.getKey();
        while(!key && !reiniciar) {
          key = keypad.getKey();
          if(millis()-timer>=8000) {
            reiniciar=true;
          }
        }
        if(!reiniciar) {
          comprobarSimon(key);
        }
      }
      if(reiniciar==false) {
        ronda++;
        pos=0;
        if(ronda >3){
          superado();
        }        
      }   
  }
}

void comprobarSimon(char key) {
  switch(pos) {
    case 0:
      if(fallos==0) {
        if(key=='D') {
          pos++;
        } else {
          fallar();
          reiniciar=true;          
        }
      } else if(fallos==1) {
        if(key=='B') {
          pos++;
        } else {
          fallar();
          reiniciar=true;          
        }
      } else {
        if(key=='C') {
          pos++;
        } else {
          fallar();
          reiniciar=true;          
        }
      }
    break;
    case 1:
      if(fallos==0) {
        if(key=='C') {
          pos++;
        } else {
          fallar();
          reiniciar=true;          
        }
      } else if(fallos==1) {
        if(key=='D') {
          pos++;
        } else {
          fallar();
          reiniciar=true;          
        }
      } else {
        if(key=='B') {
          pos++;
        } else {
          fallar();
          reiniciar=true;          
        }
      }
    break;
    case 2:
      if(fallos==0) {
        if(key=='A') {
          pos++;
        } else {
          fallar();
          reiniciar=true;          
        }
      } else if(fallos==1) {
        if(key=='C') {
          pos++;
        } else {
          fallar();
          reiniciar=true;          
        }
      } else {
        if(key=='D') {
          pos++;
        } else {
          fallar();
          reiniciar=true;          
        }
      }
    break;    
    case 3:
      if(fallos==0) {
        if(key=='B') {
          pos++;
        } else {
          fallar();
          reiniciar=true;          
        }
      } else if(fallos==1) {
        if(key=='A') {
          pos++;
        } else {
          fallar();
          reiniciar=true;          
        }
      } else {
        if(key=='A') {
          pos++;
        } else {
          fallar();
          reiniciar=true;          
        }
      }
    break;
  }
}

void mostrarSimon(int cant) {
  if(cant>=0){
    //Azul
    delay(300);
    analogWrite(pinRGBRed,255);
    analogWrite(pinRGBGreen,255);
    analogWrite(pinRGBBlue,0);
    delay(1000);
    analogWrite(pinRGBRed,255);
    analogWrite(pinRGBGreen,255);
    analogWrite(pinRGBBlue,255);
  }
   if(cant>=1){
     //Amarillo
    delay(300);
    analogWrite(pinRGBRed,0);
    analogWrite(pinRGBGreen,0);
    analogWrite(pinRGBBlue,255);
    delay(1000);
    analogWrite(pinRGBRed,255);
    analogWrite(pinRGBGreen,255);
    analogWrite(pinRGBBlue,255);
  }
   if(cant>=2){
     //Rojo
    delay(300);
    analogWrite(pinRGBRed,0);
    analogWrite(pinRGBGreen,255);
    analogWrite(pinRGBBlue,255);
    delay(1000);
    analogWrite(pinRGBRed,255);
    analogWrite(pinRGBGreen,255);
    analogWrite(pinRGBBlue,255);
  }
   if(cant>=3){
    //Verde
    delay(300);
    analogWrite(pinRGBRed,255);
    analogWrite(pinRGBGreen,0);
    analogWrite(pinRGBBlue,255);
    delay(1000);
    analogWrite(pinRGBRed,255);
    analogWrite(pinRGBGreen,255);
    analogWrite(pinRGBBlue,255);
  }
}

void colores() {
  delay(3000);
  checkPress();
  fase =0;
  jugando=true;
  started = false;
  while(jugando) {
    checkPress();
    if(started) {
      mostrarLuz();
    } else {
    analogWrite(pinRGBRed,255);
    analogWrite(pinRGBGreen,255);
    analogWrite(pinRGBBlue,255);
    }
  }  
}

void laberinto() {
  int password[13] = {0,2,2,3,1,3,2,3,2,0,2,2};
  pos=0;
  bool pull=false;
  jugando =true;
  while(jugando) {
    char key = keypad.getKey();
    switch(key) {
      case '2':
        if(password[pos]==0){
          pos+=1;              
        } else {
          fallar();
        }   
        break;
      case '4':
        if(password[pos]==1){
          pos+=1;              
        } else {
          fallar();
        }   
        break;
      case '6':
        if(password[pos]==2){
          pos+=1;              
        } else {
          fallar();
        }   
        break;
      case '8':
        if(password[pos]==3){
          pos+=1;              
        } else {
          fallar();
        }   
        break;
      default:
        break;
    }

    if(pos==12){
      superado();
    }
  }
}

void combinacionNumerica() {
  char password[5]= "1435";
  pos=0;
  char answer[5]="----";
  jugando = true;
  while(jugando) {
    char key = keypad.getKey();
    if (key){
      Serial.println(key);
      if(key=='*'){
        if(pos!=4) {
          fallar();
          pos=0;
        } else {
        //Comprobar
          Serial.println(answer);
          Serial.println(password);
          bool fail=false;
          for(int i=0;i<4;i++) {
            if(answer[i]!=password[i]) {
            	pos=0;
              fallar();
              fail=true;
              break;
            }
          }
          if(!fail) {
            superado();
          }
        }
      } else if(key=='#') {
        pos=0;
      } else {
        if(pos<=3) {
          answer[pos]=key;
          pos+=1;
        } else {
          digitalWrite(pinBuzzer,LOW);
          delay(100);
          digitalWrite(pinBuzzer,HIGH);
        }
      }
  	}
  }
}

//GESTIÓN DE INTENTOS

void fallar() {
  Serial.println("Has fallado"); 
  fallos+=1;
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(200);
  digitalWrite(pinBuzzer,HIGH);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,LOW);
  switch(fallos){
    case 0:
    digitalWrite(pinRed1,LOW);
    digitalWrite(pinRed2,LOW);
    break;
    case 1:
    digitalWrite(pinRed1,HIGH);
    digitalWrite(pinRed2,LOW);
    break;
    case 2:
    digitalWrite(pinRed1,HIGH);
    digitalWrite(pinRed2,HIGH);
    break;
    case 3:
    jugando=false;
    perder();
    break;
  }
}

void perder() {
  Serial.println("Has perdido");
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,LOW);
  delay(300);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(300);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(300);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(300);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(300);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(300);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(200);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(200);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(200);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(200);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(200);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(200);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(200);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(200);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(200);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(200);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(200);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(200);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(200);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(200);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(200);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(200);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(200);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(200);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(100);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);
  delay(100);
  digitalWrite(pinRed1,HIGH);
  digitalWrite(pinRed2,HIGH);
  digitalWrite(pinBuzzer,LOW);
  delay(1500);
  digitalWrite(pinRed1,LOW);
  digitalWrite(pinRed2,LOW);
  digitalWrite(pinBuzzer,HIGH);  
  while(true){}
}

void superado() {
  digitalWrite(pinGreen,HIGH); 
  digitalWrite(pinBuzzer,LOW);
  delay(200);
  digitalWrite(pinBuzzer,HIGH);
  delay(100);
  digitalWrite(pinBuzzer,LOW);
  delay(200);
  digitalWrite(pinBuzzer,HIGH);
  digitalWrite(pinGreen,LOW); 
  jugando=false;
}
