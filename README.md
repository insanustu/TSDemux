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
