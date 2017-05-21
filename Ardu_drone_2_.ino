#define MOTOR1 3 
#define MOTOR2 9 
#define MOTOR3 10 
#define MOTOR4 11 

boolean stringComplete_ = false; 
int motor[4];
int cnt = 0;
String data_ = "";


//char dataBit[8];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  data_.reserve(45);

  motor[0]=0;
  motor[1]=0;
  motor[2]=0;
  motor[3]=0;
 
  pinMode(3, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  delay(1000);
  for(int i = 0; i<1100; i++)initESC(2000);
  delay(1000);
  for(int i = 0; i<1100; i++)initESC(1000);
  delay(1000);
}

void loop() {
  if(Serial.available() > 0) {
    char inChar = (char) Serial.read();
  //  dataBit[cnt++] = inChar;

  //  if(inChar == '\n' || cnt == 8){
   //   stringComplete_ = true;
    //  cnt = 0;
   // }
   data_ += inChar;

    if(inChar == '\n'){
      data_+='\0';
      stringComplete_ = true;
    }
  }
  sendpluse(); 
}

void str_to_int(String str){
  int i=0, flag = 0;
  int temp = 0, arp_cnt = 0;
  arp_cnt = 0;

  
  while(1){
    if(str[i] == '-'){
      flag = 1;
    }
    else if(str[i] >= '0' && str[i] <= '9'){
      temp = temp * 10 + str[i]-'0';
    }
    else if(str[i] == ',' || str[i] == '\n'){
      if(flag)
        temp *= -1;
      motor[arp_cnt++] = (temp+1000);
      
      temp = 0;
      flag = 0;
    }   

    if(str[i++] == '\n' || i>40)
     break;
   }  
}


void sendpluse()
{
  if(stringComplete_){
   //for(int i=0; i<8; i+=2)
   //   motor[i/2] = encodeBitData(i,i+1);
   // stringComplete_ = false;   
       str_to_int(data_);
    //delay(100);
    data_ = "";
    stringComplete_ = false;
 
  }
 
  digitalWrite(3, HIGH);
  delayMicroseconds(motor[0]);
  digitalWrite(3,LOW);
  delayMicroseconds(20);
  digitalWrite(9, HIGH);
  delayMicroseconds(motor[1]);
  digitalWrite(9,LOW);
  delayMicroseconds(20);
  digitalWrite(10, HIGH);
  delayMicroseconds(motor[2]);
  digitalWrite(10,LOW);
  delayMicroseconds(20);
  digitalWrite(11, HIGH);  
  delayMicroseconds(motor[3]);
  digitalWrite(11,LOW);
  delayMicroseconds(20);  
}

void initESC(int mydelay)
{
  digitalWrite(3, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  delayMicroseconds(mydelay);
  digitalWrite(3,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  delayMicroseconds(20);
}
/*
int encodeBitData(int upBit, int downBit){
  int result = 0;
  int bitCnt = 0;
 
  while(bitCnt < 16){
    result <<= 1;

    if(bitCnt < 8){
      if(dataBit[upBit] & 1)
        result |= 1;
       
      dataBit[upBit] >>= 1;
    }
    else{
      if(dataBit[downBit] & 1)
        result |= 1;
       
      dataBit[downBit] >>= 1;
    }
    
   bitCnt++;
  }
  
  return result;
}*/
