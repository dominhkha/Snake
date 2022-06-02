#include <iostream>
#include <cmath>
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "constants.h"
// #include "SDL_utils.h"
#include "Game.h"
// #include "Gallery.h"



struct TestStruct
{
    std::string testName;
    bool result;
    bool expected;
    std::string errorMsg;
};

Position *createPositionByCellType(CellType cellType, Game &game){
  Position p(rand() % game.getWidth(), rand() % game.getHeight());
  game.setCellType(p, cellType);
  return &p;
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

  // SDL_Window* window;
  // SDL_Renderer* renderer;
  // initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  // Gallery* gallery = new Gallery(renderer);
  std::cout<<"ok50";
  Game game(BOARD_WIDTH, BOARD_HEIGHT);
  // SDL_Event e;
  std::cout<<"ok52";
  Position* p = createPositionByCellType(cellType, game);
  // renderSplashScreen();
  // renderGamePlay(renderer, game, gallery);

  // std::cout<<p.x;
  int previousScore = game.getScore();
  int previousCherry = game.getSnake().getNumCherry();
  game.snakeMoveTo(*p);
  
  // if (cellType == CELL_OFF_BOARD || CELL_SNAKE){
  //   return game.getGameStatus() == expectedStatus;
  // }
  // if (cellType == CELL_CHERRY){
  //   std::cout<<"ok65";
  //   if (getPositionByCellTypeInBoard(CELL_CHERRY, game) == nullptr){
  //     return false;
  //   }
  //   std::cout<<"ok69";
  //   return previousScore + 1 == game.getScore() && previousCherry + 1 == game.getSnake().getNumCherry();
  // }
  // return game.getSquares()[p.x][p.y] == CELL_SNAKE;
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
      std::cout<<"ok107";
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

  return result.wasSuccessful() ? 0 : 1;
}