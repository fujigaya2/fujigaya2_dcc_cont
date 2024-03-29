//200529 fujigaya2_dcc


#include <Arduino.h>

//#define BIT_ONE_US 56
//#define BIT_ZERO_US 110
#define BIT_ONE_US 50
#define BIT_ZERO_US 110
#define BIT_CUTOFF_WIDTH_US 500
#define BIT_CUTOFF_START_US 30
#define BIT_CUTOFF_END_US 30

#define PREAMBLE_NUM 15
#define REPEAT_PACKET 3

#define DECODER_ADDRESS 0x03

#define STEP128   0b00111111

#define F0_MASK   0b00010000 

#define F0F4MASK    0b00011111
#define F0F4ORDER   0b10000000 
#define F5F8MASK    0b00001111
#define F5F8ORDER   0b10110000
#define F9F12MASK   0b00001111
#define F9F12ORDER  0b10100000
#define F13F20ORDER 0b11011110
#define F21F28ORDER 0b11011111

#define ACCESSORY_ORDER         0b10000000
#define ACCESSORY_ADDRESS_MASK1 0b00111111
#define ACCESSORY_ADDRESS_MASK2 0b01110000

#define ACCESSORY_ON         0b10001001
#define ACCESSORY_OFF        0b10001000

#define LOCO_FORWARD 0b10000000
#define LOCO_REVERSE 0b00000000

#define RAW_PACKET_LENGTH_DAFAULT 10

#define OUTPIN1_DEFAULT 9
#define OUTPIN2_DEFAULT 10



class dcc_cont
{
  public:
    dcc_cont(uint8_t out_pin1 = OUTPIN1_DEFAULT,uint8_t out_pin2 = OUTPIN2_DEFAULT);
    virtual void dcc_on(bool on_off);
    virtual void write_func_packet(unsigned int address,byte function,bool on_off);
    virtual void write_func_packet(unsigned int address,byte function);//現状値を送る場合
    virtual void write_speed_packet(unsigned int address,bool loco_direction,byte loco_speed);
    virtual void write_accessory_packet(unsigned int address,bool on_off);
    virtual void write_idle_packet();
    virtual void write_reset_packet()    ;
    virtual void set_function_default(uint32_t func_value);
    virtual void set_repeat_preamble(uint8_t repeat_num);
    virtual void set_repeat_packet(uint8_t repeat_num);
    virtual void set_pulse_us(uint32_t one_us,uint32_t zero_us);
    
  private:
    virtual void write_preamble();
    virtual void write_byte(byte b);
    virtual void bit_one();
    virtual void bit_zero();
    virtual void bit_cutout();    
    virtual void bit_off();    
    virtual void raw_packet_reset();
    virtual void raw_packet_add(uint8_t value);
    virtual uint8_t write_packet();
    virtual bool loco_address_convert_add(int loco_address);
    virtual bool loco_speed_convert_add(bool loco_direction,byte loco_speed);
    virtual void loco_func_convert_add(uint8_t function_no,bool on_off);
    virtual void loco_func_convert_add(uint8_t function_no);//現状値を送る場合
    virtual void accessory_address_onoff_convert_add(unsigned int address,bool on_off);

    uint8_t preamble_num = PREAMBLE_NUM;
    uint8_t repeat_packet = REPEAT_PACKET;
    uint32_t bit_one_us = BIT_ONE_US;
    uint32_t bit_zero_us = BIT_ZERO_US;
    uint32_t bit_cutoff_width_us = BIT_CUTOFF_WIDTH_US;
    uint32_t bit_cutoff_start_us = BIT_CUTOFF_START_US;
    uint32_t bit_cutoff_end_us = BIT_CUTOFF_END_US;
    uint8_t raw_packet[RAW_PACKET_LENGTH_DAFAULT];
    uint8_t raw_packet_length; 
    uint32_t past_func = 0x00000000;//内部FuncState
    boolean dcc_out = false;//出力のOnOff

 
};
