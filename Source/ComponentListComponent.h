/*
  ==============================================================================

    ComponentListComponent.h
    Created: 30 Dec 2020 3:50:14pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
//Remove
class TestCom  : public juce::Component
{
public:
    TestCom(){DBG("Constructed");};
    ~TestCom(){};
    
    void paint(juce::Graphics& g) override {g.fillAll(juce::Colours::brown);};
};

class ComponentListComponent  : public juce::Component
{
public:
    ComponentListComponent();
    ~ComponentListComponent(){};

    void resized() override;
    
    int getNumComponents() const {return components.size();};
    
    //-1 index means move to the back
    void addComponent(std::unique_ptr<juce::Component> newComponent, int index = -1);
    
    void removeComponent(int index);
    
    juce::Component* getComponentAtIndex(int index) const;
    
    void setComponentHeight(int newHeight) {componentHeight = newHeight;};
    int getComponentHeight() const {return componentHeight;};
    
    void update();
    
    //This is available to allow iteration etc and functions that are not available through this interface. Just make sure to call update() if anything changes.
    std::vector<std::unique_ptr<juce::Component>> components;

private:
    
    class ContentDisplayer  : public juce::Component
    {
    public:
        ContentDisplayer(ComponentListComponent& parent)  : owner(parent){};
        ~ContentDisplayer(){};
        
        void resized() override;
        
    private:
        ComponentListComponent& owner;
    };
    
    ContentDisplayer displayer;
    juce::Viewport displayHolder;
    
    int componentHeight = 30;
    
    int previousDisplayerHeight = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ComponentListComponent)
};
