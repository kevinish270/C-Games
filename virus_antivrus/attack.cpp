
#include <iostream>
#include <filesystem>
#include <fstream>
using namespace std;
namespace fs = std::filesystem;

int main() {

    string folder;

    cout << "====================================\n";
    cout << "       FILE MOVEMENT SIMULATION\n";
    cout << "====================================\n";

    cout << "Enter test folder path: ";
    getline(cin, folder);

    fs::path target(folder);

    if (!fs::exists(target) || !fs::is_directory(target)) {
        cout << "Invalid folder!\n";
        return 1;
    }

    cout << "\nWARNING: This operation moves files.\n";
    cout << "Use a dedicated test folder only.\n";
    cout << "Continue? (yes/no): ";

    string answer;
    cin >> answer;

    if (answer != "yes") {
        cout << "Operation cancelled.\n";
        return 0;
    }

    fs::path hidden =
        target.parent_path() / "HiddenFiles";

    if (fs::exists(hidden)) {
        cout << "HiddenFiles already exists. "
             << "Inspect it before proceeding.\n";
        return 1;
    }

    fs::create_directories(hidden);

    ofstream manifest(hidden / "manifest.txt");

    if (!manifest) {
        cout << "Cannot create recovery manifest.\n";
        return 1;
    }

    int count = 0;

    for (const auto& entry : fs::directory_iterator(target)) {

        if (!entry.is_regular_file())
            continue;

        string filename =
            entry.path().filename().string();

        fs::path destination = hidden / filename;

        if (fs::exists(destination))
            continue;

        try {

            fs::rename(entry.path(), destination);

            manifest << filename << endl;
            manifest.flush();

            cout << "[MOVED] " << filename << endl;

            count++;

        }
        catch (const fs::filesystem_error& e) {

            cout << "[ERROR] " << filename
                 << ": " << e.what() << endl;
        }
    }

    manifest.close();

    cout << "\nSimulation completed!\n";
    cout << "Files moved: " << count << endl;

    return 0;
}
