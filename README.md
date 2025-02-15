# inet-lisp

inet-lisp is an implementation of [interaction nets](https://en.wikipedia.org/wiki/Interaction_nets)
as a [lisp-like language](https://en.wikipedia.org/wiki/lisp_(programming_language)).

The aim of this project is to build
a practical language based on interaction nets,
so that when you write a program in this language,
the running of the program can automatically make use of
any number threads on the machine.

The language uses dynamic type tag,
i.e. it has no static type checking,
because we do not yet fully understand the logic behind
the type system of this model of computation.

We use a lisp-like meta language to build interaction nets.
lisp-like syntax helps us to keep the design flexible
and the implementation simple.

And we will program with interaction nets directly first,
compiling (more conventional) functional programs
to interaction combinators will be explored only later.

## Syntax

```
(define-node <name> <port-name> ...)
(define-rule <pattern> <exp> ...)
(define-rule* (<pattern> ...) <exp> ...)
(define <name> <exp>)
(define (<name> <arg-name> ...) <exp> ...)
```

## Examples

### Natural Number

Define three nodes `(zero)`, `(add1)` and `(add)`:

```
(define-node zero value!)
(define-node add1 prev value!)
(define-node add target! addend result)
```

```
value!   value!        value
  |        |             |
(zero)   (add1)        (add)
           |           /   \
          prev    target!  addend
```

The rule between `(add1)` and `(add)`:

```
(define-rule (add (add1 prev) addend result)
  (add1 (add prev addend) result))
```

```
     value             value            value
       |                 |                |
     (add)      =>                =>    (add1)
     /   \                 \              |
(add1)   addend           addend        (add)
   |                 |                  /   \
 prev              prev              prev   addend
```

The rule between `(zero)` and `(add)`:

```
(define-rule (add (zero) addend result)
  (connect addend result))
```

```
     value          value         value
       |              |             |
     (add)     =>             =>    |
     /   \              \            \
(zero)   addend        addend       addend
```

Example interaction:

```
       |                   |                   |              |
     (add)               (add1)              (add1)         (add1)
     /   \                 |                   |              |
(add1)    (add1)         (add)               (add1)         (add1)
   |        |    =>      /   \       =>        |        =>    |
(add1)    (add1)    (add1)    (add1)         (add)          (add1)
   |        |          |        |            /   \            |
(zero)    (zero)    (zero)    (add1)    (zero)   (add1)     (add1)
                                |                  |          |
                              (zero)             (add1)     (zero)
                                                   |
                                                 (zero)
```

The whole program with test:

```
(define-node zero value!)
(define-node add1 prev value!)
(define-node add target! addend result)

(define-rule (add (zero) addend result)
  (connect addend result))

(define-rule (add (add1 prev) addend result)
  (add1 (add prev addend) result))

(define (two) (add1 (add1 (zero))))

(inspect-run (add (two) (two)))
```

<details>
<summary>output</summary>

```
<net>
<root>
(add₇)-result-<>-
</root>
<body>
(add1₃)-value!-<>-!target-(add₇)
(add1₆)-value!-<>-addend-(add₇)
(add1₅)-value!-<>-prev-(add1₆)
(zero₄)-value!-<>-prev-(add1₅)
(add1₂)-value!-<>-prev-(add1₃)
(zero₁)-value!-<>-prev-(add1₂)
</body>
</net>

<net>
<root>
(add1₉)-value!-<>-
</root>
<body>
(add1₁₁)-value!-<>-prev-(add1₉)
(add1₆)-value!-<>-prev-(add1₁₁)
(add1₅)-value!-<>-prev-(add1₆)
(zero₄)-value!-<>-prev-(add1₅)
</body>
</net>
```

</details>

### List

```
(define-node null value!)
(define-node cons head tail value!)
(define-node append target! rest result)

(define-rule (append (null) rest result)
  (connect rest result))

(define-rule (append (cons head tail) rest result)
  (cons head (append tail rest) result))

(define-node sole value!)

(inspect-run
  (append
    (cons (sole) (cons (sole) (cons (sole) (null))))
    (cons (sole) (cons (sole) (cons (sole) (null))))))
```

<details>
<summary>output</summary>

```
<net>
<root>
(append₁₅)-result-<>-
</root>
<body>
(cons₇)-value!-<>-!target-(append₁₅)
(cons₁₄)-value!-<>-rest-(append₁₅)
(sole₈)-value!-<>-head-(cons₁₄)
(cons₁₃)-value!-<>-tail-(cons₁₄)
(sole₉)-value!-<>-head-(cons₁₃)
(cons₁₂)-value!-<>-tail-(cons₁₃)
(sole₁₀)-value!-<>-head-(cons₁₂)
(null₁₁)-value!-<>-tail-(cons₁₂)
(sole₁)-value!-<>-head-(cons₇)
(cons₆)-value!-<>-tail-(cons₇)
(sole₂)-value!-<>-head-(cons₆)
(cons₅)-value!-<>-tail-(cons₆)
(sole₃)-value!-<>-head-(cons₅)
(null₄)-value!-<>-tail-(cons₅)
</body>
</net>

<net>
<root>
(cons₁₇)-value!-<>-
</root>
<body>
(sole₁)-value!-<>-head-(cons₁₇)
(cons₁₉)-value!-<>-tail-(cons₁₇)
(sole₂)-value!-<>-head-(cons₁₉)
(cons₂₁)-value!-<>-tail-(cons₁₉)
(sole₃)-value!-<>-head-(cons₂₁)
(cons₁₄)-value!-<>-tail-(cons₂₁)
(sole₈)-value!-<>-head-(cons₁₄)
(cons₁₃)-value!-<>-tail-(cons₁₄)
(sole₉)-value!-<>-head-(cons₁₃)
(cons₁₂)-value!-<>-tail-(cons₁₃)
(sole₁₀)-value!-<>-head-(cons₁₂)
(null₁₁)-value!-<>-tail-(cons₁₂)
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
