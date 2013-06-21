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

int main (int argc, char *argv[])
{
	if(argc != 5)
	{
	//std::cout << "ERROR: Usage filename1 filename2 xmlfile" << std::endl;
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

  if (!file1.is_open())
  {
	//std::cout << "ERROR: failed to open file1" << std::endl;
    xmlfile << "<filesize1>" << filesize1 << "</filesize1>" << std::endl;
    xmlfile << "<filesize2>" << filesize2 << "</filesize2>" << std::endl;
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
	//std::cout << "ERROR: failed to open file2" << std::endl;
	  xmlfile << "<filesize1>" << filesize1 << "</filesize1>" << std::endl;
    xmlfile << "<filesize2>" << filesize2 << "</filesize2>" << std::endl;
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

  if( filesize1 == filesize2 )
  {
	//std::cout << "file sizes match" << std::endl;
    xmlfile << "<filesize1>" << filesize1 << "</filesize1>" << std::endl;
    xmlfile << "<filesize2>" << filesize2 << "</filesize2>" << std::endl;
	xmlfile << "<result>PASSED</result>" << std::endl;
    xmlfile << "</newtest>" << std::endl;
    xmlfile.close();
	return EXIT_SUCCESS;
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
	return EXIT_FAILURE;
  }
}