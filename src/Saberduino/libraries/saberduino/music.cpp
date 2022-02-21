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
constexpr uint8_t kRX = 12;
constexpr uint8_t kTX = 13;

void send_command(int8_t command, int16_t dat) {
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
        mySerial.write(val) ;
    }
}

void Music::init()
{
}

void Music::play(uint8_t idx)
{
sendCommand(SINGLE_PLAY, idx);//Premier chanson sans repertoire
}

void Music::stop()
{

}
#endif


