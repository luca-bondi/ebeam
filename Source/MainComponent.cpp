#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    
    
    //==============================================================================
    /* Value Tree*/
    statusFile = File::getSpecialLocation(File::userDocumentsDirectory).getChildFile("EbeaMote.xml");
    valueTreePersistent = ValueTree("EbeaMote");
    valueTreeFile.init(valueTreePersistent, statusFile, true);
    
    if (!valueTreeFile.load()){
        /** Initialize value tree if not loaded */
        valueTreePersistent.setProperty(serverIpIdentifier, "", nullptr);
        valueTreePersistent.setProperty(serverPortIdentifier, 9001, nullptr);
        valueTreeFile.save();
    }

    /* Value tree for session parameters */
    valueTree = ValueTree("EbeaMoteTmp");
    
    //==============================================================================
    /* OSC controller */
    oscController.init(valueTree);
    oscController.initBroadcastReceiver(serversIdentifier);
    
    //==============================================================================
    /* Value Tree parameters */
    
    valueTree.setProperty(configIdentifier,ULA_1ESTICK,nullptr);
    oscController.registerIdentifier(configIdentifier);
    
    valueTree.setProperty(frontIdentifier,false,nullptr);
    oscController.registerIdentifier(frontIdentifier);
    
    valueTree.setProperty(cpuIdentifier,0,nullptr);
    oscController.registerIdentifier(cpuIdentifier);
    
    valueTree.setProperty(hpfIdentifier,150,nullptr);
    oscController.registerIdentifier(hpfIdentifier);
    
    valueTree.setProperty(gainIdentifier,20,nullptr);
    oscController.registerIdentifier(gainIdentifier);
    
    valueTree.setProperty(steerX1Identifier,-0.2,nullptr);
    oscController.registerIdentifier(steerX1Identifier);
    
    valueTree.setProperty(steerX2Identifier,0.2,nullptr);
    oscController.registerIdentifier(steerX2Identifier);
    
    valueTree.setProperty(steerY1Identifier,-0.2,nullptr);
    oscController.registerIdentifier(steerY1Identifier);
    
    valueTree.setProperty(steerY2Identifier,0.2,nullptr);
    oscController.registerIdentifier(steerY2Identifier);
    
    valueTree.setProperty(width1Identifier,0.2,nullptr);
    oscController.registerIdentifier(width1Identifier);
    
    valueTree.setProperty(width2Identifier,0.4,nullptr);
    oscController.registerIdentifier(width2Identifier);
    
    valueTree.setProperty(pan1Identifier,-0.5,nullptr);
    oscController.registerIdentifier(pan1Identifier);
    
    valueTree.setProperty(pan2Identifier,0.5,nullptr);
    oscController.registerIdentifier(pan2Identifier);
    
    valueTree.setProperty(level1Identifier,-4,nullptr);
    oscController.registerIdentifier(level1Identifier);
    
    valueTree.setProperty(level2Identifier,4,nullptr);
    oscController.registerIdentifier(level2Identifier);
    
    valueTree.setProperty(mute1Identifier,false,nullptr);
    oscController.registerIdentifier(mute1Identifier);
    
    valueTree.setProperty(mute2Identifier,true,nullptr);
    oscController.registerIdentifier(mute2Identifier);
    
    Array<var> inMetersInit(0,0,0,0);
    valueTree.setProperty(inMetersIdentifier,inMetersInit,nullptr);
    oscController.registerIdentifier(inMetersIdentifier);
    
    valueTree.setProperty(outMeter1Identifier,0,nullptr);
    oscController.registerIdentifier(outMeter1Identifier);
    
    valueTree.setProperty(outMeter2Identifier,0,nullptr);
    oscController.registerIdentifier(outMeter2Identifier);

    Array<var> energyInit;
    energyInit.resize(1);
    energyInit.set(0, Array<var>(0,0,0,0,0,0,0,0,0));
    valueTree.setProperty(energyIdentifier,energyInit,nullptr);
    oscController.registerIdentifier(energyIdentifier);
    
    //==============================================================================
    /* Init GUI */
    auto app = JUCEApplication::getInstance();
    auto appVersion = app->getApplicationVersion();
    auto appName = app->getApplicationName();
    
    gui.init("Eventide",appName,appVersion,valueTree,valueTreePersistent,CLIENT,this);
    addAndMakeVisible(gui);
    
    //==============================================================================
    setSize(MIN_WIDTH, MIN_HEIGHT);
    
}

MainComponent::~MainComponent()
{
    
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    gui.setBounds(getLocalBounds());
}

//=====================================================================================
//OSC Methods

bool MainComponent::oscConnect(const String& serverIp, int serverPort){
    
    const Server srv = {serverIp, serverPort};
    if (oscController.addSender(srv)){
        
        if(!oscController.startReceiver())
            return false;
        
        /* Connection successful */
        connected = true;
        
        /* Start polling */
        oscController.startPolling(srv, oscPollingFreq);
        
        return true;
        
    }else{
        std::ostringstream errMsg;
        errMsg << "Error: cannot connect to " << serverIp << " on " << String(serverPort);
        showConnectionErrorMessage (errMsg.str());
        
        return false;
    }
    
}

bool MainComponent::oscDisconnect(const String& serverIp, int serverPort){
    if (oscController.stopPolling()){
        if (oscController.stopReceiver()){
            if (oscController.removeSender({serverIp,serverPort})){
                connected = false;
                /* Reset graphic components */
                valueTree.setProperty(cpuIdentifier, 0, nullptr);
                return true;
            }else{
                showConnectionErrorMessage ("Error: could not remove sender");
                return false;
            }
        }else{
            showConnectionErrorMessage ("Error: could not disconnect receiver");
            return false;
        }
    }else{
        showConnectionErrorMessage ("Error: could not stop polling");
        return false;
    }
}


void MainComponent::showConnectionErrorMessage (const String& messageText){
    juce::AlertWindow::showMessageBoxAsync (AlertWindow::WarningIcon,
                                            "OSC error",
                                            messageText,
                                            "OK");
}

bool MainComponent::isConnected() const{
    return connected;
}
