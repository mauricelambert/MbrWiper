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
gcc -march=native -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -Wall -Wextra -Werror -O5 MbrWiper.c -o MbrWiper.exe
```

#### Linux

```bash
gcc -march=native -fstack-protector-strong -D_FORTIFY_SOURCE=2 -fPIE -pie -Wl,-z,relro,-z,now,-z,noexecstack -Wall -Wextra -Werror -O5 MbrWiper.c -o MbrWiper
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
 - [Github - Python Windows compiled executable](https://github.com/mauricelambert/MbrWiper/releases/latest/)
 - [SourceForce - Python Windows compiled executable](https://sourceforge.net/projects/MbrWiper/files/)

## Licence

Licensed under the [GPL, version 3](https://www.gnu.org/licenses/).
