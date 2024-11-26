#include<iostream>
#include <windows.h>
#include "system.cpp"

void CardTitle(int columns, int cardColumn, int row)
{
    // Horizontal centering only
    int startColumn = (columns - cardColumn) / 2;

    moveCursorToPosition(startColumn, row);
    cout << ".------..------..------..------..------..------..------..------." << endl;

    moveCursorToPosition(startColumn, row + 1);
    cout << "|W.--. ||O.--. ||R.--. ||D.--. ||W.--. ||I.--. ||S.--. ||E.--. |" << endl;

    moveCursorToPosition(startColumn, row + 2);
    cout << "| :/\\: || :/\\: || :(): || :/\\: || :/\\: || (\\/) || :/\\: || (\\/) |" << endl;

    moveCursorToPosition(startColumn, row + 3);
    cout << "| :\\/: || :\\/: || ()() || (__) || :\\/: || :\\/: || :\\/: || :\\/: |" << endl;

    moveCursorToPosition(startColumn, row + 4);
    cout << "| '--'W|| '--'O|| '--'R|| '--'D|| '--'W|| '--'I|| '--'S|| '--'E|" << endl;

    moveCursorToPosition(startColumn, row + 5);
    cout << "`------'`------'`------'`------'`------'`------'`------'`------'" << endl;
}


void BoldTitle(int columns, int cardColumn, int row)
{
    moveCursorToPosition((columns - cardColumn) / 2, row);
    cout << ":::       :::  ::::::::  :::::::::  :::::::::  :::       ::: ::::::::::: ::::::::  :::::::::: " << endl;
    moveCursorToPosition((columns - cardColumn) / 2, row + 1);
    cout << ":+:       :+: :+:    :+: :+:    :+: :+:    :+: :+:       :+:     :+:    :+:    :+: :+:        " << endl;
    moveCursorToPosition((columns - cardColumn) / 2, row + 2);
    cout << "+:+       +:+ +:+    +:+ +:+    +:+ +:+    +:+ +:+       +:+     +:+    +:+        +:+        " << endl;
    moveCursorToPosition((columns - cardColumn) / 2, row + 3);
    cout << "+#+  +:+  +#+ +#+    +:+ +#++:++#:  +#+    +:+ +#+  +:+  +#+     +#+    +#++:++#++ +#++:++#   " << endl;
    moveCursorToPosition((columns - cardColumn) / 2, row + 4);
    cout << "+#+ +#+#+ +#+ +#+    +#+ +#+    +#+ +#+    +#+ +#+ +#+#+ +#+     +#+           +#+ +#+        " << endl;
    moveCursorToPosition((columns - cardColumn) / 2, row + 5);
    cout << " #+#+# #+#+#  #+#    #+# #+#    #+# #+#    #+#  #+#+# #+#+#      #+#    #+#    #+# #+#        " << endl;
    moveCursorToPosition((columns - cardColumn) / 2, row + 6);
    cout << "  ###   ###    ########  ###    ### #########    ###   ###   ########### ########  ########## " << endl;
    moveCursorToPosition((columns - cardColumn) / 2, 19);
}