# GDB Debugging Investigation: The Infinite Loop Mystery

## Step 1: Discover the Problem and Prepare for Debugging

**Problem:** Let's run the program and see what happens.

```bash
gcc demo.c -o demo
./demo
```

**Observation:** The program prints array values but never stops - it's an infinite loop! Press `Ctrl+C` to stop it.

**Prepare for debugging:** To use GDB effectively, we need debugging symbols (variable names, line numbers, etc.) compiled into our program.

```bash
gcc -g demo.c -o demo
```

**Observation:** The program size is slightly larger now because it includes debugging information. Performance is essentially the same - the `-g` flag doesn't affect optimization or runtime speed.


## Step 2: Launch GDB with Visual Interface and Control Execution

**Let's use GDB to investigate:** Start GDB with TUI (Text User Interface) for a visual view of the source code.

```bash
gdb -tui ./demo
```

**Inside GDB, set a breakpoint and run:**

```gdb
(gdb) break main
(gdb) run
```

**Explain:**
- TUI mode: Shows source code in top panel, commands in bottom. Toggle with `Ctrl+X` then `A`
- `Ctrl+L`: Refresh screen if display gets messy
- `break main`: Sets a breakpoint to pause at the start of main function

**Observation:** The program stops at the first line of main() before any code executes. In TUI mode, an arrow or highlight shows the current line, giving us full control to examine variables and step through code.


## Step 3: Step Through and Examine Variables

**Investigation:** Let's execute the code line by line and check what's happening to our variables.

```gdb
(gdb) next
(gdb) print i
(gdb) next
(gdb) print i
(gdb) next
(gdb) print i
```

**Explain:**
- `next` (or `n`): Executes one line at a time
- `print` (or `p`): Shows current value of a variable
- In TUI mode, watch the arrow move line by line

**Observation:** First `next` declares variables (uninitialized values). After `i = 0` executes, `print i` shows 0. Loop iterations show `i` incrementing (0, 1, 2...). This is manual step-by-step tracking - foundational but tedious.


## Step 4: Use Watch for Automatic Monitoring

**Problem:** Typing `print i` after every step is tedious. Let's use `watch` to automatically show us when `i` changes.

```gdb
(gdb) watch i
(gdb) continue
```

**Explain:**
- `watch`: Monitors a variable and stops execution whenever its value changes, showing old and new values
- `continue` (or `c`): Runs program normally until next breakpoint, watchpoint, or program end
- Tip: Press Enter to repeat the last command

**Observation:** GDB automatically stops each time `i` is modified and displays "Old value = X, New value = Y". We see `i` incrementing: 0→1, 1→2, 2→3... Keep pressing Enter to watch the pattern.


## Step 5: Examine Memory Layout

**Investigation:** Let's look at where our variables are stored in memory and what values are there.

```gdb
(gdb) print &i
(gdb) print &a[0]
(gdb) print &a[10]
(gdb) x/12uw &a[0]
```

**Explain:**
- `&`: Shows the memory address where a variable is stored (in hexadecimal)
- `x/12uw`: Examine memory command. Format: `x/[count][format][size] address`
  - `12` = examine 12 units (12 complete `unsigned int` values)
  - `u` = display **values** as unsigned decimal
  - `w` = word size (4 bytes, same as `unsigned int`)
  - Addresses shown in hex, values in decimal. GDB displays 4 values per line for readability.

**Example output and analysis:**
```
(gdb) x/12uw &a[0]
0x7fffffffdec0: 0    0    0    0    ← a[0], a[1], a[2], a[3]
0x7fffffffdec0: 0    0    0    0    ← a[4], a[5], a[6], a[7]
0x7fffffffded0: 0    0    0    11   ← a[8], a[9], a[10], ??? (12th value)
```

**What we're seeing:** We requested 12 `unsigned int` values starting from `a[0]`. Our array only has 11 elements (a[0] through a[10]), so the 12th value is whatever's stored in memory right after the array. Here it shows 11 - that's likely `i`! Each `unsigned int` takes 4 bytes, so memory addresses increment by 4 for each element.

**Observation:** The memory location right after our array contains the value of `i`. This means accessing `a[11]` would write directly into `i`'s memory location!


## Step 6: Set Up Permanent Display

**Investigation:** Let's restart fresh and set up permanent monitoring of key variables.

```gdb
(gdb) delete
(gdb) break main
(gdb) run
(gdb) display i
(gdb) display &i
(gdb) display &a[11]
```

**Explain:**
- `delete`: Removes all breakpoints and watchpoints to start clean
- `display`: Automatically shows values every time GDB stops - no need to keep typing `print`

**Observation:** Now every time GDB stops, we'll automatically see the values of `i`, its address, and the address of `a[11]`.


## Step 7: Jump to the Bug and Witness It

**Investigation:** Instead of stepping through all iterations, let's jump straight to when `i` becomes 11.

```gdb
(gdb) delete breakpoints
(gdb) break 26 if i == 11
(gdb) continue
(gdb) next
```

**Explain:**
- `break 26 if i == 11`: Conditional breakpoint - only stops when the condition is true

**Observation:** The program runs until `i` reaches 11. Notice `&i` and `&a[11]` show the same address! After `next`, watch the display - `i` changed from 11 to 0! We overwrote our loop counter, causing the infinite loop.


## Step 8: The Solution

**Understanding the bug:** Array `a[11]` has valid indices 0-10. When we access `a[11]`, we write beyond the array boundary into where `i` is stored, resetting it to 0.

**The fix:** Change the loop condition from `i < 12` to `i < 11` to match the array size.

**Key lesson:** GDB helps visualize what's happening in memory - making debugging faster and more intuitive than printf debugging alone.


## Step 9: GDB Commands Reference

### Starting & Control
| Command | Description |
|---------|-------------|
| `gdb -tui ./program` | Start GDB with visual interface |
| `break main` (or `b main`) | Set breakpoint at function |
| `break 26` (or `b 26`) | Set breakpoint at line number |
| `break 26 if i == 11` | Conditional breakpoint |
| `set var i = 10` | Set variable value |
| `run` (or `r`) | Start program execution |
| `continue` (or `c`) | Continue until next stop point |
| `next` (or `n`) | Execute next line (step over) |
| `quit` (or `q`) | Exit GDB |
---

### Examining Variables & Memory
| Command | Description |
|---------|-------------|
| `print variable` (or `p`) | Show variable value |
| `print &variable` | Show variable address |
| `display variable` | Auto-show value at every stop |
| `watch variable` | Stop when variable changes |
| `x/12uw address` | Examine memory: count/format/size |
---

### Managing Breakpoints
| Command | Description |
|---------|-------------|
| `delete` (or `d`) | Remove all breakpoints/watchpoints |
| `delete breakpoints` | Remove all breakpoints only |
---

### Interface Controls
| Command | Description |
|---------|-------------|
| `Ctrl+X` then `A` | Toggle TUI mode |
| `Ctrl+L` | Refresh screen |
| `Enter` | Repeat last command |
---

### Display and Examine (`x/`) Flags
- `display /<count><format><size> expression`
- `x/<count><format><size> expression`

#### Format
| Flag | Description |
|------|-------------|
| `x` | Hexadecimal |
| `d` | Signed Decimal |
| `u` | Unsigned Decimal |
| `o` | Octal |
| `t` | Binary (t for 'two') |
| `f` | Floating Point |
| `a` | Address (hex) |
| `c` | Character |
| `s` | Null-terminated String |
| `i` | Machine Instruction |

#### Size
| Flag | Description |
|------|-------------|
| `b` | byte (1 byte) |
| `h` | halfword (2 bytes) |
| `w` | word (4 bytes) - Default |
| `g` | giant word (8 bytes) |
---

### TUI Keybindings
| Keybinding |Action |
|------------|-------|
| `Ctrl + x` then `a` | Toggle TUI mode on/off. |
| `Ctrl + l` | Refresh the screen if it gets garbled. |
| `Ctrl + x`  then `2` | Cycle through all available layouts (src, asm, split, regs).
| `Ctrl + p` | Previous Command	|
| `Ctrl + n` | Next Command	|
| `Ctrl + x` then `o` | Switch Window	|

### Useful Links
[GNU debugger](www.sourceware.org/gdb/)
[Beej's Quick Guide to GDB](beej.us/guide/bggdb/)
