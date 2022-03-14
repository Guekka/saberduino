#include "music.hpp"

#ifdef SABERDUINO_DESKTOP_COMPUTER
void Music::init()
{
   
}

void Music::play(uint8_t idx)
{

}

void Music::stop()
{

}
#else
void send_command(int8_t command, int16_t dat)
{
    static int8_t send_buffer[8] = {0}; //The MP3 player undestands 8 bytes orders

    delay(20);
    send_buffer[0] = 0x7e; //starting byte
    send_buffer[1] = 0xff; //version
    send_buffer[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
    send_buffer[3] = command; //
    send_buffer[4] = 0x00;//0x00 = no feedback, 0x01 = feedback
    send_buffer[5] = (int8_t)(dat >> 8);//datah
    send_buffer[6] = (int8_t)(dat); //datal
    send_buffer[7] = 0xef; //ending byte
    for(auto val : send_buffer){
        Serial3.write(val);
    }
}

void Music::init()
{
    Serial3.begin(9600);
    stop();
}

void Music::play(uint8_t idx)
{
    send_command(0x08, idx);
}

void Music::stop()
{
    send_command(0X16, 0);
}
#endif


