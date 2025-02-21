# inet-lisp

In 10 years, consumer processors will likely feature 64–128 cores, how to program them?

The graph-based computation model [interaction nets](https://en.wikipedia.org/wiki/Interaction_nets)
is one possible solution, **inet-lisp** is an implementation of it
as a [lisp-like language](https://en.wikipedia.org/wiki/lisp_(programming_language)).

My aim is to build a
practical language based on interaction nets,
so that when you write a program in this language,
the running of the program can automatically make use of
any number cores on the machine.

We use a lisp-like meta language to build interaction nets.
lisp-like syntax helps us to keep the design flexible
and the implementation simple.

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
:root -<>-result-(add₇)
(add₇
 :target! -<>-!value-(add1₃)
 :addend -<>-!value-(add1₆)
 :result -<>-)
(add1₆
 :prev -<>-!value-(add1₅)
 :value! -<>-addend-(add₇))
(add1₅
 :prev -<>-!value-(zero₄)
 :value! -<>-prev-(add1₆))
(zero₄
 :value! -<>-prev-(add1₅))
(add1₃
 :prev -<>-!value-(add1₂)
 :value! -<>-!target-(add₇))
(add1₂
 :prev -<>-!value-(zero₁)
 :value! -<>-prev-(add1₃))
(zero₁
 :value! -<>-prev-(add1₂))
</net>

<net>
:root -<>-!value-(add1₉)
(add1₉
 :prev -<>-!value-(add1₁₁)
 :value! -<>-)
(add1₁₁
 :prev -<>-!value-(add1₆)
 :value! -<>-prev-(add1₉))
(add1₆
 :prev -<>-!value-(add1₅)
 :value! -<>-prev-(add1₁₁))
(add1₅
 :prev -<>-!value-(zero₄)
 :value! -<>-prev-(add1₆))
(zero₄
 :value! -<>-prev-(add1₅))
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
:root -<>-result-(append₁₅)
(append₁₅
 :target! -<>-!value-(cons₇)
 :rest -<>-!value-(cons₁₄)
 :result -<>-)
(cons₁₄
 :head -<>-!value-(sole₈)
 :tail -<>-!value-(cons₁₃)
 :value! -<>-rest-(append₁₅))
(cons₁₃
 :head -<>-!value-(sole₉)
 :tail -<>-!value-(cons₁₂)
 :value! -<>-tail-(cons₁₄))
(cons₁₂
 :head -<>-!value-(sole₁₀)
 :tail -<>-!value-(null₁₁)
 :value! -<>-tail-(cons₁₃))
(null₁₁
 :value! -<>-tail-(cons₁₂))
(sole₁₀
 :value! -<>-head-(cons₁₂))
(sole₉
 :value! -<>-head-(cons₁₃))
(sole₈
 :value! -<>-head-(cons₁₄))
(cons₇
 :head -<>-!value-(sole₁)
 :tail -<>-!value-(cons₆)
 :value! -<>-!target-(append₁₅))
(cons₆
 :head -<>-!value-(sole₂)
 :tail -<>-!value-(cons₅)
 :value! -<>-tail-(cons₇))
(cons₅
 :head -<>-!value-(sole₃)
 :tail -<>-!value-(null₄)
 :value! -<>-tail-(cons₆))
(null₄
 :value! -<>-tail-(cons₅))
(sole₃
 :value! -<>-head-(cons₅))
(sole₂
 :value! -<>-head-(cons₆))
(sole₁
 :value! -<>-head-(cons₇))
</net>

<net>
:root -<>-!value-(cons₁₇)
(cons₁₇
 :head -<>-!value-(sole₁)
 :tail -<>-!value-(cons₁₉)
 :value! -<>-)
(cons₁₉
 :head -<>-!value-(sole₂)
 :tail -<>-!value-(cons₂₁)
 :value! -<>-tail-(cons₁₇))
(cons₂₁
 :head -<>-!value-(sole₃)
 :tail -<>-!value-(cons₁₄)
 :value! -<>-tail-(cons₁₉))
(cons₁₄
 :head -<>-!value-(sole₈)
 :tail -<>-!value-(cons₁₃)
 :value! -<>-tail-(cons₂₁))
(cons₁₃
 :head -<>-!value-(sole₉)
 :tail -<>-!value-(cons₁₂)
 :value! -<>-tail-(cons₁₄))
(cons₁₂
 :head -<>-!value-(sole₁₀)
 :tail -<>-!value-(null₁₁)
 :value! -<>-tail-(cons₁₃))
(null₁₁
 :value! -<>-tail-(cons₁₂))
(sole₁₀
 :value! -<>-head-(cons₁₂))
(sole₉
 :value! -<>-head-(cons₁₃))
(sole₈
 :value! -<>-head-(cons₁₄))
(sole₃
 :value! -<>-head-(cons₂₁))
(sole₂
 :value! -<>-head-(cons₁₉))
(sole₁
 :value! -<>-head-(cons₁₇))
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
