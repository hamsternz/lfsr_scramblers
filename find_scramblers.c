/********************************************************************
 * find_scramblers.c : Find maximal LFSR shift registers with 1 tap
 *
 * (c) 2020 Mike Field <hamster@snap.net.nz>
 *
 *******************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

uint32_t state = 1;
uint8_t seen[64*1024*1024];

uint8_t doit(int len, int tap1) {
   uint8_t out = ((state>>(len-1)) ^ (state>>(len-tap1))) & 1;
   state = (state <<1) | out;
   state &= (1<<len)-1;
   return out;
}

int test(int len, int tap1) {
   int cycle=0;

   assert(1<<(len-3) <= sizeof(seen));
   memset(seen,0, 1<<(len-3));
   state = 1;
   for(int j = 0; (seen[state/8] & (1<<(state&7)))==0; ++j, ++cycle) {
      seen[state/8] |= 1<<(state&7);
      doit(len, tap1);
   }
   return (cycle == (1<<len)-1);
}

int main(int argc, char *argv[]) {
   for(int len = 3; len < 30; ++len) {
      for(int tap = 0; tap < len; ++tap) {
         if(test(len,tap)) { 
            printf("Len %i tap %i: GOOD\n", len, tap);
//         } else {
 //           printf("Len %i tap %i: bad\n", len, tap);
         }
      }
   }
}
