#ifndef assets_bitstring_h
#define assets_bitstring_h

class Bitstring {
public:
	char* bytes;
	int size;

	Bitstring(int size);

	Bit operator[]( int i);
private:
};

class Bit {
public:
	char* byte;
	int offset;

	Bit( char* byte, int offet);

	operator bool () const;
	Bit& operator=( const Bit& other);
	Bit& operator=( const bool& other);

	Bit& flip();
private:
};

#endif