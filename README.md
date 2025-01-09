asfmt
===

This utility formats x86 GNU assembler code to user specifications or a default style. All hexproof.sh code is formatted with this utility.

STYLE

asfmt recognizes, directives, labels, local labels, comments and instructions. It attempts to format code uniformially throughout the document. The default style is usually sufficient for most large projects. It does **NOT** use tabs, everything is spaces since different editors handle tabs differently.

It will set most directives in column 0:

```
.set STDOUT, 1
```

If its a section directive it will be set to column 5 where instructions are setup. This allows
for labels to be easily seen and sections to be scanned.

```
     .globl _start
     .section .text

_start:
     mov   $1, %rax
```

Labels to column 0 as well as local labels to column 0.

```
my_label:
     xor   %rcx, %rcx
.L_loop:
     mov   $1, %rcx
```

If we are inside a label and have comments over an instruction then it lines up the comments with the instructions.

```
my_label:
     # This is a comment after a label
     mov   $1, %rax
```

If its a comment before a label it lines it up with the label in column 0

```
# This is a comment before a label
my_label:
     mov ....
```
KNOWN BUGS

- Multi line comments

TODO

- Not spacing after comma in mov instructions
- use .asformat file for settings