#include <fstream>
#include <iostream>
#include <time.h>

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"

#include "Guest.h"

std::ofstream os;
using namespace std;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));


  //create a miner
  Miner* Bob = new Miner(ent_Miner_Bob);

  //create his wife
  MinersWife* Elsa = new MinersWife(ent_Elsa);

  // 새 인물 추가
  Guest* HeeSeung = new Guest(ent_HeeSeung);

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(HeeSeung);

  //run Bob and Elsa through a few Update calls
  for (int i=0; i<30; ++i)
  { 
    Bob->Update();
    Elsa->Update();

	HeeSeung->Update();

    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
  }

  //tidy up
  delete Bob;
  delete Elsa;
  delete HeeSeung;

  // 학번 이름 출력

  cout << endl << "2015182038 정희승" << endl;


  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






