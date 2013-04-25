#include <iostream>
#include <fstream>
#include "vtkPNGReader.h"
#include "vtkImageData.h"

int main (int argc, char *argv[])
{
	if(argc != 4)
	{
	std::cout << "ERROR: Usage filename1 filename2 xmlfile" << std::endl;
	for(int i=0; i<argc; i++)
	{
		std::cout << "argv[" << i << "] " << argv[i] << std::endl;
	}
    return EXIT_FAILURE;
	}

  const char *filename1 = argv[1];
  const char *filename2 = argv[2];
  const char *xmlfilename = argv[3];

  std::cout << "Testing " << filename1 << std::endl;
  //std::cout << "filename2 : " << filename2 << std::endl;
  //std::cout << "xmlfilename : " << xmlfilename << std::endl;

  //std::ofstream removefile(xmlfilename);
  //removefile.close();

  std::ofstream xmlfile;
  xmlfile.open (xmlfilename);
  xmlfile << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << std::endl;
  xmlfile << "<?xml-stylesheet type=\"text/xsl\" href=\"xipresult.xsl\"?>" << std::endl;
  xmlfile << "<newtest>" << std::endl;

  xmlfile << "<filename1>" << filename1 << "</filename1>" << std::endl;
  xmlfile << "<filename2>" << filename2 << "</filename2>" << std::endl;

  long begin, end;
  long filesize1 = -1;
  long filesize2 = -1;

  std::ifstream file1(filename1);

  // try to open file

  if (!file1.is_open())
  {
	xmlfile << "<error>failed to open file1</error>" << std::endl;
	xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
	return EXIT_FAILURE;
  }

  begin = file1.tellg();
  file1.seekg (0, std::ios::end);
  end = file1.tellg();
  file1.close();
  filesize1 = end - begin;

  std::ifstream file2(filename2);

  if (!file2.is_open())
  {
	xmlfile << "<error>failed to open file2</error>" << std::endl;
	xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
	return EXIT_FAILURE;
  }

  begin = file2.tellg();
  file2.seekg (0, std::ios::end);
  end = file2.tellg();
  file2.close();
  filesize2 = end - begin;

  xmlfile << "<filesize1>" << filesize1 << "</filesize1>" << std::endl;
  xmlfile << "<filesize2>" << filesize2 << "</filesize2>" << std::endl;

  if( filesize1 != filesize2 )
  {
	xmlfile << "<error>files have different sizes</error>" << std::endl;
	xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
	return EXIT_FAILURE;
  }

  vtkPNGReader *PNGReader1 = vtkPNGReader::New();
  PNGReader1->SetFileName(filename1);

  vtkPNGReader *PNGReader2 = vtkPNGReader::New();
  PNGReader2->SetFileName(filename2);

  //xmlfile << "<canreadfile1>" << PNGReader1->CanReadFile(filename1) << "</canreadfile1>" << std::endl;
  //xmlfile << "<canreadfile2>" << PNGReader2->CanReadFile(filename2) << "</canreadfile2>" << std::endl;

  if( !PNGReader1->CanReadFile(filename1) )
    {
	xmlfile << "<error>cannot read png file1</error>" << std::endl;
	xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
	return EXIT_FAILURE;
    }

  if( !PNGReader2->CanReadFile(filename2) )
	{
	xmlfile << "<error>cannot read png file2</error>" << std::endl;
	xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
	return EXIT_FAILURE;
    }

  PNGReader1->Update();
  PNGReader2->Update();

  //xmlfile << "<code1>" << PNGReader1->GetErrorCode() << "</code1>" << std::endl;
  //xmlfile << "<code2>" << PNGReader2->GetErrorCode() << "</code2>" << std::endl;

  if( PNGReader1->GetErrorCode() )
    {
    xmlfile << "<error>failed to read png file1</error>" << std::endl;
    xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
	return EXIT_FAILURE;
    }

  if( PNGReader2->GetErrorCode() )
    {
    xmlfile << "<error>failed to read png file2</error>" << std::endl;
    xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
	return EXIT_FAILURE;
    }

  // compare pixel values

  int numPts = PNGReader1->GetOutput()->GetNumberOfPoints();
  int numComps = PNGReader1->GetOutput()->GetNumberOfScalarComponents();

  if ( PNGReader2->GetOutput()->GetNumberOfPoints() != numPts )
    {
    xmlfile << "<error>image1 has " << numPts << " while image2 has "
		<< PNGReader2->GetOutput()->GetNumberOfPoints() << std::endl;
    xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
	return EXIT_FAILURE;
    }

  if ( PNGReader2->GetOutput()->GetNumberOfScalarComponents() != numComps )
    {
    xmlfile << "<error>image1 has " << numComps << " while image2 has "
		<< PNGReader2->GetOutput()->GetNumberOfScalarComponents() << std::endl;
    xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
	return EXIT_FAILURE;
    }

  if( PNGReader1->GetOutput()->GetScalarType() != VTK_UNSIGNED_CHAR )
    {
    xmlfile << "<error>image1 pixel type is not UCHAR. Type is "
		<< PNGReader1->GetOutput()->GetScalarType() << std::endl;
    xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
	return EXIT_FAILURE;
    }

  if( PNGReader2->GetOutput()->GetScalarType() != VTK_UNSIGNED_CHAR )
    {
    xmlfile << "<error>image2 pixel type is not UCHAR. Type is "
		<< PNGReader2->GetOutput()->GetScalarType() << std::endl;
    xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
	return EXIT_FAILURE;
    }

  unsigned char *imagePtr1 = (unsigned char*)PNGReader1->GetOutput()->GetScalarPointer();
  unsigned char *imagePtr2 = (unsigned char*)PNGReader2->GetOutput()->GetScalarPointer();

  long numDiffPixels = 0;

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

  //xmlfile << "<numDiffPixels>" << numDiffPixels << "</numDiffPixels>" << std::endl;

  if( numDiffPixels )
    {
	xmlfile << "<error>number of pixels with different values " << numDiffPixels << "</error>" << std::endl;
    xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
	return EXIT_FAILURE;
    }

  xmlfile << "<result>PASSED</result>" << std::endl;
  xmlfile << "</newtest>" << std::endl;
  xmlfile.close();

  return EXIT_SUCCESS;
}