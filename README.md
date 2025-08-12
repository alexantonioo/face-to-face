# Face to Face

## Description

"Face to Face" is a 2D one-on-one boxing game experience that invites two players to engage in epic hand-to-hand combat. Developed in C++, this game will offer an intense and exciting local gaming experience. Each player takes control of a boxer, each with their own statistics and abilities. Health, strength, speed, and stamina will be key factors in determining the outcome of each match. Players will be able to execute punches and combos, along with a strategic defense system that will allow them to block their opponent's attacks. "Face to Face" will stand out for its retro visual style, evoking the nostalgia of classic arcade games.

## Technologies Used

- C++ (version 17)
- SFML (Simple and Fast Multimedia Library) for graphics and event handling
- Behavior Trees

## Project Structure

The project has the following directory structure:

- FaceToFace
  - .vscode/
  - bin/
    - .gitkeep
  - lib/
    - include/
      - Archievement.hpp
      - Boxer.hpp
      - Combo.hpp
      - Game.hpp
      - Match.hpp
      - Ring.hpp
      - Timer.hpp
    - obj/
      - .gitkeep
    - src/
      - Archievement.cpp
      - Boxer.cpp
      - Combo.cpp
      - Game.cpp
      - Match.cpp
      - Ring.cpp
      - Timer.cpp
  - test/
    - bin/
      - GameTest
    - src/
      - GameTest.cpp
  - .gitignore
  - CHANGELOG
  - Makefile
  - README.md


## Compilation and Execution

### Prerequisites
- **C++17**: Ensure you have a compiler compatible with C++17 installed.
- **SFML**: Install the SFML library for graphics and event handling.

#### Installing SFML (Ubuntu)

1. Run in the console 
    ```bash
    sudo apt-get install libsfml-dev
    ```

## Steps to Run the Game

1. Locate the path of the `face-to-face` folder.
2. Compile using the command `make`:
   ```bash
   make

3. Open the executable by navigating through the folders test, then bin, and execute the GameTest file with:
    ```bash
    ./GameTest
    ```

## Single Player (Bot) Mode

From the main menu you can toggle the option "Jugar con Bot" (Play with Bot). When enabled:
- Player 1 uses WASD to move, R/Y to punch, K to block, P/L to dodge (existing controls).
- Player 2 becomes an AI-controlled boxer.

### Current AI Behavior
The bot uses a lightweight Behavior Tree composed of:
1. Selector (root)
   - Sequence (Punch Sequence)
     - Condition: Has minimum stamina (>= 10)
     - Condition: Within punch range (<= 120 px)
     - Action: Perform right jab
   - Action: Approach (move towards opponent until in range)

Distance is recomputed every frame; if outside range the bot advances, otherwise attempts a jab when stamina allows. This is intentionally simple and can be extended (add dodge, block, left jab, combos, retreat on low stamina) in future iterations.

### Notes
- Bot logic is frame-time aware and updates movement before evaluating attack.
- Stamina constraints prevent constant spam of attacks.
- Behavior Tree nodes are defined in `BehaviorTree.hpp` (added ConditionNode).