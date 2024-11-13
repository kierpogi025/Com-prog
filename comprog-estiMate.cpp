#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Function prototypes for calculating materials
double calculateCement(double volume);
double calculateSand(double volume);
double calculateGravel(double volume);
double calculateRebar(double volume, const string& component);
double calculateCHB(double wallArea);
double calculatePlywood(double wallArea);
double calculateSteelBars(double volume);
double calculateTiles(double floorArea);
double calculateWood(double floorArea);

void showWelcomeMessage(const string& language);
void showLanguageMenu();
void showHouseTypeMenu(const string& language);
void showMaterialCalculationResults(const string& language, double cement, double sand, double gravel, double rebar, 
                                     double chb, double plywood, double steelBars, double tiles, double wood);

int main() {
    int languageChoice, houseTypeChoice;
    string language = "en";  // Default language is English

    // Show the language selection menu
    showLanguageMenu();
    cin >> languageChoice;

    // Set the language preference based on the input
    if (languageChoice == 2) {
        language = "tl";  // Filipino
    }

    // Display the welcome message in the selected language
    showWelcomeMessage(language);

    // Ask the user to choose the house type (Bungalow or Single Detached)
    showHouseTypeMenu(language);
    cin >> houseTypeChoice;

    // Declare variables for measurements
    double floorArea, wallArea, foundationVolume, columnVolume, ceilingHeight;
    double slabThickness = 0.15;  // Assume 0.15m thickness for floor and roof slabs

    // Material quantities (in cubic meters or bags or pieces)
    double cement, sand, gravel, rebar, chb, plywood, steelBars, tiles, wood;

    // Input measurements
    cout << (language == "en" ? "Enter the floor area per floor (in m²): " : "Ilagay ang lugar ng sahig bawat palapag (sa m²): ");
    cin >> floorArea;
    
    cout << (language == "en" ? "Enter the wall area (in m²): " : "Ilagay ang lugar ng pader (sa m²): ");
    cin >> wallArea;
    
    cout << (language == "en" ? "Enter the height of the ceiling (in meters): " : "Ilagay ang taas ng kisame (sa metro): ");
    cin >> ceilingHeight;
    
    cout << (language == "en" ? "Enter the foundation volume (in m³): " : "Ilagay ang volume ng pundasyon (sa m³): ");
    cin >> foundationVolume;

    cout << (language == "en" ? "Enter the column volume (in m³): " : "Ilagay ang volume ng haligi (sa m³): ");
    cin >> columnVolume;

    // Calculate total floor area based on house type
    double totalFloorArea = floorArea * (houseTypeChoice == 1 ? 1 : 2);  // Bungalow has 1 floor, Single Detached has 2 floors

    // Calculate materials for the foundation
    cement = calculateCement(foundationVolume);
    sand = calculateSand(foundationVolume);
    gravel = calculateGravel(foundationVolume);
    rebar = calculateRebar(foundationVolume, "foundation");

    // Calculate materials for the structure (slabs, columns)
    cement += calculateCement(totalFloorArea * slabThickness);  // Slab cement (floor + ceiling)
    sand += calculateSand(totalFloorArea * slabThickness);
    gravel += calculateGravel(totalFloorArea * slabThickness);
    rebar += calculateRebar(totalFloorArea * slabThickness, "slab");

    // Calculate materials for the walls (CHB, cement, mortar)
    chb = calculateCHB(wallArea);
    plywood = calculatePlywood(wallArea);

    // Calculate steel bars for reinforcement (simplified estimation)
    steelBars = calculateSteelBars(totalFloorArea);

    // Calculate tiles for flooring (assuming tiles are 12" x 12")
    tiles = calculateTiles(totalFloorArea);

    // Estimate wood required for structural framing (approximate based on floor area)
    wood = calculateWood(totalFloorArea);

    // Display material calculation results
    showMaterialCalculationResults(language, cement, sand, gravel, rebar, chb, plywood, steelBars, tiles, wood);

    return 0;
}

// Function to calculate cement
double calculateCement(double volume) {
    return 8 * volume;  // 8 bags of cement per cubic meter
}

// Function to calculate sand
double calculateSand(double volume) {
    return 0.5 * volume;  // 0.5 cubic meters of sand per cubic meter of concrete
}

// Function to calculate gravel
double calculateGravel(double volume) {
    return 0.75 * volume;  // 0.75 cubic meters of gravel per cubic meter of concrete
}

// Function to calculate rebar (steel reinforcement)
double calculateRebar(double volume, const string& component) {
    if (component == "slab") {
        return 100 * volume;  // 100 kg of rebar per cubic meter of concrete for slabs
    } else if (component == "foundation") {
        return 120 * volume;  // 120 kg of rebar per meter for foundation beams
    }
    return 0;
}

// Function to calculate CHB (Concrete Hollow Blocks) for walls
double calculateCHB(double wallArea) {
    // Standard size CHB is 4" x 8" x 16"
    double chbVolume = 0.04 * 0.20 * 0.40;  // 4" x 8" x 16" CHB in cubic meters
    return wallArea / (chbVolume * 1000);  // Divide wall area by the volume of one CHB
}

// Function to calculate plywood for formworks
double calculatePlywood(double wallArea) {
    // Approximate the number of plywood sheets for formworks based on wall area
    double plywoodArea = 1.22 * 2.44;  // Area of 1 sheet of plywood in m²
    return wallArea / plywoodArea;  // Divide wall area by the area of one sheet of plywood
}

// Function to calculate steel bars for reinforcement
double calculateSteelBars(double volume) {
    // Approximate steel bar requirement (simplified)
    return 100 * (volume / 10);  // Estimate 100 kg of steel for every 10m² of floor area
}

// Function to calculate tiles for flooring
double calculateTiles(double floorArea) {
    // Standard tile size: 12" x 12" = 0.0929 m²
    double tileArea = 0.0929;
    return floorArea / tileArea;  // Divide floor area by tile area
}

// Function to calculate wood for structural framing
double calculateWood(double floorArea) {
    // Simplified estimation (assuming 0.2m³ of wood per m² of floor area)
    return floorArea * 0.2;
}

// Function to display welcome message based on language
void showWelcomeMessage(const string& language) {
    if (language == "en") {
        cout << "Welcome to the Construction Material Estimator!" << endl;
    } else {
        cout << "Maligayang pagdating sa Sistema ng Pagtantiya ng Materyales!" << endl;
    }
}

// Function to show language selection menu
void showLanguageMenu() {
    cout << "Choose language:" << endl;
    cout << "1. English" << endl;
    cout << "2. Filipino" << endl;
    cout << "Enter your choice (1 or 2): ";
}

// Function to show house type menu (Bungalow or Single Detached)
void showHouseTypeMenu(const string& language) {
    if (language == "en") {
        cout << "\nChoose the house type:" << endl;
        cout << "1. Bungalow (Single Story)" << endl;
        cout << "2. Single Detached (Two Floors)" << endl;
    } else {
        cout << "\nPiliin ang uri ng bahay:" << endl;
        cout << "1. Bungalow (Isang Palapag)" << endl;
        cout << "2. Single Detached (Dalawang Palapag)" << endl;
    }
    cout << "Enter your choice (1 or 2): ";
}

// Function to display material calculation results
void showMaterialCalculationResults(const string& language, double cement, double sand, double gravel, double rebar, 
                                     double chb, double plywood, double steelBars, double tiles, double wood) {
    if (language == "en") {
        cout << "\nMaterial Estimation Results:" << endl;
        cout << fixed << setprecision(2);
        cout << "Cement: " << cement << " bags" << endl;
        cout << "Sand: " << sand << " cubic meters" << endl;
        cout << "Gravel: " << gravel << " cubic meters" << endl;
        cout << "Rebar: " << rebar << " kg" << endl;
        cout << "Concrete Hollow Blocks (CHB): " << chb << " pieces" << endl;
        cout << "Plywood: " << plywood << " sheets" << endl;
        cout << "Steel Bars: " << steelBars << " kg" << endl;
        cout << "Tiles: " << tiles << " pieces" << endl;
        cout << "Wood for Framing: " << wood << " m³" << endl;
    } else {
        cout << "\nMga Resulta ng Pagtantiya ng Materyales:" << endl;
        cout << fixed << setprecision(2);
        cout << "Semento: " << cement << " sako" << endl;
        cout << "Buhangin: " << sand << " kubiko metro" << endl;
        cout << "Graba: " << gravel << " kubiko metro" << endl;
        cout << "Rebar: " << rebar << " kg" << endl;
        cout << "Concrete Hollow Blocks (CHB): " << chb << " piraso" << endl;
        cout << "Plywood: " << plywood << " piraso" << endl;
        cout << "Steel Bars: " << steelBars << " kg" << endl;
        cout << "Mga Tile: " << tiles << " piraso" << endl;
        cout << "Kahoy para sa Framing: " << wood << " m³" << endl;
    }
}