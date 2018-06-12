// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <iDoom.h>

iDoom doom;

byte movie[][8] = {{0,0,0,0,0,0,0,0}};
String curr_price;
int price;
int prev_price;

int min_price;
int max_price;
int dots;

String prices[5] = {"1528315800000:4.0,","1528315800000:3.7,","1528315800000:4.1,","1528315800000:1.1,","1528315800000:1.3,"};

int colorVal = 255;

void setup() {
  Serial.begin(9600);

  min_price = 19;
  max_price = 37;

  doom.begin (2000);  // 72 ms ~~ 14 Hz
}

void loop() {
  
  //Here is where the price will be delivered
  curr_price = prices[random(0,5)];
  //Turn the string into a usable number
  price = stringToPrice2(stringToPrice(curr_price)); 

  if(price != prev_price)
  {   
    dots = calc_dots(min_price, max_price, price);
    
    //Set the screen characters
    setCharacter(4, (price / 10), dots);
    setCharacter(5, (price % 10), dots);
    
    doom.begin (2000);  // 72 ms ~~ 14 Hz
  }

  prev_price = price;

  doom.play (movie, sizeof movie / sizeof *movie); 
}

void setCharacter(int pos, int toDisplay, int dots)
{
  if(toDisplay == 0){
    movie[0][pos] = 252;
  }
  else if(toDisplay == 1){
    movie[0][pos] = 96;
  }
  else if(toDisplay == 2){
    movie[0][pos] = 218;
  }
  else if(toDisplay == 3){
    movie[0][pos] = 242;
  }
  else if(toDisplay == 4){
    movie[0][pos] = 102;
  }
  else if(toDisplay == 5){
    movie[0][pos] = 182;
  }
  else if(toDisplay == 6){
    movie[0][pos] = 190;
  }
  else if(toDisplay == 7){
    movie[0][pos] = 224;
  }
  else if(toDisplay == 8){
    movie[0][pos] = 254;
  }
  else if(toDisplay == 9){
    movie[0][pos] = 230;
  }

  if(pos == 4){movie[0][pos]++;}

  if(dots > 0)
  {
    Serial.print(dots);Serial.print(" ");Serial.println(price);
    
    if(dots < 9){
      movie[0][6] = 0;
      if(dots == 1)
        movie[0][7] = 1;
      else
        movie[0][7] = pow(2, dots);
    }
    else{
      movie[0][7] = 255;
      if(dots == 9)
        movie[0][6] = 1;
      else
        movie[0][6] = pow(2, (dots - 8));
    }
  }
}

int calc_dots(int minp, int maxp, int price)
{
  //Note min = 3 dots
  //Note max = 9 dots

  int dots;

  double slope = (maxp - minp)/5.0;
  

  if(price < minp)
  {
    for(int i = 1; i < 5; i++)
    {
      if(price > (minp - slope*i))
      {
        dots = 4 - i;
        break;
      }
      if(i == 4)
      {
        dots = 0;
        break;
      }
    }
  }
  else if(price > maxp)
  {
    for(int i = 1; i < 5; i++)
    {
      if(price < (maxp + slope*i))
      {
        dots = 8 + i;
        break;
      }
      if(i == 4)
      {
        dots = 12;
        break;
      }
    }
  }
  else
  {
    for(int i = 1; i < 6; i++)
    {
      if(price < (minp + slope*i))
      {
        dots = 3 + i;
        break;
      }
    }
  }

  return dots;
}

String stringToPrice(String s){
  int pos = 0;
  String toReturn;
  while(s.substring(pos, pos + 1) != ":"){
    pos++;  
  }
  pos++;
  toReturn = s.substring(pos, pos + 3);
  return toReturn;
}

int stringToPrice2(String s){
  int sum = 0;

  sum += (s.substring(0, 1).toInt())*10;
  sum += (s.substring(2, 3).toInt());

  return sum;
}

