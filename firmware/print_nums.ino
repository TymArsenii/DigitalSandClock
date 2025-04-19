static const uint8_t font3x5[][3] PROGMEM = 
{
  { //0
    0b11111,
    0b10001,
    0b11111,
  },
  { //1
    0b11111,
    0b01000,
    0b00000,
  },
  { 
    //2
    0b11101,
    0b10101,
    0b10111,
  },
  { //3
    0b11111,
    0b10101,
    0b10101,
  },
  { //4
    0b11111,
    0b00100,
    0b11100,
  },
  { //5
    0b10111,
    0b10101,
    0b11101,
  },
  { //6
    0b10111,
    0b10101,
    0b11111,
  },
  { //7
    0b11111,
    0b10000,
    0b10000,
  },
  { //8
    0b11111,
    0b10101,
    0b11111,
  },
  { //9
    0b11111,
    0b10101,
    0b11101,
  },
};

static const uint8_t font3x5_rotated[][3] PROGMEM = 
{
  { //0 rotated
    0b11111,
    0b10001,
    0b11111,
  },
  { //1 rotated
    0b00000,
    0b00010,
    0b11111,
  },
  { //2 rotated
    0b11101,
    0b10101,
    0b10111,
  },
  { //3 rotated
    0b10101,
    0b10101,
    0b11111,
  },
  { //4 rotated
    0b00111,
    0b00100,
    0b11111,
  },
  { //5 rotated
    0b10111,
    0b10101,
    0b11101,
  },
  { //6 rotated
    0b11111,
    0b10101,
    0b11101,
  },
  { //7 rotated
    0b00001,
    0b00001,
    0b11111,
  },
  { //8 rotated
    0b11111,
    0b10101,
    0b11111,
  },
  { //9 rotated
    0b10111,
    0b10101,
    0b11111,
  },
};



void print_num(uint8_t num, uint8_t matrix_id) // matrix_id 1-top; 2-bottom 
{
  if(view_log) Serial.print("!   ");
  uint8_t first_digit=255;
  uint8_t second_digit=255;
  if(num>=10 && num<=99)
  {
    first_digit=num/10;
    second_digit=num%10;
  }
  else if(num<=9 && num>0)
  {
    first_digit=0;
    second_digit=num;
  }
  else if(num==0) 
  {
    first_digit=0;
    second_digit=0;
  }
  
  /*     debug
  if(view_log) Serial.print(num);
  if(view_log) Serial.print(" ; ");
  if(view_log) Serial.print(first_digit);
  if(view_log) Serial.print(" : ");
  if(view_log) Serial.println(second_digit);
  */

  if(first_digit!=255 && second_digit!=255)
  {
    if(angle>=0 && angle<=180)
    {
      for (uint8_t x=1; x<=3; x++) 
      {
        uint8_t col=pgm_read_byte(&font3x5[first_digit][x-1]);
        for (uint8_t y=1; y<=5; y++) 
        {
          if(bitRead(col, 5-y))
          {
            uint8_t _y=matrix_id==2 ? y+8 : y;
            set_dot(_y, x+4, 1);
          }
        }
      }
      for (uint8_t x=1; x<=3; x++) 
      {
        uint8_t col=pgm_read_byte(&font3x5[second_digit][x-1]);
        for (uint8_t y=1; y<=5; y++) 
        {
          if(bitRead(col, 5-y))
          {
            uint8_t _y=matrix_id==2 ? y+8 : y;
            set_dot(_y, x, 1);
          }
        }
      }
    }
    else
    {
      //if(matrix_id==1) matrix_id=2;
      //else if(matrix_id==2) matrix_id=1;

      first_digit=first_digit+second_digit;
      second_digit=first_digit-second_digit;
      first_digit=first_digit-second_digit; 
      for (uint8_t x=1; x<=3; x++) 
      {
        uint8_t col=pgm_read_byte(&font3x5_rotated[first_digit][x-1]);
        for (uint8_t y=1; y<=5; y++) 
        {
          if(bitRead(col, 5-y))
          {
            uint8_t _y=matrix_id==2 ? y+8 : y;
            set_dot(_y, x+3, 1);
          }
        }
      }
      for (uint8_t x=1; x<=3; x++) 
      {
        uint8_t col=pgm_read_byte(&font3x5_rotated[second_digit][x-1]);
        for (uint8_t y=1; y<=5; y++) 
        {
          if(bitRead(col, 5-y))
          {
            uint8_t _y=matrix_id==2 ? y+8 : y;
            set_dot(_y, x-1, 1);
          }
        }
      }
    }

    //return true;
  }
  //else return false;
}