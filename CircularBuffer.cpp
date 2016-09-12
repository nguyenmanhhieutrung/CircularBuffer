#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(size_t pCapacity) :
m_Head (0),
m_Tail (0),
m_Capacity (pCapacity),
m_Free (pCapacity)
{
	m_Data = new unsigned char[pCapacity];
}

CircularBuffer::~CircularBuffer() {
	delete [] m_Data;
}

size_t CircularBuffer::Write(BYTE* pInputData, size_t pDataSize) {
	size_t write_size = std::min(pDataSize, m_Free);
	size_t first_piece = std::min(write_size, (m_Capacity-m_Head) );
	size_t second_piece = write_size - first_piece;

	memcpy( (m_Data+m_Head), pInputData, first_piece);
	if ( second_piece > 0 )
		memcpy( m_Data, (pInputData+first_piece), second_piece);

	Step(m_Head,write_size);
	m_Free = m_Free-write_size;

	return write_size;
}

size_t CircularBuffer::Read(BYTE* pOutData, size_t pDataSize) {
	size_t read_size = std::min(pDataSize, m_Capacity-m_Free);
	size_t first_piece = std::min(read_size, (m_Capacity-m_Tail) );
	size_t second_piece = read_size - first_piece;

	memcpy(pOutData, (m_Data+m_Tail), first_piece);
	if ( second_piece > 0 )
		memcpy(pOutData+first_piece, m_Data, second_piece);

	Step(m_Tail,read_size);
	m_Free = m_Free+read_size;
	return read_size;
}

void CircularBuffer::Step(INDEX& pIndex, size_t pStepSize) {
	if( pStepSize >= (m_Capacity-pIndex) )
		pIndex = pIndex+pStepSize-m_Capacity;
	else
		pIndex = pIndex+pStepSize;
}
