# SimplePassMan - Password Manager

SimplePassMan is a simple password manager created in C for educational purposes to learn about encryption and encoding. It uses AES256 encryption and stores data as base64. Please note that this project is not tested and not guaranteed to be safe or bug-free. It uses the OpenSSL library for encryption and encoding.

## Usage

### Compilation

To compile the SimplePassMan password manager, you can use the provided Makefile. Open a terminal and navigate to the project directory, then run the following command:
#### Windows using mingw:
```shell
mingw32-make.exe main
```
#### Linux/mac, untested but should be:
```shell
make main
```

This will compile the project and create an executable named `main`.

### Running SimplePassMan

Once you have compiled the program, you can run it from the terminal with the following command:

```shell
./main AES_KEY_HERE
```

Replace `AES_KEY_HERE` with your AES encryption key.

Optionally, you can specify an output file to store the encrypted data by providing the output file name as a second argument:

```shell
./main AES_KEY_HERE OUTPUT_FILE_HERE
```

Replace `OUTPUT_FILE_HERE` with the desired output file name.

## Disclaimer

SimplePassMan is created for educational purposes and is not intended for production use. It has not been thoroughly tested and may contain security vulnerabilities. Use it at your own risk.

## Dependencies

- OpenSSL library

## License

This project is provided under an open-source license. You can find the license information in the project's source code.

