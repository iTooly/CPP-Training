#include "File.hpp"
#include "Utils.hpp"

#include <exception>
#include <cassert>

File::File(const std::filesystem::path& path)
	: m_handle(open(path)) { }

File::~File()
{
	try {
		const BOOL status = CloseHandle(m_handle);
		assert(status != FALSE);
	}
	catch (...) {
		PRINT_LOG(L"Something bad happened while closing the File.");
	}
}

Buffer File::read(uint32_t length) const
{
	constexpr LPOVERLAPPED NO_OVERLAP = nullptr;

	Buffer buffer(length, NULL);
	DWORD number_of_bytes_read = 0;

	const BOOL status = ReadFile(m_handle, buffer.data(), length, &number_of_bytes_read, NO_OVERLAP);

	if (status == FALSE) {
		throw std::exception("An error has occurred while trying to read the file.");
	}

	if (number_of_bytes_read != length) {
		throw std::exception("EOF");
	}

	return buffer;
}

HANDLE File::open(const std::filesystem::path& path)
{
	constexpr LPSECURITY_ATTRIBUTES DEFAULT_SECURITY_ATTRIBUTES = nullptr;
	constexpr HANDLE NO_TEMPLATE = nullptr;
	const HANDLE handle = CreateFileW(path.wstring().c_str(),
									  GENERIC_READ,
									  FILE_SHARE_READ,
									  DEFAULT_SECURITY_ATTRIBUTES,
									  OPEN_EXISTING,
									  FILE_ATTRIBUTE_NORMAL,
									  NO_TEMPLATE);

	if (handle == INVALID_HANDLE_VALUE) {
		throw std::exception("An error has occurred while trying to open the file.");
	}

	return handle;
}

uint8_t FileUtils::read_byte(const File& file, BOOL& eof_flag_out)
{
	try
	{
		eof_flag_out = FALSE;
		constexpr size_t FIRST_INDEX = 0;
		return file.read(sizeof(uint8_t))[FIRST_INDEX];
	}
	catch (const std::exception& e) {
		constexpr size_t EOF_LENGTH = 3;
		if (std::strncmp(e.what(), "EOF", EOF_LENGTH) == NULL) {
			eof_flag_out = TRUE;
			return NULL;
		}

		throw e;
	}
}

Buffer FileUtils::read_line(const File& file, BOOL& eof_flag_out)
{
	eof_flag_out = FALSE;
	
	uint8_t byte = 0;
	Buffer buffer;

	constexpr char NEWLINE = '\n';
	
	while (byte != NEWLINE && eof_flag_out == FALSE) {
		// CR: FileUtils is redundent
		byte = FileUtils::read_byte(file, eof_flag_out);
		buffer.push_back(byte);
	}

	return buffer;
}
