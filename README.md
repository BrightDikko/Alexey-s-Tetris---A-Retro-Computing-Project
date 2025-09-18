# Alexey’s Tetris  -  A Retro Computing Project

---

## Historical Context & Importance

This project sets out to recreate a formative artifact from the 1980s/1990s home-computing era. After browsing classic titles on RetroGames (retrogames.cz), **Tetris** immediately stood out. The game remains universally recognizable, yet its origin story also channels the hacker ethos Steven Levy describes in *Hackers: Heroes of the Computer Revolution*.

Tetris was created in 1984 by **Alexey Pajitnov** at the Dorodnitsyn Computing Centre of the Soviet Academy of Sciences in Moscow. Working on an **Elektronika 60** - a machine without bitmap graphics - Pajitnov prototyped falling shapes using **text characters** to approximate the game board and tetrominoes. Computers in the Soviet Union were scarce and expensive; the Elektronika 60 was intended for research, not play. In the spirit of Levy’s “True Hackers,” Pajitnov explored the machine’s possibilities after-hours, guided by curiosity and the intrinsic joy of making. The result was a deceptively simple puzzle loop that spread rapidly from office to office, then beyond Moscow, and eventually around the world.

Tetris influenced the trajectory of computing and games in several enduring ways. First, it demonstrated how **expressive gameplay can emerge from strict technical constraints** - in this case, a text-only display. Second, it showcased a powerful **human-computer interaction pattern**: players enter a flow state balancing spatial reasoning, timing, and risk. Third, as Tetris crossed borders and platforms - 8-bit microcomputers, consoles, handhelds, PCs - it became a **portability benchmark**, motivating programmers to re-implement core logic cleanly and adapt rendering layers to wildly different environments.

Our artifact pays homage to this lineage. We implement the game in **C++**, a language historically relevant to commercial games of the 1990s and 2000s, and render it with **raylib**, a lightweight modern library that still feels close to the metal. We retain the minimal, grid-first look and tighten the core systems - gravity, rotation, collision, line clears, levels, and scoring - so the experience centers on play rather than spectacle.

---

## Build & Run

### Prerequisites
- A C++ compiler (Clang or GCC)
- [raylib](https://www.raylib.com/) development libraries

### macOS (Apple Silicon or Intel)
```bash
# Install raylib (Homebrew)
brew install raylib

# Build
make

# Run
./tetris
```

### Linux (Debian/Ubuntu or similar)
Install build tools and raylib (package name may vary; if unavailable, build raylib from source):
```bash
sudo apt update
sudo apt install build-essential libraylib-dev
```
Edit `Makefile` for Linux by replacing the macOS frameworks in `LDLIBS` with:
```
LDLIBS = -lraylib -lm -lpthread -ldl -lrt -lX11
```
Then:
```bash
make
./tetris
```

---

## Controls

- **Left / Right Arrow**  -  Move piece horizontally
- **Up Arrow**  -  Rotate piece (clockwise)
- **Down Arrow**  -  Soft drop (**+1 point per row**)
- **Space**  -  Hard drop (**+2 points per row**)
- **Any key** (after game over)  -  Restart

---

## Scoring & Levels (current implementation)

- **Line clears (per piece placement):**
    - 1 line: **100 × level**
    - 2 lines: **300 × level**
    - 3 lines: **500 × level**
    - 4 lines (“Tetris”): **800 × level**
- **Soft drop:** +1 per row the player manually drops.
- **Hard drop:** +2 per row.
- **Leveling:** `level = 1 + (totalLines / 2)` → level increases every **2** cleared lines.
- **Gravity speed:** Interval = `0.40 * 0.90^(level - 1)`, floored at **0.05s** per step.

---

## Project Structure

```
- Makefile
- main.cpp              # Entry point; window loop and timing
- game.h / game.cpp     # Game state, input handling, gravity, panels, scoring
- grid.h / grid.cpp     # Playfield grid, rendering, row clearing
- tetrominoes.h / .cpp  # Tetromino data/rotation, rendering helpers
- README.md
```

---

## Usage Tips

- If the game feels too fast/slow initially, tune the constants inside `Game::GetFallIntervalSeconds()`:
  ```cpp
  const double base = 0.40;
  const double factor = 0.90;
  const double minInterval = 0.05;
  ```
- The stats and control panels can be resized by changing `sidebarWidth` in `Game`’s constructor.

---

## Acknowledgments

- Inspired by Alexey Pajitnov’s original 1984 Tetris and the histories recounted in Steven Levy’s *Hackers: Heroes of the Computer Revolution*.
- Referenced this Youtube Tutorial - https://www.youtube.com/watch?v=wVYKG_ch4yM&t=6910s
- Built with **raylib**
