# Password-Manager

A password manager built using C++ from scratch with detailed documentation and security-focused design.

This is an attempt of mine / a project to make a password manager using C++. I want to learn creating software using C++ (for now), so first I plan to make a CLI-based password manager then shift to GUI later.

---

## Current Features

It only allows for a single masterpassword - note to be used, trying to enter with a new master password will result in a master password incorrect error.
Currently this CLI application on starting for the first time prompt user to:
- give a master password 
- then provide the main menu option
- user can choose to do anything, if nothing is added, a empty byte dat gets created.
- on saving and exiting a encrypted dat file gets created
- only that existing dat file can be accessed/ is accessed in the next time program is run
- failure to enter the masterpassword correctly will result in loss of the file **Due to the unsafe/less credible nature of the - custom kdf function, cracking the dat file is possible.
- entering the correct password, u can make chnages to the existing encrypted file.

---

## Encryption

I will be using symmetric encryption, i.e., the same key used for encryption is used for decryption here.  
The specific encryption algorithm I will implement is the AES encryption algorithm, AES-256, meaning my encryption key will be 256 bits.

---

### Padding

Since AES is a block cipher, it only works on 16-byte blocks at a time. Our data gets divided into blocks of 16 and is processed one block at a time. If a block size is less than 16, then padding is needed.

For example:  
If our data is 28 bytes long, the next multiple of 16 is 32. We need 32 - 28 = 4 bytes of padding. So we add four bytes, each with the value 4, to the end of our data. When we decrypt, we look at the last byte to determine how many padding bytes to remove.

---

## Key Derivation

My app will require the user to enter a master password. It will then convert this master password into a 256-bit key for the AES encryption algorithm. To do this, a key derivation algorithm is used:

- User will input the master password.
- The master password or derived key will only be available during the runtime of the program; it won't be stored on disk.
- A key derivation algorithm will be used to generate a 256-bit key from this master password. I will be using a simple and custom key derivation algorithm.

**WARNING:**  
Since my key derivation algorithm is a simple and custom algorithm, please do not use this application for storing your passwords currently. Later on, I will change my custom algorithm to a more secure option.

---

## Current Architecture

### On Startup

- The program will ask for the Master Password from the user.
- It will look for a file named `passwords.dat` (it will be an encrypted binary file).
- It will read the entire encrypted contents of the file into a buffer in memory.
- It will use the Master Password to derive the AES key and decrypt the entire buffer at once.
- If successful, it will parse the resulting plaintext and load it into a clean, structured data format in memory.

### During Runtime

- Every operation performed, like adding a new password or viewing passwords, will now interact only with the data in memory. The program will not touch the hard drive again until you are ready to exit.

### On Exit

- When you choose to exit, the program will take the current state of your data in memory.
- It will serialize this data back into a single plaintext string.
- It will pad this string to be a multiple of 16 bytes.
- It will encrypt the entire padded string with the AES key.
- It will overwrite the old `passwords.dat` file with this new ciphertext.

---
