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
  int previousScore = gameTest.getScore();

  gameTest.setCellType(p, cellType);
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

bool verifyCanChange(Direction  current, Direction next){
  Game gameTest(BOARD_WIDTH, BOARD_HEIGHT);
  Position p(rand()%gameTest.getWidth(), rand()%gameTest.getHeight());

  return gameTest.canChange(current, next);
}

bool verifySetCellType(CellType expectedCellType){
  Game gameTest(BOARD_WIDTH, BOARD_HEIGHT);

  Position p(rand()%gameTest.getWidth(), rand()%gameTest.getHeight());

  // if outside of the board
  if(expectedCellType==CELL_OFF_BOARD){
    p.x = gameTest.getWidth() + 1;
    p.y = gameTest.getHeight() + 1;
  }

  gameTest.setCellType(p, expectedCellType);
  return gameTest.getCellType(p) == expectedCellType;
}


bool verifyAddCherry(){
  Game gameTest(BOARD_WIDTH, BOARD_HEIGHT);

  // remove current cherry position to add new one
  Position previousCherryPos = gameTest.getCherryPosition();  
  gameTest.setCellType(previousCherryPos, CELL_EMPTY);

  // add new cherry
  gameTest.addCherry();

  Position updatedCherryPos = gameTest.getCherryPosition();
  Position *actualCherryPos =  getPositionByCellTypeInBoard(CELL_CHERRY, gameTest);

  // if no cherry is added, return false
  if(actualCherryPos == nullptr){
    std::cout<<"none";
    return false;
  }
  std::cout<<updatedCherryPos.x;
  std::cout<<actualCherryPos->x;

  return updatedCherryPos.x == actualCherryPos->x && updatedCherryPos.y == actualCherryPos->y;
}

class Test: public CPPUNIT_NS::TestCase {
  CPPUNIT_TEST_SUITE(Test);
  CPPUNIT_TEST(testSnakeMoveTo);
  CPPUNIT_TEST(testSnakeLeave);
  CPPUNIT_TEST(testCanChange);
  CPPUNIT_TEST(testSetCellType);
  CPPUNIT_TEST(testAddCherry);

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
            sharedName + "should not be CELL_OFF_BOARD",
            verifySnakeLeave(CELL_OFF_BOARD),
            false,
            "cell should be CELL_EMPTY is snake leaves"
          },
          {
            sharedName + "should be CELL_EMPTY",
            verifySnakeLeave(CELL_EMPTY),
            true,
            "cell should be CELL_EMPTY is snake leaves"
          }
        };
      
        runTestLoop(snakeLeaveTestCases, testSize);
  }

  void testCanChange(void){
      int testSize = 4;
      std::string sharedName = "[testCanChange] ";
      TestStruct snakeLeaveTestCases[testSize] =
        {
          {
            sharedName + "canChange 1",
            verifyCanChange(UP, LEFT),
            true,
            "Snake can move if current is UP and next is LEFT direction"
          },
          {
            sharedName + "canChange 2",
            verifyCanChange(UP, DOWN),
            false,
            "Snake can not move if current is UP and next is DOWN direction"
          },
          {
            sharedName + "canChange 3",
            verifyCanChange(LEFT, UP),
            true,
            "Snake can move if current is LEFT and next is UP direction"
          },
          {
            sharedName + "canChange 3",
            verifyCanChange(LEFT, RIGHT),
            false,
            "Snake can not move if current is LEFT and next is RIGHT direction"
          },

        };
      
        runTestLoop(snakeLeaveTestCases, testSize);
  }
  
  void testSetCellType(void){
      int testSize = 4;
      std::string sharedName = "[testSetCellType] ";
      TestStruct snakeLeaveTestCases[testSize] =
        {
          {
            sharedName + "CELL_EMPTY",
            verifySetCellType(CELL_EMPTY),
            true,
            "Set cell as CELL_EMPTY"
          },
          {
            sharedName + "CELL_OFF_BOARD",
            verifySetCellType(CELL_OFF_BOARD),
            true,
            "Set cell as CELL_OFF_BOARD"
          }

        };
      
        runTestLoop(snakeLeaveTestCases, testSize);
  }

  void testAddCherry(void){

    int testSize = 1;
    std::string sharedName = "[testAddCherry] ";

    TestStruct snakeAddCherryTestCases[testSize] = 
    {
      {
        sharedName,
        verifyAddCherry(),
        true,
        "Cherry should be randomly added if snake have already eaten"
      },
    };

    runTestLoop(snakeAddCherryTestCases, testSize);
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