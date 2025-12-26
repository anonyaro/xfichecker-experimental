#ifndef XFILE_H
#define XFILE_H

#include <string>

class XFile final
{
public:
	XFile() = default;
	uint64_t calculateHash(const std::string& path2file) const;
	bool verifyData(const std::string& path2file, uint64_t& expectedHash);
	~XFile() = default;
	
private:
	char byte;

	static constexpr uint64_t OFFSET = 14695981039346656037ULL;
	static constexpr uint64_t PRIME = 1099511628211ULL;
};

#endif