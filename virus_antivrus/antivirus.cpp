
#include <iostream>
#include <filesystem>
#include <fstream>
using namespace std;
namespace fs = std::filesystem;

int main() {

    string folder;

    cout << "====================================\n";
    cout << "          C++ ANTIVIRUS\n";
    cout << "====================================\n";

    cout << "Enter the same test folder path: ";
    getline(cin, folder);

    fs::path target(folder);

    if (!fs::exists(target) || !fs::is_directory(target)) {
        cout << "Invalid folder!\n";
        return 1;
    }

    fs::path hidden =
        target.parent_path() / "HiddenFiles";

    fs::path manifest =
        hidden / "manifest.txt";

    if (!fs::exists(manifest)) {
        cout << "No recovery manifest found!\n";
        return 0;
    }

    ifstream input(manifest);

    string filename;
    int detected = 0;
    int restored = 0;

    cout << "\nScanning quarantine...\n";

    while (getline(input, filename)) {

        if (filename.empty())
            continue;

        detected++;

        fs::path source = hidden / filename;
        fs::path destination = target / filename;

        cout << "\n[DETECTED] " << filename << endl;

        if (!fs::exists(source)) {
            cout << "[ERROR] File missing!\n";
            continue;
        }

        if (fs::exists(destination)) {
            cout << "[SKIPPED] Original file already exists.\n";
            continue;
        }

        try {

            fs::rename(source, destination);

            cout << "[RESTORED] " << filename << endl;

            restored++;

        }
        catch (const fs::filesystem_error& e) {

            cout << "[ERROR] " << e.what() << endl;
        }
    }

    input.close();

    cout << "\n====================================\n";
    cout << "             SCAN REPORT\n";
    cout << "====================================\n";

    cout << "Files detected: " << detected << endl;
    cout << "Files restored: " << restored << endl;

    cout << "\nAntivirus operation completed!\n";

    return 0;
}
