#include "wav.h"
#include <QFile>

QByteArray wav_decode_init(QString filepath,wavctrl *wavctrl)
{
   bool flag;
   char *buf = nullptr;
   QByteArray audio_wav;
   ChunkRIFF *riff;
   ChunkFMT *fmt;
   ChunkFACT *fact;
   ChunkDATA *data;
   QFile file(filepath);
   flag = file.open(QFile::ReadOnly);
   audio_wav = file.readAll();
   file.read(buf,file.size());
   if(flag == true)
   {
       riff = (ChunkRIFF*)audio_wav.data();
       if(riff->Format == 0X45564157) //判断Wav文件
       {
           fmt = (ChunkFMT*)(audio_wav.data()+12);
           fact = (ChunkFACT*)(audio_wav.data()+12+8+fmt->ChunkSize);

           //fact块或list块
           if(fmt->ChunkID == 0X20746D66 && fact->ChunkID == 0X5453494C)
           {
               wavctrl->datastart = 12+8+(fmt->ChunkSize)+8+(fact->ChunkSize);
           }
           else
           {
               wavctrl->datastart = 12+8+fmt->ChunkSize;
           }
           data = (ChunkDATA*)(audio_wav.data()+wavctrl->datastart);
           if(data->ChunkID == 0X61746164)//wav解析成功
           {
               wavctrl->audioformat=fmt->AudioFormat;		//音频格式
               wavctrl->nchannels=fmt->NumOfChannels;		//通道数
               wavctrl->samplerate=fmt->SampleRate;		//采样率
               wavctrl->bitrate=fmt->ByteRate*8;			//得到位速
               wavctrl->blockalign=fmt->BlockAlign;		//块对齐
               wavctrl->bps=fmt->BitsPerSample;			//位数,16/24/32位
               wavctrl->datasize=data->ChunkSize;			//数据块大小
               wavctrl->datastart=wavctrl->datastart+8;		//数据流开始的地方.
           }
           else return 0;
       }
       else return 0;
   }
   else return 0;
   file.close();
   return audio_wav;
}
