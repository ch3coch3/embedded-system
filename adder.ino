const int f[] = {4,3,2};
const int b[] = {7,6,5};
int s[4];
int cin[] = {0,0,0,0,0};
int A[] = {0,0,0,0};
int B[] = {0,0,0,0};
int C[] = {1,0,0,0};  // represent 1 to deal with 2'x complement
int D[] = {1,0,0,1};  // 2's complement of -1 to transform back to normal binary
void setup() {
  // put your setup code here, to run once:
  for(int i = 0;i<3;i++){
    pinMode(f[i],INPUT);
    pinMode(b[i],INPUT);
  }
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  Serial.begin(9600);
  Serial.println("start");
}

void loop() {
  // put your main code here, to run repeatedly:

  // read the value
  for(int i = 0;i < 3;i++){
    A[i] = digitalRead(f[i]);
    B[i] = digitalRead(b[i]);
  }
  

  // transform to 4-bit
  if(A[2] == 0){
    A[3] = A[2];
  }
  if(A[2] == 1){
    A[3] = 0; A[2] = 0;
    for(int i = 0;i < 4;i++){
      A[i]=(A[i] == 1)? 0 :1;
    }
    for(int i = 0;i < 4;i++){
      int a = 0;
      a = A[i] ^ C[i] ^ cin[i];
      cin[i+1] = (A[i] & C[i]) | (cin[i] & (A[i] ^ C[i]));
      cin[i] = 0;
      A[i] = a;
    }
  }
  
  if(B[2] == 0){
    B[3] = B[2];
  }

  if(B[2] == 1){
    B[3] = 0; B[2] = 0;
    for(int i = 0;i < 4;i++){
      B[i]=(B[i] == 1)? 0 :1;
    }

    for(int i = 0;i < 4;i++){
      int a = 0;
      a = B[i] ^ C[i] ^ cin[i];
      cin[i+1] = (B[i] & C[i]) | (cin[i] & (B[i] ^ C[i]));
      cin[i] = 0;
      B[i] = a;
    }
  }
//  Serial.print("A");
//  for(int i = 3; i >=0 ; i--){
//    Serial.print(A[i]); 
//  }
//  Serial.println(" ");
//  Serial.print("B");
//  for(int i = 3; i >=0 ; i--){
//    Serial.print(B[i]); 
//  }
  
  // adder
  for(int i = 0;i < 4;i++){
    s[i] = A[i] ^ B[i] ^ cin[i];
    cin[i+1] = (A[i] & B[i]) | (cin[i] & (A[i] ^ B[i]));
    cin[i] = 0;
  }
//  Serial.print(A[1]); 
  digitalWrite(12, s[3]);
  digitalWrite(11, s[2]);
  digitalWrite(10, s[1]);
  digitalWrite(9, s[0]);
  
  
  for(int i = 3; i >=0 ; i--){
    Serial.print(s[i]); 
  }
  Serial.println("");
  Serial.println("--------------------------");
  delay(2000);
  
}
