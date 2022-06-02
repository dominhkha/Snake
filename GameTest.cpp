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


Game gameTest(BOARD_WIDTH, BOARD_HEIGHT);


struct TestStruct
{
    std::string testName;
    bool result;
    bool expected;
    std::string errorMsg;
};


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

  // SDL_Window* window;
  // SDL_Renderer* renderer;
  // initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  // Gallery* gallery = new Gallery(renderer);
  // SDL_Event e;
  Position p(1, 2);
  gameTest.setCellType(p, cellType);

  // renderSplashScreen();
  // renderGamePlay(renderer, game, gallery);

  int previousScore = gameTest.getScore();
  int previousCherry = gameTest.getSnake().getNumCherry();
  gameTest.snakeMoveTo(p);
  
  if (cellType == CELL_OFF_BOARD || CELL_SNAKE){
    return gameTest.getGameStatus() == expectedStatus;
  }
  if (cellType == CELL_CHERRY){
    if (getPositionByCellTypeInBoard(CELL_CHERRY, gameTest) == nullptr){
      return false;
    }
    return previousScore + 1 == gameTest.getScore() && previousCherry + 1 == gameTest.getSnake().getNumCherry();
  }
  // return gameTest.getSquares()[p.x][p.y] == CELL_SNAKE;
  return true;

}

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

class Test: public CPPUNIT_NS::TestCase {
  CPPUNIT_TEST_SUITE(Test);
  CPPUNIT_TEST(testSnakeMoveTo);
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
             "score should be increased, snake sould eat sherry and new cherry should be added if snake moves to CELL_CHERRY"
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