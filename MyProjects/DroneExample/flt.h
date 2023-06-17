#ifndef DRONEEXAMPLE_FLT_H_
#define DRONEEXAMPLE_FLT_H_
#include "daisysp.h"
#include "daisy_seed.h"

class Filter {
    public:
        void Init(float sampleRate) {
            this->_flt.Init(sampleRate);
        }

        void SetTimbre(float timbre) {
            float fltFreq = daisysp::fmap(timbre, 60, 15000);
            float fltRes = daisysp::fmap(1.0f - timbre, 0, 0.5);
            this->_flt.SetFreq(fltFreq);
            this->_flt.SetRes(fltRes);
        }

        float Process(const float in) {
            return this->_flt.Process(in);
        }

    private:
        daisysp::MoogLadder _flt;
};

#endif /* DRONEEXAMPLE_FLT_H_ */
