/********************************************************************
 * scramble.c : Investigate LFSR based scramblers
 *
 * (c) 2020 Mike Field <hamster@snap.net.nz>
 *
 *******************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>

uint32_t state_s = 0xAAAAAAAA;
uint32_t state_u = 0xFFFFFFF1;


static uint8_t scramble(int len, int tap, uint8_t d) {
   uint8_t out = ((state_s>>(len-1)) ^ (state_s>>(len-tap))) & 1;
   out ^= d;
   state_s = (state_s <<1) | out;
   state_s &= (1<<len)-1;
   return out;
}

static uint8_t unscramble(int len, int tap, uint8_t d) {
   uint8_t q = ((state_u>>(len-1)) ^ (state_u>>(len-tap))) & 1;
   uint8_t out;
   out = q ^ d;
   state_u = (state_u <<1) | d;
   state_u &= (1<<len)-1;
   return out;
}

int main(int argc, char *argv[]) {
   uint64_t data = 0xFFFFFFFFFFFE487FL;
   int w=0;
   char d_str[80];
   char s_str[80];
   char u_str[80];

   int length = 15;
   int tap = 2;

   for(int len = 3; len < 1000; ++len) {
      uint8_t d, s, u;
      d = data&1;
      s = scramble(length, tap, d);
      u = unscramble(length, tap, s);
      data = (data>>1) | (data<<63);

      d_str[w] = d ? '1' : '0';
      s_str[w] = s ? '1' : '0';
      u_str[w] = u ? '1' : '0';
      w++;
      if(w == 70) {
	 d_str[w] = 0;
	 s_str[w] = 0;
	 u_str[w] = 0;
         printf("Data        : %s\n",d_str); 
         printf("Scrambled   : %s\n",s_str); 
         printf("Unscrambled : %s\n",u_str); 
	 printf("\n");
	 w = 0;
      }
   }
   if(w != 0) {
      d_str[w] = 0;
      s_str[w] = 0;
      u_str[w] = 0;
      printf("Data        : %s\n",d_str); 
      printf("Scrambled   : %s\n",s_str); 
      printf("Unscrambled : %s\n",u_str); 
      printf("\n");
      w = 0;
   }
}
