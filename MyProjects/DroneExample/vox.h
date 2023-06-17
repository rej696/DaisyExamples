#ifndef DRONEEXAMPLE_VOX_H_
#define DRONEEXAMPLE_VOX_H_
#include "daisysp.h"
#include "daisy_seed.h"
#include <stdlib.h>

class Vox {
    public:
        static constexpr float kOscLowestFreq = 36;

        void Init(float sampleRate, float oscHighestFreq) {
            // Oscillator Setup
            this->_osc.Init(sampleRate);
            this->_osc.SetWaveform(daisysp::Oscillator::WAVE_SAW);
            this->_oscHighestFreq = oscHighestFreq;

            // Lfo Setup
            this->_lfo.Init(sampleRate);
            this->_lfo.SetFreq(this->randFloat() / 10.0);
            this->_lfo.SetWaveform(daisysp::Oscillator::WAVE_SIN);
        }

        void Read(float oscPitch, float oscFreq) {
            float pitch = daisysp::fmap(oscPitch, 0 , 500);
            float oscFreqMin = kOscLowestFreq + pitch;
            float oscFreqMax = this->_oscHighestFreq + pitch;
            this->_oscFreq = daisysp::fmap(oscFreq, oscFreqMin, oscFreqMax);
            float lfoAmp = daisysp::fmap(oscFreq, 0.0f, 0.005);
            this->_lfo.SetAmp(lfoAmp);
        }

        float Process() {
            this->_osc.SetFreq(this->_oscFreq * (1.0f + this->_lfo.Process()));
            return this->_osc.Process();
        }

    private:
        float randFloat() {
            int range = this->_randMax - this->_randMin + 1;
            return static_cast<float>(rand() % range + this->_randMin) ;
        }

        const int _randMin = 50;
        const int _randMax = 150;

        daisysp::Oscillator _osc;
        daisysp::Oscillator _lfo;
        float _oscFreq;
        float _oscHighestFreq;
};

#endif /* DRONEEXAMPLE_VOX_H_ */
