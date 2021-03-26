/*
  ==============================================================================

    ValueTreeFile.cpp
    Created: 26 Mar 2021 6:31:28pm
 Author:  https://forum.juce.com/t/save-restore-state-in-ios/33845/9

  ==============================================================================
*/

#include "ValueTreeFile.h"

ValueTreeFile::ValueTreeFile ()
    : Thread ("ValueTreeFile")
{
}

ValueTreeFile::ValueTreeFile (ValueTree vt, File f, bool enableAutoSave)
    : ValueTreeFile ()
{
    init (vt, f, enableAutoSave);
}

ValueTreeFile::~ValueTreeFile ()
{
    stopThread (5000);
    vtData.removeListener (this);
}

void ValueTreeFile::init (ValueTree vt, File f, bool enableAutoSave)
{
    vtData = vt;
    file = f;
    autoSaveEnabled = enableAutoSave;
    vtData.addListener (this);
    load ();
}

void ValueTreeFile::enableAutoSave (bool isEnabled)
{
    const auto wasEnabled = autoSaveEnabled;
    autoSaveEnabled = isEnabled;

    // if toggling from disabled to enabled, then request a delayed save
    if (! wasEnabled && isEnabled)
        requestAutoSave ();
}

void ValueTreeFile::save ()
{
    auto xmlToWrite = vtData.createXml ();
    save (xmlToWrite.get ());
}

void ValueTreeFile::save (XmlElement* xmlToWrite)
{
    xmlToWrite->writeTo (file, {});
}

void ValueTreeFile::load ()
{
    if (file.exists ())
    {
        XmlDocument xmlDoc (file);
        auto xmlToRead = xmlDoc.getDocumentElement ();
        vtData.copyPropertiesAndChildrenFrom (ValueTree::fromXml (*xmlToRead), nullptr);
    }
}

void ValueTreeFile::setAutoSaveTimes (uint32 sdt, uint32 msdt)
{
    saveDelayTime = sdt;
    maxSaveDelayTime = jmax (sdt, msdt);
}

void ValueTreeFile::requestAutoSave ()
{
    if (autoSaveEnabled)
    {
        if (initialSaveRequestedTime == 0)
        {
            startTimer (saveDelayTime / 2);
            initialSaveRequestedTime = Time::getMillisecondCounter ();
        }
        mostRecentSaveRequestedTime = Time::getMillisecondCounter ();
    }
}

void ValueTreeFile::timerCallback ()
{
    const uint32 curTime = Time::getMillisecondCounter ();
    if (curTime - mostRecentSaveRequestedTime >= saveDelayTime ||
        curTime - initialSaveRequestedTime >= maxSaveDelayTime)
    {
        ScopedLock xmlLock (xmlDataCS);
        if (xml.get () == nullptr)
        {
            stopTimer ();
            xml = vtData.createXml ();
            startThread ();
            initialSaveRequestedTime = 0;
        }
    }
}

void ValueTreeFile::run ()
{
    if (! threadShouldExit ())
    {
        std::unique_ptr<XmlElement> xmlToWrite;
        {
            ScopedLock xmlLock (xmlDataCS);
            xmlToWrite.reset (xml.release ());
        }
        if (xmlToWrite.get () != nullptr)
            save (xmlToWrite.get ());
    }
}

void ValueTreeFile::valueTreePropertyChanged (ValueTree& , const Identifier&)
{
    requestAutoSave ();
}
void ValueTreeFile::valueTreeChildAdded (ValueTree& , ValueTree&)
{
    requestAutoSave ();
}
void ValueTreeFile::valueTreeChildRemoved (ValueTree& , ValueTree& , int)
{
    requestAutoSave ();
}
void ValueTreeFile::valueTreeChildOrderChanged (ValueTree& , int , int)
{
    requestAutoSave ();
}
void ValueTreeFile::valueTreeParentChanged (ValueTree&)
{
    requestAutoSave ();
}
