# TSDemux
tool to extract video and audio from the MPEG-2 TS stream. without 3rd libraries

## How to build
```
cd TSDemux
cmake .
make
```

## How to use
```
./ts-demux -i <input_ts_file> -a <audio_file_to_extract> -v <video_file_to_extract>
```
e.g.
```
./ts-demux -i awesome-video.ts -a awesome-audio.aac -v awesome-video-onlny.h264
```

## Design highlight
The tool reads the source file packet by packet (188 bytes), extracts video and audio related data and stores it into corresponding files provided with command line parameters.

All the main logic is performed by M2TSProcessor class.

Actually it processes only 3 types of TS packets and ignores others:

PAT - to detect the program translated and its PMT. Each time it comes, current program PID is updated. 

PMT - to detect the elementary stream for video/audio. Each time it comes, PID of audio/video streams are updated

PES - elementary stream packet that contains raw data of vide and audio to be extracted. Each time it comes, the raw data is stored in the corresponding output stream.
