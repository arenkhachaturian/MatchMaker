import random
import time

class Bot:
    def __init__(self, name):
        self.name = name

    def choose_action(self, options):
        """Simulate a bot selecting an option, excluding 'quit'."""
        non_quit_options = [opt for opt in options if opt != "quit"]
        time.sleep(random.uniform(0.5, 1.0))  # Simulate delay
        return random.choice(non_quit_options)

    def __str__(self):
        return self.name

    def input(self, prompt):
        """Read the last printed message and select an action."""
        print(prompt)
        options = self._extract_options(prompt)
        return self.choose_action(options)

    def _extract_options(self, prompt):
        """Extract options from a message of the format 'Press [option1, option2, ...] for your turn'."""
        if "[" in prompt and "]" in prompt:
            start = prompt.index("[") + 1
            end = prompt.index("]")
            return [opt.strip() for opt in prompt[start:end].split(",")]
        return []
