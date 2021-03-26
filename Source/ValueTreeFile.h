/*
  ==============================================================================

    ValueTreeFile.h
    Created: 26 Mar 2021 6:31:28pm
    Author:  https://forum.juce.com/t/save-restore-state-in-ios/33845/9

  ==============================================================================
*/

#ifndef _VALUE_TREE_FILE_H_
#define _VALUE_TREE_FILE_H_

#include "../JuceLibraryCode/JuceHeader.h"

// ValueTreeFile connects a ValueTree and a file, with auto-save functionality
//
// Auto-save is triggered when every anything in the ValueTree changes. The auto-save takes place
// on an independent thread, so as not to interrupt the message thread.
//
// To reduce the number of saves when there are many changes in a short period of time, it is a deferred
// save, waiting 'saveDelayTime' before doing the actual save. If second change happens
// the time is restarted. To keep a long series of rapid changes from keeping the save from
// happening, a save will be done if the total time since the first change exceeds maxSaveDelayTime.

class ValueTreeFile : private ValueTree::Listener,
                      private Timer,
                      private Thread
{
public:
    ValueTreeFile ();
    ValueTreeFile (ValueTree vt, File f, bool enableAutoSave);
    ~ValueTreeFile ();

    void init (ValueTree vt, File f, bool enableAutoSave);
    void save ();
    void load ();
    void requestAutoSave ();
    void setAutoSaveTimes (uint32 sdt, uint32 msdt);
    void enableAutoSave (bool isEnabled);

private:
    ValueTree vtData;
    File file;
    uint32 saveDelayTime    { 1000 };
    uint32 maxSaveDelayTime { 5000 };
    uint32 mostRecentSaveRequestedTime { 0 };
    uint32 initialSaveRequestedTime    { 0 };
    bool autoSaveEnabled { false };
    CriticalSection xmlDataCS;
    std::unique_ptr<XmlElement> xml;

    void save (XmlElement* xmlToWrite);
    void run () override;
    void valueTreePropertyChanged (ValueTree& treeWhosePropertyHasChanged, const Identifier& property) override;
    void valueTreeChildAdded (ValueTree& parentTree, ValueTree& childWhichHasBeenAdded) override;
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree& childWhichHasBeenRemoved, int indexFromWhichChildWasRemoved) override;
    void valueTreeChildOrderChanged (ValueTree& parentTreeWhoseChildrenHaveMoved, int oldIndex, int newIndex) override;
    void valueTreeParentChanged (ValueTree& treeWhoseParentHasChanged) override;
    void timerCallback () override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ValueTreeFile)
};

#endif // _VALUE_TREE_FILE_H_
