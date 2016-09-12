//============================================================================
// Name        	: CircularBuffer.h
// Author      	: Trung Nguyen
// Version     	: 0.01.2016.0910.2243
// Copyright   	:
// Description 	: A ring buffer for raw byte data.
// Note		: Begin at index 0. Write to head; read from tail.
//
//============================================================================
#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

typedef int INDEX;
typedef unsigned char BYTE;

class CircularBuffer {
public:
	explicit CircularBuffer(size_t m_Capacity=10*1024*1024); //10 MB.
	virtual ~CircularBuffer();

	size_t Write(BYTE* pInputData, size_t pDataSize);
	size_t Read(BYTE* pOutData, size_t pDataSize);

private:
	void Step(INDEX &pIndex ,size_t pStepSize);
protected:
	INDEX m_Head;
	INDEX m_Tail;
	BYTE* m_Data;
	size_t m_Capacity;
	size_t m_Free;
};

#endif /* CIRCULARBUFFER_H_ */
