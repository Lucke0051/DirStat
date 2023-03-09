#include <conio.h>
#include <iostream>
#include <filesystem>
#include <windows.h>

using namespace std;
using namespace filesystem;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#define KILO 1000
#define MEGA 1000000
#define GIGA 1000000000

string fileSizeInUnits(unsigned long long int fileSize) {
    if (fileSize >= GIGA) {
        return to_string(fileSize / GIGA) + " GB";
    } else if (fileSize >= MEGA) {
        return to_string(fileSize / MEGA) + " MB";
    } else if (fileSize >= KILO) {
        return to_string(fileSize / KILO) + " kB";
    }

    return to_string(fileSize) + " B";
}

unsigned long long int dive(string initialPath, signed short int depth, bool output) {
    unsigned long long int totalSize = 0;

    for (const auto entry: directory_iterator(initialPath, directory_options::skip_permission_denied)) {
        string filename = entry.path().filename().string();

        if (filename.starts_with("$")) {
            continue;
        }

        if (output) {
            for (short i = 0; i < depth; ++i) {
                cout << "--";
            }

            cout << " " << filename;
        }

        if (entry.is_regular_file()) {
            unsigned long long int fileSize = entry.file_size();

            if (output) {
                cout.width(48 - filename.length());
                cout << fileSizeInUnits(fileSize);
            }

            totalSize += fileSize;
        }


        if (entry.is_directory()) {
            unsigned long long int directorySize = dive(entry.path().string(), depth + 1, false);
            totalSize += directorySize;

            if (output) {
                cout.width(48 - filename.length());
                cout << fileSizeInUnits(directorySize);
            }
        }

        if (output) {
            cout << endl;
        }
    }

    return totalSize;
}

int main() {
    string initialPath = "D:\\Filer\\Repos";

    cout << initialPath << endl;

    long long totalSize = dive(initialPath, 1, true);
    cout << "Total size: " << fileSizeInUnits(totalSize);

    return 0;
}
