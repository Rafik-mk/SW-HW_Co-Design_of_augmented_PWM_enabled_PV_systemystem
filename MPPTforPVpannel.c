#include <30F4013.h>
#fuses NOWDT, NOPROTECT, NOPUT
#DEVICE ADC=10
#use delay (crystal=20MHz)

#include "flex_lcd.c"
#include <stdio.h>

void main() {
   int rapportCyclique;
   float tension=0, courant=0, puissance=0, puissanceAncien=0;
   float tensionAncien, batterie;
   setup_timer2(TMR_INTERNAL | TMR_DIV_BY_1, 100);
   setup_compare(4, COMPARE_PWM | COMPARE_TIMER2);
   // sortie sur broche OC1

   setup_adc(ADC_CLOCK_INTERNAL);
   setup_adc_ports(ALL_ANALOG);
   lcd_init();

   set_adc_channel(2);
   batterie=read_adc();
   batterie=batterie*57.6/1023;

   set_adc_channel(0);
   tension=read_adc();
   tension=tension*40/1023;

   rapportCyclique=1-(0.7*tension/batterie);

   while(TRUE) {
      printf(lcd_putc,"\f");
      delay_us(20);

      set_adc_channel(0);
      tension=read_adc();
      tension=tension*40/1023;

      set_adc_channel(1);
      courant=read_adc();
      courant=courant*10/1023;

      puissance=courant*tension;
      printf(lcd_putc,"Puissance= %f W ",puissance);
      delay_us(20);

      set_adc_channel(2);
      batterie=read_adc();
      batterie=batterie*57.6/1023;
      printf(lcd_putc,"Batterie= %f V",batterie*100/57.6);
	// 57.6V = 100% de batterie

      if(batterie==57.6) (rapportCyclique=0);
      else {
         if(puissance>puissanceAncien) {
            if (tension>tensionAncien) rapportCyclique--;
            else rapportCyclique++;
         }
         else {
            if (tension>tensionAncien) rapportCyclique++;
            else rapportCyclique--;
         }
      }

      if(puissance>97) puissance=97;
      if(puissance<3) puissance=3;

      puissanceAncien=puissance;
      tensionAncien=tension;

      set_pwm_duty(4, (rapportCyclique));
      delay_ms(100);
   }
}
