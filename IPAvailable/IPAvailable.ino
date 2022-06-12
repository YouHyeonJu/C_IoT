
long lastMsg=0;
bool IsAvailableIP( const char * szIP )
{
  if( szIP == NULL ) return false;
  
  int len = strlen( szIP );
  
  if( len > 15 || len < 7 ) return false;
  
  int nNumCount = 0;
  int nDotCount = 0;
  
  // 유효성검사
  for( int i = 0; i< len; i++ )
  {
    if( szIP[ i ] < '0' || szIP[ i ] > '9' ){
      if( '.' == szIP[i] ) { 
        ++nDotCount; nNumCount = 0;
      }else return false; //"."이 아닌 다른문자가 들어오면 false 출력
    }else{
        if( ++nNumCount > 3 ) return false; //IP 각 자리가 3자리가 넘을 시 false 출력
      }
  }
  if( nDotCount != 3 ) return false; //"."이 3개가 들어오지 않으면 false 출력
  
  return true;
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  char ip[20]="192.168.1.22";
  char errip[20]="192.168.1";
  String stip="192.168.1.22";
  long now = millis();
    if(now - lastMsg > 1000){
      lastMsg=now;
      Serial.print("ip:");
      Serial.println(IsAvailableIP(ip));
      Serial.print("errip:");
      Serial.println(IsAvailableIP(errip));
//      Serial.print("stip:");
//      Serial.println(IsAvailableIP(stip));
    }
}
