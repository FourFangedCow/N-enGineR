
#pragma once

#include "Serialization.h"
#include <fstream>

namespace Engine
{
	///Serializer for a simple text file format.
	class TextSerializer : public Serializer
	{
	public:
		std::ifstream stream;
		virtual bool Open(const std::string& file);
		virtual bool IsGood();
		virtual void ReadInt(int& i);
		virtual void ReadFloat(float& f);
		virtual void ReadString(std::string& str);
		virtual void ReadULong(unsigned long& l);
	};
}