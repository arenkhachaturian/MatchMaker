from launcher import initialize_players
from bot import Bot
import random

def play_game(player1, player2):
    print("Welcome to the Dice Game!")
    print("Each player must roll the dice. The player with the highest roll wins. In case of a tie, both win.\n")

    players = [player1, player2]
    rolls = {}

    for player in players:
        prompt = f"{player}, enter [roll] for your turn(or 'q' to exit) "
        action = player.input(prompt) if isinstance(player, Bot) else input(prompt).strip()

        if action == "roll":
            roll = random.randint(1, 6)
            rolls[player] = roll
            print(f"{player} rolled a {roll}\n")
        elif action == "q":
            print(f"{player} quit the game. No winner!")
            return
        else:
            print("Invalid option. Turn skipped.\n")

    # Determine the winner
    roll_values = list(rolls.values())
    if roll_values[0] > roll_values[1]:
        winner = players[0]
        print(f"WINNER: {winner}")
    elif roll_values[0] < roll_values[1]:
        winner = players[1]
        print(f"WINNER: {winner}")
    else:
        print(f"WINNER: {players[0]}, {players[1]}")  # Tie case

if __name__ == "__main__":
    player1, player2 = initialize_players()
    play_game(player1, player2)
