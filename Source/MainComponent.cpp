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
    valueTree = ValueTree("Ebeamer");
    initValueTreeParameters(valueTree);
    
    //==============================================================================
    /* OSC controller */
    oscController.init(valueTree);
    registerCommonOscParameters(oscController);
    oscController.initBroadcastReceiver(serversIdentifier);
    
    //==============================================================================
    /* Init GUI */
    auto app = JUCEApplication::getInstance();
    auto appVersion = app->getApplicationVersion();
    auto appName = app->getApplicationName();
    
    gui.initClient("Eventide",appName,appVersion,valueTree,valueTreePersistent,this);
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
        
        /* Subscribe to updates from the server server */
        oscController.subscribe();
        
        return true;
        
    }else{
        std::ostringstream errMsg;
        errMsg << "Error: could not connect to " << serverIp << " on " << String(serverPort);
        showConnectionErrorMessage (errMsg.str());
        
        return false;
    }
    
}

bool MainComponent::oscDisconnect(const String& serverIp, int serverPort){
    const Server srv({serverIp,serverPort});
    
    if (oscController.unsubscribe()){
        if (oscController.stopReceiver()){
            if (oscController.removeSender(srv)){
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
        showConnectionErrorMessage ("Error: could not unsubscribe");
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
