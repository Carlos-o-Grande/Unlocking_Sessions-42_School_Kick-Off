# Run-in-browser links for the slide snippets

Each `.c` file here is the complete, runnable version of a slide snippet. The file name starts
with the slide number. In the page, each code panel names its file with `data-snippet="<name>"`,
and its two buttons (▶ Step through / ⚙ Compile & run) open that file with the code already loaded.

After editing a `.c` file, check it with the 42 flags, then rewrite every panel's buttons
(run from the `Syntax` folder):

```
cc -Wall -Wextra -Werror snippets/s16_shadowing.c && ./a.out
python3 snippets/make_links.py --update Unlocking_session_Syntax.html
```

To add a snippet: write `snippets/<name>.c`, add `data-snippet="<name>"` to the slide's
`<pre>` (or code panel `<div>`), and run the update. To print a file's links without touching
the page: `python3 snippets/make_links.py snippets/<name>.c`.

A line `// args: a b c` in a `.c` file sets the command-line arguments for the Compiler Explorer run
(Python Tutor has no arguments).

A panel with `data-compare="<compiler id>"` (e.g. `cclang2210` = x86-64 clang 22.1.0) makes the Compile & run
link open a second run pane with that compiler, next to gcc - used on S13 to show gcc and clang
evaluating function arguments in a different order. Note: the run pane is tied to its compiler;
changing the compiler in the assembly pane does not change what the run pane uses.

Two programs fail to compile with the 42 flags on purpose, because that is what their slide teaches:
`s11_assign_vs_compare.c` (`if (x = 5)`, `-Wparentheses`) and `s17_uninitialized.c`
(reading an uninitialised variable, `-Wuninitialized`). Their Compile & run button shows the
compiler stopping them. Their panels also carry `data-no-flags`, which adds a third button,
⚙ Run without flags: the same Compiler Explorer setup with no flags, so the program compiles and runs. Python Tutor compiles without `-Werror`: it steps through
`s11_assign_vs_compare.c` normally, and stops `s17_uninitialized.c` at the `printf` with
"Conditional jump or move depends on uninitialised value(s)".
`s10_null_check.c` crashes on purpose at its last `if`: Compile & run shows `SIGSEGV`,
Python Tutor stops there with "Invalid read of size 4".

The code lives inside the link itself, so nothing is uploaded until someone clicks it.

## Python Tutor - step-by-step visualiser

No official API docs. Parameters below were read from the site's frontend bundle
(`https://pythontutor.com/build/visualize.bundle.js`) on 2026-10-16.

URL form:

```
https://pythontutor.com/visualize.html#code=<url-encoded source>&py=c_gcc9.3.0&mode=display&curInstr=0
```

| param | meaning |
|---|---|
| `code` | source, percent-encoded (`encodeURIComponent`) |
| `py` | language: `c_gcc9.3.0` for C, `cpp_g++9.3.0` for C++ (the only C/C++ values in the bundle) |
| `mode` | `display` (or `visualize`) opens the stepper; `edit` opens the editor |
| `curInstr` | step to start on, 0 = first |

Others it reads but we don't need: `cumulative`, `heapPrimitives`, `textReferences`, `rawInputLstJSON`
(stdin lines as a JSON list), `verticalStack`.

## Compiler Explorer (godbolt.org) - compile, assembly, run

Source: https://github.com/compiler-explorer/compiler-explorer/blob/main/docs/API.md
(BSD-2-Clause, © Compiler Explorer authors), excerpt retrieved 2026-10-16:

> ### `GET /clientstate/<base64>` - Opens the website in a given state
>
> This call is to open the website with a given state (without having to store the state first with /api/shortener). The
> state is the same object described under `POST /api/shortener` above; here it is encoded with base64 and attached
> directly onto the URL instead of being sent in a POST body. It is possible to compress the JSON string with the zlib
> deflate method (compression used by gzip; available for many programming languages like
> [javascript](https://nodejs.org/api/zlib.html)). It is automatically detected.
>
> To avoid problems in reading base64 by the API, some characters must be kept in unicode. Therefore, before calling the
> API, it is necessary to replace these characters with their respective unicodes. A suggestion is to use the Regex
> expression `/[\u007F-￿]/g` that allows mapping these characters.

> An example of one the easiest forms of a clientstate:
>
> ```JSON
> {
>   "sessions": [
>     {
>       "id": 1,
>       "language": "c++",
>       "source": "int main() { return 42; }",
>       "compilers": [
>         {
>           "id": "g82",
>           "options": "-O3"
>         }
>       ],
>       "executors": [
>         {
>           "arguments": "arg1",
>           "compiler": {
>               "id": "g92",
>               "libs": [],
>               "options": "-O3"
>           },
>           "stdin": ""
>         }
>       ]
>     }
>   ]
> }
> ```

> ### `POST /api/shortener` - saves given state _forever_ to a shortlink and returns the unique id for the link
>
> Returns `{"url": "https://godbolt.org/z/Km_340"}`

`make_links.py` uses `/clientstate/` (no upload). `json.dumps` escapes non-ASCII characters as `\uXXXX`,
which covers the "keep in unicode" note above. `"executors"` adds the panel that runs the program and shows its output.

Compiler id: `cg162` = x86-64 gcc 16.2 (set in `GODBOLT_COMPILER`). To list current C compilers:

```
curl -s -H "Accept: application/json" "https://godbolt.org/api/compilers/c?fields=id,name"
```

## First visit

Both sites show a one-time consent / privacy dialog on the first visit in a browser; the code is already loaded behind it.
