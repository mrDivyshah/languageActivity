#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;


    map<int, vector<pair<string, vector<string>>>> vocabulary = {
        {1, {
            {"apple", {"A fruit", "Red or green", "Keeps the doctor away", "Can be eaten raw", "Used in pies"}},
            {"table", {"Furniture", "Has legs", "Used for eating", "Can be round or rectangular", "Often found in dining rooms"}},
            {"car", {"Has four wheels", "Used for transportation", "Runs on fuel", "Can be electric", "Can be driven"}},
            {"house", {"Where people live", "Has a roof", "Can have many rooms", "Provides shelter", "Often found in neighborhoods"}},
            {"computer", {"Used for processing data", "Has a screen", "Can connect to the internet", "Used for gaming", "Can be portable"}},
            {"window", {"Opening in a wall", "Lets in light", "Can be opened", "Used for ventilation", "Often has glass"}},
            {"bottle", {"Holds liquids", "Made of glass or plastic", "Can be recycled", "Often has a cap", "Used for storage"}},
            {"phone", {"Used for communication", "Can be mobile", "Has a screen", "Can connect to the internet", "Used for calls"}},
            {"chair", {"Furniture for sitting", "Has four legs", "Can be comfortable", "Used in homes and offices", "Can have arms"}},
            {"book", {"Contains pages", "Used for reading", "Can be fiction or non-fiction", "Often has a cover", "Can be borrowed from libraries"}},
            {"clock", {"Tells time", "Has hands or digital display", "Used for scheduling", "Can be wall-mounted", "Often has a ticking sound"}},
            {"lamp", {"Provides light", "Has a bulb", "Can be used in homes", "Can be table or floor type", "Used for reading"}},
            {"bag", {"Used for carrying items", "Can be made of fabric or plastic", "Often has handles", "Used for shopping", "Can be backpack-style"}},
            {"wallet", {"Holds money", "Can store cards", "Used for personal items", "Often carried in pockets", "Made of leather or fabric"}},
            {"keyboard", {"Used for typing", "Has keys", "Can be mechanical or membrane", "Connected to computers", "Used in gaming"}},
            {"mouse", {"Used for navigating", "Has buttons", "Can be wired or wireless", "Used with computers", "Can be optical or laser"}}
        }},
        {2, {
            {"guitar", {"Musical instrument", "Has six strings", "Used in bands", "Played with fingers or a pick", "Can be acoustic or electric"}},
            {"piano", {"Musical instrument", "Has keys", "Used for playing music", "Can be grand or upright", "Often used in classical music"}},
            {"drum", {"Percussion instrument", "Played with sticks", "Used in bands", "Can be acoustic or electronic", "Provides rhythm"}},
            {"camera", {"Takes photographs", "Can be digital", "Used for capturing memories", "Has lenses", "Can record videos"}},
            {"telescope", {"Used for viewing distant objects", "Has lenses", "Used in astronomy", "Can be refracting or reflecting", "Enables stargazing"}},
            {"microphone", {"Captures sound", "Used in recordings", "Can be wired or wireless", "Used in concerts", "Enhances audio quality"}},
            {"notebook", {"Used for writing", "Contains pages", "Can be spiral-bound", "Used by students", "Often carried in bags"}},
            {"backpack", {"Used for carrying items", "Has straps", "Can be worn on the back", "Used for school", "Often has multiple compartments"}},
            {"umbrella", {"Used for protection from rain", "Can be opened", "Often has a handle", "Can be portable", "Used in sunny weather too"}},
            {"calculator", {"Used for calculations", "Can be scientific", "Has buttons", "Used in math", "Can be portable"}},
            {"tablet", {"Portable device", "Has a touch screen", "Used for browsing", "Can run apps", "Often used for reading"}},
            {"projector", {"Displays images or videos", "Used in presentations", "Projects onto a screen", "Can be portable", "Used in classrooms"}},
            {"printer", {"Produces paper copies", "Can be inkjet or laser", "Used for documents", "Often connected to computers", "Used in offices"}},
            {"scanner", {"Digitizes documents", "Used for archiving", "Can scan photos", "Often connected to computers", "Used in offices"}},
            {"router", {"Connects devices to the internet", "Has antennas", "Can be wireless", "Used in networking", "Transmits data"}}
        }},
        {3, {
            {"sofa", {"Furniture for sitting", "Can be comfortable", "Often found in living rooms", "Can seat multiple people", "Usually has cushions"}},
            {"refrigerator", {"Appliance for cooling food", "Has shelves", "Used in kitchens", "Can be electric", "Keeps food fresh"}},
            {"television", {"Used for watching shows", "Can be smart or traditional", "Displays video", "Can connect to the internet", "Used for entertainment"}},
            {"microwave", {"Appliance for heating food", "Uses electromagnetic waves", "Can cook quickly", "Used in kitchens", "Often has a timer"}},
            {"air conditioner", {"Cools indoor air", "Used in summer", "Can be window-mounted", "Improves comfort", "Can be central or portable"}},
            {"vacuum", {"Cleans floors", "Uses suction", "Can be upright or handheld", "Used in homes", "Collects dust and debris"}},
            {"washing machine", {"Cleans clothes", "Uses water and detergent", "Can be front or top-loading", "Used in homes", "Improves laundry efficiency"}},
            {"dishwasher", {"Cleans dishes", "Uses water and detergent", "Can be built-in or portable", "Saves time", "Used in kitchens"}},
            {"blender", {"Used for mixing", "Can puree ingredients", "Has blades", "Used in kitchens", "Can be electric"}},
            {"toaster", {"Cooks bread", "Can be electric", "Produces toast", "Used in breakfasts", "Can have multiple slots"}},
            {"stove", {"Cooks food", "Can be gas or electric", "Used in kitchens", "Has burners", "Essential for cooking"}},
            {"frying pan", {"Used for cooking", "Has a flat bottom", "Often made of metal", "Used for frying", "Can have a non-stick surface"}},
            {"cutting board", {"Used for food preparation", "Can be made of wood or plastic", "Protects surfaces", "Easy to clean", "Often found in kitchens"}},
            {"pot", {"Used for cooking", "Has a handle", "Can be made of metal or ceramic", "Used for boiling", "Essential for soups"}},
            {"pan", {"Used for cooking", "Flat and shallow", "Can be non-stick", "Used for frying", "Essential for meals"}},
            {"kettle", {"Used for boiling water", "Can be electric", "Used for making tea", "Has a handle", "Common in kitchens"}}
        }},
        {4, {
            {"battery", {"Stores energy", "Powers devices", "Can be recharged", "Comes in different sizes", "Used in electronics"}},
            {"speaker", {"Produces sound", "Connected to devices", "Used for listening", "Can be wireless", "Amplifies audio"}},
            {"laptop", {"Portable computer", "Has a screen", "Used for work or gaming", "Can be battery-powered", "Can connect to Wi-Fi"}},
            {"engine", {"Powers vehicles", "Converts fuel to energy", "Found in cars", "Makes vehicles move", "Runs on gasoline or diesel"}},
            {"network", {"Connects computers", "Transfers data", "Used for communication", "Can be wireless", "Part of the internet"}},
            {"memory", {"Stores information", "Used in computers", "Can be RAM or storage", "Measured in GB or TB", "Temporary or permanent"}},
            {"sensor", {"Detects changes", "Used in devices", "Measures physical quantities", "Converts to signals", "Can be thermal, motion, etc."}},
            {"cable", {"Transmits power or data", "Connects devices", "Can be USB or HDMI", "Made of wires", "Used in electronics"}},
            {"fan", {"Cools devices", "Has blades", "Rotates to produce airflow", "Used in computers", "Prevents overheating"}},
            {"database", {"Stores structured data", "Used in programming", "Can be queried", "Organized in tables", "Contains records"}},
            {"compiler", {"Transforms code", "Used in programming", "Produces executable files", "Ensures syntax correctness", "Essential for development"}},
            {"algorithm", {"Step-by-step procedure", "Used in problem-solving", "Essential in programming", "Can be simple or complex", "Defines logic"}},
            {"function", {"Reusable code block", "Performs specific tasks", "Can take inputs", "Returns outputs", "Fundamental in programming"}},
            {"variable", {"Stores data", "Has a name", "Can change values", "Used in programming", "Essential for logic"}},
            {"object", {"Instance of a class", "Encapsulates data", "Used in OOP", "Can have properties", "Supports methods"}},
            {"class", {"Blueprint for objects", "Defines properties", "Used in OOP", "Can be inherited", "Encapsulates data"}}
        }},
        {5, {
            {"robot", {"Automated machine", "Can perform tasks", "Used in manufacturing", "Can be programmed", "Can have sensors"}},
            {"drone", {"Unmanned aerial vehicle", "Can fly", "Used for photography", "Can be controlled remotely", "Used in deliveries"}},
            {"tablet", {"Portable touch device", "Used for browsing", "Has a screen", "Can run apps", "Used for reading"}},
            {"browser", {"Used to access the internet", "Displays web pages", "Can be Chrome or Firefox", "Can save bookmarks", "Used for searching"}},
            {"webcam", {"Camera for computers", "Used for video calls", "Can be integrated", "Used in streaming", "Connects to the internet"}},
            {"algorithm", {"Set of rules", "Used for problem-solving", "Can be complex", "Implemented in programming", "Defines steps to follow"}},
            {"encryption", {"Secures data", "Transforms information", "Used in cybersecurity", "Protects privacy", "Can be symmetric or asymmetric"}},
            {"firewall", {"Protects networks", "Monitors traffic", "Blocks unauthorized access", "Used in security", "Can be hardware or software"}},
            {"virus", {"Malicious software", "Can infect computers", "Spreads through networks", "Causes damage", "Can be removed with antivirus"}},
            {"malware", {"Malicious software", "Can disrupt systems", "Used to steal data", "Includes viruses and spyware", "Can be harmful"}},
            {"password", {"Secret word or phrase", "Used for authentication", "Protects accounts", "Should be strong", "Can be changed regularly"}},
            {"account", {"User profile", "Used for accessing services", "Contains information", "Can be personal or business", "Requires password"}},
            {"server", {"Provides resources", "Hosts websites", "Handles requests", "Used in networking", "Can be dedicated or shared"}},
            {"cloud", {"Remote storage", "Accessed via the internet", "Used for backup", "Can be public or private", "Offers scalability"}},
            {"website", {"Collection of web pages", "Accessed through browsers", "Used for information", "Can be personal or business", "Includes domains"}},
            {"application", {"Software program", "Used for tasks", "Can be mobile or desktop", "Includes features", "Can be downloaded"}},
            {"platform", {"Base for applications", "Supports development", "Can be software or hardware", "Enables functionality", "Can be cloud-based"}},
            {"integration", {"Combines systems", "Ensures compatibility", "Used in software development", "Facilitates communication", "Enhances functionality"}}
        }}
    };

