// -----------------------------------------------------------------------------
//    ASPiK Plugin Kernel File:  plugincore.h
//
/**
    \file   plugincore.h
    \author Will Pirkle
    \date   17-September-2018
    \brief  base class interface file for ASPiK plugincore object
    		- http://www.aspikplugins.com
    		- http://www.willpirkle.com
*/
// -----------------------------------------------------------------------------
#ifndef __pluginCore_h__
#define __pluginCore_h__

#include "pluginbase.h"
#include "autopan.h"


// **--0x7F1F--**

// --- Plugin Variables controlID Enumeration 

enum controlID {
	enableLFOa = 0,
	soloLFOa = 1,
	LFOaDepth = 3,
	LFOaRate = 4,
	LFOaSyncToBPM = 5,
	enableLFOb = 10,
	soloLFOb = 11,
	LFObDepth = 13,
	LFObRate = 14,
	LFObSyncToBPM = 15,
	enableLFOc = 20,
	soloLFOc = 21,
	LFOcDepth = 23,
	LFOcRate = 24,
	LFOcSyncToBPM = 25,
	enableLFOd = 30,
	soloLFOd = 31,
	LFOdDepth = 33,
	LFOdRate = 34,
	LFOdSyncToBPM = 35,
	volume_dB = 40,
	enableMute = 41,
	enableMSdecode = 42,
	channelSelector = 43,
	panValue = 44,
	outputMeterL = 45,
	outputMeterR = 46,
	stereoWidth = 47,
	LFOaWaveform = 2,
	LFObWaveform = 12,
	LFOcWaveform = 22,
	LFOdWaveform = 32,
	LFOaPhase = 6,
	LFObPhase = 16,
	LFOcPhase = 26,
	LFOdPhase = 36
};

	// **--0x0F1F--**

/**
\class PluginCore
\ingroup ASPiK-Core
\brief
The PluginCore object is the default PluginBase derived object for ASPiK projects.
Note that you are fre to change the name of this object (as long as you change it in the compiler settings, etc...)


PluginCore Operations:
- overrides the main processing functions from the base class
- performs reset operation on sub-modules
- processes audio
- processes messages for custom views
- performs pre and post processing functions on parameters and audio (if needed)

\author Will Pirkle http://www.willpirkle.com
\remark This object is included in Designing Audio Effects Plugins in C++ 2nd Ed. by Will Pirkle
\version Revision : 1.0
\date Date : 2018 / 09 / 7
*/
class PluginCore : public PluginBase
{
public:
    PluginCore();

	/** Destructor: empty in default version */
    virtual ~PluginCore(){}

	// --- PluginBase Overrides ---
	//
	/** this is the creation function for all plugin parameters */
	bool initPluginParameters();

	/** called when plugin is loaded, a new audio file is playing or sample rate changes */
	virtual bool reset(ResetInfo& resetInfo);

	/** one-time post creation init function; pluginInfo contains path to this plugin */
	virtual bool initialize(PluginInfo& _pluginInfo);

	// --- preProcess: sync GUI parameters here; override if you don't want to use automatic variable-binding
	virtual bool preProcessAudioBuffers(ProcessBufferInfo& processInfo);

	/** process frames of data */
	virtual bool processAudioFrame(ProcessFrameInfo& processFrameInfo);

	// --- uncomment and override this for buffer processing; see base class implementation for
	//     help on breaking up buffers and getting info from processBufferInfo
	//virtual bool processAudioBuffers(ProcessBufferInfo& processBufferInfo);

	/** preProcess: do any post-buffer processing required; default operation is to send metering data to GUI  */
	virtual bool postProcessAudioBuffers(ProcessBufferInfo& processInfo);

	/** called by host plugin at top of buffer proccess; this alters parameters prior to variable binding operation  */
	virtual bool updatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo);

	/** called by host plugin at top of buffer proccess; this alters parameters prior to variable binding operation  */
	virtual bool updatePluginParameterNormalized(int32_t controlID, double normalizedValue, ParameterUpdateInfo& paramInfo);

	/** this can be called: 1) after bound variable has been updated or 2) after smoothing occurs  */
	virtual bool postUpdatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo);

	/** this is ony called when the user makes a GUI control change */
	virtual bool guiParameterChanged(int32_t controlID, double actualValue);

	/** processMessage: messaging system; currently used for custom/special GUI operations */
	virtual bool processMessage(MessageInfo& messageInfo);

	/** processMIDIEvent: MIDI event processing */
	virtual bool processMIDIEvent(midiEvent& event);

	/** specialized joystick servicing (currently not used) */
	virtual bool setVectorJoystickParameters(const VectorJoystickData& vectorJoysickData);

	/** create the presets */
	bool initPluginPresets();

	// --- BEGIN USER VARIABLES AND FUNCTIONS -------------------------------------- //
	//	   Add your variables and methods here
	AutoPan autoPan;
	// --- GUI -> Object transfer function
	void updateParameters();


	// --- END USER VARIABLES AND FUNCTIONS -------------------------------------- //

private:
	//  **--0x07FD--**

	// --- Continuous Plugin Variables 
	double LFOaDepth = 0.0;
	double LFOaRate = 0.0;
	int LFOaSyncToBPM = 0;
	double LFObDepth = 0.0;
	double LFObRate = 0.0;
	int LFObSyncToBPM = 0;
	double LFOcDepth = 0.0;
	double LFOcRate = 0.0;
	int LFOcSyncToBPM = 0;
	double LFOdDepth = 0.0;
	double LFOdRate = 0.0;
	int LFOdSyncToBPM = 0;
	double volume_dB = 0.0;
	double panValue = 0.0;
	double stereoWidth = 0.0;
	int LFOaWaveform = 0;
	int LFObWaveform = 0;
	int LFOcWaveform = 0;
	int LFOdWaveform = 0;
	int LFOaPhase = 0;
	int LFObPhase = 0;
	int LFOcPhase = 0;
	int LFOdPhase = 0;

	// --- Discrete Plugin Variables 
	int enableLFOa = 0;
	enum class enableLFOaEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(enableLFOaEnum::SWITCH_OFF, enableLFOa)) etc... 

	int soloLFOa = 0;
	enum class soloLFOaEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(soloLFOaEnum::SWITCH_OFF, soloLFOa)) etc... 

	int enableLFOb = 0;
	enum class enableLFObEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(enableLFObEnum::SWITCH_OFF, enableLFOb)) etc... 

	int soloLFOb = 0;
	enum class soloLFObEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(soloLFObEnum::SWITCH_OFF, soloLFOb)) etc... 

	int enableLFOc = 0;
	enum class enableLFOcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(enableLFOcEnum::SWITCH_OFF, enableLFOc)) etc... 

	int soloLFOc = 0;
	enum class soloLFOcEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(soloLFOcEnum::SWITCH_OFF, soloLFOc)) etc... 

	int enableLFOd = 0;
	enum class enableLFOdEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(enableLFOdEnum::SWITCH_OFF, enableLFOd)) etc... 

	int soloLFOd = 0;
	enum class soloLFOdEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(soloLFOdEnum::SWITCH_OFF, soloLFOd)) etc... 

	int enableMute = 0;
	enum class enableMuteEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(enableMuteEnum::SWITCH_OFF, enableMute)) etc... 

	int enableMSdecode = 0;
	enum class enableMSdecodeEnum { SWITCH_OFF,SWITCH_ON };	// to compare: if(compareEnumToInt(enableMSdecodeEnum::SWITCH_OFF, enableMSdecode)) etc... 

	int channelSelector = 0;
	enum class channelSelectorEnum { Stereo,Left,Right };	// to compare: if(compareEnumToInt(channelSelectorEnum::Stereo, channelSelector)) etc... 

	// --- Meter Plugin Variables
	float outputMeterL = 0.f;
	float outputMeterR = 0.f;

	// **--0x1A7F--**
    // --- end member variables

	double bpm;

public:
    /** static description: bundle folder name

	\return bundle folder name as a const char*
	*/
    static const char* getPluginBundleName();

    /** static description: name

	\return name as a const char*
	*/
    static const char* getPluginName();

	/** static description: short name

	\return short name as a const char*
	*/
	static const char* getShortPluginName();

	/** static description: vendor name

	\return vendor name as a const char*
	*/
	static const char* getVendorName();

	/** static description: URL

	\return URL as a const char*
	*/
	static const char* getVendorURL();

	/** static description: email

	\return email address as a const char*
	*/
	static const char* getVendorEmail();

	/** static description: Cocoa View Factory Name

	\return Cocoa View Factory Name as a const char*
	*/
	static const char* getAUCocoaViewFactoryName();

	/** static description: plugin type

	\return type (FX or Synth)
	*/
	static pluginType getPluginType();

	/** static description: VST3 GUID

	\return VST3 GUID as a const char*
	*/
	static const char* getVSTFUID();

	/** static description: 4-char code

	\return 4-char code as int
	*/
	static int32_t getFourCharCode();

	/** initalizer */
	bool initPluginDescriptors();

};




#endif /* defined(__pluginCore_h__) */
