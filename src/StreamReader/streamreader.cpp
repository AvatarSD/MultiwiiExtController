#include "streamreader.h"

StreamReader::StreamReader(AsyncIOStream & iface) :
		_iface(iface)
{
	using namespace std::placeholders;
	_iface.read = std::bind(&StreamReader::read, this, _1, _2);
}

StreamReader::~StreamReader()
{
}

void StreamReader::read(const uint8_t * inData, uint32_t byteToRead)
{
	/*outputs*/
	static uint8_t * outHeader, *outData; // = new unsigned char[RX_Buffer];
	static uint32_t OutReadingByte = 0;
	static uint8_t headerLength;
	static uint32_t dataLength;
	static uint8_t CmdCRC, CalcCRC = 0;

	for (uint32_t InputReadingByte = 0; InputReadingByte < byteToRead;
			InputReadingByte++)
	{
		//detect startBytes
		if (OutReadingByte < strlen(startBytes))
		{
			if (inData[InputReadingByte] == startBytes[OutReadingByte])
			{
				OutReadingByte++;
				CalcCRC ^= inData[InputReadingByte];
			}
			else
			{
				OutReadingByte = 0;
				CalcCRC = 0;
			}
		}

		//detect headerLenth (big endian)
		else if ((OutReadingByte >= strlen(startBytes))
				&& (OutReadingByte < strlen(startBytes) + sizeof(headerLength)))
		{
			CalcCRC ^= inData[InputReadingByte];
			headerLength = inData[InputReadingByte];
			headerLength <<= ((sizeof(headerLength) - 1)
					- (OutReadingByte - strlen(startBytes))) * 8;
			if ((sizeof(headerLength) - 1)
					== (OutReadingByte - strlen(startBytes)))
				outHeader = new uint8_t[headerLength];
			OutReadingByte++;
		}

		//detect cmdLenth (big endian)
		else if ((OutReadingByte >= strlen(startBytes) + sizeof(headerLength))
				&& (OutReadingByte
						< strlen(startBytes) + sizeof(headerLength)
								+ sizeof(dataLength)))
		{
			CalcCRC ^= inData[InputReadingByte];
			dataLength = inData[InputReadingByte];
			dataLength <<= ((sizeof(dataLength) - 1)
					- (OutReadingByte - strlen(startBytes)
							- sizeof(headerLength))) * 8;
			if ((sizeof(dataLength) - 1)
					== (OutReadingByte - strlen(startBytes)
							- sizeof(headerLength)))
				outData = new uint8_t[dataLength];
			OutReadingByte++;
		}

		//copy header
		else if ((OutReadingByte
				>= strlen(startBytes) + sizeof(headerLength)
						+ sizeof(dataLength))
				&& (OutReadingByte
						< strlen(startBytes) + sizeof(headerLength)
								+ sizeof(dataLength) + headerLength))
		{
			outHeader[OutReadingByte
					- (strlen(startBytes) + sizeof(headerLength)
							+ sizeof(dataLength))] = inData[InputReadingByte];
			OutReadingByte++;
			CalcCRC ^= inData[InputReadingByte];
		}

		//copy data
		else if ((OutReadingByte
				>= strlen(startBytes) + sizeof(headerLength)
						+ sizeof(dataLength) + headerLength)
				&& (OutReadingByte
						< strlen(startBytes) + sizeof(headerLength)
								+ sizeof(dataLength) + dataLength + headerLength))
		{
			outData[OutReadingByte
					- (strlen(startBytes) + sizeof(headerLength)
							+ sizeof(dataLength) + headerLength)] =
					inData[InputReadingByte];
			OutReadingByte++;
			CalcCRC ^= inData[InputReadingByte];
		}

		//detect and compare crc
		else if (OutReadingByte
				== strlen(startBytes) + sizeof(headerLength)
						+ sizeof(dataLength) + dataLength + headerLength)
		{
			CmdCRC = inData[InputReadingByte];

			//Checking CRC
			if (CalcCRC == CmdCRC)
				//call next func
				takeCmd(Message(outHeader, outData, headerLength, dataLength));

			OutReadingByte = 0;
			CalcCRC = 0;
			delete[] outData;
			delete[] outHeader;
		}
		else if (OutReadingByte
				> strlen(startBytes) + sizeof(headerLength) + sizeof(dataLength)
						+ dataLength + headerLength)
		{
			OutReadingByte = 0;
			CalcCRC = 0;
			delete[] outData;
			delete[] outHeader;
		}
	}
}

void StreamReader::sendCmd(const Message & message)
{
	char cheksum = 0;
	uint8_t * buf = new uint8_t[strlen(startBytes) + sizeof(message.headerLength)
			+ sizeof(message.dataLength) + message.headerLength
			+ message.dataLength + sizeof(cheksum)];

	//write start bytes
	for (unsigned int i = 0; i < strlen(startBytes); i++)
	{
		buf[i] = startBytes[i];
		cheksum ^= buf[i];
	}
	//write header Lenth
	for (unsigned int i = 0; i < sizeof(message.headerLength); i++)
	{
		buf[i + strlen(startBytes)] = (message.headerLength
				>> (((sizeof(message.headerLength) - 1) - i) * 8)) & 0xFF;
		cheksum ^= buf[i + strlen(startBytes)];
	}
	//write command lenth
	for (unsigned int i = 0; i < sizeof(message.dataLength); i++)
	{
		buf[i + strlen(startBytes) + sizeof(message.headerLength)] =
				(message.dataLength
						>> (((sizeof(message.dataLength) - 1) - i) * 8)) & 0xFF;
		cheksum ^= buf[i + strlen(startBytes) + sizeof(message.headerLength)];
	}
	//write header
	for (unsigned int i = 0; i < message.headerLength; i++)
	{
		buf[i + strlen(startBytes) + sizeof(message.headerLength)
				+ sizeof(message.dataLength)] = message.header[i];
		cheksum ^= buf[i + strlen(startBytes) + sizeof(message.headerLength)
				+ sizeof(message.dataLength)];
	}
	//write command
	for (unsigned int i = 0; i < message.dataLength; i++)
	{
		buf[i + strlen(startBytes) + sizeof(message.headerLength)
				+ sizeof(message.dataLength) + message.headerLength] =
				message.data[i];
		cheksum ^= buf[i + strlen(startBytes) + sizeof(message.headerLength)
				+ sizeof(message.dataLength) + message.headerLength];
	}
	//write CRC
	buf[strlen(startBytes) + sizeof(message.headerLength)
			+ sizeof(message.dataLength) + message.headerLength
			+ message.dataLength] = cheksum;

	_iface.write(buf,
			strlen(startBytes) + sizeof(message.headerLength)
					+ sizeof(message.dataLength) + message.headerLength
					+ message.dataLength + sizeof(cheksum));

	delete[] buf;
}

