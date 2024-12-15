import argparse
from bot import Bot

def initialize_players():
    print("intializing players...")
    parser = argparse.ArgumentParser(description="Game Launcher")
    parser.add_argument("--player1", required=True, help="Name of Player 1")
    parser.add_argument("--player1Type", choices=["human", "bot"], default="bot", help="Type of Player 1 (human or bot, default is bot)")
    parser.add_argument("--player2", required=True, help="Name of Player 2")
    parser.add_argument("--player2Type", choices=["human", "bot"], default="bot", help="Type of Player 2 (human or bot, default is bot)")

    args = parser.parse_args()

    # Determine player types
    player1 = Bot(args.player1) if args.player1Type == "bot" else args.player1
    player2 = Bot(args.player2) if args.player2Type == "bot" else args.player2

    return player1, player2
