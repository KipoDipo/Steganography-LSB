# Image Steganography

This is a simple CLI C++ program that implements image steganography by hiding one image within another using the least significant bits (LSB) method.

## Features
- Encode a secret image into a cover image
- Decode the hidden image from an encoded image

## Usage
### Encoding
To encode a secret image into a cover image:
```sh
Steganography encode <original.png> <secret.png>
```
This will generate an `result.png` image containing the hidden image inside the least significant bits of the original image.

### Decoding
To extract the hidden image from an encoded image:
```sh
Ssteganography decode <encoded.png>
```
This will generate a `decoded.png` image revealing the hidden content.

### [Example from Wikipedia](https://en.wikipedia.org/wiki/Steganography)
Encoded image:  
![encoded](https://github.com/user-attachments/assets/33cf9db9-ab6b-482c-8470-cf8e991675b5)  

Decoded image:  
![decoded](https://github.com/user-attachments/assets/5b12fd09-6654-4b1a-850c-f5fbbfd5c4d8)


## How It Works
- The secret image is compressed from 8bits to 2bits per channel
- These bits are embedded into the original image by replacing the 2 least significant bits, thus preserving its visual appearance.
- The decoding process retrieves and scales the least significant bits back to their original range.

## Notes
- The cover image and secret image must have the same dimensions.
- The method uses a 2-bit LSB technique, meaning some data loss in the secret image.
- The code allows for change in the amount of LSB used, by default it's 2 (line 7, `lsb`) 
