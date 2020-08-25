#include "File.hpp"
#include "Utils.hpp"

#include <exception>
#include <cassert>

File::File(const std::filesystem::path& path)
	: m_handle(open(path))
{ }

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

uint64_t File::size() const
{
	LARGE_INTEGER file_size{ 0, 0 };
	const BOOL status = GetFileSizeEx(m_handle, &file_size);

	if (status == FALSE) {
		throw std::exception("An error has occurred while trying to get the file size.");
	}

	return file_size.QuadPart;
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

/* TODO: If needed in the future to enable read files with the size bigger then uint32_t max */
Buffer FileUtils::read_all(const File& file)
{
	return file.read(static_cast<uint32_t>(file.size()));
}