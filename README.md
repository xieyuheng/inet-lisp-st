# inet-lisp

An implementation of [interaction nets](https://en.wikipedia.org/wiki/Interaction_nets)
as a [lisp-like language](https://en.wikipedia.org/wiki/lisp_(programming_language)).

- Untyped.
- Using a meta language to build nets.
- Programming with interaction nets directly (no compilation via combinators).

## Syntax

```xml
(define-node <name> <ports>)
(define-rule <pattern> <function-body>)
(define <name> <function-body>)
```

## Examples

### Natural Number

```
(define-node nzero value!)
(define-node nadd1 prev value!)
(define-node nadd target! addend result)
```

The rule between `(nadd1)` and `(nadd)` as ASCII art:

```
     value             value            value
       |                 |                |
    (nadd)     =>                =>    (nadd1)
     /   \                 \              |
(nadd1)   addend           addend       (nadd)
   |                 |                  /   \
 prev              prev              prev   addend
```

Define the rule between `(nadd1)` and `(nadd)`:

```
(define-rule (nadd (nadd1 prev) addend result)
  (nadd1 (nadd prev addend) result))
```

The rule between `(nzero)` and `(nadd)` as ASCII art:

```
     value          value         value
       |              |             |
     (nadd)     =>             =>   |
     /   \              \            \
(nzero)   addend        addend       addend
```

Define the rule between `(nzero)` and `(nadd)`:

```
(define-rule (nadd (nzero) addend result)
  (connect addend result))
```

Example interaction:

```
       |                   |                   |              |
    (nadd)              (nadd1)             (nadd1)        (nadd1)
     /   \                 |                   |              |
(nadd1)  (nadd1)        (nadd)              (nadd1)        (nadd1)
   |        |    =>      /   \       =>        |        =>    |
(nadd1)  (nadd1)    (nadd1)  (nadd1)         (nadd)        (nadd1)
   |        |          |        |            /   \            |
(nzero)  (nzero)    (nzero)  (nadd1)    (nzero) (nadd1)    (nadd1)
                                |                  |          |
                             (nzero)            (nadd1)    (nzero)
                                                   |
                                                (nzero)
```

The whole program with test:

```
(define-node nzero value!)
(define-node nadd1 prev value!)
(define-node nadd target! addend result)

(define-rule (nadd (nadd1 prev) addend result)
  (nadd1 (nadd prev addend) result))

(define-rule (nadd (nzero) addend result)
  (connect addend result))

(define two (nadd1 (nadd1 (nzero))))

(define (test wire)
  (wire-print-net (run (wire-print-net wire))))

(test (nadd two two))
```

<details>
<summary>output</summary>

```xml
<net>
<root>
(nadd₇)-result-<>-
</root>
<body>
(nadd1₃)-value!-<>-!target-(nadd₇)
(nadd1₆)-value!-<>-addend-(nadd₇)
(nadd1₅)-value!-<>-prev-(nadd1₆)
(nzero₄)-value!-<>-prev-(nadd1₅)
(nadd1₂)-value!-<>-prev-(nadd1₃)
(nzero₁)-value!-<>-prev-(nadd1₂)
</body>
</net>

<net>
<root>
(nadd1₉)-value!-<>-
</root>
<body>
(nadd1₁₁)-value!-<>-prev-(nadd1₉)
(nadd1₆)-value!-<>-prev-(nadd1₁₁)
(nadd1₅)-value!-<>-prev-(nadd1₆)
(nzero₄)-value!-<>-prev-(nadd1₅)
</body>
</net>
```

</details>

### List

```
(define-node nil value!)
(define-node cons head tail value!)
(define-node append target! rest result)

(define-rule (append (nil) rest result)
  (connect rest result))

(define-rule (append (cons head tail) rest result)
  (cons head (append tail rest) result))

(define-node sole value!)

(define (test wire)
  (wire-print-net (run (wire-print-net wire))))

(test
  (append
    (cons sole (cons sole (cons sole nil)))
    (cons sole (cons sole (cons sole nil)))))
```

<details>
<summary>output</summary>

```xml
<net>
<root>
(append₁₅)-result-<>-
</root>
<body>
(cons₇)-value!-<>-!target-(append₁₅)
(cons₁₄)-value!-<>-rest-(append₁₅)
(cons₁₂)-value!-<>-tail-(cons₁₄)
(sole₁₃)-value!-<>-head-(cons₁₄)
(cons₁₀)-value!-<>-tail-(cons₁₂)
(sole₁₁)-value!-<>-head-(cons₁₂)
(nil₈)-value!-<>-tail-(cons₁₀)
(sole₉)-value!-<>-head-(cons₁₀)
(cons₅)-value!-<>-tail-(cons₇)
(sole₆)-value!-<>-head-(cons₇)
(cons₃)-value!-<>-tail-(cons₅)
(sole₄)-value!-<>-head-(cons₅)
(nil₁)-value!-<>-tail-(cons₃)
(sole₂)-value!-<>-head-(cons₃)
</body>
</net>

<net>
<root>
(cons₁₇)-value!-<>-
</root>
<body>
(cons₁₉)-value!-<>-tail-(cons₁₇)
(sole₆)-value!-<>-head-(cons₁₇)
(cons₂₁)-value!-<>-tail-(cons₁₉)
(sole₄)-value!-<>-head-(cons₁₉)
(cons₁₄)-value!-<>-tail-(cons₂₁)
(sole₂)-value!-<>-head-(cons₂₁)
(cons₁₂)-value!-<>-tail-(cons₁₄)
(sole₁₃)-value!-<>-head-(cons₁₄)
(cons₁₀)-value!-<>-tail-(cons₁₂)
(sole₁₁)-value!-<>-head-(cons₁₂)
(nil₈)-value!-<>-tail-(cons₁₀)
(sole₉)-value!-<>-head-(cons₁₀)
</body>
</net>
```

</details>

### More

For more examples, please see the [examples/](examples/) directory.

## Docs

- [Programming with Interaction Nets](docs/articles/programming-with-interaction-nets.md)
- [反应网编程](docs/articles/反应网编程.md)

## Community

- [Discord / concatenative #inet](https://discord.gg/EcUfwRkbdx)

## Install

Dependencies:

- `libx11`:
  - debian: `sudo apt install libx11-dev`
  - ubuntu: `sudo apt install libx11-dev`

Compile:

```
git clone https://github.com/cicada-lang/inet-lisp
cd inet-lisp
make -j
make test
```

The compiled binary `./bin/inet-lisp` is the command-line program.

```sh
$ ./bin/inet-lisp
inet-lisp 0.1.0

commands:
  run -- run files
  self-test -- run self test
  version -- print version
  help -- print help message
```

For examples:

```sh
./bin/inet-lisp run examples/nat.fth
```

## Development

```shell
make all      # compile src/ files to lib/ and bin/
make run      # compile and run the command-line program
make test     # compile and run test
make clean    # clean up compiled files
```

## Implementations

- [inet-cute](https://github.com/cicada-lang/inet-cute)
- [inet-js](https://github.com/cicada-lang/inet-js)
- [inet-forth](https://github.com/cicada-lang/inet-forth)
- [inet-lisp](https://github.com/cicada-lang/inet-lisp)

## References

**Papers**:

- [1990-interaction-nets](./docs/references/1990-interaction-nets.pdf)
- [1997-interaction-combinators](./docs/references/1997-interaction-combinators.pdf)

**Books**:

- [scalable c](https://github.com/booksbyus/scalable-c)

## Contributions

To make a contribution, fork this project and create a pull request.

Please read the [STYLE-GUIDE.md](STYLE-GUIDE.md) before you change the code.

Remember to add yourself to [AUTHORS](AUTHORS).
Your line belongs to you, you can write a little
introduction to yourself but not too long.

## License

[GPLv3](LICENSE)
