"""Build Python Tutor and Compiler Explorer links for the snippet programs.

usage:
  python3 make_links.py <file.c> [...]       print both links for each file
  python3 make_links.py --update <page.html> rewrite the buttons in every code panel
                                             marked data-snippet="<name>" (uses <name>.c
                                             from this folder); panels that also have
                                             data-no-flags get a third button that
                                             compiles without the 42 flags

A line `// args: a b c` in a .c file sets the command-line arguments for the
Compiler Explorer run.
"""
import base64
import html
import json
import os
import re
import sys
from urllib.parse import quote

CFLAGS = "-Wall -Wextra -Werror"
GODBOLT_COMPILER = "cg162"  # x86-64 gcc 16.2 on godbolt.org
HERE = os.path.dirname(os.path.abspath(__file__))


def pythontutor(code):
    return ("https://pythontutor.com/visualize.html#code=" + quote(code, safe="")
            + "&py=c_gcc9.3.0&mode=display&curInstr=0")


def godbolt(code, flags=CFLAGS):
    args = re.search(r"^// args: (.*)$", code, re.M)
    state = {"sessions": [{
        "id": 1,
        "language": "c",
        "source": code,
        "compilers": [{"id": GODBOLT_COMPILER, "options": flags}],
        "executors": [{"compiler": {"id": GODBOLT_COMPILER, "libs": [], "options": flags},
                       "arguments": args.group(1) if args else "", "stdin": ""}],
    }]}
    b64 = base64.b64encode(json.dumps(state).encode("ascii")).decode("ascii")
    return "https://godbolt.org/clientstate/" + quote(b64, safe="")


def buttons(name, no_flags=False):
    code = open(os.path.join(HERE, name + ".c"), encoding="utf-8").read()
    extra = (f'<a href="{html.escape(godbolt(code, ""))}" target="_blank" rel="noopener">⚙ Run without flags</a>'
             if no_flags else "")
    return ('<span class="run-links">'
            f'<a href="{html.escape(pythontutor(code))}" target="_blank" rel="noopener">▶ Step through</a>'
            f'<a href="{html.escape(godbolt(code))}" target="_blank" rel="noopener">⚙ Compile &amp; run</a>'
            + extra + '</span>')


def update(page):
    text = open(page, encoding="utf-8").read()
    opening = re.compile(r'(<(?:pre|div)\b[^>]*\bdata-snippet="([\w-]+)"[^>]*>)(<span class="run-links">.*?</span>)?', re.S)
    names = []

    def repl(m):
        names.append(m.group(2))
        return m.group(1) + buttons(m.group(2), "data-no-flags" in m.group(1))

    text = opening.sub(repl, text)
    open(page, "w", encoding="utf-8").write(text)
    print(f"updated {len(names)} panels: " + ", ".join(names))


if sys.argv[1:2] == ["--update"]:
    update(sys.argv[2])
else:
    for path in sys.argv[1:]:
        code = open(path, encoding="utf-8").read()
        print(path)
        print("  pythontutor:", pythontutor(code))
        print("  godbolt:    ", godbolt(code))
