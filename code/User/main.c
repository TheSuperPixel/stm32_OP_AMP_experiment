#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "led.h"
#include "beep.h"
#include "i2c_eeprom.h"
#include "stdio.h"
#include "math.h"
uint16_t AD0, AD1, AD2;
float k1=(9.7+9.4)/3195.0;
float k2=(9.7+9.7)/3400.0;
float k3=(9.7+9.7)/3500.0;
float b1=-9.40;
float b2=-9.65;
float b3=-9.70;
float v1;
float v2;
float v3;
int v1_y;
int v2_y;
int v3_y;
int v1_y_all[128];
int v2_y_all[128];
int v3_y_all[128];
int v1_show_en=1;
int v2_show_en=0;
int v3_show_en=0;
int vn_show_en_point=1;
char text[30];
int key_num;
int page=0;
int page0_point=1;
int setting_x=1;
int setting_y=1;
int edit_mode=0;
unsigned char k1_temp[4];
unsigned char k2_temp[4];
unsigned char k3_temp[4];
unsigned char b1_temp[4];
unsigned char b2_temp[4];
unsigned char b3_temp[4];
float temp;
float test_v;
void save(){
	LED_change(1);
	k1_temp[0]=((unsigned char *)&k1)[0],k1_temp[1]=((unsigned char *)&k1)[1],k1_temp[2]=((unsigned char *)&k1)[2],k1_temp[3]=((unsigned char *)&k1)[3];
	k2_temp[0]=((unsigned char *)&k2)[0],k2_temp[1]=((unsigned char *)&k2)[1],k2_temp[2]=((unsigned char *)&k2)[2],k2_temp[3]=((unsigned char *)&k2)[3];
	k3_temp[0]=((unsigned char *)&k3)[0],k3_temp[1]=((unsigned char *)&k3)[1],k3_temp[2]=((unsigned char *)&k3)[2],k3_temp[3]=((unsigned char *)&k3)[3];
	b1_temp[0]=((unsigned char *)&b1)[0],b1_temp[1]=((unsigned char *)&b1)[1],b1_temp[2]=((unsigned char *)&b1)[2],b1_temp[3]=((unsigned char *)&b1)[3];
	b2_temp[0]=((unsigned char *)&b2)[0],b2_temp[1]=((unsigned char *)&b2)[1],b2_temp[2]=((unsigned char *)&b2)[2],b2_temp[3]=((unsigned char *)&b2)[3];
	b3_temp[0]=((unsigned char *)&b3)[0],b3_temp[1]=((unsigned char *)&b3)[1],b3_temp[2]=((unsigned char *)&b3)[2],b3_temp[3]=((unsigned char *)&b3)[3];
	int i;
	for(i=0;i<=3;i++){
		eeprom_white(i,k1_temp[i]);
	}
	for(i=4;i<=7;i++){
		eeprom_white(i,k2_temp[i-4]);
	}
	for(i=8;i<=11;i++){
		eeprom_white(i,k3_temp[i-8]);
	}
	for(i=12;i<=15;i++){
		eeprom_white(i,b1_temp[i-12]);
	}
	for(i=16;i<=19;i++){
		eeprom_white(i,b2_temp[i-16]);
	}
	for(i=20;i<=23;i++){
		eeprom_white(i,b3_temp[i-20]);
	}
	LED_change(0);
}
void read(){
	LED_change(2);
	int i;
	for(i=0;i<=3;i++){
		k1_temp[i]=eeprom_read(i);
	}
	for(i=4;i<=7;i++){
		k2_temp[i-4]=eeprom_read(i);
	}
	for(i=8;i<=11;i++){
		k3_temp[i-8]=eeprom_read(i);
	}
	for(i=12;i<=15;i++){
		b1_temp[i-12]=eeprom_read(i);
	}
	for(i=16;i<=19;i++){
		b2_temp[i-16]=eeprom_read(i);
	}
	for(i=20;i<=23;i++){
		b3_temp[i-20]=eeprom_read(i);
	}
	((unsigned char *)&k1)[0]=k1_temp[0],((unsigned char *)&k1)[1]=k1_temp[1],((unsigned char *)&k1)[2]=k1_temp[2],((unsigned char *)&k1)[3]=k1_temp[3];
	((unsigned char *)&k2)[0]=k2_temp[0],((unsigned char *)&k2)[1]=k2_temp[1],((unsigned char *)&k2)[2]=k2_temp[2],((unsigned char *)&k2)[3]=k2_temp[3];
	((unsigned char *)&k3)[0]=k3_temp[0],((unsigned char *)&k3)[1]=k3_temp[1],((unsigned char *)&k3)[2]=k3_temp[2],((unsigned char *)&k3)[3]=k3_temp[3];
	((unsigned char *)&b1)[0]=b1_temp[0],((unsigned char *)&b1)[1]=b1_temp[1],((unsigned char *)&b1)[2]=b1_temp[2],((unsigned char *)&b1)[3]=b1_temp[3];
	((unsigned char *)&b2)[0]=b2_temp[0],((unsigned char *)&b2)[1]=b2_temp[1],((unsigned char *)&b2)[2]=b2_temp[2],((unsigned char *)&b2)[3]=b2_temp[3];
	((unsigned char *)&b3)[0]=b3_temp[0],((unsigned char *)&b3)[1]=b3_temp[1],((unsigned char *)&b3)[2]=b3_temp[2],((unsigned char *)&b3)[3]=b3_temp[3];
	LED_change(0);
}
int main(void)
{
	OLED_Init();
	AD_Init();
	Key_Init();
	LED_Init();
	beep_Init();
	I2CInit();
//	save();//»Ö¸´³ö³§ÉèÖÃ
	read();
	beep_change(1);
	Delay_ms(100);
	beep_change(0);
	Delay_ms(100);
	int i;
	for(i=0;i<127;i++){
		v1_y_all[i]=32;
	}
	for(i=0;i<127;i++){
		v2_y_all[i]=32;
	}
	for(i=0;i<127;i++){
		v3_y_all[i]=32;
	}
	while (1)
	{
		//key
		key_num=Key_GetNum();
		if(key_num==1){//left
			if(page==1||page==2){
				page=0;
			}
			if(page==4){
				if(setting_y==4){
					if(setting_x==2){
						setting_x=1;
					}
				}else{
					setting_x--;
					if(setting_x<1){
						setting_x=1;
					}
				}
			}
			if(page==3){
				vn_show_en_point--;
				if(vn_show_en_point<1){
					vn_show_en_point=1;
				}
			}
		}else if(key_num==2){//right
			if(page==4){
				if(setting_y==4){
					if(setting_x==1){
						setting_x=2;
					}
				}else{
					setting_x++;
					if(setting_x>6){
						setting_x=6;
					}
				}
			}
			if(page==3){
				vn_show_en_point++;
				if(vn_show_en_point>3){
					vn_show_en_point=3;
				}
			}
		}else if(key_num==3){//up
			if(page==0){
				if(page0_point==2){
					page0_point=1;
				}
			}else if(page==3){
				page=2;
			}else if(page==2){
				page=1;
			}else if(page==4){
				if(edit_mode==0){
					setting_y--;
					if(setting_y<1){
						setting_y=1;
					}
				}else if(edit_mode==1){
					if(setting_x==1&&setting_y==1){
						k1+=1;
					}
					if(setting_x==2&&setting_y==1){
						k1+=0.1;
					}
					if(setting_x==3&&setting_y==1){
						k1+=0.01;
					}
					if(k1>9.99){
						k1=9.99;
					}
					
					if(setting_x==4&&setting_y==1){
						b1+=1;
					}
					if(setting_x==5&&setting_y==1){
						b1+=0.1;
					}
					if(setting_x==6&&setting_y==1){
						b1+=0.01;
					}
					if(b1>-0.01){
						b1=-0.01;
					}
					
					if(setting_x==1&&setting_y==2){
						k2+=1;
					}
					if(setting_x==2&&setting_y==2){
						k2+=0.1;
					}
					if(setting_x==3&&setting_y==2){
						k2+=0.01;
					}
					if(k2>9.99){
						k2=9.99;
					}
					
					if(setting_x==4&&setting_y==2){
						b2+=1;
					}
					if(setting_x==5&&setting_y==2){
						b2+=0.1;
					}
					if(setting_x==6&&setting_y==2){
						b2+=0.01;
					}
					if(b2>-0.01){
						b2=-0.01;
					}
					
					if(setting_x==1&&setting_y==3){
						k3+=1;
					}
					if(setting_x==2&&setting_y==3){
						k3+=0.1;
					}
					if(setting_x==3&&setting_y==3){
						k3+=0.01;
					}
					if(k3>9.99){
						k3=9.99;
					}
					
					if(setting_x==4&&setting_y==3){
						b3+=1;
					}
					if(setting_x==5&&setting_y==3){
						b3+=0.1;
					}
					if(setting_x==6&&setting_y==3){
						b3+=0.01;
					}
					if(b3>-0.01){
						b3=-0.01;
					}
				}
			}
		}else if(key_num==4){//down
			if(page==0){
				if(page0_point==1){
					page0_point=2;
				}
			}else if(page==1){
				page=2;
			}else if(page==2){
				page=3;
			}else if(page==4){
				if(edit_mode==0){
					if(setting_y==3){
						setting_y++;
						setting_x=1;
					}else{
						setting_y++;
					}
					if(setting_y>4){
						setting_y=4;
					}
				}else if(edit_mode==1){
					if(setting_x==1&&setting_y==1){
						k1-=1;
					}
					if(setting_x==2&&setting_y==1){
						k1-=0.1;
					}
					if(setting_x==3&&setting_y==1){
						k1-=0.01;
					}
					if(k1<0.01){
						k1=0.01;
					}
					
					if(setting_x==4&&setting_y==1){
						b1-=1;
					}
					if(setting_x==5&&setting_y==1){
						b1-=0.1;
					}
					if(setting_x==6&&setting_y==1){
						b1-=0.01;
					}
					if(b1<-9.99){
						b1=-9.99;
					}
					
					if(setting_x==1&&setting_y==2){
						k2-=1;
					}
					if(setting_x==2&&setting_y==2){
						k2-=0.1;
					}
					if(setting_x==3&&setting_y==2){
						k2-=0.01;
					}
					if(k2<0.01){
						k2=0.01;
					}
					
					if(setting_x==4&&setting_y==2){
						b2-=1;
					}
					if(setting_x==5&&setting_y==2){
						b2-=0.1;
					}
					if(setting_x==6&&setting_y==2){
						b2-=0.01;
					}
					if(b2<-9.99){
						b2=-9.99;
					}
					
					if(setting_x==1&&setting_y==3){
						k3-=1;
					}
					if(setting_x==2&&setting_y==3){
						k3-=0.1;
					}
					if(setting_x==3&&setting_y==3){
						k3-=0.01;
					}
					if(k3<0.01){
						k3=0.01;
					}
					
					if(setting_x==4&&setting_y==3){
						b3-=1;
					}
					if(setting_x==5&&setting_y==3){
						b3-=0.1;
					}
					if(setting_x==6&&setting_y==3){
						b3-=0.01;
					}
					if(b3<-9.99){
						b3=-9.99;
					}
				}
			}
		}else if(key_num==5){//push
			beep_change(1);
			Delay_ms(100);
			beep_change(0);
			Delay_ms(100);
			if(page==0){
				if(page0_point==1){
					page=1;
				}else if(page0_point==2){
					page=4;
				}
			}
			else if(page==4){
				if(setting_y==4){
					if(setting_x==1){
						save();
						page=0;;
					}else if(setting_x==2){
						page=0;;
					}
					OLED_Clear();
				}else{
					if(edit_mode==0){
						edit_mode=1;
					}else if(edit_mode==1){
						edit_mode=0;
					}
				}
			}else if(page==3){
				if(vn_show_en_point==1){
					if(v1_show_en==1){
						v1_show_en=0;
					}else if(v1_show_en==0){
						v1_show_en=1;
					}
				}
				if(vn_show_en_point==2){
					if(v2_show_en==1){
						v2_show_en=0;
					}else if(v2_show_en==0){
						v2_show_en=1;
					}
				}
				if(vn_show_en_point==3){
					if(v3_show_en==1){
						v3_show_en=0;
					}else if(v3_show_en==0){
						v3_show_en=1;
					}
				}
			}
		}
		
		//adc
		AD0 = AD_GetValue(ADC_Channel_0);
		AD1 = AD_GetValue(ADC_Channel_1);
		AD2 = AD_GetValue(ADC_Channel_2);
		v1=k1*AD0+b1;
		v2=k2*AD1+b2;
		v3=k3*AD2+b3;
		
		OLED_Clear();
		if(page==0){
			LED_change(0);
			OLED_ShowString(0, 0*16, "     Menu     ",OLED_8X16);
			OLED_ShowString(0, 1*16, "  start      ",OLED_8X16);
			OLED_ShowString(0, 2*16, "  setting      ",OLED_8X16);
			if(page0_point==1){
				OLED_ShowString(0, 1*16, "*",OLED_8X16);
				OLED_ShowString(0, 2*16, " ",OLED_8X16);
			}
			if(page0_point==2){
				OLED_ShowString(0, 1*16, " ",OLED_8X16);
				OLED_ShowString(0, 2*16, "*",OLED_8X16);
			}
		}
		if(page==1){
			LED_change(4);
			OLED_ShowString(0, 0*16, "   raw data",OLED_8X16);
			OLED_ShowString(0, 1*16, "IN1:",OLED_8X16);
			OLED_ShowString(0, 2*16, "IN2:",OLED_8X16);
			OLED_ShowString(0, 3*16, "OUT:",OLED_8X16);
			OLED_ShowNum(4*8, 1*16, AD0, 4,OLED_8X16);
			OLED_ShowNum(4*8, 2*16, AD1, 4,OLED_8X16);
			OLED_ShowNum(4*8, 3*16, AD2, 4,OLED_8X16);
			OLED_ShowString(8*8,1*16, "      ",OLED_8X16);
			OLED_ShowString(8*8,2*16, "      ",OLED_8X16);
			OLED_ShowString(8*8,3*16, "      ",OLED_8X16);
		}else if(page==2){
			LED_change(4);
			OLED_ShowString(0, 0*16, "     data",OLED_8X16);
			sprintf(text,"IN1_U;%.2f",v1);
			OLED_ShowString(0,1*16,(char*)text,OLED_8X16);
			sprintf(text,"IN2_U;%.2f",v2);
			OLED_ShowString(0,2*16,(char*)text,OLED_8X16);
			sprintf(text,"OUT_U;%.2f",v3);
			OLED_ShowString(0,3*16,(char*)text,OLED_8X16);
		}else if(page==3){
			
			int i;
			for(i=0;i<127;i++){
				v1_y_all[i]=v1_y_all[i+1];
			}
			temp=64-(v1+10)*(64/20.0);
			v1_y=(int)temp;
			v1_y_all[127]=v1_y;
			
			for(i=0;i<127;i++){
				v2_y_all[i]=v2_y_all[i+1];
			}
			temp=64-(v2+10)*(64/20.0);
			v2_y=(int)temp;
			v2_y_all[127]=v2_y;

			for(i=0;i<127;i++){
				v3_y_all[i]=v3_y_all[i+1];
			}
			temp=64-(v3+10)*(64/20.0);
			v3_y=(int)temp;
			v3_y_all[127]=v3_y;
			
			if(v1_show_en==1){
				for(i=0;i<128;i++){
				OLED_DrawPoint(i,v1_y_all[i]);
				}
			}
			if(v2_show_en==1){
				for(i=0;i<128;i++){
				OLED_DrawPoint(i,v2_y_all[i]);
				}
			}
			if(v3_show_en==1){
				for(i=0;i<128;i++){
				OLED_DrawPoint(i,v3_y_all[i]);
				}
			}
			sprintf(text,"v1:%d v2:%d v3:%d",v1_show_en,v2_show_en,v3_show_en);
			OLED_ShowString(0,0,(char*)text,OLED_6X8);
			if(vn_show_en_point==1){
				OLED_ReverseArea(3*6,0,6,8);
			}
			if(vn_show_en_point==2){
				OLED_ReverseArea(8*6,0,6,8);
			}
			if(vn_show_en_point==3){
				OLED_ReverseArea(13*6,0,6,8);
			}
			
			OLED_DrawLine(0, 32, 128, 32);
		}else if(page==4){
			sprintf(text,"k1:%.2f b1:%.2f",k1,b1);
			OLED_ShowString(0,0*16,(char*)text,OLED_8X16);
			sprintf(text,"k2:%.2f b2:%.2f",k2,b2);
			OLED_ShowString(0,1*16,(char*)text,OLED_8X16);
			sprintf(text,"k3:%.2f b3:%.2f",k3,b3);
			OLED_ShowString(0,2*16,(char*)text,OLED_8X16);
			sprintf(text,"save");
			OLED_ShowString(0,3*16,(char*)text,OLED_8X16);
			sprintf(text,"back");
			OLED_ShowString(5*8,3*16,(char*)text,OLED_8X16);
			if(edit_mode==0){
				sprintf(text,"select");
				OLED_ShowString(10*8,3*16,(char*)text,OLED_8X16);
			}else if(edit_mode==1){
				sprintf(text,"  edit");
				OLED_ShowString(10*8,3*16,(char*)text,OLED_8X16);
			}
			if(setting_y<4){
				int reverse_x,reverse_y;
				if(setting_x==1) reverse_x=3*8;
				if(setting_x==2) reverse_x=5*8;
				if(setting_x==3) reverse_x=6*8;
				if(setting_x==4) reverse_x=12*8;
				if(setting_x==5) reverse_x=14*8;
				if(setting_x==6) reverse_x=15*8;
				if(setting_y==1) reverse_y=0*16;
				if(setting_y==2) reverse_y=1*16;
				if(setting_y==3) reverse_y=2*16;
				OLED_ReverseArea(reverse_x,reverse_y,8,16);
			}else{
				if(setting_x==1){
					OLED_ReverseArea(0,3*16,8*4,16);
				}else if(setting_x==2){
					OLED_ReverseArea(5*8,3*16,8*4,16);
				}
				
			}
		}
		
		OLED_Update();
		Delay_ms(100);
	}
}
