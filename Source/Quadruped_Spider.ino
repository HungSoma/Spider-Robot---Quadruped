#include <Servo.h>  
#include <math.h> 
#define walk 1
#define updown 2
#define spin 3
#define ziczac 4
#define TRIG_PIN A0    // Chân Trig nối với chân A0
#define ECHO_PIN A1    // Chân Echo nối với chân A1
#define TIME_OUT 5000 // Time_out của pulseIn là 5000 microsecond
const float Coxa = 27;
const float Femur = 55;
const float Tibia = 79;
const double z_offset = 60;
const double x_offset = 60;
const double y_offset = 60;
int t =0;
double x_cur1,y_cur1,z_cur1,x_cur2,y_cur2,z_cur2,x_cur3,y_cur3,z_cur3,x_cur4,y_cur4,z_cur4;
const double pi = PI;
//long distanceCm;
Servo servo[4][3];
int leg[4] = { 0,1,2,3};
//define servos' ports
const int servo_pin[4][3] = { {2, 3, 4}, {5, 6, 7}, {8, 9, 10}, {11, 12, 13} };
void attch(){
   for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      servo[i][j].attach(servo_pin[i][j]);
      delay(20);
    }
  }
}
void default_position(int speed){
     moveRF(1,x_offset,y_offset,z_offset,speed);
     moveRB(1,x_offset,-y_offset,z_offset,speed);
     moveLF(1,-x_offset,y_offset,z_offset,speed);
     moveLB(1,-x_offset,-y_offset,z_offset,speed);
     curent_xyz(x_offset,y_offset,z_offset,x_offset,-y_offset,z_offset,-x_offset,y_offset,z_offset,-x_offset,-y_offset,z_offset);
}
void setup()
{Serial.begin(9600);
  //initialize all servos
  attch();
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  // set stand position
  default_position(0);
}
// STAND UP
      
void loop(void)
{
  delay(1000);

   /*long distanceCm = getDistance();
    Serial.print(" khoang cach : ");
    Serial.println(distanceCm);
*/
  body_dance(0);
 
  for(int i =0; i <3 ; i++)
  {  
  walk_forward(200,50,t);
  t++;
  }
  t =0;
  moveRB(0,x_offset,-y_offset,z_offset,200);
  moveRF(1,x_offset,y_offset,z_offset,50);
  for(int i =0; i <3; i++)
  {
  turnL(200);
  }
   for(int i =0; i <2 ; i++)
  {
  walk_forward(200,55,t);
  t++;
  }
  t =0;
  moveRB(0,x_offset,-y_offset,z_offset,200);
  moveRF(1,x_offset,y_offset,z_offset,50);
    for(int i =0; i <3; i++)
  {
  turnR(200);
  }
  up_down_body(40,0);
  up_down_body(-40,0);
  handshake(0);
     for(int i =0; i <2 ; i++)
  {
  walk_backward(200,50,t);
  t++;
  }
  t =0;
  //delay(200);
  
  default_position(0);
  for(int i =0; i<=2; i++){
  left_right_updown(0,20);
  //delay(100);
  left_right_updown(1,20);
  //delay(100);
  left_right_updown(1,20);
  //delay(100);
  left_right_updown(0,20);
  }
   
   delay(500);
    
  while(1);
}
int  RadtoDo(double Rad ){         //doi tu radian sang do
   double Do = Rad*180/pi;
   return Do;
}
void walk_forward(int speed, int longdis, int t ){
   int i ;
   if(t ==0){
  for( i = 0; i<= 25; i++){
    movebody(x_offset+i,y_offset-i,z_offset,x_offset+i,-y_offset-i,z_offset,-x_offset+i,y_offset-i,z_offset,-x_offset+i,-y_offset-i,z_offset,0,0);
    delay(10);
  }
   moveRB(0,x_offset+25, -y_offset+longdis-25,z_offset,speed);
   for(int j =0; j<= 25; j++){
    movebody(x_offset+i-j,y_offset-i+j,z_offset,x_offset+25-j,-y_offset+longdis+j-25,z_offset,-x_offset+i-j,y_offset-i+j,z_offset,-x_offset+i-j,-y_offset-i+j,z_offset,0,0);
    delay(10);
  }
   }
   else{
  moveRB(0,x_offset, -y_offset+longdis,z_offset,speed);
   }
  moveRF(0,x_offset,y_offset+longdis,z_offset,speed);
  movebody(x_offset,y_offset+longdis,z_offset,x_offset,-y_offset+longdis,z_offset,-x_offset,y_offset,z_offset,-x_offset,-y_offset,z_offset,longdis,0);
  delay(300);
  moveLB(0,-x_offset,-y_offset+longdis,z_offset,speed);
  moveLF(0,-x_offset,y_offset+longdis,z_offset,speed);
  movebody(x_offset,y_offset,z_offset,x_offset,-y_offset,z_offset,-x_offset,y_offset+longdis,z_offset,-x_offset,-y_offset+longdis,z_offset,longdis,0);
  curent_xyz(x_offset,y_offset,z_offset,x_offset,-y_offset,z_offset,-x_offset,y_offset+longdis,z_offset,-x_offset,-y_offset+longdis,z_offset);
  delay(300);
}
void walk_backward(int speed, int longdis, int t){
     int i ;
     if(t ==0){
  for( i = 0; i<= 25; i++){
    movebody(x_offset+i,y_offset+i,z_offset,x_offset+i,-y_offset+i,z_offset,-x_offset+i,y_offset+i,z_offset,-x_offset+i,-y_offset+i,z_offset,0,0);
    delay(10);
  }
   moveRF(0,x_offset+25,y_offset-longdis+25,z_offset,speed);
   for(int j =0; j<= 25; j++){
    movebody(x_offset+25-j,y_offset+25-longdis-j,z_offset,x_offset+i-j,-y_offset+i-j,z_offset,-x_offset+i-j,y_offset+i-j,z_offset,-x_offset+i-j,-y_offset+i-j,z_offset,0,0);
    delay(10);
  }
     }
     else{
       moveRF(0,x_offset,y_offset-longdis,z_offset,speed);
      }
 
  moveRB(0,x_offset, -y_offset-longdis,z_offset,speed);
  movebody(x_offset,y_offset-longdis,z_offset,x_offset,-y_offset-longdis,z_offset,-x_offset,y_offset,z_offset,-x_offset,-y_offset,z_offset,-longdis,0);
  delay(300);
  moveLF(0,-x_offset,y_offset-longdis,z_offset,speed);
  moveLB(0,-x_offset,-y_offset-longdis,z_offset,speed);
  movebody(x_offset,y_offset,z_offset,x_offset,-y_offset,z_offset,-x_offset,y_offset-longdis,z_offset,-x_offset,-y_offset-longdis,z_offset,-longdis,0);
  curent_xyz(x_offset,y_offset,z_offset,x_offset,-y_offset,z_offset,-x_offset,y_offset-longdis,z_offset,-x_offset,-y_offset-longdis,z_offset);
  delay(300);
}

void turnL(int speed){
 // default_position(speed);
 int i ;
  for( i = 0; i<= 20; i++){
    movebody(x_offset+i,y_offset-i,z_offset,x_offset+i,-y_offset-i,z_offset,-x_offset+i,y_offset-i,z_offset,-x_offset+i,-y_offset-i,z_offset,0,0);
    delay(10);
  }
  moveRB(0,90, -30,z_offset,speed);
   for(int j =0; j<= 20; j++){
    movebody(x_offset+i-j,y_offset-i+j,z_offset,90-j,-30+j,z_offset,-x_offset+i-j,y_offset-i+j,z_offset,-x_offset+i-j,-y_offset-i+j,z_offset,0,0);
    delay(10);
  }
 
  moveRF(0,10,80,z_offset,speed);
  
  moveLF(0,-80,10,z_offset,speed);
 
  moveLB(0,-10,-80,z_offset,speed);
  default_position(0);
  delay(500);
}
void turnR(int speed){
  //default_position(speed);
  int i;
    for( i = 0; i<= 20; i++){
    movebody(x_offset-i,y_offset-i,z_offset,x_offset-i,-y_offset-i,z_offset,-x_offset-i,y_offset-i,z_offset,-x_offset-i,-y_offset-i,z_offset,0,0);
    delay(10);
  }
  moveLB(0,-90, -30,z_offset,speed);
  //curent_xyz(x_offset-i,y_offset-i,z_offset,x_offset-i,-y_offset-i,z_offset,-x_offset-i,y_offset-i,z_offset,-90,-30,z_offset);
   for(int j = 0; j<=20 ; j++){
    movebody(x_offset-i+j,y_offset-i+j,z_offset,x_offset-i+j,-y_offset-i+j,z_offset,-x_offset-i+j,y_offset-i+j,z_offset,-90+j,-30+j,z_offset,0,0);
    delay(10);
  }
  //moveLB(0,15,-70,z_offset,speed);
  moveLF(0,-10, 80,z_offset,speed);
  moveRF(0,80,-10,z_offset,speed);
  moveRB(0,10,-80,z_offset,speed);
  default_position(0);
  delay(500);
}
void handshake(int speed){
  //default_position(speed);
  int i ,k;
  for( i =0; i<= 30; i++){
  //movebody(x_offset+i,y_offset+i,z_offset,x_offset+i,-y_offset+i,z_offset,-x_offset+i,y_offset+i,z_offset,-x_offset+i,-y_offset+i,z_offset,0,0);
   movebody(x_cur1+i,y_cur1+i,z_cur1,x_cur2+i,y_cur2+i,z_cur2,x_cur3+i,y_cur3+i,z_cur3,x_cur4+i,y_cur4+i,z_cur4,0,0);
   delay(15);
  }
  curent_xyz(x_cur1+i,y_cur1+i,z_cur1,x_cur2+i,y_cur2+i,z_cur2,x_cur3+i,y_cur3+i,z_cur3,x_cur4+i,y_cur4+i,z_cur4);
  servo[0][0].write(35);
  for(int j = 0; j< 3; j++){
  for(int i = 70; i <= 130; i++){
    servo[0][1].write(i);
    delay(10);
  }
  for(int i = 130; i >= 70; i--){
    servo[0][1].write(i);
    delay(10);
  }
  }
    for( k =0; k<= 30; k++){
  //movebody(x_offset+i,y_offset+i,z_offset,x_offset+i,-y_offset+i,z_offset,-x_offset+i,y_offset+i,z_offset,-x_offset+i,-y_offset+i,z_offset,0,0);
   movebody(x_cur1-k,y_cur1-k,z_cur1,x_cur2-k,y_cur2-k,z_cur2,x_cur3-k,y_cur3-k,z_cur3,x_cur4-k,y_cur4-k,z_cur4,0,0);
   delay(15);
  }
  curent_xyz(x_cur1-k,y_cur1-k,z_cur1,x_cur2-k,y_cur2-k,z_cur2,x_cur3-k,y_cur3-k,z_cur3,x_cur4-k,y_cur4-k,z_cur4);
}
void up_down_body(int z_add, int speed){ //default 52 mm , 52>z_add >-52
  //default_position(0);
  //delay(500);
  int z_max_min = z_cur1 + z_add ;
  if( z_add > 0){
  for ( int  z_new = z_cur1; z_new <= z_max_min; z_new++)
  {
  //movebody(x_offset,y_offset,z_new,x_offset,-y_offset,z_new,-x_offset,y_offset,z_new,-x_offset,-y_offset,z_new,0,speed);
  movebody(x_cur1,y_cur1,z_new,x_cur2,y_cur2,z_new,x_cur3,y_cur3,z_new,x_cur4,y_cur4,z_new,0,speed);
  delay(10);
  curent_xyz(x_cur1,y_cur1,z_new,x_cur2,y_cur2,z_new,x_cur3,y_cur3,z_new,x_cur4,y_cur4,z_new);
  }
  }
  else{
    for ( int  z_new = z_cur1; z_new >= z_max_min; z_new--)
  {
  //movebody(x_offset,y_offset,z_new,x_offset,-y_offset,z_new,-x_offset,y_offset,z_new,-x_offset,-y_offset,z_new,0,speed);
  movebody(x_cur1,y_cur1,z_new,x_cur2,y_cur2,z_new,x_cur3,y_cur3,z_new,x_cur4,y_cur4,z_new,0,speed);
  delay(10);
  curent_xyz(x_cur1,y_cur1,z_new,x_cur2,y_cur2,z_new,x_cur3,y_cur3,z_new,x_cur4,y_cur4,z_new);
  }
  }
 }
void body_dance(int speed){
 // default_position(500);
 int i,j,k,l,m,n,o,p,q,w;
  for (  i = 0;  i <= 35; i++)
  {
  movebody(x_cur1,y_cur1+i,z_cur1,x_cur2,y_cur2+i,z_cur2,x_cur3,y_cur3+i,z_cur3,x_cur4,y_cur4+i,z_cur4,0,speed);
   delay(20);
  }
  curent_xyz(x_cur1,y_cur1+i,z_cur1,x_cur2,y_cur2+i,z_cur2,x_cur3,y_cur3+i,z_cur3,x_cur4,y_cur4+i,z_cur4);
    for (   j = 0; j <= 35; j++)
  {
  movebody(x_cur1-j,y_cur1-j,z_cur1+j,x_cur2-j,y_cur2-j,z_cur2+j,x_cur3-j,y_cur3-j,z_cur3+j,x_cur4-j,y_cur4-j,z_cur4+j,0,speed);
  delay(20);
  }
  curent_xyz(x_cur1-j,y_cur1-j,z_cur1+j,x_cur2-j,y_cur2-j,z_cur2+j,x_cur3-j,y_cur3-j,z_cur3+j,x_cur4-j,y_cur4-j,z_cur4+j);
   for (  k = 0; k <= 35; k++)
  {
  movebody(x_cur1+k,y_cur1-k,z_cur1-k,x_cur2+k,y_cur2-k,z_cur2-k,x_cur3+k,y_cur3-k,z_cur3-k,x_cur4+k,y_cur4-k,z_cur4-k,0,speed);
  delay(20);
  }
  curent_xyz(x_cur1+k,y_cur1-k,z_cur1-k,x_cur2+k,y_cur2-k,z_cur2-k,x_cur3+k,y_cur3-k,z_cur3-k,x_cur4+k,y_cur4-k,z_cur4-k);
     for (  l = 0; l <= 35; l++)
  {
  movebody(x_cur1+l,y_cur1+l,z_cur1+l,x_cur2+l,y_cur2+l,z_cur2+l,x_cur3+l,y_cur3+l,z_cur3+l,x_cur4+l,y_cur4+l,z_cur4+l,0,speed);
  delay(20);
  }
  curent_xyz(x_cur1+l,y_cur1+l,z_cur1+l,x_cur2+l,y_cur2+l,z_cur2+l,x_cur3+l,y_cur3+l,z_cur3+l,x_cur4+l,y_cur4+l,z_cur4+l);
      for ( m = 0; m <= 35; m++)
  {
  movebody(x_cur1-m,y_cur1+m,z_cur1-m,x_cur2-m,y_cur2+m,z_cur2-m,x_cur3-m,y_cur3+m,z_cur3-m,x_cur4-m,y_cur4+m,z_cur4-m,0,speed);
  delay(20);
  }
   curent_xyz(x_cur1-m,y_cur1+m,z_cur1-m,x_cur2-m,y_cur2+m,z_cur2-m,x_cur3-m,y_cur3+m,z_cur3-m,x_cur4-m,y_cur4+m,z_cur4-m);
  // Reverse  
       for (  n = 0; n <= 35; n++)
  {
  movebody(x_cur1+n,y_cur1-n,z_cur1+n,x_cur2+n,y_cur2-n,z_cur2+n,x_cur3+n,y_cur3-n,z_cur3+n,x_cur4+n,y_cur4-n,z_cur4+n,0,speed);
  delay(20);
  }
  curent_xyz(x_cur1+n,y_cur1-n,z_cur1+n,x_cur2+n,y_cur2-n,z_cur2+n,x_cur3+n,y_cur3-n,z_cur3+n,x_cur4+n,y_cur4-n,z_cur4+n);
       for (  o = 0; o <= 35; o++)
  {
  movebody(x_cur1-o,y_cur1-o,z_cur1-o,x_cur2-o,y_cur2-o,z_cur2-o,x_cur3-o,y_cur3-o,z_cur3-o,x_cur4-o,y_cur4-o,z_cur4-o,0,speed);
  delay(20);
  }
   curent_xyz(x_cur1-o,y_cur1-o,z_cur1-o,x_cur2-o,y_cur2-o,z_cur2-o,x_cur3-o,y_cur3-o,z_cur3-o,x_cur4-o,y_cur4-o,z_cur4-o);
     for (  p = 0; p <= 35; p++)
  {
  movebody(x_cur1-p,y_cur1+p,z_cur1+p,x_cur2-p,y_cur2+p,z_cur2+p,x_cur3-p,y_cur3+p,z_cur3+p,x_cur4-p,y_cur4+p,z_cur4+p,0,speed);
  delay(20);
  }
  curent_xyz(x_cur1-p,y_cur1+p,z_cur1+p,x_cur2-p,y_cur2+p,z_cur2+p,x_cur3-p,y_cur3+p,z_cur3+p,x_cur4-p,y_cur4+p,z_cur4+p);
     for (   q = 0;  q <=35; q++)
  {
  movebody(x_cur1+q,y_cur1+q,z_cur1-q,x_cur2+q,y_cur2+q,z_cur2-q,x_cur3+q,y_cur3+q,z_cur3-q,x_cur4+q,y_cur4+q,z_cur4-q,0,speed);
  delay(20);
  }
  curent_xyz(x_cur1+q,y_cur1+q,z_cur1-q,x_cur2+q,y_cur2+q,z_cur2-q,x_cur3+q,y_cur3+q,z_cur3-q,x_cur4+q,y_cur4+q,z_cur4-q);
    for (  w = 0;  w <= 35; w++)
  {
  movebody(x_cur1,y_cur1-w,z_cur1,x_cur2,y_cur2-w,z_cur2,x_cur3,y_cur3-w,z_cur3,x_cur4,y_cur4-w,z_cur4,0,speed);
   delay(20);
  }
  curent_xyz(x_cur1,y_cur1-w,z_cur1,x_cur2,y_cur2-w,z_cur2,x_cur3,y_cur3-w,z_cur3,x_cur4,y_cur4-w,z_cur4);
}
void left_right_updown(int backfull, int range){
  int i,j ;
  if( backfull == 0){ // left down _ right up
  for( i =0; i <= range; i++){
   movebody(x_cur1,y_cur1,z_cur1+i,x_cur2,y_cur2,z_cur2+i,x_cur3,y_cur3,z_cur3-i,x_cur4,y_cur4,z_cur4-i,0,0);
   delay(18);
  }
  curent_xyz(x_cur1,y_cur1,z_cur1+i,x_cur2,y_cur2,z_cur2+i,x_cur3,y_cur3,z_cur3-i,x_cur4,y_cur4,z_cur4-i);
  }
  if(backfull == 1){ // left up _ right down
    for( j =0; j <= range; j++){
   movebody(x_cur1,y_cur1,z_cur1-j,x_cur2,y_cur2,z_cur2-j,x_cur3,y_cur3,z_cur3+j,x_cur4,y_cur4,z_cur4+j,0,0);
   delay(18);
  }
  curent_xyz(x_cur1,y_cur1,z_cur1-j,x_cur2,y_cur2,z_cur2-j,x_cur3,y_cur3,z_cur3+j,x_cur4,y_cur4,z_cur4+j);
  }
}
void curent_xyz(double x,double y,double z,double x1,double y1,double z1,double x2,double y2,double z2,double x3,double y3,double z3){
  x_cur1 = x;
  y_cur1 = y;
  z_cur1 = z;
  x_cur2 = x1;
  y_cur2 = y1;
  z_cur2 = z1;
  x_cur3 = x2;
  y_cur3 = y2;
  z_cur3 = z2;
  x_cur4 = x3;
  y_cur4 = y3;
  z_cur4 = z3;
}
void movebody(double x0, double y0, double z0,double x1, double y1, double z1,double x2, double y2, double z2,double x3, double y3, double z3, double range_move, int speed){

  double y_new0 = y0 - range_move;
  double y_new1 = y1 - range_move;
  double y_new2 = y2 - range_move;
  double y_new3 = y3 - range_move;
  
  moveRF(1,x0,y_new0,z0,speed);
  moveRB(1,x1,y_new1,z1,speed);
  moveLF(1,x2,y_new2,z2,speed);
  moveLB(1,x3,y_new3,z3,speed);

}
void moveRF(int bodyTrue,double x, double y, double z, int speed){
  double a = alpha(x,y,z);
  double b = beta(x,y,z);
  double gama = gam(x,y);
  if(bodyTrue ==0 ){
  servo[0][0].write(40);
  servo[0][1].write(50);
  delay(speed);
  servo[0][2].write(gama);
  delay(speed);
  servo[0][1].write(b);
  delay(speed);
  servo[0][0].write(180-a);  
  delay(speed);
  }
  if(bodyTrue == 1){
  servo[0][2].write(gama);
  delay(speed);
  servo[0][1].write(b);
  delay(speed);
  servo[0][0].write(180-a);  
  delay(speed);
    
  }
}
 void moveRB(int bodyTrue,double x, double y, double z, int speed){
  double a = alpha(x,y,z);
  double b = beta(x,y,z);
  double gama = gam(x,y);
  if(bodyTrue == 0){
  servo[1][0].write(150);
  servo[1][1].write(120);
  delay(speed);
  servo[1][2].write(gama);
  delay(speed);
  servo[1][1].write(180-b);
  delay(speed);
  servo[1][0].write(a);   
  delay(speed);
  }
  if(bodyTrue == 1){
  servo[1][2].write(gama);
  delay(speed);
  servo[1][1].write(180-b);
  delay(speed);
  servo[1][0].write(a);   
  delay(speed);
  }
}
 void moveLF(int bodyTrue,double x, double y, double z, int speed){
  double a = alpha(x,y,z);
  double b = beta(x,y,z);
  double gama = gam(x,y);
  if(bodyTrue==0){
  servo[2][0].write(150);
  servo[2][1].write(130);
  delay(speed);
  servo[2][2].write(gama);
  delay(speed);
  servo[2][1].write(180-b);
  delay(speed);
  servo[2][0].write(a);   
  delay(speed);
  }
  if(bodyTrue ==1){
  servo[2][2].write(gama);
  delay(speed);
  servo[2][1].write(180-b);
  delay(speed);
  servo[2][0].write(a);   
  delay(speed);
  }
}
void moveLB(int bodyTrue,double x, double y, double z, int speed){
  double a = alpha(x,y,z);
  double b = beta(x,y,z);
  double gama = gam(x,y);
  
 if(bodyTrue ==0){
  servo[3][0].write(40);
  servo[3][1].write(50);
  delay(speed);
  servo[3][2].write(gama);
  delay(speed);
  servo[3][1].write(b);
  delay(speed);
  servo[3][0].write(180-a);  
  delay(speed);
 }
 if(bodyTrue ==1){
  servo[3][2].write(gama);
  delay(speed);
  servo[3][1].write(b);
  delay(speed);
  servo[3][0].write(180-a);  
  delay(speed);
 }
}
double gam(double x, double y){
  double gama;
  double gamaTemp = RadtoDo(atan(x/y));          // truc x la ngang, y la doc
  if(gamaTemp >0 ){
    gama = 180 - gamaTemp;
  }
  else {
    gama = abs(gamaTemp);
  }
  return gama;
}

double alpha(double x, double y, double z ){
  double L1 = sqrt(pow(x,2)+pow(y,2));
  double L = sqrt(pow((L1-Coxa),2)+pow(z,2));
  double a1 = RadtoDo(atan((L1-Coxa)/z));
  double cosa2 = (pow(Femur,2)+pow(L,2) -pow(Tibia,2))/(2*Femur*L);
  double a = a1+ RadtoDo(acos(cosa2));
  return a ;
}
double beta(double x, double y, double z ){
  double L1 = sqrt(pow(x,2)+pow(y,2));
  double L = sqrt(pow((L1-Coxa),2)+pow(z,2));
  double cosb = (pow(Tibia,2)+pow(Femur,2)-pow(L,2))/(2*Tibia*Femur);
  double b = RadtoDo(acos(cosb));
  return b;
}
float getDistance()
{
  long duration, distanceCm;
  // Phát 1 xung 10uS từ chân Trig 
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // Thời gian tín hiệu phản hồi lại chân Echo
  duration = pulseIn(ECHO_PIN, HIGH, TIME_OUT);
 
  // Tính khoảng cách 
  distanceCm = duration / 29.1 / 2;
  // trả lại giá trị tính được
  return distanceCm;
}
