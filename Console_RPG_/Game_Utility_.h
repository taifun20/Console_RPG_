#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include <windows.h>
#include <mmsystem.h>
#include <stdexcept>


void writeStringWithDelay(const std::string& str, int delayMilliseconds);


struct WavFile {
    WAVEFORMATEX format = { 0 };
    std::vector<BYTE> data;
};

/*WavFile loadWavFile(const char* filename);
void playWavFile(WavFile& wav);
void TryPlayWawFile(std::string wav_name);*/


WavFile loadWavFile(const char* filename);

void ApplyFadeIn(WavFile& wav, int fadeDurationMs);
void PlayWavFile(WavFile& wav, std::atomic<bool>& stopFlag);
void BackgroundSoundThread(WavFile& wav, std::atomic<bool>& stopFlag);
void FadeOutWavFile(WavFile& wav);

void playWavFileWithFadeIn(WavFile& wav, int fadeInDurationMs);

void stopWavFileWithFadeOut(HWAVEOUT hWaveOut, WAVEHDR& waveHdr, WavFile& wav, int fadeOutDurationMs);