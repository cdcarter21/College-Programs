
from random import choice

again = "y"
while again != "n":
    user_choice = input("Enter a choice (rock, paper, scissors): ")
    possible_choices = ["rock", "paper", "scissors"]
    computer_choice = choice(possible_choices)
    print(f"\nYou chose {user_choice}, computer chose {computer_choice}.\n")

    if user_choice == computer_choice:
        print(f"Both players selected {user_choice}. It's a tie!")
        
    elif user_choice == "rock":
        if computer_choice == "paper":
            print("Paper covers rock! You lose.")
        else:
            print("Rock smashes scissors! You win!")
            
    elif user_choice == "paper":
        if computer_choice == "rock":
            print("Paper covers rock! You win!")
        else:
            print("Scissors cuts paper! You lose.")

    elif user_choice == "scissors":
        if computer_choice == "rock":
            print("Rock smashes scissors! You lose.")
        else:
            print("Scissors cuts paper! You win!")

    print()
    again = input("Play again? (y/n): ")
    print()
