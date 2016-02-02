FLAGS=-I/root/ffmpeg_build/include
LIBS=-pthread -L/root/ffmpeg_build/lib -lavformat -lavcodec -lx265 -lstdc++ -lrt -lx264 -ldl -lvpx -lpthread -lvorbisenc -lvorbis -logg -lopus -lmp3lame -lfreetype -lfdk-aac -lz -lswresample -lavutil -lm

all:
	gcc -Wall -g -DUSE_H264BSF segmenter.c helpers.c options_parsing.c -o segmenter $(FLAGS) $(LIBS)

m3u8: m3u8.c
	gcc -Wall -g m3u8.c -o m3u8 $(FLAGS) $(LIBS)

clean:
	rm segmenter

install: segmenter
	cp segmenter /usr/local/bin/

uninstall:
	rm /usr/local/bin/segmenter
