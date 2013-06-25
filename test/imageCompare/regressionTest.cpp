/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <iostream>
#include <fstream>
#include <string>

#include "vtkPNGReader.h"
#include "vtkPNGWriter.h"
#include "vtkImageData.h"
#include "vtkImageDifference.h"
#include "vtkImageExtractComponents.h"

#include <xip/utils/XipColor.h>
#include <xip/utils/XipBasicOperators.h>

/*
  Should we define a xip/test/XipTestConfiguration.h ???

  It could at least contain standardized return codes so we know
  what type of error we experienced.
*/

#include <math.h>

#include <stdio.h>
#include <string.h>

#ifndef _STDINT_H
typedef unsigned char uint8_t;
#endif

#ifdef _WINDOWS
#define strcasecmp _stricmp
#endif

#ifdef XIP_BASIC_OPS_NAMESPACE
using namespace XipBasicOps;
#endif

class diff_stats_op
{
public:
    typedef XipColorDifferenceCIE76<double> colordiff_t;

    enum constants {
        NUM_LEVELS = 4
    };

    diff_stats_op()
    {
        nlevels = NUM_LEVELS;

        errlevels[0].dL(2.0);
        errlevels[0].dE(2.0);
        errlevels[0].dH(2.0);

        errlevels[1].dL(6.0);
        errlevels[1].dE(6.0);
        errlevels[1].dH(6.0);

        errlevels[2].dL(12.0);
        errlevels[2].dE(12.0);
        errlevels[2].dH(12.0);

        errlevels[3].dL(20.0);
        errlevels[3].dE(20.0);
        errlevels[3].dH(20.0);

        errcount[0][0] = errcount[0][1] = errcount[0][2] = 0;
        errcount[1][0] = errcount[1][1] = errcount[1][2] = 0;
        errcount[2][0] = errcount[2][1] = errcount[2][2] = 0;
        errcount[3][0] = errcount[3][1] = errcount[3][2] = 0;

        rmse.set(0.0, 0.0, 0.0);

        diffmin.set(500.0, 500.0, 500.0);
        diffmax.set(0.0, 0.0, 0.0);

        pixelcount = 0;
    }

    template <class colorerr_t>
    void operator () (colorerr_t & err)
    {
        pixelcount++;

#if 0
        rmse[0] += err[0] * err[0];
        rmse[1] += err[1] * err[1];
        rmse[2] += err[2] * err[2];
#else
        rmse.dL(rmse.dL() + err.dL() * err.dL());
        rmse.dE(rmse.dE() + err.dE() * err.dE());
        rmse.dH(rmse.dH() + err.dH() * err.dH());
#endif

        diffmin.dL(min(diffmin.dL(), err.dL()));
        diffmax.dL(max(diffmax.dL(), err.dL()));
        diffmin.dE(min(diffmin.dE(), err.dE()));
        diffmax.dE(max(diffmax.dE(), err.dE()));
        diffmin.dH(min(diffmin.dH(), err.dH()));
        diffmax.dH(max(diffmax.dH(), err.dH()));

        int i;

        for (int j = 0; j < 3; j++)
        {
            for (i = 0; i < nlevels; i++)
            {
                if (err[j] < errlevels[i][j])
                    break;
            }

            if (i > 0) errcount[i-1][j] += 1.0;
        }
    }

    void report(FILE * out)
    {
        fprintf(out,
                "  Pixelcount....: %ld\n"
                "  RMSE dL.......: %.2f (%.2f)\n"
                "  RMSE dE.......: %.2f (%.2f)\n"
                "  RMSE dH.......: %.2f (%.2f)\n"
                "  Min/Max:\n"
                "    dL: %6.2f / %6.2f\n"
                "    dE: %6.2f / %6.2f\n"
                "    dH: %6.2f / %6.2f\n"
                "  Error levels:\n"
                "    dL: %6.2f, %6.2f, %6.2f, %6.2f\n"
                "    dE: %6.2f, %6.2f, %6.2f, %6.2f\n"
                "    dH: %6.2f, %6.2f, %6.2f, %6.2f\n",
                pixelcount,
                sqrt(rmse.dL() / double(pixelcount)), rmse[0],
                sqrt(rmse.dE() / double(pixelcount)), rmse[1],
                sqrt(rmse.dH() / double(pixelcount)), rmse[2],
                diffmin.dL(), diffmax.dL(),
                diffmin.dE(), diffmax.dE(),
                diffmin.dH(), diffmax.dH(),
                errcount[0].dL() * 100.0 / float(pixelcount),
                errcount[1].dL() * 100.0 / float(pixelcount),
                errcount[2].dL() * 100.0 / float(pixelcount),
                errcount[3].dL() * 100.0 / float(pixelcount),
                errcount[0].dE() * 100.0 / float(pixelcount),
                errcount[1].dE() * 100.0 / float(pixelcount),
                errcount[2].dE() * 100.0 / float(pixelcount),
                errcount[3].dE() * 100.0 / float(pixelcount),
                errcount[0].dH() * 100.0 / float(pixelcount),
                errcount[1].dH() * 100.0 / float(pixelcount),
                errcount[2].dH() * 100.0 / float(pixelcount),
                errcount[3].dH() * 100.0 / float(pixelcount));
    }

public:
    int nlevels;
    colordiff_t errlevels[NUM_LEVELS];
    colordiff_t errcount[NUM_LEVELS];
    colordiff_t rmse;
    colordiff_t diffmin;
    colordiff_t diffmax;
    long        pixelcount;
};


/*
  Template image traversal algorithm...
*/

template <class diff_op>
void diffImageCIELUV(diff_op & op, void * diff, void * img, void * orig,
                     int width, int height)
{
    typename diff_op::dstpixel_t * dst =
        reinterpret_cast<typename diff_op::dstpixel_t *>(diff);
    typename diff_op::srcpixel_t * src1 =
        reinterpret_cast<typename diff_op::srcpixel_t *>(img);
    typename diff_op::srcpixel_t * src2 =
        reinterpret_cast<typename diff_op::srcpixel_t *>(orig);

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            op(dst[col], src1[col], src2[col]);
        }

        dst += width;
        src1 += width;
        src2 += width;
    }
}


/*
  diff_operator_rgb_t

  Template pixel processing operator for RGB pixels to CIE76 Color
  difference (dL, dE, dH) output data.
*/

template <class dctp, class sctp, class stat_op>
class diff_operator_rgb_t
{
public:
    typedef XipColorDifferenceCIE76<dctp> dstpixel_t;
    typedef XipColorRGB<sctp> srcpixel_t;

    diff_operator_rgb_t(dctp dstrange, sctp srcrange, stat_op & stat) :
        statop(stat)
    {
        dstscale[0] = 2.55 * float(dstrange) / 255.0;
        dstscale[1] = 2.55 * float(dstrange) / 255.0;
        dstscale[2] = 2.55 * float(dstrange) / 255.0;

        srcscale[0] = srcscale[1] = srcscale[2] = 1.0 / float(srcrange);

        dstmin = 0;
        dstmax = dstrange;
    }

    inline void operator () (dstpixel_t & dst,
                             srcpixel_t & src1, srcpixel_t & src2)
    {
        cf1[0] = src1.r() * srcscale[0];
        cf1[1] = src1.g() * srcscale[1];
        cf1[2] = src1.b() * srcscale[2];

        cf2[0] = src2.r() * srcscale[0];
        cf2[1] = src2.g() * srcscale[1];
        cf2[2] = src2.b() * srcscale[2];

        XipColorConvert(luv1, cf1);
        XipColorConvert(luv2, cf2);

        XipColorDifference(diff, luv1, luv2);

#ifndef _WINDOWS
        if (isnan(diff.dH())) {
            printf("Strange Hue difference:\n"
                   "  Color 1: Luv = %f, %f, %f,  RGB = %d,%d,%d\n"
                   "  Color 2: Luv = %f, %f, %f,  RGB = %d,%d,%d\n"
                   "  Diff: dL = %f, dE = %f, dH = %f\n",
                   luv1.L(), luv1.u(), luv1.v(), src1.r(), src1.g(), src1.b(),
                   luv2.L(), luv2.u(), luv2.v(), src2.r(), src2.g(), src2.b(),
                   diff.dL(), diff.dE(), diff.dH());
        }
#endif
        statop(diff);

        /* CIE76 dL, dE, and dH */
        dst[0] = uint8_t(clamp(floorf(dstscale[0] * diff.dL() + 0.5),
                               dstmin, dstmax));
        dst[1] = uint8_t(clamp(floorf(dstscale[1] * diff.dE() + 0.5),
                               dstmin, dstmax));
        dst[2] = uint8_t(clamp(floorf(dstscale[2] * diff.dH() + 0.5),
                               dstmin, dstmax));
    }

protected:
    XipColorRGB<float>          cf1;
    XipColorRGB<float>          cf2;
    XipColorCIELuv<float>       luv1;
    XipColorCIELuv<float>       luv2;
    XipColorDifferenceCIE76<float> diff;

    float                       srcscale[3];
    float                       dstscale[3];
    dctp                        dstmin;
    dctp                        dstmax;

    stat_op &                   statop;
};


/*
  diff_operator_rgb_t

  Template pixel processing operator for RGBA pixels to CIE76 Color
  difference (dL, dE, dH) output data.
*/

template <class dctp, class sctp, class stat_op>
class diff_operator_rgba_t
{
public:
    typedef XipColorDifferenceCIE76<dctp> dstpixel_t;
    typedef XipColorRGBA<sctp> srcpixel_t;

    diff_operator_rgba_t(dctp dstrange, sctp srcrange, stat_op & stat) :
        statop(stat)
    {
        dstscale[0] = float(dstrange) / 100.0;
        dstscale[1] = float(dstrange) / 200.0;
        dstscale[2] = float(dstrange) / 255.0;

        srcscale[0] = srcscale[1] = srcscale[2] = 1.0 / float(srcrange);

        dstmin = 0;
        dstmax = dstrange;
    }

    inline void operator () (dstpixel_t & dst,
                             srcpixel_t & src1, srcpixel_t & src2)
    {
        float alpha = src1.a() * srcscale[3];
        cf1[0] = alpha * src1.r() * srcscale[0];
        cf1[1] = alpha * src1.g() * srcscale[1];
        cf1[2] = alpha * src1.b() * srcscale[2];

        alpha = src2.a() * srcscale[3];
        cf2[0] = alpha * src2.r() * srcscale[0];
        cf2[1] = alpha * src2.g() * srcscale[1];
        cf2[2] = alpha * src2.b() * srcscale[2];

        XipColorConvert(luv1, cf1);
        XipColorConvert(luv2, cf2);

        XipColorDifference(diff, luv1, luv2);

        statop(diff);

        /* CIE76 dL, dE, and dH */
        dst[0] = uint8_t(clamp(floorf(dstscale[0] * diff.dL() + 0.5),
                               dstmin, dstmax));
        dst[1] = uint8_t(clamp(floorf(dstscale[1] * diff.dE() + 0.5),
                               dstmin, dstmax));
        dst[2] = uint8_t(clamp(floorf(dstscale[2] * diff.dH() + 0.5),
                               dstmin, dstmax));
    }

protected:
    XipColorRGB<float>          cf1;
    XipColorRGB<float>          cf2;
    XipColorCIELuv<float>       luv1;
    XipColorCIELuv<float>       luv2;
    XipColorDifferenceCIE76<float> diff;

    float                       srcscale[3];
    float                       dstscale[3];
    dctp                        dstmin;
    dctp                        dstmax;

    stat_op &                   statop;
};


int main (int argc, char *argv[])
{
	if(argc != 5 && argc != 6)
	{
	std::cout << "ERROR: Usage testImage.png expectedImage.png differenceImage.png outputLog.xml [accuracy.txt]" << std::endl;
	for(int i=0; i<argc; i++)
	{
		std::cout << "argv[" << i << "] " << argv[i] << std::endl;
	}
    return EXIT_FAILURE;
	}

  const char *testFileName = argv[1];
  const char *expectedFileName = argv[2];
  const char *differenceFileName = argv[3];
  const char *xmlFileName = argv[4];
  const char *accuracyFileName = argc == 6 ? argv[5] : NULL;

  std::cout << "<DartMeasurement name=\"accuracyFileName\" type=\"text/string\">";
  std::cout << accuracyFileName ? accuracyFileName : "(none)";
  std::cout << "</DartMeasurement>" << std::endl;

  char *accuracy = "medium";

  if( accuracyFileName )
    {
	std::string line;
    std::ifstream accuracyFile(accuracyFileName);

    if (accuracyFile.is_open())
      {
      //while (! myfile.eof() )
      getline( accuracyFile, line );
	  //std::cout << line << std::endl;

	  if(line == "low") { accuracy = "low"; }
	  else if(line == "medium") { accuracy = "medium"; }
	  else if(line == "high") { accuracy = "high"; }
      }
	else
	{
		std::cout << "<DartMeasurement name=\"Error\" type=\"text/string\">";
		std::cout << "Unable to open file";
		std::cout << "</DartMeasurement>" << std::endl;
	}

    accuracyFile.close();
  }

  std::cout << "<DartMeasurement name=\"accuracy\" type=\"text/string\">";
  std::cout << accuracy;
  std::cout << "</DartMeasurement>" << std::endl;

  std::ofstream removeFile(xmlFileName);
  removeFile.close();

  std::ofstream xmlfile;
  xmlfile.open (xmlFileName);
  xmlfile << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << std::endl;
  xmlfile << "<?xml-stylesheet type=\"text/xsl\" href=\"xipresult.xsl\"?>" << std::endl;
  xmlfile << "<newtest>" << std::endl;

  xmlfile << "<testFileName>" << testFileName << "</testFileName>" << std::endl;
  xmlfile << "<expectedFileName>" << expectedFileName << "</expectedFileName>" << std::endl;

  vtkPNGReader *testReader = vtkPNGReader::New();
  vtkPNGReader *expectedReader = vtkPNGReader::New();

  if( !testReader->CanReadFile(testFileName) )
    {
	std::cout << "<DartMeasurement name=\"Error\" type=\"text/string\">";
	std::cout << "ERROR: failed to read file " << testFileName;
	std::cout << "</DartMeasurement>" << std::endl;
    xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
    testReader->Delete();
    expectedReader->Delete();
	return EXIT_FAILURE;
    }

  if( !expectedReader->CanReadFile(expectedFileName) )
    {
	std::cout << "<DartMeasurement name=\"Error\" type=\"text/string\">";
	std::cout << "ERROR: failed to read file " << expectedFileName;
	std::cout << "</DartMeasurement>" << std::endl;
	xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
    testReader->Delete();
    expectedReader->Delete();
	return EXIT_FAILURE;
    }

  testReader->SetFileName(testFileName);
  testReader->Update();

  expectedReader->SetFileName(expectedFileName);
  expectedReader->Update();

  if( testReader->GetErrorCode() )
    {
	std::cout << "<DartMeasurement name=\"Error\" type=\"text/string\">";
	std::cout << "ERROR: failed to read file " << testFileName;
	std::cout << "</DartMeasurement>" << std::endl;
    xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
    testReader->Delete();
    expectedReader->Delete();
	return EXIT_FAILURE;
    }

  if( expectedReader->GetErrorCode() )
    {
	std::cout << "<DartMeasurement name=\"Error\" type=\"text/string\">";
	std::cout << "ERROR: failed to read file " << expectedFileName;
	std::cout << "</DartMeasurement>" << std::endl;
	xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
    testReader->Delete();
    expectedReader->Delete();
	return EXIT_FAILURE;
    }

  // compare pixel values

  int testDim[3], expectedDim[3];

  testReader->GetOutput()->GetDimensions(testDim);
  expectedReader->GetOutput()->GetDimensions(expectedDim);
#if 0
  std::cout << "testDim " << testDim[0]
  << " " << testDim[1]
  << " " << testDim[2] << std::endl;

  std::cout << "expectedDim " << expectedDim[0]
  << " " << expectedDim[1]
  << " " << expectedDim[2] << std::endl;
#endif
  if(testDim[0] < 1
  || testDim[1] < 1
  || testDim[2] != 1)
  {
	std::cout << "<DartMeasurement name=\"Error\" type=\"text/string\">";
	std::cout << "ERROR: wrong image dimensions";
	std::cout << "</DartMeasurement>" << std::endl;
	xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
    testReader->Delete();
    expectedReader->Delete();
	return EXIT_FAILURE;    
  }

  if(testDim[0] != expectedDim[0]
  || testDim[1] != expectedDim[1]
  || testDim[2] != expectedDim[2])
  {
	std::cout << "<DartMeasurement name=\"Error\" type=\"text/string\">";
	std::cout << "ERROR: different image dimensions";
	std::cout << "</DartMeasurement>" << std::endl;
	xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
    testReader->Delete();
    expectedReader->Delete();
	return EXIT_FAILURE;    
  }
  
  if( testReader->GetOutput()->GetScalarType() != VTK_UNSIGNED_CHAR )
    {
	std::cout << "<DartMeasurement name=\"Error\" type=\"text/string\">";
	std::cout << "ERROR: scalar type in not uchar";
	std::cout << "</DartMeasurement>" << std::endl;
	xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
    testReader->Delete();
    expectedReader->Delete();
	return EXIT_FAILURE;
    }

  if( expectedReader->GetOutput()->GetScalarType() != VTK_UNSIGNED_CHAR )
    {
	std::cout << "<DartMeasurement name=\"Error\" type=\"text/string\">";
	std::cout << "ERROR: scalar type in not uchar";
	std::cout << "</DartMeasurement>" << std::endl;
	xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
    testReader->Delete();
    expectedReader->Delete();
	return EXIT_FAILURE;
    }

  int testNumComps = testReader->GetOutput()->GetNumberOfScalarComponents();
  int expectedNumComps = expectedReader->GetOutput()->GetNumberOfScalarComponents();

  std::cout << "testNumComps " << testNumComps << std::endl;
  std::cout << "expectedNumComps " << expectedNumComps << std::endl;

  if( expectedNumComps != 3 )
    {
	std::cout << "<DartMeasurement name=\"Error\" type=\"text/string\">";
	std::cout << "ERROR: expected image must have 3 components. ";
	std::cout << "It has " << expectedNumComps << " components.";
	std::cout << "</DartMeasurement>" << std::endl;
	xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
    testReader->Delete();
    expectedReader->Delete();
	return EXIT_FAILURE;
    }

  if( testNumComps != 3 && testNumComps != 4 )
    {
	std::cout << "<DartMeasurement name=\"Error\" type=\"text/string\">";
	std::cout << "ERROR: different number of components";
	std::cout << "</DartMeasurement>" << std::endl;
	xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
    testReader->Delete();
    expectedReader->Delete();
	return EXIT_FAILURE;
    }

  vtkImageExtractComponents *imageExtractComponents = vtkImageExtractComponents::New();
  imageExtractComponents->SetInputConnection(testReader->GetOutputPort());
  testReader->Delete();
  imageExtractComponents->SetComponents(0,1,2);
  imageExtractComponents->Update();

  int numPixels = testDim[0] * testDim[1] * testDim[2];

  unsigned char *imagePtr1 = (unsigned char*)imageExtractComponents->GetOutput()->GetScalarPointer();
  unsigned char *imagePtr2 = (unsigned char*)expectedReader->GetOutput()->GetScalarPointer();
  unsigned char *diffImage = new unsigned char[numPixels * testNumComps];

  long numDiffPixels = 0;
#if 0
  for(int i=0; i<numPts; i++)
    {
	for(int j=0; j<numComps; j++)
	  {
      if(*imagePtr1 != *imagePtr2)
	    {
        numDiffPixels++;
	    }
	  
	  imagePtr1++;
	  imagePtr2++;
	  }
    }
#else
  diff_stats_op stat;
  diff_operator_rgb_t<uint8_t, uint8_t, diff_stats_op>
      op(255, 255, stat);
  diffImageCIELUV(op, diffImage, imagePtr1, imagePtr2, numPixels, 1);
  stat.report(stdout);
  diff_stats_op::colordiff_t * errcnt = stat.errcount;

  numDiffPixels = long(errcnt[0].dE() + errcnt[1].dE() +
		               errcnt[2].dE() + errcnt[3].dE());
#endif
  vtkImageData *differenceImage = vtkImageData::New();
  differenceImage->DeepCopy(imageExtractComponents->GetOutput());

  unsigned char *differencePtr = (unsigned char *)differenceImage->GetScalarPointer();
  memcpy(differencePtr,diffImage,3*numPixels*sizeof(unsigned char));

  vtkPNGWriter *differenceWriter = vtkPNGWriter::New();
  differenceWriter->SetInput(differenceImage);
  differenceWriter->SetFileName(differenceFileName);
  differenceWriter->Write();
  differenceWriter->Delete();
  differenceImage->Delete();

  double dE = sqrt(stat.rmse.dE() / double(stat.pixelcount));
  double dL = sqrt(stat.rmse.dL() / double(stat.pixelcount));
  double dH = sqrt(stat.rmse.dH() / double(stat.pixelcount));
  
  std::cout << "<DartMeasurement name=\"rmse dE\" type=\"text/string\">";
  std::cout << dE;
  std::cout << "</DartMeasurement>" << std::endl;

  std::cout << "<DartMeasurement name=\"rmse dL\" type=\"text/string\">";
  std::cout << dL;
  std::cout << "</DartMeasurement>" << std::endl;

  std::cout << "<DartMeasurement name=\"rmse dH\" type=\"text/string\">";
  std::cout << dH;
  std::cout << "</DartMeasurement>" << std::endl;

  xmlfile << "<rmse>" << std::endl;
  xmlfile << "<dE>" << dE << "</dE>" << std::endl;
  xmlfile << "<dL>" << dL << "</dL>" << std::endl;
  xmlfile << "<dH>" << dH << "</dH>" << std::endl;
  xmlfile << "</rmse>" << std::endl;
#if 0
  colordiff_t errlevels[NUM_LEVELS];
  colordiff_t errcount[NUM_LEVELS];
  colordiff_t rmse;
  colordiff_t diffmin;
  colordiff_t diffmax;
  long        pixelcount;
#endif
  std::cout << "<DartMeasurement name=\"numDiffPixels\" type=\"text/string\">";
  std::cout << numDiffPixels;
  std::cout << "</DartMeasurement>" << std::endl;

  xmlfile << "<numDiffPixels>" << numDiffPixels << "</numDiffPixels>" << std::endl;

  if( numDiffPixels )
    {
	xmlfile << "<error>number of pixels with different values " << numDiffPixels << "</error>" << std::endl;
    xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    }
  else
    {
    xmlfile << "<result>PASSED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
  }

  xmlfile.close();
  imageExtractComponents->Delete();
  expectedReader->Delete();

  if( dE > 0.5 )
    {  
    std::cout << "<DartMeasurement name=\"testFileName\" type=\"text/string\">";
    std::cout << testFileName;
    std::cout << "</DartMeasurement>" << std::endl;

    std::cout <<  "<DartMeasurementFile name=\"TestImage\" type=\"image/png\">";
    std::cout << testFileName;
    std::cout << "</DartMeasurementFile>" << std::endl;

    std::cout << "<DartMeasurement name=\"expectedFileName\" type=\"text/string\">";
    std::cout << expectedFileName;
    std::cout << "</DartMeasurement>" << std::endl;

    std::cout <<  "<DartMeasurementFile name=\"ExpectedImage\" type=\"image/png\">";
    std::cout << expectedFileName;
    std::cout << "</DartMeasurementFile>" << std::endl;

    std::cout << "<DartMeasurement name=\"DifferenceFileName\" type=\"text/string\">";
    std::cout << differenceFileName;
    std::cout << "</DartMeasurement>" << std::endl;

    std::cout <<  "<DartMeasurementFile name=\"DifferenceImage\" type=\"image/png\">";
    std::cout << differenceFileName;
    std::cout << "</DartMeasurementFile>" << std::endl;
    }
#if 0  
  std::cout << "dL " << stat.errcount[0].dL() * 100.0 / float(stat.pixelcount);
  std::cout << " " << stat.errcount[1].dL() * 100.0 / float(stat.pixelcount);
  std::cout << " " << stat.errcount[2].dL() * 100.0 / float(stat.pixelcount);
  std::cout << " " << stat.errcount[3].dL() * 100.0 / float(stat.pixelcount) << std::endl;
  
  std::cout << "dE " << stat.errcount[0].dE() * 100.0 / float(stat.pixelcount);
  std::cout << " " << stat.errcount[1].dE() * 100.0 / float(stat.pixelcount);
  std::cout << " " << stat.errcount[2].dE() * 100.0 / float(stat.pixelcount);
  std::cout << " " << stat.errcount[3].dE() * 100.0 / float(stat.pixelcount) << std::endl;
  
  std::cout << "dH " << stat.errcount[0].dH() * 100.0 / float(stat.pixelcount);
  std::cout << " " << stat.errcount[1].dH() * 100.0 / float(stat.pixelcount);
  std::cout << " " << stat.errcount[2].dH() * 100.0 / float(stat.pixelcount);
  std::cout << " " << stat.errcount[3].dH() * 100.0 / float(stat.pixelcount) << std::endl;
#endif
  // high: dE=0.5
  //  2-6  pixels: 1%
  //  6-12 pixels: 0.1%
  // 12-20 pixels: 0%
  //  >20  pixels: 0%

  // medium: dE=2.5
  //  2-6  pixels: 8%
  //  6-12 pixels: 4%
  // 12-20 pixels: 1%
  //  >20  pixels: 0.5%

  // low: dE=5
  //  2-6  pixels: 20%
  //  6-12 pixels: 10%
  // 12-20 pixels: 4%
  //  >20  pixels: 1%

  if( strcmp(accuracy,"low") == 0 )
  {
    if( dE < 5.0 )
	  {
      return EXIT_SUCCESS;
	  }
	else
	  {
      return EXIT_FAILURE;
	  }
  }

  else if( strcmp(accuracy,"medium") == 0 )
  {
    if( dE < 2.5 )
	  {
      return EXIT_SUCCESS;
	  }
	else
	  {
      return EXIT_FAILURE;
	  }
  }

  else if( strcmp(accuracy,"high") == 0 )
  {
    if( dE < 0.5 )
	  {
      return EXIT_SUCCESS;
	  }
	else
	  {
      return EXIT_FAILURE;
	  }
  }

  return EXIT_FAILURE;
}
