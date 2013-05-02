/*[ Compilation unit -----------------------------------------------
Component       : RAD – Image Processing(IP)
Name            : ShaderProgramManager
Author          : Lindholm S, SCR, Princeton
Language        : C++ Source File
Creation Date   : 2-Oct-2007
ClearCaseInfo   : ClearCase $Version$ Tag
Test State      : %Q%
Description     : Class Declaration/Definition.
                  Singleton class providing support
                  for a shader manager that handles
                  all compiled and linked shaders.
Requirement Keys: 
Internals       : 
History         : 
Copyright © Siemens AG 2006-2007. All Rights Reserved.
-----------------------------------------------------------------*/


#include <xip/inventor/coregl/ShaderProgramManager.h>
#include <stdlib.h>
#include <string.h>

#include <map>

class cstrlessthan {
public:
    bool operator() (const char * lhs, const char* rhs) const
    {
        if (lhs == rhs) return false;

        return strcmp(lhs, rhs) < 0;
    }
};

// let's avoid declaring anything using STL in the header due to export/import issues
// we simply allocate the property list dynamically
class ShaderProgramManager::EntryMap :
    public std::map<char *, ShaderProgramManager::ShaderEntry *, cstrlessthan>
{
};


//#pragma warning( push )
//#pragma warning( disable : 4996 )


/**
 * Definition of static instance variable.
 */
ShaderProgramManager * ShaderProgramManager::mInstance = 0;

/**
 * Class initiator.
 */
void ShaderProgramManager::initClass()
{
    // The skeleton exists due to Invetor methology
}

/**
 * Instance manager.
 */
ShaderProgramManager * ShaderProgramManager::getInstance()
{
    if (!mInstance)
        mInstance = new ShaderProgramManager;

    return mInstance;
}

/**
 * Constructor.
 */
ShaderProgramManager::ShaderProgramManager()
{
    mEntryMap = new EntryMap;
}

/**
 * Destructor.
 * Frees the singleton instance.
 */
ShaderProgramManager::~ShaderProgramManager()
{
    ShaderProgramManager * singleton = mInstance;
    mInstance = 0;

    if (mEntryMap) {
        deleteAllEntries();
        delete mEntryMap;
        mEntryMap = 0;
    }

    // Delete the singleton if that's not us...
    if (singleton != this && singleton)
        delete singleton;
}


void ShaderProgramManager::deleteAllEntries()
{
#if 1
    if (!mEntryMap) return;

    while (!mEntryMap->empty()) {
        EntryMap::iterator it = mEntryMap->begin();

        free(it->first);
        // Should/could we delete program?
        free(it->second);

        mEntryMap->erase(it);
    }
#else
    ShaderEntry * entry = mEntryListAnchor;
    ShaderEntry * tmp = 0;
    while (entry)
    {
        tmp = entry->next;
        delete entry;
        entry = tmp;
    }
    mEntryListAnchor = 0;
#endif
}

/**
 * Creating or Modifying an entry.
 *
 * The function is used for both modifying an existing entry or if no
 * entry exists to create e new one.
 *
 * There are several possible cases here:
 *
 * 1. If the tag is not previously in the list, return the program handle
 * being added (newProgramHandle).
 *
 * 2. If the tag already exists, return the previous handle.
 *
 * 3. Zero is returned if the tag is empty (null or zero length)
 *
 * @param newTag Requested tag for entry.
 * @param newProgramHandle New program handle.
 * @param newTimeStamp New time stamp.
 * @see removeEntry()
 * @return Returns handle to program associated with entry (in case of a replacement the old handle is returned).
 */
unsigned int
ShaderProgramManager::insertEntry(const char * newTag,
                                  unsigned int newProgramHandle,
                                  __uint64 newTimeStamp)
{
    // Check invalid tag
    if (!newTag || !*newTag)
        return 0;

    ShaderEntry * newEntry = 0;     // New entry
    ShaderEntry * oldEntry = 0;     // Existing entry with same tag
    ShaderEntry * obsEntry = 0;     // Obsolete entry
    unsigned int returnID = 0;      // Return code

    // Find existing tag
    oldEntry = findEntry(newTag);

    if (oldEntry) {
        // Update existing entry
        returnID = oldEntry->programHandle;

        oldEntry->programHandle = newProgramHandle;
        oldEntry->timeStamp = newTimeStamp;
    }
    else {
        // Create new entry
        newEntry = reinterpret_cast<ShaderEntry *>(calloc(1, sizeof(ShaderEntry)));
        newEntry->tag = strdup(newTag);
        newEntry->programHandle = newProgramHandle;
        newEntry->timeStamp = newTimeStamp;
#if 1
        (*mEntryMap)[newEntry->tag] = newEntry;
#else
        // Push entry to list
        if (mEntryListAnchor) {
            mEntryListAnchor->prev = newEntry;
            newEntry->next = mEntryListAnchor;
        }
        mEntryListAnchor = newEntry;
#endif
        returnID = newProgramHandle;
    }

    return returnID;
}

/**
 * Removing entries.
 * Note that this function does not destroy or even disables the entry program.
 * It is up to the user to do so and therefor the program handle is returned.
 * @param iSearchTag Tag for requested entry.
 * @see insertEntry()
 * @return Returns handle to program associated with entry.
 */
unsigned int ShaderProgramManager::removeEntry(const char * iSearchTag)
{
    unsigned int oProgramHandle = 0;

    if (!iSearchTag) return 0;

    EntryMap::iterator it = mEntryMap->find(const_cast<char *>(iSearchTag));

    if (it != mEntryMap->end()) {
        oProgramHandle = it->second->programHandle;

        free(it->first);
        free(it->second);

        mEntryMap->erase(it);
    }
#if 0
    // Find shader
    ShaderEntry * entry = findEntry(iSearchTag);

    // Relink and destroy
    if (entry) {
        ShaderEntry * oPrev = entry->prev;
        ShaderEntry * oNext = entry->next;
        if (oPrev)
            oPrev->next = entry->next;
        else
            mEntryListAnchor = oNext;
        if (oNext)
            oNext->prev = entry->prev;

        oProgramHandle = entry->programHandle;
#if 1
        free(entry->tag);
        entry->tag = 0;
        free(entry);
        entry = 0;
#endif
    }
#endif

    return oProgramHandle;
}

/**
 * Get function for entire entry.
 * Use only if getProgramHandle and getTimeStamp is insufficient.
 * @param iSearchTag Tag for requested entry.
 * @see getProgramHandle()
 * @see getTimeStamp()
 * @return Returns pointer to entry.
 */
ShaderProgramManager::ShaderEntry * ShaderProgramManager::getEntry(const char * iSearchTag)
{
    // Find shader entry
    ShaderEntry * entry = findEntry(iSearchTag);
    return entry;
}

/**
 * Get function for program handle in entry.
 * @param iSearchTag Tag for requested entry.
 * @return Returns handle.
 * @see getTimeStamp()
 */
unsigned int ShaderProgramManager::getProgramHandle(const char * iSearchTag)
{
    // Find shader entry
    ShaderEntry * entry = findEntry(iSearchTag);
    return (entry) ? entry->programHandle : 0;
}

/**
 * Get function for time stamp in entry.
 * @param iSearchTag Tag for requested entry.
 * @return Returns time stamp.
 * @see getProgramHandle()
 */
__uint64 ShaderProgramManager::getTimeStamp(const char * iSearchTag)
{
    // Find shader entry
    ShaderEntry * entry = findEntry(iSearchTag);
    return (entry) ? entry->timeStamp : 0;
}

/**
 * Internal function to retrieve entries.
 * @param iSearchTag Tag to search for.
 * @return Returns pointer to the entire entry.
 */
ShaderProgramManager::ShaderEntry * ShaderProgramManager::findEntry(const char * iSearchTag)
{
    // Check invalid searchtag
    if (!iSearchTag || !*iSearchTag)
        return 0;

#if 1
    EntryMap::iterator it = mEntryMap->find(const_cast<char *>(iSearchTag));

    if (it != mEntryMap->end())
        return it->second;
    else
        return 0;
#else    
    ShaderEntry * entry = 0;
    bool match = false;
    if (iSearchTag && mEntryListAnchor) {
        // Find entry
        entry = mEntryListAnchor;
        if (strcmp(entry->tag, iSearchTag) == 0)
            match = true;
        int i = 0;
        while (!match && entry->next && i<100) {
            entry = entry->next;
            if (strcmp(entry->tag, iSearchTag) == 0)
                match = true;
            i++;
        }
    }
    return (match) ? entry : 0;
#endif
}

/**
 * Cats all tags into a string (Debug ONLY).
 * Note! This function allocates memory and it is up to the user to free that memory.
 * Therfore do NOT use from seperate .dll
 * @return char pointer to allocated string
 */
char * ShaderProgramManager::getAllTagsAsOneString()
{
    char * tag = 0;
    ShaderEntry * entry = 0;

    // Get total length of all tags
    size_t totLength = 1;

#if 1
    for (EntryMap::iterator it = mEntryMap->begin(); it != mEntryMap->end(); it++) {
        totLength += strlen(it->first) + 1;
    }

    char * tags = reinterpret_cast<char *>(malloc(totLength * sizeof(char)));

    if (!tags) return 0;

    char * end = tags;

    for (EntryMap::iterator it = mEntryMap->begin(); it != mEntryMap->end(); it++) {
        // Add separator after first tag
        if (tags != end)
            *(end++) = ' ';
            
        for (const char * src = it->first; *src; src++, end++)
            *end = *src;
    }

    *end = 0;   // Place end of string
#else
    entry = mEntryListAnchor;
    while (entry) {
        totLength += static_cast<int>(strlen(entry->tag)) +1;    // +1 due to separating space
        entry = entry->next;
    }

    // Allocate memory and cat tags
    char * tags = reinterpret_cast<char *>(calloc(totLength, sizeof(char)));
    tags[0] = ' ';

    entry = mEntryListAnchor;
    while (entry) {
        strcat(tags + strlen(tags), " ");           // cat from current end of tags
        strcat(tags + strlen(tags), entry->tag);    // cat from current end of tags
        entry = entry->next;
    }
#endif

    return tags;
}

//#pragma warning( pop )


