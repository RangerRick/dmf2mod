
#include "instruments.h"

Instrument loadInstrument(FILE *filePointer, System systemType)
{
    Instrument inst; 

    int name_size = fgetc(filePointer); 
    inst.name = (char *)malloc(name_size * sizeof(char)); 
    fgets(inst.name, name_size + 1, filePointer);

    inst.mode = fgetc(filePointer);
    
    if (inst.mode == 1) // FM instrument 
    {
        inst.fmALG = fgetc(filePointer); 
        inst.fmFB = fgetc(filePointer); 
        inst.fmLFO = fgetc(filePointer); 
        inst.fmLFO2 = fgetc(filePointer); 

        int TOTAL_OPERATORS = 1;  // I'm not sure what toal operators is or where I'm supposed to get it from 
        for (int i = 0; i < TOTAL_OPERATORS; i++)
        {
            inst.fmAM = fgetc(filePointer); 
            inst.fmAR = fgetc(filePointer); 
            inst.fmDR = fgetc(filePointer); 
            inst.fmMULT = fgetc(filePointer); 
            inst.fmRR = fgetc(filePointer); 
            inst.fmSL = fgetc(filePointer); 
            inst.fmTL = fgetc(filePointer); 
            inst.fmDT2 = fgetc(filePointer); 
            inst.fmRS = fgetc(filePointer); 
            inst.fmDT = fgetc(filePointer); 
            inst.fmD2R = fgetc(filePointer); 
            inst.fmSSGMODE = fgetc(filePointer); 
        }
    }
    else if (inst.mode == 0) // Standard instrument 
    {
        if (systemType.name != "GAMEBOY") 
        {
            // Volume macro 
            inst.stdVolEnvSize = fgetc(filePointer); 
            inst.stdVolEnvValue = (int *)malloc(inst.stdVolEnvSize * sizeof(int));
            for (int i = 0; i < inst.stdVolEnvSize; i++)
            {
                inst.stdVolEnvValue[i] = fgetc(filePointer); 
                inst.stdVolEnvValue[i] <<= 8;
                inst.stdVolEnvValue[i] |= fgetc(filePointer);
                inst.stdVolEnvValue[i] <<= 8;
                inst.stdVolEnvValue[i] |= fgetc(filePointer);
                inst.stdVolEnvValue[i] <<= 8;
                inst.stdVolEnvValue[i] |= fgetc(filePointer);
            }
            if (inst.stdVolEnvSize > 0) 
                inst.stdVolEnvLoopPos = fgetc(filePointer); 
        }

        // Arpeggio macro 
        inst.stdArpEnvSize = fgetc(filePointer); 
        inst.stdArpEnvValue = (int *)malloc(inst.stdArpEnvSize * sizeof(int));
        for (int i = 0; i < inst.stdArpEnvSize; i++)
        {
            inst.stdArpEnvValue[i] = fgetc(filePointer); 
            inst.stdArpEnvValue[i] <<= 8;
            inst.stdArpEnvValue[i] |= fgetc(filePointer);
            inst.stdArpEnvValue[i] <<= 8;
            inst.stdArpEnvValue[i] |= fgetc(filePointer);
            inst.stdArpEnvValue[i] <<= 8;
            inst.stdArpEnvValue[i] |= fgetc(filePointer);
        }
        if (inst.stdArpEnvSize > 0) 
            inst.stdArpEnvLoopPos = fgetc(filePointer); 
        inst.stdArpMacroMode = fgetc(filePointer); 

        // Duty/Noise macro 
        inst.stdDutyNoiseEnvSize = fgetc(filePointer); 
        inst.stdDutyNoiseEnvValue = (int *)malloc(inst.stdDutyNoiseEnvSize * sizeof(int));
        for (int i = 0; i < inst.stdDutyNoiseEnvSize; i++)
        {
            inst.stdDutyNoiseEnvValue[i] = fgetc(filePointer); 
            inst.stdDutyNoiseEnvValue[i] <<= 8;
            inst.stdDutyNoiseEnvValue[i] |= fgetc(filePointer);
            inst.stdDutyNoiseEnvValue[i] <<= 8;
            inst.stdDutyNoiseEnvValue[i] |= fgetc(filePointer);
            inst.stdDutyNoiseEnvValue[i] <<= 8;
            inst.stdDutyNoiseEnvValue[i] |= fgetc(filePointer);
        }
        if (inst.stdDutyNoiseEnvSize > 0) 
            inst.stdDutyNoiseEnvLoopPos = fgetc(filePointer); 

        // Wavetable macro 
        inst.stdWavetableEnvSize = fgetc(filePointer); 
        inst.stdWavetableEnvValue = (int *)malloc(inst.stdWavetableEnvSize * sizeof(int));
        for (int i = 0; i < inst.stdWavetableEnvSize; i++)
        {
            inst.stdWavetableEnvValue[i] = fgetc(filePointer); 
            inst.stdWavetableEnvValue[i] <<= 8;
            inst.stdWavetableEnvValue[i] |= fgetc(filePointer);
            inst.stdWavetableEnvValue[i] <<= 8;
            inst.stdWavetableEnvValue[i] |= fgetc(filePointer);
            inst.stdWavetableEnvValue[i] <<= 8;
            inst.stdWavetableEnvValue[i] |= fgetc(filePointer);
        }
        if (inst.stdWavetableEnvSize > 0) 
            inst.stdWavetableEnvLoopPos = fgetc(filePointer); 

        // Per system data
        if (systemType.name == "C64_SID_8580" || systemType.name == "C64_SID_6581") 
        {
            inst.stdC64TriWaveEn = fgetc(filePointer); 
            inst.stdC64SawWaveEn = fgetc(filePointer); 
            inst.stdC64PulseWaveEn = fgetc(filePointer); 
            inst.stdC64NoiseWaveEn = fgetc(filePointer); 
            inst.stdC64Attack = fgetc(filePointer); 
            inst.stdC64Decay = fgetc(filePointer); 
            inst.stdC64Sustain = fgetc(filePointer); 
            inst.stdC64Release = fgetc(filePointer); 
            inst.stdC64PulseWidth = fgetc(filePointer); 
            inst.stdC64RingModEn = fgetc(filePointer); 
            inst.stdC64SyncModEn = fgetc(filePointer); 
            inst.stdC64ToFilter = fgetc(filePointer); 
            inst.stdC64VolMacroToFilterCutoffEn = fgetc(filePointer); 
            inst.stdC64UseFilterValuesFromInst = fgetc(filePointer); 
            
            // Filter globals 
            inst.stdC64FilterResonance = fgetc(filePointer); 
            inst.stdC64FilterCutoff = fgetc(filePointer); 
            inst.stdC64FilterHighPass = fgetc(filePointer); 
            inst.stdC64FilterLowPass = fgetc(filePointer); 
            inst.stdC64FilterCH2Off = fgetc(filePointer); 
        }
        else if (systemType.name == "GAMEBOY") 
        {
            inst.stdGBEnvVol = fgetc(filePointer); 
            inst.stdGBEnvDir = fgetc(filePointer); 
            inst.stdGBEnvLen = fgetc(filePointer); 
            inst.stdGBSoundLen = fgetc(filePointer); 
        }
    }

}


