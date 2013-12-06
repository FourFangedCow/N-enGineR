
#pragma once

namespace Engine
{
	class Serializer
	{
	public:
		virtual bool Open(const std::string &file) = 0;
		virtual bool IsGood() = 0;
		virtual void ReadInt(int &i) = 0;
		virtual void ReadFloat(float &f) = 0;
		virtual void ReadString(std::string &str) = 0;
		virtual void ReadULong(unsigned long &l) = 0;
	};

	template<typename type> 
	inline void StreamRead(Serializer &stream, type &typeInstance) 
	{
		typeInstance.Serialize(stream);
	}
	inline void StreamRead(Serializer &stream, float &f) {stream.ReadFloat(f);}
	inline void StreamRead(Serializer &stream, unsigned long &l) {stream.ReadULong(l);}
	inline void StreamRead(Serializer &stream, int &i) {stream.ReadInt(i);}
	inline void StreamRead(Serializer &stream, std::string &str) {stream.ReadString(str);}
}