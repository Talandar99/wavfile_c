#!/bin/bash

rm main 
rm sound.wav
gcc main.c -o main -lm

./main
mpv sound.wav
rm sound.wav
rm main 
