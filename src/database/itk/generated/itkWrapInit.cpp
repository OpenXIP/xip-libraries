/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
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
/* author Sylvain Jaume, Julien Gein */

#include "SoItkProcessObject.h"
#include "SoItkImageSource.h"
#include "SoItkImageToImageFilter.h"
#include "SoItkMorphologyImageFilter.h"
#include "SoItkGrayscaleDilateImageFilter.h"
#include "SoItkBinaryDilateImageFilter.h"
#include "SoItkBinaryErodeImageFilter.h"
#include "SoItkGrayscaleFunctionDilateImageFilter.h"
#include "SoItkGrayscaleErodeImageFilter.h"
#include "SoItkGrayscaleFunctionErodeImageFilter.h"
#include "SoItkBSplineDecompositionImageFilter.h"
#include "SoItkSmoothingRecursiveGaussianImageFilter.h"
#include "SoItkHConvexImageFilter.h"
#include "SoItkResampleImageFilter.h"
#include "SoItkWhiteTopHatImageFilter.h"
#include "SoItkLaplacianSharpeningImageFilter.h"
#include "SoItkGradientMagnitudeImageFilter.h"
#include "SoItkLaplacianRecursiveGaussianImageFilter.h"
#include "SoItkRegionOfInterestImageFilter.h"
#include "SoItkMedianImageFilter.h"
#include "SoItkHConcaveImageFilter.h"
#include "SoItkPermuteAxesImageFilter.h"
#include "SoItkAdaptiveHistogramEqualizationImageFilter.h"
#include "SoItkApproximateSignedDistanceMapImageFilter.h"
#include "SoItkFastMarchingImageFilter.h"
#include "SoItkStatisticsImageFilter.h"
#include "SoItkObjectMorphologyImageFilter.h"
#include "SoItkDilateObjectMorphologyImageFilter.h"
#include "SoItkErodeObjectMorphologyImageFilter.h"
#include "SoItkDifferenceImageFilter.h"
#include "SoItkShrinkImageFilter.h"
#include "SoItkNoiseImageFilter.h"
#include "SoItkReflectImageFilter.h"
#include "SoItkConfidenceConnectedImageFilter.h"
#include "SoItkHausdorffDistanceImageFilter.h"
#include "SoItkPadImageFilter.h"
#include "SoItkWrapPadImageFilter.h"
#include "SoItkMirrorPadImageFilter.h"
#include "SoItkConstantPadImageFilter.h"
#include "SoItkHistogramMatchingImageFilter.h"
#include "SoItkScalarImageKmeansImageFilter.h"
#include "SoItkRegionGrowImageFilter.h"
#include "SoItkChangeInformationImageFilter.h"
#include "SoItkOtsuThresholdImageFilter.h"
#include "SoItkVotingBinaryImageFilter.h"
#include "SoItkVotingBinaryHoleFillingImageFilter.h"
//#include "SoItkGetAverageSliceImageFilter.h"
#include "SoItkIsolatedWatershedImageFilter.h"
#include "SoItkBSplineResampleImageFilterBase.h"
#include "SoItkBSplineDownsampleImageFilter.h"
#include "SoItkBSplineCenteredResampleImageFilterBase.h"
#include "SoItkBSplineCenteredL2ResampleImageFilterBase.h"
#include "SoItkBSplineUpsampleImageFilter.h"
#include "SoItkNeighborhoodConnectedImageFilter.h"
#include "SoItkContourDirectedMeanDistanceImageFilter.h"
#include "SoItkSignedDanielssonDistanceMapImageFilter.h"
#include "SoItkInPlaceImageFilter.h"
#include "SoItkGradientMagnitudeRecursiveGaussianImageFilter.h"
#include "SoItkTernaryFunctorImageFilter.h"
#include "SoItkTernaryAddImageFilter.h"
#include "SoItkTernaryMagnitudeSquaredImageFilter.h"
#include "SoItkTernaryMagnitudeImageFilter.h"
#include "SoItkPasteImageFilter.h"
#include "SoItkBinaryFunctorImageFilter.h"
#include "SoItkAndImageFilter.h"
#include "SoItkAtan2ImageFilter.h"
#include "SoItkWeightedAddImageFilter.h"
#include "SoItkConstrainedValueDifferenceImageFilter.h"
#include "SoItkAddImageFilter.h"
#include "SoItkMinimumImageFilter.h"
#include "SoItkXorImageFilter.h"
#include "SoItkMaskImageFilter.h"
#include "SoItkMultiplyImageFilter.h"
#include "SoItkBinaryMagnitudeImageFilter.h"
#include "SoItkConstrainedValueAdditionImageFilter.h"
#include "SoItkDivideImageFilter.h"
#include "SoItkOrImageFilter.h"
#include "SoItkSquaredDifferenceImageFilter.h"
#include "SoItkSubtractImageFilter.h"
#include "SoItkAbsoluteValueDifferenceImageFilter.h"
#include "SoItkMaximumImageFilter.h"
#include "SoItkMaskNegatedImageFilter.h"
#include "SoItkThresholdImageFilter.h"
#include "SoItkUnaryFunctorImageFilter.h"
#include "SoItkCosImageFilter.h"
#include "SoItkNotImageFilter.h"
#include "SoItkRescaleIntensityImageFilter.h"
#include "SoItkAsinImageFilter.h"
#include "SoItkSigmoidImageFilter.h"
#include "SoItkSqrtImageFilter.h"
#include "SoItkBoundedReciprocalImageFilter.h"
#include "SoItkTanImageFilter.h"
#include "SoItkSquareImageFilter.h"
#include "SoItkExpImageFilter.h"
#include "SoItkExpNegativeImageFilter.h"
#include "SoItkSinImageFilter.h"
#include "SoItkAtanImageFilter.h"
#include "SoItkAcosImageFilter.h"
#include "SoItkLogImageFilter.h"
#include "SoItkIntensityWindowingImageFilter.h"
#include "SoItkAbsImageFilter.h"
#include "SoItkCastImageFilter.h"
#include "SoItkLog10ImageFilter.h"
#include "SoItkBinaryThresholdImageFilter.h"
#include "SoItkFiniteDifferenceImageFilter.h"
#include "SoItkDenseFiniteDifferenceImageFilter.h"
#include "SoItkCurvatureFlowImageFilter.h"
#include "SoItkMinMaxCurvatureFlowImageFilter.h"
#include "SoItkBinaryMinMaxCurvatureFlowImageFilter.h"
#include "SoItkAnisotropicDiffusionImageFilter.h"
#include "SoItkCurvatureAnisotropicDiffusionImageFilter.h"
#include "SoItkGradientAnisotropicDiffusionImageFilter.h"
#include "SoItkSparseFieldLevelSetImageFilter.h"
#include "SoItkSegmentationLevelSetImageFilter.h"
#include "SoItkGeodesicActiveContourLevelSetImageFilter.h"
#include "SoItkShapeDetectionLevelSetImageFilter.h"
#include "SoItkThresholdSegmentationLevelSetImageFilter.h"
#include "SoItkLaplacianSegmentationLevelSetImageFilter.h"
#include "SoItkCannySegmentationLevelSetImageFilter.h"
#include "SoItkShapePriorSegmentationLevelSetImageFilter.h"
#include "SoItkGeodesicActiveContourShapePriorLevelSetImageFilter.h"
#include "SoItkCurvesLevelSetImageFilter.h"
#include "SoItkSparseFieldFourthOrderLevelSetImageFilter.h"
#include "SoItkIsotropicFourthOrderLevelSetImageFilter.h"
#include "SoItkAnisotropicFourthOrderLevelSetImageFilter.h"
#include "SoItkUnsharpMaskLevelSetImageFilter.h"
#include "SoItkAntiAliasBinaryImageFilter.h"
#include "SoItkNaryFunctorImageFilter.h"
#include "SoItkNaryMaximumImageFilter.h"
#include "SoItkNaryAddImageFilter.h"
#include "SoItkRelabelComponentImageFilter.h"
#include "SoItkLaplacianImageFilter.h"
#include "SoItkTobogganImageFilter.h"
#include "SoItkMultiResolutionPyramidImageFilter.h"
#include "SoItkZeroCrossingImageFilter.h"
#include "SoItkMinimumMaximumImageFilter.h"
#include "SoItkCannyEdgeDetectionImageFilter.h"
#include "SoItkReconstructionByDilationImageFilter.h"
#include "SoItkNormalizeImageFilter.h"
#include "SoItkAccumulateImageFilter.h"
#include "SoItkRecursiveSeparableImageFilter.h"
#include "SoItkRecursiveGaussianImageFilter.h"
#include "SoItkZeroCrossingBasedEdgeDetectionImageFilter.h"
#include "SoItkGrayscaleConnectedOpeningImageFilter.h"
#include "SoItkGrayscaleConnectedClosingImageFilter.h"
#include "SoItkWatershedImageFilter.h"
#include "SoItkSTAPLEImageFilter.h"
#ifdef BUILD_WITH_ITK_PATENTED
#include "SoItkSimpleFuzzyConnectednessImageFilterBase.h"
#include "SoItkSimpleFuzzyConnectednessScalarImageFilter.h"
#endif
#include "SoItkGrayscaleMorphologicalOpeningImageFilter.h"
//#include "SoItkLazyEdgeDetectionImageFilter3D.h"
#include "SoItkGrayscaleGrindPeakImageFilter.h"
#include "SoItkDerivativeImageFilter.h"
#include "SoItkGrayscaleGeodesicDilateImageFilter.h"
#include "SoItkOpeningByReconstructionImageFilter.h"
#include "SoItkReconstructionByErosionImageFilter.h"
#include "SoItkNonThreadedShrinkImageFilter.h"
#include "SoItkBlackTopHatImageFilter.h"
#include "SoItkCollidingFrontsImageFilter.h"
#include "SoItkTileImageFilter.h"
#include "SoItkInterpolateImageFilter.h"
#include "SoItkContourMeanDistanceImageFilter.h"
#include "SoItkDanielssonDistanceMapImageFilter.h"
#include "SoItkFastIncrementalBinaryDilateImageFilter.h"
#include "SoItkBinaryPruningImageFilter.h"
#include "SoItkDoubleThresholdImageFilter.h"
#include "SoItkHMaximaImageFilter.h"
#include "SoItkBinaryMedianImageFilter.h"
#include "SoItkConnectedComponentImageFilter.h"
#include "SoItkBinaryThinningImageFilter.h"
#include "SoItkShiftScaleImageFilter.h"
#include "SoItkDirectedHausdorffDistanceImageFilter.h"
#include "SoItkExtractImageFilter.h"
#include "SoItkCropImageFilter.h"
#include "SoItkConnectedThresholdImageFilter.h"
#include "SoItkNeighborhoodOperatorImageFilter.h"
#include "SoItkNormalizedCorrelationImageFilter.h"
#include "SoItkMaskNeighborhoodOperatorImageFilter.h"
#include "SoItkHMinimaImageFilter.h"
#include "SoItkGrayscaleGeodesicErodeImageFilter.h"
#include "SoItkVotingBinaryIterativeHoleFillingImageFilter.h"
#include "SoItkClosingByReconstructionImageFilter.h"
#include "SoItkJoinSeriesImageFilter.h"
#include "SoItkGrayscaleFillholeImageFilter.h"
#include "SoItkExpandImageFilter.h"
#include "SoItkCheckerBoardImageFilter.h"
#include "SoItkGrayscaleMorphologicalClosingImageFilter.h"
#include "SoItkFlipImageFilter.h"
#include "SoItkDiscreteGaussianImageFilter.h"
#include "SoItkBilateralImageFilter.h"
#include "SoItkHardConnectedComponentImageFilter.h"
#include "SoItkIsolatedConnectedImageFilter.h"
#include "SoItkOtsuMultipleThresholdsImageFilter.h"
#include "SoItkMeanImageFilter.h"
#include "SoItkBinomialBlurImageFilter.h"
#include "SoItkSimpleContourExtractorImageFilter.h"
#include "SoItkSobelEdgeDetectionImageFilter.h"
#include "SoItkMeshSource.h"
#include "SoItkImageToMeshFilter.h"
#include "SoItkBinaryMaskToNarrowBandPointSetFilter.h"

void itkWrapInit()
{
	SoItkProcessObject::initClass();
	SoItkImageSource::initClass();
	SoItkImageToImageFilter::initClass();
	SoItkMorphologyImageFilter::initClass();
	SoItkGrayscaleDilateImageFilter::initClass();
	SoItkBinaryDilateImageFilter::initClass();
	SoItkBinaryErodeImageFilter::initClass();
	SoItkGrayscaleFunctionDilateImageFilter::initClass();
	SoItkGrayscaleErodeImageFilter::initClass();
	SoItkGrayscaleFunctionErodeImageFilter::initClass();
	SoItkBSplineDecompositionImageFilter::initClass();
	SoItkSmoothingRecursiveGaussianImageFilter::initClass();
	SoItkHConvexImageFilter::initClass();
	SoItkResampleImageFilter::initClass();
	SoItkWhiteTopHatImageFilter::initClass();
	SoItkLaplacianSharpeningImageFilter::initClass();
	SoItkGradientMagnitudeImageFilter::initClass();
	SoItkLaplacianRecursiveGaussianImageFilter::initClass();
	SoItkRegionOfInterestImageFilter::initClass();
	SoItkMedianImageFilter::initClass();
	SoItkHConcaveImageFilter::initClass();
	SoItkPermuteAxesImageFilter::initClass();
	SoItkAdaptiveHistogramEqualizationImageFilter::initClass();
	SoItkApproximateSignedDistanceMapImageFilter::initClass();
	SoItkFastMarchingImageFilter::initClass();
	SoItkStatisticsImageFilter::initClass();
	SoItkObjectMorphologyImageFilter::initClass();
	SoItkDilateObjectMorphologyImageFilter::initClass();
	SoItkErodeObjectMorphologyImageFilter::initClass();
	SoItkDifferenceImageFilter::initClass();
	SoItkShrinkImageFilter::initClass();
	SoItkNoiseImageFilter::initClass();
	SoItkReflectImageFilter::initClass();
	SoItkConfidenceConnectedImageFilter::initClass();
	SoItkHausdorffDistanceImageFilter::initClass();
	SoItkPadImageFilter::initClass();
	SoItkWrapPadImageFilter::initClass();
	SoItkMirrorPadImageFilter::initClass();
	SoItkConstantPadImageFilter::initClass();
	SoItkHistogramMatchingImageFilter::initClass();
	SoItkScalarImageKmeansImageFilter::initClass();
	SoItkRegionGrowImageFilter::initClass();
	SoItkChangeInformationImageFilter::initClass();
	SoItkOtsuThresholdImageFilter::initClass();
	SoItkVotingBinaryImageFilter::initClass();
	SoItkVotingBinaryHoleFillingImageFilter::initClass();
	//SoItkGetAverageSliceImageFilter::initClass();
	SoItkIsolatedWatershedImageFilter::initClass();
	SoItkBSplineResampleImageFilterBase::initClass();
	SoItkBSplineDownsampleImageFilter::initClass();
	SoItkBSplineCenteredResampleImageFilterBase::initClass();
	SoItkBSplineCenteredL2ResampleImageFilterBase::initClass();
	SoItkBSplineUpsampleImageFilter::initClass();
	SoItkNeighborhoodConnectedImageFilter::initClass();
	SoItkContourDirectedMeanDistanceImageFilter::initClass();
	SoItkSignedDanielssonDistanceMapImageFilter::initClass();
	SoItkInPlaceImageFilter::initClass();
	SoItkGradientMagnitudeRecursiveGaussianImageFilter::initClass();
	SoItkTernaryFunctorImageFilter::initClass();
	SoItkTernaryAddImageFilter::initClass();
	SoItkTernaryMagnitudeSquaredImageFilter::initClass();
	SoItkTernaryMagnitudeImageFilter::initClass();
	SoItkPasteImageFilter::initClass();
	SoItkBinaryFunctorImageFilter::initClass();
	SoItkAndImageFilter::initClass();
	SoItkAtan2ImageFilter::initClass();
	SoItkWeightedAddImageFilter::initClass();
	SoItkConstrainedValueDifferenceImageFilter::initClass();
	SoItkAddImageFilter::initClass();
	SoItkMinimumImageFilter::initClass();
	SoItkXorImageFilter::initClass();
	SoItkMaskImageFilter::initClass();
	SoItkMultiplyImageFilter::initClass();
	SoItkBinaryMagnitudeImageFilter::initClass();
	SoItkConstrainedValueAdditionImageFilter::initClass();
	SoItkDivideImageFilter::initClass();
	SoItkOrImageFilter::initClass();
	SoItkSquaredDifferenceImageFilter::initClass();
	SoItkSubtractImageFilter::initClass();
	SoItkAbsoluteValueDifferenceImageFilter::initClass();
	SoItkMaximumImageFilter::initClass();
	SoItkMaskNegatedImageFilter::initClass();
	SoItkThresholdImageFilter::initClass();
	SoItkUnaryFunctorImageFilter::initClass();
	SoItkCosImageFilter::initClass();
	SoItkNotImageFilter::initClass();
	SoItkRescaleIntensityImageFilter::initClass();
	SoItkAsinImageFilter::initClass();
	SoItkSigmoidImageFilter::initClass();
	SoItkSqrtImageFilter::initClass();
	SoItkBoundedReciprocalImageFilter::initClass();
	SoItkTanImageFilter::initClass();
	SoItkSquareImageFilter::initClass();
	SoItkExpImageFilter::initClass();
	SoItkExpNegativeImageFilter::initClass();
	SoItkSinImageFilter::initClass();
	SoItkAtanImageFilter::initClass();
	SoItkAcosImageFilter::initClass();
	SoItkLogImageFilter::initClass();
	SoItkIntensityWindowingImageFilter::initClass();
	SoItkAbsImageFilter::initClass();
	SoItkCastImageFilter::initClass();
	SoItkLog10ImageFilter::initClass();
	SoItkBinaryThresholdImageFilter::initClass();
	SoItkFiniteDifferenceImageFilter::initClass();
	SoItkDenseFiniteDifferenceImageFilter::initClass();
	SoItkCurvatureFlowImageFilter::initClass();
	SoItkMinMaxCurvatureFlowImageFilter::initClass();
	SoItkBinaryMinMaxCurvatureFlowImageFilter::initClass();
	SoItkAnisotropicDiffusionImageFilter::initClass();
	SoItkCurvatureAnisotropicDiffusionImageFilter::initClass();
	SoItkGradientAnisotropicDiffusionImageFilter::initClass();
	SoItkSparseFieldLevelSetImageFilter::initClass();
	SoItkSegmentationLevelSetImageFilter::initClass();
	SoItkGeodesicActiveContourLevelSetImageFilter::initClass();
	SoItkShapeDetectionLevelSetImageFilter::initClass();
	SoItkThresholdSegmentationLevelSetImageFilter::initClass();
	SoItkLaplacianSegmentationLevelSetImageFilter::initClass();
	SoItkCannySegmentationLevelSetImageFilter::initClass();
	SoItkShapePriorSegmentationLevelSetImageFilter::initClass();
	SoItkGeodesicActiveContourShapePriorLevelSetImageFilter::initClass();
	SoItkCurvesLevelSetImageFilter::initClass();
	SoItkSparseFieldFourthOrderLevelSetImageFilter::initClass();
	SoItkIsotropicFourthOrderLevelSetImageFilter::initClass();
	SoItkAnisotropicFourthOrderLevelSetImageFilter::initClass();
	SoItkUnsharpMaskLevelSetImageFilter::initClass();
	SoItkAntiAliasBinaryImageFilter::initClass();
	SoItkNaryFunctorImageFilter::initClass();
	SoItkNaryMaximumImageFilter::initClass();
	SoItkNaryAddImageFilter::initClass();
	SoItkRelabelComponentImageFilter::initClass();
	SoItkLaplacianImageFilter::initClass();
	SoItkTobogganImageFilter::initClass();
	SoItkMultiResolutionPyramidImageFilter::initClass();
	SoItkZeroCrossingImageFilter::initClass();
	SoItkMinimumMaximumImageFilter::initClass();
	SoItkCannyEdgeDetectionImageFilter::initClass();
	SoItkReconstructionByDilationImageFilter::initClass();
	SoItkNormalizeImageFilter::initClass();
	SoItkAccumulateImageFilter::initClass();
	SoItkRecursiveSeparableImageFilter::initClass();
	SoItkRecursiveGaussianImageFilter::initClass();
	SoItkZeroCrossingBasedEdgeDetectionImageFilter::initClass();
	SoItkGrayscaleConnectedOpeningImageFilter::initClass();
	SoItkGrayscaleConnectedClosingImageFilter::initClass();
	SoItkWatershedImageFilter::initClass();
	SoItkSTAPLEImageFilter::initClass();
#ifdef BUILD_WITH_ITK_PATENTED
	SoItkSimpleFuzzyConnectednessImageFilterBase::initClass();
	SoItkSimpleFuzzyConnectednessScalarImageFilter::initClass();
#endif
	SoItkGrayscaleMorphologicalOpeningImageFilter::initClass();
	//SoItkLazyEdgeDetectionImageFilter3D::initClass();
	SoItkGrayscaleGrindPeakImageFilter::initClass();
	SoItkDerivativeImageFilter::initClass();
	SoItkGrayscaleGeodesicDilateImageFilter::initClass();
	SoItkOpeningByReconstructionImageFilter::initClass();
	SoItkReconstructionByErosionImageFilter::initClass();
	SoItkNonThreadedShrinkImageFilter::initClass();
	SoItkBlackTopHatImageFilter::initClass();
	SoItkCollidingFrontsImageFilter::initClass();
	SoItkTileImageFilter::initClass();
	SoItkInterpolateImageFilter::initClass();
	SoItkContourMeanDistanceImageFilter::initClass();
	SoItkDanielssonDistanceMapImageFilter::initClass();
	SoItkFastIncrementalBinaryDilateImageFilter::initClass();
	SoItkBinaryPruningImageFilter::initClass();
	SoItkDoubleThresholdImageFilter::initClass();
	SoItkHMaximaImageFilter::initClass();
	SoItkBinaryMedianImageFilter::initClass();
	SoItkConnectedComponentImageFilter::initClass();
	SoItkBinaryThinningImageFilter::initClass();
	SoItkShiftScaleImageFilter::initClass();
	SoItkDirectedHausdorffDistanceImageFilter::initClass();
	SoItkExtractImageFilter::initClass();
	SoItkCropImageFilter::initClass();
	SoItkConnectedThresholdImageFilter::initClass();
	SoItkNeighborhoodOperatorImageFilter::initClass();
	SoItkNormalizedCorrelationImageFilter::initClass();
	SoItkMaskNeighborhoodOperatorImageFilter::initClass();
	SoItkHMinimaImageFilter::initClass();
	SoItkGrayscaleGeodesicErodeImageFilter::initClass();
	SoItkVotingBinaryIterativeHoleFillingImageFilter::initClass();
	SoItkClosingByReconstructionImageFilter::initClass();
	SoItkJoinSeriesImageFilter::initClass();
	SoItkGrayscaleFillholeImageFilter::initClass();
	SoItkExpandImageFilter::initClass();
	SoItkCheckerBoardImageFilter::initClass();
	SoItkGrayscaleMorphologicalClosingImageFilter::initClass();
	SoItkFlipImageFilter::initClass();
	SoItkDiscreteGaussianImageFilter::initClass();
	SoItkBilateralImageFilter::initClass();
	SoItkHardConnectedComponentImageFilter::initClass();
	SoItkIsolatedConnectedImageFilter::initClass();
	SoItkOtsuMultipleThresholdsImageFilter::initClass();
	SoItkMeanImageFilter::initClass();
	SoItkBinomialBlurImageFilter::initClass();
	SoItkSimpleContourExtractorImageFilter::initClass();
	SoItkSobelEdgeDetectionImageFilter::initClass();
	SoItkMeshSource::initClass();
	SoItkImageToMeshFilter::initClass();
	SoItkBinaryMaskToNarrowBandPointSetFilter::initClass();
}
