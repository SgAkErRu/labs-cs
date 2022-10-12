import copy
from enum import Enum
import os
import random


class ReversiBoard:

    class BoardValue(Enum):
        EMPTY = 0,
        WHITE = 1,
        BLACK = 2

    class BoardDirection(Enum):
        LEFT = 0,
        RIGHT = 1,
        UP = 2,
        DOWN = 3,
        UP_LEFT = 4,
        UP_RIGHT = 5,
        DOWN_LEFT = 6,
        DOWN_RIGHT = 7

    BOARD_SIZE = 8

    PRINT_VALUES = {
        BoardValue.EMPTY: "*",
        BoardValue.WHITE: "W",
        BoardValue.BLACK: "B"
    }

    DIRECTION_OFFSETS: dict[BoardDirection, tuple[int, int]] = {
        BoardDirection.LEFT: (0, -1),
        BoardDirection.RIGHT: (0, 1),
        BoardDirection.UP: (1, 0),
        BoardDirection.DOWN: (-1, 0),
        BoardDirection.UP_LEFT: (-1, -1),
        BoardDirection.UP_RIGHT: (-1, 1),
        BoardDirection.DOWN_LEFT: (1, -1),
        BoardDirection.DOWN_RIGHT: (1, 1)
    }

    def __init__(self) -> None:
        self.gameMatrix = self.createGameMatrix()
        self.prepareGameMatrix()

    def createGameMatrix(self) -> list[list[BoardValue]]:
        gameMatrix = [self.BoardValue.EMPTY] * self.BOARD_SIZE

        for x in range(self.BOARD_SIZE):
            gameMatrix[x] = [self.BoardValue.EMPTY] * self.BOARD_SIZE

        return gameMatrix

    def prepareGameMatrix(self) -> None:
        # В начале игры в центр доски выставляются 4 фишки: чёрные на d5 и e4,
        # белые на d4 и e5.
        self.setCellValue("d5", self.BoardValue.BLACK)
        self.setCellValue("e4", self.BoardValue.BLACK)
        self.setCellValue("d4", self.BoardValue.WHITE)
        self.setCellValue("e5", self.BoardValue.WHITE)

    def printBoard(self) -> None:
        print("   ", end="")

        for x in range(1, self.BOARD_SIZE + 1):
            print(x, end="  ")

        print()

        letters = "ABCDEFGH"

        for i in range(0, self.BOARD_SIZE):
            print(letters[i], end="  ")

            for j in range(0, self.BOARD_SIZE):
                print(self.PRINT_VALUES[self.gameMatrix[i][j]], end="  ")

            print()

    def convertLetterToDigit(self, letter: str) -> int | None:
        switch = {
            'A': 0,
            'B': 1,
            'C': 2,
            'D': 3,
            'E': 4,
            'F': 5,
            'G': 6,
            'H': 7
        }

        return switch.get(letter.upper(), None)

    def convertDigitToLetter(self, digit: int) -> str | None:
        switch = {
            0: 'A',
            1: 'B',
            2: 'C',
            3: 'D',
            4: 'E',
            5: 'F',
            6: 'G',
            7: 'H'
        }

        return switch.get(digit, None)

    def getOpponentSide(self, side: BoardValue) -> BoardValue:
        if side == self.BoardValue.BLACK:
            return self.BoardValue.WHITE
        else:
            return self.BoardValue.BLACK

    def getCoordsByCell(self, cell: str) -> tuple[int, int]:
        i = self.convertLetterToDigit(cell[0])
        j = int(cell[1]) - 1
        return (i, j)

    def getCellByCoords(self, i: int, j: int) -> str:
        letter = self.convertDigitToLetter(i)
        digit = j + 1
        return letter + str(digit)

    def setCellValue(self, cell: str, value: BoardValue) -> None:
        (i, j) = self.getCoordsByCell(cell)
        self.gameMatrix[i][j] = value

    def setCellValueByCoords(self, i: int, j: int, value: BoardValue) -> None:
        self.gameMatrix[i][j] = value

    def checkInputCell(self, cell: str) -> bool:
        if len(cell) != 2:
            return False

        convertedLetter = self.convertLetterToDigit(cell[0])
        digit = int(cell[1]) if cell[1].isdigit() else None

        return (
            isinstance(convertedLetter, int)
            and isinstance(digit, int)
            and digit <= 8
        )

    def checkMoveDirection(
            self,
            i: int,
            j: int,
            value: BoardValue,
            direction: BoardDirection
    ) -> int:
        onDirection = False
        cellCount = 0

        directionI, directionJ = self.DIRECTION_OFFSETS[direction]

        for x in range(0, self.BOARD_SIZE - 1):
            i += directionI
            j += directionJ

            if (i < 0 or i >= self.BOARD_SIZE) or (
                    j < 0 or j >= self.BOARD_SIZE
            ):
                break

            cellX = self.gameMatrix[i][j]
            cellCount += 1

            if (cellX == self.BoardValue.EMPTY):
                break

            if (cellX == value):
                if cellCount >= 2:
                    onDirection = True
                break

        return cellCount if onDirection else 0

    def checkMove(
        self,
        i: int,
        j: int,
        value: BoardValue
    ) -> dict[BoardDirection, int]:

        directionMap: dict[self.BoardDirection, int] = {}

        for direction in self.BoardDirection:
            directionMap[direction] = self.checkMoveDirection(
                i, j, value, direction)

        return directionMap

    def checkCellEmptiness(self, i: int, j: int) -> bool:
        return self.gameMatrix[i][j] == self.BoardValue.EMPTY

    def makeMove(self, i: int, j: int, value: BoardValue) -> bool:
        isMoveMade = False

        if self.checkCellEmptiness(i, j) == False:
            return False

        directionMap = self.checkMove(i, j, value)

        for item in directionMap.items():
            direction, count = item

            if count > 0:
                self.setCells(i, j, value, direction, count)
                isMoveMade = True

        return isMoveMade

    def setCells(
            self,
            i: int,
            j: int,
            value: BoardValue,
            direction: BoardDirection,
            count: int
    ) -> None:
        self.setCellValueByCoords(i, j, value)

        directionI, directionJ = self.DIRECTION_OFFSETS[direction]

        for x in range(0, count):
            i += directionI
            j += directionJ
            self.setCellValueByCoords(i, j, value)

    def getSideCount(self, side: BoardValue) -> int:
        count = 0
        for i in range(0, self.BOARD_SIZE):
            for j in range(0, self.BOARD_SIZE):
                if self.gameMatrix[i][j] == side:
                    count += 1
        return count

    def getAvailableMoves(self, side: BoardValue) -> list[tuple[int, int]]:

        result = []

        for i in range(0, self.BOARD_SIZE):
            for j in range(0, self.BOARD_SIZE):
                if self.checkCellEmptiness(i, j):
                    directionMap = self.checkMove(i, j, side)

                    isValidMove = False

                    for x in directionMap.values():
                        if x > 0:
                            isValidMove = True

                    if isValidMove:
                        result.append((i, j))

        return result


class Player:
    def __init__(self, side: ReversiBoard.BoardValue) -> None:
        self.side = side

    def move(self, board: ReversiBoard) -> tuple[bool, str]:
        pass


class HumanPlayer(Player):
    def __init__(self, side: ReversiBoard.BoardValue) -> None:
        super().__init__(side)

    def move(self, board: ReversiBoard) -> tuple[bool, str]:
        print("> Input cell (for example: e5 or E5) or 'exit':")
        cell = input()

        if cell == "exit":
            os._exit(0)

        if board.checkInputCell(cell):
            coords = board.getCoordsByCell(cell)
            i = coords[0]
            j = coords[1]

            isMoveMade = board.makeMove(i, j, self.side)

            if isMoveMade:
                statusMsg = ("White" if self.side == board.BoardValue.WHITE else "Black") + \
                    " made move to " + cell.upper()
                return (True, statusMsg)
            else:
                statusMsg = "Wrong move. Try again"
                return (False, statusMsg)
        else:
            statusMsg = "Wrong cell input"
            return (False, statusMsg)


class AiPlayer(Player):

    WIN_VALUE: int = 10000
    LOSE_VALUE: int = -10000

    def __init__(self, side: ReversiBoard.BoardValue) -> None:
        super().__init__(side)

    def calcHeuristic(
            self,
            board: ReversiBoard,
            movesCount: int,
            opponentMovesCount: int
    ) -> int:
        opponentSide = board.getOpponentSide(self.side)
        # подсчитаем количество очков на доске
        myCount = board.getSideCount(self.side)
        opponentCount = board.getSideCount(opponentSide)
        diff = (myCount - opponentCount)

        emptyCellsCount = board.BOARD_SIZE * board.BOARD_SIZE - myCount - opponentCount

        # если ходы закончились
        if ((emptyCellsCount == 0) or (
                movesCount == 0 and opponentMovesCount == 0)):
            if diff >= 0:
                return self.WIN_VALUE
            else:
                return self.LOSE_VALUE

        # иначе вернем вес хода
        weight = (movesCount - opponentMovesCount) * 3 + diff
        return weight

    # вес и координаты хода
    def findMove(
            self,
            n: int,
            board: ReversiBoard,
            turn: ReversiBoard.BoardValue
    ) -> tuple[int, tuple[int, int]]:
        opponentSide = board.getOpponentSide(self.side)

        levelDepth = 3

        # подсчитаем количество ходов каждой стороны
        myMoves = board.getAvailableMoves(self.side)
        myMovesCount = len(myMoves)
        opponentMoves = board.getAvailableMoves(opponentSide)
        opponentMovesCount = len(opponentMoves)

        if (n < levelDepth) and (myMovesCount != 0 or opponentMovesCount != 0):
            # увеличиваем глубину
            n += 1

            if (turn == self.side and myMovesCount == 0):
                turn = opponentSide
            elif (turn == opponentSide and opponentMovesCount == 0):
                turn = self.side

            weight = None
            weightCoords = None

            moves = myMoves
            if (turn == opponentSide):
                moves = opponentMoves

            for (i, j) in moves:
                copy_board = copy.deepcopy(board)
                copy_board.makeMove(i, j, turn)
                move = self.findMove(
                    n, copy_board, board.getOpponentSide(turn)
                )

                #if n == 1:
                    #print(n, board.getCellByCoords(i,j), move, turn, self.side, weight)

                moveWeight = move[0]

                if (weight is None) or (
                    weight is not None and turn == self.side and moveWeight > weight) or (
                        weight is not None and turn == opponentSide and moveWeight < weight):
                    weight = moveWeight
                    weightCoords = (i, j)

            return (weight, weightCoords)

        else:
            return (
                self.calcHeuristic(
                    board, myMovesCount, opponentMovesCount
                ), (0, 0))

    def move(self, board: ReversiBoard) -> tuple[bool, str]:

        move = self.findMove(0, board, self.side)
        (i, j) = move[1]

        #print(move)

        isMoveMade = board.makeMove(i, j, self.side)

        if isMoveMade:
            statusMsg = ("White" if self.side == board.BoardValue.WHITE else "Black") + \
                " made move to " + board.getCellByCoords(i, j)
            return (True, statusMsg)
        else:
            statusMsg = "AI error"
            return (False, statusMsg)


class ReversiGame:

    statusMsg: str = "Game was started"

    class PlayerTurn(Enum):
        PLAYER_A = 0,
        PLAYER_B = 1

    def __init__(self) -> None:
        self.gameBoard = ReversiBoard()

        sideForA = random.randint(1, 2)

        if (sideForA == 1):
            self.playerA = HumanPlayer(ReversiBoard.BoardValue.WHITE)
            self.playerB = AiPlayer(ReversiBoard.BoardValue.BLACK)
            self.playerTurn = self.PlayerTurn.PLAYER_B
        elif (sideForA == 2):
            self.playerA = HumanPlayer(ReversiBoard.BoardValue.BLACK)
            self.playerB = AiPlayer(ReversiBoard.BoardValue.WHITE)
            self.playerTurn = self.PlayerTurn.PLAYER_A

        self.PLAYER_MAP = {
            self.PlayerTurn.PLAYER_A: self.playerA,
            self.PlayerTurn.PLAYER_B: self.playerB
        }

    def changePlayerTurn(self):
        if (self.playerTurn == self.PlayerTurn.PLAYER_A):
            self.playerTurn = self.PlayerTurn.PLAYER_B
        elif (self.playerTurn == self.PlayerTurn.PLAYER_B):
            self.playerTurn = self.PlayerTurn.PLAYER_A

    def gameOver(self, whiteCount: int, blackCount: int) -> None:
        print("> Game over!")
        print(("White" if whiteCount > blackCount else "Black") + " wins!")
        os._exit(0)

    def start(self):
        while (True):
            os.system('cls||clear')

            self.gameBoard.printBoard()

            print("\n" + "> Status: " + self.statusMsg + ".")
            print("-----------------------------------------")
            whiteCount = self.gameBoard.getSideCount(
                ReversiBoard.BoardValue.WHITE)
            blackCount = self.gameBoard.getSideCount(
                ReversiBoard.BoardValue.BLACK)

            print("> White count:", whiteCount)
            print("> Black count:", blackCount)

            emptyCellsCount = self.gameBoard.BOARD_SIZE * \
                self.gameBoard.BOARD_SIZE - blackCount - whiteCount

            # если больше пустых клеток нет, то конец игры
            if emptyCellsCount == 0:
                self.gameOver(whiteCount, blackCount)

            print("> Empty count:", emptyCellsCount)

            sideForCurrentPlayer = self.PLAYER_MAP[self.playerTurn].side
            availableMoves = len(
                self.gameBoard.getAvailableMoves(sideForCurrentPlayer))
            if availableMoves == 0:
                print(
                    ">",
                    "PlayerA" if self.playerTurn == self.PlayerTurn.PLAYER_A else "PlayerB",
                    "have no moves. Change player turn.")
                self.changePlayerTurn()
                # посчитаем количество ходов для другого игрока
                sideForCurrentPlayer = self.PLAYER_MAP[self.playerTurn].side
                availableMoves = len(
                    self.gameBoard.getAvailableMoves(sideForCurrentPlayer))
                if (availableMoves == 0):
                    # если и у второго игрока нет ходов, то конец игры
                    self.gameOver(whiteCount, blackCount)
            else:
                print("> Available moves:", availableMoves)

            print("-----------------------------------------")
            print(
                "> Move for",
                ("PlayerA" if self.playerTurn == self.PlayerTurn.PLAYER_A else "PlayerB") +
                ":",
                ("White" if sideForCurrentPlayer == self.gameBoard.BoardValue.WHITE else "Black") +
                " side.")
            res, self.statusMsg = self.PLAYER_MAP[self.playerTurn].move(
                self.gameBoard
            )
            if res:
                self.changePlayerTurn()


game = ReversiGame()
game.start()
