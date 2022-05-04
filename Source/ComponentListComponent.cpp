/*
  ==============================================================================

    ComponentListComponent.cpp
    Created: 30 Dec 2020 3:50:14pm
    Author:  Max Walley

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ComponentListComponent.h"

//==============================================================================

ComponentListComponent::ComponentListComponent()  : displayer(*this)
{
    displayHolder.setViewedComponent(&displayer, false);
    addAndMakeVisible(displayHolder);
}

void ComponentListComponent::resized()
{
    displayHolder.setBounds(getLocalBounds());
}

void ComponentListComponent::addComponent(std::unique_ptr<juce::Component> newComponent, int index)
{
    if(index < 0 || index > components.size())
    {
        index = components.size();
    }
    
    components.insert(components.begin() + index, std::move(newComponent));
    
    update();
}

void ComponentListComponent::removeComponent(int index)
{
    if(index >= 0 && index < components.size())
    {
        components.erase(components.begin() + index);
        update();
    }
}

juce::Component* ComponentListComponent::getComponentAtIndex(int index) const
{
    if(index >= 0 && index < components.size())
    {
        return components[index].get();
    }
    
    return nullptr;
}

void ComponentListComponent::ContentDisplayer::resized()
{
    int index = 0;
    
    for (juce::Component* component : getChildren())
    {
        component->setBounds(0, owner.componentHeight * index++, getWidth(), owner.componentHeight);
    }
}

void ComponentListComponent::update()
{
    bool oldVerticalShown = displayHolder.isVerticalScrollBarShown();
    
    //If the scroll bar is there make the components narrower
    int displayerWidth = oldVerticalShown ? getWidth() - 8 : getWidth();
    
    //If changing this size has made the scroll bar be shown or not we start function over again
    if (oldVerticalShown != displayHolder.isVerticalScrollBarShown())
    {
        update();
    }
    
    displayer.setSize(displayerWidth, componentHeight * components.size());
    
    //If displayer hasn't changed size
    if(previousDisplayerHeight == displayer.getHeight())
    {
        displayer.resized();
    }
    
    previousDisplayerHeight = displayer.getHeight();
}
