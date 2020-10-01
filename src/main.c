#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include <time.h>

#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "GUI_BMPfile.h"
#include "EPD_4in2bc.h"

void  Handler(int signo) {
  //System Exit
  printf("\r\nHandler:exit\r\n");
  DEV_Module_Exit();

  exit(0);
}

int main(void) {
  // Exception handling:ctrl + c
  signal(SIGINT, Handler);

 if(DEV_Module_Init() != 0){
   return -1;
 }
 puts("dev module init");
 struct timespec start={0,0}, finish={0,0};
 clock_gettime(CLOCK_REALTIME,&start);
 EPD_4IN2BC_Init();
 EPD_4IN2BC_Clear();
 clock_gettime(CLOCK_REALTIME,&finish);
 printf("%ld S\r\n",finish.tv_sec-start.tv_sec);
 puts("paper init");

  UBYTE *BlackImage, *RYImage;
  UWORD Imagesize = (EPD_4IN2BC_WIDTH / 8) * EPD_4IN2BC_HEIGHT;
  if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for black memory...\r\n");
    return -1;
  }
  if((RYImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    printf("Failed to apply for red memory...\r\n");
    return -1;
  }
  Paint_NewImage(BlackImage, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, 180, WHITE);
  Paint_NewImage(RYImage, EPD_4IN2BC_WIDTH, EPD_4IN2BC_HEIGHT, 180, WHITE);
  Paint_SelectImage(BlackImage);
  GUI_ReadBmp("./in.bmp", 0, 0);
  Paint_SelectImage(RYImage);
  GUI_ReadBmp("./in-red.bmp", 0, 0);
  EPD_4IN2BC_Display(BlackImage, RYImage);
  DEV_Delay_ms(2000);

  // EPD_4IN2BC_Sleep();
  free(BlackImage);
  free(RYImage);
  BlackImage = RYImage = NULL;

  return 0;
}
