/*****************************************
normalizeProperly_cdf
Purpose:  This file properly normalizes an input file produced with
          given Tevatron Run II luminosity,
          producing an output file corresponding to the actual 
          luminosity recorded at Tevatron Run II.
*****************************************/

#include <iostream>
#include "Validation/VstQuaeroUtils/interface/Luminosity.hh"
#include "Validation/VstQuaeroUtils/interface/QuaeroItemFile.hh"
#include "Validation/VstQuaeroUtils/interface/QuaeroEvent.hh"
using namespace std;


void normalizeProperly_cdf(string infilename, Luminosity inLumi,
			   string outfilename, Luminosity outLumi)
{

  //cout << "  file names:  " << infilename << " -> " << outfilename << endl;
  cout << "      normalizeProperly_cdf    " << endl;
  cout << "          ppbar at 1960: " << inLumi.getLuminosity("pb^-1") << " -> " << outLumi.getLuminosity("pb^-1") << "pb^-1" << endl;

  QuaeroItemFile<QuaeroEvent> eventFile(infilename);
  ofstream fout(outfilename.c_str());
  QuaeroEvent event;
  string eventType;
  double z=0;
  if(inLumi.getLuminosity("pb^-1")>=0)
    z = outLumi.getLuminosity("pb^-1")/inLumi.getLuminosity("pb^-1");
  while(eventFile.nextEvent(event))
    {
      if((event.getCollisionType()=="ppbar")&&
	 (fabs(event.getRootS()-1960)<1))
	event.reWeight(event.getWeight()*z);
      else
	{
	  cout << "ERROR!  Event " << event << " does not have allowed center-of-mass energy in normalizeProperly routine." << endl;
	  exit(1);
	}
      fout << event << endl;
    }
  fout.close();
  return;
}


int main(int argc, char* argv[])
{
  if((argc!=5))
    {
      cout << "normalizeProperly_cdf <inputFile> <inLumi> <outputFile> <outlumi>" << endl;
      exit(1);
    }

  string infilename = argv[1];
  string outfilename = argv[3];
  Luminosity inLumi(argv[2]);
  Luminosity outLumi(argv[4]);
  normalizeProperly_cdf(infilename, inLumi,
		       outfilename, outLumi);
  return 0;
}



