#include "Game_Utility_.h"

void writeStringWithDelay(const std::string& str, int delayMilliseconds)
{
    for (char c : str) {
        std::cout << c << std::flush;  // Flush the output buffer to ensure immediate display
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMilliseconds));
    }
    std::cout << std::endl;
}


/*
WavFile loadWavFile(const char* filename) {
    WavFile wav;
    // Open the file
    HMMIO hMmio = mmioOpenA(const_cast<char*>(filename), nullptr, MMIO_READ | MMIO_ALLOCBUF);
    if (!hMmio) throw std::runtime_error("Could not open file");

    MMCKINFO ckInRiff;
    ckInRiff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    mmioDescend(hMmio, &ckInRiff, nullptr, MMIO_FINDRIFF);

    MMCKINFO ckIn;
    ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
    mmioDescend(hMmio, &ckIn, &ckInRiff, MMIO_FINDCHUNK);
    mmioRead(hMmio, reinterpret_cast<HPSTR>(&wav.format), sizeof(wav.format));
    mmioAscend(hMmio, &ckIn, 0);

    ckIn.ckid = mmioFOURCC('d', 'a', 't', 'a');
    mmioDescend(hMmio, &ckIn, &ckInRiff, MMIO_FINDCHUNK);
    wav.data.resize(ckIn.cksize);
    mmioRead(hMmio, reinterpret_cast<HPSTR>(wav.data.data()), ckIn.cksize);

    mmioClose(hMmio, 0);
    return wav;
}


void playWavFile(WavFile& wav) {
    HWAVEOUT hWaveOut;
    WAVEHDR waveHdr;
    ZeroMemory(&waveHdr, sizeof(WAVEHDR));
    waveHdr.dwBufferLength = wav.data.size();
    waveHdr.lpData = reinterpret_cast<LPSTR>(wav.data.data());

    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wav.format, 0, 0, CALLBACK_NULL);
    waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &waveHdr, sizeof(WAVEHDR));

    // Fade out effect
    for (int i = 100; i >= 0; --i) {
        double volume = i / 100.0;
        for (size_t j = 0; j < wav.data.size(); j += 2) {
            SHORT* sample = reinterpret_cast<SHORT*>(&wav.data[j]);
            *sample = static_cast<SHORT>(*sample * volume);
        }
        waveOutWrite(hWaveOut, &waveHdr, sizeof(WAVEHDR));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

void TryPlayWawFile(std::string wav_name) {
    try {
        std::string filename = "../Console_RPG_/Sounds/" + wav_name + ".wav";  // Concatenate to form the full filename
        WavFile wav = loadWavFile(filename.c_str());  // Pass the C-string to loadWavFile
        playWavFile(wav);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}*/


WavFile loadWavFile(const char* filename) {
    WavFile wav;

    // Open the file
    HMMIO hMmio = mmioOpenA(const_cast<char*>(filename), nullptr, MMIO_READ | MMIO_ALLOCBUF);
    if (!hMmio) throw std::runtime_error("Could not open file");

    MMCKINFO ckInRiff;
    ckInRiff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    mmioDescend(hMmio, &ckInRiff, nullptr, MMIO_FINDRIFF);

    MMCKINFO ckIn;
    ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
    mmioDescend(hMmio, &ckIn, &ckInRiff, MMIO_FINDCHUNK);
    mmioRead(hMmio, reinterpret_cast<HPSTR>(&wav.format), sizeof(wav.format));
    mmioAscend(hMmio, &ckIn, 0);

    ckIn.ckid = mmioFOURCC('d', 'a', 't', 'a');
    mmioDescend(hMmio, &ckIn, &ckInRiff, MMIO_FINDCHUNK);
    wav.data.resize(ckIn.cksize);
    mmioRead(hMmio, reinterpret_cast<HPSTR>(wav.data.data()), ckIn.cksize);

    mmioClose(hMmio, 0);
    return wav;
}


void ApplyFadeIn(WavFile& wav, int fadeDurationMs) {
    int sampleRate = wav.format.nSamplesPerSec;
    int bytesPerSample = wav.format.nBlockAlign;
    int totalSamples = (fadeDurationMs * sampleRate) / 1000;

    for (int i = 0; i < totalSamples; ++i) {
        double volume = static_cast<double>(i) / totalSamples;
        for (int j = 0; j < bytesPerSample; j += 2) {
            int index = (i * bytesPerSample) + j;
            if (index < wav.data.size()) {
                SHORT* sample = reinterpret_cast<SHORT*>(&wav.data[index]);
                *sample = static_cast<SHORT>(*sample * volume);
            }
        }
    }
}

void PlayWavFile(WavFile& wav, std::atomic<bool>& stopFlag) {
    HWAVEOUT hWaveOut;
    WAVEHDR waveHdr;
    ZeroMemory(&waveHdr, sizeof(WAVEHDR));
    waveHdr.dwBufferLength = wav.data.size();
    waveHdr.lpData = reinterpret_cast<LPSTR>(wav.data.data());

    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wav.format, 0, 0, CALLBACK_NULL);
    waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &waveHdr, sizeof(WAVEHDR));

    // Wait until the sound playback is done or stopFlag is set
    while (!(waveHdr.dwFlags & WHDR_DONE) && !stopFlag.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    waveOutReset(hWaveOut); // Stop playback immediately
    waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}

void BackgroundSoundThread(WavFile& wav, std::atomic<bool>& stopFlag) {
    PlayWavFile(wav, stopFlag);
}


void FadeOutWavFile(WavFile& wav) {
    HWAVEOUT hWaveOut;
    WAVEHDR waveHdr;
    ZeroMemory(&waveHdr, sizeof(WAVEHDR));
    waveHdr.dwBufferLength = wav.data.size();
    waveHdr.lpData = reinterpret_cast<LPSTR>(wav.data.data());

    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wav.format, 0, 0, CALLBACK_NULL);
    waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &waveHdr, sizeof(WAVEHDR));

    // Fade out effect
    for (int i = 25; i >= 0; --i) {
        double volume = i / 25.0;
        for (size_t j = 0; j < wav.data.size(); j += 2) {
            SHORT* sample = reinterpret_cast<SHORT*>(&wav.data[j]);
            *sample = static_cast<SHORT>(*sample * volume);
        }
        waveOutWrite(hWaveOut, &waveHdr, sizeof(WAVEHDR));
        //std::this_thread::sleep_for(std::chrono::milliseconds(5));
        //std::cout << "Audio Out: "<< i << std::endl;
    }

    waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}


void playWavFileWithFadeIn(WavFile& wav, int fadeInDurationMs) {
    HWAVEOUT hWaveOut = nullptr; // Initialize to nullptr
    WAVEHDR waveHdr;
    ZeroMemory(&waveHdr, sizeof(WAVEHDR));
    waveHdr.dwBufferLength = static_cast<DWORD>(wav.data.size()); // Cast to DWORD to resolve warning
    waveHdr.lpData = reinterpret_cast<LPSTR>(wav.data.data());

    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wav.format, 0, 0, CALLBACK_NULL);
    waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &waveHdr, sizeof(WAVEHDR));

    int fadeInSteps = fadeInDurationMs / 10;
    for (DWORD i = 0; i <= static_cast<DWORD>(fadeInSteps); ++i) { // Cast to DWORD to resolve warning
        double volume = static_cast<double>(i) / fadeInSteps;
        for (size_t j = 0; j < wav.data.size(); j += 2) {
            SHORT* sample = reinterpret_cast<SHORT*>(&wav.data[j]);
            *sample = static_cast<SHORT>(*sample * volume);
        }
        waveOutWrite(hWaveOut, &waveHdr, sizeof(WAVEHDR));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    waveOutWrite(hWaveOut, &waveHdr, sizeof(WAVEHDR));
}

void stopWavFileWithFadeOut(HWAVEOUT hWaveOut, WAVEHDR& waveHdr, WavFile& wav, int fadeOutDurationMs) {
    int fadeOutSteps = fadeOutDurationMs / 10;
    for (DWORD i = static_cast<DWORD>(fadeOutSteps); i != 0; --i) { // Cast to DWORD to resolve warning
        double volume = static_cast<double>(i) / fadeOutSteps;
        for (size_t j = 0; j < wav.data.size(); j += 2) {
            SHORT* sample = reinterpret_cast<SHORT*>(&wav.data[j]);
            *sample = static_cast<SHORT>(*sample * volume);
        }
        waveOutWrite(hWaveOut, &waveHdr, sizeof(WAVEHDR));
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
