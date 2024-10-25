"""
Tic Tac Toe Player
"""
import copy
import math

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY], [EMPTY, EMPTY, EMPTY], [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    num_of_x = 0
    num_of_o = 0
    for row in board:
        for box in row:
            if box == X:
                num_of_x += 1
            elif box == O:
                num_of_o += 1
    if num_of_x > num_of_o:
        return O
    else:
        return X


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    foo = set()
    for i in range(3):
        for j in range(3):
            if board[i][j] == EMPTY:
                foo.add((i, j))
    return foo


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    board_copy = copy.deepcopy(board)
    if action not in actions(board):
        raise NameError("invalid action")
    row, col = action
    board_copy[row][col] = player(board_copy)
    return board_copy

def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    for i in range(3):
        if (
            (board[i][0] == X and board[i][1] == X and board[i][2] == X)
            or (board[0][i] == X and board[1][i] == X and board[2][i] == X)
            or (board[0][0] == X and board[1][1] == X and board[2][2] == X)
            or (board[2][0] == X and board[1][1] == X and board[0][2] == X)
        ):
            return X
        elif (
            (board[i][0] == O and board[i][1] == O and board[i][2] == O)
            or (board[0][i] == O and board[1][i] == O and board[2][i] == O)
            or (board[0][0] == O and board[1][1] == O and board[2][2] == O)
            or (board[2][0] == O and board[1][1] == O and board[0][2] == O)
        ):
            return O
    return None


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    if winner(board) != None:
        return True
    elif not actions(board):
        return True
    else:
        return False


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    if winner(board) == X:
        return 1
    elif winner(board) == O:
        return -1
    else:
        return 0


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """

    board = board

    def maxvalue(board):
        if terminal(board):
            return utility(board)
        v = -1
        for action in actions(board):
            v = max(v, minvalue(result(board, action)))
        return v

    def minvalue(board):
        if terminal(board):
            return utility(board)
        v = 1
        for action in actions(board):
            v = min(v, maxvalue(result(board, action)))
        return v

    if player(board) == O:
        return minvalue(board)
    else:
        return maxvalue(board)
