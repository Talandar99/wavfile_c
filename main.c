#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define WAVFILE_SAMPLES_PER_SECOND 44100

struct wavfile_header {
    char riff_tag[4];
    int riff_length;
    char wave_tag[4];
    char fmt_tag[4];
    int fmt_length;
    short audio_format;
    short num_channels;
    int sample_rate;
    int byte_rate;
    short block_align;
    short bits_per_sample;
    char data_tag[4];
    int data_length;
};

FILE *wavfile_open(const char *filename) {
    struct wavfile_header header;
    int bits_per_sample = 16;
    strncpy(header.riff_tag, "RIFF", 4);
    strncpy(header.wave_tag, "WAVE", 4);
    strncpy(header.fmt_tag, "fmt ", 4);
    strncpy(header.data_tag, "data", 4);
    header.riff_length = 0;
    header.fmt_length = 16;
    header.audio_format = 1;
    header.num_channels = 1;
    header.sample_rate = WAVFILE_SAMPLES_PER_SECOND;
    header.byte_rate = WAVFILE_SAMPLES_PER_SECOND * (bits_per_sample / 8);
    header.block_align = bits_per_sample / 8;
    header.bits_per_sample = bits_per_sample;
    header.data_length = 0;
    FILE *file = fopen(filename, "wb+");
    if (!file) return 0;
    fwrite(&header, sizeof(header), 1, file);
    fflush(file);
    return file;
}

void wavfile_write_and_close(FILE *file, short data[], int length) {
    fwrite(data, sizeof(short), length, file);
    int file_length = ftell(file);
    int data_length = file_length - sizeof(struct wavfile_header);
    fseek(file, sizeof(struct wavfile_header) - sizeof(int), SEEK_SET);
    fwrite(&data_length, sizeof(data_length), 1, file);
    int riff_length = file_length - 8;
    fseek(file, 4, SEEK_SET);
    fwrite(&riff_length, sizeof(riff_length), 1, file);
    fclose(file);
}

int main() {
    const int NUM_SAMPLES = (WAVFILE_SAMPLES_PER_SECOND * 3);
    short waveform[NUM_SAMPLES];
    double frequency = 220.0;
    int volume = 8000;
    printf("%i\n", 44100);

    for (int i = 0; i < NUM_SAMPLES; i++) {
        double t = (double)i / WAVFILE_SAMPLES_PER_SECOND;

        if (NUM_SAMPLES < NUM_SAMPLES / 10) {
            waveform[i] = volume * sin(frequency * t * 2 * M_PI * 2);
        } else if (i < (NUM_SAMPLES / 10) * 2) {
            waveform[i] = volume * sin(frequency * t * 2 * M_PI * 200);
        } else if (i < (NUM_SAMPLES / 10) * 3) {
            waveform[i] = volume * sin(frequency * t * 2 * M_PI * 2);
        } else if (i < (NUM_SAMPLES / 10) * 4) {
            waveform[i] = volume * sin(frequency * t * 2 * M_PI * 200);
        } else if (i < (NUM_SAMPLES / 10) * 5) {
            waveform[i] = volume * sin(frequency * t * 2 * M_PI * 200);
        } else if (i < (NUM_SAMPLES / 10) * 6) {
            waveform[i] = volume * sin(frequency * t * 2 * M_PI * 2);
        } else if (i < (NUM_SAMPLES / 10) * 7) {
            waveform[i] = volume * sin(frequency * t * 2 * M_PI * 2);
        } else if (i < (NUM_SAMPLES / 10) * 8) {
            waveform[i] = volume * sin(frequency * t * 2 * M_PI * 2);
        } else if (i < (NUM_SAMPLES / 10) * 9) {
            waveform[i] = volume * sin(frequency * t * 2 * M_PI * 2);
        } else {
            waveform[i] = volume * sin(frequency * t * 2 * M_PI * 2);
        }
    }

    FILE *f = wavfile_open("sound.wav");
    if (!f) {
        printf("couldn't open sound.wav for writing: %s", strerror(errno));
        return 1;
    }
    wavfile_write_and_close(f, waveform, NUM_SAMPLES);

    return 0;
}
