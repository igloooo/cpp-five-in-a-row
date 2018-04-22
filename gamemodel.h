#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <iostream>
#include <map>
#include <vector>
#include "coordinate.h"
#include "stone.h"
using namespace std;

/*
 * Constant: REPRESENTATION
 * Usage: current_board[3][2] = REPRESENTATION["white"];
 * --------------------------------------------
 * This constant recorded the correponding value
 * of each color on the chess board.
 */
const map<string, int> REPRESENTATION = {{"black",1},{"white",-1},{"empty",0}};
/*
 * Constant: BOARDSIZE
 * Usage: BOARDSIZE.x
 * --------------------------------------------
 * This constant represents board size.
 */
const Coordinate BOARDSIZE(15,15);
/*
 * Constant: WHO_FIRST
 * ---------------------------------------------
 * This denotes the first player's color.
 */
const string WHO_FIRST = "black";
/* Constant: DIRECTIONS
 * ---------------------------------------------
 * It's a map represents four directions on the
 * board. "x"/"y" means the direction along which x/y
 * coordinate varies. "d" means diagonal, "a" means
 * anti-diagonal
 */
const map<string, Coordinate> DIRECTIONS = {{"x",Coordinate(1,0)},
                                            {"y",Coordinate(0,1)},
                                            {"d",Coordinate(1,1)},
                                            {"a",Coordinate(1,-1)}};

/*
 * Class GameModel
 * -----------------------------------------
 * This class records the state of the game
 * and offers method to retrieve board state,
 * history record, or to make move, retract move
 * etc.
 */

class GameModel
{
public:
    /*
     * Method: constructor
     * Usage: GameModel game();
     * --------------------------------------
     * This method initialize the parameters
     */
    GameModel();

    /*
     * Method: TakeMove
     * Usage: string result = game.TakeMove(xy)
     *        string result = game.TakeMove(x,y)
     * ---------------------------------------
     * This method is called when a new move is
     * to be taken. It returns "illegal""continuing"
     * "terminated" based on the outcome of the move.
     */
    string TakeMove(Coordinate xy);
    string TakeMove(int x, int y);

    /*
     * Method: CheckRule
     * Usage: string result = game.CheckRule(xy)
     *        string result = game.CheckRule(x,y)
     * ---------------------------------------
     * This method checks the rule and returns
     * "illegal""continuing""white""black""tie"
     * to denote the legitimacy and consequence
     * of the given move.
     */
    string CheckRule(Coordinate xy);//"illegal""continuing""white""black""tie"
    string CheckRule(int x, int y);

    /*
     * Method: EndGame
     * Usage: game.EndGame(winner)
     * --------------------------------------
     * This method ends the game and specify
     * the winner. If the game is already over
     * when the method is called, the winner
     * will not be changed.
     */
    bool EndGame(string winner);

    /*
     * Method: CancelLastMove
     * Usage: game.CancelLastMove()
     * --------------------------------------
     * This method restore the game to last
     * step. In PVE mode, it has to be called
     * twice.
     */
    bool CancelLastMove();


    /*
     * Method: at
     * Usage: Stone st = game.at(x,y)
     *        Stone st = game.at(xy)
     * ---------------------------------------
     * This method returns a Stone object, which
     * is a (x,y,color) pair to denote the state
     * at given place.
     */
    Stone at(Coordinate xy);
    Stone at(int x, int y);

    /*
     * Method: get_history_move
     * Usage: Stone st = game.get_history_move(round, color)
     *        Stone st = game.get_history_move(step)
     * ---------------------------------------
     * This method returns the move at the specifed
     * step or round.
     */
    Stone get_history_move(int round, string color);
    Stone get_history_move(int step);

    /*
     * Method: get_last_move
     * Usage: Stone last_move = game.get_last_move()
     * ----------------------------------------
     * This method returns last move that has been
     * taken.
     */
    Stone get_last_move();

    bool isFirstPlayer(string color);
    string get_whose_turn();
    bool isTerminated();
    string get_winner();
    int get_round();
    int get_steps();
    bool isEmptyBoard();
    int get_num_of_empty_places();
    string toString();

protected:
    string whose_turn;//"black""white""empty"
    bool terminated;
    string winner;//"black","white","tie","None"
    int round;//starts from 1

    vector<vector<int>> current_board;
    vector<Stone> history_moves;

    int num_of_empty_places;
};
ostream & operator<<(ostream & os, GameModel & rhs);
string ReverseColor(string color);

#endif // GAMEMODEL_H
