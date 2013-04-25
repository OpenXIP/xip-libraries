// Author Sylvain Jaume 2008
#include "vtkImageData.h"
#include "vtkPNGReader.h"
#include "vtkTesting.h"
#include "vtkPolyData.h"

int main(int argc, char *argv[])
{
  for(int i=0; i<argc; i++)
  {
  std::cout << __LINE__ << " argv[" << i << "] " << argv[i] << std::endl;
  }

  if(argc != 3)
  {
    std::cout << "ERROR: argc " << argc << std::endl;
    return EXIT_FAILURE;
  }

  vtkPNGReader *testPNGReader = vtkPNGReader::New();
  testPNGReader->SetFileName(argv[1]);
  testPNGReader->Update();

  vtkPNGReader *expectedPNGReader = vtkPNGReader::New();
  expectedPNGReader->SetFileName(argv[2]);
  expectedPNGReader->Update();

  vtkTesting *t = vtkTesting::New();

  for ( int cc = 1; cc < argc; cc ++ )
    {
    t->AddArgument(argv[cc]);
    }

//  Option 2:
//  t->AddArgument("-D");
//  t->AddArgument(my_data_dir);
//  t->AddArgument("-V");
//  t->AddArgument(my_valid_image);

  double threshold = 1.0;
  int res = t->RegressionTest(testPNGReader->GetOutput(), threshold);

  if ( res == vtkTesting::PASSED )
    {
      std::cout<<"Test passed"<<std::endl;
      return EXIT_SUCCESS;
    }
  else
    {
	  std::cout<<"Test failed"<<std::endl;
	  return EXIT_FAILURE;
    }
}
