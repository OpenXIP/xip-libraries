/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). eXtensible Imaging Platform (XIP)
 *  was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
 */

#include "XipDicomSortUtil.h"
#include "XipDicomSortAlg.h"

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>


class XipDicomSortImageList : public std::vector<const XipDicomSortImage*> { };
class XipDicomSortVolumeList : public std::vector<XipDicomSortImageList> { };



// returns the first number in a string
static float getFirstNumber(const char *str)
{
	const char numbers[] = "0123456789";
	float val = 0;

	// is string valid?
	if (str)
	{
		// get pointer to first number in string
		const char *pos = strpbrk(str, numbers);
		if (pos)
		{
			sscanf(pos, "%f", &val);
		}
	}

	return val;
}


// comparison function to sort by image position only
static bool imagePosition_less ( const XipDicomSortImage* elem1, const XipDicomSortImage* elem2 )
{
	return (elem1->getAttributes()->objectPositionZ < elem2->getAttributes()->objectPositionZ);
}


// comparison function to sort by trigger time and image position
static bool triggerTime_imagePosition_less ( const XipDicomSortImage* elem1, const XipDicomSortImage* elem2 )
{
	if (elem1->getAttributes()->triggerTime < elem2->getAttributes()->triggerTime)
	{
		return true;
	}
	else if (elem1->getAttributes()->triggerTime > elem2->getAttributes()->triggerTime)
	{
		return false;
	}
	
	// if equal trigger time, sort by position
	return (elem1->getAttributes()->objectPositionZ < elem2->getAttributes()->objectPositionZ);
}

// comparison function to sort by series number and image position
static bool seriesNumber_imagePosition_less ( const XipDicomSortImage* elem1, const XipDicomSortImage* elem2 )
{
	if (elem1->getAttributes()->seriesNumber < elem2->getAttributes()->seriesNumber)
	{
		return true;
	}
	else if (elem1->getAttributes()->seriesNumber > elem2->getAttributes()->seriesNumber)
	{
		return false;
	}
	
	// if equal trigger time, sort by position
	return (elem1->getAttributes()->objectPositionZ < elem2->getAttributes()->objectPositionZ);
}


// comparison function to sort by image number and image position
static bool imageNumber_imagePosition_less ( const XipDicomSortImage* elem1, const XipDicomSortImage* elem2 )
{
	if (elem1->getAttributes()->imageNumber < elem2->getAttributes()->imageNumber)
	{
		return true;
	}
	else if (elem1->getAttributes()->imageNumber > elem2->getAttributes()->imageNumber)
	{
		return false;
	}
	
	// if equal trigger time, sort by position
	return (elem1->getAttributes()->objectPositionZ < elem2->getAttributes()->objectPositionZ);
}


// comparison function to sort by acquisition time and image position
static bool acquisitionTime_imagePosition_less ( const XipDicomSortImage* elem1, const XipDicomSortImage* elem2 )
{
	if (elem1->getAttributes()->acquisitionTime < elem2->getAttributes()->acquisitionTime)
	{
		return true;
	}
	else if (elem1->getAttributes()->acquisitionTime > elem2->getAttributes()->acquisitionTime)
	{
		return false;
	}
	
	// if equal trigger time, sort by position
	return (elem1->getAttributes()->objectPositionZ < elem2->getAttributes()->objectPositionZ);
}


// comparison function to sort by scan options and image position
static bool scanOptions_imagePosition_less ( const XipDicomSortImage* elem1, const XipDicomSortImage* elem2 )
{
	float v1 = getFirstNumber(elem1->getAttributes()->scanOptions);
	float v2 = getFirstNumber(elem2->getAttributes()->scanOptions);

	if (v1 < v2)
	{
		return true;
	}
	else if (v1 > v2)
	{
		return false;
	}

	// if equal trigger time, sort by position
	return (elem1->getAttributes()->objectPositionZ < elem2->getAttributes()->objectPositionZ);
}


// comparison function to sort by scan options and image position
static bool XipDicomSortKeyGroup_less ( const XipDicomSortImage* elem1, const XipDicomSortImage* elem2 )
{
	return (XipDicomSortAlg(elem1) < XipDicomSortAlg(elem2));
}



/**
 *
 *	Initializes all members to zero.
 *
 */
XipDicomSortUtil::XipDicomSortUtil()
{
	mSortImageList = 0;
	mSortVolumeList = 0;
}


/**
 *
 *	Currently there is nothing to clean up (lists have their own destructor).
 *
 */
XipDicomSortUtil::~XipDicomSortUtil()
{
	clear();

	if (mSortImageList)
	{
		delete mSortImageList;
	}

	if (mSortVolumeList)
	{
		delete mSortVolumeList;
	}
}


int XipDicomSortUtil::addImage(const XipDicomSortImageAttributes *attributes)
{
	int rc = 0;

	if (!mSortImageList)
	{
		mSortImageList = new XipDicomSortImageList();
	}

	if (mSortImageList)
	{
		XipDicomSortImage *img = new XipDicomSortImage();
		if (img)
		{
			rc = img->setAttributes(attributes);
			mSortImageList->push_back(img);
		}
		else rc = -1;
	}
	else rc = -1;

	return rc;
}


/**
 *	This method invokes sorting of the objects identified by the names contained in dataObjectNamelist 
 *  set by the client application using XipDicomSortUtil::setObjects(). This method sorts the objects into 
 *  a list of groups, each group representing a set of volumes with similar characteristics.
 *
 *	The client application can subsequently query the group descriptor and use the information. The information
 *  provided through the group descriptor will be valid until the next sorting session is invoked.
 *
 *  \param	option	Optional sorting option/criteria. Can be RADSORT_SAME_ROWVECTOR, RADSORT_SAME_COLUMNVECTOR,
 *					RADSORTGENERIC_CREATE_DEFAULTGROUP or a combination of all values.
 *
 *	\b Example:
	\code

	// assumed that sorting and data plugins are loaded, dataObjects are dragged and dropped
	// and a valid dataObjectNamelist is created by the dataPlugin.

	// The application sets the dataObjectNamelist and dataConnector to the sorting plugin
	// and invokes the sorting by calling XipDicomSortUtil::sort() with appropriate optional flags.
 
	mSorterPlugin->setObjects(dataObjectNamelist, dataConnectorPtr);
	mSorterPlugin->sort(RADSORT_SAME_ROWVECTOR | RADSORT_SAME_COLUMNVECTOR);

	// As a result of the above, the sorting plugin has created the group list which can
	// be queried by the application now.

	// get the group count
	unsigned int numberOfAvailableGroups = mSorterPlugin->getGroups();

	//get a pointer to the first group 
	unsigned int groupIndex = 0;
	Rad4DSequenceDescriptor * desc = (Rad4DSequenceDescriptor*) ( mSorterPlugin->getGroupDescriptor(groupIndex) );

	//use the information contained in the group descriptor.

	//The application must not delete the pointer to Rad4DSequenceDescriptor object.

	\endcode
 */
void XipDicomSortUtil::sort(unsigned int option)
{
	if (!mSortImageList)
		return;

	if (mSortVolumeList)
	{
		mSortVolumeList->clear();
	}
	else
	{
		mSortVolumeList = new XipDicomSortVolumeList();
		if (!mSortVolumeList)
			return;
	}

	XipDicomSortImageList::const_iterator from;
	XipDicomSortImageList::const_iterator i;
	XipDicomSortVolumeList::iterator g;

	// first pass, put all images into baskets
	XipDicomSortVolumeList firstPassBaskets;

	// sort by group separator
	std::sort(mSortImageList->begin(), mSortImageList->end(), XipDicomSortKeyGroup_less );
	XipDicomSortImageList imageList;
	
	from = mSortImageList->begin();
	for (i = mSortImageList->begin(); i != mSortImageList->end(); i++)
	{
		if (XipDicomSortAlg(*from) != XipDicomSortAlg(*i))
		{
			imageList.assign(from, i);
			if (imageList.size() > 0)
				firstPassBaskets.push_back(imageList);

			from = i;
		}
	}

	imageList.assign(from, i);
	if (imageList.size() > 0)
		firstPassBaskets.push_back(imageList);

	// now deal with each basket individually
	for (g = firstPassBaskets.begin(); g != firstPassBaskets.end(); g++)
	{
		// sort all slices by image position
		std::sort(g->begin(), g->end(), imagePosition_less );

		// check if time sequence (or any other overlapping stuff)
		unsigned int sortHint;
		int numDupImagePositions = getNumDuplicateImagePositions(*g, sortHint);

		if (numDupImagePositions == 0)
		{
			// no duplicated slices, take as is
			mSortVolumeList->push_back(*g);
		}
		else
		{
			// NOTE: It requires a minimum of two slices when it goes through the following conditions.

			// TBD: What if only the first or last slice have duplicates such as with older CT scans?

			// most likely multiple volumes such as time sequence
			// might be separable by:
			// - trigger time
			// - image number
			// - scan options
			// - acquisition time

			if ((sortHint & TRIGGER_TIME) && canSortByTriggerTime(*g))
			{
				// assume that all slices in a volume have the same trigger time
				std::sort(g->begin(), g->end(), triggerTime_imagePosition_less );

				from = g->begin();
				float triggerTime = (*(g->begin()))->getAttributes()->triggerTime;
				for (i = g->begin(); i != g->end(); i++)
				{
					if (triggerTime != (*i)->getAttributes()->triggerTime)
					{
						imageList.assign(from, i);

						// add new group
						if (imageList.size() > 0)
						{
							mSortVolumeList->push_back(imageList);
						}
						from = i;

						triggerTime = (*i)->getAttributes()->triggerTime;
					}
				}

				// add last group
				imageList.assign(from, i);
				if (imageList.size() > 0)
				{
					mSortVolumeList->push_back(imageList);
				}
			}
			else if ((sortHint & SERIES_NUMBER) && canSortBySeriesNumber(*g))
			{
				// assume that all slices in a volume have the same series number
				std::sort(g->begin(), g->end(), seriesNumber_imagePosition_less );

				from = g->begin();
				unsigned int seriesNumber = (*(g->begin()))->getAttributes()->seriesNumber;
				for (i = g->begin(); i != g->end(); i++)
				{
					if (seriesNumber != (*i)->getAttributes()->seriesNumber)
					{
						imageList.assign(from, i);

						// add new group
						if (imageList.size() > 0)
						{
							mSortVolumeList->push_back(imageList);
						}
						from = i;

						seriesNumber = (*i)->getAttributes()->seriesNumber;
					}
				}

				// add last group
				imageList.assign(from, i);
				if (imageList.size() > 0)
				{
					mSortVolumeList->push_back(imageList);
				}
			}
			else if ((sortHint & IMAGE_NUMBER) && canSortByImageNumber(*g))
			{
				// assume that all slices in a volume have the same image number
				std::sort(g->begin(), g->end(), imageNumber_imagePosition_less );

				from = g->begin();
				unsigned int imageNumber = (*(g->begin()))->getAttributes()->imageNumber;
				for (i = g->begin(); i != g->end(); i++)
				{
					if (imageNumber != (*i)->getAttributes()->imageNumber)
					{
						imageList.assign(from, i);

						// add new group
						if (imageList.size() > 0)
						{
							mSortVolumeList->push_back(imageList);
						}
						from = i;

						imageNumber = (*i)->getAttributes()->imageNumber;
					}
				}
				// add last group
				imageList.assign(from, i);
				if (imageList.size() > 0)
				{
					mSortVolumeList->push_back(imageList);
				}
			}
			else if ((sortHint & SCAN_OPTIONS) && canSortByScanOptions(*g))
			{
				// assume that all slices in a volume have the same number in the scan options
				std::sort(g->begin(), g->end(), scanOptions_imagePosition_less );

				from = g->begin();
				float scanOptions = getFirstNumber((*(g->begin()))->getAttributes()->scanOptions);
				for (i = g->begin(); i != g->end(); i++)
				{
					if (scanOptions != getFirstNumber((*i)->getAttributes()->scanOptions))
					{
						imageList.assign(from, i);

						// add new group
						if (imageList.size() > 0)
						{
							mSortVolumeList->push_back(imageList);
						}
						from = i;

						scanOptions = getFirstNumber((*i)->getAttributes()->scanOptions);
					}
				}
				// add last group
				imageList.assign(from, i);
				if (imageList.size() > 0)
				{
					mSortVolumeList->push_back(imageList);
				}
			}
			else if ((sortHint & ACQUISITION_TIME) && canSortByAcquisitionTime(*g))
			{
				// assume that all slices in a volume have the same acquisition time
				std::sort(g->begin(), g->end(), acquisitionTime_imagePosition_less );

				from = g->begin();
				float acquisitionTime = (*(g->begin()))->getAttributes()->acquisitionTime;
				for (i = g->begin(); i != g->end(); i++)
				{
					if (acquisitionTime != (*i)->getAttributes()->acquisitionTime)
					{
						imageList.assign(from, i);

						// add new group
						if (imageList.size() > 0)
						{
							mSortVolumeList->push_back(imageList);
						}
						from = i;

						acquisitionTime = (*i)->getAttributes()->acquisitionTime;
					}
				}
				// add last group
				imageList.assign(from, i);
				if (imageList.size() > 0)
				{
					mSortVolumeList->push_back(imageList);
				}
			}
			else if (sortHint & TRIGGER_TIME)
			{
				// we have unique trigger time for each slice
				// sort by trigger time and break volumes once direction in image position changes
				std::sort(g->begin(), g->end(), triggerTime_imagePosition_less );

				double prevImagePosition = (*(g->begin()))->getAttributes()->objectPositionZ;
				double nextImagePosition = (*(g->begin() + 1))->getAttributes()->objectPositionZ;
				bool dir = (nextImagePosition > prevImagePosition);

				from = g->begin();
				for (i = g->begin(); i != g->end(); i++)
				{
					if (dir ? (*i)->getAttributes()->objectPositionZ < prevImagePosition : (*i)->getAttributes()->objectPositionZ > prevImagePosition)
					{
						imageList.assign(from, i);

						// add new group
						if (imageList.size() > 0)
						{
							mSortVolumeList->push_back(imageList);
						}
						from = i;
					}

					prevImagePosition = (*i)->getAttributes()->objectPositionZ;
				}
				// add last group
				imageList.assign(from, i);
				if (imageList.size() > 0)
				{
					mSortVolumeList->push_back(imageList);
				}

			}
			else if (sortHint & IMAGE_NUMBER)
			{
				// we have unique image numbers for each slice
				// sort by image number and break volumes once direction in image position changes
				std::sort(g->begin(), g->end(), imageNumber_imagePosition_less );

				double prevImagePosition = (*(g->begin()))->getAttributes()->objectPositionZ;
				double nextImagePosition = (*(g->begin() + 1))->getAttributes()->objectPositionZ;
				bool dir = (nextImagePosition > prevImagePosition);

				from = g->begin();
				for (i = g->begin(); i != g->end(); i++)
				{
					if (dir ? (*i)->getAttributes()->objectPositionZ < prevImagePosition : (*i)->getAttributes()->objectPositionZ > prevImagePosition)
					{
						imageList.assign(from, i);

						// add new group
						if (imageList.size() > 0)
						{
							mSortVolumeList->push_back(imageList);
						}
						from = i;
					}

					prevImagePosition = (*i)->getAttributes()->objectPositionZ;
				}
				// add last group
				imageList.assign(from, i);
				if (imageList.size() > 0)
				{
					mSortVolumeList->push_back(imageList);
				}
			}
			else
			{
				// cannot separate by any criteria
				// just sort by position and hope for the best
				mSortVolumeList->push_back(*g);
			}
		}
	}
}


/**
 *
 *	The sorting operation will create logical groupings for the provided objects. The number
 *	of groups created by the last sorting operation is returned by this method.
 *
 *	\return	Number of logical groups created by the last sorting operation.
 *
 * \b Examples
   \code

	// assumed that the sorting plugin has completed the sorting and has a valid group list.
	 
	// The client application queries the group count.
	unsigned int numberOfAvailableGroups = mSorterPlugin->getGroups();

	\endcode
 */
unsigned int XipDicomSortUtil::getNumVolumes() const
{
	return mSortVolumeList ? mSortVolumeList->size() : 0;
}


/**
 *
 *	This method returns the number of objects in the given group.
 *
 *	\param	volumeIndex		Specifies the group by an index. The index ranges from 0 to RadSortBase::getGroups.
 *	\return	Number of objects that belong to a given group.
 *
 *
 * \b Examples
   \code

	// assumed that the sorting plugin has completed the sorting and has a valid group list.

	unsigned int groupIndex						= 0; 	//get the number of objects in the first group 
	unsigned int numberOfObjectsInFirstGroup	= mSorterPlugin->getObjectsInGroup(groupIndex);

	\endcode
 */
unsigned int XipDicomSortUtil::getNumSlicesInVolume(unsigned int volumeIndex) const
{
	if (!mSortVolumeList || (volumeIndex >= mSortVolumeList->size()))
	{			
		return -1;
	}

	return mSortVolumeList->at(volumeIndex).size();
}


/**
 *
 *	This method can be used to retrieve a constant pointer to the descriptor for a given
 *	object. 
 *
 *  The application must not delete the pointer. This pointer will be valid until the next sorting session 
 *  is invoked.
 * 
 *	\param	groupIndex		Specifies the group by an index. The index ranges from 0 to RadSortBase::getGroups.
 *
 *	\param	objectIndex		Specifies the object by an index. The index ranges from 0 to RadSortBase::getObjectsInGroup.
 *
 *	\return	Pointer to RadImageDescriptor
 *
 * \b Examples
   \code

	// assumed that the sorting plugin has completed the sorting and has a valid group list.

	// get the pointer to the RadImageDescriptor object which describes the first object in the
	// first group.
	
	const struct RadImageDescriptor *firstImgInFirstGroup = NULL;
	firstImgInFirstGroup = (const struct RadImageDescriptor *) mSorterPlugin->getObjectDescriptor(0, 0);

	// The application must not delete the RadImageDescriptor object.
	\endcode
 */
const XipDicomSortImageAttributes * XipDicomSortUtil::getImageAttributes(unsigned int volumeIndex, unsigned int sliceIndex) const
{
	if (volumeIndex >= mSortVolumeList->size())
	{			
		return 0;
	}

	if (sliceIndex >= mSortVolumeList->at(volumeIndex).size())
	{			
		return 0;
	}

	return mSortVolumeList->at(volumeIndex)[sliceIndex]->getAttributes();
}


/**
 *
 *	Count number of duplicate image positions in given image list.
 *
 *  \param	imageList	List of images to count duplicate image positions in.
 *
 *	\return	Number of duplicate image positions.
 *
 */
int XipDicomSortUtil::getNumDuplicateImagePositions(const XipDicomSortImageList &imageList, unsigned int &sortOption)
{
	XipDicomSortImageList::const_iterator i;
	int duplicates = 0;
	sortOption = SORT_OPTIONS_ALL;

	double prevPos = (*imageList.begin())->getAttributes()->objectPositionZ;

	float prevAcqTime = (*imageList.begin())->getAttributes()->acquisitionTime;
	float prevTriggerTime = (*imageList.begin())->getAttributes()->triggerTime;
	unsigned int prevSeriesNumber = (*imageList.begin())->getAttributes()->seriesNumber;
	unsigned int prevImageNumber = (*imageList.begin())->getAttributes()->imageNumber;
	float prevScanOptions = getFirstNumber((*imageList.begin())->getAttributes()->scanOptions);

	for (i = imageList.begin() + 1; i != imageList.end(); i++)
	{
		double pos = (*i)->getAttributes()->objectPositionZ;
		if (pos == prevPos)
		{
			if (prevTriggerTime == (*i)->getAttributes()->triggerTime)
			{
				sortOption &= ~TRIGGER_TIME;
			}
			if (prevSeriesNumber == (*i)->getAttributes()->seriesNumber)
			{
				sortOption &= ~SERIES_NUMBER;
			}
			if (prevAcqTime == (*i)->getAttributes()->acquisitionTime)
			{
				sortOption &= ~ACQUISITION_TIME;
			}
			if (prevImageNumber == (*i)->getAttributes()->imageNumber)
			{
				sortOption &= ~IMAGE_NUMBER;
			}
			if (prevScanOptions == getFirstNumber((*i)->getAttributes()->scanOptions))
			{
				sortOption &= ~SCAN_OPTIONS;
			}

			duplicates++;
		}

		prevPos = pos;

		prevAcqTime = (*i)->getAttributes()->acquisitionTime;
		prevTriggerTime = (*i)->getAttributes()->triggerTime;
		prevSeriesNumber = (*i)->getAttributes()->seriesNumber;
		prevImageNumber = (*i)->getAttributes()->imageNumber;
		prevScanOptions = getFirstNumber((*i)->getAttributes()->scanOptions);
	}

	return duplicates;
}


/**
 *
 *	Quick check if trigger time will separate images with duplicate positions.
 *
 *	\return	Returns true if trigger time is different in images with same position.
 *
 */
bool XipDicomSortUtil::canSortByTriggerTime(const XipDicomSortImageList &imageList) const
{
	// in order to sort we need to find same attribute in at least three 
	// but less than all of the images

	XipDicomSortImageList::const_iterator i;
	unsigned int duplicates = 0;
	float triggerTime = 0;

	for (i = imageList.begin(); i != imageList.end(); i++)
	{
		if (i == imageList.begin())
		{
			triggerTime = (*i)->getAttributes()->triggerTime;
		}
		
		if (triggerTime == (*i)->getAttributes()->triggerTime)
		{
			duplicates++;
		}
	}

	return ( (duplicates > 1) && (duplicates < imageList.size()) );
}

/**
 *
 *	Quick check if series number will separate images with duplicate positions.
 *
 *	\return	Returns true if series number is different in images with same position.
 *
 */
bool XipDicomSortUtil::canSortBySeriesNumber(const XipDicomSortImageList &imageList) const
{
	// in order to sort we need to find same attribute in at least three 
	// but less than all of the images

	XipDicomSortImageList::const_iterator i;
	unsigned int duplicates = 0;
	int seriesNumber = 0;

	for (i = imageList.begin(); i != imageList.end(); i++)
	{
		if (i == imageList.begin())
		{
			seriesNumber = (*i)->getAttributes()->seriesNumber;
		}
		
		if (seriesNumber == (*i)->getAttributes()->seriesNumber)
		{
			duplicates++;
		}
	}

	return ( (duplicates > 1) && (duplicates < imageList.size()) );
}


/**
 *
 *	Quick check if image number will separate images with duplicate positions.
 *
 *	\return	Returns true if image number is different in images with same position.
 *
 */
bool XipDicomSortUtil::canSortByImageNumber(const XipDicomSortImageList &imageList) const
{
	// in order to sort we need to find same attribute in at least three 
	// but less than all of the images

	XipDicomSortImageList::const_iterator i;
	unsigned int duplicates = 0;
	unsigned int imageNumber = 0;

	for (i = imageList.begin(); i != imageList.end(); i++)
	{
		if (i == imageList.begin())
		{
			imageNumber = (*i)->getAttributes()->imageNumber;
		}
		
		if (imageNumber == (*i)->getAttributes()->imageNumber)
		{
			duplicates++;
		}
	}

	return ( (duplicates > 1) && (duplicates < imageList.size()) );
}


/**
 *
 *	Quick check if number in scan options will separate images with duplicate positions.
 *
 *	\return	Returns true if number in scan options is different in images with same position.
 *
 */
bool XipDicomSortUtil::canSortByScanOptions(const XipDicomSortImageList &imageList) const
{
	// in order to sort we need to find same attribute in at least three 
	// but less than all of the images

	XipDicomSortImageList::const_iterator i;
	unsigned int duplicates = 0;
	float scanOptions = 0;

	for (i = imageList.begin(); i != imageList.end(); i++)
	{
		if (i == imageList.begin())
		{
			scanOptions = getFirstNumber((*i)->getAttributes()->scanOptions);
		}
		
		if (scanOptions == getFirstNumber((*i)->getAttributes()->scanOptions))
		{
			duplicates++;
		}
	}

	return ( (duplicates > 1) && (duplicates < imageList.size()) );
}


/**
 *
 *	Quick check if acquisition time will separate images with duplicate positions.
 *
 *	\return	Returns true if acquisition time is different in images with same position.
 *
 */
bool XipDicomSortUtil::canSortByAcquisitionTime(const XipDicomSortImageList &imageList) const
{
	// in order to sort we need to find same attribute in at least three 
	// but less than all of the images

	XipDicomSortImageList::const_iterator i;
	unsigned int duplicates = 0;
	float acquisitionTime = 0;

	for (i = imageList.begin(); i != imageList.end(); i++)
	{
		if (i == imageList.begin())
		{
			acquisitionTime = (*i)->getAttributes()->acquisitionTime;
		}
		
		if (acquisitionTime == (*i)->getAttributes()->acquisitionTime)
		{
			duplicates++;
		}
	}

	return ( (duplicates > 1) && (duplicates < imageList.size()) );
}


/**
 *
 *	Clears all parsed image information and previous sorting results. This method is called
 *  in the beginning of the sort() method and the destructor.
 *
 */
void XipDicomSortUtil::clear()
{
	// delete all images in list
	if (mSortImageList)
	{
		XipDicomSortImageList::const_iterator i;
		for (i = mSortImageList->begin(); i != mSortImageList->end(); i++)
		{
			delete (*i);
		}

		// free list entries
		mSortImageList->clear();
	}

	if (mSortVolumeList)
		mSortVolumeList->clear();
}
