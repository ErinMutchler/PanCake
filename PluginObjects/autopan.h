#pragma once

#ifndef __AutoPan__
#define __AutoPan__

#include "fxobjects.h"
#include "superlfo.h"


#define _kSIN 0
#define _kTRIANGLE 1
#define _kSAW 2
#define _kQRSH 3

#define kNORMAL_PHASE 0
#define kQUAD_PHASE 1
#define kINVERTED_PHASE 2
#define kQUAD_INVERTED_PHASE 3

/**
\struct AutoPanParameters
\ingroup FX-Objects
\brief
Custom parameter structure for the AutoPan object.

\author <Aaron Mutchler> <http://www.aaronmutchler.com>
\remark <Put any remarks or notes here>
\version Revision : 1.0
\date Date : 2019 / 01 / 31
*/

enum class channelSelectionEnum { kStereo, kLeft, kRight };

struct AutoPanParameters
{
	AutoPanParameters() {}

	/** all FXObjects parameter objects require overloaded= operator so remember to add new entries if you add new variables. */
	AutoPanParameters& operator=(const AutoPanParameters& params)	// need this override for collections to work
	{
		// --- it is possible to try to make the object equal to itself
		//     e.g. thisObject = thisObject; so this code catches that
		//     trivial case and just returns this object
		if (this == &params)
			return *this;

		// --- copy from params (argument) INTO our variables
		enableLFOa = params.enableLFOa;
		enableLFOb = params.enableLFOb;
		enableLFOc = params.enableLFOc;
		enableLFOd = params.enableLFOd;

		soloLFOa = params.soloLFOa;
		soloLFOb = params.soloLFOb;
		soloLFOc = params.soloLFOc;
		soloLFOd = params.soloLFOd;

		LFOaWaveform = params.LFOaWaveform;
		LFObWaveform = params.LFObWaveform;
		LFOcWaveform = params.LFOcWaveform;
		LFOdWaveform = params.LFOdWaveform;

		LFOaDepth = params.LFOaDepth;
		LFObDepth = params.LFObDepth;
		LFOcDepth = params.LFOcDepth;
		LFOdDepth = params.LFOdDepth;

		LFOaRate = params.LFOaRate;
		LFObRate = params.LFObRate;
		LFOcRate = params.LFOcRate;
		LFOdRate = params.LFOdRate;

		LFOaSyncToBPM = params.LFOaSyncToBPM;
		LFObSyncToBPM = params.LFObSyncToBPM;
		LFOcSyncToBPM = params.LFOcSyncToBPM;
		LFOdSyncToBPM = params.LFOdSyncToBPM;

		LFOaPhase = params.LFOaPhase;
		LFObPhase = params.LFObPhase;
		LFOcPhase = params.LFOcPhase;
		LFOdPhase = params.LFOdPhase;

		volume_dB = params.volume_dB;
		enableMute = params.enableMute;
		enableMSdecode = params.enableMSdecode;
		channelSelection = params.channelSelection;
		panValue = params.panValue;
		outputMeterL = params.outputMeterL;
		outputMeterR = params.outputMeterR;
		stereoWidth = params.stereoWidth; 

		bpm = params.bpm;


		// --- MUST be last
		return *this;
	}

	// --- individual parameters
	bool enableLFOa = false;	///< All LFO's start as un-enabled
	bool enableLFOb = false;	///< All LFO's start as un-enabled
	bool enableLFOc = false;	///< All LFO's start as un-enabled
	bool enableLFOd = false;	///< All LFO's start as un-enabled

	bool soloLFOa = false;      ///< Solo enable for all LFO's start as un-enabled
	bool soloLFOb = false;      ///< Solo enable for all LFO's start as un-enabled
	bool soloLFOc = false;      ///< Solo enable for all LFO's start as un-enabled
	bool soloLFOd = false;      ///< Solo enable for all LFO's start as un-enabled

	int LFOaWaveform = _kSIN; ///< Default Waveform for LFO 'A' is a Sine wave
	int LFObWaveform = _kSIN; ///< Default Waveform for LFO 'B' is a Sine wave
	int LFOcWaveform = _kSIN; ///< Default Waveform for LFO 'C' is a Sine wave
	int LFOdWaveform = _kSIN; ///< Default Waveform for LFO 'D' is a Sine wave

	double LFOaDepth = 0.00;
	double LFObDepth = 0.00;
	double LFOcDepth = 0.00;
	double LFOdDepth = 0.00;

	double LFOaRate = 0.00;
	double LFObRate = 0.00;
	double LFOcRate = 0.00;
	double LFOdRate = 0.00;

	int LFOaSyncToBPM = 0; ///< Defaults to 0 which corresponds with 'off'
	int LFObSyncToBPM = 0; ///< Defaults to 0 which corresponds with 'off'
	int LFOcSyncToBPM = 0; ///< Defaults to 0 which corresponds with 'off'
	int LFOdSyncToBPM = 0; ///< Defaults to 0 which corresponds with 'off'

	int LFOaPhase = kNORMAL_PHASE; ///< Defaults to normal phase
	int LFObPhase = kNORMAL_PHASE; ///< Defaults to normal phase
	int LFOcPhase = kNORMAL_PHASE; ///< Defaults to normal phase
	int LFOdPhase = kNORMAL_PHASE; ///< Defaults to normal phase

	double volume_dB = 0.00;
	bool enableMute = false;
	bool enableMSdecode = false;
	channelSelectionEnum channelSelection = channelSelectionEnum::kStereo;
	double panValue = 0.00;
	float outputMeterL = 0.f;
	float outputMeterR = 0.f;
	double stereoWidth = 0.00;  ///< Defaults to 0% width (range -100% to 100%)

	double bpm = 0.00;
};


/**
\class AutoPan
\ingroup FX-Objects
\brief
The AutoPan object implements ....

Audio I/O:
- Processes mono input to mono output.
- *** Optionally, process frame *** Modify this according to your object functionality

Control I/F:
- Use AutoPanParameters structure to get/set object params.

\author <Aaron Mutchler> <http://www.aaronmutchler.com>
\remark <Put any remarks or notes here>
\version Revision : 1.0
\date Date : 2019 / 01 / 31
*/
class AutoPan : public IAudioSignalProcessor
{
public:
	AutoPan(void) {}	/* C-TOR */
	~AutoPan(void) {}	/* D-TOR */

public:
	/** reset members to initialized state */
	virtual bool reset(double _sampleRate)
	{
		// --- store the sample rate
		sampleRate = _sampleRate;

		// --- do any other per-audio-run inits here
		AutoPanParameters params = getParameters();

		LFOa.reset(sampleRate);
		LFOb.reset(sampleRate);
		LFOc.reset(sampleRate);
		LFOd.reset(sampleRate);

		return true;
	}

	/** process MONO input */
	/**
	\param xn input
	\return the processed sample
	*/

	virtual double processAudioSample(double xn)
	{
		// --- the output variable
		double yn = 0.0;

		// --- do your DSP magic here to create yn


		double gain = volumeCooked;
		// --- mute branch
		if (parameters.enableMute)
			gain = 0.0;
		// --- the DSP
		yn = gain * xn;
		// --- set meter
		parameters.outputMeterL = yn;
		parameters.outputMeterR = yn;

		// --- done
		return yn;
	}

	/** query to see if this object can process frames */
	virtual bool canProcessAudioFrame() { return true; } // <-- change this!

	/** process audio frame: implement this function if you answer "true" to above query */
	virtual bool processAudioFrame(const float* inputFrame,	/* ptr to one frame of data: pInputFrame[0] = left, pInputFrame[1] = right, etc...*/
					     float* outputFrame,
					     uint32_t inputChannels,
					     uint32_t outputChannels)
	{
		AutoPanParameters params = getParameters();
		SuperLFOParameters LFOparams;

		double activeLFOcount = 0.0;

		double LFOaModifier = 0.0;
		double LFObModifier = 0.0;
		double LFOcModifier = 0.0;
		double LFOdModifier = 0.0;

		double syncedNoteValues[6];
		//double noteValues[6] = { 3.0, 2.0, 1.5, 1.0, 0.5, 0.25 }; ///< Corresponds to eighth note triplets, eighth note, quarter note triplet, quarter note, half note, whole note

		double noteValues[6] = { 0.125, 0.334, 0.5, 1.0, 2.0, 4.0 }; ///< Corresponds to eighth note triplets, eighth note, quarter note triplet, quarter note, half note, whole note

		// Split input frame into left and right signal
		double xnL = inputFrame[0];
		double xnR = inputChannels == 1 ? inputFrame[0] : inputFrame[1];

		if (params.enableMSdecode) {
			double side = 0.5 * (xnL - xnR);
			double mid = 0.5 * (xnL + xnR);
			xnL = mid + side;
			xnR = mid - side;
		}
		
		// Sync beats to tempo

		double bps = params.bpm / 60.0;
		for (int i = 0; i < 6; i++) {
			syncedNoteValues[i] = (bps * noteValues[i]);
		}

		// Calculate LFOs A through D outputs

		if (params.enableLFOa) {
			LFOparams.frequency_Hz = params.LFOaRate;
			if (params.LFOaSyncToBPM != 0) {
				LFOparams.frequency_Hz = (1.0 / syncedNoteValues[params.LFOaSyncToBPM - 1]);
				boundValue(LFOparams.frequency_Hz, 0.02, 20);
			}
			LFOparams.outputAmplitude = params.LFOaDepth / 100.0;

			if (params.LFOaWaveform == _kSIN) { LFOparams.waveform = LFOWaveform::kSin; }
			else if (params.LFOaWaveform == _kTRIANGLE) { LFOparams.waveform = LFOWaveform::kTriangle; }
			else if (params.LFOaWaveform == _kSAW) { LFOparams.waveform = LFOWaveform::kSaw; }
			else if (params.LFOaWaveform == _kQRSH) { LFOparams.waveform = LFOWaveform::kQRSH; }

			LFOa.setParameters(LFOparams);
			SignalModulatorOutput output = LFOa.renderModulatorOutput();

			if (params.LFOaPhase == kQUAD_INVERTED_PHASE) { LFOaModifier = output.quadPhaseOutput_neg; }
			else if (params.LFOaPhase == kNORMAL_PHASE) { LFOaModifier = output.normalOutput; }
			else if (params.LFOaPhase == kQUAD_PHASE) { LFOaModifier = output.quadPhaseOutput_pos; }
			else if (params.LFOaPhase == kINVERTED_PHASE) { LFOaModifier = output.invertedOutput; }
			activeLFOcount++;
		}

		if (params.enableLFOb) {
			LFOparams.frequency_Hz = params.LFObRate;
			if (params.LFObSyncToBPM != 0) {
				LFOparams.frequency_Hz = syncedNoteValues[params.LFObSyncToBPM - 1];
			}
			LFOparams.outputAmplitude = params.LFObDepth / 100.0;

			if (params.LFObWaveform == _kSIN) { LFOparams.waveform = LFOWaveform::kSin; }
			else if (params.LFObWaveform == _kTRIANGLE) { LFOparams.waveform = LFOWaveform::kTriangle; }
			else if (params.LFObWaveform == _kSAW) { LFOparams.waveform = LFOWaveform::kSaw; }
			else if (params.LFObWaveform == _kQRSH) { LFOparams.waveform = LFOWaveform::kQRSH; }

			LFOb.setParameters(LFOparams);
			SignalModulatorOutput output = LFOb.renderModulatorOutput();

			if (params.LFObPhase == kQUAD_INVERTED_PHASE) { LFObModifier = output.quadPhaseOutput_neg; }
			else if (params.LFObPhase == kNORMAL_PHASE) { LFObModifier = output.normalOutput; }
			else if (params.LFObPhase == kQUAD_PHASE) { LFObModifier = output.quadPhaseOutput_pos; }
			else if (params.LFObPhase == kINVERTED_PHASE) { LFObModifier = output.invertedOutput; }
			activeLFOcount++;
		}

		if (params.enableLFOc) {
			LFOparams.frequency_Hz = params.LFOcRate;
			if (params.LFOcSyncToBPM != 0) {
				LFOparams.frequency_Hz = syncedNoteValues[params.LFOcSyncToBPM - 1];
			}
			LFOparams.outputAmplitude = params.LFOcDepth / 100.0;

			if (params.LFOcWaveform == _kSIN) { LFOparams.waveform = LFOWaveform::kSin; }
			else if (params.LFOcWaveform == _kTRIANGLE) { LFOparams.waveform = LFOWaveform::kTriangle; }
			else if (params.LFOcWaveform == _kSAW) { LFOparams.waveform = LFOWaveform::kSaw; }
			else if (params.LFOcWaveform == _kQRSH) { LFOparams.waveform = LFOWaveform::kQRSH; }

			LFOc.setParameters(LFOparams);
			SignalModulatorOutput output = LFOc.renderModulatorOutput();

			if (params.LFOcPhase == kQUAD_INVERTED_PHASE) { LFOcModifier = output.quadPhaseOutput_neg; }
			else if (params.LFOcPhase == kNORMAL_PHASE) { LFOcModifier = output.normalOutput; }
			else if (params.LFOcPhase == kQUAD_PHASE) { LFOcModifier = output.quadPhaseOutput_pos; }
			else if (params.LFOcPhase == kINVERTED_PHASE) { LFOcModifier = output.invertedOutput; }
			activeLFOcount++;
		}

		if (params.enableLFOd) {
			LFOparams.frequency_Hz = params.LFOdRate;
			if (params.LFOdSyncToBPM != 0) {
				LFOparams.frequency_Hz = syncedNoteValues[params.LFOdSyncToBPM - 1];
			}
			LFOparams.outputAmplitude = params.LFOdDepth / 100.0;

			if (params.LFOdWaveform == _kSIN) { LFOparams.waveform = LFOWaveform::kSin; }
			else if (params.LFOdWaveform == _kTRIANGLE) { LFOparams.waveform = LFOWaveform::kTriangle; }
			else if (params.LFOdWaveform == _kSAW) { LFOparams.waveform = LFOWaveform::kSaw; }
			else if (params.LFOdWaveform == _kQRSH) { LFOparams.waveform = LFOWaveform::kQRSH; }

			LFOd.setParameters(LFOparams);
			SignalModulatorOutput output = LFOd.renderModulatorOutput();

			if (params.LFOdPhase == kQUAD_INVERTED_PHASE) { LFOdModifier = output.quadPhaseOutput_neg; }
			else if (params.LFOdPhase == kNORMAL_PHASE) { LFOdModifier = output.normalOutput; }
			else if (params.LFOdPhase == kQUAD_PHASE) { LFOdModifier = output.quadPhaseOutput_pos; }
			else if (params.LFOdPhase == kINVERTED_PHASE) { LFOdModifier = output.invertedOutput; }
			activeLFOcount++;
		}

		if ((params.soloLFOa && params.enableLFOa) || (params.soloLFOb && params.enableLFOb) || (params.soloLFOc && params.enableLFOc) || (params.soloLFOd && params.enableLFOd)) {
			if (!params.soloLFOa && params.enableLFOa) { LFOaModifier = 0.0; activeLFOcount--; }
			if (!params.soloLFOb && params.enableLFOb) { LFObModifier = 0.0; activeLFOcount--; }
			if (!params.soloLFOc && params.enableLFOc) { LFOcModifier = 0.0; activeLFOcount--; }
			if (!params.soloLFOd && params.enableLFOd) { LFOdModifier = 0.0; activeLFOcount--; }
		}

		double combinedLFOs = 0.0;
		if (activeLFOcount > 0.0) {
			combinedLFOs = (LFOaModifier + LFObModifier + LFOcModifier + LFOdModifier) / activeLFOcount;
		}

		double panModifier_L = panValue_L * cos((combinedLFOs + 1) * (kPi / 4.0));
		double panModifier_R = panValue_R * sin((combinedLFOs + 1) * (kPi / 4.0));

		double gain_L = volumeCooked * panModifier_L;
		double gain_R = volumeCooked * panModifier_R;

		if (parameters.channelSelection == channelSelectionEnum::kLeft) {
			gain_R = 0.0;
		}
		else if (parameters.channelSelection == channelSelectionEnum::kRight) {
			gain_L = 0.0;
		}

		if (parameters.enableMute) {
			gain_L = 0.0;
			gain_R = 0.0;
		}

		double stereoWidth = params.stereoWidth;
		if (stereoWidth < 0.0) { stereoWidth = stereoWidth / 2.0;}
		
		double leftImage = ((xnL * gain_L) - (xnR * gain_R)) * (stereoWidth / 100.0);
		double rightImage = ((xnR * gain_R) - (xnL * gain_L)) * (stereoWidth / 100.0);

		double ynL = (xnL * gain_L) + leftImage;
		double ynR = (xnR * gain_R) + rightImage;

		outputFrame[0] = ynL;
		if (outputChannels == 2) {
			outputFrame[1] = ynR;
		}

		parameters.outputMeterL = ynL;
		parameters.outputMeterR = ynR;
		
		return true;
	}

	/** get parameters: note use of custom structure for passing param data */
	/**
	\return AutoPanParameters custom data structure
	*/
	AutoPanParameters getParameters()
	{
		return parameters;
	}

	/** set parameters: note use of custom structure for passing param data */
	/**
	\param AutoPanParameters custom data structure
	*/
	void setParameters(const AutoPanParameters& params)
	{
		// --- copy them; note you may choose to ignore certain items
		//     and copy the variables one at a time, or you may test
		//     to see if cook-able variables have changed; if not, then
		//     do not re-cook them as it just wastes CPU
		parameters = params;

		// --- if dB = -60, then we shut off completely
		if (parameters.volume_dB == -60.0) {
			volumeCooked = 0.0;
		}
		else {
			volumeCooked = pow(10.0, parameters.volume_dB / 20.0);
		}

		// --- constant power panning
		if (parameters.panValue != prevParameters.panValue) {
			panValue_L = cos((parameters.panValue + 1.0) * (kPi / 4.0));
			panValue_R = sin((parameters.panValue + 1.0) * (kPi / 4.0));
		}

		prevParameters = parameters;
	}

private:
	AutoPanParameters parameters; ///< object parameters
	AutoPanParameters prevParameters; ///< previous frame's parameters

	SuperLFO LFOa;
	SuperLFO LFOb;
	SuperLFO LFOc;
	SuperLFO LFOd;

	SuperLFOParameters LFOaParams;
	SuperLFOParameters LFObParams;
	SuperLFOParameters LFOcParams;
	SuperLFOParameters LFOdParams;

	// --- local variables used by this object
	double sampleRate = 0.0;	///< sample rate

	double volumeCooked = 1.0; ///< unity gain
	double panValue_L = 0.707; ///< center cooked value
	double panValue_R = 0.707; ///< center cooked value

};

#endif