// -----------------------------------------------------------------------------
//    ASPiK Plugin Kernel File:  plugincore.cpp
//
/**
    \file   plugincore.cpp
    \author Will Pirkle
    \date   17-September-2018
    \brief  Implementation file for PluginCore object
    		- http://www.aspikplugins.com
    		- http://www.willpirkle.com
*/
// -----------------------------------------------------------------------------
#include "plugincore.h"
#include "plugindescription.h"

/**
\brief PluginCore constructor is launching pad for object initialization

Operations:
- initialize the plugin description (strings, codes, numbers, see initPluginDescriptors())
- setup the plugin's audio I/O channel support
- create the PluginParameter objects that represent the plugin parameters (see FX book if needed)
- create the presets
*/
PluginCore::PluginCore()
{
    // --- describe the plugin; call the helper to init the static parts you setup in plugindescription.h
    initPluginDescriptors();

    // --- default I/O combinations
	// --- for FX plugins
	if (getPluginType() == kFXPlugin)
	{
		addSupportedIOCombination({ kCFMono, kCFMono });
		addSupportedIOCombination({ kCFMono, kCFStereo });
		addSupportedIOCombination({ kCFStereo, kCFStereo });
	}
	else // --- synth plugins have no input, only output
	{
		addSupportedIOCombination({ kCFNone, kCFMono });
		addSupportedIOCombination({ kCFNone, kCFStereo });
	}

	// --- for sidechaining, we support mono and stereo inputs; auxOutputs reserved for future use
	addSupportedAuxIOCombination({ kCFMono, kCFNone });
	addSupportedAuxIOCombination({ kCFStereo, kCFNone });

	// --- create the parameters
    initPluginParameters();

    // --- create the presets
    initPluginPresets();
}

/**
\brief create all of your plugin parameters here

\return true if parameters were created, false if they already existed
*/
bool PluginCore::initPluginParameters()
{
	if (pluginParameterMap.size() > 0)
		return false;

    // --- Add your plugin parameter instantiation code bewtween these hex codes
	// **--0xDEA7--**


	// --- Declaration of Plugin Parameter Objects 
	PluginParameter* piParam = nullptr;

	// --- discrete control: LFO A Enable
	piParam = new PluginParameter(controlID::enableLFOa, "LFO A Enable", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&enableLFOa, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: LFO A Solo
	piParam = new PluginParameter(controlID::soloLFOa, "LFO A Solo", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&soloLFOa, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: LFO A Depth
	piParam = new PluginParameter(controlID::LFOaDepth, "LFO A Depth", "%", controlVariableType::kDouble, 0.000000, 100.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFOaDepth, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO A Rate
	piParam = new PluginParameter(controlID::LFOaRate, "LFO A Rate", "Hz", controlVariableType::kDouble, 0.020000, 20.000000, 0.020000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFOaRate, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO A Sync
	piParam = new PluginParameter(controlID::LFOaSyncToBPM, "LFO A Sync", "", controlVariableType::kInt, 0.000000, 6.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFOaSyncToBPM, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: LFO B Enable
	piParam = new PluginParameter(controlID::enableLFOb, "LFO B Enable", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&enableLFOb, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: LFO B Solo
	piParam = new PluginParameter(controlID::soloLFOb, "LFO B Solo", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&soloLFOb, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: LFO B Depth
	piParam = new PluginParameter(controlID::LFObDepth, "LFO B Depth", "%", controlVariableType::kDouble, 0.000000, 100.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFObDepth, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO B Rate
	piParam = new PluginParameter(controlID::LFObRate, "LFO B Rate", "Hz", controlVariableType::kDouble, 0.020000, 20.000000, 0.020000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFObRate, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO B Sync
	piParam = new PluginParameter(controlID::LFObSyncToBPM, "LFO B Sync", "", controlVariableType::kInt, 0.000000, 6.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFObSyncToBPM, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: LFO C Enable
	piParam = new PluginParameter(controlID::enableLFOc, "LFO C Enable", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&enableLFOc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: LFO C Solo
	piParam = new PluginParameter(controlID::soloLFOc, "LFO C Solo", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&soloLFOc, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: LFO C Depth
	piParam = new PluginParameter(controlID::LFOcDepth, "LFO C Depth", "%", controlVariableType::kDouble, 0.000000, 100.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFOcDepth, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO C Rate
	piParam = new PluginParameter(controlID::LFOcRate, "LFO C Rate", "Hz", controlVariableType::kDouble, 0.020000, 20.000000, 0.020000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFOcRate, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO C Sync
	piParam = new PluginParameter(controlID::LFOcSyncToBPM, "LFO C Sync", "", controlVariableType::kInt, 0.000000, 6.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFOcSyncToBPM, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- discrete control: LFO D Enable
	piParam = new PluginParameter(controlID::enableLFOd, "LFO D Enable", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&enableLFOd, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: LFO D Solo
	piParam = new PluginParameter(controlID::soloLFOd, "LFO D Solo", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&soloLFOd, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: LFO D Depth
	piParam = new PluginParameter(controlID::LFOdDepth, "LFO D Depth", "%", controlVariableType::kDouble, 0.000000, 100.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFOdDepth, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO D Rate
	piParam = new PluginParameter(controlID::LFOdRate, "LFO D Rate", "Hz", controlVariableType::kDouble, 0.020000, 20.000000, 0.020000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFOdRate, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO D Sync
	piParam = new PluginParameter(controlID::LFOdSyncToBPM, "LFO D Sync", "", controlVariableType::kInt, 0.000000, 6.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFOdSyncToBPM, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: Volume
	piParam = new PluginParameter(controlID::volume_dB, "Volume", "dB", controlVariableType::kDouble, -60.000000, 12.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&volume_dB, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- discrete control: Mute
	piParam = new PluginParameter(controlID::enableMute, "Mute", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&enableMute, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: M-S Decode
	piParam = new PluginParameter(controlID::enableMSdecode, "M-S Decode", "SWITCH OFF,SWITCH ON", "SWITCH OFF");
	piParam->setBoundVariable(&enableMSdecode, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- discrete control: Channels
	piParam = new PluginParameter(controlID::channelSelector, "Channels", "Stereo,Left,Right", "Stereo");
	piParam->setBoundVariable(&channelSelector, boundVariableType::kInt);
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- continuous control: Pan
	piParam = new PluginParameter(controlID::panValue, "Pan", "", controlVariableType::kDouble, -1.000000, 1.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&panValue, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- meter control: Output L
	piParam = new PluginParameter(controlID::outputMeterL, "Output L", 10.00, 100.00, ENVELOPE_DETECT_MODE_RMS, meterCal::kLinearMeter);
	piParam->setBoundVariable(&outputMeterL, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- meter control: Output R
	piParam = new PluginParameter(controlID::outputMeterR, "Output R", 10.00, 100.00, ENVELOPE_DETECT_MODE_RMS, meterCal::kLinearMeter);
	piParam->setBoundVariable(&outputMeterR, boundVariableType::kFloat);
	addPluginParameter(piParam);

	// --- continuous control: Stereo Width
	piParam = new PluginParameter(controlID::stereoWidth, "Stereo Width", "%", controlVariableType::kDouble, -100.000000, 100.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&stereoWidth, boundVariableType::kDouble);
	addPluginParameter(piParam);

	// --- continuous control: LFO A Waveform
	piParam = new PluginParameter(controlID::LFOaWaveform, "LFO A Waveform", "", controlVariableType::kInt, 0.000000, 3.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFOaWaveform, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: LFO B Waveform
	piParam = new PluginParameter(controlID::LFObWaveform, "LFO B Waveform", "", controlVariableType::kInt, 0.000000, 3.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFObWaveform, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: LFO C Waveform
	piParam = new PluginParameter(controlID::LFOcWaveform, "LFO C Waveform", "", controlVariableType::kInt, 0.000000, 3.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFOcWaveform, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: LFO D Waveform
	piParam = new PluginParameter(controlID::LFOdWaveform, "LFO D Waveform", "", controlVariableType::kInt, 0.000000, 3.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFOdWaveform, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: LFO A Phase
	piParam = new PluginParameter(controlID::LFOaPhase, "LFO A Phase", "", controlVariableType::kInt, 0.000000, 3.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFOaPhase, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: LFO B Phase
	piParam = new PluginParameter(controlID::LFObPhase, "LFO B Phase", "", controlVariableType::kInt, 0.000000, 3.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFObPhase, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: LFO C Phase
	piParam = new PluginParameter(controlID::LFOcPhase, "LFO C Phase", "", controlVariableType::kInt, 0.000000, 3.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFOcPhase, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- continuous control: LFO D Phase
	piParam = new PluginParameter(controlID::LFOdPhase, "LFO D Phase", "", controlVariableType::kInt, 0.000000, 3.000000, 0.000000, taper::kLinearTaper);
	piParam->setParameterSmoothing(false);
	piParam->setSmoothingTimeMsec(100.00);
	piParam->setBoundVariable(&LFOdPhase, boundVariableType::kInt);
	addPluginParameter(piParam);

	// --- BONUS Parameters
	// --- SCALE_GUI_SIZE
	piParam = new PluginParameter(SCALE_GUI_SIZE, "Scale GUI", "tiny,small,medium,normal,large,giant", "normal");
	piParam->setIsDiscreteSwitch(true);
	addPluginParameter(piParam);

	// --- Aux Attributes
	AuxParameterAttribute auxAttribute;

	// --- RAFX GUI attributes
	// --- controlID::enableLFOa
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741824);
	setParamAuxAttribute(controlID::enableLFOa, auxAttribute);

	// --- controlID::soloLFOa
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741824);
	setParamAuxAttribute(controlID::soloLFOa, auxAttribute);

	// --- controlID::LFOaDepth
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFOaDepth, auxAttribute);

	// --- controlID::LFOaRate
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFOaRate, auxAttribute);

	// --- controlID::LFOaSyncToBPM
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFOaSyncToBPM, auxAttribute);

	// --- controlID::enableLFOb
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741824);
	setParamAuxAttribute(controlID::enableLFOb, auxAttribute);

	// --- controlID::soloLFOb
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741824);
	setParamAuxAttribute(controlID::soloLFOb, auxAttribute);

	// --- controlID::LFObDepth
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFObDepth, auxAttribute);

	// --- controlID::LFObRate
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFObRate, auxAttribute);

	// --- controlID::LFObSyncToBPM
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFObSyncToBPM, auxAttribute);

	// --- controlID::enableLFOc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741824);
	setParamAuxAttribute(controlID::enableLFOc, auxAttribute);

	// --- controlID::soloLFOc
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741824);
	setParamAuxAttribute(controlID::soloLFOc, auxAttribute);

	// --- controlID::LFOcDepth
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFOcDepth, auxAttribute);

	// --- controlID::LFOcRate
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFOcRate, auxAttribute);

	// --- controlID::LFOcSyncToBPM
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFOcSyncToBPM, auxAttribute);

	// --- controlID::enableLFOd
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741824);
	setParamAuxAttribute(controlID::enableLFOd, auxAttribute);

	// --- controlID::soloLFOd
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741824);
	setParamAuxAttribute(controlID::soloLFOd, auxAttribute);

	// --- controlID::LFOdDepth
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFOdDepth, auxAttribute);

	// --- controlID::LFOdRate
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFOdRate, auxAttribute);

	// --- controlID::LFOdSyncToBPM
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFOdSyncToBPM, auxAttribute);

	// --- controlID::volume_dB
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::volume_dB, auxAttribute);

	// --- controlID::enableMute
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741824);
	setParamAuxAttribute(controlID::enableMute, auxAttribute);

	// --- controlID::enableMSdecode
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(1073741824);
	setParamAuxAttribute(controlID::enableMSdecode, auxAttribute);

	// --- controlID::channelSelector
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(268435456);
	setParamAuxAttribute(controlID::channelSelector, auxAttribute);

	// --- controlID::panValue
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::panValue, auxAttribute);

	// --- controlID::outputMeterL
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::outputMeterL, auxAttribute);

	// --- controlID::outputMeterR
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(201326592);
	setParamAuxAttribute(controlID::outputMeterR, auxAttribute);

	// --- controlID::stereoWidth
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::stereoWidth, auxAttribute);

	// --- controlID::LFOaWaveform
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFOaWaveform, auxAttribute);

	// --- controlID::LFObWaveform
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFObWaveform, auxAttribute);

	// --- controlID::LFOcWaveform
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFOcWaveform, auxAttribute);

	// --- controlID::LFOdWaveform
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFOdWaveform, auxAttribute);

	// --- controlID::LFOaPhase
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFOaPhase, auxAttribute);

	// --- controlID::LFObPhase
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFObPhase, auxAttribute);

	// --- controlID::LFOcPhase
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFOcPhase, auxAttribute);

	// --- controlID::LFOdPhase
	auxAttribute.reset(auxGUIIdentifier::guiControlData);
	auxAttribute.setUintAttribute(2147483648);
	setParamAuxAttribute(controlID::LFOdPhase, auxAttribute);


	// **--0xEDA5--**
   
    // --- BONUS Parameter
    // --- SCALE_GUI_SIZE
    PluginParameter* piParamBonus = new PluginParameter(SCALE_GUI_SIZE, "Scale GUI", "tiny,small,medium,normal,large,giant", "normal");
    addPluginParameter(piParamBonus);

	// --- create the super fast access array
	initPluginParameterArray();

    return true;
}

/**
\brief initialize object for a new run of audio; called just before audio streams

Operation:
- store sample rate and bit depth on audioProcDescriptor - this information is globally available to all core functions
- reset your member objects here

\param resetInfo structure of information about current audio format

\return true if operation succeeds, false otherwise
*/
bool PluginCore::reset(ResetInfo& resetInfo)
{
    // --- save for audio processing
    audioProcDescriptor.sampleRate = resetInfo.sampleRate;
    audioProcDescriptor.bitDepth = resetInfo.bitDepth;

    // --- other reset inits
	autoPan.reset(resetInfo.sampleRate);

    return PluginBase::reset(resetInfo);
}

/**
\brief one-time initialize function called after object creation and before the first reset( ) call

Operation:
- saves structure for the plugin to use; you can also load WAV files or state information here
*/
bool PluginCore::initialize(PluginInfo& pluginInfo)
{
	// --- add one-time init stuff here

	return true;
}

/**
\brief do anything needed prior to arrival of audio buffers

Operation:
- syncInBoundVariables when preProcessAudioBuffers is called, it is *guaranteed* that all GUI control change information
  has been applied to plugin parameters; this binds parameter changes to your underlying variables
- NOTE: postUpdatePluginParameter( ) will be called for all bound variables that are acutally updated; if you need to process
  them individually, do so in that function
- use this function to bulk-transfer the bound variable data into your plugin's member object variables

\param processInfo structure of information about *buffer* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::preProcessAudioBuffers(ProcessBufferInfo& processInfo)
{
    // --- sync internal variables to GUI parameters; you can also do this manually if you don't
    //     want to use the auto-variable-binding
    syncInBoundVariables();

    return true;
}

/**
\brief frame-processing method

Operation:
- decode the plugin type - for synth plugins, fill in the rendering code; for FX plugins, delete the if(synth) portion and add your processing code
- note that MIDI events are fired for each sample interval so that MIDI is tightly sunk with audio
- doSampleAccurateParameterUpdates will perform per-sample interval smoothing

\param processFrameInfo structure of information about *frame* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processAudioFrame(ProcessFrameInfo& processFrameInfo)
{
    // --- fire any MIDI events for this sample interval
    processFrameInfo.midiEventQueue->fireMidiEvents(processFrameInfo.currentFrame);

	// --- do per-frame updates; VST automation and parameter smoothing
	doSampleAccurateParameterUpdates();

	// --- update GUI params to object
	bpm = processFrameInfo.hostInfo->dBPM;

	updateParameters();
	// --- panman operates on frames! Our work here is easy!
	bool processed = autoPan.processAudioFrame(
		processFrameInfo.audioInputFrame,
		processFrameInfo.audioOutputFrame,
		processFrameInfo.numAudioInChannels,
		processFrameInfo.numAudioOutChannels);
	// --- the object will set its meter value, we just copy it 
	if (processed)
	{
		// --- get params
		AutoPanParameters params =
			autoPan.getParameters();
		// --- copy outbound data
		outputMeterL = params.outputMeterL;
		outputMeterR = params.outputMeterR;
		return processed;
	}

    return false; /// NOT processed
}


void PluginCore::updateParameters()
{
	// --- use get/set paradigm to transfer GUI controls to object
	AutoPanParameters params = autoPan.getParameters();
	// --- now modify

	params.bpm = bpm;

	params.enableLFOa = (enableLFOa == 1);
	params.enableLFOb = (enableLFOb == 1);
	params.enableLFOc = (enableLFOc == 1);
	params.enableLFOd = (enableLFOd == 1);

	params.soloLFOa = (soloLFOa == 1);
	params.soloLFOb = (soloLFOb == 1);
	params.soloLFOc = (soloLFOc == 1);
	params.soloLFOd = (soloLFOd == 1);

	params.LFOaWaveform = LFOaWaveform;
	params.LFObWaveform = LFObWaveform;
	params.LFOcWaveform = LFOcWaveform;
	params.LFOdWaveform = LFOdWaveform;
	 
	params.LFOaDepth = LFOaDepth;
	params.LFObDepth = LFObDepth;
	params.LFOcDepth = LFOcDepth;
	params.LFOdDepth = LFOdDepth;

	params.LFOaRate = LFOaRate;
	params.LFObRate = LFObRate;
	params.LFOcRate = LFOcRate;
	params.LFOdRate = LFOdRate;

	params.LFOaSyncToBPM = LFOaSyncToBPM;
	params.LFObSyncToBPM = LFObSyncToBPM;
	params.LFOcSyncToBPM = LFOcSyncToBPM;
	params.LFOdSyncToBPM = LFOdSyncToBPM;

	params.LFOaPhase = LFOaPhase;
	params.LFObPhase = LFObPhase;
	params.LFOcPhase = LFOcPhase;
	params.LFOdPhase = LFOdPhase;

	params.volume_dB = volume_dB;
	params.enableMute = (enableMute == 1);
	params.enableMSdecode = (enableMSdecode == 1);
	params.channelSelection = convertIntToEnum(channelSelector, channelSelectionEnum);
	params.panValue = panValue;
	params.outputMeterL = outputMeterL;
	params.outputMeterR = outputMeterR;
	params.stereoWidth = stereoWidth;

	// --- send back to object
	autoPan.setParameters(params);
}


/**
\brief do anything needed prior to arrival of audio buffers

Operation:
- updateOutBoundVariables sends metering data to the GUI meters

\param processInfo structure of information about *buffer* processing

\return true if operation succeeds, false otherwise
*/
bool PluginCore::postProcessAudioBuffers(ProcessBufferInfo& processInfo)
{
	// --- update outbound variables; currently this is meter data only, but could be extended
	//     in the future
	updateOutBoundVariables();

    return true;
}

/**
\brief update the PluginParameter's value based on GUI control, preset, or data smoothing (thread-safe)

Operation:
- update the parameter's value (with smoothing this initiates another smoothing process)
- call postUpdatePluginParameter to do any further processing

\param controlID the control ID value of the parameter being updated
\param controlValue the new control value
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::updatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo)
{
    // --- use base class helper
    setPIParamValue(controlID, controlValue);

    // --- do any post-processing
    postUpdatePluginParameter(controlID, controlValue, paramInfo);

    return true; /// handled
}

/**
\brief update the PluginParameter's value based on *normlaized* GUI control, preset, or data smoothing (thread-safe)

Operation:
- update the parameter's value (with smoothing this initiates another smoothing process)
- call postUpdatePluginParameter to do any further processing

\param controlID the control ID value of the parameter being updated
\param normalizedValue the new control value in normalized form
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::updatePluginParameterNormalized(int32_t controlID, double normalizedValue, ParameterUpdateInfo& paramInfo)
{
	// --- use base class helper, returns actual value
	double controlValue = setPIParamValueNormalized(controlID, normalizedValue, paramInfo.applyTaper);

	// --- do any post-processing
	postUpdatePluginParameter(controlID, controlValue, paramInfo);

	return true; /// handled
}

/**
\brief perform any operations after the plugin parameter has been updated; this is one paradigm for
	   transferring control information into vital plugin variables or member objects. If you use this
	   method you can decode the control ID and then do any cooking that is needed. NOTE: do not
	   overwrite bound variables here - this is ONLY for any extra cooking that is required to convert
	   the GUI data to meaninful coefficients or other specific modifiers.

\param controlID the control ID value of the parameter being updated
\param controlValue the new control value
\param paramInfo structure of information about why this value is being udpated (e.g as a result of a preset being loaded vs. the top of a buffer process cycle)

\return true if operation succeeds, false otherwise
*/
bool PluginCore::postUpdatePluginParameter(int32_t controlID, double controlValue, ParameterUpdateInfo& paramInfo)
{
    // --- now do any post update cooking; be careful with VST Sample Accurate automation
    //     If enabled, then make sure the cooking functions are short and efficient otherwise disable it
    //     for the Parameter involved
    /*switch(controlID)
    {
        case 0:
        {
            return true;    /// handled
        }

        default:
            return false;   /// not handled
    }*/

    return false;
}

/**
\brief has nothing to do with actual variable or updated variable (binding)

CAUTION:
- DO NOT update underlying variables here - this is only for sending GUI updates or letting you
  know that a parameter was changed; it should not change the state of your plugin.

WARNING:
- THIS IS NOT THE PREFERRED WAY TO LINK OR COMBINE CONTROLS TOGETHER. THE PROPER METHOD IS
  TO USE A CUSTOM SUB-CONTROLLER THAT IS PART OF THE GUI OBJECT AND CODE.
  SEE http://www.willpirkle.com for more information

\param controlID the control ID value of the parameter being updated
\param actualValue the new control value

\return true if operation succeeds, false otherwise
*/
bool PluginCore::guiParameterChanged(int32_t controlID, double actualValue)
{
	/*
	switch (controlID)
	{
		case controlID::<your control here>
		{

			return true; // handled
		}

		default:
			break;
	}*/

	return false; /// not handled
}

/**
\brief For Custom View and Custom Sub-Controller Operations

NOTES:
- this is for advanced users only to implement custom view and custom sub-controllers
- see the SDK for examples of use

\param messageInfo a structure containing information about the incoming message

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processMessage(MessageInfo& messageInfo)
{
	// --- decode message
	switch (messageInfo.message)
	{
		// --- add customization appearance here
	case PLUGINGUI_DIDOPEN:
	{
		return false;
	}

	// --- NULL pointers so that we don't accidentally use them
	case PLUGINGUI_WILLCLOSE:
	{
		return false;
	}

	// --- update view; this will only be called if the GUI is actually open
	case PLUGINGUI_TIMERPING:
	{
		return false;
	}

	// --- register the custom view, grab the ICustomView interface
	case PLUGINGUI_REGISTER_CUSTOMVIEW:
	{

		return false;
	}

	case PLUGINGUI_REGISTER_SUBCONTROLLER:
	case PLUGINGUI_QUERY_HASUSERCUSTOM:
	case PLUGINGUI_USER_CUSTOMOPEN:
	case PLUGINGUI_USER_CUSTOMCLOSE:
	case PLUGINGUI_EXTERNAL_SET_NORMVALUE:
	case PLUGINGUI_EXTERNAL_SET_ACTUALVALUE:
	{

		return false;
	}

	default:
		break;
	}

	return false; /// not handled
}


/**
\brief process a MIDI event

NOTES:
- MIDI events are 100% sample accurate; this function will be called repeatedly for every MIDI message
- see the SDK for examples of use

\param event a structure containing the MIDI event data

\return true if operation succeeds, false otherwise
*/
bool PluginCore::processMIDIEvent(midiEvent& event)
{
	return true;
}

/**
\brief (for future use)

NOTES:
- MIDI events are 100% sample accurate; this function will be called repeatedly for every MIDI message
- see the SDK for examples of use

\param vectorJoysickData a structure containing joystick data

\return true if operation succeeds, false otherwise
*/
bool PluginCore::setVectorJoystickParameters(const VectorJoystickData& vectorJoysickData)
{
	return true;
}

/**
\brief use this method to add new presets to the list

NOTES:
- see the SDK for examples of use
- for non RackAFX users that have large paramter counts, there is a secret GUI control you
  can enable to write C++ code into text files, one per preset. See the SDK or http://www.willpirkle.com for details

\return true if operation succeeds, false otherwise
*/
bool PluginCore::initPluginPresets()
{
	// **--0xFF7A--**

	// --- Plugin Presets 
	int index = 0;
	PresetInfo* preset = nullptr;

	// --- Preset: Factory Preset
	preset = new PresetInfo(index++, "Factory Preset");
	initPresetParameters(preset->presetParameters);
	setPresetParameter(preset->presetParameters, controlID::enableLFOa, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloLFOa, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFOaDepth, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFOaRate, 0.020000);
	setPresetParameter(preset->presetParameters, controlID::LFOaSyncToBPM, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableLFOb, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloLFOb, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFObDepth, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFObRate, 0.020000);
	setPresetParameter(preset->presetParameters, controlID::LFObSyncToBPM, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableLFOc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloLFOc, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFOcDepth, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFOcRate, 0.020000);
	setPresetParameter(preset->presetParameters, controlID::LFOcSyncToBPM, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableLFOd, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::soloLFOd, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFOdDepth, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFOdRate, 0.020000);
	setPresetParameter(preset->presetParameters, controlID::LFOdSyncToBPM, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::volume_dB, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableMute, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::enableMSdecode, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::channelSelector, -0.000000);
	setPresetParameter(preset->presetParameters, controlID::panValue, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::stereoWidth, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFOaWaveform, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFObWaveform, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFOcWaveform, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFOdWaveform, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFOaPhase, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFObPhase, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFOcPhase, 0.000000);
	setPresetParameter(preset->presetParameters, controlID::LFOdPhase, 0.000000);
	addPreset(preset);


	// **--0xA7FF--**

    return true;
}

/**
\brief setup the plugin description strings, flags and codes; this is ordinarily done through the ASPiKreator or CMake

\return true if operation succeeds, false otherwise
*/
bool PluginCore::initPluginDescriptors()
{
    pluginDescriptor.pluginName = PluginCore::getPluginName();
    pluginDescriptor.shortPluginName = PluginCore::getShortPluginName();
    pluginDescriptor.vendorName = PluginCore::getVendorName();
    pluginDescriptor.pluginTypeCode = PluginCore::getPluginType();

	// --- describe the plugin attributes; set according to your needs
	pluginDescriptor.hasSidechain = kWantSidechain;
	pluginDescriptor.latencyInSamples = kLatencyInSamples;
	pluginDescriptor.tailTimeInMSec = kTailTimeMsec;
	pluginDescriptor.infiniteTailVST3 = kVSTInfiniteTail;

    // --- AAX
    apiSpecificInfo.aaxManufacturerID = kManufacturerID;
    apiSpecificInfo.aaxProductID = kAAXProductID;
    apiSpecificInfo.aaxBundleID = kAAXBundleID;  /* MacOS only: this MUST match the bundle identifier in your info.plist file */
    apiSpecificInfo.aaxEffectID = "aaxDeveloper.";
    apiSpecificInfo.aaxEffectID.append(PluginCore::getPluginName());
    apiSpecificInfo.aaxPluginCategoryCode = kAAXCategory;

    // --- AU
    apiSpecificInfo.auBundleID = kAUBundleID;   /* MacOS only: this MUST match the bundle identifier in your info.plist file */

    // --- VST3
    apiSpecificInfo.vst3FUID = PluginCore::getVSTFUID(); // OLE string format
    apiSpecificInfo.vst3BundleID = kVST3BundleID;/* MacOS only: this MUST match the bundle identifier in your info.plist file */
	apiSpecificInfo.enableVST3SampleAccurateAutomation = kVSTSAA;
	apiSpecificInfo.vst3SampleAccurateGranularity = kVST3SAAGranularity;

    // --- AU and AAX
    apiSpecificInfo.fourCharCode = PluginCore::getFourCharCode();

    return true;
}

// --- static functions required for VST3/AU only --------------------------------------------- //
const char* PluginCore::getPluginBundleName() { return kAUBundleName; }
const char* PluginCore::getPluginName(){ return kPluginName; }
const char* PluginCore::getShortPluginName(){ return kShortPluginName; }
const char* PluginCore::getVendorName(){ return kVendorName; }
const char* PluginCore::getVendorURL(){ return kVendorURL; }
const char* PluginCore::getVendorEmail(){ return kVendorEmail; }
const char* PluginCore::getAUCocoaViewFactoryName(){ return AU_COCOA_VIEWFACTORY_STRING; }
pluginType PluginCore::getPluginType(){ return kPluginType; }
const char* PluginCore::getVSTFUID(){ return kVSTFUID; }
int32_t PluginCore::getFourCharCode(){ return kFourCharCode; }
