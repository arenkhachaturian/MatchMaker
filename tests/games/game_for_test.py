import argparse

print ("eeeh")

def main():
    print("eeeeh")
    parser = argparse.ArgumentParser(description="Mock Game Simulator")
    parser.add_argument("--player1", type=str, help="Name of Player 1")
    parser.add_argument("--player2", type=str, help="Name of Player 2")
    parser.add_argument("--winner", type=str, help="Name of the winner (optional)")

    args = parser.parse_args()

    if args.winner:
        print(f"WINNER: {args.winner}")
    else:
        print(f"WINNER: {args.player1}, {args.player2}")

if __name__ == "__main__":
    main()
