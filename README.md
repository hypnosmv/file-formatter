# File Formatter

Simple binary which provides rule based file formatting.\
Current implementation supports basic code formatting rules.

## Usage

```
chmod u+x run.sh
./run.sh prep
./run.sh release
./build/bin/release <target-path> <config-path> <destination-directory>
```

## Predefined rules

### Find rules

| Name | Note |
| ---- | ---- |
| FIND_DUPLICATED_SEMICOLON | |
| FIND_TRAILING_BRACE | |
| FIND_SQUEEZED_PARENTHESIS | if, else if, while, for, switch |
| FIND_LOOSE_PARENTHESIS | anywhere other than FIND_SQUEEZED_PARENTHESIS |
| FIND_LAST_LINE | |
| FIND_TRAILING_SPACE | one or more spaces at the end of the line |

### Format rules
| Name | Note |
| ---- | ---- |
| FORMAT_DUPLICATED_SEMICOLON | |
| FORMAT_TRAILING_BRACE | preserves indentation |
| FORMAT_SQUEEZED_PARENTHESIS | |
| FORMAT_LOOSE_PARENTHESIS | |
| FORMAT_LAST_LINE | maintains newline character consistency |
| FORMAT_TRAILING_SPACE | |

### Guard rules

Executed between the `find` and `format` instruction pair to exclude sections from formatting.

| Name | Note |
| ---- | ---- |
| FIND_SINGLE_LINE_COMMENT | |
| FIND_MULTI_LINE_COMMENT | comment does not have to contain newline |
| FIND_STRING_SCOPE | |
| FIND_CHAR_SCOPE | validates escape sequences |

## Config

### Execution order

```
{
    A.B

    {
        {
            C
            D.E
        }

        F
        G.H

        I
        J.K
    }

    L.M
    N.O
}
```

| Instruction | Type | Guard stack |
| ----------- | ---- | ----------- |
| A | find | |
| B | format | |
| D | find | C |
| C | guard | C |
| E | format | C |
| G | find | F |
| F | guard | F |
| H | format | F |
| J | find | F, I |
| F | guard | F, I |
| I | guard | F, I |
| K | format | F, I |
| L | find | |
| M | format | |
| N | find | |
| O | format | |

## Exit codes

Defined in `src/misc/include/ExitCode.hpp`.

| Code | Meaning |
| ---- | ------- |
| 0 | Success |
| 1 | Invalid number of arguments |
| 2 | Failed to read file |
| 3 | Failed to write file |
| 4 | Invalid config file |
| 5 | Invalid find rule name |
| 6 | Invalid format rule name |

> **Note:** Guard rules are effectively treated as find rules.
