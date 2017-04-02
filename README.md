# Compilo

## Install

```
git clone https://github.com/Marie-Donnie/Compilo.git
make
```

### Make Doxygen

Requires Doxygen ([Download Doxygen](http://www.stack.nl/~dimitri/doxygen/download.html))

```
doxygen doxyconfig
```
Use by launching html/index.html in your browser.

## Use

### Testing

```
./testo
```

### Compiling

General syntax:

```
./compilo <GPL> <GPL-program>
```

As an example, using Ultimate.gpl on somme.ult:

```
./compilo Ultimate gpl somme.ult
```
