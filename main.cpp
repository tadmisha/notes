#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <filesystem>

using namespace std;
using filesystem::remove_all;
using filesystem::create_directory;

//& Note struct
struct Note {
    string name;
    string text;
    string date;
};


//& Note input
Note input_note() {
    Note note;

    //? Input name
    cout << "Name: ";
    getline(cin, note.name);
    transform(note.name.begin(), note.name.end(), note.name.begin(), [](unsigned char c) { return std::tolower(c); });

    //? Input text
    cout << "Text: ";
    getline(cin, note.text);

    //? Input date
    note.date = (string(__DATE__) + " " + string(__TIME__));

    return note;
}


//& Read file
string read_file(string name) {
    std::ifstream file("notes/" + name + ".txt");

    string content;
    string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            content += line + '\n';
        }
        return content;
    }
    else {
        content = { static_cast<char>(0) };
        return content;
    }
}


//& Creates a file (note)
void create_file(Note note) {
    ofstream file("notes/" + note.name + ".txt");

    if (file.is_open()) {
        file << note.date << std::endl;
        file << note.text << std::endl;
    }
    else {
        std::cout << "Couldn't create a file" << std::endl;
    }
}



int main() {
    string function;

    create_directory("notes");

    cout << "Type /help to get information about every function";
    while (true) {
        cout << endl << "Type function: ";
        cin >> function;
        cin.ignore();

        //? Help function (writes information about every function)
        if (function == "/help") {
            std::cout << "/help - writes information about every function\n/add - adds a new note\n/read - reads a file\n/delete - deletes a note\n/delall - deletes all notes\n/exit - exits from a program";
        }

        //? Add function (add a new note)
        else if (function == "/add") {
            Note note = input_note();
            if (note.name == "") {
                std::cout << "Name cannot be empty" << endl;
                continue;
            }
            create_file(note);
        }

        //? Read function (reads a file)
        else if (function == "/read") {
            string name;
            std::cout << "Input name: ";
            cin >> name;
            transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
            string content = read_file(name);
            if (!content[0]) {
                std::cout << "File doesn't exist" << endl;
                continue;
            }
            std::cout << endl << content;
        }

        //? Delete function (deletes a note (file))
        else if (function == "/delete") {
            string name;
            std::cout << "Input name: ";
            cin >> name;
            std::cout << "Type \"yes\" if you are sure you want to delete this note: ";
            string yes;
            cin >> yes;
            if (yes != "yes") {
                cout << endl;
                continue;
            }
            transform(name.begin(), name.end(), name.begin(), [](unsigned char c) { return std::tolower(c); });
            if (remove(("notes/" + name + ".txt").c_str())) {
                std::cout << "Cannot delete the note" << endl;
                continue;
            }
            std::cout << "The note was deleted";
        }

        //? Delete all function (deletes every single note)
        else if (function == "/delall") {
            string yes;
            cout << "Are you sure you want to delete every single note? Type \"yes\" if you are: ";
            cin >> yes;
            if (yes != "yes") {
                cout << endl;
                continue;
            }
            remove_all("notes");
            create_directory("notes");

            std::cout << "All the notes were deleted";

        }

        //? Exit function (exits the program)
        else if (function == "/exit") {
            std::cout << "See you next time!" << endl;
            break;
        }

        //? Not a function
        else {
            std::cout << "Function doesn't exist";
        }
        cout << endl;
    }

    return 0;
}