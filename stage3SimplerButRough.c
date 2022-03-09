
#include <avr/io.h>
#include <util/delay.h>  //delay library

#define F_CPU 16000000UL // 16 MHz clock speed
#define secUp (PINC & (1<<PC5))>>PC5
#define secDown (PINC & (1<<PC4))>>PC4
#define velUp (PINC & (1<<PC3))>>PC3
#define velDown (PINC & (1<<PC2))>>PC2

int seqID = 0;
int velID = 0;
int velocities[] = {800,750,650,600,320,160,80,40,20,10};

void getVel(){
	if (velID < 0) velID = 0;
	if (velID > 9) velID = 9;
	if (velUp) {_delay_ms(250); velID++;}
	if (velDown) {_delay_ms(250); velID--;}
}
void getSeq(){
	if (seqID < 0) seqID = 0;
	if (seqID > 20) seqID = 20;
	if (secUp) {_delay_ms(250); seqID++;}
	if (secDown) {_delay_ms(250); seqID--;}
}
void delayms(int n){
	for (int i = 0; i < n; i++)
	{
		_delay_ms(1);
	}
}

void seq1(){
	PORTD = 0xF9 & 0xFF;
	PORTB = 0xF9 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x357 & 0xFF;
	PORTB = 0x357 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x13B & 0xFF;
	PORTB = 0x13B >> 8;
	delayms(velocities[velID]);
	PORTD = 0x19B & 0xFF;
	PORTB = 0x19B >> 8;
	delayms(velocities[velID]);
	PORTD = 0x238 & 0xFF;
	PORTB = 0x238 >> 8;
	delayms(velocities[velID]);
	PORTD = 0xF8 & 0xFF;
	PORTB = 0xF8 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x3D1 & 0xFF;
	PORTB = 0x3D1 >> 8;
	delayms(velocities[velID]);
	PORTD = 0xA6 & 0xFF;
	PORTB = 0xA6 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x184 & 0xFF;
	PORTB = 0x184 >> 8;
	delayms(velocities[velID]);
	PORTD = 0xA2 & 0xFF;
	PORTB = 0xA2 >> 8;
	delayms(velocities[velID]);
}
void seq2(){
	PORTD = 0x345 & 0xFF;
	PORTB = 0x345>> 8;
	delayms(velocities[velID]);
	PORTD = 0x355 & 0xFF;
	PORTB = 0x355 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x290 & 0xFF;
	PORTB = 0x290 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x182 & 0xFF;
	PORTB = 0x182 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x207 & 0xFF;
	PORTB = 0x207 >> 8;
	delayms(velocities[velID]);
	PORTD = 0xCE & 0xFF;
	PORTB = 0xCE >> 8;
	delayms(velocities[velID]);
	PORTD = 0xE2 & 0xFF;
	PORTB = 0xE2 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x151 & 0xFF;
	PORTB = 0x151 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1E & 0xFF;
	PORTB = 0x1E >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2D9 & 0xFF;
	PORTB = 0x2D9 >> 8;
	delayms(velocities[velID]);
}
void seq3(){
	PORTD = 0x195 & 0xFF;
	PORTB = 0x195>> 8;
	delayms(velocities[velID]);
	PORTD = 0x3ED & 0xFF;
	PORTB = 0x3ED >> 8;
	delayms(velocities[velID]);
	PORTD = 0x3B & 0xFF;
	PORTB = 0x3B >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2A & 0xFF;
	PORTB = 0x2A >> 8;
	delayms(velocities[velID]);
	PORTD = 0x23D & 0xFF;
	PORTB = 0x23D >> 8;
	delayms(velocities[velID]);
	PORTD = 0xD2 & 0xFF;
	PORTB = 0xD2 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x19D & 0xFF;
	PORTB = 0x19D >> 8;
	delayms(velocities[velID]);
	PORTD = 0x95 & 0xFF;
	PORTB = 0x95 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x83 & 0xFF;
	PORTB = 0x83 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x24F & 0xFF;
	PORTB = 0x24F >> 8;
	delayms(velocities[velID]);
}
void seq4(){
	PORTD = 0x1A9 & 0xFF;
	PORTB = 0x1A9>> 8;
	delayms(velocities[velID]);
	PORTD = 0x3B1 & 0xFF;
	PORTB = 0x3B1 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x386 & 0xFF;
	PORTB = 0x386 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x3F0 & 0xFF;
	PORTB = 0x3F0 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x58 & 0xFF;
	PORTB = 0x58 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x88 & 0xFF;
	PORTB = 0x88 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x161 & 0xFF;
	PORTB = 0x161 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x178 & 0xFF;
	PORTB = 0x178 >> 8;
	delayms(velocities[velID]);
	PORTD = 0xD4 & 0xFF;
	PORTB = 0xD4 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x263 & 0xFF;
	PORTB = 0x263 >> 8;
	delayms(velocities[velID]);
}
void seq5(){
	PORTD = 0x1B6 & 0xFF;
	PORTB = 0x1B6>> 8;
	delayms(velocities[velID]);
	PORTD = 0x1A9 & 0xFF;
	PORTB = 0x1A9 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2E6 & 0xFF;
	PORTB = 0x2E6 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1E7 & 0xFF;
	PORTB = 0x1E7 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x387 & 0xFF;
	PORTB = 0x387 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x3FD & 0xFF;
	PORTB = 0x3FD >> 8;
	delayms(velocities[velID]);
	PORTD = 0x31E & 0xFF;
	PORTB = 0x31E >> 8;
	delayms(velocities[velID]);
	PORTD = 0x100 & 0xFF;
	PORTB = 0x100 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2B4 & 0xFF;
	PORTB = 0x2B4 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x17 & 0xFF;
	PORTB = 0x17 >> 8;
	delayms(velocities[velID]);
}
void seq6(){
	PORTD = 0x9F & 0xFF;
	PORTB = 0x9F>> 8;
	delayms(velocities[velID]);
	PORTD = 0x6A & 0xFF;
	PORTB = 0x6A >> 8;
	delayms(velocities[velID]);
	PORTD = 0x30 & 0xFF;
	PORTB = 0x30 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x117 & 0xFF;
	PORTB = 0x117 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x32C & 0xFF;
	PORTB = 0x32C >> 8;
	delayms(velocities[velID]);
	PORTD = 0x18E & 0xFF;
	PORTB = 0x18E >> 8;
	delayms(velocities[velID]);
	PORTD = 0x216 & 0xFF;
	PORTB = 0x216 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x365 & 0xFF;
	PORTB = 0x365 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x141 & 0xFF;
	PORTB = 0x141 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x141 & 0xFF;
	PORTB = 0x141 >> 8;
	delayms(velocities[velID]);
}
void seq7(){
	PORTD = 0x12D & 0xFF;
	PORTB = 0x12D>> 8;
	delayms(velocities[velID]);
	PORTD = 0x34B & 0xFF;
	PORTB = 0x34B >> 8;
	delayms(velocities[velID]);
	PORTD = 0x39F & 0xFF;
	PORTB = 0x39F >> 8;
	delayms(velocities[velID]);
	PORTD = 0x202 & 0xFF;
	PORTB = 0x202 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x296 & 0xFF;
	PORTB = 0x296 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x175 & 0xFF;
	PORTB = 0x175 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1AB & 0xFF;
	PORTB = 0x1AB >> 8;
	delayms(velocities[velID]);
	PORTD = 0xF4 & 0xFF;
	PORTB = 0xF4 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1A8 & 0xFF;
	PORTB = 0x1A8 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x3F1 & 0xFF;
	PORTB = 0x3F1 >> 8;
	delayms(velocities[velID]);
}
void seq8(){
	PORTD = 0x184 & 0xFF;
	PORTB = 0x184 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x113 & 0xFF;
	PORTB = 0x113 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x29F & 0xFF;
	PORTB = 0x29F >> 8;
	delayms(velocities[velID]);
	PORTD = 0x27 & 0xFF;
	PORTB = 0x27 >> 8;
	delayms(velocities[velID]);
	PORTD = 0xE3 & 0xFF;
	PORTB = 0xE3 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x27E & 0xFF;
	PORTB = 0x27E >> 8;
	delayms(velocities[velID]);
	PORTD = 0x102 & 0xFF;
	PORTB = 0x102 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x222 & 0xFF;
	PORTB = 0x222 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x103 & 0xFF;
	PORTB = 0x103 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1C7 & 0xFF;
	PORTB = 0x1C7 >> 8;
	delayms(velocities[velID]);
}
void seq9(){
	PORTD = 0x1E3 & 0xFF;
	PORTB = 0x1E3 >> 8;
	delayms(velocities[velID]);
	PORTD = 0xD0 & 0xFF;
	PORTB = 0xD0 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1E9 & 0xFF;
	PORTB = 0x1E9 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x38A & 0xFF;
	PORTB = 0x38A >> 8;
	delayms(velocities[velID]);
	PORTD = 0xFC & 0xFF;
	PORTB = 0xFC >> 8;
	delayms(velocities[velID]);
	PORTD = 0x28C & 0xFF;
	PORTB = 0x28C >> 8;
	delayms(velocities[velID]);
	PORTD = 0x46 & 0xFF;
	PORTB = 0x46 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x18C & 0xFF;
	PORTB = 0x18C >> 8;
	delayms(velocities[velID]);
	PORTD = 0x261 & 0xFF;
	PORTB = 0x261 >> 8;
	delayms(velocities[velID]);
	PORTD = 0xE5 & 0xFF;
	PORTB = 0xE5 >> 8;
	delayms(velocities[velID]);
}
void seq10(){
	PORTD = 0xBB & 0xFF;
	PORTB = 0xBB >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2D1 & 0xFF;
	PORTB = 0x2D1 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1F7 & 0xFF;
	PORTB = 0x1F7 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1E0 & 0xFF;
	PORTB = 0x1E0 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x104 & 0xFF;
	PORTB = 0x104 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2CB & 0xFF;
	PORTB = 0x2CB >> 8;
	delayms(velocities[velID]);
	PORTD = 0x25F & 0xFF;
	PORTB = 0x25F >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2BE & 0xFF;
	PORTB = 0x2BE >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2EA & 0xFF;
	PORTB = 0x2EA >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2FF & 0xFF;
	PORTB = 0x2FF >> 8;
	delayms(velocities[velID]);
}
void seq11(){
	PORTD = 0x1F0 & 0xFF;
	PORTB = 0x1F0 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x28 & 0xFF;
	PORTB = 0x28 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1CE & 0xFF;
	PORTB = 0x1CE >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1F7 & 0xFF;
	PORTB = 0x1F7 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x314 & 0xFF;
	PORTB = 0x314 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x354 & 0xFF;
	PORTB = 0x354 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x16 & 0xFF;
	PORTB = 0x16 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x3D9 & 0xFF;
	PORTB = 0x3D9 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x95 & 0xFF;
	PORTB = 0x95 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x346 & 0xFF;
	PORTB = 0x346 >> 8;
	delayms(velocities[velID]);
}
void seq12(){
	PORTD = 0x260 & 0xFF;
	PORTB = 0x260 >> 8;
	delayms(velocities[velID]);
	PORTD = 0xEB & 0xFF;
	PORTB = 0xEB >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1CB & 0xFF;
	PORTB = 0x1CB >> 8;
	delayms(velocities[velID]);
	PORTD = 0xBA & 0xFF;
	PORTB = 0xBA >> 8;
	delayms(velocities[velID]);
	PORTD = 0x221 & 0xFF;
	PORTB = 0x221 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x17C & 0xFF;
	PORTB = 0x17C >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2A9 & 0xFF;
	PORTB = 0x2A9 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x28B & 0xFF;
	PORTB = 0x28B >> 8;
	delayms(velocities[velID]);
	PORTD = 0x338 & 0xFF;
	PORTB = 0x338 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x101 & 0xFF;
	PORTB = 0x101 >> 8;
	delayms(velocities[velID]);
}
void seq13(){
	PORTD = 0x14B & 0xFF;
	PORTB = 0x14B >> 8;
	delayms(velocities[velID]);
	PORTD = 0x186 & 0xFF;
	PORTB = 0x186 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x12B & 0xFF;
	PORTB = 0x12B >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2FD & 0xFF;
	PORTB = 0x2FD >> 8;
	delayms(velocities[velID]);
	PORTD = 0x3FE & 0xFF;
	PORTB = 0x3FE >> 8;
	delayms(velocities[velID]);
	PORTD = 0x151 & 0xFF;
	PORTB = 0x151 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2B1 & 0xFF;
	PORTB = 0x2B1 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x352 & 0xFF;
	PORTB = 0x352 >> 8;
	delayms(velocities[velID]);
	PORTD = 0xB & 0xFF;
	PORTB = 0xB >> 8;
	delayms(velocities[velID]);
	PORTD = 0x30D & 0xFF;
	PORTB = 0x30D >> 8;
	delayms(velocities[velID]);
}
void seq14(){
	PORTD = 0x70 & 0xFF;
	PORTB = 0x70 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x289 & 0xFF;
	PORTB = 0x289 >> 8;
	delayms(velocities[velID]);
	PORTD = 0xC & 0xFF;
	PORTB = 0xC >> 8;
	delayms(velocities[velID]);
	PORTD = 0x3B4 & 0xFF;
	PORTB = 0x3B4 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2F8 & 0xFF;
	PORTB = 0x2F8 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1AB & 0xFF;
	PORTB = 0x1AB >> 8;
	delayms(velocities[velID]);
	PORTD = 0x53 & 0xFF;
	PORTB = 0x53 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x6A & 0xFF;
	PORTB = 0x6A >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2CC & 0xFF;
	PORTB = 0x2CC >> 8;
	delayms(velocities[velID]);
	PORTD = 0x37E & 0xFF;
	PORTB = 0x37E >> 8;
	delayms(velocities[velID]);
}
void seq15(){
	PORTD = 0x314 & 0xFF;
	PORTB = 0x314 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x23F & 0xFF;
	PORTB = 0x23F >> 8;
	delayms(velocities[velID]);
	PORTD = 0x9B & 0xFF;
	PORTB = 0x9B >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1DF & 0xFF;
	PORTB = 0x1DF >> 8;
	delayms(velocities[velID]);
	PORTD = 0x11F & 0xFF;
	PORTB = 0x11F >> 8;
	delayms(velocities[velID]);
	PORTD = 0x3F & 0xFF;
	PORTB = 0x3F >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1DA & 0xFF;
	PORTB = 0x1DA >> 8;
	delayms(velocities[velID]);
	PORTD = 0x143 & 0xFF;
	PORTB = 0x143 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2DD & 0xFF;
	PORTB = 0x2DD >> 8;
	delayms(velocities[velID]);
	PORTD = 0x166 & 0xFF;
	PORTB = 0x166 >> 8;
	delayms(velocities[velID]);
}
void seq16(){
	PORTD = 0x14C & 0xFF;
	PORTB = 0x14C >> 8;
	delayms(velocities[velID]);
	PORTD = 0xA1 & 0xFF;
	PORTB = 0xA1 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x187 & 0xFF;
	PORTB = 0x187 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x0 & 0xFF;
	PORTB = 0x0 >> 8;
	delayms(velocities[velID]);
	PORTD = 0xE7 & 0xFF;
	PORTB = 0xE7 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x10D & 0xFF;
	PORTB = 0x10D >> 8;
	delayms(velocities[velID]);
	PORTD = 0x30F & 0xFF;
	PORTB = 0x30F >> 8;
	delayms(velocities[velID]);
	PORTD = 0x8D & 0xFF;
	PORTB = 0x8D >> 8;
	delayms(velocities[velID]);
	PORTD = 0x400 & 0xFF;
	PORTB = 0x400 >> 8;
	delayms(velocities[velID]);
	PORTD = 0xB3 & 0xFF;
	PORTB = 0xB3 >> 8;
	delayms(velocities[velID]);
}
void seq17(){
	PORTD = 0x2CB & 0xFF;
	PORTB = 0x2CB >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2C7 & 0xFF;
	PORTB = 0x2C7 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x3A2 & 0xFF;
	PORTB = 0x3A2 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x84 & 0xFF;
	PORTB = 0x84 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x106 & 0xFF;
	PORTB = 0x106 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x3E1 & 0xFF;
	PORTB = 0x3E1 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x394 & 0xFF;
	PORTB = 0x394 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x182 & 0xFF;
	PORTB = 0x182 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x223 & 0xFF;
	PORTB = 0x223 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x389 & 0xFF;
	PORTB = 0x389 >> 8;
	delayms(velocities[velID]);
}
void seq18(){
	PORTD = 0x1F9 & 0xFF;
	PORTB = 0x1F9 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x133 & 0xFF;
	PORTB = 0x133 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x3DC & 0xFF;
	PORTB = 0x3DC >> 8;
	delayms(velocities[velID]);
	PORTD = 0x3EF & 0xFF;
	PORTB = 0x3EF >> 8;
	delayms(velocities[velID]);
	PORTD = 0x329 & 0xFF;
	PORTB = 0x329 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1CA & 0xFF;
	PORTB = 0x1CA >> 8;
	delayms(velocities[velID]);
	PORTD = 0x234 & 0xFF;
	PORTB = 0x234 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x17B & 0xFF;
	PORTB = 0x17B >> 8;
	delayms(velocities[velID]);
	PORTD = 0x78 & 0xFF;
	PORTB = 0x78 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x155 & 0xFF;
	PORTB = 0x155 >> 8;
	delayms(velocities[velID]);
}	
void seq19(){
	PORTD = 0x17B & 0xFF;
	PORTB = 0x17B >> 8;
	delayms(velocities[velID]);
	PORTD = 0x0 & 0xFF;
	PORTB = 0x0 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2B6 & 0xFF;
	PORTB = 0x2B6 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x221 & 0xFF;
	PORTB = 0x221 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x123 & 0xFF;
	PORTB = 0x123 >> 8;
	delayms(velocities[velID]);
	PORTD = 0xFB & 0xFF;
	PORTB = 0xFB >> 8;
	delayms(velocities[velID]);
	PORTD = 0x325 & 0xFF;
	PORTB = 0x325 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1F1 & 0xFF;
	PORTB = 0x1F1 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x298 & 0xFF;
	PORTB = 0x298 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2E4 & 0xFF;
	PORTB = 0x2E4 >> 8;
	delayms(velocities[velID]);
}
void seq20(){
	PORTD = 0x3B4 & 0xFF;
	PORTB = 0x3B4 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x2AD & 0xFF;
	PORTB = 0x2AD >> 8;
	delayms(velocities[velID]);
	PORTD = 0x67 & 0xFF;
	PORTB = 0x67 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x148 & 0xFF;
	PORTB = 0x148 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x210 & 0xFF;
	PORTB = 0x210 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1E4 & 0xFF;
	PORTB = 0x1E4 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1B5 & 0xFF;
	PORTB = 0x1B5 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x309 & 0xFF;
	PORTB = 0x309 >> 8;
	delayms(velocities[velID]);
	PORTD = 0x28B & 0xFF;
	PORTB = 0x28B >> 8;
	delayms(velocities[velID]);
	PORTD = 0x1D1 & 0xFF;
	PORTB = 0x1D1 >> 8;
	delayms(velocities[velID]);
}
	
int main(void)
{
	DDRD |= 0xFF;
	DDRB |= 0xFF;
	DDRC |= 0x00;
    
	PORTD = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	while (1) 
    {
		PORTC = 0x00;
		getSeq();
		getVel();
		switch(seqID)
		{
			case 0:           break;
			case 1:{seq1();   break;}
			case 2:{seq2();   break;}
			case 3:{seq3();   break;}
			case 4:{seq4();   break;}
			case 5:{seq5();   break;}
			case 6:{seq6();   break;}
			case 7:{seq7();   break;}
			case 8:{seq8();   break;}
			case 9:{seq9();   break;}
			case 10:{seq10(); break;}
			case 11:{seq11(); break;}
			case 12:{seq12(); break;}
			case 13:{seq13(); break;}
			case 14:{seq14(); break;}
			case 15:{seq15(); break;}
			case 16:{seq16(); break;}
			case 17:{seq17(); break;}
			case 18:{seq18(); break;}
			case 19:{seq19(); break;}
			case 20:{seq20(); break;}
		}
    }
}
