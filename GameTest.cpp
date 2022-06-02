#include <iostream>
#include <cmath>
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

// #include "constants.h"
// #include "SDL_utils.h"
// #include "Game.h"
// #include "Gallery.h"

// #include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

#include "SDL_utils.h"
#include "Game.h"
#include "Gallery.h"

#include "constants.h"





struct TestStruct
{
    std::string testName;
    bool result;
    bool expected;
    std::string errorMsg;
};

void runTestLoop(TestStruct testCases[], int testSize){
    int i;
    
    for (i = 0; i< testSize; i++){
        std::cout << testCases[i].testName + ": ";
        if (testCases[i].result == testCases[i].expected)
        {
            std::cout << "PASSED \n";
        }
        else
        {
            std::cout << testCases[i].errorMsg;
            exit(1);
        }
    }
}


Position *getPositionByCellTypeInBoard(CellType cellType, Game &game){
  for (int i = 0; i < game.getWidth(); i++){
    for (int j = 0; j< game.getHeight(); j++){
      if(game.getSquares()[i][j] == cellType){
        Position p(i, j);
        Position *p_pointer = &p;
        return p_pointer;
      }
    }
  }
  return nullptr;
}


bool verifySnakeMoveTo(CellType cellType, GameStatus expectedStatus){

  Game gameTest(BOARD_WIDTH, BOARD_HEIGHT);
  Position p(rand()%gameTest.getWidth(), rand()%gameTest.getHeight());

  gameTest.setCellType(p, cellType);

  int previousScore = gameTest.getScore();
  gameTest.snakeMoveTo(p);
  
  if (cellType == CELL_OFF_BOARD || CELL_SNAKE){
    return gameTest.getGameStatus() == expectedStatus;
  }

  if (cellType == CELL_CHERRY){
    return previousScore + 1 == gameTest.getScore() && getPositionByCellTypeInBoard(CELL_CHERRY, gameTest) != nullptr;
  }

  return gameTest.getSquares()[p.x][p.y] == CELL_SNAKE;
}

bool verifySnakeLeave(CellType cellcheck){
  Game gameTest(BOARD_WIDTH, BOARD_HEIGHT);
  Position p(rand()%gameTest.getWidth(), rand()%gameTest.getHeight());
  
  gameTest.snakeLeave(p);
  return gameTest.getCellType(p) == cellcheck;

}

bool verifyCanChange()


class Test: public CPPUNIT_NS::TestCase {
  CPPUNIT_TEST_SUITE(Test);
  CPPUNIT_TEST(testSnakeMoveTo);
  CPPUNIT_TEST(testSnakeLeave);
  CPPUNIT_TEST(successTestExit);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp(void) {}
  void tearDown(void) {}

protected:

  void testSnakeMoveTo(void){
      int testSize = 4;
      std::string sharedName = "[testSnakeMoveTo] ";
      TestStruct snakeMoveToTestCases[testSize] =
        {
          {
            sharedName + "CELL_OFF_BOARD",
            verifySnakeMoveTo(CELL_OFF_BOARD, GAME_OVER),
            true,
            "GAME_OVER if snake moves to CELL_OFF_BOARD"
          },
          {
            sharedName + "CELL_SNAKE",
            verifySnakeMoveTo(CELL_SNAKE, GAME_OVER),
            true,
            "GAME_OVER if snake moves to CELL_SNAKE"
          },
          {
            sharedName + "CELL_CHERRY",
            verifySnakeMoveTo(CELL_CHERRY, GAME_RUNNING),
            true,
             "score should be increased, and new cherry should be added if snake moves to CELL_CHERRY"
          },
          {
            sharedName + "CELL_EMPTY",
            verifySnakeMoveTo(CELL_EMPTY, GAME_RUNNING),
            true,
            "snake should continue moving if snake moves to CELL_EMPTY"
          },
        };
      
        runTestLoop(snakeMoveToTestCases, testSize);
  }

   void testSnakeLeave(void){
      int testSize = 2;
      std::string sharedName = "[testSnakeLeave] ";
      TestStruct snakeLeaveTestCases[testSize] =
        {
          {
            sharedName + "CELL_OFF_BOARD",
            verifySnakeLeave(CELL_OFF_BOARD),
            false,
            "cell should be CELL_EMPTY is snake leaves"
          },
          {
            sharedName + "CELL_SNAKE",
            verifySnakeLeave(CELL_EMPTY),
            true,
            "cell should be CELL_EMPTY is snake leaves"
          }
        };
      
        runTestLoop(snakeLeaveTestCases, testSize);
  }


  void successTestExit(void) {
    std::cout << "all tests passed! \n";
    
  }

};


CPPUNIT_TEST_SUITE_REGISTRATION(Test);

int main()
{

  CPPUNIT_NS::TestResult controller;

  CPPUNIT_NS::TestResultCollector result;
  controller.addListener(&result);

  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener(&progress);

  CPPUNIT_NS::TestRunner runner;

  runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
  runner.run(controller);

  // return result.wasSuccessful() ? 0 : 1;
  return 0;
}