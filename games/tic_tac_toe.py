from launcher import initialize_players

def play_game(player1, player2):
    print("Welcome to Tic Tac Toe!")
    print("Take turns to mark X or O on the board. The first to get three in a row wins!\n")

    board = [" " for _ in range(9)]
    players = [(player1, "X"), (player2, "O")]

    def print_board():
        for i in range(0, 9, 3):
            print(" | ".join(board[i:i + 3]))
            if i < 6:
                print("--+---+--")
        print()

    def check_winner():
        win_conditions = [
            (0, 1, 2), (3, 4, 5), (6, 7, 8),  # Rows
            (0, 3, 6), (1, 4, 7), (2, 5, 8),  # Columns
            (0, 4, 8), (2, 4, 6)              # Diagonals
        ]
        for x, y, z in win_conditions:
            if board[x] == board[y] == board[z] and board[x] != " ":
                return True
        return False

    board_fields = [0, 1, 2, 3, 4, 5, 7, 8]
    for turn in range(9):
        current_player, symbol = players[turn % 2]
        print_board()
        # this explicityis for bot
        prompt = f"{current_player}, enter " + str(board_fields) +  " for your turn('q' to exit) "

        if isinstance(current_player, str):  # Human player
            action = input(prompt).strip()
        else:  # Bot player
            action = current_player.input(prompt)

        if action == "q":
            print(f"{current_player} quit the game. No winner!")
            return

        if action.isdigit() and 0 <= int(action) <= 8:
            move = int(action)
            board_fields.remove(move)
            if board[move] == " ":
                board[move] = symbol
                if check_winner():
                    print_board()
                    print(f"WINNER: {current_player}")
                    return
            else:
                print("Invalid move! Cell already taken.\n")
        else:
            print("Invalid option.\n")

    # If no one wins after 9 turns, it's a draw
    print_board()
    print(f"WINNER: {players[0][0]}, {players[1][0]}")  # Draw case

if __name__ == "__main__":
    player1, player2 = initialize_players()
    play_game(player1, player2)
