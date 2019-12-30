#include "receiverprotocol.h"

#include <stdio.h>

//ReceiverProtocol::ReceiverProtocol()
//{

//}

//ReceiverProtocol::~ReceiverProtocol()
//{

//}

/*
 * @result: data of 16channels

RX：0F E0 03 1F 58 C0 07 16 B0 80 05 2C 60 01 0B F8 C0 07 00 00 00 00 00 03 00
CH: 992 992 352 992 352 352 352 352 352 352 992 992 000 000 000 000

RX：0F 60 01 0B 58 C0 07 66 30 83 19 7C 60 06 1F F8 C0 07 00 00 00 00 00 03 00
CH: 352 352 352 992 1632 1632 1632 992 1632 992 992 992 000 000 000 000
*/

void ReceiverProtocol::parse(char* buf, int* ch)
{
    sbusPackage_t *data = (sbusPackage_t *)buf;

    if ((data->start == SBUS_STARTBIT) && (data->end == SBUS_ENDBIT)){
        ch[ 0] = (buf[ 1] | (buf[2] << 8)) &0x07ff;                                     //!< Channel 0
        ch[ 1] = ((buf[ 2] >> 3) | (buf[3] << 5)) &0x07ff;                              //!< Channel 1
        ch[ 2] = ((buf[ 3] >> 6) | (buf[4] << 2) | (buf[5] << 10)) &0x07ff;  //!< Channel 2 			油门通道
        ch[ 3] = ((buf[ 5] >> 1) | (buf[6] << 7)) &0x07ff;    							//!< Channel 3
        ch[ 4] = ((buf[ 6] >> 4) | (buf[7] << 4)) &0x07ff;    							//!< Channel 4
        ch[ 5] = ((buf[ 7] >> 7) | (buf[8] << 1) | (buf[9] << 9)) &0x07ff;	//!< Channel 5
        ch[ 6] = ((buf[ 9] >> 2) | (buf[10] << 6)) &0x07ff;								//!< Channel 6
        ch[ 7] = ((buf[10] >> 5) | (buf[11] << 3)) &0x07ff;								//!< Channel 7
        ch[ 8] = (buf[12] | (buf[13] << 8)) &0x07ff;									//!< Channel 8
        ch[ 9] = ((buf[13] >> 3) | (buf[14] << 5)) &0x07ff;								//!< Channel 9
        ch[10] = ((buf[14] >> 6) | (buf[15] << 2) | (buf[16] << 10)) &0x07ff;//!< Channel 10
        ch[11] = ((buf[16] >> 1) | (buf[17] << 7)) &0x07ff;								//!< Channel 11
        ch[12] = ((buf[17] >> 4) | (buf[18] << 4)) &0x07ff;								//!< Channel 12
        ch[13] = ((buf[18] >> 7) | (buf[19] << 1) | (buf[20] << 9)) &0x07ff;	//!< Channel 13
        ch[14] = ((buf[20] >> 2) | (buf[21] << 6)) &0x07ff;								//!< Channel 14
        ch[15] = ((buf[21] >> 5) | (buf[22] << 3)) &0x07ff;								//!< Channel 15

        for (int i = 0; i < 16; i++){
            printf("%d ", ch[i]);
            if (i == 7)
                printf("\n");
        }
        printf("\n");

//        qDebug("parse data: over");
    }
    else{
        memset(ch, 0, 16);
        qDebug("Invalid data");
    }
}
