#include <stdio.h>
#include <Windows.h>

const wchar_t currentDirectoryIndicator[] = L".";
const wchar_t parentDirectoryIndicator[] = L"..";

void depthPrint(unsigned short* depth, wchar_t* text) {
	unsigned short i;

	for (i = 0; i < *depth; i++) {
		printf("-");
	}

	printf(" ");
	printf("%S", text);
	printf("\n");
}

void readDirectory(wchar_t* path, unsigned short currentDepth) {
	wcscat_s(path, 1, L"\\");
	
	wchar_t pathWithAsterisk[] = *path;

	WIN32_FIND_DATAW findData;
	HANDLE handle = FindFirstFileW(pathWithAsterisk, &findData);

	if (handle == INVALID_HANDLE_VALUE) {
		return;
	}

	do
	{
		if (wcscmp(findData.cFileName, currentDirectoryIndicator) != 0 && wcscmp(findData.cFileName, parentDirectoryIndicator) != 0) {
			depthPrint(&currentDepth, &findData.cFileName);

			//wchar_t newPath = wcscat_s(pathWithEnd, wcslen(findData.cFileName), findData.cFileName);

			//readDirectory(newPath, currentDepth + 1);
		}
	} while (FindNextFileW(handle, &findData) != 0);
}

int main() {
	const wchar_t start[] = L"C:\\Users\\lukas\\Documents\\My Games";

	printf("%S", start);
	printf("\n");

	readDirectory(&start, 1);

	return 0;
}