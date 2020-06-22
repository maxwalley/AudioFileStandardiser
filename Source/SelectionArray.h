/*
  ==============================================================================

    SelectionArray.h
    Created: 10 Jun 2020 12:36:38pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

template <class t>
class SelectionArray
{
public:
    SelectionArray(){};
    
    //Move constructor
    SelectionArray(SelectionArray&& otherArray) noexcept    :   objectArray(std::move(otherArray.objectArray)), selectedValues(std::move(otherArray.selectedValues))
    {
        
    }
    
    ~SelectionArray(){clear();};
    
    /**Adds a new object to the end of the array
     
     @param newObjectToAdd      The new object to add to the end of the array
     @param isSelected      Whether to set the corresponding bit to this object as true or false
     
     @returns A pointer to the new object
     */
    t* add(t* newObjectToAdd, bool isSelected)
    {
        int currentIndex = objectArray.size();
        
        objectArray.push_back(newObjectToAdd);
        selectedValues.setBit(currentIndex, isSelected);
        
        return objectArray[currentIndex];
    };
    
    t* insert(int index, t* newObjectToInsert, bool isSelected)
    {
        objectArray.insert(objectArray.begin()+index, newObjectToInsert);
        selectedValues.insertBit(index, isSelected);
        return objectArray[index];
    };
    
    t* set(int index, t* newObjectToSet, bool isSelected)
    {
        if(index < objectArray.size())
        {
            remove(index);
            insert(index, newObjectToSet, isSelected);
        }
        return nullptr;
    }
    
    void remove(int index)
    {
        BigInteger tempBitSet = selectedValues.getBitRange(0, index);
        
        for(int i = index + 1; i < objectArray.size(); i++)
        {
            tempBitSet.setBit(i-1, selectedValues[i]);
        }
        
        selectedValues = tempBitSet;
        
        delete objectArray[index];
        objectArray.erase(objectArray.begin()+index);
    };
    
    t* removeAndReturn(int index)
    {
        BigInteger tempBitSet = selectedValues.getBitRange(0, index);
        
        for(int i = index + 1; i < objectArray.size(); i++)
        {
            tempBitSet.setBit(i-1, selectedValues[i]);
        }
        
        selectedValues = tempBitSet;
        
        
        t* tempValue = objectArray[index];
        
        objectArray.erase(objectArray.begin()+index);
        
        return tempValue;
    }
    
    bool getIfSelected(int index)
    {
        return selectedValues[index];
    };
    
    void setIfSelected(int index, bool selected)
    {
        selectedValues.setBit(index, selected);
    };
    
    int getNumberOfItemsBasedOnSelection(bool selected)
    {
        int count = 0;
        
        for(int i = 0; i < objectArray.size(); i++)
        {
            if(selectedValues[i] == selected)
            {
                count++;
            }
        }
        return count;
    }
    
    /**ITEMS RETURNED BY THIS WILL STILL BE OWNED BY THE SELECTION ARRAY*/
    std::vector<t*> getItemsBasedOnSelection(bool selected)
    {
        std::vector<t*> tempArray;
        
        for(int i = 0; i < objectArray.size(); i++)
        {
            if(selectedValues[i] == selected)
            {
                tempArray.push_back(objectArray[i]);
            }
        }
        return tempArray;
    }
    
    /**Returns an item based on a selection based index. This means if a the array held 10 items but only 5 were selected the number of indexs would only go up to 5. If using this in a for statement I would use it in conjunction with getNumberOfItemsBasedOnSelection*/
    t* getItemFromSelectionBasedIndex(bool selected, int index)
    {
        std::vector<t*> tempArray = getItemsBasedOnSelection(selected);
        
        if(index < tempArray.size())
        {
            return tempArray[index];
        }
        
        return nullptr;
    }
    
    void removeItemsBasedOnSelection(bool selected)
    {
        for(int i = 0; i < objectArray.size(); i++)
        {
            if(getIfSelected(i) == selected)
            {
                remove(i);
            }
        }
    };
    
    void clear()
    {
        for(int i = 0; i < objectArray.size(); i++)
        {
            delete objectArray[i];
        }
        
        selectedValues.clear();
        objectArray.clear();
    };
    
    int size()
    {
        return objectArray.size();
    };
    
    int getIndexFor(t* objectToLookFor)
    {
        for(int i = 0; i < objectArray.size(); i++)
        {
            if(objectArray[i] == objectToLookFor)
            {
                return i;
            }
        }
        return -1;
    }
    
    int getFirstIndexBasedOnSelection(bool selection)
    {
        for(int i = 0; i < objectArray.size(); i++)
        {
            if(getIfSelected(i) == selection)
            {
                return i;
            }
        }
        return -1;
    }
    
    int getLastIndexBasedOnSelection(bool selection)
    {
        for(int i = objectArray.size() - 1; i >= 0; i--)
        {
            if(getIfSelected(i) == selection)
            {
                return i;
            }
        }
    }
    
    /* compare func works if first > seconds = 1, same = 0, less = -1*/
    // Uses insertion sort

    void sort(int (*compareFunc)(t* first, t* second))
    {
        for(int i = 1; i < objectArray.size(); i++)
        {
            bool rightPlaceFound = false;
            
            for(int j = i-1; rightPlaceFound == false; j--)
            {
                if(compareFunc(objectArray[j], objectArray[i]) == 1)
                {
                    if(j == 0 || compareFunc(objectArray[j-1], objectArray[i]) != 1)
                    {
                        rightPlaceFound = true;
                        
                        bool selectionOfObject = getIfSelected(i);
                        t* objectBeingMoved = removeAndReturn(i);
                        
                        insert(j, objectBeingMoved, selectionOfObject);
                    }
                }
                else
                {
                    rightPlaceFound = true;
                }
            }
            rightPlaceFound = true;
        }
    }
    
    t* operator[](int index)
    {
        return objectArray[index];
    };
    
    void operator-(int index)
    {
        setIfSelected(index, !getIfSelected(index));
    };
    
private:
    std::vector<t*> objectArray;
    BigInteger selectedValues;
};
