#include <xip/system/standard.h>
#include <xip/inventor/core/XipInventorUtils.h>
#include <Inventor/SoPath.h>
#include <Inventor/nodes/SoLabel.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/errors/SoMemoryError.h>

#include <xip/inventor/core/SbXipImage.h>
#include <xip/common/XipException.h>
#include <string>
#include <stdio.h>

SoNode *getNodeByLabel(const SoPath *labelPath, const char *name, const SoType &type)
{
	if (!labelPath || !name) return 0;

	int len = labelPath->getLength();
	if (len > 1)
	{
		SoLabel *labelNode = (SoLabel*) labelPath->getTail();
		SoNode *parent = labelPath->getNode(len - 2);
		SbName label = labelNode->label.getValue();

		// return if not the one we are looking for
		if (label != SbName(name)) return 0;

		if (!parent->isOfType(SoGroup::getClassTypeId()))
		{
			// parent is not a group, so parent is the node
			if (parent->isOfType(type))
			{
				return parent;
			}
		}
		else
		{
			SoGroup *group = (SoGroup*) parent;
			int index = group->findChild(labelNode);
			if (index > 0)
			{
				// check preceeding child
				SoNode *prevNode = group->getChild(index - 1);
				if (prevNode->isOfType(type))
				{
					return prevNode;
				}
			}
			else
			{
				// first child, label group
				if (group->isOfType(type))
				{
					return parent;
				}
			}
		}
	}

	return 0;
}

XipWStringConv::XipWStringConv(const char *str)
{
	mStr = 0;
	if (str)
	{
		size_t len = strlen(str);
        if (len <=0)
            return;
        len += 1;
		mStr = new wchar_t [len];
		if (!mStr)
        {
            throw XipException(__LINE__, __FILE__, XipException::MEMORY_HEAP_ERROR, L"Error allocating wchar_t string conversion");

        } else
			#if defined(WINDOWS) || defined(_WIN32)
				_snwprintf(mStr, len, L"%hs", str);
			#else
				 swprintf(mStr, len, L"%hs", str);
			#endif
	}
}

XipWStringConv::XipWStringConv()
{
	mStr = 0;
}

XipWStringConv::~XipWStringConv()
{
	if (mStr)
	{
		delete [] mStr;
		mStr = 0;
	}
}

const wchar_t *XipWStringConv::getString() const
{
	return mStr;
}




XipStringConv::XipStringConv(const wchar_t *str)
{
	mStr = 0;
	if (str)
	{
		size_t len = wcslen(str);
        if (len <= 0)
            return;
        len += 1;
		mStr = new char [len];
		if (!mStr)
        {
            throw XipException(__LINE__, __FILE__, XipException::MEMORY_HEAP_ERROR, L"Error allocating string conversion");

        } else
        {
			#if defined(WINDOWS) || defined(_WIN32)
                size_t sizeOfBuf = (sizeof(char) * len);
                _snprintf(mStr, sizeOfBuf, "%S", str);
			#else
				 snprintf(mStr, len + 1, "%S", str);
			#endif
        }
	}
}

XipStringConv::XipStringConv()
{
	mStr = 0;
}

XipStringConv::~XipStringConv()
{
	if (mStr)
	{
		delete [] mStr;
		mStr = 0;
	}
}

const char *XipStringConv::getString() const
{
	return mStr;
}

/*! \fn XipPostException(XipException& e_in)
* This function posts XipExceptions based on the exception types
* 
* As "SoDebugError:postWarnings"
* IVT_INVALID_PARAM_ERROR, IVT_NULLPTR_ERROR, IVT_STRUCTURED_EXCEPTION,
* IVT_OPERATION_UNSUPPORTED, IVT_INCOMPATIBLE_GEOMETRY, IVT_LICENSE_UNAVAILABLE
* 
* As "SoMemoryError::post"
* IVT_OUTOFMEMORY_ERROR, IVT_MEMORYMAPPING_ERROR, IVT_HWOUTOFMEMORY_ERROR,  as memory errors
*
* As "SoDebugError::postInfo"
* IVT_ABORT_EXECUTION (progress cancel) as info
*
* As "SoError::post"
* IVT_INTERNAL_SYSTEM_ERROR, IVT_COMM_ERROR as errors
* 
* \param e_in - the input exception
*/
void XipPostException(XipException& e_in)
{
    char* tmpStr = 0;
    try
    {
        XipStringConv strConv(e_in.getMessage());

        switch (e_in.getType())
        {
        case XipException::INVALID_PARAM_ERROR:
        case XipException::INVALID_STATE_ERROR:
        case XipException::OPERATION_UNSUPPORTED:
            {
                SoDebugError::postWarning(e_in.getFile(), strConv.getString());
            } break;
        case XipException::MEMORY_HEAP_ERROR:
        case XipException::MEMORY_MAPPING_ERROR:
        case XipException::MEMORY_DISK_ERROR:
            {
                int len = strlen(e_in.getFile()) + 1;
                len += (strlen(strConv.getString()) + 1);

                tmpStr = new char[len];
                if (!tmpStr)
                {
                    throw XipException(__LINE__, __FILE__, XipException::MEMORY_HEAP_ERROR, L"Temp string allocation error.");
                }
                snprintf(tmpStr, sizeof(char)*len, "%s, %s", e_in.getFile(), strConv.getString());
                SoMemoryError::post(tmpStr);
            } break;
        case XipException::ABORT_EXECUTION:
            {
                SoDebugError::postInfo(e_in.getFile(), strConv.getString());
            } break;
        case XipException::INTERNAL_SYSTEM_ERROR:
        case XipException::IO_ERROR:
        case XipException::COMM_ERROR:
            {
                SoError::post("%s, %s", e_in.getFile(), strConv.getString());
            } break;
        default:
            {
                SoError::post("%s, %s", e_in.getFile(), strConv.getString());
            } break;
        }

        delete [] tmpStr;
        tmpStr = 0;

    } catch (...)
    {
        delete [] tmpStr;
        throw;
    }

}
