
#include "U8glib.h"

//U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);
U8GLIB_SH1106_128X64_2X u8g(U8G_I2C_OPT_NONE); // I think the 2X option uses double the memory but should be faster

uint8_t draw_state = 0;

int cashPence = -5000; 
char* cashString = "0000.00"; 
int position[] = {
  0,0};

void setup(void) {



  // flip screen, if required
  u8g.setRot180();

  // if font never changes then you can stick it here in setup.


  pinMode(13, OUTPUT);           
  digitalWrite(13, HIGH);  
}

void loop(void) {

  updateScreen(); 

  cashPence+=50;
  updateCashString(); 

}


void draw(void) {

  u8g.drawStr( position[0], position[1], cashString); // only currently accommodates for 3 or 4 digits
}


void updateScreen() { 


  // Nice fonts what I like : 
  //u8g.setFont(u8g_font_fub25); // basically, helvetica bold
  //u8g.setFont(u8g_font_helvB24);
  //u8g.setFont(u8g_font_profont29);
  //u8g.setFont(u8g_font_profont29);
  //u8g.setFont(u8g_font_tpssb);

  int textwidth; 
  int textheight = 35; 

  u8g.setFont(u8g_font_fub35n);

  textwidth = u8g.getStrWidth(cashString);
  if(textwidth>128) { 
    u8g.setFont(u8g_font_fub30n);
    textwidth = u8g.getStrWidth(cashString);
    textheight = 30; 

  }
  if(textwidth>128) { 
    u8g.setFont(u8g_font_fub25n);
    textwidth = u8g.getStrWidth(cashString);
    textheight = 25; 

  }
  if(textwidth>128) { 
    u8g.setFont(u8g_font_fub20n);
    textwidth = u8g.getStrWidth(cashString);
    textheight = 20; 

  }
  u8g.setFontPosTop();

  position[0] = (128-textwidth)/2 +  1;
  position[1] = (64 - 35)/2;  

  // picture loop  
  u8g.firstPage();  
  do {
    draw();
  } 
  while( u8g.nextPage() );

}
void updateCashString() { 

  if((cashPence>-100) && (cashPence<0)) sprintf(cashString, "-0.%02d", abs(cashPence%100) ); // add a minus sign if necessary
  else sprintf(cashString, "%01d.%02d", (cashPence/100), abs(cashPence%100) ); 


}




