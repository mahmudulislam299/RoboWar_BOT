/* Mahmudul Islam
 * EEE,Bangladesh University of Engineering and Technology (BUET)
 * Email: mahmudulislam299@gmail.com
 */

#define binA 4///back right
#define binB 5///back right
#define binC 6///back left
#define binD 7///back left
#define bena 8
#define benb 9

#define finA 14///right
#define finB 15///right
#define finC 16///left
#define finD 17///left
#define fena 2
#define fenb 3

int ch1 = 10;// channel 1 to 8//left right
int ch2 = 11; /// channel to 9//front back
int v1, v2, s;

char q;

//these values are got from calibrating RC remote
#define fmax 17225
#define fmin 16800
#define bmax 16700
#define bmin 16245
#define lmax 17250
#define lmin 16900
#define rmax 16700
#define rmin 16320

#define h 255
#define l 100


void setup() {
    void  fmtr_strt();
    void  bmtr_strt();
    pinMode(ch1, INPUT);
    pinMode(ch2, INPUT);
    Serial.begin(9600);
}

void loop() {
  rcfun();
  drive_car(q);
    }

    
void rcfun() { 
  v1 = pulseIn(ch1,INPUT);
  Serial.print("val1=");
  Serial.println(v1);
   v2 = pulseIn(ch2,INPUT);
   Serial.print("val2=");
  Serial.println(v2);
  delay(10);
  Serial.print("\n");
  

  //********************************************************************//
  if( v1>=rmax && v1<=lmin && v2>= bmax && v2 <= fmin) 
    {q= 'S'; /*Serial.println(q);*/}
    
  else if(v1>rmax && v1<lmin && v2>fmin) 
    {q= 'F'; s = map(v2,fmin,fmax,50,255); /*Serial.println(s); Serial.println(q);*/}
    
  else if(v1>rmax && v1<lmin && v2<bmax) 
    {q= 'B'; s = map(v2,bmax,bmin,50,255);/* Serial.println(s); Serial.println(q);*/}
    
  else if(v2> bmax && v2 <fmin && v1<rmax) 
    {q= 'R';s = map(v1,rmin,rmax,255,50); /*Serial.println(s); Serial.println(q);*/}
    
  else if( v2> bmax && v2 <fmin && v1>lmin) 
    {q= 'L'; s = map(v1,lmin,lmax,50,255); /*Serial.println(s); Serial.println(q);*/}

  //********************************************************************//

   else if( v2>= fmin && v1>=lmin) 
    {q= 'G'; /*s = map(v1,lmin,lmax,0,255); /*Serial.println(s); Serial.println(q);*/}
    
    else if( v2>=fmin && v1<=rmax) 
    {q= 'I'; /*s = map(v1,lmin,lmax,0,255); /*Serial.println(s); Serial.println(q);*/}

    else if( v2<=bmax && v1>=lmin) 
    {q= 'H'; /*s = map(v1,lmin,lmax,0,255); /*Serial.println(s); Serial.println(q);*/}

   else if( v2<=bmax && v2>100 && v1<=rmax && v1>100) 
   {q= 'J'; /*s = map(v1,lmin,lmax,0,255); /*Serial.println(s); Serial.println(q);*/}
  
  else
    {q='S';}
}

void fmtr_strt()
{
  pinMode(finA,OUTPUT);
  pinMode(finB,OUTPUT);
  pinMode(finC,OUTPUT);
  pinMode(finD,OUTPUT);
  pinMode(fena,OUTPUT);
  pinMode(fenb,OUTPUT);
  
  digitalWrite(finA,HIGH);
  digitalWrite(finB,HIGH);
  digitalWrite(finC,HIGH);
  digitalWrite(finD,HIGH);
}

void bmtr_strt()
{
  pinMode(binA,OUTPUT);
  pinMode(binB,OUTPUT);
  pinMode(binC,OUTPUT);
  pinMode(binD,OUTPUT);
  pinMode(bena,OUTPUT);
  pinMode(benb,OUTPUT);
  
  digitalWrite(binA,HIGH);
  digitalWrite(binB,HIGH);
  digitalWrite(binC,HIGH);
  digitalWrite(binD,HIGH);
}

void drive_car(char p){
  if(p=='F') //forward
  {
    f_speed(s, s);
    b_speed(s, s);
  }

  else if(p=='B') // backword
  {
    f_speed(-s, -s);
    b_speed(-s, -s);
  }

  if(p=='R') //right
  {
   f_speed(s, -s);
   b_speed(s, -s);
  }

  if(p=='L') // left
  {
   f_speed(-s, s);
   b_speed(-s, s);
  }

  if(p=='G') // forward left
  {
    f_speed(l, h);
    b_speed(l, h);
  }

  if(p=='I') // forward right
  {
    f_speed(h, 60);
    b_speed(h, 60);
  }

  if(p=='H') // backword left
  {
    f_speed(-l, -h);
    b_speed(-l, -h);
  }

  if(p=='J') // backword right
  {
    f_speed(-h, -l);
    b_speed(-h, -l);
  }

  if(p=='S') //stop
  {
    f_speed(0,0);
    b_speed(0,0);
  }
}



void f_speed(int flm, int frm)       
{
 if(flm==0)                 
  {
    digitalWrite(finC,HIGH);
    digitalWrite(finD,HIGH);
  }
  if(flm>0)
  {
    digitalWrite(finC,HIGH);        
    digitalWrite(finD,LOW);
  }
  else if(flm<0)
  {
    digitalWrite(finC,LOW);          
    digitalWrite(finD,HIGH);
  }


  if(frm==0)
  {
    digitalWrite(finA,HIGH);
    digitalWrite(finB,HIGH);
  }
  if(frm>0)
  {
    digitalWrite(finA,HIGH);
    digitalWrite(finB,LOW);
  }
  else if(frm<0)
  {
    digitalWrite(finA,LOW);
    digitalWrite(finB,HIGH);
  }
  if(flm>254) flm=254;                
  if(flm<-254) flm=-254;
  if(frm>254) frm=254;
  if(frm<-254) frm=-254;
  
  analogWrite(fena,abs(frm));         
  analogWrite(fenb,abs(flm));         
  
}

void b_speed(int blm, int brm)       
{
 if(blm==0)                 
  {
    digitalWrite(binC,HIGH);
    digitalWrite(binD,HIGH);
  }
  else if(blm>0)
  {
    digitalWrite(binC,HIGH);        
    digitalWrite(binD,LOW);
  }
  else if(blm<0)
  {
    digitalWrite(binC,LOW);          
    digitalWrite(binD,HIGH);
  }


  if(brm==0)
  {
    digitalWrite(binA,HIGH);
    digitalWrite(binB,HIGH);
  }
  else if(brm>0)
  {
    digitalWrite(binA,HIGH);
    digitalWrite(binB,LOW);
  }
  else if(brm<0)
  {
    digitalWrite(binA,LOW);
    digitalWrite(binB,HIGH);
  }
  if(blm>254) blm=254;                
  if(blm<-254) blm=-254;
  if(brm>254) brm=254;
  if(brm<-254) brm=-254;
  
  analogWrite(bena,abs(brm));         
  analogWrite(benb,abs(blm));         
  
}
