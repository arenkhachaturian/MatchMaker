from launcher import initialize_players
import random

def play_game(player1, player2):
    print("Welcome to Russian Roulette!")
    print("One bullet in the chamber. Let's take turns shooting...\n")
    players = [player1, player2]
    chamber = [False, False, False, False, False, True]  # One bullet
    random.shuffle(chamber)

    for turn in range(len(chamber)):
        current_player = players[turn % 2]
        prompt = f"{current_player}, enter [shoot] for your turn(or 'q' to exit) "

        if isinstance(current_player, str):  # Human player
            action = input(prompt).strip()
        else:  # Bot player
            action = current_player.input(prompt)

        if action == "shoot":
            if chamber.pop(0):  # Bullet fired
                print(f"BOOM! {current_player} is dead!")
                print(f"WINNER: {players[(turn + 1) % 2]}")
                return
            else:
                print("Click! The chamber is empty...\n")
        elif action == "q":
            print(f"{current_player} quit the game. No winner!")
            return
        else:
            print("Invalid option. Turn skipped.\n")

    # If no one loses (edge case), it's a draw
    print("Unbelievable! The chamber was empty all along...")
    print(f"WINNER: {players[0]}, {players[1]}")

if __name__ == "__main__":
    print("hello")
    player1, player2 = initialize_players()
    play_game(player1, player2)
