![MbrWiper Logo](https://mauricelambert.github.io/info/c/security/MbrWiper_small.png "MbrWiper logo")

# MbrWiper

## Description

This file implements a little MBR Wiper.

## Requirements

 - No requirements

## Download

[Download binaries (Linux and Windows Libraries and examples) from latest github release](https://github.com/mauricelambert/MbrWiper/releases/latest).

## Compile

### Download sources

```bash
git clone https://github.com/mauricelambert/MbrWiper.git
cd MbrWiper
```

#### Windows

```bash
gcc -Wall -Wextra -Werror -O5 MbrWiper.c -o MbrWiper.exe
strip MbrWiper
```

#### Linux

```bash
gcc -Wall -Wextra -Werror -O5 MbrWiper.c -o MbrWiper.exe
strip MbrWiper.exe
```

## Usages

**Privileges required**

### Linux

```bash
./MbrWiper
```

### Windows

```bash
MbrWiper.exe
```

## Links

 - [Github](https://github.com/mauricelambert/MbrWiper/)
 - [Github - compiled executable](https://github.com/mauricelambert/MbrWiper/releases/latest/)
 - [SourceForce - compiled executable](https://sourceforge.net/projects/MbrWiper/files/)

## Licence

Licensed under the [GPL, version 3](https://www.gnu.org/licenses/).
