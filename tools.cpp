

void drawBorder(int columns, bool isTopBottom = true) {
    for (int i = 0; i < columns; i++) {
        cout << (i == 0 || i == columns - 1 ? "+" : "-");
    }
    cout << endl;
}



void centerText(string text, int width, string color) {
    int padding = (width - text.length()) / 2;
    cout << color << string(padding, ' ') << text << string(padding, ' ') << Color_Reset;
}

void drawMessageBox(string type, string message) {
    int boxWidth = message.length() + 8;
    cout << Color_Red;
    cout << "* " << string(boxWidth - 4, '-') << " *\n";
    cout << "|   " << message << "   |\n";
    cout << "* " << string(boxWidth - 4, '-') << " *\n";
    cout << Color_Reset;
}

