#ifndef _WAV_H
#define _WAV_H

#include <QFile>


//RIFF块
  struct ChunkRIFF
{
    int ChunkID;		   	//chunk id;这里固定为"RIFF",即0X46464952
    int ChunkSize ;		   	//集合大小;文件总大小-8
    int Format;	   			//格式;WAVE,即0X45564157
} ;
//fmt块
  struct ChunkFMT
{
    int ChunkID;		   	//chunk id;这里固定为"fmt ",即0X20746D66
    int ChunkSize ;		   	//子集合大小(不包括ID和Size);这里为:20.
    short AudioFormat;	  	//音频格式;0X01,表示线性PCM;0X11表示IMA ADPCM
    short NumOfChannels;		//通道数量;1,表示单声道;2,表示双声道;
    int SampleRate;			//采样率;0X1F40,表示8Khz
    int ByteRate;			//字节速率;
    short BlockAlign;			//块对齐(字节);
    short BitsPerSample;		//单个采样数据大小;4位ADPCM,设置为4
//	u16 ByteExtraData;		//附加的数据字节;2个; 线性PCM,没有这个参数
};
//fact块
  struct ChunkFACT
{
    int ChunkID;		   	//chunk id;这里固定为"fact",即0X74636166;
    int ChunkSize ;		   	//子集合大小(不包括ID和Size);这里为:4.
    int NumOfSamples;	  	//采样的数量;
};
//LIST块
  struct ChunkLIST
{
    int ChunkID;		   	//chunk id;这里固定为"LIST",即0X74636166;
    int ChunkSize ;		   	//子集合大小(不包括ID和Size);这里为:4.
};
//data块
  struct ChunkDATA
{
    int ChunkID;		   	//chunk id;这里固定为"data",即0X5453494C
    int ChunkSize ;		   	//子集合大小(不包括ID和Size)
};

//wav头
  struct WaveHeader
{
    ChunkRIFF riff;	//riff块
    ChunkFMT fmt;  	//fmt块
//	ChunkFACT fact;	//fact块 线性PCM,没有这个结构体
    ChunkDATA data;	//data块
};

//wav 播放控制结构体
  struct wavctrl
{
    short audioformat;			//音频格式;0X01,表示线性PCM;0X11表示IMA ADPCM
    short nchannels;				//通道数量;1,表示单声道;2,表示双声道;
    short blockalign;				//块对齐(字节);
    int datasize;				//WAV数据大小

    int totsec ;				//整首歌时长,单位:秒
    int cursec ;				//当前播放时长

    int bitrate;	   			//比特率(位速)
    int samplerate;				//采样率
    short bps;					//位数,比如16bit,24bit,32bit

    int datastart;				//数据帧开始的位置(在文件里面的偏移)
};


QByteArray wav_decode_init(QString filepath, wavctrl *wavctrl);

#endif
