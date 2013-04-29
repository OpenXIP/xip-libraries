// Sylvain Jaume 2008

#include <iostream>
#include <fstream>
#include <cstring>

int main (int argc, char *argv[])
{
	if(argc != 3)
	{
	std::cout << "ERROR: Usage testedFileName expectedFileName" << std::endl;
	for(int i=0; i<argc; i++)
	{
		std::cout << "argv[" << i << "] " << argv[i] << std::endl;
	}
    return 1;//EXIT_FAILURE;
	}

  const char *testedFileName = argv[1];
  const char *expectedFileName = argv[2];

  std::cout << "<DartMeasurement name=\"TestFileName\" type=\"text/string\">";
  std::cout << testedFileName;
  std::cout << "</DartMeasurement>";

  std::cout <<  "<DartMeasurementFile name=\"TestImage\" type=\"image/png\">";
  std::cout << testedFileName;
  std::cout << "</DartMeasurementFile>";

  std::cout <<  "<DartMeasurementFile name=\"ExpectedImage\" type=\"image/png\">";
  std::cout << expectedFileName;
  std::cout << "</DartMeasurementFile>";

  std::cout << "tested file: " << testedFileName << std::endl;
  std::cout << "expected file: " << expectedFileName << std::endl;

  long begin, end;
  long testedFileSize = -1;
  long expectedFileSize = -1;

  std::ifstream testedFile(testedFileName);

  if (!testedFile.is_open())
  {
	  std::cout << "ERROR: cannot open tested file " << testedFileName << std::endl;
	  return 1;//EXIT_FAILURE;
  }

  begin = testedFile.tellg();
  testedFile.seekg (0, std::ios::end);
  end = testedFile.tellg();
  testedFile.close();
  testedFileSize = end - begin;

  std::cout << "<DartMeasurement name=\"testedFileSize\" type=\"text/string\">";
  std::cout << testedFileSize;
  std::cout << "</DartMeasurement>";

  std::cout << "tested file size " << testedFileSize << std::endl;

  std::ifstream expectedFile(expectedFileName);

  if (!expectedFile.is_open())
  {
	  std::cout << "ERROR: cannot open expected file " << expectedFileName << std::endl;
	  return 1;//EXIT_FAILURE;
  }

  begin = expectedFile.tellg();
  expectedFile.seekg (0, std::ios::end);
  end = expectedFile.tellg();
  expectedFile.close();
  expectedFileSize = end - begin;

  std::cout << "<DartMeasurement name=\"expectedFileSize\" type=\"text/string\">";
  std::cout << expectedFileSize;
  std::cout << "</DartMeasurement>";

  std::cout << "expected file size " << expectedFileSize << std::endl;

  if( testedFileSize == expectedFileSize )
  {
	  std::cout << "SUCCESS: testedFileSize == expectedFileSize" << std::endl;
	  return 0;//EXIT_SUCCESS;
  }

  char alternativeExpectedFileName[256];
  strcpy(alternativeExpectedFileName,expectedFileName);

  int fileNameLength = strlen(expectedFileName);
  strcpy(alternativeExpectedFileName+fileNameLength-4,"_1.png");

  std::cout << "alternativeExpectedFile " << alternativeExpectedFileName << std::endl;

  std::ifstream alternativeExpectedFile;
  alternativeExpectedFile.open(alternativeExpectedFileName);

  begin = alternativeExpectedFile.tellg();
  alternativeExpectedFile.seekg (0, std::ios::end);
  end = alternativeExpectedFile.tellg();
  alternativeExpectedFile.close();
  expectedFileSize = end - begin;

  std::cout << "<DartMeasurement name=\"second expected file fileSize\" type=\"text/string\">";
  std::cout << expectedFileSize;
  std::cout << "</DartMeasurement>";

  std::cout << "expected file size " << expectedFileSize << std::endl;

  if( testedFileSize == expectedFileSize )
  {
	  std::cout << "SUCCESS: testedFileSize == expectedFileSize" << std::endl;
	  return 0;//EXIT_SUCCESS;
  }
  else
  {
	  std::cout << "ERROR: testedFileSize != expectedFileSize" << std::endl;
	  return 1;//EXIT_FAILURE;
  }
#if 0
  if( filesize1 == filesize2 )
  {
	//std::cout << "file sizes match" << std::endl;
    xmlfile << "<filesize1>" << filesize1 << "</filesize1>" << std::endl;
    xmlfile << "<filesize2>" << filesize2 << "</filesize2>" << std::endl;
	xmlfile << "<result>PASSED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
	return 0;//EXIT_SUCCESS;
  }
  else
  {
	//std::cout << "ERROR: file sizes don't match" << std::endl;
	//std::cout << "filesize1 : " << filesize1 << " bytes.\n";
    //std::cout << "filesize2 : " << filesize2 << " bytes.\n";
    xmlfile << "<filesize1>" << filesize1 << "</filesize1>" << std::endl;
    xmlfile << "<filesize2>" << filesize2 << "</filesize2>" << std::endl;
	xmlfile << "<result>FAILED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
	return 1;//EXIT_FAILURE;
  }
#endif
}

