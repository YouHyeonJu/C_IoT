#include <WiFi.h>
#define WiFi_SEARCH_NUM 5 // 최대 비교할 AP 개수
#define WiFi_SAVE_NUM 15// 최대 wifi 등록 개수
int debug=1;
char   ssid[20];
char   password[20];
typedef struct SSID_PASSWORD{       //WiFi ID_PW 구조체
   char SSID[20];
   char Password[20];

}ID_PW;
ID_PW DW1[WiFi_SAVE_NUM]={
    {"chnj00","yds54321"},
    {"chnj01","yds54321"},{"chnj02","yds54321"},{"chnj03","yds54321"},{"chnj04","yds54321"},
    {"chnj05","yds54321"},{"chnj06","yds54321"},{"chnj07","yds54321"},{"chnj08","yds54321"},{"chnj09","yds54321"},
    {"chnj10","yds54321"},{"chnj11","yds54321"},{"chnj12","yds54321"},{"chnj13","yds54321"},{"chnj14","yds54321"}
};
void findtopWiFi(){
  int n = WiFi.scanNetworks(); //WiFi 갯수를 n에 담음
    String rs[n];
    int AP_num;
    if (n == 0) { 
      Serial.println("no networks found");
    } else {
      Serial.print(n);
      Serial.println(" networks found");
      if(n >= WiFi_SEARCH_NUM){
          AP_num=WiFi_SEARCH_NUM;
      }else{
        AP_num=n;
      }
      for (int i = 0; i < AP_num; i++) { 
        if(debug == 1){
              Serial.print(i + 1);
              Serial.print(": ");
              Serial.print(WiFi.SSID(i));
              Serial.print(" (");
              Serial.print(WiFi.RSSI(i));
              Serial.print(")");
              Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
          }
          rs[i]=WiFi.SSID(i);
          delay(10);
      }
      bool exitLoop=false; 
      for(int i=0; i<AP_num; i++){             //등록된 WiFi (구조체)ID_PW 중에서 일치하는 ID가 있으면 그 password를 얻음
          for (int j=0;j<WiFi_SAVE_NUM;j++){
            if(rs[i] == String(DW1[j].SSID)){      //scan 해온 SSID중에서 등록되어 있는 SSID 찾기. 및 연결
                String strSSID=DW1[j].SSID;
                String strpasswd=DW1[j].Password;
                ssid[0]=0;
                password[0]=0;
                strcpy(ssid,strSSID.c_str());
                strcpy(password,strpasswd.c_str());
                if(debug == 1){
                  Serial.print("find_h_SSID : ");
                  Serial.println(ssid);
                  Serial.print("find_password : ");
                  Serial.println(password);
                }
                // WiFi.begin(ssid, password);
                exitLoop=true;                   //2중 for문 나가기
                break;
            }
          }
          if(exitLoop==true)
          break;
      }
    }
    if(debug == 1){
      Serial.println("----SAVE_AP----");
      for(int i=0; i<WiFi_SAVE_NUM;i++){
        Serial.print("SSID : ");
        Serial.print(DW1[i].SSID);
        Serial.print("  password : ");
        Serial.println(DW1[i].Password);
      }
      Serial.println("---------------");
    }
    
   
}
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
