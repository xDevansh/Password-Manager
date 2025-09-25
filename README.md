# Password-Manager
A password manager built using C++ from scratch with detailed documentation and security-focused design

This is an attempt of mine / a project to make a password manager using cpp. I wanna learn creating software using cpp (for now) so i first i plan to make a CLI based password manager then shift to GUI, while learning how to make good software.



I will be using symmetric encryption, i.e the same key used for encryption is used for decryption here.
The specific encryption algorithm i will implement is the AES encryption algorithm, AES-256, meaning my encryption key will be 256 bits.

For padding: Since Aes is a block cipher meaning it only works on 16 blocks at a time, our data gets divided into block of 16 and is processed one block at a time, if a block size is less than 16 , then we apply padding. I will be using the PKCS#7 standard for padding. Its rule:  if you need to add N bytes of padding, you add N bytes that each have the value N.
For example: 
If our data is 28 bytes long, the next multiple of 16 is 32. We need 32 - 28 = 4 bytes of padding. So we add four bytes, each with the value 4, to the end of our data. When we decrypt, we look at the very last byte. If it's a 4, we know to discard the last 4 bytes as padding.

Key Derivation:
My app will require user to enter a master password. it will then convert this master password into a 256 bit key for the AES encryption algorithm. To do this a key derivation algo is used.
a) User will input the master password.
b) The master password will/deirved key only be available during the run time of the program, it wont be stored on disk.
c) A key derivation algo will be used to generate a 256 bit key from this master password, I will be using a simple and custom key derivation algorithm.
**WARNING: SINCE MY KEY DERIVATION ALGORITHM IS A SIMPLE AND CUSTOM ALGORITHM, PLEASE DO NOT USE THIS APPLICATION FOR STORING YOUR PASSWORDS CURRENTLY, LATER ON I WILL CHANGE MY CUSTOM ALGO TO A MOR EPOWERFUL AND WELL KNOW KDF SUCH AS ARGON2, PKDF2.**


My current architecture for the password manager:
On Startup:
•	The program will ask for the Master Password from the user.
•	It will look for a file named passwords.dat (it will be a encrypted binary file).
•	It will read the entire encrypted contents of the file into a buffer in memory.
•	It will use the Master Password to derive the AES key and decrypt the entire buffer at once.
•	If successful, it will parse the resulting plaintext and load it into a clean, structured data format in memory.
During Runtime:
•	Every operation performed, like adding a new password, viewing passwords will now interact only with the data in memory. The program will not touch the hard drive again until you are ready to exit. This will be faster, cleaner, and more scalable.
On Exit:
•	When you choose to exit, the program will take the current state of your data in memory.
•	It will serialize this data back into a single plaintext string.
•	It will pad this string to be a multiple of 16 bytes.
•	It will encrypt the entire padded string with the AES key..
•	It will overwrite the old passwords.dat file with this new ciphertext.


