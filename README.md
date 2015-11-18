This library will handle reading packets of a fixed length, into a buffer that the user provides.
The library reads byte per byte, so buffers that use larger than one byte variable types will
have the several bytes input put into the larger than one byte variables.
